#define _USE_MATH_DEFINES
#include "D3D9Mgr.h"
#include "../EsoMgr.h"
#include <detours.h>
#include <math.h>
#include <sstream>
#include <vector>

void D3D9Mgr::Initialize()
{

	EsoMgr* esoMgr = EsoMgr::GetSingleton();
	ZoRenderManager* renderManager = esoMgr->GetRenderManager();

	if (renderManager)
	{

		if (renderManager->GetRenderApiType() == ZoRenderManager::RENDER_API::D3D9)
		{

			ZoRenderDeviceD3D9* renderDeviceD3D9 = renderManager->GetRenderDeviceD3D9();

			if (renderDeviceD3D9)
			{

				s_d3d9Device = renderDeviceD3D9->GetDevice();

				if (s_d3d9Device)
				{
					
					DWORD* vTable = *(DWORD**)s_d3d9Device;
					s_resetAddress = vTable[16];
					s_presentAddress = vTable[17];
					s_setDepthStencilSurfaceAddress = vTable[39];

					oPresent = (Present_t)DetourFunction((PBYTE)s_presentAddress, (PBYTE)MyPresent);
					oReset = (Reset_t)DetourFunction((PBYTE)s_resetAddress, (PBYTE)MyReset);
					oSetDepthStencilSurface = (SetDepthStencilSurface_t)DetourFunction((PBYTE)s_setDepthStencilSurfaceAddress, (PBYTE)MySetDepthStencilSurface);

				}
				else
				{
					MessageBoxA(NULL, "Couldn't grab IDirect3DDevice9", "Error", MB_ICONERROR);
				}

			}
			else
			{
				MessageBoxA(NULL, "Couldn't grab ZoRenderDeviceD3D9", "Error", MB_ICONERROR);
			}

		}
		else
		{
			MessageBoxA(NULL, "Game must run in DirectX9 mode !", "Error", MB_ICONERROR);
		}

	}
	else
	{
		MessageBoxA(NULL, "Couldn't grab ZoRenderManager !", "Error", MB_ICONERROR);
	}

}

void D3D9Mgr::Shutdown()
{

	if (s_presentAddress)
	{
		DetourRemove((PBYTE)oPresent, (PBYTE)MyPresent);
		s_presentAddress = NULL;
	}

	if (s_resetAddress)
	{
		DetourRemove((PBYTE)oReset, (PBYTE)MyReset);
		s_resetAddress = NULL;
	}

	if (s_setDepthStencilSurfaceAddress)
	{
		DetourRemove((PBYTE)oSetDepthStencilSurface, (PBYTE)MySetDepthStencilSurface);
		s_setDepthStencilSurfaceAddress = NULL;
	}

}

void D3D9Mgr::OnFrame()
{

	// Save the game's RenderStates, etc
	SaveDeviceState();

	// Setup our view and projection matrix using the game's camera
	SetupViewProjMatrix();

	// Setup our RenderStates for 3D rendering
	SetupRenderStates();

	// Let our main class handle the pulse
	EsoMgr::GetSingleton()->OnFrame();

	// Reset the depth stencil surface
	s_firstSurface = NULL;

	// Restore the game's RenderStates, etc
	RestoreDeviceState();

}

void D3D9Mgr::SetupRenderStates()
{
	if (s_d3d9Device)
	{

		s_d3d9Device->SetPixelShader(NULL);
		s_d3d9Device->SetVertexShader(NULL);
		s_d3d9Device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		s_d3d9Device->SetRenderState(D3DRS_LIGHTING, FALSE);
		s_d3d9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		s_d3d9Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		s_d3d9Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		s_d3d9Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		s_d3d9Device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		s_d3d9Device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
		s_d3d9Device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);

		if (s_firstSurface != NULL)
			s_d3d9Device->SetDepthStencilSurface(s_firstSurface);

	}
}

void D3D9Mgr::SetupViewProjMatrix()
{
	ClientWorld* clientWorld = EsoMgr::GetSingleton()->GetClientWorld();

	if (s_d3d9Device &&
		clientWorld)
	{
		ZoCamera* camera = clientWorld->GetCamera();

		if (camera)
		{

			D3DXMATRIX viewMatrix = camera->GetViewMatrix();
			D3DXMATRIX projMatrix = camera->GetProjectionMatrix();

			s_d3d9Device->SetTransform(D3DTS_VIEW, &viewMatrix);
			s_d3d9Device->SetTransform(D3DTS_PROJECTION, &projMatrix);

		}
	}
}

void D3D9Mgr::Draw3DEllipse(float* pos, float radius, int complexity, DWORD color)
{

	std::vector<CUSTOMVERTEX> V;
	V.resize(complexity + 1);

	V[0].x = 0.0f;
	V[0].y = 0.0f;
	V[0].z = 0.0f;
	V[0].color = color;

	float stepAngle = ((float)M_PI * 2) / ((float)complexity - 1);

	for (int i = 1; i <= complexity; i++)
	{

		float angle = ((float)i - 1) * stepAngle;
		float X = radius * std::cos(angle);
		float Z = -radius * std::sin(angle);

		V[i].x = X;
		V[i].y = 0.f;
		V[i].z = Z;
		V[i].color = color;

	}

	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixTranslation(&worldMatrix, pos[0], pos[1], pos[2]);

	s_d3d9Device->SetTransform(D3DTS_WORLD, &worldMatrix);
	s_d3d9Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, V.size() - 2, V.data(), sizeof(CUSTOMVERTEX));

}

void D3D9Mgr::Draw3DBox(float* pos, float heading, float width, float height, DWORD color)
{
	
	// Ugly sh*t using D3DPT_TRIANGLELIST cause I suck at 3D.
	CUSTOMVERTEX Vertex[] =
	{
		// Bottom
		{ width / 2, 0.f, width / 2, color },
		{ -(width / 2), 0.f, width / 2, color },
		{ width / 2, 0.f, -(width / 2), color },

		{ -(width / 2), 0.f, -(width / 2), color },
		{ -(width / 2), 0.f, width / 2, color },
		{ width / 2, 0.f, -(width / 2), color },

		// Face 1
		{ width / 2, 0.f, width / 2, color },
		{ -(width / 2), 0.f, width / 2, color },
		{ width / 2, height, width / 2, color },

		{ width / 2, height, width / 2, color },
		{ -(width / 2), 0.f, width / 2, color },
		{ -(width / 2), height, width / 2, color },

		// Face 2
		{ -(width / 2), 0.f, -(width / 2), color },
		{ -(width / 2), 0.f, width / 2, color },
		{ -(width / 2), height, width / 2, color },

		{ -(width / 2), height, -(width / 2), color },
		{ -(width / 2), 0.f, -(width / 2), color },
		{ -(width / 2), height, width / 2, color },

		// Face 3
		{ width / 2, 0.f, width / 2, color },
		{ width / 2, 0.f, -(width / 2), color },
		{ width / 2, height, -(width / 2), color },

		{ width / 2, 0.f, width / 2, color },
		{ width / 2, height, width / 2, color },
		{ width / 2, height, -(width / 2), color },

		// Face 4
		{ width / 2, 0.f, -(width / 2), color },
		{ -(width / 2), 0.f, -(width / 2), color },
		{ width / 2, height, -(width / 2), color },

		{ -(width / 2), 0.f, -(width / 2), color },
		{ -(width / 2), height, -(width / 2), color },
		{ width / 2, height, -(width / 2), color },
		
		// Top
		{ width / 2, height, width / 2, color },
		{ -(width / 2), height, width / 2, color },
		{ width / 2, height, -(width / 2), color },

		{ -(width / 2), height, -(width / 2), color },
		{ -(width / 2), height, width / 2, color },
		{ width / 2, height, -(width / 2), color },
	};

	D3DXMATRIX worldMatrix;
	D3DXMATRIX rotMatrix;
	D3DXMatrixRotationY(&rotMatrix, heading);
	D3DXMatrixIdentity(&worldMatrix);
	D3DXMatrixTranslation(&worldMatrix, pos[0], pos[1], pos[2]);

	s_d3d9Device->SetTransform(D3DTS_WORLD, &(rotMatrix * worldMatrix));
	s_d3d9Device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, Vertex, sizeof(CUSTOMVERTEX));

}

void D3D9Mgr::SaveDeviceState()
{
	if (s_d3d9Device)
	{
		s_d3d9Device->GetRenderState(D3DRS_LIGHTING, &s_originalRenderStates[D3DRS_LIGHTING]);
		s_d3d9Device->GetRenderState(D3DRS_ALPHABLENDENABLE, &s_originalRenderStates[D3DRS_ALPHABLENDENABLE]);
		s_d3d9Device->GetRenderState(D3DRS_SRCBLEND, &s_originalRenderStates[D3DRS_SRCBLEND]);
		s_d3d9Device->GetRenderState(D3DRS_DESTBLEND, &s_originalRenderStates[D3DRS_DESTBLEND]);
		s_d3d9Device->GetRenderState(D3DRS_CULLMODE, &s_originalRenderStates[D3DRS_CULLMODE]);
		s_d3d9Device->GetRenderState(D3DRS_ZENABLE, &s_originalRenderStates[D3DRS_ZENABLE]);
		s_d3d9Device->GetRenderState(D3DRS_ZFUNC, &s_originalRenderStates[D3DRS_ZFUNC]);
		s_d3d9Device->GetRenderState(D3DRS_COLORWRITEENABLE, &s_originalRenderStates[D3DRS_COLORWRITEENABLE]);
		s_d3d9Device->GetPixelShader(&s_originalPShader);
		s_d3d9Device->GetVertexShader(&s_originalVShader);
		s_d3d9Device->GetDepthStencilSurface(&s_originalDepthStencilState);
	}
}

void D3D9Mgr::RestoreDeviceState()
{
	if (s_d3d9Device)
	{

		for (auto it = s_originalRenderStates.begin(); it != s_originalRenderStates.end(); it++)
		{
			s_d3d9Device->SetRenderState(it->first, it->second);
		}

		s_d3d9Device->SetPixelShader(s_originalPShader);
		s_d3d9Device->SetVertexShader(s_originalVShader);
		s_d3d9Device->SetDepthStencilSurface(s_originalDepthStencilState);

	}
}

HRESULT __stdcall D3D9Mgr::MyPresent(LPDIRECT3DDEVICE9* pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
	OnFrame();
	return oPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT __stdcall D3D9Mgr::MyReset(LPDIRECT3DDEVICE9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	return oReset(pDevice, pPresentationParameters);
}

HRESULT __stdcall D3D9Mgr::MySetDepthStencilSurface(LPDIRECT3DDEVICE9* pDevice, IDirect3DSurface9* pNewZStencil)
{

	if (s_firstSurface == NULL)
		s_firstSurface = pNewZStencil;

	return oSetDepthStencilSurface(pDevice, pNewZStencil);

}


IDirect3DSurface9* D3D9Mgr::s_originalDepthStencilState;
IDirect3DVertexShader9* D3D9Mgr::s_originalVShader;
IDirect3DPixelShader9* D3D9Mgr::s_originalPShader;
std::map<D3DRENDERSTATETYPE, DWORD> D3D9Mgr::s_originalRenderStates;
IDirect3DSurface9* D3D9Mgr::s_firstSurface;
IDirect3DDevice9* D3D9Mgr::s_d3d9Device;
DWORD D3D9Mgr::s_resetAddress;
DWORD D3D9Mgr::s_presentAddress;
DWORD D3D9Mgr::s_setDepthStencilSurfaceAddress;
Present_t D3D9Mgr::oPresent;
Reset_t D3D9Mgr::oReset;
SetDepthStencilSurface_t D3D9Mgr::oSetDepthStencilSurface;

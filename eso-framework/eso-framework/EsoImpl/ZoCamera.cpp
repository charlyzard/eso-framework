#include "ZoCamera.h"
#include "../Patchables/Offsets.h"

float* ZoCamera::GetViewMatrix() const
{
	return (float*)(this + (DWORD)Offsets::ZoCamera::m_viewMatrix);
}

float* ZoCamera::GetProjectionMatrix() const
{
	return (float*)(this + (DWORD)Offsets::ZoCamera::m_projectionMatrix);
}

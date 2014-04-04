#pragma once
#include "ZoCamera.h"

class ZoCamera
{

public:
	float* GetViewMatrix() const;
	float* GetProjectionMatrix() const;

};
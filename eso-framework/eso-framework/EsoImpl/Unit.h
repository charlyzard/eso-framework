#pragma once

class Unit
{

public:

	enum class UNIT_TYPE : int
	{
		Invalid,
		Player,
		Monster,
		InteractableObject,
		InteractableFixture,
		Anchor,
		SiegeWeapon,
		SimpleInteractableObject,
		SimpleInteractableFixture
	};

	UNIT_TYPE GetType() const;
	char* GetName() const;
	void GetPosition(float* pos) const;
	void GetRenderPosition(float* pos) const;
	float GetRenderHeading() const;

};
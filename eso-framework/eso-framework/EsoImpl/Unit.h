#pragma once
#include "../Patchables/Offsets.h"

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

};
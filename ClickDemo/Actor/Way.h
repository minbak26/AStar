#pragma once

#include "Actor/DrawableActor.h"

class Way : public DrawableActor
{
	RTTI_DECLARATIONS(Way, DrawableActor)
public:
	Way(int x, int y);
};
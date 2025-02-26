#pragma once

#include "Actor/DrawableActor.h"

class MapZero : public DrawableActor
{
	RTTI_DECLARATIONS(MapZero, DrawableActor)

public:
	MapZero(int xPosition, int yPosition);

private:
	int xPosition;
	int yPosition;

	//virtual void Update(float deltaTime) override;
};
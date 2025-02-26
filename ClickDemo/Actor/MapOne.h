#pragma once

#include "Actor/DrawableActor.h"

class MapOne : public DrawableActor
{
	RTTI_DECLARATIONS(MapOne, DrawableActor)

public:
	MapOne(int xPosition, int yPosition);

	int xPosition;
	int yPosition;

	//virtual void Update(float deltaTime) override;
};
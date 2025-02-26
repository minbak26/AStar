#pragma once

#include "Actor/DrawableActor.h"

class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)


public:
	Player();

	int GetPlayerX() const;
	int GetPlayerY() const;

	virtual void Update(float deltaTime) override;
};
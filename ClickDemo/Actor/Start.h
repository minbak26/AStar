#pragma once

#include "Actor/DrawableActor.h"

class Start : public DrawableActor
{
	RTTI_DECLARATIONS(Start, DrawableActor)
public:
	Start();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	// Getter �Լ� �߰�
	int GetPositionX() const;
	int GetPositionY() const;

	int testX = 0;
};
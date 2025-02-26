#pragma once

#include "Actor/DrawableActor.h"

class Start : public DrawableActor
{
	RTTI_DECLARATIONS(Start, DrawableActor)
public:
	Start();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	// Getter 함수 추가
	int GetPositionX() const;
	int GetPositionY() const;

	int testX = 0;
};
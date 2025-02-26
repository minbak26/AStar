#pragma once

#include "Level/Level.h"
#include "../Actor/Start.h"
#include "../Actor/Player.h"
#include "../Actor/way.h"
#include "../Algorithm/Node.h"

class DemoLevel : public Level
{
	// RTTI 정의.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();
	void UpdatePath();
	//맵 바꿔주는 함수
	void PrintMap();
	void ClearMap();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;


protected:
	//스타트, 플레이어 객체 생성


	Start* startActor;
	Player* playerActor;
	AStar* aStar;
	std::vector<std::vector<int>> grid;
	std::vector<Way*> wayPoint;
	std::vector<Node*> path;
	

};
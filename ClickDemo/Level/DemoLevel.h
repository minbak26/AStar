#pragma once

#include "Level/Level.h"
#include "../Actor/Start.h"
#include "../Actor/Player.h"
#include "../Actor/way.h"
#include "../Algorithm/Node.h"

class DemoLevel : public Level
{
	// RTTI ����.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();
	void UpdatePath();
	//�� �ٲ��ִ� �Լ�
	void PrintMap();
	void ClearMap();
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;


protected:
	//��ŸƮ, �÷��̾� ��ü ����


	Start* startActor;
	Player* playerActor;
	AStar* aStar;
	std::vector<std::vector<int>> grid;
	std::vector<Way*> wayPoint;
	std::vector<Node*> path;
	

};
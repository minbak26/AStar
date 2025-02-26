#include "DemoLevel.h"
#include "Actor/Player.h"
#include "Actor/Start.h"
#include "Actor/MapZero.h"
#include "Actor/MapOne.h"
#include <memory>
#include <string.h>
#include <stdio.h>

#include "../Engine/Engine/Engine.h"

#include <vector>
#include "../Algorithm/AStar.h"
#include "../Algorithm/Node.h"
#include <windows.h>
#include "Actor/way.h"

//�ʷ���
std::vector<std::string> mapFiles =
{
    "../Assets/AstarMap.txt",
    "../Assets/AstarMap1.txt",
    "../Assets/AstarMap2.txt",
    "../Assets/AstarMap3.txt",
    "../Assets/AstarMap4.txt"

};

DemoLevel::DemoLevel()
{
    int randomIndex = rand() % mapFiles.size();
    std::string selectMap = mapFiles[randomIndex];

    // �� ������ �ҷ�����
    //
    FILE* file = nullptr;
    fopen_s(&file, selectMap.c_str(), "rb");

    // ���� ���� ���� üũ
    if (file == nullptr)
    {
        printf("������ �� �� �����ϴ�.\n");
        return;
    }

    // ������ ������ �̵��Ͽ� ũ�� Ȯ��
    fseek(file, 0, SEEK_END);
    size_t readSize = ftell(file);
    rewind(file);

    // ���� ũ�Ⱑ 0�̸� ����
    if (readSize == 0)
    {
        printf("������ ��� �ֽ��ϴ�.\n");
        fclose(file);
        return;
    }

    // ���� ���� �� �ʱ�ȭ
    char* buffer = new char[readSize + 1];
    memset(buffer, 0, readSize + 1);

    // ���� �б�
    size_t byteRead = fread(buffer, 1, readSize, file);
    buffer[byteRead] = '\0';  // �����ϰ� �� ���� �߰�
    fclose(file);

    // ��ǥ ����
    int xPosition = 0;
    int yPosition = 0;

    //2���� ���� 
    grid = std::vector<std::vector<int>>(1000, std::vector<int>(1000, 0));

    //�ɹ����� gridũ�� ����
    grid.resize(1000, std::vector<int>(1000, 0));

    for (size_t index = 0; index < byteRead; index++)
    {
        wchar_t mapChar = buffer[index];



        if (mapChar == '\r') continue; // Windows ����(CR) ����

        // ���� ������ ��� �ٹٲ�
        if (mapChar == '\n')
        {

            ++yPosition;
            xPosition = 0;
            continue;
        }


        // 1�̸� MapOne ����
        if (mapChar == '1')
        {
            grid[xPosition][yPosition] = 1;
            AddActor(new MapOne(xPosition, yPosition));
        }
        // 0�̸� MapZero ����
        else if (mapChar == '0')
        {
            grid[xPosition][yPosition] = 0;
            AddActor(new MapZero(xPosition, yPosition));
        }

        // x ����
        xPosition++;
    }
    // �޸� ����
    delete[] buffer;


    bool hasInitialized = false;

    //AStar astar;


    //Start, Player��ü ����
    startActor = new Start();
    playerActor = new Player();

    AddActor(startActor);
    AddActor(playerActor);

}

void DemoLevel::PrintMap()
{
    if (Engine::Get().GetKeyDown(VK_SPACE))
    {
        new DemoLevel();
    }
}


void DemoLevel::Update(float deltaTime)
{
    Super::Update(deltaTime);
    //�Է� ��� false��
    if (Engine::Get().GetKeyDown(MK_LBUTTON))
    {
        //OutputDebugStringA("Ŭ���ȴ�.");//Ŭ���Ǵ°� �Ѵ� Ȯ��
        startActor->SetPosition(Engine::Get().MousePosition());

    }
    if (Engine::Get().GetKeyDown(MK_RBUTTON))
    {
        //OutputDebugStringA("Ŭ���ȴ�.2");
        playerActor->SetPosition(Engine::Get().MousePosition());
    }
   


    //A* �˰��� ���� �� ��� ����
    UpdatePath();

}

void DemoLevel::UpdatePath()
{
    AStar aStar;

    int startGetX = startActor->GetPositionX();
    int startGetY = startActor->GetPositionY();
    int playerGetX = playerActor->GetPlayerX();
    int playerGetY = playerActor->GetPlayerY();

    Node* startNode = new Node(Vector2(startGetX, startGetY));
    Node* goalNode = new Node(Vector2(playerGetX, playerGetY));

    //������ ���� ���ܻ��� ����
    //grid�� 0�̿���
    //
    path = aStar.FindPath(startNode,goalNode, grid);

    if (!path.empty())
    {
        //��� Ȯ��
        //OutputDebugStringA("��θ� ã�ҽ��ϴ�.\n");

       
        //// ���� ��� ����
        ////�ѹ��� �׳� �Ѱܾ� ��
        //if (!wayPoint.empty())
        //{
        //    for (int i = 1; i < (int)(wayPoint.size()-1); ++i)
        //    {
        //        Engine::Get().DestroyActor(wayPoint[i]);
        //    }
        //    wayPoint.clear();
        //}
     
     

        
            //������ ����
       //for (auto* node : path)
       //{
       //    Way* way = new Way(node->GetNodeX(), node->GetNodeY());
       //    wayPoint.push_back(way);
       //    AddActor(way);
       //}
       
    }
    else
    {
        //std::cout << "��θ� ã�� ���߽��ϴ�.\n";
    }

    delete goalNode;
    
}

void DemoLevel::Draw()
{
    AStar aStar;

    int startGetX = startActor->GetPositionX();
    int startGetY = startActor->GetPositionY();
    int playerGetX = playerActor->GetPlayerX();
    int playerGetY = playerActor->GetPlayerY();

    Node* startNode = new Node(Vector2(startGetX, startGetY));
    Node* goalNode = new Node(Vector2(playerGetX, playerGetY));

    path = aStar.FindPath(startNode, goalNode, grid);

    Super::Draw();
    if (!path.empty())
    {
        for (int i = 1; i < path.size() -1; ++i)
         {

           //if (startGetX == path[i]->GetNodeX() && startGetY == path[i]->GetNodeY() ||
           //    playerGetX == path[i]->GetNodeX() && playerGetY == path[i]->GetNodeY())
           //        continue;
         Engine::Get().Draw(Vector2(path[i]->GetNodeX(), path[i]->GetNodeY()), "T", Color::Green);
        }


    }
   
     
}

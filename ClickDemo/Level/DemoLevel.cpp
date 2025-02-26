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

//맵랜덤
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

    // 맵 데이터 불러오기
    //
    FILE* file = nullptr;
    fopen_s(&file, selectMap.c_str(), "rb");

    // 파일 열기 실패 체크
    if (file == nullptr)
    {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 파일의 끝으로 이동하여 크기 확인
    fseek(file, 0, SEEK_END);
    size_t readSize = ftell(file);
    rewind(file);

    // 파일 크기가 0이면 종료
    if (readSize == 0)
    {
        printf("파일이 비어 있습니다.\n");
        fclose(file);
        return;
    }

    // 버퍼 생성 및 초기화
    char* buffer = new char[readSize + 1];
    memset(buffer, 0, readSize + 1);

    // 파일 읽기
    size_t byteRead = fread(buffer, 1, readSize, file);
    buffer[byteRead] = '\0';  // 안전하게 널 종료 추가
    fclose(file);

    // 좌표 변수
    int xPosition = 0;
    int yPosition = 0;

    //2차원 벡터 
    grid = std::vector<std::vector<int>>(1000, std::vector<int>(1000, 0));

    //맴버변수 grid크기 설정
    grid.resize(1000, std::vector<int>(1000, 0));

    for (size_t index = 0; index < byteRead; index++)
    {
        wchar_t mapChar = buffer[index];



        if (mapChar == '\r') continue; // Windows 개행(CR) 무시

        // 개행 문자인 경우 줄바꿈
        if (mapChar == '\n')
        {

            ++yPosition;
            xPosition = 0;
            continue;
        }


        // 1이면 MapOne 생성
        if (mapChar == '1')
        {
            grid[xPosition][yPosition] = 1;
            AddActor(new MapOne(xPosition, yPosition));
        }
        // 0이면 MapZero 생성
        else if (mapChar == '0')
        {
            grid[xPosition][yPosition] = 0;
            AddActor(new MapZero(xPosition, yPosition));
        }

        // x 증가
        xPosition++;
    }
    // 메모리 해제
    delete[] buffer;


    bool hasInitialized = false;

    //AStar astar;


    //Start, Player객체 생성
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
    //입력 계속 false남
    if (Engine::Get().GetKeyDown(MK_LBUTTON))
    {
        //OutputDebugStringA("클릭된다.");//클릭되는거 둘다 확인
        startActor->SetPosition(Engine::Get().MousePosition());

    }
    if (Engine::Get().GetKeyDown(MK_RBUTTON))
    {
        //OutputDebugStringA("클릭된다.2");
        playerActor->SetPosition(Engine::Get().MousePosition());
    }
   


    //A* 알고리즘 실행 및 경로 갱신
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

    //벡터의 범위 예외사항 수정
    //grid가 0이였음
    //
    path = aStar.FindPath(startNode,goalNode, grid);

    if (!path.empty())
    {
        //경로 확인
        //OutputDebugStringA("경로를 찾았습니다.\n");

       
        //// 기존 경로 삭제
        ////한번은 그냥 넘겨야 함
        //if (!wayPoint.empty())
        //{
        //    for (int i = 1; i < (int)(wayPoint.size()-1); ++i)
        //    {
        //        Engine::Get().DestroyActor(wayPoint[i]);
        //    }
        //    wayPoint.clear();
        //}
     
     

        
            //위껄로 수정
       //for (auto* node : path)
       //{
       //    Way* way = new Way(node->GetNodeX(), node->GetNodeY());
       //    wayPoint.push_back(way);
       //    AddActor(way);
       //}
       
    }
    else
    {
        //std::cout << "경로를 찾지 못했습니다.\n";
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

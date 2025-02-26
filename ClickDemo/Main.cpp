#include "Engine/Engine.h"
#include "Level/DemoLevel.h"
#include <windows.h>
int main()
{

	Engine engine;
	engine.LoadLevel(new DemoLevel());
	engine.Run();
}
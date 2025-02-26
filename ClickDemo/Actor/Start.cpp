#include "Start.h"
#include "Engine/Engine.h"

Start::Start()
	: DrawableActor("s")
{
	color = Color::Red;

	position = Vector2(1, 1);
	

}

void Start::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_LBUTTON))
	{
		position = Engine::Get().MousePosition();
	}
}

void Start::Draw()
{
	Super::Draw();


}

int Start::GetPositionX() const
{
	return position.x;
}

int Start::GetPositionY() const
{
	return position.y;
}
#include "Player.h"
#include "Engine/Engine.h"

Player::Player()
	: DrawableActor("e")
{
	color = Color::Blue;
	position = Vector2(5, 5);
}

int Player::GetPlayerX() const
{
	return position.x;
}

int Player::GetPlayerY() const
{
	return position.y;
}

void Player::Update(float deltaTime)
{
	DrawableActor::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	if (Engine::Get().GetKeyDown(VK_RBUTTON))
	{
		position = Engine::Get().MousePosition();
	}
}
#include "Way.h"
#include "Engine/Engine.h"

Way::Way(int x, int y)
	: DrawableActor("T")
{
	color = Color::Green;
	position = Vector2(x, y);
}


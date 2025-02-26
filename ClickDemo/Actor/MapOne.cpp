#include "MapOne.h"

MapOne::MapOne(int xPosition, int yPosition)
	:DrawableActor("#"), xPosition(xPosition), yPosition(yPosition)
{
	
	position = Vector2(xPosition, yPosition);

}

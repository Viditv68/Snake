#include "Food.h"

void Food::genFood()
{
    pos.X = (rand() % WIDTH - 3) + 1;
    pos.Y = (rand() % HEIGHT - 3) + 1;
}

COORD Food::getPos() { return pos; }
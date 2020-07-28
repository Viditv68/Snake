#include <windows.h>
#include <cstdio>

#define WIDTH 50
#define HEIGHT 25

class Food
{
private:
    COORD pos;

public:
    void genFood();

    COORD getPos();
};
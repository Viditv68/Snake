#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<ctime>
#include<Windows.h>
#include "Snake.h"
#include "Food.h"
#define width 50
#define height 25
using namespace std;
using namespace std;

Snake snake({ WIDTH / 2, HEIGHT / 2 }, 1);
Food food;

int score;

void board()
{
    COORD snakePos = snake.getPos();
    COORD food_pos = food.getPos();

    vector<COORD> snake_body = snake.getBody();

    cout << "SCORE : " << score << "\n\n";

    for (int i = 0; i < HEIGHT; i++)
    {
        cout << "\t\t#";
        for (int j = 0; j < WIDTH - 2; j++)
        {
            if (i == 0 || i == HEIGHT - 1) cout << '#';

            else if (i == snakePos.Y && j + 1 == snakePos.X) cout << '0';
            else if (i == food_pos.Y && j + 1 == food_pos.X) cout << '@';

            else
            {
                bool isBodyPart = false;
                for (int k = 0; k < snake_body.size() - 1; k++)
                {
                    if (i == snake_body[k].Y && j + 1 == snake_body[k].X)
                    {
                        cout << 'o';
                        isBodyPart = true;
                        break;
                    }
                }

                if (!isBodyPart) cout << ' ';
            }
        }
        cout << "#\n";
    }
}

int main()
{
    score = 0;
    srand(time(NULL));

    food.genFood();

    char game_over = false;

    while (!game_over)
    {
        board();

        if (_kbhit())
        {
            switch (_getch())
            {
            case 'w': snake.direction('u'); break;
            case 'a': snake.direction('l'); break;
            case 's': snake.direction('d'); break;
            case 'd': snake.direction('r'); break;
            }
        }

        if (snake.collided()) game_over = true;

        if (snake.eaten(food.getPos()))
        {
            food.genFood();
            snake.grow();
            score = score + 10;
        }

        snake.moveSnake();

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
    }
}

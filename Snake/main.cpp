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

void board(string head,string tail)
{
    COORD snakePos = snake.getPos();
    COORD foodPos = food.getPos();

    vector<COORD> snake_body = snake.getBody();

    cout << "SCORE : " << score << "\n\n";

    for (int i = 0; i < HEIGHT; i++)
    {
        cout << "\t\t#";
        for (int j = 0; j < WIDTH - 2; j++)
        {
            if (i == 0 || i == HEIGHT - 1)
            {
                cout << '#';
            }

            else if (i == snakePos.Y && j + 1 == snakePos.X)
            {
                cout << head;
            }
            else if (i == foodPos.Y && j + 1 == foodPos.X)
            {
                cout << '@';
            }

            else
            {
                bool isBodyPart = false;
                for (int k = 0; k < snake_body.size() - 1; k++)
                {
                    if (i == snake_body[k].Y && j + 1 == snake_body[k].X)
                    {
                        cout << tail;
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
    string head;
    string tail;
    bool movingHoizontaly = false;
    bool movingVerticaly = false;
    cout << "Input character for snake head (max 5 characters)" << endl;
    cin >> head;
    cout << "Input character for snake tail" << endl;
    cin >> tail;
    score = 0;
    srand(time(NULL));

    food.genFood();

    char game_over = false;

    while (!game_over)
    {
        board(head,tail);

        if (_kbhit())
        {
            switch (_getch())
            {
            case 'w': 
                if (!movingVerticaly)
                {
                    snake.direction('u');
                    movingHoizontaly = false;
                    movingVerticaly = true;
                }
           
                break;

            case 'a': 
                if (!movingHoizontaly)
                {
                    snake.direction('l');
                    movingHoizontaly = true;
                    movingVerticaly = false;
                }
                 
                break;

            case 's': 
                if (!movingVerticaly)
                {
                    snake.direction('d');
                    movingVerticaly = true;
                    movingHoizontaly = false;
                }
                
                break;

            case 'd': 
                if (!movingHoizontaly)
                {
                    snake.direction('r');
                    movingVerticaly = false;
                    movingHoizontaly = true;
                }
                
                break;
            
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

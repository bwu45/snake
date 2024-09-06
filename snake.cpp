#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

bool gameOver;
const int HEIGHT{20};
const int WIDTH{20};
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100], nTail;

enum Direction
{
    STOP = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

Direction dir;

void startup()
{
    gameOver = false;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
}

void draw()
{
    system("CLS");

    for (int i = 0; i < HEIGHT; i++)
    {
        std::cout << "W";
    }
    std::cout << std::endl;

    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0 || j == (HEIGHT - 1))
            {
                std::cout << "N";
            }
            else if (i == y && j == x)
            {
                std::cout << "@";
            }
            else if (i == fruitY && j == fruitX)
            {
                std::cout << "A";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (i == tailY[k] && j == tailX[k])
                    {
                        std::cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < WIDTH; i++)
    {
        std::cout << "W";
    }
    std::cout << std::endl;
    std::cout << std::endl
              << "SCORE: " << score << std::endl;
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        default:
            break;
        }
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prev2X, prev2Y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }

    if (x < 0 || x > WIDTH-1 || y < 0 || y > HEIGHT)
    {
        gameOver = true;
    }

    for (int i = 0; i < nTail; i++)
    {
        if ((x == tailX[i] && y == tailY[i]) || score == 3600)
        {
            gameOver = true;
        }
    }

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}

int main(int argc, char const *argv[])
{
    startup();
    while (!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(100);
    }
    std::cout << "GAME OVER" << std::endl;
    std::getchar();
    return 0;
}

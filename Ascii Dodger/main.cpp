#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const int width = 21;  // Wider screen
const int height = 15; // Taller screen
const int maxObstacles = 3;

int playerX;
int score;
bool gameOver;

struct Obstacle
{
    int x;
    int y;
};

vector<Obstacle> obstacles;

void clearScreen()
{
    // Clears screen efficiently
    COORD cursorPos;
    cursorPos.X = 0;
    cursorPos.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
}

void resetGame()
{
    playerX = width / 2;
    score = 0;
    gameOver = false;
    obstacles.clear();
    for (int i = 0; i < maxObstacles; i++)
    {
        obstacles.push_back({rand() % (width - 2) + 1, rand() % (height / 2)});
    }
}

void draw()
{
    cout << "ASCII DODGER 🔻   Score: " << score << "\n";

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (x == 0 || x == width - 1)
                cout << "|";
            else
            {
                bool printed = false;

                for (auto &obs : obstacles)
                {
                    if (obs.x == x && obs.y == y)
                    {
                        cout << "*";
                        printed = true;
                        break;
                    }
                }

                if (!printed)
                {
                    if (y == height - 1 && x == playerX)
                        cout << "^";
                    else
                        cout << " ";
                }
            }
        }
        cout << "\n";
    }

    for (int i = 0; i < width; i++)
        cout << "-";
    cout << "\n";
}

void input()
{
    if (_kbhit())
    {
        char key = _getch();
        if (key == 'a' || key == 'A')
            playerX = max(1, playerX - 1);
        else if (key == 'd' || key == 'D')
            playerX = min(width - 2, playerX + 1);
        else if (key == 'q' || key == 'Q')
            gameOver = true;
    }
}

void logic()
{
    for (auto &obs : obstacles)
    {
        obs.y++;

        if (obs.y == height - 1 && obs.x == playerX)
        {
            gameOver = true;
        }

        if (obs.y >= height)
        {
            obs.y = 0;
            obs.x = rand() % (width - 2) + 1;
            score++;
        }
    }
}

int main()
{
    srand(time(0));
    resetGame();

    // Hide blinking cursor
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);

    while (true)
    {
        clearScreen();
        draw();
        input();
        logic();
        Sleep(100);

        if (gameOver)
        {
            clearScreen();
            draw();
            cout << "\nGame Over! Final Score: " << score << "\n";
            cout << "Play again? (Y/N): ";
            char ch;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                resetGame();
                continue;
            }
            else
            {
                break;
            }
        }
    }

    return 0;
}

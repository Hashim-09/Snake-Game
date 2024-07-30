//Author - Hashim Khan
/*
  Written from a tutorial to learn about basics of programming a console game.
*/

#include<iostream>
#include<conio.h>
#include<Windows.h>

using namespace std;
bool gameOver;

const int width = 30;
const int height = 30;
int headX, headY, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;

void Setup()
{
  gameOver = false;
  dir = STOP;
  headX = width / 2;
  headY = height / 2;
  fruitX = rand() % width-1;
  fruitY = rand() % height-1;
  score = 0;
}

void Draw()
{
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
  CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

  // Draw top border
  for (int i=0; i < width; i++)
    cout << "-";
  cout << "-";
  cout << endl;

  //Draw pattern
  for (int i=0; i < height; i++)
  {
    for (int j=0; j < width; j++)
    {
        if (j==0 || j==width-1)
          cout << "|";
        if (i==headY && j==headX)
          cout << "O";
		else if (i==fruitY && j==fruitX)
			cout << "^";
        else
          {
            bool print = false;
            for (int k = 0; k < nTail; k++)
            {
              if (tailX[k] == j && tailY[k] == i)
              {
                cout << "o";
                print = true;
              }
            }
            if (!print)
              cout << " ";
          }
    }
    cout << endl;
  }

  // Draw bottom border
  for (int i=0; i < width; i++)
    cout << "-";
  cout << "-";
  cout << endl;
  cout << "Score: " << score << endl;
}
void Input()
{
  if (_kbhit())
  {
    switch (_getch())
    {
      case 'a':
        dir = LEFT;
        break;
      case 'd':
        dir = RIGHT;
        break;
      case 'w':
        dir = UP;
        break;
      case 's':
        dir = DOWN;
        break;
      case 'x':
        gameOver = true;
        break;
    }
  }
}
void Logic()
{
  int prevX = tailX[0];
  int prevY = tailY[0];
  int prev2X, prev2Y;
  tailX[0] = headX;
  tailY[0] = headY;
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
  case LEFT:
    headX--;
    break;
  case RIGHT:
    headX++;
    break;
  case UP:
    headY--;
    break;
  case DOWN:
  headY++;
    break;
  default:
    break;
  }
  if (headX == width - 1) 
    headX = 0;
  if (headX < 0) 
    headX = width - 1;
  if (headY < 0) 
    headY = height - 1;
  if (headY >= height) 
    headY = 0;
  for (int i = 0; i < nTail; i++)
    if (tailX[i] == headX && tailY[i] == headY)
      gameOver = true;
  if (headX == fruitX && headY == fruitY)
  {
    score += 10;
    fruitX = rand() % (width - 1);
    fruitY = rand() % (height - 1);
    nTail++; 
  }
}
int main()
{
  Setup();
  while (!gameOver)
  {
    Draw();
    Input();
    Logic();
    Sleep(10);
  }
  return 0;
}
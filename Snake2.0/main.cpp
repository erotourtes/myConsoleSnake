#include<iostream>
#include<windows.h>
#include<conio.h> 
#include<ctime>
#include<vector>
#include<thread>
#include"Menu.h"
#include"SetCur.h"

using namespace std;

short int speedid = 5;
bool dieMode = true;

int speedLevel[] = { 0, 35, 70, 105, 140, 175, 210, 245, 280, 315 };

class Fruit;

class Use
{
	friend class Snake;
	friend class PlayersSnake;
	friend void Draw(int width, int height, Snake *snake, Fruit *fruit);

public:
	virtual void generatePosition(int width, int height) = 0;
protected:
	int positionX;
	int positionY;
};
class Fruit :public Use
{
public:
	void generatePosition(int width, int height)
	{
		srand(time(nullptr));
		positionX = rand() % (width - 2) + 1;
		positionY = rand() % (height - 2) + 1;
	}
		

};

class Snake
{
	friend void Draw(int width, int height, Snake *snake, Fruit *fruit);
public:
	Snake();
	
	virtual void move() = 0;
	virtual void eatTail() = 0;
	virtual void eatFruit(Fruit *fruit) = 0;


protected:
	int speed;
	int nTail;
	int score;
	int positionX;
	int positionY;
	bool gameover;
	enum Direction { Stop = 0, Left, Right, Up, Down };
	Direction Dir;
	vector<int> tailX;
	vector<int> tailY;
};
Snake::Snake()
{
	speed = 5;
	nTail = 0;
	score = 0;
	gameover = false;
	positionX = 0;
	positionY = 0;
	tailX.push_back(0);
	tailY.push_back(0);
	tailX.reserve(10);
	tailY.reserve(10);
}



class PlayersSnake: public Snake
{
public:
	PlayersSnake(int width, int heigth);

	void checkMove() 
	{
		if (_kbhit() )
			switch (_getch())
			{
			case 'a':
				Dir = Left;
				break;
			case 'd':
				Dir = Right;
				break;
			case 'w':
				Dir = Up;
				break;
			case 's':
				Dir = Down;
				break;
			}
	}
	void move() override
	{
		checkMove();
			switch (Dir)
			{
			case Left:
				positionX--;
				break;
			case Right:
				positionX++;
				break;
			case Up:
				positionY--;
				break;
			case Down:
				positionY++;
				break;
			}
	}
	void eatFruit(Fruit *fruit) override
	{
		if (positionX == fruit->positionX && positionY == fruit->positionY)
		{
			nTail++;
			score += 10;
			fruit->generatePosition(width, height);
			tailX.push_back(0);
			tailY.push_back(0);
		}
	}
	void checkDie()
	{
		eatTail();
		dieFromWall();
	}
	void dieFromWall()
	{
		if (positionX == 0 || positionX == width -1 || positionY == 0 || positionY == height -1)
		{
			gameover = true;
		}
	}
	void moveTail()
	{
		int prevX = tailX[0];
		int prevY = tailY[0];
		int prevTempX = 0, prevTempY = 0;
		tailX[0] = positionX;
		tailY[0] = positionY;

		for (int i = 1; i < nTail; i++)
		{
			prevTempX = tailX[i];
			prevTempY = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;

			prevX = prevTempX;
			prevY = prevTempY;
		}
	}
	void eatTail()  override 
	{
		for (int i = 0; i < nTail; i++)
		{
			if ((tailX[i] == positionX) && (tailY[i] == positionY))
			{
				gameover = true;
			}
		}
	}
	bool GetGameover() { return gameover; }
private:
	int width;
	int height;
};
PlayersSnake::PlayersSnake(int width, int height)
{
	this->width = width;
	this->height = height;
	positionX = width / 2;
	positionY = height / 2;
}

void DrawFloorAndCeil(int width)
{
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
}
void Draw(int width, int height, Snake *snake, Fruit *fruit)
	{
		int RightHeight = height - 2;
		setcur(0, 0);
		DrawFloorAndCeil(width);

		for (int i = 0; i < RightHeight; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (j == 0 || j == width - 1)
				{
					cout << '#';
				}
				else if (i == snake->positionY - 1 && j == snake->positionX)
				{
					cout << '0';
				}
				else if (i == fruit->positionY - 1 && j == fruit->positionX)
				{
					cout << 'F';
				}
				else
				{
					bool print = true;
					for (int k = 0; k < snake->nTail; k++)
					{
						if ((snake->tailX[k] == j) && (snake->tailY[k] - 1 == i))
						{
							cout << 'o';
							print = false;
						}
						
					}
					if (print)
					{
						cout << ' ';
					}
				}
			}
			cout << endl;
		}

		DrawFloorAndCeil(width);
	}


int main()
{
	

	int width = 21, height = 21;

	PlayersSnake Pl1(width, height);
	Fruit fruit;
	fruit.generatePosition(width, height);

	try
	{
		Menu(speedid, dieMode);
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}

	showStats(width, speedid, dieMode);

	while (Pl1.GetGameover() == 0) // start
	{
		Pl1.moveTail();
		Pl1.move();
		thread th(Draw, width, height, &Pl1, &fruit);
		
		Pl1.eatFruit(&fruit);
		Pl1.checkDie();
		Sleep(speedLevel[speedid  - 1]);

		th.join();
		
	}
	
	return 0;
}
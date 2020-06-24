#include "Menu.h"





bool setByDefault = false;

void FsetByDefault()
{
	if (_kbhit())
		switch (_getch())
		{
		case 's':
			setByDefault = true;
			break;
		default:
			setByDefault = false;
			break;
		}

}

void Menu(short int &speedid, bool &dieMode)
{
	if (!setByDefault)
	{
		FsetByDefault();
		setMenuColour();
		setcur(31, 9);
		std::cout << "Menu";

		setcur(9, 10);
		std::cout << "Press \'s\' to set by default (anytime)";
		Sleep(2500);

		setcur(9, 10);
		std::cout << "Level of Speed (1 - 10) -> \t\t\t";
		std::cin >> speedid;
		if (speedid < 1 || speedid > 10)
		{
			throw speedid;
		}

		setcur(9, 11);
		std::cout << "Die mode (\"true\" - 1 or \"false\" - 0) -> \t";
		std::cin >> dieMode;

		setB_ConsoleColour();
		system("cls");
		setConsoleColour();
	}
	
}
void showStats(const int &width, const short int &speedid, const bool &dieMode)
{
	setMenuColour();
	setcur(width + 1, 1);
	std::cout << "Speed ->    " << speedid;
	setcur(width + 1, 2);
	std::cout << "dieMode ->  " << dieMode;

	setConsoleColour();


} // must be in draw

void setMenuColour()
{
	SetConsoleTitle(L"Snake(Console)");
	SetConsoleTitle(L"Snake(Console)");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE |
		(FOREGROUND_RED | FOREGROUND_GREEN) | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void setB_ConsoleColour()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_RED);
}


void setConsoleColour()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_BLUE |
	(FOREGROUND_RED | FOREGROUND_GREEN) | FOREGROUND_INTENSITY); 
}
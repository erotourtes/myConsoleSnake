#pragma once
#include<iostream>
#include<Windows.h>
#include<conio.h> 
#include "SetCur.h"
#include<functional>
typedef std::function<void()>  Colour;

void Menu(short int &speedid, bool &dieMode);
void showStats(const int &width, const short int &speedid, const bool &dieMode);
void setMenuColour();
void setConsoleColour();
void setB_ConsoleColour();

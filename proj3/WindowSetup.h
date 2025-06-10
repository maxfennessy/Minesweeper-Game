#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>
#include "TextureManager.h"
using namespace sf;
using namespace std;


class WindowSetup
{
public:
	static int columnNum;
	static int rowNum;
	static int mineCount;
	static int xPix;
	static int yPix;
	static int flagCount;
	static bool setMines;
	static bool gameLose;
	static bool gameWin;
	static bool debug;
	static bool clickSlower;
	WindowSetup();
};


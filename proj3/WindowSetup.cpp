#include "WindowSetup.h"

int WindowSetup::columnNum;
int WindowSetup::rowNum;
int WindowSetup::mineCount;
int WindowSetup::xPix;
int WindowSetup::yPix;
int WindowSetup::flagCount;
bool WindowSetup::setMines;
bool WindowSetup::gameLose;
bool WindowSetup::gameWin;
bool WindowSetup::debug;
bool WindowSetup::clickSlower;

WindowSetup::WindowSetup()
{
    ifstream inFile("boards/config.cfg");
    string lineFromFile;

    istringstream stream(lineFromFile);
    string xValueString;
    string yValueString;
    string mineCountString;

    getline(inFile, xValueString, '\n');
    getline(inFile, yValueString, '\n');
    getline(inFile, mineCountString, '\n');


    columnNum = stoi(xValueString);
    rowNum = stoi(yValueString);
    mineCount = stoi(mineCountString);

    xPix = columnNum * 32;
    yPix = 100 + (rowNum * 32);
    setMines = false;
}


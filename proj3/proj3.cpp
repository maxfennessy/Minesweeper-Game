#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector> 
#include "TextureManager.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include "Random.h"
#include "WindowSetup.h"
#include "Tile.h"
using namespace sf;
using namespace std;


void TestCase(string testNum, vector<vector<Tile>> TilesVect)
{

    WindowSetup::mineCount = 0;
    string lineFromFile;
    ifstream inFile("boards/testboard" + testNum + ".cfg");

    int row = 0;
    while (getline(inFile, lineFromFile))
    {
        WindowSetup::gameLose = false;
        WindowSetup::gameWin = false;
        WindowSetup::setMines = true;
        WindowSetup::flagCount = 0;

        for (int i = 0; i < WindowSetup::rowNum; i++)
        {
            for (int j = 0; j < WindowSetup::columnNum; j++)
            {
                Tile tile = Tile(32 * j, 32 * i);
                TilesVect[i][j] = tile;
            }
        }

        istringstream stream(lineFromFile);

        string currentLine;

        getline(stream, currentLine);

        for (int i = 0; i < currentLine.length(); i++) {

            if (currentLine[i] == 1)
            {
                TilesVect[row][i].SetMine(true);
                WindowSetup::mineCount++;
            }
            if (currentLine[i] == 0)
            {
                TilesVect[row][i].SetMine(false);
            }
        }
        row++;
    }


    WindowSetup::setMines = true;
}

void AdjRevealed(vector<vector<Tile>>& TilesVect, int row, int col)
{
    if (TilesVect[row][col].GetMine())
    {
        WindowSetup::gameLose = true;
    }
    else
    {
        if (TilesVect[row][col].GetMinesClose() > 0)
        {
            TilesVect[row][col].SetRevealed();
        }
        if (TilesVect[row][col].GetMinesClose() == 0 && !TilesVect[row][col].GetRevealed() && !TilesVect[row][col].GetFlag())
        {
            TilesVect[row][col].SetRevealed();
            if (row > 0)
            {
                AdjRevealed(TilesVect, row - 1, col);
                if (col > 0)
                {
                    AdjRevealed(TilesVect, row - 1, col - 1);
                }
                if (col < WindowSetup::columnNum - 1)
                {
                    AdjRevealed(TilesVect, row - 1, col + 1);
                }
            }
            if (col < WindowSetup::columnNum - 1)
            {
                AdjRevealed(TilesVect, row, col + 1);
            }
            if (col > 0)
            {
                AdjRevealed(TilesVect, row, col - 1);
            }
            if (row < WindowSetup::rowNum - 1)
            {
                AdjRevealed(TilesVect, row + 1, col);
                if (col > 0)
                {
                    AdjRevealed(TilesVect, row + 1, col - 1);

                }
                if (col < WindowSetup::columnNum - 1)
                {
                    AdjRevealed(TilesVect, row + 1, col + 1);
                }
            }
        }
    }
}


int main()
{
    WindowSetup();

    vector<vector<Tile>> TilesVect(WindowSetup::rowNum, vector<Tile>(WindowSetup::columnNum));

    WindowSetup::gameLose = false;
    WindowSetup::gameWin = false;
    WindowSetup::debug = false;
    WindowSetup::flagCount = 0;


    RenderWindow window(VideoMode(WindowSetup::xPix, WindowSetup::yPix), "Minesweeper");

    Sprite hiddenTileSprite(TextureManager::GetTexture("tile_hidden"));
    Sprite revTileSprite(TextureManager::GetTexture("tile_revealed"));


    Sprite faceHappy(TextureManager::GetTexture("face_happy"));
    Sprite faceLose(TextureManager::GetTexture("face_lose"));
    Sprite faceWin(TextureManager::GetTexture("face_win"));
    Sprite debugSprite(TextureManager::GetTexture("debug"));
    Sprite testOne(TextureManager::GetTexture("test_1"));
    Sprite testTwo(TextureManager::GetTexture("test_2"));
    Sprite testThree(TextureManager::GetTexture("test_3"));

    Sprite mine(TextureManager::GetTexture("mine"));
    Sprite flag(TextureManager::GetTexture("flag"));




    for (int i = 0; i < WindowSetup::rowNum; i++)
    {
        for (int j = 0; j < WindowSetup::columnNum; j++)
        {
            Tile tile = Tile(32 * j, 32 * i);
            TilesVect[i][j] = tile;
        }
    }


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();

        for (int i = 0; i < WindowSetup::rowNum; i++)
        {
            for (int j = 0; j < WindowSetup::columnNum; j++)
            {
                if (!TilesVect[i][j].GetRevealed())
                {
                    hiddenTileSprite.setPosition(32 * j, 32 * i);
                    window.draw(hiddenTileSprite);
                }
                if (TilesVect[i][j].GetRevealed())
                {
                    revTileSprite.setPosition(32 * j, 32 * i);
                    window.draw(revTileSprite);
                    if (TilesVect[i][j].GetMine())
                    {
                        mine.setPosition(32 * j, 32 * i);
                        window.draw(mine);
                    }
                    else
                    {
                        int mines = TilesVect[i][j].GetMinesClose();
                        if (mines > 0)
                        {
                            string file = "number_";
                            int numb = mines;
                            file += to_string(numb);
                            Sprite num(TextureManager::GetTexture(file));
                            num.setPosition(32 * j, 32 * i);
                            window.draw(num);
                        }
                    }
                }
                if (TilesVect[i][j].GetFlag())
                {
                    flag.setPosition(32 * j, 32 * i);
                    window.draw(flag);
                }
                if (WindowSetup::debug)
                {
                    if (TilesVect[i][j].GetMine())
                    {
                        mine.setPosition(32 * j, 32 * i);
                        window.draw(mine);
                    }
                }
                if (WindowSetup::gameLose)
                {
                    faceLose.setPosition(WindowSetup::xPix / 2.0f, WindowSetup::yPix - 100.0f);
                    window.draw(faceLose);
                    if (TilesVect[i][j].GetMine())
                    {
                        revTileSprite.setPosition(32 * j, 32 * i);
                        window.draw(revTileSprite);
                        mine.setPosition(32 * j, 32 * i);
                        window.draw(mine);
                    }
                }
            }
        }
        if (WindowSetup::gameWin)
        {
            faceWin.setPosition(WindowSetup::xPix / 2.0f, WindowSetup::yPix - 100.0f);
            window.draw(faceWin);
        }
        if (!WindowSetup::gameWin && !WindowSetup::gameLose)
        {
            faceHappy.setPosition(WindowSetup::xPix / 2.0f, WindowSetup::yPix - 100.0f);
            window.draw(faceHappy);
        }
      debugSprite.setPosition((WindowSetup::xPix / 2.0f) + 128.0f, WindowSetup::yPix - 100.0f);
        window.draw(debugSprite);
       testOne.setPosition((WindowSetup::xPix / 2.0f) + 192.0f, WindowSetup::yPix - 100.0f);
        window.draw(testOne);
        testTwo.setPosition((WindowSetup::xPix / 2.0f) + 256.0f, WindowSetup::yPix - 100.0f);
       window.draw(testTwo);
       testThree.setPosition((WindowSetup::xPix / 2.0f) + 320.0f, WindowSetup::yPix - 100.0f);
        window.draw(testThree);


        bool neg = false;
        int minesLeft = WindowSetup::mineCount - WindowSetup::flagCount;
        if (minesLeft < 0)
        {
            minesLeft -= 2 * minesLeft;
            neg = true;
        }
        int hundo = minesLeft / 100;
        int tenth = (minesLeft % 100) / 10;
        int ones = minesLeft % 10;
        Sprite hundreds(TextureManager::GetTextureCounter(hundo));
        hundreds.setPosition(32, WindowSetup::yPix - 100.0f);
        window.draw(hundreds);
        Sprite tens(TextureManager::GetTextureCounter(tenth));
        tens.setPosition(64, WindowSetup::yPix - 100.0f);
        window.draw(tens);
        Sprite onesplace(TextureManager::GetTextureCounter(ones));
        onesplace.setPosition(96, WindowSetup::yPix - 100.0f);
        window.draw(onesplace);
        if (neg)
        {
            Sprite negative(TextureManager::GetTextureCounter(10));
            negative.setPosition(0, WindowSetup::yPix - 100.0f);
            window.draw(negative);
        }




        if (!WindowSetup::setMines)
        {
            for (int x = 0; x < WindowSetup::mineCount; x++)
            {
                int i = Random::Int(0, (WindowSetup::rowNum)-1);
                int j = Random::Int(0, (WindowSetup::columnNum)-1);

                while (TilesVect[i][j].GetMine())
                {
                    i = Random::Int(0, (WindowSetup::rowNum)-1);
                    j = Random::Int(0, (WindowSetup::columnNum)-1);
                }
                TilesVect[i][j].SetMine(true);
            }

            for (int i = 0; i < WindowSetup::rowNum; i++)
            {
                for (int j = 0; j < WindowSetup::columnNum; j++)
                {
                    if (!WindowSetup::setMines)
                    {
                        TilesVect[i][j].SetMinesClose(TilesVect);
                    }
                }
            }
            WindowSetup::setMines = true;
        }

        int index = 0;
        for (int i = 0; i < WindowSetup::rowNum; i++)
        {
            for (int j = 0; j < WindowSetup::columnNum; j++)
            {
                if (!TilesVect[i][j].GetMine() && !TilesVect[i][j].GetRevealed())
                {
                    index++;
                }
            }
        }
        if (index == 0 && (WindowSetup::mineCount - WindowSetup::flagCount) == 0)
        {
            WindowSetup::gameWin = true;
        } 

        WindowSetup::clickSlower = true;
        if (event.type == sf::Event::MouseButtonPressed)
        {
            Vector2i mousePosition = Mouse::getPosition(window);

            int colNum = (mousePosition.x / 32) * 32;
            int rowNum = (mousePosition.y / 32) * 32;

            for (int i = 0; i < WindowSetup::rowNum; i++)
            {
                for (int j = 0; j < WindowSetup::columnNum; j++)
                {
                    if (TilesVect[i][j].GetTileX() == colNum && TilesVect[i][j].GetTileY() == rowNum)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left && !TilesVect[i][j].GetFlag() && !WindowSetup::gameLose && !WindowSetup::gameWin)
                        {
                            AdjRevealed(TilesVect, i, j);
                        }
                        if (event.mouseButton.button == sf::Mouse::Right && !TilesVect[i][j].GetRevealed() && !WindowSetup::gameLose && !WindowSetup::gameWin)
                        {
                            if (TilesVect[i][j].GetFlag() && WindowSetup::clickSlower)
                            {
                                TilesVect[i][j].SetFlag(false);
                                WindowSetup::flagCount--;
                                WindowSetup::clickSlower = false;
                            }
                            else if (!TilesVect[i][j].GetFlag() && WindowSetup::clickSlower)
                            {
                                TilesVect[i][j].SetFlag(true);
                                WindowSetup::flagCount++;
                                WindowSetup::clickSlower = false;

                            }
                        }
                    }
                }
            }
            WindowSetup::clickSlower = true;
            if (event.mouseButton.button == sf::Mouse::Left && debugSprite.getGlobalBounds().contains(colNum, rowNum) && !WindowSetup::gameLose && !WindowSetup::gameWin)
            {
                WindowSetup::debug = !WindowSetup::debug;
                WindowSetup::clickSlower = false;

            }

            if (event.mouseButton.button == sf::Mouse::Left && testOne.getGlobalBounds().contains(colNum, rowNum))
            {

                WindowSetup::gameLose = false;
                WindowSetup::gameWin = false;
                WindowSetup::setMines = false;
                WindowSetup::flagCount = 0;
                WindowSetup::mineCount = 0;

                for (int i = 0; i < WindowSetup::rowNum; i++)
                {
                    for (int j = 0; j < WindowSetup::columnNum; j++)
                    {
                        Tile tile = Tile(32 * j, 32 * i);
                        TilesVect[i][j] = tile;
                    }
                }


                ifstream inFile("boards/testboard1.brd");
                string lineFromFile;

                istringstream stream(lineFromFile);
                string currentLine;
                int row = 0;
                while (getline(inFile, currentLine, '\n'))
                {
                    for (int i = 0; i < currentLine.length(); i++) {

                        if (currentLine[i] == '1')
                        {
                            TilesVect[row][i].SetMine(true);
                            WindowSetup::mineCount++;
                        }
                        if (currentLine[i] == '0')
                        {
                            TilesVect[row][i].SetMine(false);
                        }
                    }
                    row++;
                }
                for (int i = 0; i < WindowSetup::rowNum; i++)
                {
                    for (int j = 0; j < WindowSetup::columnNum; j++)
                    {
                        if (!WindowSetup::setMines)
                        {
                            TilesVect[i][j].SetMinesClose(TilesVect);
                        }
                    }
                }
                WindowSetup::setMines = true;
            }

            if (event.mouseButton.button == sf::Mouse::Left && testTwo.getGlobalBounds().contains(colNum, rowNum))
            {

                WindowSetup::gameLose = false;
                WindowSetup::gameWin = false;
                WindowSetup::setMines = false;
                WindowSetup::flagCount = 0;
                WindowSetup::mineCount = 0;

                for (int i = 0; i < WindowSetup::rowNum; i++)
                {
                    for (int j = 0; j < WindowSetup::columnNum; j++)
                    {
                        Tile tile = Tile(32 * j, 32 * i);
                        TilesVect[i][j] = tile;
                    }
                }


                ifstream inFile("boards/testboard2.brd");
                string lineFromFile;

                istringstream stream(lineFromFile);
                string currentLine;
                int row = 0;
                while (getline(inFile, currentLine, '\n'))
                {
                    for (int i = 0; i < currentLine.length(); i++) {

                        if (currentLine[i] == '1')
                        {
                            TilesVect[row][i].SetMine(true);
                            WindowSetup::mineCount++;
                        }
                        if (currentLine[i] == '0')
                        {
                            TilesVect[row][i].SetMine(false);
                        }
                    }
                    row++;
                }
                for (int i = 0; i < WindowSetup::rowNum; i++)
                {
                    for (int j = 0; j < WindowSetup::columnNum; j++)
                    {
                        if (!WindowSetup::setMines)
                        {
                            TilesVect[i][j].SetMinesClose(TilesVect);
                        }
                    }
                }
                WindowSetup::setMines = true;
            }

            if (event.mouseButton.button == sf::Mouse::Left && testThree.getGlobalBounds().contains(colNum, rowNum))
            {

                WindowSetup::gameLose = false;
                WindowSetup::gameWin = false;
                WindowSetup::setMines = false;
                WindowSetup::flagCount = 0;
                WindowSetup::mineCount = 0;

                for (int i = 0; i < WindowSetup::rowNum; i++)
                {
                    for (int j = 0; j < WindowSetup::columnNum; j++)
                    {
                        Tile tile = Tile(32 * j, 32 * i);
                        TilesVect[i][j] = tile;
                    }
                }


                ifstream inFile("boards/testboard3.brd");
                string lineFromFile;

                istringstream stream(lineFromFile);
                string currentLine;
                int row = 0;
                while (getline(inFile, currentLine, '\n'))
                {
                    for (int i = 0; i < currentLine.length(); i++) {

                        if (currentLine[i] == '1')
                        {
                            TilesVect[row][i].SetMine(true);
                            WindowSetup::mineCount++;
                        }
                        if (currentLine[i] == '0')
                        {
                            TilesVect[row][i].SetMine(false);
                        }
                    }
                    row++;
                }
                for (int i = 0; i < WindowSetup::rowNum; i++)
                {
                    for (int j = 0; j < WindowSetup::columnNum; j++)
                    {
                        if (!WindowSetup::setMines)
                        {
                            TilesVect[i][j].SetMinesClose(TilesVect);
                        }
                    }
                }
                WindowSetup::setMines = true;
            }

            if (event.mouseButton.button == sf::Mouse::Left && faceHappy.getGlobalBounds().contains(colNum, rowNum))
            {
                WindowSetup::gameLose = false;
                WindowSetup::gameWin = false;
                WindowSetup::setMines = false;
                WindowSetup::flagCount = 0;
                for (int i = 0; i < WindowSetup::rowNum; i++)
                {
                    for (int j = 0; j < WindowSetup::columnNum; j++)
                    {
                        Tile tile = Tile(32 * j, 32 * i);
                        TilesVect[i][j] = tile;
                    }
                }
            }

        }

        window.display();
    }


    // clears textures
    TextureManager::Clear();
    return 0;
}
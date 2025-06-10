#pragma once
#include "WindowSetup.h"

class Tile
{
	bool mine;
	bool flag;
	bool revealed;
	int xPos;
	int yPos;
	int minesClose;
	int col;
	int row;
public:
	Tile();
	Tile(int xPos_, int yPos_);
	int GetTileX();
	int GetTileY();
	bool GetMine();
	bool GetFlag();
	bool GetRevealed();
	void SetMine(bool mine_);
	void SetFlag(bool flag_);
	//vector<vector<Tile>> SetRevealedRec(vector<vector<Tile>> TilesVect);
	void SetRevealed();
	void SetMinesClose(vector<vector<Tile>> TilesVect);
	int GetMinesClose();
	int GetCol();
	int GetRow();
};


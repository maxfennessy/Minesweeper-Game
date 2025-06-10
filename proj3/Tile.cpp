#include "Tile.h"

Tile::Tile()
{
	xPos = 0;
	yPos = 0;
	minesClose = 0;
	col = 0;
	row = 0;
	mine = false;
	flag = false;
	revealed = false;
}

Tile::Tile(int xPos_, int yPos_)
{
	xPos = xPos_;
	yPos = yPos_;
	col = xPos_ / 32;
	row = yPos_ / 32;
	minesClose = 0;
	mine = false;
	flag = false;
	revealed = false;
}

int Tile::GetTileX()
{
	return xPos;
}

int Tile::GetTileY()
{
	return yPos;
}

bool Tile::GetMine()
{
	return mine;
}

bool Tile::GetFlag()
{
	return flag;
}

bool Tile::GetRevealed()
{
	return revealed;
}

void Tile::SetMine(bool mine_)
{
	mine = mine_;
}

void Tile::SetFlag(bool flag_)
{
	flag = flag_;
}

void Tile::SetRevealed()
{
	revealed = true;
}

//vector<vector<Tile>> Tile::SetRevealedRec(vector<vector<Tile>> TilesVect)
//{
//	vector<vector<Tile>> temp(WindowSetup::rowNum, vector<Tile>(WindowSetup::columnNum));
//
//	for (int i = 0; i < WindowSetup::rowNum; i++)
//	{
//		for (int j = 0; j < WindowSetup::columnNum; j++)
//		{
//			temp[i][j] = TilesVect[i][j];
//		}
//	}
//
//	Tile tile = TilesVect[row][col];
//	tile.SetRevealed();
//	temp[row][col] = tile;
//
//	if (!tile.GetMine() && tile.GetMinesClose() == 0)
//	{
//
//
//		// middle
//		if (col > 0 && col < WindowSetup::columnNum - 1 && row > 0 && row < WindowSetup::rowNum - 1)
//		{
//			//for (int i = col - 1; i <= col + 1; i++)
//			//{
//				//for (int j = row - 1; j <= row + 1; j++)
//				//{
//					if (!TilesVect[row -1 ][ col - 1].GetRevealed())
//					{
//						cout << "k" << endl;
//						TilesVect[row - 1][col - 1].SetRevealedRec(temp);
//
//
//					}
//				//}
//			//}
//		}
//		// corners
//		// top left
//		if (col == 0 && row == 0)
//		{
//			for (int i = 0; i <= 1; i++)
//			{
//				for (int j = 0; j <= 1; j++)
//				{
//					if (!TilesVect[j][i].GetRevealed())
//					{
//						TilesVect[j][i].SetRevealedRec(temp);
//					}
//				}
//			}
//		}
//		// top right
//		if (col == 0 && row == WindowSetup::rowNum - 1)
//		{
//			for (int i = 0; i <= 1; i++)
//			{
//				for (int j = WindowSetup::rowNum - 2; j <= WindowSetup::rowNum - 1; j++)
//				{
//					if (!TilesVect[j][i].GetRevealed())
//					{
//						TilesVect[j][i].SetRevealedRec(temp);
//					}
//				}
//			}
//		}
//		// bottom left
//		if (col == WindowSetup::columnNum - 1 && row == 0)
//		{
//			for (int i = WindowSetup::columnNum - 2; i <= WindowSetup::columnNum - 1; i++)
//			{
//				for (int j = 0; j <= 1; j++)
//				{
//					if (!TilesVect[j][i].GetRevealed())
//					{
//						TilesVect[j][i].SetRevealedRec(temp);
//					}
//				}
//			}
//		}
//
//		// bottom right
//		if (col == WindowSetup::columnNum - 1 && row == WindowSetup::rowNum - 1)
//		{
//			for (int i = WindowSetup::columnNum - 2; i <= WindowSetup::columnNum - 1; i++)
//			{
//				for (int j = WindowSetup::rowNum - 2; j <= WindowSetup::rowNum - 1; j++)
//				{
//					if (!TilesVect[j][i].GetRevealed())
//					{
//						TilesVect[j][i].SetRevealedRec(temp);
//					}
//				}
//			}
//		}
//
//		// left edge
//		if (col == 0 && row > 0 && row < WindowSetup::rowNum - 1)
//		{
//			for (int j = 0; j <= 1; j++)
//			{
//				for (int i = row - 1; i <= row + 1; i++)
//				{
//					if (TilesVect[i][j].GetRevealed())
//					{
//						TilesVect[i][j].SetRevealedRec(temp);
//					}
//				}
//			}
//		}
//
//		// top edge
//		if (row == 0 && col > 0 && col < WindowSetup::columnNum - 1)
//		{
//			for (int i = 0; i <= 1; i++)
//			{
//				for (int j = col - 1; j <= col + 1; j++)
//				{
//					if (TilesVect[i][j].GetRevealed())
//					{
//						TilesVect[i][j].SetRevealedRec(temp);
//					}
//				}
//			}
//		}
//
//		// right edge
//		if (col == WindowSetup::columnNum - 1 && row > 0 && row < WindowSetup::rowNum - 1)
//		{
//			for (int j = WindowSetup::columnNum - 2; j <= WindowSetup::columnNum - 1; j++)
//			{
//				for (int i = row - 1; i <= row + 1; i++)
//				{
//					if (TilesVect[i][j].GetRevealed())
//					{
//						TilesVect[i][j].SetRevealedRec(temp);
//					}
//				}
//			}
//		}
//
//		// bottom edge
//		if (row == WindowSetup::rowNum - 1 && col > 0 && col < WindowSetup::columnNum - 1)
//		{
//			for (int i = WindowSetup::rowNum - 2; i <= WindowSetup::rowNum - 1; i++)
//			{
//				for (int j = col - 1; j <= col + 1; j++)
//				{
//					if (TilesVect[i][j].GetRevealed())
//					{
//						TilesVect[i][j].SetRevealedRec(temp);
//					}
//				}
//			}
//		}
//	}
//	return temp;
//}

void Tile::SetMinesClose(vector<vector<Tile>> TilesVect)
{
	if (!mine)
	{
		// middle
		if (col > 0 && col < WindowSetup::columnNum - 1 && row > 0 && row < WindowSetup::rowNum - 1)
		{
			for (int i = col - 1; i <= col + 1; i++)
			{
				for (int j = row - 1; j <= row + 1; j++)
				{
					if (TilesVect[j][i].GetMine())
					{
						minesClose++;
					}
				}
			}
		}
		// corners
		// top left
		if (col == 0 && row == 0)
		{
			for (int i = 0; i <= 1; i++)
			{
				for (int j = 0; j <= 1; j++)
				{
					if (TilesVect[j][i].GetMine())
					{
						minesClose++;
					}
				}
			}
		}
		// top right
		if (col == 0 && row == WindowSetup::rowNum - 1)
		{
			for (int i = 0; i <= 1; i++)
			{
				for (int j = WindowSetup::rowNum - 2; j <= WindowSetup::rowNum - 1; j++)
				{
					if (TilesVect[j][i].GetMine())
					{
						minesClose++;
					}
				}
			}
		}
		// bottom left
		if (col == WindowSetup::columnNum - 1 && row == 0)
		{
			for (int i = WindowSetup::columnNum - 2; i <= WindowSetup::columnNum - 1; i++)
			{
				for (int j = 0; j <= 1; j++)
				{
					if (TilesVect[j][i].GetMine())
					{
						minesClose++;
					}
				}
			}
		}

		// bottom right
		if (col == WindowSetup::columnNum - 1 && row == WindowSetup::rowNum - 1)
		{
			for (int i = WindowSetup::columnNum - 2; i <= WindowSetup::columnNum - 1; i++)
			{
				for (int j = WindowSetup::rowNum - 2; j <= WindowSetup::rowNum - 1; j++)
				{
					if (TilesVect[j][i].GetMine())
					{
						minesClose++;
					}
				}
			}
		}

		// left edge
		if (col == 0 && row > 0 && row < WindowSetup::rowNum - 1)
		{
			for (int j = 0; j <= 1; j++)
			{
				for (int i = row - 1; i <= row + 1; i++)
				{
					if (TilesVect[i][j].GetMine())
					{
						minesClose++;
					}
				}
			}
		}

		// top edge
		if (row == 0 && col > 0 && col < WindowSetup::columnNum - 1)
		{
			for (int i = 0; i <= 1; i++)
			{
				for (int j = col - 1; j <= col + 1; j++)
				{
					if (TilesVect[i][j].GetMine())
					{
						minesClose++;
					}
				}
			}
		}

		// right edge
		if (col == WindowSetup::columnNum - 1 && row > 0 && row < WindowSetup::rowNum - 1)
		{
			for (int j = WindowSetup::columnNum - 2; j <= WindowSetup::columnNum - 1; j++)
			{
				for (int i = row - 1; i <= row + 1; i++)
				{
					if (TilesVect[i][j].GetMine())
					{
						minesClose++;
					}
				}
			}
		}

		// bottom edge
		if (row == WindowSetup::rowNum - 1 && col > 0 && col < WindowSetup::columnNum - 1)
		{
			for (int i = WindowSetup::rowNum - 2; i <= WindowSetup::rowNum - 1; i++)
			{
				for (int j = col - 1; j <= col + 1; j++)
				{
					if (TilesVect[i][j].GetMine())
					{
						minesClose++;
					}
				}
			}
		}
	}
}

int Tile::GetMinesClose()
{
	return minesClose;
}

int Tile::GetCol()
{
	return col;
}
int Tile::GetRow()
{
	return row;
}
#include "Board.h"



Board::Board(Pieces * pPieces, int pScreenHeight)
{
	// Get the screen height
	mScreenHeight = pScreenHeight;

	// Get the pointer to the pieces class
	mPieces = pPieces;

	//Init the board blocks with free positions
	InitBoard();
}

/*
--------------------------------------------------------------
Initialises the board and sets all blocks to free position
--------------------------------------------------------------
*/
void Board::InitBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			mBoard[i][j] = POS_FREE;
		}
			
	}
		
}

/*
--------------------------------------------------------------
Stores a piece in the board by filling blocks

Parameters:
	pX			X position
	pY			Y position
	pPiece		Piece to draw
	pRot		rotation of piece
--------------------------------------------------------------
*/
void Board::StorePiece(int pX, int pY, int pPiece, int pRot)
{
	//Sotre each block of the piece of board
	for (int ia = pX, ib = 0; ia < pX + PIECE_BLOCKS; ia++, ib++)
	{
		for (int ja = pY, jb = 0; ja < pY + PIECE_BLOCKS; ja++, jb++)
		{
			//store only the blocks that arent 0
			if (mPieces->GetBlockType(pPiece, pRot, jb, ib) != 0)
			{
				mBoard[ia][ja] = POS_FILLED;
			}
		}
	}
}

/*
--------------------------------------------------------------
Checks if a piece has hit the board limit

Returns:
	Returns true if a pool is outside the board parameters
--------------------------------------------------------------
*/
bool Board::IsGameOver()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (mBoard[i][0] == POS_FILLED)
			return true;
	}

	return false;
}

/*
--------------------------------------------------------------
Deletes a line by moving all the lines above it down one row

Parameters:
	pY			vertical position of the line to delete
--------------------------------------------------------------
*/
void Board::DeleteLine(int pY)
{
	//move all the lines one row down
	for (int j = pY; j > 0; j--)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			mBoard[i][j] = mBoard[i][j - 1];
		}
	}
}

/*
--------------------------------------------------------------
Deletes all the lines that need to be removed
--------------------------------------------------------------
*/
void Board::DeletePossibleLines()
{

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		int x = 0;
		while (x < BOARD_WIDTH)
		{
			if (mBoard[x][i] != POS_FILLED)
				break;

			x++;
		}

		if (x == BOARD_WIDTH)
		{
			DeleteLine(i);
		}
	}
}

/*
--------------------------------------------------------------
Checks if a block on the board is free

Parameters:
	pX			X position of block
	pY			Y postion of block

Returns:
	Returns true if the blocks position is free
--------------------------------------------------------------
*/
bool Board::IsFreeBlock(int pX, int pY)
{
	if (mBoard[pX][pY] == POS_FREE)
		return true;

	else
		return false;
}

/*
--------------------------------------------------------------
Returns the x postion of a block

Parameters:
	pPos		the x postion of the block

Returns:
	x postion in pixels of the block on the board
--------------------------------------------------------------
*/
int Board::GetXPosInPix(int pPos)
{
	return  ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pPos * BLOCK_SIZE));
}

/*
--------------------------------------------------------------
Returns the y postion of a block

Parameters:
	pPos		the y postion of the block

Returns:
	y postion in pixels of the block on the board
--------------------------------------------------------------
*/
int Board::GetYPosInPix(int pPos)
{
	return ((mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE));
}

/*
--------------------------------------------------------------
Checks if piece can be stored at this position without any collision

Parameters:
	pX			the x postion in blocks
	pY			the y postion in blocks
	pPiece		Piece to draw
	pRot		rotation of the piece

Returns:
	Returns true if movement is possible without collisions
--------------------------------------------------------------
*/
bool Board::IsPossibleMovement(int pX, int pY, int pPiece, int pRot)
{
	for (int ia = pX, ib = 0; ia < pX + PIECE_BLOCKS; ia++, ib++)
	{
		for (int ja = pY, jb = 0; ja < pY + PIECE_BLOCKS; ja++, jb++)
		{
			// Check if the piece is outside the limits of the board
			if (ia < 0 || ia > BOARD_WIDTH - 1 || ja > BOARD_HEIGHT - 1)
			{
				if (mPieces->GetBlockType(pPiece, pRot, jb, ib) != 0)
					return 0;
			}

			if (ja >= 0)
			{
				if ( (mPieces->GetBlockType(pPiece, pRot, jb, ib) != 0) && (!IsFreeBlock(ia, ja)) )
				{
					return false;
				}
			}
		}

	}

	
	return true;
}







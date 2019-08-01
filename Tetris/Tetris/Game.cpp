#include "Game.h"
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()



Game::Game(Board * pBoard, Pieces * pPieces, IO * pIO, int pScreenHeight)
{
	mScreenHeight = pScreenHeight;

	// Get the pointer to the Board and Pieces classes
	mBoard = pBoard;
	mPieces = pPieces;
	mIO = pIO;

	// Game initialization
	InitGame();
}

/*
--------------------------------------------------------------
Drawss all objects necessary for the game
--------------------------------------------------------------
*/
void Game::DrawScene()
{
	DrawBoard();
	DrawPiece(mPosX, mPosY, mPiece, mRot);
	DrawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);
}

/*
--------------------------------------------------------------
Creates a random new piece
--------------------------------------------------------------
*/
void Game::CreateNewPiece()
{
	mPiece = mNextPiece;
	mRot = mNextRotation;
	mPosX = (BOARD_WIDTH / 2) + mPieces->GetXPos(mPiece, mRot);
	mPosY = mPieces->GetYPos(mPiece, mRot);

	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
}

/*
--------------------------------------------------------------
Gets a random int

Parameters:
	pA			minum number it can be
	pB			maximum number it can be

Returns:
	Returns a random integer
--------------------------------------------------------------
*/
int Game::GetRand(int pA, int pB)
{
	return rand() % (pB - pA +1) + pA;
}

/*
--------------------------------------------------------------
Initializes games parameters
--------------------------------------------------------------
*/
void Game::InitGame()
{
	srand(time(NULL));

	
	mPiece = GetRand(0, 6);
	mRot = GetRand(0, 3);
	mPosX = (BOARD_WIDTH / 2) + mPieces->GetXPos(mPiece, mRot);
	mPosY = mPieces->GetYPos(mPiece, mRot);

	
	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
	mNextPosX = BOARD_WIDTH + 5;
	mNextPosY = 5;
}

/*
--------------------------------------------------------------
Iterates through each piece and draws the block in

Parameters:
	pX			x position in blocks
	pY			y position in blocks
	pPiece		piece to draw	
	pRot		rotation of the piece

--------------------------------------------------------------
*/
void Game::DrawPiece(int pX, int pY, int pPiece, int pRot)
{
	color mColor;

	//postion of the blocks in pixels on screen
	int mPixelX = mBoard->GetXPosInPix(pX);
	int mPixelY = mBoard->GetYPosInPix(pY);

	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			switch (mPieces->GetBlockType(pPiece, pRot, j, i))
			{
				case 1: 
					mColor = GREEN;
					break;
				case 2:
					mColor = BLUE;
					break;

			}

			if (mPieces->GetBlockType(pPiece, pRot, j, i) != 0)
				mIO->DrawRectangle(mPixelX + i * BLOCK_SIZE, mPixelY + j * BLOCK_SIZE,(mPixelX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,(mPixelY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, mColor);
		}
	}

}

/*
--------------------------------------------------------------
Draws out the board
--------------------------------------------------------------
*/
void Game::DrawBoard()
{
	int mX = BOARD_POSITION - (BLOCK_SIZE*(BOARD_WIDTH / 2)) - 1;
	int mXOutline = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

	mIO->DrawRectangle(mX - BOARD_LINE_WIDTH, mY, mX, mScreenHeight - 1, BLUE);

	mIO->DrawRectangle(mXOutline, mY, mXOutline + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);
	
	mX += 1;
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			// Check if the block is filled, if so, draw it
			if (!mBoard->IsFreeBlock(i, j))
				mIO->DrawRectangle(mX + i * BLOCK_SIZE, mY + j * BLOCK_SIZE, (mX + i * BLOCK_SIZE) + BLOCK_SIZE - 1, (mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, RED);
		}
	}

}

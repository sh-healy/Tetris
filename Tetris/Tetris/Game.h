#ifndef _GAME_
#define _GAME_

// ------ Includes -----

#include "Board.h"
#include "Pieces.h"
#include "IO.h"
#include <time.h>

// ------ Defines -----

#define WAIT_TIME 700           // Number of milliseconds that the piece remains before going 1 block down 


class Game
{
public:

	Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight);

	void DrawScene();
	void CreateNewPiece();

	int mPosX;			// X position of the piece falling down
	int mPosY;          // Y position of the piece falling down
	int mPiece;			// position of the piece falling down
	int mRot;           // rotation the piece falling down

private:

	int mScreenHeight;   // Screen height in pixels
	int mNextPosX;
	int mNextPosY;      
	int mNextPiece;
	int mNextRotation;  

	Board *mBoard;
	Pieces *mPieces;
	IO *mIO;

	int GetRand(int pA, int pB);
	void InitGame();
	void DrawPiece(int pX, int pY, int pPiece, int pRot);
	void DrawBoard();
};

#endif  _GAME_
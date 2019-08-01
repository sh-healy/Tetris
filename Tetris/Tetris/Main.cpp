#include "Game.h"
#include <iostream>

#undef main
int main ()  
{
	std::cout << "test";
	IO mIO;
	int mScreenHeight = mIO.GetScreenHeight();

	// Pieces
	Pieces mPieces;

	// Board
	Board mBoard(&mPieces, mScreenHeight);

	// Game
	Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);

	// Get the actual clock milliseconds (SDL)
	unsigned long mTime1 = SDL_GetTicks();

	
	//Main loop
	while (!mIO.IsKeyDown(SDLK_ESCAPE))
	{
		// ----- Draw -----

		mIO.ClearScreen(); 		// Clear screen
		mGame.DrawScene();			// Draw staff
		mIO.UpdateScreen();		// Put the graphic context in the screen

		// ----- Input -----

		int mKey = mIO.Pollkey();

		switch (mKey)
		{
			case (SDLK_RIGHT):
			{
				if (mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRot))
					mGame.mPosX++;
				break;
			}

			case (SDLK_LEFT):
			{
				if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRot))
					mGame.mPosX--;
				break;
			}

			case (SDLK_DOWN):
			{
				if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRot))
					mGame.mPosY++;
				break;
			}

			case (SDLK_x):
			{
				// Check collision from up to down
				while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRot)) { mGame.mPosY++; }

				mBoard.StorePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRot);

				mBoard.DeletePossibleLines();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					exit(0);
				}

				mGame.CreateNewPiece();

				break;
			}

			case (SDLK_UP):
			{
				if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRot + 1) % 4))
					mGame.mRot = (mGame.mRot + 1) % 4;

				break;
			}
		}

		// ----- Vertical movement -----

		unsigned long mTime2 = SDL_GetTicks();

		if ((mTime2 - mTime1) > WAIT_TIME)
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRot))
			{
				mGame.mPosY++;
			}
			else
			{
				mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRot);

				mBoard.DeletePossibleLines();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					exit(0);
				}

				mGame.CreateNewPiece();
			}

			mTime1 = SDL_GetTicks();
		}
	}

	return 0;
}
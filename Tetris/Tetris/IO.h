#ifndef _IO_
#define _IO_

// ------ Includes -----


#include "C:\Users\s.healy\Documents\C++\Tetris\Tetris\SDL\include\SDL.h"   
#include "C:\Users\s.healy\Documents\C++\Tetris\Tetris\SDL\SDL_GfxPrimitives\SDL_gfxPrimitives.h"

#pragma comment (lib, "C:/Users/s.healy/Documents/C++/Tetris/Tetris/SDL/lib/SDL.lib")
#pragma comment (lib, "C:/Users/s.healy/Documents/C++/Tetris/Tetris/SDL/SDL_GfxPrimitives/SDL_GfxPrimitives_Static.lib")

// ------ Enums -----

enum color { BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX }; // Colors


// --------------------------------------------------------------------------------
//                                   IO
// --------------------------------------------------------------------------------

class IO
{
public:

	IO();

	void DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC);
	void ClearScreen();
	int GetScreenHeight();
	int InitGraph();
	int Pollkey();
	int Getkey();
	int IsKeyDown(int pKey);
	void UpdateScreen();

};

#endif _IO_

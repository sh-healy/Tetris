#ifndef _PIECES_
#define _PIECES_


class Pieces
{
public:
	int GetBlockType(int pPiece, int pRot, int pX, int pY);
	int GetXPos(int pPiece, int pRot);
	int GetYPos(int pPiece, int pRot);
};

#endif

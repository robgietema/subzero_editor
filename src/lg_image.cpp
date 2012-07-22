/*******************************************************************************
* File:		lg_image.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		27 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../include/lg_image.h"

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* DrawLine
*******************************************************************************/
int DrawLine (int iWidth, int iHeight, int iBeginX, int iBeginY, int iEndX, int iEndY, byte bSide, float fLineWidth, byte* bpBits) {
	int iOffset;

	// Check if horizontal
	if (iBeginY == iEndY) {

		// Cycle through rows
		for (int iRows = 0; iRows < (int)fLineWidth; iRows++) {

			// Set side
			iOffset = iRows;
			if (bSide == 0) {
				iOffset *= -1;
			}

			// Cycle through pixels
			for (int iX = 0; iX < iEndX - iBeginX + 1; iX++) {

				bpBits[((iX+((iHeight - iBeginY - iOffset - 1)*iWidth))*4)] = 0;
				bpBits[((iX+((iHeight - iBeginY - iOffset - 1)*iWidth))*4)+1] = 0;
				bpBits[((iX+((iHeight - iBeginY - iOffset - 1)*iWidth))*4)+2] = 0;
			}
		}

	// Check if vertical
	} else if (iBeginX == iEndX) {

		// Cycle through cols
		for (int iCols = 0; iCols < (int)fLineWidth; iCols++) {

			// Set side
			iOffset = iCols;
			if (bSide == 0) {
				iOffset *= -1;
			}

			// Cycle through pixels
			for (int iY = 0; iY < iEndY - iBeginY; iY++) {

				bpBits[((iOffset+((iHeight - iBeginY - iY - 1)*iWidth))*4)] = 0;
				bpBits[((iOffset+((iHeight - iBeginY - iY - 1)*iWidth))*4)+1] = 0;
				bpBits[((iOffset+((iHeight - iBeginY - iY - 1)*iWidth))*4)+2] = 0;
			}
		}

	// Diagonal
	} else {

		// Todo
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* Scale
*******************************************************************************/
int Scale (int iOldWidth, int iOldHeight, int iNewWidth, int iNewHeight, byte* bpOldBits, byte* bpNewBits) {
	int iFactor = iOldWidth / iNewWidth;

	// Cycle through x
	for (int iX = 0; iX < iNewWidth; iX++) {

		// Cycle through y
		for (int iY = 0; iY < iNewHeight; iY++) {

			// Set pixels
			bpNewBits[(iX + (iY * iNewWidth))*4] = bpOldBits[((iX*iFactor) + (iY * iOldWidth * iFactor))*4];
			bpNewBits[(iX + (iY * iNewWidth))*4+1] = bpOldBits[((iX*iFactor) + (iY * iOldWidth * iFactor))*4+1];
			bpNewBits[(iX + (iY * iNewWidth))*4+2] = bpOldBits[((iX*iFactor) + (iY * iOldWidth * iFactor))*4+2];
			bpNewBits[(iX + (iY * iNewWidth))*4+3] = bpOldBits[((iX*iFactor) + (iY * iOldWidth * iFactor))*4+3];
		}
	}
	// Return no error
	return (0);
}
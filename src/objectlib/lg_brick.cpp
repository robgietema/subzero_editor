/*******************************************************************************
* File:		lg_brick.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		19 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/objectlib/lg_brick.h"
#include "../../include/bricklib/lg_bricklib.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* LGBrick::LGBrick
*******************************************************************************/
LGBrick::LGBrick () {

	// Init values
	LGBrick::bSelected = false;
}

/*******************************************************************************
* LGBrick::~LGBrick
*******************************************************************************/
LGBrick::~LGBrick () {
}

/*******************************************************************************
* LGBrick::initDefaultValues
*******************************************************************************/
int LGBrick::initDefaultValues (int iX, int iY, int iZ, int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim) {
	extern LGBrickLib bBrickLib;	// Bricklib

	// Print status
//	VerbosePrintf ("Init brick with coordinates: %d, %d, %d", iX, iY, iZ);

	// Set values
	LGBrick::iBlockNumber = 3001;
	LGBrick::iType = bBrickLib.getBlockIndex (LGBrick::iBlockNumber);
	LGBrick::iColor = 0; // rand() % NR_OF_COLORS;
	LGBrick::vPos.iX = iX*4;
	LGBrick::vPos.iY = iY*3;
	LGBrick::vPos.iZ = iZ*2;
	LGBrick::vOffset.fX = 0.0f;
	LGBrick::vOffset.fY = 0.0f;
	LGBrick::vOffset.fZ = 0.0f;
	LGBrick::vRotate.fX = 0.0f;
	LGBrick::vRotate.fY = 0.0f;
	LGBrick::vRotate.fZ = 0.0f;

	LGBrick::calcAnimStart (iAnimType, LGBrick::vOffset, vBrickPositionAnim, vBrickOffsetAnim, vBrickRotationAnim);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrick::createNew
*******************************************************************************/
int LGBrick::createNew (int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim) {
	extern LGBrickLib bBrickLib;	// Bricklib

	// Set values
	LGBrick::iBlockNumber = 3001;
	LGBrick::iType = bBrickLib.getBlockIndex (LGBrick::iBlockNumber);
	LGBrick::iColor = 0;
	LGBrick::vPos.iX = 0;
	LGBrick::vPos.iY = 0;
	LGBrick::vPos.iZ = 0;
	LGBrick::vOffset.fX = 0.0f;
	LGBrick::vOffset.fY = 0.0f;
	LGBrick::vOffset.fZ = 0.0f;
	LGBrick::vRotate.fX = 0.0f;
	LGBrick::vRotate.fY = 0.0f;
	LGBrick::vRotate.fZ = 0.0f;

	LGBrick::calcAnimStart (iAnimType, LGBrick::vOffset, vBrickPositionAnim, vBrickOffsetAnim, vBrickRotationAnim);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrick::calcAnimStart
*******************************************************************************/
int LGBrick::calcAnimStart (int iAnimType, LGVertex3f vGroupOffset, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim) {
	extern LGBrickLib bBrickLib;	// Bricklib

	// Check anim type
	switch (iAnimType) {

		// Fall down
		case 0:

			// Calculate anim start variables
			if (rand () % 2 == 0) {
				LGBrick::vAnimOffset.fX = vGroupOffset.fX + vBrickPositionAnim.fX + vBrickOffsetAnim.fX + (rand() % ((int)vBrickOffsetAnim.fZ - (int)vBrickOffsetAnim.fX));
			} else {
				LGBrick::vAnimOffset.fX = vGroupOffset.fX + vBrickPositionAnim.fX + -1 * (vBrickOffsetAnim.fX + (rand() % ((int)vBrickOffsetAnim.fZ - (int)vBrickOffsetAnim.fX)));
			}
			if (rand () % 2 == 0) {
				LGBrick::vAnimOffset.fY = vGroupOffset.fY + vBrickPositionAnim.fY + vBrickOffsetAnim.fX + (rand() % ((int)vBrickOffsetAnim.fZ - (int)vBrickOffsetAnim.fX));
			} else {
				LGBrick::vAnimOffset.fY = vGroupOffset.fY + vBrickPositionAnim.fY + -1 * (vBrickOffsetAnim.fX + (rand() % ((int)vBrickOffsetAnim.fZ - (int)vBrickOffsetAnim.fX)));
			}
			if (rand () % 2 == 0) {
				LGBrick::vAnimOffset.fZ = vGroupOffset.fZ + vBrickPositionAnim.fZ + vBrickOffsetAnim.fX + (rand() % ((int)vBrickOffsetAnim.fZ - (int)vBrickOffsetAnim.fX));
			} else {
				LGBrick::vAnimOffset.fZ = vGroupOffset.fZ + vBrickPositionAnim.fZ + -1 * (vBrickOffsetAnim.fX + (rand() % ((int)vBrickOffsetAnim.fZ - (int)vBrickOffsetAnim.fX)));
			}
			break;

		// Explosion
		case 1:

			LGVertex3f vPos;		// Block position
			LGVertex3f vDirection;	// Direction
			vPos.fX = LGBrick::vPos.iX * UNIT_X + vGroupOffset.fX;
			vPos.fY = LGBrick::vPos.iY * UNIT_Y + vGroupOffset.fY;
			vPos.fZ = LGBrick::vPos.iZ * UNIT_Z + vGroupOffset.fZ;
			vDirection.fX = vPos.fX - vBrickPositionAnim.fX;
			vDirection.fY = vPos.fY - vBrickPositionAnim.fY;
			vDirection.fZ = vPos.fZ - vBrickPositionAnim.fZ;

			// Calc distance
			float fDistance;
			fDistance = (float) sqrt (vDirection.fX * vDirection.fX + vDirection.fY * vDirection.fY + vDirection.fZ * vDirection.fZ);

			// Random
			LGBrick::vAnimOffset.fX = (vBrickOffsetAnim.fX + (rand () % (int)(vBrickOffsetAnim.fZ - vBrickOffsetAnim.fX))) * ((vDirection.fX / fDistance) * 2);
			LGBrick::vAnimOffset.fY = (vBrickOffsetAnim.fX + (rand () % (int)(vBrickOffsetAnim.fZ - vBrickOffsetAnim.fX))) * ((vDirection.fY / fDistance) * 8);
			LGBrick::vAnimOffset.fZ = (vBrickOffsetAnim.fX + (rand () % (int)(vBrickOffsetAnim.fZ - vBrickOffsetAnim.fX))) * ((vDirection.fZ / fDistance) * 2);

			// Add random
			LGBrick::vAnimOffset.fX = LGBrick::vAnimOffset.fX + (rand () % (int)(vBrickOffsetAnim.fZ)) - (vBrickOffsetAnim.fZ / 2);
			// LGBrick::vAnimOffset.fY = LGBrick::vAnimOffset.fY + (rand () % (int)(vBrickOffsetAnim.fZ / 10));
			LGBrick::vAnimOffset.fZ = LGBrick::vAnimOffset.fZ + (rand () % (int)(vBrickOffsetAnim.fZ)) - (vBrickOffsetAnim.fZ / 2);

			LGBrick::fFloor = vBrickOffsetAnim.fY;
			break;
	}

	// Rotation
	LGBrick::vAnimRotate.fX = (float)(rand() % (int)vBrickRotationAnim.fX);
	LGBrick::vAnimRotate.fY = (float)(rand() % (int)vBrickRotationAnim.fY);
	LGBrick::vAnimRotate.fZ = (float)(rand() % (int)vBrickRotationAnim.fZ);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrick::read
*******************************************************************************/
int LGBrick::read (byte* bpData, int iDataSize, int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim) {
	int iCurrentByte=0;				// Current byte
	extern LGBrickLib bBrickLib;	// Bricklib

	// Print status
	VerbosePrintf ("Begin BRK");

	// Get variables from buffer
	LGBrick::iBlockNumber = GetInt (bpData + iCurrentByte);
	iCurrentByte += SIZE_INT;
	LGBrick::iType = bBrickLib.getBlockIndex (LGBrick::iBlockNumber);
	LGBrick::vPos = GetVertex3i (bpData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3I;
	LGBrick::iColor = GetInt (bpData + iCurrentByte);
	iCurrentByte += SIZE_INT;
	LGBrick::vOffset = GetVertex3f (bpData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3F;
	LGBrick::vRotate = GetVertex3f (bpData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3F;

	// Calculate anim start variables
	LGBrick::vAnimOffset.fX = (rand() % (int)vBrickOffsetAnim.fX) - (vBrickOffsetAnim.fX / 2);
	LGBrick::vAnimOffset.fY = vBrickOffsetAnim.fY + (rand() % (int)vBrickOffsetAnim.fY);
	LGBrick::vAnimOffset.fZ = (rand() % (int)vBrickOffsetAnim.fZ) - (vBrickOffsetAnim.fZ / 2);
	LGBrick::vAnimRotate.fX = (float)(rand() % (int)vBrickRotationAnim.fX);
	LGBrick::vAnimRotate.fY = (float)(rand() % (int)vBrickRotationAnim.fY);
	LGBrick::vAnimRotate.fZ = (float)(rand() % (int)vBrickRotationAnim.fZ);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrick::write
*******************************************************************************/
int LGBrick::write (FILE* fpFile) {

	// Print header id
	PrintChunkID (fpFile, "BRK");

	// Print chunk size
	PrintInt (fpFile, LGBrick::getChunkSize ());

	// Print number of objects
	PrintInt (fpFile, LGBrick::iBlockNumber);

	// Print position
	PrintVertex3i (fpFile, LGBrick::vPos);

	// Print color
	PrintInt (fpFile, LGBrick::iColor);

	// Print offset
	PrintVertex3f (fpFile, LGBrick::vOffset);

	// Print rotate
	PrintVertex3f (fpFile, LGBrick::vRotate);

	// Return on error
	return (0);
}

/*******************************************************************************
* LGBrick::draw
*******************************************************************************/
int LGBrick::draw (int iTime, int iFramesPerBrick, int iAnimType, LGVertex3f vGroupOffset) {
	extern LGBrickLib	bBrickLib;		// Bricklib
	extern DWORD		dGlobalTicks;	// Ticks
	LGVertex3f			vTranslate;		// Translate
	LGVertex3f			vRotate;		// Rotate

	// Set min max values
	if (iTime < 0) { iTime = 0; }
	if (iTime > iFramesPerBrick - 1) { iTime = iFramesPerBrick - 1; }

	vTranslate.fX = LGBrick::vPos.iX * UNIT_X;
	vTranslate.fY = LGBrick::vPos.iY * UNIT_Y;
	vTranslate.fZ = LGBrick::vPos.iZ * UNIT_Z;

	// Check anim type
	if (iAnimType == 0) {

		// Add anim translate
		vTranslate.fX += (LGBrick::vAnimOffset.fX - (((float)iTime + 1) / (float)iFramesPerBrick) * LGBrick::vAnimOffset.fX);
		vTranslate.fY += (LGBrick::vAnimOffset.fY - (((float)iTime + 1) / (float)iFramesPerBrick) * LGBrick::vAnimOffset.fY);
		vTranslate.fZ += (LGBrick::vAnimOffset.fZ - (((float)iTime + 1) / (float)iFramesPerBrick) * LGBrick::vAnimOffset.fZ);
	} else {

		// Add anim translate
		vTranslate.fX += ((((float)iTime) / (float)iFramesPerBrick) * LGBrick::vAnimOffset.fX);
		vTranslate.fY += ((((float)iTime) / (float)iFramesPerBrick) * LGBrick::vAnimOffset.fY);
		vTranslate.fZ += ((((float)iTime) / (float)iFramesPerBrick) * LGBrick::vAnimOffset.fZ);

		// Percentage
		float fPercentage = (((float)iTime) / (float)iFramesPerBrick);

		vTranslate.fY = ((1.0f - fPercentage) * vTranslate.fY) -
			(fPercentage * (((LGBrick::vPos.iY * UNIT_Y) + vGroupOffset.fY) - LGBrick::fFloor));

		// Check floor
		if (vTranslate.fY < LGBrick::fFloor - vGroupOffset.fY) {

			// Set floor
			vTranslate.fY = LGBrick::fFloor - vGroupOffset.fY;
		}
	}

	// Add offset
	vTranslate.fX += LGBrick::vOffset.fX;
	vTranslate.fY += LGBrick::vOffset.fY;
	vTranslate.fZ += LGBrick::vOffset.fZ;

	glPushMatrix ();

	glTranslatef (vTranslate.fX, vTranslate.fY, vTranslate.fZ);

	// Check anim type
	if (iAnimType == 0) {

		// Add anim rotation
		vRotate.fX = LGBrick::vAnimRotate.fX - (((float)iTime + 1) / (float)iFramesPerBrick) * LGBrick::vAnimRotate.fX;
		vRotate.fY = LGBrick::vAnimRotate.fY - (((float)iTime + 1) / (float)iFramesPerBrick) * LGBrick::vAnimRotate.fY;
		vRotate.fZ = LGBrick::vAnimRotate.fZ - (((float)iTime + 1) / (float)iFramesPerBrick) * LGBrick::vAnimRotate.fZ;
	} else {

		// Add anim rotation
		vRotate.fX = (((float)iTime) / (float)iFramesPerBrick) * LGBrick::vAnimRotate.fX;
		vRotate.fY = (((float)iTime) / (float)iFramesPerBrick) * LGBrick::vAnimRotate.fY;
		vRotate.fZ = (((float)iTime) / (float)iFramesPerBrick) * LGBrick::vAnimRotate.fZ;
	}

	// Add rotation
	vRotate.fX += LGBrick::vRotate.fX;
	vRotate.fY += LGBrick::vRotate.fY;
	vRotate.fZ += LGBrick::vRotate.fZ;

	// Rotate
	glRotatef (vRotate.fX, 1.0f, 0.0f, 0.0f);
	glRotatef (vRotate.fY, 0.0f, 1.0f, 0.0f);
	glRotatef (vRotate.fZ, 0.0f, 0.0f, 1.0f);

	// Check if selected
	if (((LGBrick::bSelected) && (dGlobalTicks%512 > 255)) || (!LGBrick::bSelected)) {

		// Draw brick
		bBrickLib.draw (LGBrick::iType, LGBrick::iColor);
	}

	glPopMatrix ();

	// Return on error
	return (0);
}

/*******************************************************************************
* LGBrick::getChunkHeaderSize
*******************************************************************************/
int LGBrick::getChunkHeaderSize () {
	int iChunkHeaderSize = 0;		// Chunk header size

	// Add chunk fields
	iChunkHeaderSize += SIZE_CHUNKID;		// Id
	iChunkHeaderSize += SIZE_INT;			// Chunk size
	iChunkHeaderSize += SIZE_INT;			// Brick number
	iChunkHeaderSize += SIZE_VERTEX3I;		// Position
	iChunkHeaderSize += SIZE_INT;			// Color
	iChunkHeaderSize += SIZE_VERTEX3F;		// Offset
	iChunkHeaderSize += SIZE_VERTEX3F;		// Rotate

	// Return chunk size
	return (iChunkHeaderSize);
}

/*******************************************************************************
* LGBrick::getChunkSize
*******************************************************************************/
int LGBrick::getChunkSize () {
	int iChunkSize = LGBrick::getChunkHeaderSize ();		// Chunk size

	// Return chunk size
	return (iChunkSize);
}


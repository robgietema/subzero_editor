/*******************************************************************************
* File:		lg_objectgroup.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		19 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/objectlib/lg_objectgroup.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* LGObjectGroup::LGObjectGroup
*******************************************************************************/
LGObjectGroup::LGObjectGroup () {

	// Init values
	LGObjectGroup::iNrOfBricks = 0;
	LGObjectGroup::bpBricks = NULL;
	LGObjectGroup::bHide = false;
	strcpy (LGObjectGroup::acName, "object group 1");
}

/*******************************************************************************
* LGObjectGroup::~LGObjectGroup
*******************************************************************************/
LGObjectGroup::~LGObjectGroup () {

	// If allocated
	if ((LGObjectGroup::bpBricks) && (LGObjectGroup::iNrOfBricks > 0)) {

		// Delete
		delete []LGObjectGroup::bpBricks;
	}
}

/*******************************************************************************
* LGObjectGroup::sort
*******************************************************************************/
int LGObjectGroup::sort () {

	// Cycle through bricks
	for (int iCount1 = 0; iCount1 < LGObjectGroup::iNrOfBricks - 1; iCount1++) {

		// Cycle through bricks
		for (int iCount2 = iCount1 + 1; iCount2 < LGObjectGroup::iNrOfBricks; iCount2++) {

			// Check if needs to be swapped
			if (LGObjectGroup::bpBricks[iCount1].vPos.iY > LGObjectGroup::bpBricks[iCount2].vPos.iY) {

				// Swap bricks
				LGObjectGroup::swapBricks (iCount1, iCount2);
			}
		}
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectGroup::swapBricks
*******************************************************************************/
int LGObjectGroup::swapBricks (int iItem1, int iItem2) {
	LGBrick		bDummy;

	// Make backup of item 1
	bDummy.iType			= LGObjectGroup::bpBricks[iItem1].iType;
	bDummy.iBlockNumber		= LGObjectGroup::bpBricks[iItem1].iBlockNumber;
	bDummy.iColor			= LGObjectGroup::bpBricks[iItem1].iColor;
	bDummy.fFloor			= LGObjectGroup::bpBricks[iItem1].fFloor;

	bDummy.vPos.iX			= LGObjectGroup::bpBricks[iItem1].vPos.iX;
	bDummy.vPos.iY			= LGObjectGroup::bpBricks[iItem1].vPos.iY;
	bDummy.vPos.iZ			= LGObjectGroup::bpBricks[iItem1].vPos.iZ;

	bDummy.vAnimOffset.fX	= LGObjectGroup::bpBricks[iItem1].vAnimOffset.fX;
	bDummy.vAnimOffset.fY	= LGObjectGroup::bpBricks[iItem1].vAnimOffset.fY;
	bDummy.vAnimOffset.fZ	= LGObjectGroup::bpBricks[iItem1].vAnimOffset.fZ;

	bDummy.vAnimRotate.fX	= LGObjectGroup::bpBricks[iItem1].vAnimRotate.fX;
	bDummy.vAnimRotate.fY	= LGObjectGroup::bpBricks[iItem1].vAnimRotate.fY;
	bDummy.vAnimRotate.fZ	= LGObjectGroup::bpBricks[iItem1].vAnimRotate.fZ;

	bDummy.vRotate.fX		= LGObjectGroup::bpBricks[iItem1].vRotate.fX;
	bDummy.vRotate.fY		= LGObjectGroup::bpBricks[iItem1].vRotate.fY;
	bDummy.vRotate.fZ		= LGObjectGroup::bpBricks[iItem1].vRotate.fZ;

	bDummy.vOffset.fX		= LGObjectGroup::bpBricks[iItem1].vOffset.fX;
	bDummy.vOffset.fY		= LGObjectGroup::bpBricks[iItem1].vOffset.fY;
	bDummy.vOffset.fZ		= LGObjectGroup::bpBricks[iItem1].vOffset.fZ;

	// Copy 2 to 1
	LGObjectGroup::bpBricks[iItem1].iType			= LGObjectGroup::bpBricks[iItem2].iType;
	LGObjectGroup::bpBricks[iItem1].iBlockNumber	= LGObjectGroup::bpBricks[iItem2].iBlockNumber;
	LGObjectGroup::bpBricks[iItem1].iColor			= LGObjectGroup::bpBricks[iItem2].iColor;
	LGObjectGroup::bpBricks[iItem1].fFloor			= LGObjectGroup::bpBricks[iItem2].fFloor;

	LGObjectGroup::bpBricks[iItem1].vPos.iX			= LGObjectGroup::bpBricks[iItem2].vPos.iX;
	LGObjectGroup::bpBricks[iItem1].vPos.iY			= LGObjectGroup::bpBricks[iItem2].vPos.iY;
	LGObjectGroup::bpBricks[iItem1].vPos.iZ			= LGObjectGroup::bpBricks[iItem2].vPos.iZ;

	LGObjectGroup::bpBricks[iItem1].vAnimOffset.fX	= LGObjectGroup::bpBricks[iItem2].vAnimOffset.fX;
	LGObjectGroup::bpBricks[iItem1].vAnimOffset.fY	= LGObjectGroup::bpBricks[iItem2].vAnimOffset.fY;
	LGObjectGroup::bpBricks[iItem1].vAnimOffset.fZ	= LGObjectGroup::bpBricks[iItem2].vAnimOffset.fZ;

	LGObjectGroup::bpBricks[iItem1].vAnimRotate.fX	= LGObjectGroup::bpBricks[iItem2].vAnimRotate.fX;
	LGObjectGroup::bpBricks[iItem1].vAnimRotate.fY	= LGObjectGroup::bpBricks[iItem2].vAnimRotate.fY;
	LGObjectGroup::bpBricks[iItem1].vAnimRotate.fZ	= LGObjectGroup::bpBricks[iItem2].vAnimRotate.fZ;

	LGObjectGroup::bpBricks[iItem1].vRotate.fX		= LGObjectGroup::bpBricks[iItem2].vRotate.fX;
	LGObjectGroup::bpBricks[iItem1].vRotate.fY		= LGObjectGroup::bpBricks[iItem2].vRotate.fY;
	LGObjectGroup::bpBricks[iItem1].vRotate.fZ		= LGObjectGroup::bpBricks[iItem2].vRotate.fZ;

	LGObjectGroup::bpBricks[iItem1].vOffset.fX		= LGObjectGroup::bpBricks[iItem2].vOffset.fX;
	LGObjectGroup::bpBricks[iItem1].vOffset.fY		= LGObjectGroup::bpBricks[iItem2].vOffset.fY;
	LGObjectGroup::bpBricks[iItem1].vOffset.fZ		= LGObjectGroup::bpBricks[iItem2].vOffset.fZ;

	// Copy dummy to 2
	LGObjectGroup::bpBricks[iItem2].iType			= bDummy.iType;
	LGObjectGroup::bpBricks[iItem2].iBlockNumber	= bDummy.iBlockNumber;
	LGObjectGroup::bpBricks[iItem2].iColor			= bDummy.iColor;
	LGObjectGroup::bpBricks[iItem2].fFloor			= bDummy.fFloor;

	LGObjectGroup::bpBricks[iItem2].vPos.iX			= bDummy.vPos.iX;
	LGObjectGroup::bpBricks[iItem2].vPos.iY			= bDummy.vPos.iY;
	LGObjectGroup::bpBricks[iItem2].vPos.iZ			= bDummy.vPos.iZ;

	LGObjectGroup::bpBricks[iItem2].vAnimOffset.fX	= bDummy.vAnimOffset.fX;
	LGObjectGroup::bpBricks[iItem2].vAnimOffset.fY	= bDummy.vAnimOffset.fY;
	LGObjectGroup::bpBricks[iItem2].vAnimOffset.fZ	= bDummy.vAnimOffset.fZ;

	LGObjectGroup::bpBricks[iItem2].vAnimRotate.fX	= bDummy.vAnimRotate.fX;
	LGObjectGroup::bpBricks[iItem2].vAnimRotate.fY	= bDummy.vAnimRotate.fY;
	LGObjectGroup::bpBricks[iItem2].vAnimRotate.fZ	= bDummy.vAnimRotate.fZ;

	LGObjectGroup::bpBricks[iItem2].vRotate.fX		= bDummy.vRotate.fX;
	LGObjectGroup::bpBricks[iItem2].vRotate.fY		= bDummy.vRotate.fY;
	LGObjectGroup::bpBricks[iItem2].vRotate.fZ		= bDummy.vRotate.fZ;

	LGObjectGroup::bpBricks[iItem2].vOffset.fX		= bDummy.vOffset.fX;
	LGObjectGroup::bpBricks[iItem2].vOffset.fY		= bDummy.vOffset.fY;
	LGObjectGroup::bpBricks[iItem2].vOffset.fZ		= bDummy.vOffset.fZ;

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectGroup::createNew
*******************************************************************************/
int LGObjectGroup::createNew (int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim) {
	char acNewName[256];

	// Set values
	LGObjectGroup::iNrOfBricks = 1;
	LGObjectGroup::iTime = 0;
	LGObjectGroup::vOffset.fX = 0.0f;
	LGObjectGroup::vOffset.fY = 0.0f;
	LGObjectGroup::vOffset.fZ = 0.0f;
	LGObjectGroup::vRotate.fX = 0.0f;
	LGObjectGroup::vRotate.fY = 0.0f;
	LGObjectGroup::vRotate.fZ = 0.0f;
	LGObjectGroup::vRotationPoint.fX = 0.0f;
	LGObjectGroup::vRotationPoint.fY = 0.0f;
	LGObjectGroup::vRotationPoint.fZ = 0.0f;

	sprintf (acNewName, "object group 1");
	strcpy (LGObjectGroup::acName, acNewName);
	LGObjectGroup::bpBricks = new LGBrick[LGObjectGroup::iNrOfBricks];

	// Read bricks
	LGObjectGroup::bpBricks[0].createNew (iAnimType, vBrickPositionAnim, vBrickOffsetAnim, vBrickRotationAnim);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectGroup::initDefaultValues
*******************************************************************************/
int LGObjectGroup::initDefaultValues (int iZ, int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim) {
	char acNewName[256];

	// Print status
	VerbosePrintf ("Init objectgroup with z-index: %d", iZ);

	// Set values
	LGObjectGroup::iNrOfBricks = 400;
	LGObjectGroup::iTime = 0; // iZ * 32;
	LGObjectGroup::vOffset.fX = 0.0f;
	LGObjectGroup::vOffset.fY = 0.0f;
	LGObjectGroup::vOffset.fZ = 0.0f;
	LGObjectGroup::vRotate.fX = 0.0f;
	LGObjectGroup::vRotate.fY = 0.0f;
	LGObjectGroup::vRotate.fZ = 0.0f;
	LGObjectGroup::vRotationPoint.fX = 0.0f;
	LGObjectGroup::vRotationPoint.fY = 0.0f;
	LGObjectGroup::vRotationPoint.fZ = 0.0f;
	sprintf (acNewName, "object group %d", iZ + 1);
	strcpy (LGObjectGroup::acName, acNewName);
	LGObjectGroup::bpBricks = new LGBrick[LGObjectGroup::iNrOfBricks];

	// Loop thru bricks
	for (int iY = 0; iY < LGObjectGroup::iNrOfBricks/20; iY++) {

		// Loop thru bricks
		for (int iX = 0; iX < LGObjectGroup::iNrOfBricks/20; iX++) {

			// Read bricks
			LGObjectGroup::bpBricks[iY * 20 + iX].initDefaultValues (iX, iY, iZ, iAnimType, vBrickPositionAnim, vBrickOffsetAnim, vBrickRotationAnim);
		}
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectGroup::calcAnimStart
*******************************************************************************/
int LGObjectGroup::calcAnimStart (int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim) {

	// Loop thru bricks
	for (int iCount = 0; iCount < LGObjectGroup::iNrOfBricks; iCount++) {

		// Read bricks
		LGObjectGroup::bpBricks[iCount].calcAnimStart (iAnimType, LGObjectGroup::vOffset, vBrickPositionAnim, vBrickOffsetAnim, vBrickRotationAnim);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectGroup::read
*******************************************************************************/
int LGObjectGroup::read (byte* bpData, int iDataSize, int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim) {
	int iCurrentByte=0;		// Current byte
	int iCurrentBrick=0;	// Current brick
	int iChunkID=0;			// Chunk id
	int iChunkSize=0;		// Chunksize

	// Print status
	VerbosePrintf ("Begin GRP");

	// Get variables from buffer
	LGObjectGroup::iNrOfBricks = GetInt (bpData + iCurrentByte);
	iCurrentByte += SIZE_INT;
	LGObjectGroup::iTime = GetInt (bpData + iCurrentByte);
	iCurrentByte += SIZE_INT;
	GetString16 (bpData + iCurrentByte, LGObjectGroup::acName);
	iCurrentByte += SIZE_STRING16;
	LGObjectGroup::vOffset = GetVertex3f (bpData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3F;
	LGObjectGroup::vRotate = GetVertex3f (bpData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3F;
	LGObjectGroup::vRotationPoint = GetVertex3f (bpData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3F;

	// Check if > 0
	if (LGObjectGroup::iNrOfBricks > 0) {

		// Alloc bricks
		LGObjectGroup::bpBricks = new LGBrick[LGObjectGroup::iNrOfBricks];
	}

	// Get other chunks
	while (iCurrentByte < iDataSize) {

		// Get chunk id
		if (strncmp ((char*)(bpData + iCurrentByte), "BRK", 3) == 0) iChunkID = BRK_ID;
		else iChunkID = UNKNOWN_ID;
		iCurrentByte += SIZE_CHUNKID;

		// Get chunk size
		iChunkSize = GetInt (bpData + iCurrentByte);
		iCurrentByte += SIZE_INT;

		// Print status
		VerbosePrintf ("Chunksize: %d", iChunkSize);

		// Read chunk
		switch (iChunkID) {
			case BRK_ID:
				// Print status
				VerbosePrintf ("BRK chunk found");

				// Read objects
				LGObjectGroup::bpBricks[iCurrentBrick].read (bpData + iCurrentByte, iChunkSize - SIZE_CHUNKID - SIZE_INT, iAnimType, vBrickPositionAnim, vBrickOffsetAnim, vBrickRotationAnim);

				// Inc current brick
				iCurrentBrick++;
				break;
			default:
				// Print status
				VerbosePrintf ("Read Objectgroup: Unknown chunk found");
				break;
		}

		// Set current byte
		iCurrentByte += (iChunkSize - SIZE_CHUNKID - SIZE_INT);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectGroup::write
*******************************************************************************/
int LGObjectGroup::write (FILE* fpFile) {

	// Print header id
	PrintChunkID (fpFile, "GRP");

	// Print chunk size
	PrintInt (fpFile, LGObjectGroup::getChunkSize ());

	// Print number of objects
	PrintInt (fpFile, LGObjectGroup::iNrOfBricks);

	// Print time
	PrintInt (fpFile, LGObjectGroup::iTime);

	// Print string
	PrintString16 (fpFile, LGObjectGroup::acName);

	// Print offset
	PrintVertex3f (fpFile, LGObjectGroup::vOffset);

	// Print rotate
	PrintVertex3f (fpFile, LGObjectGroup::vRotate);

	// Print rotation point
	PrintVertex3f (fpFile, LGObjectGroup::vRotationPoint);

	// Print objects
	for (int iCount = 0; iCount < LGObjectGroup::iNrOfBricks; iCount++) {

		// Write object
		LGObjectGroup::bpBricks[iCount].write (fpFile);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectGroup::getChunkHeaderSize
*******************************************************************************/
int LGObjectGroup::getChunkHeaderSize () {
	int iChunkHeaderSize = 0;		// Chunk size

	// Add chunk fields
	iChunkHeaderSize += SIZE_CHUNKID;		// Id
	iChunkHeaderSize += SIZE_INT;			// Chunk size
	iChunkHeaderSize += SIZE_INT;			// Number of objectgroups
	iChunkHeaderSize += SIZE_INT;			// Time
	iChunkHeaderSize += SIZE_STRING16;		// Name
	iChunkHeaderSize += SIZE_VERTEX3F;		// Offset
	iChunkHeaderSize += SIZE_VERTEX3F;		// Rotate
	iChunkHeaderSize += SIZE_VERTEX3F;		// Rotation point

	// Return chunk size
	return (iChunkHeaderSize);
}

/*******************************************************************************
* LGObjectGroup::getChunkSize
*******************************************************************************/
int LGObjectGroup::getChunkSize () {
	int iChunkSize = LGObjectGroup::getChunkHeaderSize ();		// Chunk size

	// Add bricks sizes
	for (int iCount = 0; iCount < LGObjectGroup::iNrOfBricks; iCount++) {

		// Add object size
		iChunkSize += LGObjectGroup::bpBricks[iCount].getChunkSize ();
	}

	// Return chunk size
	return (iChunkSize);
}

/*******************************************************************************
* LGObjectGroup::draw
*******************************************************************************/
int LGObjectGroup::draw (int iFrame, int iFramesPerBrick, int iFramesBetweenBricks, int iAnimType) {
	int iBrickAnimLength;		// Animation length

	// Push matrix
	glPushMatrix ();

	// Translate
	glTranslatef (LGObjectGroup::vOffset.fX, LGObjectGroup::vOffset.fY, LGObjectGroup::vOffset.fZ);

	// Translate to rotation point
	glTranslatef (LGObjectGroup::vRotationPoint.fX, LGObjectGroup::vRotationPoint.fY, LGObjectGroup::vRotationPoint.fZ);

	// Rotate
	glRotatef (LGObjectGroup::vRotate.fX, 1.0f, 0.0f, 0.0f);
	glRotatef (LGObjectGroup::vRotate.fY, 0.0f, 1.0f, 0.0f);
	glRotatef (LGObjectGroup::vRotate.fZ, 0.0f, 0.0f, 1.0f);

	// Translate back to draw point from rotation point
	glTranslatef (LGObjectGroup::vRotationPoint.fX * -1, LGObjectGroup::vRotationPoint.fY * -1, LGObjectGroup::vRotationPoint.fZ * -1);

	// If animation start
	if (iFrame >= LGObjectGroup::iTime) {

		// Clac anim length
		iBrickAnimLength = iFramesPerBrick * iFramesBetweenBricks;

		// Draw bricks
		for (int iCount = 0; iCount < LGObjectGroup::iNrOfBricks; iCount++) {

			// Calc relative frame
//			if ((iFrame >= iCount * iFramesBetweenBricks) && (iFrame < (iCount * iFramesBetweenBricks) + iBrickAnimLength)) {

			// Draw brick
			LGObjectGroup::bpBricks[iCount].draw (iFrame - (iCount * iFramesBetweenBricks) - LGObjectGroup::iTime, iFramesPerBrick, iAnimType, LGObjectGroup::vOffset);
//			} else if (iFrame >= (iCount * iFramesBetweenBricks) + iBrickAnimLength) {

				// Draw static group model
//				LGObjectGroup::drawStatic ();
//			}
		}
	}

	// Pop matrix
	glPopMatrix ();

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectGroup::drawStatic
*******************************************************************************/
int LGObjectGroup::drawStatic () {

	// Todo

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectGroup::deleteBrick
*******************************************************************************/
int LGObjectGroup::deleteBrick (int iBrick) {
	LGBrick*	bpTempBricks;		// Temp buffer

	// Check if out of range
	if (iBrick >= LGObjectGroup::iNrOfBricks) {

		// Return error
		return (-1);
	}

	// Alloc new bricks
	bpTempBricks = new LGBrick[LGObjectGroup::iNrOfBricks - 1];

	// Copy till brick to be deleted
	memcpy (bpTempBricks, LGObjectGroup::bpBricks, sizeof (LGBrick) * iBrick);

	// Copy after brick to be deleted
	memcpy (&bpTempBricks[iBrick], &LGObjectGroup::bpBricks[iBrick + 1], sizeof (LGBrick) * (LGObjectGroup::iNrOfBricks - iBrick - 1));

	// Decrease number of bricks
	LGObjectGroup::iNrOfBricks--;

	// Realloc buffer
	LGObjectGroup::bpBricks = new LGBrick[LGObjectGroup::iNrOfBricks];

	// Copy bricks
	memcpy (LGObjectGroup::bpBricks, bpTempBricks, sizeof (LGBrick) * LGObjectGroup::iNrOfBricks);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectGroup::insertBrick
*******************************************************************************/
int LGObjectGroup::insertBrick (int iBrick) {
	LGBrick*	bpTempBricks;		// Temp buffer

	// Check if out of range
	if (iBrick >= LGObjectGroup::iNrOfBricks) {

		// Return error
		return (-1);
	}

	// Alloc new bricks
	bpTempBricks = new LGBrick[LGObjectGroup::iNrOfBricks + 1];

	// Copy till brick to be inserted
	memcpy (bpTempBricks, LGObjectGroup::bpBricks, sizeof (LGBrick) * (iBrick + 1));

	// Copy after brick to be inserted
	memcpy (&bpTempBricks[iBrick + 1], &LGObjectGroup::bpBricks[iBrick], sizeof (LGBrick) * (LGObjectGroup::iNrOfBricks - iBrick));

	// Decrease number of bricks
	LGObjectGroup::iNrOfBricks++;

	// Realloc buffer
	LGObjectGroup::bpBricks = new LGBrick[LGObjectGroup::iNrOfBricks];

	// Copy bricks
	memcpy (LGObjectGroup::bpBricks, bpTempBricks, sizeof (LGBrick) * LGObjectGroup::iNrOfBricks);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectGroup::addBrick
*******************************************************************************/
int LGObjectGroup::addBrick (LGBrick bBrick) {
	LGBrick*	bpTempBricks;		// Temp buffer

	// Alloc new bricks
	bpTempBricks = new LGBrick[LGObjectGroup::iNrOfBricks];

	// Copy till brick to be inserted
	memcpy (bpTempBricks, LGObjectGroup::bpBricks, sizeof (LGBrick) * LGObjectGroup::iNrOfBricks);

	// Increase number of bricks
	LGObjectGroup::iNrOfBricks++;

	// Realloc buffer
	LGObjectGroup::bpBricks = new LGBrick[LGObjectGroup::iNrOfBricks];

	// Copy bricks
	memcpy (LGObjectGroup::bpBricks, bpTempBricks, sizeof (LGBrick) * LGObjectGroup::iNrOfBricks - 1);

	// Copy entry
	memcpy (&LGObjectGroup::bpBricks[LGObjectGroup::iNrOfBricks - 1], &bBrick, sizeof (LGBrick));

	// Return no error
	return (0);
}
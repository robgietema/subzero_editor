/*******************************************************************************
* File:		lg_object.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		19 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/objectlib/lg_object.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* LGObject::LGObject
*******************************************************************************/
LGObject::LGObject () {

	// Init values
	LGObject::iNrOfObjectGroups = 0;
	LGObject::iAnimType = 0;
	LGObject::vBrickPositionAnim.fX = 0.0f;
	LGObject::vBrickPositionAnim.fY = 0.0f;
	LGObject::vBrickPositionAnim.fZ = 0.0f;
	LGObject::vBrickOffsetAnim.fX = 0.0f;
	LGObject::vBrickOffsetAnim.fY = 0.0f;
	LGObject::vBrickOffsetAnim.fZ = 0.0f;
	LGObject::vBrickRotationAnim.fX = 0.0f;
	LGObject::vBrickRotationAnim.fY = 0.0f;
	LGObject::vBrickRotationAnim.fZ = 0.0f;
	LGObject::iFramesPerBrick = 12;
	LGObject::iFramesBetweenBricks = 2;
	LGObject::iAnimLength = 0;
	LGObject::gpObjectGroups = NULL;
	strcpy (LGObject::acName, "Object");
}

/*******************************************************************************
* LGObject::~LGObject
*******************************************************************************/
LGObject::~LGObject () {

	// If allocated
	if (LGObject::gpObjectGroups) {

		// Delete
		delete []LGObject::gpObjectGroups;
	}
}

/*******************************************************************************
* LGObject::initDefaultValues
*******************************************************************************/
int LGObject::initDefaultValues () {

	// Set values
	LGObject::iNrOfObjectGroups = 10;
	LGObject::iFramesPerBrick = 64;
	LGObject::iFramesBetweenBricks = 0;
	LGObject::iAnimLength = 320;

/*
	LGObject::iAnimType = 0;
	LGObject::vBrickPositionAnim.fX = 0.0f;
	LGObject::vBrickPositionAnim.fY = 150.0f;
	LGObject::vBrickPositionAnim.fZ = 0.0f;
	LGObject::vBrickOffsetAnim.fX = 0.0f;
	LGObject::vBrickOffsetAnim.fY = 50.0f;
	LGObject::vBrickOffsetAnim.fZ = 50.0f;
	LGObject::vBrickRotationAnim.fX = 360.0f;
	LGObject::vBrickRotationAnim.fY = 360.0f;
	LGObject::vBrickRotationAnim.fZ = 360.0f;
*/

	LGObject::iAnimType = 1;
	LGObject::vBrickPositionAnim.fX = 35.0f;
	LGObject::vBrickPositionAnim.fY = 4.0f;
	LGObject::vBrickPositionAnim.fZ = 7.0f;
	LGObject::vBrickOffsetAnim.fX = 25.0f;
	LGObject::vBrickOffsetAnim.fY = -10.0f;
	LGObject::vBrickOffsetAnim.fZ = 30.0f;
	LGObject::vBrickRotationAnim.fX = 360.0f;
	LGObject::vBrickRotationAnim.fY = 360.0f;
	LGObject::vBrickRotationAnim.fZ = 360.0f;

	strcpy (LGObject::acName, "Object");
	LGObject::gpObjectGroups = new LGObjectGroup[LGObject::iNrOfObjectGroups];

	// Init objectgroups
	for (int iCount = 0; iCount < LGObject::iNrOfObjectGroups; iCount++) {

		// Read subobjects
		LGObject::gpObjectGroups[iCount].initDefaultValues (iCount, iAnimType, LGObject::vBrickPositionAnim, LGObject::vBrickOffsetAnim, LGObject::vBrickRotationAnim);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::createNew
*******************************************************************************/
int LGObject::createNew () {

	// Set values
	LGObject::iNrOfObjectGroups = 1;
	LGObject::iFramesPerBrick = 64;
	LGObject::iFramesBetweenBricks = 0;
	LGObject::iAnimLength = 320;

	LGObject::iAnimType = 1;
	LGObject::vBrickPositionAnim.fX = 35.0f;
	LGObject::vBrickPositionAnim.fY = 4.0f;
	LGObject::vBrickPositionAnim.fZ = 7.0f;
	LGObject::vBrickOffsetAnim.fX = 25.0f;
	LGObject::vBrickOffsetAnim.fY = -10.0f;
	LGObject::vBrickOffsetAnim.fZ = 30.0f;
	LGObject::vBrickRotationAnim.fX = 360.0f;
	LGObject::vBrickRotationAnim.fY = 360.0f;
	LGObject::vBrickRotationAnim.fZ = 360.0f;

	strcpy (LGObject::acName, "Object");
	LGObject::gpObjectGroups = new LGObjectGroup[LGObject::iNrOfObjectGroups];

	// Init objectgroups
	for (int iCount = 0; iCount < LGObject::iNrOfObjectGroups; iCount++) {

		// Read subobjects
		LGObject::gpObjectGroups[iCount].createNew (iAnimType, LGObject::vBrickPositionAnim, LGObject::vBrickOffsetAnim, LGObject::vBrickRotationAnim);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::calcAnimStart
*******************************************************************************/
int LGObject::calcAnimStart () {

	
	VerbosePrintf ("CALC OFFSET: %f", LGObject::vBrickPositionAnim.fY);

	// Init objectgroups
	for (int iCount = 0; iCount < LGObject::iNrOfObjectGroups; iCount++) {

		// Read subobjects
		LGObject::gpObjectGroups[iCount].calcAnimStart (LGObject::iAnimType, LGObject::vBrickPositionAnim, LGObject::vBrickOffsetAnim, LGObject::vBrickRotationAnim);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::calcAnimStart
*******************************************************************************/
int LGObject::calcAnimStart (int iObjectGroup, int iBrick) {

	// Read subobjects
	LGObject::gpObjectGroups[iObjectGroup].bpBricks[iBrick].calcAnimStart (LGObject::iAnimType, LGObject::gpObjectGroups[iObjectGroup].vOffset, LGObject::vBrickPositionAnim, LGObject::vBrickOffsetAnim, LGObject::vBrickRotationAnim);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::readFromFile
*******************************************************************************/
int LGObject::readFromFile (char* cpFilename) {
	int		iCurrentByte=0;			// Current byte in the buffer
	int		iFileLength;			// Length of the OOF file
	FILE*	fpFile;					// Input file
	byte*	bpData;					// Buffer
	int		iChunkID;				// Chunk ID
	int		iChunkSize;				// Chunk size
	int		iCurrentObjectGroup=0;	// Current sub object

	// Open file
	if ((fpFile  = fopen (cpFilename, "rb" )) == NULL) {

		// Print error
		ErrorPrintf ("Input file could not be opened");

		// Return error
		return (-1);
	}

	// Get file length
	fseek (fpFile, 0, SEEK_END);
	iFileLength = ftell (fpFile);

	// Reset file pointer to begin
	fseek (fpFile, 0, SEEK_SET);

	// Allocate buffer
	bpData = new byte[iFileLength];

	// Read buffer
	fread (bpData, sizeof (char), iFileLength, fpFile);

	// Check header
	if (strncmp ((char*)bpData, "OBJ", 3) == 0) {

		// Set current byte
		iCurrentByte += 3;

		// Skip Chunksize
		iCurrentByte += 4;

		// Read number of objectgroups
		LGObject::iNrOfObjectGroups = GetInt (bpData + iCurrentByte);
		iCurrentByte += 4;

		// Check if > 0
		if (LGObject::iNrOfObjectGroups > 0) {

			// Alloc objectgroups
			LGObject::gpObjectGroups = new LGObjectGroup[LGObject::iNrOfObjectGroups];
		}

		// Get properties
		LGObject::iFramesPerBrick = GetInt (bpData + iCurrentByte);
		iCurrentByte += SIZE_INT;
		LGObject::iFramesBetweenBricks = GetInt (bpData + iCurrentByte);
		iCurrentByte += SIZE_INT;
		LGObject::iAnimType = GetInt (bpData + iCurrentByte);
		iCurrentByte += SIZE_INT;
		LGObject::vBrickPositionAnim = GetVertex3f (bpData + iCurrentByte);
		iCurrentByte += SIZE_VERTEX3F;
		LGObject::vBrickOffsetAnim = GetVertex3f (bpData + iCurrentByte);
		iCurrentByte += SIZE_VERTEX3F;
		LGObject::vBrickRotationAnim = GetVertex3f (bpData + iCurrentByte);
		iCurrentByte += SIZE_VERTEX3F;
		GetString16 (bpData + iCurrentByte, LGObject::acName);
		iCurrentByte += SIZE_STRING16;

	// No header found
	} else {
		// Print error
		ErrorPrintf ("This is no object file");

		// Return error
		return (-1);
	}

	// Get other chunks
	while (iCurrentByte < iFileLength) {
		// Get chunk id
		if (strncmp ((char*)(bpData + iCurrentByte), "GRP", 3) == 0) iChunkID = GRP_ID;
		else iChunkID = UNKNOWN_ID;
		iCurrentByte += SIZE_CHUNKID;

		// Get chunk size
		iChunkSize = GetInt (bpData + iCurrentByte);
		iCurrentByte += SIZE_INT;

		// Read chunk
		switch (iChunkID) {
			case GRP_ID:
				// Print status
				VerbosePrintf ("GRP chunk found");
				
				// Read objects
				LGObject::gpObjectGroups[iCurrentObjectGroup].read (bpData + iCurrentByte, iChunkSize - SIZE_CHUNKID - SIZE_INT, iAnimType, vBrickPositionAnim, vBrickOffsetAnim, vBrickRotationAnim);

				// Inc current objectgroup
				iCurrentObjectGroup++;
				break;
			default:
				// Print status
				VerbosePrintf ("Unknown chunk found");
				break;
		}

		// Set current byte
		iCurrentByte += (iChunkSize - SIZE_CHUNKID - SIZE_INT);
	}

	// Calc anim length
	LGObject::iAnimLength = LGObject::getAnimLength ();

	// Free buffer
	delete []bpData;
	
	// Close file
	fclose (fpFile);

	// Calc anim start
	LGObject::calcAnimStart ();

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::read
*******************************************************************************/
int LGObject::read (byte* bpData, int iDataSize) {
	int iCurrentByte=0;			// Current byte
	int iCurrentObjectGroup=0;	// Current object group
	int iChunkID=0;				// Chunk ID
	int iChunkSize=0;			// Chunk size

	// Print status
	VerbosePrintf ("Begin OBJ");

	// Get variables from buffer
	LGObject::iNrOfObjectGroups = GetInt (bpData + iCurrentByte);
	iCurrentByte += SIZE_INT;
	LGObject::iFramesPerBrick = GetInt (bpData + iCurrentByte);
	iCurrentByte += SIZE_INT;
	LGObject::iFramesBetweenBricks = GetInt (bpData + iCurrentByte);
	iCurrentByte += SIZE_INT;
	LGObject::iAnimType = GetInt (bpData + iCurrentByte);
	iCurrentByte += SIZE_INT;
	LGObject::vBrickPositionAnim = GetVertex3f (bpData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3F;
	LGObject::vBrickOffsetAnim = GetVertex3f (bpData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3F;
	LGObject::vBrickRotationAnim = GetVertex3f (bpData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3F;
	GetString16 (bpData + iCurrentByte, LGObject::acName);
	iCurrentByte += SIZE_STRING16;

	// Print status
	VerbosePrintf ("Number of objectgroups: %d", LGObject::iNrOfObjectGroups);

	// Alloc objectgroups
	LGObject::gpObjectGroups = new LGObjectGroup[LGObject::iNrOfObjectGroups];

	// Get other chunks
	while (iCurrentByte < iDataSize) {

		// Get chunk id
		if (strncmp ((char*)(bpData + iCurrentByte), "GRP", 3) == 0) iChunkID = GRP_ID;
		else iChunkID = UNKNOWN_ID;
		iCurrentByte += 3;

		// Get chunk size
		iChunkSize = GetInt (bpData + iCurrentByte);
		iCurrentByte += 4;

		// Read chunk
		switch (iChunkID) {
			case GRP_ID:
				// Print status
				VerbosePrintf ("GRP chunk found");

				// Read objects
				LGObject::gpObjectGroups[iCurrentObjectGroup].read (bpData + iCurrentByte, iChunkSize - SIZE_CHUNKID - SIZE_INT, iAnimType, vBrickPositionAnim, vBrickOffsetAnim, vBrickRotationAnim);

				// Inc current object
				iCurrentObjectGroup++;
				break;
			default:
				// Print status
				VerbosePrintf ("Read object: Unknown chunk found");
				break;
		}

		// Set current byte
		iCurrentByte += (iChunkSize - SIZE_CHUNKID - SIZE_INT);
	}

	// Calc anim length
	LGObject::iAnimLength = getAnimLength ();

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::writeToFile
*******************************************************************************/
int LGObject::writeToFile (char* cpFilename) {
	FILE* fpFile;		// Output file

	// Open output file
	if (!(fpFile = fopen (cpFilename, "wb"))) {

		// Print error
		printf ("Error opening file: %s", cpFilename);

		// Return error
		return (-1);
	}

	// Print header id
	PrintChunkID (fpFile, "OBJ");

	// Print chunk size
	PrintInt (fpFile, LGObject::getChunkSize ());

	// Print number of objects
	PrintInt (fpFile, LGObject::iNrOfObjectGroups);

	// Print properties
	PrintInt (fpFile, LGObject::iFramesPerBrick);
	PrintInt (fpFile, LGObject::iFramesBetweenBricks);
	PrintInt (fpFile, LGObject::iAnimType);
	PrintVertex3f (fpFile, LGObject::vBrickPositionAnim);
	PrintVertex3f (fpFile, LGObject::vBrickOffsetAnim);
	PrintVertex3f (fpFile, LGObject::vBrickRotationAnim);
	PrintString16 (fpFile, LGObject::acName);

	VerbosePrintf ("WRITE OFFSET: %f", LGObject::vBrickPositionAnim.fY);

	// Print objects
	for (int iCount = 0; iCount < LGObject::iNrOfObjectGroups; iCount++) {

		// Write object
		LGObject::gpObjectGroups[iCount].write (fpFile);
	}

	// Close file
	fclose (fpFile);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::write
*******************************************************************************/
int LGObject::write (FILE* fpFile) {

	// Print header id
	PrintChunkID (fpFile, "OBJ");

	// Print chunk size
	PrintInt (fpFile, LGObject::getChunkSize ());

	// Print number of objects
	PrintInt (fpFile, LGObject::iNrOfObjectGroups);

	// Print properties
	PrintInt (fpFile, LGObject::iFramesPerBrick);
	PrintInt (fpFile, LGObject::iFramesBetweenBricks);
	PrintInt (fpFile, LGObject::iAnimType);
	PrintVertex3f (fpFile, LGObject::vBrickPositionAnim);
	PrintVertex3f (fpFile, LGObject::vBrickOffsetAnim);
	PrintVertex3f (fpFile, LGObject::vBrickRotationAnim);
	PrintString16 (fpFile, LGObject::acName);

	// Print objects
	for (int iCount = 0; iCount < LGObject::iNrOfObjectGroups; iCount++) {

		// Write object
		LGObject::gpObjectGroups[iCount].write (fpFile);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::getChunkHeaderSize
*******************************************************************************/
int LGObject::getChunkHeaderSize () {
	int iChunkHeaderSize = 0;		// Chunk size

	// Add chunk fields
	iChunkHeaderSize += SIZE_CHUNKID;		// Id
	iChunkHeaderSize += SIZE_INT;			// Chunk size
	iChunkHeaderSize += SIZE_INT;			// Number of objectgroups
	iChunkHeaderSize += SIZE_INT;			// Frames per brick
	iChunkHeaderSize += SIZE_INT;			// Frames between bricks
	iChunkHeaderSize += SIZE_INT;			// Anim type
	iChunkHeaderSize += SIZE_VERTEX3F;		// Brick position anim
	iChunkHeaderSize += SIZE_VERTEX3F;		// Brick offset anim
	iChunkHeaderSize += SIZE_VERTEX3F;		// Brick rotate diff anim
	iChunkHeaderSize += SIZE_STRING16;		// Name

	// Return chunk size
	return (iChunkHeaderSize);
}

/*******************************************************************************
* LGObject::getChunkSize
*******************************************************************************/
int LGObject::getChunkSize () {
	int iChunkSize = LGObject::getChunkHeaderSize ();		// Chunk size

	// Add subobjects sizes
	for (int iCount = 0; iCount < LGObject::iNrOfObjectGroups; iCount++) {

		// Add object size
		iChunkSize += LGObject::gpObjectGroups[iCount].getChunkSize ();
	}

	// Return chunk size
	return (iChunkSize);
}

/*******************************************************************************
* LGObject::draw
*******************************************************************************/
int LGObject::draw (int iFrame) {
float		outlineColor[3]	= { 0.0f, 0.0f, 0.0f };				// Color Of The Lines ( NEW )
float		outlineWidth	= 1.5f;								// Width Of The Lines ( NEW )
extern bool bDrawLine;
	// If anim start
//	if ((iFrame >= LGObject::iTime) && (iFrame < LGObject::iTime + LGObject::iAnimLength)) {

		// Draw objectgroups
		for (int iCount = 0; iCount < LGObject::iNrOfObjectGroups; iCount++) {

			// If not hidden
			if (LGObject::gpObjectGroups[iCount].bHide == false) {

				// Draw object
				LGObject::gpObjectGroups[iCount].draw (iFrame, LGObject::iFramesPerBrick, LGObject::iFramesBetweenBricks, LGObject::iAnimType);
			}
		}
	if (bDrawLine == true) {
		glEnable (GL_BLEND);				// Enable Blending
		glBlendFunc (GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA);
		glPolygonMode (GL_BACK, GL_LINE);		// Draw Backfacing Polygons As Wireframes
		glLineWidth (outlineWidth);			// Set The Line Width
		glCullFace (GL_FRONT);				// Don't Draw Any Front-Facing Polygons

		glDepthFunc (GL_LEQUAL);			// Change The Depth Mode

		glColor3fv (&outlineColor[0]);			// Set The Outline Color

		// Draw objectgroups
		for (iCount = 0; iCount < LGObject::iNrOfObjectGroups; iCount++) {

			// If not hidden
			if (LGObject::gpObjectGroups[iCount].bHide == false) {

				// Draw object
				LGObject::gpObjectGroups[iCount].draw (iFrame, LGObject::iFramesPerBrick, LGObject::iFramesBetweenBricks, LGObject::iAnimType);
			}
		}

		glDepthFunc (GL_LESS);				// Reset The Depth-Testing Mode
		glCullFace (GL_BACK);				// Reset The Face To Be Culled
		glPolygonMode (GL_BACK, GL_FILL);		// Reset Back-Facing Polygon Drawing Mode
		glDisable (GL_BLEND);				// Disable Blending
	}
	// Else and of anim
//	} else if (iFrame >= LGObject::iTime + LGObject::iAnimLength) {

		// Draw static model
//		LGObject::drawStatic ();
//	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::drawStatic
*******************************************************************************/
int LGObject::drawStatic () {

	// Todo

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::getAnimLength
*******************************************************************************/
int LGObject::getAnimLength () {
	int iNewTime = 0;		// New time
	int iTemp;				// Temp time

	// Calc highest anim start time
	for (int iCount = 0; iCount < LGObject::iNrOfObjectGroups; iCount++) {

		// Calc time
		iTemp = LGObject::gpObjectGroups[iCount].iTime +
			LGObject::iFramesPerBrick +
			(LGObject::gpObjectGroups[iCount].iNrOfBricks - 1) * LGObject::iFramesBetweenBricks;

		// Check if higher than current max
		if (iTemp > iNewTime) {
			iNewTime = iTemp;
		}
	}

	// Return new time
	return (iNewTime);
}

/*******************************************************************************
* LGObject::getNrOfBricks
*******************************************************************************/
int LGObject::getNrOfBricks () {
	int iNrOfBricks = 0;		// Number of bricks

	// Add groups
	for (int iCount = 0; iCount < LGObject::iNrOfObjectGroups; iCount++) {

		// Add bricks
		iNrOfBricks += LGObject::gpObjectGroups[iCount].iNrOfBricks;
	}

	// Return nr of bricks
	return (iNrOfBricks);
}

/*******************************************************************************
* LGObject::deleteObjectGroup
*******************************************************************************/
int LGObject::deleteObjectGroup (int iIndex) {
	LGObjectGroup*	bpTempObjectGroups;		// Temp buffer

	// Check if out of range
	if (iIndex >= LGObject::iNrOfObjectGroups) {

		// Return error
		return (-1);
	}

	// Alloc new bricks
	bpTempObjectGroups = new LGObjectGroup[LGObject::iNrOfObjectGroups - 1];

	// Copy till object group to be deleted
	memcpy (bpTempObjectGroups, LGObject::gpObjectGroups, sizeof (LGObjectGroup) * iIndex);

	// Copy after brick to be deleted
	memcpy (&bpTempObjectGroups[iIndex], &LGObject::gpObjectGroups[iIndex + 1], sizeof (LGObjectGroup) * (LGObject::iNrOfObjectGroups - iIndex - 1));

	// Decrease number of bricks
	LGObject::iNrOfObjectGroups--;

	// Realloc buffer
	LGObject::gpObjectGroups = new LGObjectGroup[LGObject::iNrOfObjectGroups];

	// Copy bricks
	memcpy (LGObject::gpObjectGroups, bpTempObjectGroups, sizeof (LGObjectGroup) * LGObject::iNrOfObjectGroups);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::addObjectGroup
*******************************************************************************/
int LGObject::addObjectGroup (char acName[16]) {
	LGObjectGroup*	bpTempObjectGroups;		// Temp buffer

	// Alloc new bricks
	bpTempObjectGroups = new LGObjectGroup[LGObject::iNrOfObjectGroups];

	// Copy till brick to be inserted
	memcpy (bpTempObjectGroups, LGObject::gpObjectGroups, sizeof (LGObjectGroup) * LGObject::iNrOfObjectGroups);

	// Decrease number of bricks
	LGObject::iNrOfObjectGroups++;

	// Realloc buffer
	LGObject::gpObjectGroups = new LGObjectGroup[LGObject::iNrOfObjectGroups];

	// Copy object groups
	memcpy (LGObject::gpObjectGroups, bpTempObjectGroups, sizeof (LGObjectGroup) * LGObject::iNrOfObjectGroups - 1);

	// Set default values
	strcpy (LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].acName, acName);
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].iNrOfBricks = 0;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].iTime = 0;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].bHide = false;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vOffset.fX = 0.0f;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vOffset.fY = 0.0f;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vOffset.fZ = 0.0f;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vRotate.fX = 0.0f;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vRotate.fY = 0.0f;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vRotate.fZ = 0.0f;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vRotationPoint.fX = 0.0f;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vRotationPoint.fY = 0.0f;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vRotationPoint.fZ = 0.0f;

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::cloneObjectGroup
*******************************************************************************/
int LGObject::cloneObjectGroup (int iObjectGroup) {
	LGObjectGroup*	bpTempObjectGroups;		// Temp buffer

	// Alloc new bricks
	bpTempObjectGroups = new LGObjectGroup[LGObject::iNrOfObjectGroups];

	// Copy till brick to be inserted
	memcpy (bpTempObjectGroups, LGObject::gpObjectGroups, sizeof (LGObjectGroup) * LGObject::iNrOfObjectGroups);

	// Increase number of bricks
	LGObject::iNrOfObjectGroups++;

	// Realloc buffer
	LGObject::gpObjectGroups = new LGObjectGroup[LGObject::iNrOfObjectGroups];

	// Copy object groups
	memcpy (LGObject::gpObjectGroups, bpTempObjectGroups, sizeof (LGObjectGroup) * LGObject::iNrOfObjectGroups - 1);

	// Clone object group
	strcpy (LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].acName, LGObject::gpObjectGroups[iObjectGroup].acName);
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].iNrOfBricks =			LGObject::gpObjectGroups[iObjectGroup].iNrOfBricks;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].iTime =				LGObject::gpObjectGroups[iObjectGroup].iTime;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].bHide =				LGObject::gpObjectGroups[iObjectGroup].bHide;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vOffset.fX =			LGObject::gpObjectGroups[iObjectGroup].vOffset.fX;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vOffset.fY =			LGObject::gpObjectGroups[iObjectGroup].vOffset.fY;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vOffset.fZ =			LGObject::gpObjectGroups[iObjectGroup].vOffset.fZ;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vRotate.fX =			LGObject::gpObjectGroups[iObjectGroup].vRotate.fX;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vRotate.fY =			LGObject::gpObjectGroups[iObjectGroup].vRotate.fY;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vRotate.fZ =			LGObject::gpObjectGroups[iObjectGroup].vRotate.fZ;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vRotationPoint.fX =	LGObject::gpObjectGroups[iObjectGroup].vRotationPoint.fX;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vRotationPoint.fY =	LGObject::gpObjectGroups[iObjectGroup].vRotationPoint.fY;
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].vRotationPoint.fZ =	LGObject::gpObjectGroups[iObjectGroup].vRotationPoint.fZ;

	// Alloc new brick
	LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].bpBricks = new LGBrick[LGObject::gpObjectGroups[iObjectGroup].iNrOfBricks];

	// Copy bricks
	memcpy (LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].bpBricks, LGObject::gpObjectGroups[iObjectGroup].bpBricks, sizeof (LGBrick) * LGObject::gpObjectGroups[iObjectGroup].iNrOfBricks);

	// Deselect all
	for (int iCount = 0; iCount < LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].iNrOfBricks; iCount++) {

		// Deselect
		LGObject::gpObjectGroups[LGObject::iNrOfObjectGroups - 1].bpBricks[iCount].bSelected = false;
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::cloneObjectGroup
*******************************************************************************/
int LGObject::replaceColor (int iOld, int iNew) {
	
	// Cycle through objectgroups
	for (int iCountGroups = 0; iCountGroups < LGObject::iNrOfObjectGroups; iCountGroups++) {

		// Cycle through bricks
		for (int iCountBricks = 0; iCountBricks < LGObject::gpObjectGroups[iCountGroups].iNrOfBricks; iCountBricks++) {

			// Check if color is to be replaced
			if (LGObject::gpObjectGroups[iCountGroups].bpBricks[iCountBricks].iColor == iOld) {

				// Set new color
				LGObject::gpObjectGroups[iCountGroups].bpBricks[iCountBricks].iColor = iNew;
			}
		}
	}

	// Return no error
	return (0);
}

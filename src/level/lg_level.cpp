/*******************************************************************************
* File:		lg_level.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 February 2005
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/level/lg_level.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* LGLevel::LGLevel
*******************************************************************************/
LGLevel::LGLevel () {
	LGLevel::iNrOfObjects = 0;
	LGLevel::opObjects = NULL;
	LGLevel::iNrOfPoints = 0;
	LGLevel::ppPoints = NULL;
}

/*******************************************************************************
* LGLevel::~LGLevel
*******************************************************************************/
LGLevel::~LGLevel () {

	// If allocated
	if (LGLevel::opObjects) {

		// Delete
		delete []LGLevel::opObjects;
	}

	// If allocated
	if (LGLevel::ppPoints) {

		// Delete
		delete []LGLevel::ppPoints;
	}
}

/*******************************************************************************
* LGLevel::readFromFile
*******************************************************************************/
int LGLevel::readFromFile (char* cpFilename) {
	/*
	int		iCurrentByte=0;		// Current byte in the buffer
	int		iFileLength;		// Length of the file
	FILE*	fpFile;				// Input file
	byte*	bpData;				// Buffer
	int		iChunkID;			// Chunk ID
	int		iChunkSize;			// Chunk size
	int		iCurrentObject=0;	// Current sub object

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
	if (strncmp ((char*)bpData, "OBL", 3) == 0) {

		// Set current byte
		iCurrentByte += 3;

		// Skip Chunksize
		iChunkSize = GetInt (bpData + iCurrentByte);
		iCurrentByte += 4;

		// Read number of objects
		LGLevel::iNrOfObjects = GetInt (bpData + iCurrentByte);
		iCurrentByte += 4;

		// Check if > 0
		if (LGLevel::iNrOfObjects > 0) {

			// Alloc objects
			LGLevel::opObjects = new LGObject[LGLevel::iNrOfObjects];
		}

		// Print status
		VerbosePrintf ("Number of objects: %d", LGLevel::iNrOfObjects);

	// No header found
	} else {
		// Print error
		ErrorPrintf ("This is no level file");

		// Return error
		return (-1);
	}

	// Get other chunks
	while (iCurrentByte < iFileLength) {
		// Get chunk id
		if (strncmp ((char*)(bpData + iCurrentByte), "OBJ", 3) == 0) iChunkID = OBJ_ID;
		else iChunkID = UNKNOWN_ID;
		iCurrentByte += SIZE_CHUNKID;

		// Get chunk size
		iChunkSize = GetInt (bpData + iCurrentByte);
		iCurrentByte += SIZE_INT;

		// Read chunk
		switch (iChunkID) {
			case OBJ_ID:
				// Print status
				VerbosePrintf ("OBJ chunk found");
				
				// Read objects
				LGLevel::opObjects[iCurrentObject].read (bpData + iCurrentByte, iChunkSize - SIZE_CHUNKID - SIZE_INT);

				// Inc current object
				iCurrentObject++;
				break;
			default:
				// Print status
				VerbosePrintf ("Read Scene: Unknown chunk found");
				break;
		}

		// Set current byte
		iCurrentByte += (iChunkSize - SIZE_CHUNKID - SIZE_INT);
	}
	
	// Free buffer
	delete []bpData;
	
	// Close file
	fclose (fpFile);
	*/

	// Return no error
	return (0);
}

/*******************************************************************************
* LGLevel::initDefaultValues
*******************************************************************************/
int LGLevel::initDefaultValues () {
	int iCount;

	// Print status
	VerbosePrintf ("Init level values");

	// Init objects
	LGLevel::iNrOfObjects = 9;
	LGLevel::opObjects = new LGObject[LGLevel::iNrOfObjects];

	for (iCount=0; iCount < LGLevel::iNrOfObjects; iCount++) {
		
		LGLevel::opObjects[iCount].initDefaultValues ((float)iCount*3,0.0f,3.0f,(float)((iCount+1)*3),0.0f,3.0f,iCount%4);
	}

	// Init points
	LGLevel::iNrOfPoints = 10;
	LGLevel::ppPoints = new LGPoint[LGLevel::iNrOfPoints];
	
	for (iCount=0; iCount < LGLevel::iNrOfPoints; iCount++) {
		
		LGLevel::ppPoints[iCount].initDefaultValues ((float)iCount*3,0.0f,3.0f);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGLevel::draw
*******************************************************************************/
int LGLevel::draw () {
	int iCount;

	// Print objects
	for (iCount = 0; iCount < LGLevel::iNrOfObjects; iCount++) {

		// Draw object
		LGLevel::opObjects[iCount].draw ();
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGLevel::writeToFile
*******************************************************************************/
int LGLevel::writeToFile (char* cpFilename) {
	FILE* fpFile;		// Output file
	float fMinX = 10000.0f;
	float fMinY = 10000.0f;
	float fMinZ = 10000.0f;
	int iCount;

	// Calc min
	for (iCount = 0; iCount < LGLevel::iNrOfObjects; iCount++) {

		if (LGLevel::opObjects[iCount].vVert1.fX < fMinX) { fMinX = LGLevel::opObjects[iCount].vVert1.fX; }
		if (LGLevel::opObjects[iCount].vVert1.fY < fMinY) { fMinY = LGLevel::opObjects[iCount].vVert1.fY; }
		if (LGLevel::opObjects[iCount].vVert1.fZ < fMinZ) { fMinZ = LGLevel::opObjects[iCount].vVert1.fZ; }

		if (LGLevel::opObjects[iCount].iType == 0) {
			if (LGLevel::opObjects[iCount].vVert2.fX < fMinX) { fMinX = LGLevel::opObjects[iCount].vVert2.fX; }
			if (LGLevel::opObjects[iCount].vVert2.fY < fMinY) { fMinY = LGLevel::opObjects[iCount].vVert2.fY; }
			if (LGLevel::opObjects[iCount].vVert2.fZ < fMinZ) { fMinZ = LGLevel::opObjects[iCount].vVert2.fZ; }
		}
	}

	// Open output file
	if (!(fpFile = fopen (cpFilename, "wt"))) {

		// Print error
		printf ("Error opening file: %s", cpFilename);

		// Return error
		return (-1);
	}

	// Print header
	PrintHeader (fpFile, cpFilename);

	// Print number of objects
	PrintInt12 (fpFile, LGLevel::iNrOfObjects);

	// Print objects
	for (iCount = 0; iCount < LGLevel::iNrOfObjects; iCount++) {

		// Write object
		LGLevel::opObjects[iCount].write (fpFile, fMinX, fMinY, fMinZ);
	}

	// Print footer
	PrintFooter (fpFile);

	// Close file
	fclose (fpFile);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGLevel::deletePoint
*******************************************************************************/
int LGLevel::deletePoint (int iIndex) {
	LGPoint*	bpTempPoints;		// Temp buffer

	// Check if out of range
	if (iIndex >= LGLevel::iNrOfPoints) {

		// Return error
		return (-1);
	}

	// Alloc new points
	bpTempPoints = new LGPoint[LGLevel::iNrOfPoints - 1];

	// Copy till point to be deleted
	memcpy (bpTempPoints, LGLevel::ppPoints, sizeof (LGPoint) * iIndex);

	// Copy after point to be deleted
	memcpy (&bpTempPoints[iIndex], &LGLevel::ppPoints[iIndex + 1], sizeof (LGPoint) * (LGLevel::iNrOfPoints - iIndex - 1));

	// Decrease number of points
	LGLevel::iNrOfPoints--;

	// Realloc buffer
	LGLevel::ppPoints = new LGPoint[LGLevel::iNrOfPoints];

	// Copy points
	memcpy (LGLevel::ppPoints, bpTempPoints, sizeof (LGPoint) * LGLevel::iNrOfPoints);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGLevel::deleteObject
*******************************************************************************/
int LGLevel::deleteObject (int iIndex) {
	LGObject*	bpTempObjects;		// Temp buffer

	// Check if out of range
	if (iIndex >= LGLevel::iNrOfObjects) {

		// Return error
		return (-1);
	}

	// Alloc new objects
	bpTempObjects = new LGObject[LGLevel::iNrOfObjects - 1];

	// Copy till object to be deleted
	memcpy (bpTempObjects, LGLevel::opObjects, sizeof (LGObject) * iIndex);

	// Copy after object to be deleted
	memcpy (&bpTempObjects[iIndex], &LGLevel::opObjects[iIndex + 1], sizeof (LGObject) * (LGLevel::iNrOfObjects - iIndex - 1));

	// Decrease number of objects
	LGLevel::iNrOfObjects--;

	// Realloc buffer
	LGLevel::opObjects = new LGObject[LGLevel::iNrOfObjects];

	// Copy objects
	memcpy (LGLevel::opObjects, bpTempObjects, sizeof (LGObject) * LGLevel::iNrOfObjects);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGLevel::insertPoint
*******************************************************************************/
int LGLevel::insertPoint (int iIndex) {
	LGPoint*	bpTempPoints;		// Temp buffer

	// Check if out of range
	if (iIndex >= LGLevel::iNrOfPoints) {

		// Return error
		return (-1);
	}

	// Alloc new points
	bpTempPoints = new LGPoint[LGLevel::iNrOfPoints + 1];

	// Copy till point to be inserted
	memcpy (bpTempPoints, LGLevel::ppPoints, sizeof (LGPoint) * (iIndex + 1));

	// Copy after point to be inserted
	memcpy (&bpTempPoints[iIndex + 1], &LGLevel::ppPoints[iIndex], sizeof (LGPoint) * (LGLevel::iNrOfPoints - iIndex));

	// Increase number of points
	LGLevel::iNrOfPoints++;

	// Realloc buffer
	LGLevel::ppPoints = new LGPoint[LGLevel::iNrOfPoints];

	// Copy points
	memcpy (LGLevel::ppPoints, bpTempPoints, sizeof (LGPoint) * LGLevel::iNrOfPoints);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGLevel::insertObject
*******************************************************************************/
int LGLevel::insertObject (int iIndex) {
	LGObject*	bpTempObjects;		// Temp buffer

	// Check if out of range
	if (iIndex >= LGLevel::iNrOfObjects) {

		// Return error
		return (-1);
	}

	// Alloc new objects
	bpTempObjects = new LGObject[LGLevel::iNrOfObjects + 1];

	// Copy till object to be inserted
	memcpy (bpTempObjects, LGLevel::opObjects, sizeof (LGObject) * (iIndex + 1));

	// Copy after object to be inserted
	memcpy (&bpTempObjects[iIndex + 1], &LGLevel::opObjects[iIndex], sizeof (LGObject) * (LGLevel::iNrOfObjects - iIndex));

	// Increase number of objects
	LGLevel::iNrOfObjects++;

	// Realloc buffer
	LGLevel::opObjects = new LGObject[LGLevel::iNrOfObjects];

	// Copy objects
	memcpy (LGLevel::opObjects, bpTempObjects, sizeof (LGObject) * LGLevel::iNrOfObjects);

	// Return no error
	return (0);
}


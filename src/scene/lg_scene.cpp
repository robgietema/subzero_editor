/*******************************************************************************
* File:		lg_scene.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		19 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/scene/lg_scene.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* LGScene::LGScene
*******************************************************************************/
LGScene::LGScene () {
	LGScene::iNrOfObjects = 0;
	LGScene::opObjects = NULL;
}

/*******************************************************************************
* LGScene::~LGScene
*******************************************************************************/
LGScene::~LGScene () {

	// If allocated
	if (LGScene::opObjects) {

		// Delete
		delete []LGScene::opObjects;
	}
}

/*******************************************************************************
* LGScene::readFromFile
*******************************************************************************/
int LGScene::readFromFile (char* cpFilename) {
	int		iCurrentByte=0;		// Current byte in the buffer
	int		iFileLength;		// Length of the OOF file
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
	if (strncmp ((char*)bpData, "SCN", 3) == 0) {

		// Set current byte
		iCurrentByte += 3;

		// Skip Chunksize
		iChunkSize = GetInt (bpData + iCurrentByte);
		iCurrentByte += 4;

		// Read number of objects
		LGScene::iNrOfObjects = GetInt (bpData + iCurrentByte);
		iCurrentByte += 4;

		// Check if > 0
		if (LGScene::iNrOfObjects > 0) {

			// Alloc objects
			LGScene::opObjects = new LGObjectInstance[LGScene::iNrOfObjects];
		}

		// Print status
		VerbosePrintf ("Number of objects: %d", LGScene::iNrOfObjects);

	// No header found
	} else {
		// Print error
		ErrorPrintf ("This is no scene file");

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
				LGScene::opObjects[iCurrentObject].read (bpData + iCurrentByte, iChunkSize - SIZE_CHUNKID - SIZE_INT);

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

	// Return no error
	return (0);
}

/*******************************************************************************
* LGScene::initDefaultValues
*******************************************************************************/
int LGScene::initDefaultValues () {

	// Vertex
	LGVertex3f vVertex;
	vVertex.fY = 0.0f;

	// Print status
	VerbosePrintf ("Init scene values");

	// Set default values
	LGScene::iNrOfObjects = 1;
	LGScene::opObjects = new LGObjectInstance[LGScene::iNrOfObjects];

	// Init object 1
	vVertex.fX = 0.0f;
	vVertex.fZ = 0.0f;
	LGScene::opObjects[0].initDefaultValues (vVertex, 0);
/*
	// Init object 2
	vVertex.fX = -17.6f;
	vVertex.fZ =  17.6f;
	LGScene::opObjects[1].initDefaultValues (vVertex, 0);

	// Init object 3
	vVertex.fX =  17.6f;
	vVertex.fZ = -17.6f;
	LGScene::opObjects[2].initDefaultValues (vVertex, 0);

	// Init object 4
	vVertex.fX = -17.6f;
	vVertex.fZ = -17.6f;
	LGScene::opObjects[3].initDefaultValues (vVertex, 0);
*/
	// Return no error
	return (0);
}

/*******************************************************************************
* LGScene::writeToFile
*******************************************************************************/
int LGScene::writeToFile (char* cpFilename) {
	FILE* fpFile;		// Output file

	// Open output file
	if (!(fpFile = fopen (cpFilename, "wb"))) {

		// Print error
		printf ("Error opening file: %s", cpFilename);

		// Return error
		return (-1);
	}

	// Print header id
	PrintChunkID (fpFile, "SCN");

	// Print chunk size
	PrintInt (fpFile, LGScene::getChunkSize ());

	// Print number of objects
	PrintInt (fpFile, LGScene::iNrOfObjects);

	// Print objects
	for (int iCount = 0; iCount < LGScene::iNrOfObjects; iCount++) {

		// Write object
		LGScene::opObjects[iCount].write (fpFile);
	}

	// Close file
	fclose (fpFile);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGScene::getChunkHeaderSize
*******************************************************************************/
int LGScene::getChunkHeaderSize () {
	int iChunkHeaderSize = 0;		// Chunk size

	// Add chunk fields
	iChunkHeaderSize += SIZE_CHUNKID;	// Chunk id
	iChunkHeaderSize += SIZE_INT;		// Chunk size
	iChunkHeaderSize += SIZE_INT;		// Number of objects

	// Return chunk size
	return (iChunkHeaderSize);
}

/*******************************************************************************
* LGScene::getChunkSize
*******************************************************************************/
int LGScene::getChunkSize () {
	int iChunkSize = LGScene::getChunkHeaderSize ();		// Chunk size

	// Add subobjects sizes
	for (int iCount = 0; iCount < LGScene::iNrOfObjects; iCount++) {

		// Add object size
		iChunkSize += LGScene::opObjects[iCount].getChunkSize ();
	}

	// Return chunk size
	return (iChunkSize);
}

/*******************************************************************************
* LGScene::draw
*******************************************************************************/
int LGScene::draw (int iFrame) {
	LGVertex3f	vOffset;
	
	// Draw objects
	for (int iCount = 0; iCount < LGScene::iNrOfObjects; iCount++) {

		// Reset The Modelview Matrix
//		glLoadIdentity ();

		glPushMatrix ();

		// Get previous offset
		vOffset = LGScene::opObjects[iCount].vOffset;

		// Translate to new object start point
		glTranslatef (vOffset.fX, vOffset.fY, vOffset.fZ);

		// Draw object
		LGScene::opObjects[iCount].draw (iFrame);

		glPopMatrix ();
	}

	// Return no error
	return (0);
}

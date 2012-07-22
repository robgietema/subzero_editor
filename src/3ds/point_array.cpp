/*******************************************************************************
* File:		point_array.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/point_array.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			POINT_ARRAY ()
*******************************************************************************/
POINT_ARRAY::POINT_ARRAY()
{
	// Initialize member variables
	POINT_ARRAY::iNrOfPoints = 0;
	POINT_ARRAY::pPoints = NULL;
}

/*******************************************************************************
* Name:			~POINT_ARRAY ()
*******************************************************************************/
POINT_ARRAY::~POINT_ARRAY()
{
	// If allocated
	if (POINT_ARRAY::pPoints) {

		// Delete
		delete []POINT_ARRAY::pPoints;
	}
}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int POINT_ARRAY::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCount;					// Counter
	int iPointCount;			// Number of faces

	// Print status
	VerbosePrintf ("Begin reading POINT_ARRAY chunk");
	
	// Check for zero length
	if (iNrOfBytes < (2 + (2 * 3)))
	{
		// Set error file contains no data
		ErrorPrintf ("File contains no data");

		// Return error
		return (-1);
	}

	// Get pointcount
	iPointCount = GetShort (bp3DSData);

	// Set number of points
	POINT_ARRAY::iNrOfPoints = iPointCount;

	// Check if > 0
	if (iPointCount > 0) {

		// Allocate point list
		POINT_ARRAY::pPoints = new POINT_3DS[iPointCount];
	}

	// Print status
	VerbosePrintf ("%d points found", iNrOfBytes / 12);

	// Get points from POINT_ARRAY chunk
	for (iCount = 0; iCount < iPointCount; iCount++)
	{
		// Get point		
		POINT_ARRAY::pPoints[iCount].fX = GetFloat (bp3DSData+2+(iCount*12));
		POINT_ARRAY::pPoints[iCount].fY = GetFloat (bp3DSData+2+(iCount*12)+4);
		POINT_ARRAY::pPoints[iCount].fZ = GetFloat (bp3DSData+2+(iCount*12)+8);

		// Print status
		VerbosePrintf ("Point: (%f,%f,%f)", 
			POINT_ARRAY::pPoints[iCount].fX, POINT_ARRAY::pPoints[iCount].fY,
			POINT_ARRAY::pPoints[iCount].fZ);
	}
	
	// Print status
	VerbosePrintf ("End reading POINT_ARRAY chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetFaces ()
*******************************************************************************/
int POINT_ARRAY::GetPoints (int* iNrOfPoints, POINT_3DS** pPoints)
{
	// Set return values
	*pPoints = POINT_ARRAY::pPoints;

	// Set number of points
	*iNrOfPoints = POINT_ARRAY::iNrOfPoints;
	
	// Return no error
	return (0);
}

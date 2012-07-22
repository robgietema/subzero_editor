/*******************************************************************************
* File:		face_smoothing.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		2 January 2004
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/face_smoothing.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			FACE_SMOOTHING ()
*******************************************************************************/
FACE_SMOOTHING::FACE_SMOOTHING ()
{

}

/*******************************************************************************
* Name:			~FACE_SMOOTHING ()
*******************************************************************************/
FACE_SMOOTHING::~FACE_SMOOTHING ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int FACE_SMOOTHING::Read3DS (int iNrOfBytes, byte* bp3DSData, int iFaces)
{
	int iCurrentByte = 0;	// Pointer to current byte in chunk

	// Set nr of faces
	FACE_SMOOTHING::iNrOfFaces = iFaces;

	// Allocate list
	FACE_SMOOTHING::aiFaceSmoothing = new int[iNrOfFaces];

	// Print status
	VerbosePrintf ("Begin reading FACE_SMOOTHING chunk");

	// Loop thru faces
	for (int iCount = 0; iCount < FACE_SMOOTHING::iNrOfFaces; iCount++) {

		// Get version from buffer
		FACE_SMOOTHING::aiFaceSmoothing[iCount] = GetInt (bp3DSData + iCurrentByte);
		iCurrentByte += SIZE_INT;
	
		// Print status
		VerbosePrintf ("Face smoothing face %d: %d", iCount, FACE_SMOOTHING::aiFaceSmoothing[iCount]);
	}

	// Print status
	VerbosePrintf ("End reading FACE_SMOOTHING chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* File:		local_axis.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		2 January 2004
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/local_axis.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			LOCAL_AXIS ()
*******************************************************************************/
LOCAL_AXIS::LOCAL_AXIS ()
{

}

/*******************************************************************************
* Name:			~LOCAL_AXIS ()
*******************************************************************************/
LOCAL_AXIS::~LOCAL_AXIS ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int LOCAL_AXIS::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCurrentByte = 0;	// Pointer to current byte in chunk

	// Print status
	VerbosePrintf ("Begin reading MAT_MAP_ROTATION chunk");

	// Get data from buffer
	LOCAL_AXIS::vX = GetVertex3f (bp3DSData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3F;
	LOCAL_AXIS::vY = GetVertex3f (bp3DSData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3F;
	LOCAL_AXIS::vZ = GetVertex3f (bp3DSData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3F;
	LOCAL_AXIS::vCenter = GetVertex3f (bp3DSData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3F;
	
	// Print status
	VerbosePrintf ("X-axis: %f, %f, %f", LOCAL_AXIS::vX.fX, LOCAL_AXIS::vX.fY, LOCAL_AXIS::vX.fZ);
	VerbosePrintf ("Y-axis: %f, %f, %f", LOCAL_AXIS::vY.fX, LOCAL_AXIS::vY.fY, LOCAL_AXIS::vY.fZ);
	VerbosePrintf ("Z-axis: %f, %f, %f", LOCAL_AXIS::vZ.fX, LOCAL_AXIS::vZ.fY, LOCAL_AXIS::vZ.fZ);
	VerbosePrintf ("Center: %f, %f, %f", LOCAL_AXIS::vCenter.fX, LOCAL_AXIS::vCenter.fY, LOCAL_AXIS::vCenter.fZ);
		
	// Print status
	VerbosePrintf ("End reading LOCAL_AXIS chunk");

	// Return no error
	return (0);
}

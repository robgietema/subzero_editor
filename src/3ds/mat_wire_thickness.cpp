/*******************************************************************************
* File:		mat_wire_thickness.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		2 January 2004
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/mat_wire_thickness.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MAT_WIRE_THICKNESS ()
*******************************************************************************/
MAT_WIRE_THICKNESS::MAT_WIRE_THICKNESS ()
{

}

/*******************************************************************************
* Name:			~MAT_WIRE_THICKNESS ()
*******************************************************************************/
MAT_WIRE_THICKNESS::~MAT_WIRE_THICKNESS ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MAT_WIRE_THICKNESS::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCurrentByte = 0;	// Pointer to current byte in chunk

	// Print status
	VerbosePrintf ("Begin reading MAT_WIRE_THICKNESS chunk");

	// Get version from buffer
	MAT_WIRE_THICKNESS::fWireThickness = GetFloat (bp3DSData);
	
	// Print status
	VerbosePrintf ("Wirethickness: %f", MAT_WIRE_THICKNESS::fWireThickness);
		
	// Print status
	VerbosePrintf ("End reading MAT_WIRE_THICKNESS chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetWireThickness ()
*******************************************************************************/
int MAT_WIRE_THICKNESS::GetWireThickness (float* fThickness)
{
	// Set return value
	*fThickness = MAT_WIRE_THICKNESS::fWireThickness;
	
	// Return no error
	return (0);
}

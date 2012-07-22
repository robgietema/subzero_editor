/*******************************************************************************
* File:		lin_color_f.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/lin_color_f.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			LIN_COLOR_F ()
*******************************************************************************/
LIN_COLOR_F::LIN_COLOR_F()
{
	// Initialize color to white
	LIN_COLOR_F::fRed 	= 1;
	LIN_COLOR_F::fGreen	= 1;
	LIN_COLOR_F::fBlue	= 1;
	LIN_COLOR_F::bUsed  = false;
}

/*******************************************************************************
* Name:			~LIN_COLOR_F ()
*******************************************************************************/
LIN_COLOR_F::~LIN_COLOR_F()
{

}

/*******************************************************************************
* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData)
*******************************************************************************/
int LIN_COLOR_F::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading LIN_COLOR_F chunk");

	// Check chunk length
	if (iNrOfBytes < 3)
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get color from buffer
	LIN_COLOR_F::fRed   = GetFloat (bp3DSData);
	LIN_COLOR_F::fGreen = GetFloat (bp3DSData + 1);
	LIN_COLOR_F::fBlue  = GetFloat (bp3DSData + 2);

	// Set color to used
	LIN_COLOR_F::bUsed = true;

	// Print status
	VerbosePrintf ("Color: (%f, %f, %f)", LIN_COLOR_F::fRed, 
		LIN_COLOR_F::fGreen, LIN_COLOR_F::fBlue);

	// Print status
	VerbosePrintf ("End reading LIN_COLOR_F chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:		Used ()
*******************************************************************************/
bool LIN_COLOR_F::Used (void)
{
	// Return used
	return (LIN_COLOR_F::bUsed);
}

/*******************************************************************************
* Name:			GetColor (float* fRed, float* fGreen, float* fBlue)
*******************************************************************************/
int LIN_COLOR_F::GetColor (float* fRed, float* fGreen, float* fBlue)
{
	// Assign values to parameter variables
	*fRed 	= LIN_COLOR_F::fRed;
	*fGreen = LIN_COLOR_F::fGreen;
	*fBlue 	= LIN_COLOR_F::fBlue;	

	// Return no error
	return (0);
}

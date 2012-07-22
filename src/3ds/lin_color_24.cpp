/*******************************************************************************
* File:		lin_color_24.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/lin_color_24.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			LIN_COLOR_24 ()
*******************************************************************************/
LIN_COLOR_24::LIN_COLOR_24 ()
{
	// Initialize color to white
	LIN_COLOR_24::bRed 	 = 255;
	LIN_COLOR_24::bGreen = 255;
	LIN_COLOR_24::bBlue	 = 255;
	LIN_COLOR_24::bUsed  = false;
}

/*******************************************************************************
* Name:			~LIN_COLOR_24 ()
*******************************************************************************/
LIN_COLOR_24::~LIN_COLOR_24 ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int LIN_COLOR_24::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading LIN_COLOR_24 chunk");

	// Check chunk length
	if (iNrOfBytes < 3)
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get color from buffer
	LIN_COLOR_24::bRed 	 = bp3DSData[0];
	LIN_COLOR_24::bGreen = bp3DSData[1];
	LIN_COLOR_24::bBlue  = bp3DSData[2];

	// Set color to used
	LIN_COLOR_24::bUsed = true;

	// Print status
	VerbosePrintf ("Color: (%d, %d, %d)", LIN_COLOR_24::bRed, 
		LIN_COLOR_24::bGreen, LIN_COLOR_24::bBlue);

	// Print status
	VerbosePrintf ("End reading LIN_COLOR_24 chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:		Used ()
*******************************************************************************/
bool LIN_COLOR_24::Used (void)
{
	// Return used
	return (LIN_COLOR_24::bUsed);
}

/*******************************************************************************
* Name:			GetColor ()
*******************************************************************************/
int LIN_COLOR_24::GetColor (byte* bRed, byte* bGreen, byte* bBlue)
{
	// Assign values to parameter variables
	*bRed 	= LIN_COLOR_24::bRed;
	*bGreen = LIN_COLOR_24::bGreen;
	*bBlue 	= LIN_COLOR_24::bBlue;	

	// Return no error
	return (0);
}

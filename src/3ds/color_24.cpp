/*******************************************************************************
* File:		color_24.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/color_24.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			COLOR_24 ()
*******************************************************************************/
COLOR_24::COLOR_24()
{
	// Initialize color to white
	COLOR_24::bRed 	 = 255;
	COLOR_24::bGreen = 255;
	COLOR_24::bBlue  = 255;
	COLOR_24::bUsed  = false;
}

/*******************************************************************************
* Name:			~COLOR_24 ()
*******************************************************************************/
COLOR_24::~COLOR_24()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int COLOR_24::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading COLOR_24 chunk");

	// Check chunk length
	if (iNrOfBytes < 3)
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get color from buffer
	COLOR_24::bRed 	 = bp3DSData[0];
	COLOR_24::bGreen = bp3DSData[1];
	COLOR_24::bBlue  = bp3DSData[2];
	
	// Set color to used
	COLOR_24::bUsed = true;

	// Print status
	VerbosePrintf ("Color: (%d, %d, %d)", COLOR_24::bRed, 
		COLOR_24::bGreen, COLOR_24::bBlue);

	// Print status
	VerbosePrintf ("End reading COLOR_24 chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:		Used ()
*******************************************************************************/
bool COLOR_24::Used (void)
{
	// Return used
	return (COLOR_24::bUsed);
}

/*******************************************************************************
* Name:			GetColor ()
*******************************************************************************/
int COLOR_24::GetColor (byte* bRed, byte* bGreen, byte* bBlue)
{
	// Assign values to parameter variables
	*bRed 	= COLOR_24::bRed;
	*bGreen = COLOR_24::bGreen;
	*bBlue 	= COLOR_24::bBlue;	

	// Return no error
	return (0);
}

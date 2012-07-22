/*******************************************************************************
* File:		color_f.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/color_f.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			COLOR_F ()
*******************************************************************************/
COLOR_F::COLOR_F()
{
	// Initialize color to white
	COLOR_F::fRed 	= 1;
	COLOR_F::fGreen	= 1;
	COLOR_F::fBlue	= 1;
	COLOR_F::bUsed  = false;
}

/*******************************************************************************
* Name:			~COLOR_F ()
*******************************************************************************/
COLOR_F::~COLOR_F()
{

}
		
/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int COLOR_F::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading COLOR_F chunk");

	// Check chunk length
	if (iNrOfBytes < 3)
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get color from buffer
	COLOR_F::fRed   = GetFloat (bp3DSData);
	COLOR_F::fGreen = GetFloat (bp3DSData + 1);
	COLOR_F::fBlue  = GetFloat (bp3DSData + 2);

	// Set color to used
	COLOR_F::bUsed = true;

	// Print status
	VerbosePrintf ("Color: (%f, %f, %f)", COLOR_F::fRed, 
		COLOR_F::fGreen, COLOR_F::fBlue);

	// Print status
	VerbosePrintf ("End reading COLOR_F chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:		Used ()
*******************************************************************************/
bool COLOR_F::Used (void)
{
	// Return used
	return (COLOR_F::bUsed);
}

/*******************************************************************************
* Name:			GetColor ()
*******************************************************************************/
int COLOR_F::GetColor (float* fRed, float* fGreen, float* fBlue)
{
	// Assign values to parameter variables
	*fRed 	= COLOR_F::fRed;
	*fGreen = COLOR_F::fGreen;
	*fBlue 	= COLOR_F::fBlue;	

	// Return no error
	return (0);
}

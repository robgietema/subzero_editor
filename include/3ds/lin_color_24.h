/*******************************************************************************
* File:		lin_color_24.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (LIN_COLOR_24_H)
#define LIN_COLOR_24_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/3ds.h"
#include "../../include/lg_print.h"
#include "../../include/3ds/chunks.h"
#include "../../include/lg_buffer_functions.h"

////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	LIN_COLOR_24
* Function:		This class is used to describe a linear color.
*******************************************************************************/
class LIN_COLOR_24  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LIN_COLOR_24 ()
		* Function:		Constructor
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		LIN_COLOR_24 ();

		/***********************************************************************
		* Name:			~LIN_COLOR_24 ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~LIN_COLOR_24 ();

		/***********************************************************************
		* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData)
		* Function:		This function reads 3ds data.
		* Pre:          bp3DSData contains the 3DS data and iNrOfBytes
		*				contains the number of bytes in the 3DS data.
		* Post:         3DS data is stored in the datastructure.
		***********************************************************************/
		int Read3DS (int iNrOfBytes, byte* bp3DSData);

		/***********************************************************************
		* Name:			Used (void)
		* Function:		This function checks if the color is used.
		* Pre:          -
		* Post:         True is returned if color is used else false.
		***********************************************************************/
		bool Used (void);

		/***********************************************************************
		* Name:			GetColor (byte* bRed, byte* bGreen, byte* bBlue)
		* Function:		This function return a color.
		* Pre:          -
		* Post:         bRed contains the red value, bGreen the green and
		*				bBlue the blue.
		***********************************************************************/
		int GetColor (byte* bRed, byte* bGreen, byte* bBlue);

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
		byte		bRed;		// Red value (0 - 255)
		byte		bGreen;		// Green value (0 - 255)
		byte		bBlue;		// Blue value (0 - 255)
		bool		bUsed;		// True if color is used else false
}; // End LIN_COLOR_24

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

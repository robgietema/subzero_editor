/*******************************************************************************
* File:		lin_color_f.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (LIN_COLOR_F_H)
#define LIN_COLOR_F_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/3ds.h"
#include "../../include/lg_print.h"
#include "../../include/3ds/chunks.h"
#include "../../include/lg_buffer_functions.h"


////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	LIN_COLOR_F
* Function:		This class is used to describe a linear color.
*******************************************************************************/
class LIN_COLOR_F  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LIN_COLOR_F ()
		* Function:		Constructor
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		LIN_COLOR_F ();

		/***********************************************************************
		* Name:			~LIN_COLOR_24 ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~LIN_COLOR_F ();

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
		* Name:			GetColor (float* fRed, float* fGreen, float* fBlue)
		* Function:		This function return a color.
		* Pre:          -
		* Post:         fRed contains the red value, fGreen the green and
		*				fBlue the blue.
		***********************************************************************/
		int GetColor (float* fRed, float* fGreen, float* fBlue);

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
		float		fRed;			// Red value (0.0 - 1.0)
		float		fGreen;			// Green value (0.0 - 1.0)
		float		fBlue;			// Blue value (0.0 - 1.0)
		bool		bUsed;			// True if color is used
}; // End LIN_COLOR_F

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

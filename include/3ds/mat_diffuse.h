/*******************************************************************************
* File:		mat_diffuse.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (MAT_DIFFUSE_H)
#define MAT_DIFFUSE_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/3ds.h"
#include "../../include/lg_print.h"
#include "../../include/3ds/chunks.h"
#include "../../include/lg_buffer_functions.h"
#include "../../include/3ds/color_24.h"
#include "../../include/3ds/lin_color_24.h"

////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	MAT_DIFFUSE
* Function:		This class describes the diffuse color of the material.
*******************************************************************************/
class MAT_DIFFUSE  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			MAT_DIFFUSE ()
		* Function:		Constructor
		* Pre:          - 
		* Post:         Object is created.
		***********************************************************************/
		MAT_DIFFUSE ();

		/***********************************************************************
		* Name:			~MAT_DIFFUSE ()
		* Function:		Destructor 
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~MAT_DIFFUSE ();

		/***********************************************************************
		* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData)
		* Function:		This function reads 3ds data.
		* Pre:          bp3DSData contains the 3DS data and iNrOfBytes
		*				contains the number of bytes in the 3DS data.
		* Post:         3DS data is stored in the datastructure.
		***********************************************************************/
		int Read3DS (int iNrOfBytes, byte* bp3DSData);

		/***********************************************************************
		* Name:			GetColor (byte* bRed, byte* bGreen, byte* bBlue)
		* Function:		This function return a color.
		* Pre:          -
		* Post:         bRed contains the red value, bGreen the green and
		*				bBlue the blue.	
		***********************************************************************/
		int GetColor (byte* bRed, byte* bGreen, byte* bBlue);

		/***********************************************************************
		* Name:			GetLinColor (byte* bRed, byte* bGreen, byte* bBlue)
		* Function:		This function returns a color.
		* Pre:          -
		* Post:         bRed contains the red value, bGreen the green and
		*				bBlue the blue.
		***********************************************************************/
		int GetLinColor (byte* bRed, byte* bGreen, byte* bBlue);

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
		COLOR_24		cColor24;		// Version R1 & R2
		LIN_COLOR_24	cLinColor24;	// Version R3 (optional)
}; // End MAT_DIFFUSE

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

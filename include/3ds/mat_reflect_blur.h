/*******************************************************************************
* File:		mat_reflect_blur.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (MAT_REFLECT_BLUR_H)
#define MAT_REFLECT_BLUR_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/3ds.h"
#include "../../include/lg_print.h"
#include "../../include/3ds/chunks.h"
#include "../../include/lg_buffer_functions.h"
#include "../../include/3ds/int_percentage.h"

////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	MAT_REFLECT_BLUR
* Function:		This class describes the percentage of reflect blur of the
*               material.
*******************************************************************************/
class MAT_REFLECT_BLUR  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			MAT_REFLECT_BLUR ()
		* Function:		Constructor 
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		MAT_REFLECT_BLUR ();

		/***********************************************************************
		* Name:			~MAT_REFLECT_BLUR ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~MAT_REFLECT_BLUR ();

		/***********************************************************************
		* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData)
		* Function:		This function reads 3ds data.
		* Pre:          bp3DSData contains the 3DS data and iNrOfBytes
		*				contains the number of bytes in the 3DS data.
		* Post:         3DS data is stored in the datastructure.
		***********************************************************************/
		int Read3DS (int iNrOfBytes, byte* bp3DSData);

		/***********************************************************************
		* Name:			GetShininess (int* iPercentage)
		* Function:		This function return the shininess.
		* Pre:          -
		* Post:         iPercentage contains percentage of shininess.
		***********************************************************************/
		int GetShininess (int* iPercentage);

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
		INT_PERCENTAGE		pIntPercentage;		// Percentage (0 - 100)
}; // End MAT_REFLECT_BLUR

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

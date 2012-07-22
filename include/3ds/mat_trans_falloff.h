/*******************************************************************************
* File:		mat_trans_falloff.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (MAT_TRANS_FALLOFF_H)
#define MAT_TRANS_FALLOFF_H
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
* Classname:	MAT_TRANS_FALLOFF
* Function:		This class describes the percentage of trans falloff of the
*               material.
*******************************************************************************/
class MAT_TRANS_FALLOFF  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			MAT_TRANS_FALLOFF ()
		* Function:		Constructor 
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		MAT_TRANS_FALLOFF ();

		/***********************************************************************
		* Name:			~MAT_TRANS_FALLOFF ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~MAT_TRANS_FALLOFF ();

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
}; // End MAT_TRANS_FALLOFF

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

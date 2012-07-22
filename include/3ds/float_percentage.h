/*******************************************************************************
* File:		float_percentage.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (FLOAT_PERCENTAGE_H)
#define FLOAT_PERCENTAGE_H
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
* Classname:	FLOAT_PERCENTAGE
* Function:		This class is used to describe a percentage from 0 to 1.
*******************************************************************************/
class FLOAT_PERCENTAGE  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			FLOAT_PERCENTAGE ()
		* Function:		Constructor
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		FLOAT_PERCENTAGE ();

		/***********************************************************************
		* Name:			~FLOAT_PERCENTAGE ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~FLOAT_PERCENTAGE ();

		/***********************************************************************
		* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData)
		* Function:		This function reads 3ds data.
		* Pre:          bp3DSData contains the 3DS data and iNrOfBytes
		*				contains the number of bytes in the 3DS data.
		* Post:         3DS data is stored in the datastructure.
		***********************************************************************/
		int Read3DS (int iNrOfBytes, byte* bp3DSData);

		/***********************************************************************
		* Name:			GetPercentage (float* fPercentage)
		* Function:		This function returns the percentage.
		* Pre:          -
		* Post:         fPercentage contains the percentage.
		***********************************************************************/
		int GetPercentage (float* fPercentage);

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
		float		fPercentage;		// Percentage (0.0 - 1.0)
}; // End FLOAT_PERCENTAGE

////////////////////////////////////////////////////////////////////////////////
#endif 
////////////////////////////////////////////////////////////////////////////////
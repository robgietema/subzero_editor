/*******************************************************************************
* File:		mat_name.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (MAT_NAME_H)
#define MAT_NAME_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <string.h>
#include "../../include/3ds/3ds.h"
#include "../../include/lg_print.h"
#include "../../include/3ds/chunks.h"
#include "../../include/lg_buffer_functions.h"


////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	MAT_NAME
* Function:		This class describes the name of the material
*******************************************************************************/
class MAT_NAME  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			MAT_NAME ()
		* Function:		Constructor
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		MAT_NAME ();

		/***********************************************************************
		* Name:			~MAT_NAME ()
		* Function:		Destructor
		* Pre:          - 
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~MAT_NAME ();

		/***********************************************************************
		* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData) 
		* Function:		This function reads 3ds data.
		* Pre:          bp3DSData contains the 3DS data and iNrOfBytes
		*				contains the number of bytes in the 3DS data.
		* Post:         3DS data is stored in the datastructure.
		***********************************************************************/
		int Read3DS (int iNrOfBytes, byte* bp3DSData);

		/***********************************************************************
		* Name:			GetMatName (char acMatName[16])
		* Function:		This function return the material name.
		* Pre:          -
		* Post:         acMatName contains the material name.
		***********************************************************************/
		int GetMatName (char acMatName[256]);

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		char		acName[256];			// Name of the material

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End MAT_NAME

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
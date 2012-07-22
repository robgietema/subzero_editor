/*******************************************************************************
* File:		mat_shading.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (MAT_SHADING_H)
#define MAT_SHADING_H
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
* Classname:	MAT_SHADING
* Function:		This class descrives the display method of the material.
*******************************************************************************/
class MAT_SHADING  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			MAT_SHADING ()
		* Function:		Constructor
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		MAT_SHADING ();

		/***********************************************************************
		* Name:			~MAT_SHADING ()
		* Function:		Destructor 
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~MAT_SHADING ();

		/***********************************************************************
		* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData) 
		* Function:		This function reads 3ds data.
		* Pre:          bp3DSData contains the 3DS data and iNrOfBytes
		*				contains the number of bytes in the 3DS data.
		* Post:         3DS data is stored in the datastructure.
		***********************************************************************/
		int Read3DS (int iNrOfBytes, byte* bp3DSData);

		/***********************************************************************
		* Name:			GetDisplayMethod (int* iDisplayMethod)
		* Function:		This function return a display method.
		* Pre:          -
		* Post:         iDisplayMethod contains the display method.
		*					0 (wireframe)
		*					1 (flat shading)
		*					2 (Gourand)
		*					3 (Phong)
		*					4 (Metal)
		***********************************************************************/
		int GetDisplayMethod (int* iDisplayMethod);

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
		int		iDisplayMethod;			// Display method: 
										//		0 (wireframe)
										//		1 (flat shading)
										//		2 (Gourand)
										//		3 (Phong)
										//		4 (Metal)
}; // End MAT_SHADING

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

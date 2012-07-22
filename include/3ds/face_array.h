/*******************************************************************************
* File:		face_array.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (FACE_ARRAY_H)
#define FACE_ARRAY_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <string.h>
#include "../../include/3ds/3ds.h"
#include "../../include/lg_print.h"
#include "../../include/3ds/chunks.h"
#include "../../include/lg_buffer_functions.h"
#include "../../include/3ds/msh_mat_group.h"
#include "../../include/3ds/face_smoothing.h"

////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	FACE_ARRAY
* Function:		This class is used to describe an array of faces with it's
*				materials.
*******************************************************************************/
class FACE_ARRAY  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			FACE_ARRAY ()
		* Function:		Constructor
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		FACE_ARRAY ();

		/***********************************************************************
		* Name:			~FACE_ARRAY ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~FACE_ARRAY ();

		/***********************************************************************
		* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData)
		* Function:		This function reads 3ds data.
		* Pre:          bp3DSData contains the 3DS data and iNrOfBytes
		*				contains the number of bytes in the 3DS data.
		* Post:         3DS data is stored in the datastructure.
		***********************************************************************/
		int Read3DS (int iNrOfBytes, byte* bp3DSData);

		/***********************************************************************
		* Name:			GetFaces (int* iNrOfFaces, FACE* fFaces)
		* Function:		This function return a list of faces.
		* Pre:          -
		* Post:         iNrOfFaces contains the number of faces. fFaces
		*				contains the list of faces.
		***********************************************************************/
		int GetFaces (int* iNrOfFaces, FACE_MAT** fFaces);

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		int				iNrOfFaces;				// Number of faces
		FACE_3DS*		fFaces;					// Array of faces
		int				iNrOfMshMatGroups;		// Number of materialgroups
		MSH_MAT_GROUP*	mMshMatGroups;			// Array of materialgroups
		FACE_SMOOTHING	sFaceSmoothing;			// Face smoothing

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End FACE_ARRAY

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

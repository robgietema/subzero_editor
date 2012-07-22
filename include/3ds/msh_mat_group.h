/*******************************************************************************
* File:		msh_mat_group.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (MSH_MAT_GROUP_H)
#define MSH_MAT_GROUP_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/3ds.h"
#include "../../include/lg_print.h"
#include "../../include/3ds/chunks.h"
#include "../../include/lg_buffer_functions.h"
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	MSH_MAT_GROUP
* Function:		This class is used to map the materials to the faces.
*******************************************************************************/
class MSH_MAT_GROUP  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			MSH_MAT_GROUP ()
		* Function:		Constructor
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		MSH_MAT_GROUP ();

		/***********************************************************************
		* Name:			~MSH_MAT_GROUP ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~MSH_MAT_GROUP ();

		/***********************************************************************
		* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData)
		* Function:		This function reads 3ds data.
		* Pre:          bp3DSData contains the 3DS data and iNrOfBytes
		*				contains the number of bytes in the 3DS data.
		* Post:         3DS data is stored in the datastructure.
		***********************************************************************/
		int Read3DS (int iNrOfBytes, byte* bp3DSData);

		/***********************************************************************
		* Name:			GetMaterialName (int iFace, char acMatName[16])
		* Function:		This function returns the name of the material if
		*				the specified face is in the face list.	Else
		*				it returns a zero string.
		* Pre:          iFace specifies a face number.
		* Post:         acMatName contains the name of the material of
		*				the specified face if the face exists in the face
		*				list. Else acMatName is zero.
		***********************************************************************/
		int GetMaterialName (int iFace, char acMatName[16]);

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		char		acName[256];	// Name of the material
		int			iNrOfFaces;		// Number of faces to map the material
		int*		iFaces;			// List of faces to map the material

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End MSH_MAT_GROUP

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

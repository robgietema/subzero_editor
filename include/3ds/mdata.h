/*******************************************************************************
* File:		mdata.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (MDATA_H)
#define MDATA_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/3ds.h"
#include "../../include/lg_print.h"
#include "../../include/3ds/chunks.h"
#include "../../include/lg_buffer_functions.h"
#include "../../include/3ds/mesh_version.h"
#include "../../include/3ds/mat_entry.h"
#include "../../include/3ds/master_scale.h"
#include "../../include/3ds/named_object.h"

////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	MDATA
* Function:		This class describes all the data from the file.
*******************************************************************************/
class MDATA  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			MDATA ()
		* Function:		Constructor
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		MDATA ();

		/***********************************************************************
		* Name:			~MDATA ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~MDATA ();

		/***********************************************************************
		* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData)
		* Function:		This function reads 3ds data.
		* Pre:          bp3DSData contains the 3DS data and iNrOfBytes
		*				contains the number of bytes in the 3DS data.
		* Post:         3DS data is stored in the datastructure.
		***********************************************************************/
		int Read3DS (int iNrOfBytes, byte* bp3DSData);

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		MESH_VERSION	vMeshVersion;		// Mesh version
		MAT_ENTRY*		eMatEntry;			// List of materials
		int				iNrOfMatEntries;	// Number of material entries
		MASTER_SCALE	sMasterScale;		// Scale factor
		NAMED_OBJECT*	oNamedObject;		// List of objects
		int				iNrOfNamedObjects;	// Number of named objects

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End MDATA

////////////////////////////////////////////////////////////////////////////////
#endif 
////////////////////////////////////////////////////////////////////////////////

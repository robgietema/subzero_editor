/*******************************************************************************
* File:		named_object.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (NAMED_OBJECT_H)
#define NAMED_OBJECT_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/3ds.h"
#include "../../include/lg_print.h"
#include "../../include/3ds/chunks.h"
#include "../../include/lg_buffer_functions.h"
#include "../../include/3ds/n_tri_object.h"
#include "../../include/3ds/light.h"
#include "../../include/3ds/camera.h"

////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	NAMED_OBJECT
* Function:		This class defines an object. This can be a polygon mesh
*               object, a camera or a light.
*******************************************************************************/
class NAMED_OBJECT  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			NAMED_OBJECT ()
		* Function:		Constructor
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		NAMED_OBJECT ();

		/***********************************************************************
		* Name:			~NAMED_OBJECT ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~NAMED_OBJECT ();

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
		char			acName[256];		// Name of the object
		N_TRI_OBJECT*	oNTriObject;		// List of objects
		int				iNrOfNTriObjects;	// Number of objects
		LIGHT*			lLight;				// List of lights
		int				iNrOfLights;		// Number of lights
		CAMERA*			cCamera;			// List of cameras
		int				iNrOfCameras;		// Number of cameras

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End NAMED_OBJECT

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

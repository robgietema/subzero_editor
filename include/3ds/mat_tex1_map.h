/*******************************************************************************
* File:		mat_tex1_map.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		2 January 2004
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (MAT_TEX1_MAP_H)
#define MAT_TEX1_MAP_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../3ds/3ds.h"
#include "../lg_print.h"
#include "../3ds/chunks.h"
#include "../lg_buffer_functions.h"
#include "../3ds/int_percentage.h"
#include "../3ds/mat_map_blur.h"
#include "../3ds/mat_map_filename.h"
#include "../3ds/mat_map_options.h"
#include "../3ds/mat_map_rotation.h"
#include "../lg_opengl.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	MAT_TEX1_MAP
* Function:		This class describes the first texture map.
*******************************************************************************/
class MAT_TEX1_MAP  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			MAT_TEX1_MAP ()
		* Function:		Constructor 
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		MAT_TEX1_MAP ();

		/***********************************************************************
		* Name:			~MAT_TEX1_MAP ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~MAT_TEX1_MAP ();

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
		INT_PERCENTAGE		pIntPercentage;		// Percentage
		MAT_MAP_BLUR		bBlur;				// Blur
		MAT_MAP_FILENAME	fFilename;			// Filename
		MAT_MAP_OPTIONS		oOptions;			// Options
		MAT_MAP_ROTATION	rRotation;			// Rotation
		GLuint				iTexture;			// Texture

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End MAT_TEX1_MAP

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

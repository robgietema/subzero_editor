/*******************************************************************************
* File:		mat_bump_map.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		2 January 2004
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (MAT_BUMP_MAP_H)
#define MAT_BUMP_MAP_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/3ds.h"
#include "../../include/lg_print.h"
#include "../../include/3ds/chunks.h"
#include "../../include/lg_buffer_functions.h"
#include "../../include/3ds/int_percentage.h"
#include "../../include/3ds/mat_map_blur.h"
#include "../../include/3ds/mat_map_filename.h"
#include "../../include/3ds/mat_map_options.h"
#include "../../include/3ds/mat_map_rotation.h"
#include "../../include/3ds/mat_bump_display_per.h"

////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	MAT_BUMP_MAP
* Function:		This class describes the first texture map.
*******************************************************************************/
class MAT_BUMP_MAP  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			MAT_BUMP_MAP ()
		* Function:		Constructor 
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		MAT_BUMP_MAP ();

		/***********************************************************************
		* Name:			~MAT_BUMP_MAP ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~MAT_BUMP_MAP ();

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

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
		INT_PERCENTAGE			pIntPercentage;		// Percentage
		MAT_MAP_BLUR			bBlur;				// Blur
		MAT_MAP_FILENAME		fFilename;			// Filename
		MAT_MAP_OPTIONS			oOptions;			// Options
		MAT_BUMP_DISPLAY_PER	dDisplay;			// Percentage of display
		MAT_MAP_ROTATION		rRotation;			// Rotation
}; // End MAT_BUMP_MAP

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

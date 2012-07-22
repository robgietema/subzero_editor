/*******************************************************************************
* File:		light.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (LIGHT_H)
#define LIGHT_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "../../include/3ds/3ds.h"
#include "../../include/lg_print.h"
#include "../../include/3ds/chunks.h"
#include "../../include/lg_buffer_functions.h"
#include "../../include/3ds/color_24.h"
#include "../../include/3ds/color_f.h"
#include "../../include/3ds/lin_color_f.h"
#include "../../include/3ds/lin_color_24.h"
#include "../../include/3ds/spotlight.h"
#include "../../include/3ds/light_off.h"


////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	LIGHT
* Function:		This class is used to describe a light.
*******************************************************************************/
class LIGHT  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LIGHT ()
		* Function:		Constructor
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		LIGHT ();

		/***********************************************************************
		* Name:			~LIGHT ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~LIGHT ();

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
		float			fX;				// X-Coordinate of light
		float			fY;				// Y-Coordinate of light
		float			fZ;				// Z-Coordinate of light
		COLOR_24		cColor24;		// Version R1 & R2
		LIN_COLOR_24	cLinColor24;	// Version R3 (optional)
		COLOR_F			cColorF;		// Version R1 & R2
		LIN_COLOR_F		cLinColorF;		// Version R3 (optional)
		SPOTLIGHT		lSpotLight;		// Contains data of a spotlight
		LIGHT_OFF		lLightOff;		// Light is on or off
}; // End LIGHT

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* File:		lg_point.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		5 February 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_POINT_H
#define LG_POINT_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../lg_datatypes.h"
#include "../lg_print.h"
#include "../lg_math.h"
#include "../lg_buffer_functions.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/*******************************************************************************
* Classname:	LGPoint
* Function:		This class describes an point.
*******************************************************************************/
class LGPoint {
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LGPoint ()
		* Function:		Constructor
		* Pre:			-
		* Post:			Object is created.
		***********************************************************************/
		LGPoint ();

		/***********************************************************************
		* Name:			~LGPoint ()
		* Function:		Destructor
		* Pre:			-
		* Post:			Object is destroyed.
		***********************************************************************/
		virtual ~LGPoint ();

		/***********************************************************************
		* Name:			initDefaultValues (float fX, float fY, float fZ)
		* Function:		Init point with default values
		* Pre:			-
		* Post:			Point has default values
		***********************************************************************/
		int initDefaultValues (float fX, float fY, float fZ);

		/***********************************************************************
		* Name:			draw ();
		* Function:		This function draws the brick.
		* Pre:			Brick is written into memory.
		* Post:			Brick is drawn.
		***********************************************************************/
		int draw ();

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		LGVertex3f	vPos;			// Position
		bool		bSelected;		// Brick selected

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End LGPoint

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

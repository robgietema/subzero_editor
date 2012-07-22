/*******************************************************************************
* File:		lg_object.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		5 February 2005
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_OBJECT_H
#define LG_OBJECT_H
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
* Classname:	LGObject
* Function:		This class describes an object.
*******************************************************************************/
class LGObject {
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LGObject ()
		* Function:		Constructor
		* Pre:			-
		* Post:			Object is created.
		***********************************************************************/
		LGObject ();

		/***********************************************************************
		* Name:			~LGObject ()
		* Function:		Destructor
		* Pre:			-
		* Post:			Object is destroyed.
		***********************************************************************/
		virtual ~LGObject ();

		/***********************************************************************
		* Name:			initDefaultValues (float fX1, float fY1, float fZ1, float fX2, float fY2, float fZ2, int iTexture)
		* Function:		Init object with default values
		* Pre:			-
		* Post:			Object has default values
		***********************************************************************/
		int initDefaultValues (float fX1, float fY1, float fZ1, float fX2, float fY2, float fZ2, int iTexture);

		/***********************************************************************
		* Name:			draw ();
		* Function:		This function draws the object.
		* Pre:			Object is written into memory.
		* Post:			Object is drawn.
		***********************************************************************/
		int draw ();

		int write (FILE* fpFile, float fMinX, float fMinY, float fMinZ);

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		int			iType;			// Type of object
		int			iSubType;		// Subtype of object
		int			iItem;			// Item
		int			iTexture;		// Texture
		int			iEnemy;			// Enemy
		int			iCritter;		// Critter

		float		fHeight;		// Height
		float		fWidth;			// Width

		bool		bSelected;		// Selected;

		LGVertex3f	vVert1;
		LGVertex3f	vVert2;

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End LGObject

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

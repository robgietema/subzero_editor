/*******************************************************************************
* File:		lg_level.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:     5 February 2005
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_LEVEL_H
#define LG_LEVEL_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../lg_datatypes.h"
#include "../lg_print.h"
#include "../lg_buffer_functions.h"
#include "../lg_opengl.h"
#include "lg_object.h"
#include "lg_point.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <GL/gl.h>

/*******************************************************************************
* Classname:	LGLevel
* Function:		This class describes a scene.
*******************************************************************************/
class LGLevel {
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LGLevel ()
		* Function:		Constructor
		* Pre:			-
		* Post:			Object is created.
		***********************************************************************/
		LGLevel ();

		/***********************************************************************
		* Name:			~LGLevel ()
		* Function:		Destructor
		* Pre:			-
		* Post:			Object is destroyed.
		***********************************************************************/
		virtual ~LGLevel ();

		/***********************************************************************
		* Name:			readFromFile (char* apFilename)
		* Function:		This function reads a file into memory.
		* Pre:			-
		* Post:			File is red into memory.
		***********************************************************************/
		int readFromFile (char* cpFilename);

		/***********************************************************************
		* Name:			initDefaultValues ()
		* Function:		Init level with default values
		* Pre:			-
		* Post:			Scene has default values
		***********************************************************************/
		int initDefaultValues ();

		/***********************************************************************
		* Name:			writeToFile (char* cpFilename)
		* Function:		This function writes a scene to a file.
		* Pre:			Scene is written into memory.
		* Post:			File is written.
		***********************************************************************/
		int writeToFile (char* cpFilename);

		/***********************************************************************
		* Name:			draw ()
		* Function:		This function draws the object
		* Pre:			-
		* Post:			Object is drawn
		***********************************************************************/
		int draw ();

		/***********************************************************************
		* Name:			deletePoint (int iIndex)
		* Function:		This function deletes a point
		* Pre:			-
		* Post:			Point is deleted
		***********************************************************************/
		int deletePoint (int iIndex);

		/***********************************************************************
		* Name:			deleteObject (int iIndex)
		* Function:		This function deletes a object
		* Pre:			-
		* Post:			Object is deleted
		***********************************************************************/
		int deleteObject (int iIndex);

		/***********************************************************************
		* Name:			insertPoint (int iIndex)
		* Function:		This function inserts a point
		* Pre:			-
		* Post:			Point is inserted
		***********************************************************************/
		int insertPoint (int iIndex);

		/***********************************************************************
		* Name:			insertObject (int iIndex)
		* Function:		This function inserts a object
		* Pre:			-
		* Post:			Point is inserted
		***********************************************************************/
		int insertObject (int iIndex);

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		int			iNrOfObjects;	// Number of objects
		LGObject	*opObjects;		// Objects
		int			iNrOfPoints;	// Number of points
		LGPoint		*ppPoints;		// Points

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End LGLevel

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

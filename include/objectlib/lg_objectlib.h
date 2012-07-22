/*******************************************************************************
* File:		lg_objectlib.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:     1 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_OBJECTLIB_H
#define LG_OBJECTLIB_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../lg_datatypes.h"
#include "../lg_print.h"
#include "../lg_buffer_functions.h"
#include "../lg_opengl.h"
#include "lg_object.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <GL/gl.h>

/*******************************************************************************
* Classname:	LGObjectLib
* Function:		This class describes a scene.
*******************************************************************************/
class LGObjectLib {
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LGObjectLib ()
		* Function:		Constructor
		* Pre:			-
		* Post:			Object is created.
		***********************************************************************/
		LGObjectLib ();

		/***********************************************************************
		* Name:			~LGObjectLib ()
		* Function:		Destructor
		* Pre:			-
		* Post:			Object is destroyed.
		***********************************************************************/
		virtual ~LGObjectLib ();

		/***********************************************************************
		* Name:			readFromFile (char* apFilename)
		* Function:		This function reads a file into memory.
		* Pre:			-
		* Post:			File is red into memory.
		***********************************************************************/
		int readFromFile (char* cpFilename);

		/***********************************************************************
		* Name:			initDefaultValues ()
		* Function:		Init objectlib with default values
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
		* Name:			getChunkSize ()
		* Function:		This function calculates the chunk size
		* Pre:			-
		* Post:			Chunk size is returned.
		***********************************************************************/
		int getChunkSize ();

		/***********************************************************************
		* Name:			getChunkHeaderSize ()
		* Function:		This function calculates the chunk header size
		* Pre:			-
		* Post:			Chunk header size is returned.
		***********************************************************************/
		int getChunkHeaderSize ();

		/***********************************************************************
		* Name:			draw (int iFrame)
		* Function:		This function draws the object
		* Pre:			-
		* Post:			Object is drawn
		***********************************************************************/
		int draw (int iFrame);

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		int			iNrOfObjects;	// Number of objects
		LGObject	*opObjects;		// Objects

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End LGObjectLib

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

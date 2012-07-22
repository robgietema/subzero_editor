/*******************************************************************************
* File:		lg_scene.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:     19 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_SCENE_H
#define LG_SCENE_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../lg_datatypes.h"
#include "../lg_print.h"
#include "../lg_buffer_functions.h"
#include "../lg_opengl.h"
#include "lg_objectinstance.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <GL/gl.h>

/*******************************************************************************
* Classname:	LGScene
* Function:		This class describes a scene.
*******************************************************************************/
class LGScene {
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LGScene ()
		* Function:		Constructor
		* Pre:			-
		* Post:			Object is created.
		***********************************************************************/
		LGScene ();

		/***********************************************************************
		* Name:			~LGScene ()
		* Function:		Destructor
		* Pre:			-
		* Post:			Object is destroyed.
		***********************************************************************/
		virtual ~LGScene ();

		/***********************************************************************
		* Name:			readFromFile (char* apFilename)
		* Function:		This function reads a file into memory.
		* Pre:			-
		* Post:			File is red into memory.
		***********************************************************************/
		int readFromFile (char* cpFilename);

		/***********************************************************************
		* Name:			initDefaultValues ()
		* Function:		Init scene with default values
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
		* Name:			loadTexture ()
		* Function:		This function loads a texture
		* Pre:			-
		* Post:			Texture is loaded.
		***********************************************************************/
		int loadTexture ();

		/***********************************************************************
		* Name:			getChunkHeaderSize ()
		* Function:		This function calculates the chunk header size
		* Pre:			-
		* Post:			Chunk header size is returned.
		***********************************************************************/
		int getChunkHeaderSize ();

		/***********************************************************************
		* Name:			draw (int iFrame)
		* Function:		This function draws the scene
		* Pre:			Scene is loaded
		* Post:			Scene is drawn.
		***********************************************************************/
		int draw (int iFrame);

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		int					iNrOfObjects;	// Number of objects
		LGObjectInstance	*opObjects;		// Objects

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End LGScene

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

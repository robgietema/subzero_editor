/*******************************************************************************
* File:		lg_objectinstance.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		1 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_OBJECTINSTANCE_H
#define LG_OBJECTINSTANCE_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../lg_datatypes.h"
#include "../lg_print.h"
#include "../lg_buffer_functions.h"
#include <stdio.h>
#include <string.h>

/*******************************************************************************
* Classname:	LGObjectInstance
* Function:		This class describes an object.
*******************************************************************************/
class LGObjectInstance {
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LGObjectInstance ()
		* Function:		Constructor
		* Pre:			-
		* Post:			Object is created.
		***********************************************************************/
		LGObjectInstance ();

		/***********************************************************************
		* Name:			~LGObjectInstance ()
		* Function:		Destructor
		* Pre:			-
		* Post:			Object is destroyed.
		***********************************************************************/
		virtual ~LGObjectInstance ();

		/***********************************************************************
		* Name:			initDefaultValues (vOffset, iTime)
		* Function:		Init scene with default values
		* Pre:			-
		* Post:			Scene has default values
		***********************************************************************/
		int initDefaultValues (LGVertex3f vOffset, int iTime);

		/***********************************************************************
		* Name:			readFromFile (char* apFilename)
		* Function:		This function reads an file into memory.
		* Pre:			-
		* Post:			File is red into memory.
		***********************************************************************/
		int readFromFile (char* cpFilename);

		/***********************************************************************
		* Name:			read (byte* bpData)
		* Function:		This function reads data into memory.
		* Pre:			-
		* Post:			Data is red into memory.
		***********************************************************************/
		int read (byte* bpData, int iDataSize);

		/***********************************************************************
		* Name:			writeToFile (char* cpFilename)
		* Function:		This function writes an object to a file.
		* Pre:			Object is written into memory.
		* Post:			File is written.
		***********************************************************************/
		int writeToFile (char* cpFilename);

		/***********************************************************************
		* Name:			write (FILE* fpFile)
		* Function:		This function writes an object to a filepointer.
		* Pre:			Object is written into memory.
		* Post:			Data is written.
		***********************************************************************/
		int write (FILE* fpFile);

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
		* Pre:			Object is loaded
		* Post:			Object is drawn.
		***********************************************************************/
		int draw (int iFrame);

		/***********************************************************************
		* Name:			drawStatic ()
		* Function:		This function draws the static object
		* Pre:			Object is loaded
		* Post:			Object is drawn.
		***********************************************************************/
		int drawStatic ();

		/***********************************************************************
		* Name:			getOffset ()
		* Function:		This function returns the offset of the object
		* Pre:			Object is loaded
		* Post:			Offset is returned.
		***********************************************************************/
		LGVertex3f getOffset ();

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		int				iTime;			// Time of animation start
		LGVertex3f		vOffset;		// Offset of the object
		int				iObject;		// Object index

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////

}; // End LGObjectInstance

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* File:		lg_object.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		19 November 2003
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
#include "../lg_buffer_functions.h"
#include "lg_objectgroup.h"
#include <stdio.h>
#include <string.h>

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
		* Name:			initDefaultValues ()
		* Function:		Init scene with default values
		* Pre:			-
		* Post:			Scene has default values
		***********************************************************************/
		int initDefaultValues ();

		/***********************************************************************
		* Name:			calcAnimStart ()
		* Function:		Calc anim start values
		* Pre:			-
		* Post:			Object has anim start values
		***********************************************************************/
		int calcAnimStart ();

		/***********************************************************************
		* Name:			calcAnimStart (int iObjectGroup, int iBrick)
		* Function:		Calc anim start values
		* Pre:			-
		* Post:			Object has anim start values
		***********************************************************************/
		int calcAnimStart (int iObjectGroup, int iBrick);

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
		* Name:			getAnimLength ()
		* Function:		This function returns the animation length
		* Pre:			Object is loaded
		* Post:			Animation length is returned.
		***********************************************************************/
		int getAnimLength ();

		/***********************************************************************
		* Name:			getNrOfBricks ()
		* Function:		This function gets the number of bricks in the object
		* Pre:			-
		* Post:			Number of bricks is returned
		***********************************************************************/
		int getNrOfBricks ();

		/***********************************************************************
		* Name:			deleteObjectGroup (int iIndex)
		* Function:		This function removes an objectgroup
		* Pre:			-
		* Post:			Objectgroup is deleted
		***********************************************************************/
		int deleteObjectGroup (int iIndex);

		/***********************************************************************
		* Name:			addObjectGroup (char acName[16])
		* Function:		This function adds an objectgroup
		* Pre:			-
		* Post:			Objectgroup is added
		***********************************************************************/
		int addObjectGroup (char acName[16]);

		/***********************************************************************
		* Name:			cloneObjectGroup (int iObjectGroup)
		* Function:		This function clones an objectgroup
		* Pre:			-
		* Post:			Objectgroup is cloned
		***********************************************************************/
		int cloneObjectGroup (int iObjectGroup);

		/***********************************************************************
		* Name:			createNew ()
		* Function:		This function creates a new empty object
		* Pre:			-
		* Post:			Object is created
		***********************************************************************/
		int createNew ();

		/***********************************************************************
		* Name:			replaceColor (int iOld, int iNew)
		* Function:		This function replaces a color
		* Pre:			-
		* Post:			Color is replaced
		***********************************************************************/
		int replaceColor (int iOld, int iNew);

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		int				iNrOfObjectGroups;			// Number of objectgroups
		int				iFramesPerBrick;			// Time of animation start
		int				iFramesBetweenBricks;		// Time of animation start
		char			acName[16];					// Name
		int				iAnimType;					// Anim type
		LGVertex3f		vBrickPositionAnim;			// Brick position from anim start
		LGVertex3f		vBrickOffsetAnim;			// Brick offset from anim start
		LGVertex3f		vBrickRotationAnim;			// Brick rotate diff from anim start
		LGObjectGroup	*gpObjectGroups;			// Objectgroups
		int				iAnimLength;				// Anim length

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

/*******************************************************************************
* File:		lg_bricklib.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		20 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_BRICKLIB_H
#define LG_BRICKLIB_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../lg_datatypes.h"
#include "../lg_print.h"
#include "../lg_buffer_functions.h"
#include "lg_bricklibentry.h"
#include <stdio.h>
#include <string.h>

/*******************************************************************************
* Classname:	LGBrickLib
* Function:		This class describes an bricklib.
*******************************************************************************/
class LGBrickLib {
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LGBrickLib ()
		* Function:		Constructor
		* Pre:			-
		* Post:			Object is created.
		***********************************************************************/
		LGBrickLib ();

		/***********************************************************************
		* Name:			~LGBrickLib ()
		* Function:		Destructor
		* Pre:			-
		* Post:			Object is destroyed.
		***********************************************************************/
		virtual ~LGBrickLib ();

		/***********************************************************************
		* Name:			readFromFile (char* apFilename)
		* Function:		This function reads an file into memory.
		* Pre:			-
		* Post:			File is red into memory.
		***********************************************************************/
		int readFromFile (char* cpFilename);

		/***********************************************************************
		* Name:			writeToFile (char* cpFilename)
		* Function:		This function writes an bricklib to a file.
		* Pre:			Bricklib is written into memory.
		* Post:			File is written.
		***********************************************************************/
		int writeToFile (char* cpFilename);

		/***********************************************************************
		* Name:			draw (int iEntry, int iColor)
		* Function:		Draw bricklibentry
		* Pre:			-
		* Post:			Bricklibentry is drawn
		***********************************************************************/
		int draw (int iEntry, int iColor);

		/***********************************************************************
		* Name:			getChunkSize ()
		* Function:		This function calculates the chunk size
		* Pre:			-
		* Post:			Chunk size is returned.
		***********************************************************************/
		int getChunkSize ();

		/***********************************************************************
		* Name:			initDefaultValues ()
		* Function:		Init bricklib with default values
		* Pre:			-
		* Post:			Bricklib has default values
		***********************************************************************/
		int initDefaultValues ();

		/***********************************************************************
		* Name:			getChunkHeaderSize ()
		* Function:		This function calculates the chunk header size
		* Pre:			-
		* Post:			Chunk header size is returned.
		***********************************************************************/
		int getChunkHeaderSize ();

		/***********************************************************************
		* Name:			getBlockIndex (int iBlockNumber)
		* Function:		This function returns the block index of the given
		*               block number.
		* Pre:			Bricklib is written
		* Post:			Blocknumber is red.
		***********************************************************************/
		int getBlockIndex (int iBlockNumber);

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		int				iNrOfEntries;		// Number of objectgroups
		LGBrickLibEntry	*epBricks;			// Objectgroups

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End LGBrickLib

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

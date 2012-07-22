/*******************************************************************************
* File:		lg_brick.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		19 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_BRICK_H
#define LG_BRICK_H
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
* Classname:	LGBrick
* Function:		This class describes an brick.
*******************************************************************************/
class LGBrick {
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LGBrick ()
		* Function:		Constructor
		* Pre:			-
		* Post:			Object is created.
		***********************************************************************/
		LGBrick ();

		/***********************************************************************
		* Name:			~LGBrick ()
		* Function:		Destructor
		* Pre:			-
		* Post:			Object is destroyed.
		***********************************************************************/
		virtual ~LGBrick ();

		/***********************************************************************
		* Name:			initDefaultValues (int iX, int iY, int iZ, int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim)
		* Function:		Init scene with default values
		* Pre:			-
		* Post:			Scene has default values
		***********************************************************************/
		int initDefaultValues (int iX, int iY, int iZ, int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim);

		/***********************************************************************
		* Name:			createNew (int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim)
		* Function:		Create new object
		* Pre:			-
		* Post:			Object is created
		***********************************************************************/
		int createNew (int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim);

		/***********************************************************************
		* Name:			calcAnimStart (int iAnimType, LGVertex3f vGroupOffset, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim)
		* Function:		Calc anim start values
		* Pre:			Object is loaded
		* Post:			Anim start values are calculated
		***********************************************************************/
		int calcAnimStart (int iAnimType, LGVertex3f vGroupOffset, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim);

		/***********************************************************************
		* Name:			read (byte* bpData, int iDataSize, int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim)
		* Function:		This function reads data into memory.
		* Pre:			-
		* Post:			Data is red into memory.
		***********************************************************************/
		int read (byte* bpData, int iDataSize, int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim);

		/***********************************************************************
		* Name:			write (FILE* fpFile)
		* Function:		This function writes an brick to a filepointer.
		* Pre:			Brick is written into memory.
		* Post:			Data is written.
		***********************************************************************/
		int write (FILE* fpFile);

		/***********************************************************************
		* Name:			draw (int iTime, int iFramesPerBrick, int iAnimType, LGVertex3f vGroupOffset);
		* Function:		This function draws the brick.
		* Pre:			Brick is written into memory.
		* Post:			Brick is drawn.
		***********************************************************************/
		int draw (int iTime, int iFramesPerBrick, int iAnimType, LGVertex3f vGroupOffset);

		/***********************************************************************
		* Name:			getChunkHeaderSize ()
		* Function:		This function calculates the chunk header size
		* Pre:			-
		* Post:			Chunk header size is returned.
		***********************************************************************/
		int getChunkHeaderSize ();

		/***********************************************************************
		* Name:			getChunkSize ()
		* Function:		This function calculates the chunk size
		* Pre:			-
		* Post:			Chunk size is returned.
		***********************************************************************/
		int getChunkSize ();

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		int			iType;			// Type of brick
		int			iBlockNumber;	// Block number
		LGVertex3i	vPos;			// Position
		LGVertex3f	vAnimOffset;	// Offset with anim start
		LGVertex3f	vAnimRotate;	// Rotate diff with anim start
		LGVertex3f	vRotate;		// Rotate
		LGVertex3f	vOffset;		// Translation offset
		int			iColor;			// Color of brick
		bool		bSelected;		// Brick selected
		float		fFloor;			// Floor

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End LGBrick

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

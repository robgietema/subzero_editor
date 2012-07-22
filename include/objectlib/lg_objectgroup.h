/*******************************************************************************
* File:		lg_objectgroup.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		19 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_OBJECTGROUP_H
#define LG_OBJECTGROUP_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../lg_datatypes.h"
#include "../lg_print.h"
#include "../lg_buffer_functions.h"
#include "lg_brick.h"
#include <stdio.h>
#include <string.h>

/*******************************************************************************
* Classname:	LGObjectGroup
* Function:		This class describes an objectgroup.
*******************************************************************************/
class LGObjectGroup {
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LGObjectGroup ()
		* Function:		Constructor
		* Pre:			-
		* Post:			Object is created.
		***********************************************************************/
		LGObjectGroup ();

		/***********************************************************************
		* Name:			~LGObjectGroup ()
		* Function:		Destructor
		* Pre:			-
		* Post:			Object is destroyed.
		***********************************************************************/
		virtual ~LGObjectGroup ();

		/***********************************************************************
		* Name:			initDefaultValues (int iZ, int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim)
		* Function:		Init scene with default values
		* Pre:			-
		* Post:			Scene has default values
		***********************************************************************/
		int initDefaultValues (int iZ, int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim);

		/***********************************************************************
		* Name:			calcAnimStart (int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim)
		* Function:		Calc anim start values
		* Pre:			-
		* Post:			Anim start values are calculated
		***********************************************************************/
		int calcAnimStart (int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim);

		/***********************************************************************
		* Name:			read (byte* bpData, int iDataSize, int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim)
		* Function:		This function reads data into memory.
		* Pre:			-
		* Post:			Data is red into memory.
		***********************************************************************/
		int read (byte* bpData, int iDataSize, int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim);

		/***********************************************************************
		* Name:			write (FILE* fpFile)
		* Function:		This function writes an objectgroup to a filepointer.
		* Pre:			Objectgroup is written into memory.
		* Post:			Data is written.
		***********************************************************************/
		int write (FILE* fpFile);

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

		/***********************************************************************
		* Name:			draw (int iFrame, int iFramesPerBrick, int iFramesBetweenBricks)
		* Function:		This function draws the objectgroup
		* Pre:			Object group is loaded
		* Post:			Objectgroup is drawn.
		***********************************************************************/
		int draw (int iFrame, int iFramesPerBrick, int iFramesBetweenBricks, int iAnimType);

		/***********************************************************************
		* Name:			drawStatic ()
		* Function:		This function draws the objectgroup with a static model
		* Pre:			Object group is loaded
		* Post:			Objectgroup is drawn.
		***********************************************************************/
		int drawStatic ();

		/***********************************************************************
		* Name:			deleteBrick (iBrick)
		* Function:		This function deletes a brick from the group
		* Pre:			Object group is loaded
		* Post:			Brick is deleted.
		***********************************************************************/
		int deleteBrick (int iBrick);

		/***********************************************************************
		* Name:			insertBrick (iBrick)
		* Function:		This function inserts a brick into the group
		* Pre:			Object group is loaded
		* Post:			Brick is inserted.
		***********************************************************************/
		int insertBrick (int iBrick);

		/***********************************************************************
		* Name:			addBrick (LGBrick bBrick)
		* Function:		This function adds a brick into the group
		* Pre:			Object group is loaded
		* Post:			Brick is added.
		***********************************************************************/
		int addBrick (LGBrick bBrick);

		/***********************************************************************
		* Name:			createNew (int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim)
		* Function:		This function creates a new empty object
		* Pre:			-
		* Post:			Object is created
		***********************************************************************/
		int createNew (int iAnimType, LGVertex3f vBrickPositionAnim, LGVertex3f vBrickOffsetAnim, LGVertex3f vBrickRotationAnim);

		/***********************************************************************
		* Name:			sort ()
		* Function:		This function sorts the bricks in this group
		* Pre:			-
		* Post:			Group is sorted
		***********************************************************************/
		int sort ();

		/***********************************************************************
		* Name:			swapBricks (int iItem1, int iItem2)
		* Function:		This function the 2 given bricks
		* Pre:			-
		* Post:			Bricks are swapped
		***********************************************************************/
		int swapBricks (int iItem1, int iItem2);

		////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		int			iNrOfBricks;	// Number of bricks
		int			iTime;			// Time of animation start
		char		acName[16];		// Group name
		LGVertex3f	vRotate;		// Rotate
		LGVertex3f	vOffset;		// Translation offset
		LGVertex3f	vRotationPoint;	// Rotation point
		LGBrick		*bpBricks;		// Bricks
		bool		bHide;			// Hide/show

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End LGObjectGroup

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

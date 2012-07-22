/*******************************************************************************
* File:		lg_object.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		5 February 2005
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/level/lg_object.h"
#include "../../include/level/lg_level.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* LGObject::LGObject
*******************************************************************************/
LGObject::LGObject () {

	// Init values
	LGObject::bSelected = false;
}

/*******************************************************************************
* LGObject::~LGObject
*******************************************************************************/
LGObject::~LGObject () {
}

/*******************************************************************************
* LGObject::initDefaultValues
*******************************************************************************/
int LGObject::initDefaultValues (float fX1, float fY1, float fZ1, float fX2, float fY2, float fZ2, int iTexture) {

	// Set values
	LGObject::iTexture = iTexture;
	LGObject::iType = 0;
	LGObject::iSubType = 0;
	LGObject::fHeight = 3.0f;
	LGObject::fWidth = 3.0f;
	LGObject::iEnemy = 0;
	LGObject::iItem = 0;
	LGObject::iCritter = 0;
	LGObject::vVert1.fX = fX1;
	LGObject::vVert1.fY = fY1;
	LGObject::vVert1.fZ = fZ1;
	LGObject::vVert2.fX = fX2;
	LGObject::vVert2.fY = fY2;
	LGObject::vVert2.fZ = fZ2;

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::write
*******************************************************************************/
int LGObject::write (FILE* fpFile, float fMinX, float fMinY, float fMinZ) {
	if (iType == 0) {
		PrintBoolInt5 (fpFile, false, LGObject::iTexture);
		PrintFloat (fpFile, LGObject::fHeight);
		PrintFloat (fpFile, LGObject::vVert1.fX - fMinX);
		PrintFloat (fpFile, LGObject::vVert1.fY - fMinY);
		PrintFloat (fpFile, LGObject::vVert1.fZ - fMinZ);
		PrintFloat (fpFile, LGObject::vVert2.fX - fMinX);
		PrintFloat (fpFile, LGObject::vVert2.fY - fMinY);
		PrintFloat (fpFile, LGObject::vVert2.fZ - fMinZ);
	} else {
		switch (LGObject::iSubType) {
			case 0:
				PrintBoolInt5 (fpFile, true, LGObject::iEnemy);
				break;
			case 2:
				PrintBoolInt5 (fpFile, true, LGObject::iItem);
				break;
			case 3:
				PrintBoolInt5 (fpFile, true, LGObject::iCritter);
				break;
		}
		PrintInt2Float10 (fpFile, LGObject::iSubType, LGObject::fWidth);
		PrintFloat (fpFile, LGObject::fHeight);
		PrintFloat (fpFile, LGObject::vVert1.fX - fMinX);
		PrintFloat (fpFile, LGObject::vVert1.fY - fMinY);
		PrintFloat (fpFile, LGObject::vVert1.fZ - fMinZ);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObject::draw
*******************************************************************************/
int LGObject::draw () {
	extern GLuint atWalls[];
	extern GLuint atItems[];
	extern GLuint atEnemies[];
	extern GLuint atCritters[];
	extern GLuint atToolbar[];
	extern LGLevel *lLevel;
	extern DWORD dGlobalTicks;	// Ticks
	extern int iSelectedTool;

	// Check if selected
	if (((LGObject::bSelected) && (iSelectedTool == 0 || iSelectedTool == 1 || iSelectedTool == 2) && (dGlobalTicks%512 > 255)) || (!LGObject::bSelected) || (iSelectedTool != 0 && iSelectedTool != 1 && iSelectedTool != 2)) {

		switch (LGObject::iType) {

			// Wall
			case 0:
				glBindTexture (GL_TEXTURE_2D, atWalls[LGObject::iTexture]);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 1.0f); glVertex3f (LGObject::vVert1.fX,  LGObject::vVert1.fY + LGObject::fHeight,	LGObject::vVert1.fZ);
					glTexCoord2f(0.0f, 0.0f); glVertex3f (LGObject::vVert1.fX,  LGObject::vVert1.fY,						LGObject::vVert1.fZ);
					glTexCoord2f(1.0f, 0.0f); glVertex3f (LGObject::vVert2.fX,  LGObject::vVert2.fY,						LGObject::vVert2.fZ);
					glTexCoord2f(1.0f, 1.0f); glVertex3f (LGObject::vVert2.fX,  LGObject::vVert2.fY + LGObject::fHeight,	LGObject::vVert2.fZ);
				glEnd();
				break;

			// Sprite
			case 1:

				switch (LGObject::iSubType) {

					// Enemy
					case 0:
						glBindTexture (GL_TEXTURE_2D, atEnemies[LGObject::iEnemy]);
						glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 1.0f); glVertex3f (LGObject::vVert1.fX - LGObject::fWidth/2,  LGObject::vVert1.fY + LGObject::fHeight,	LGObject::vVert1.fZ);
							glTexCoord2f(0.0f, 0.0f); glVertex3f (LGObject::vVert1.fX - LGObject::fWidth/2,  LGObject::vVert1.fY,						LGObject::vVert1.fZ);
							glTexCoord2f(1.0f, 0.0f); glVertex3f (LGObject::vVert1.fX + LGObject::fWidth/2,  LGObject::vVert1.fY,						LGObject::vVert1.fZ);
							glTexCoord2f(1.0f, 1.0f); glVertex3f (LGObject::vVert1.fX + LGObject::fWidth/2,  LGObject::vVert1.fY + LGObject::fHeight,	LGObject::vVert1.fZ);
						glEnd();
						break;

					// Item
					case 2:
						glBindTexture (GL_TEXTURE_2D, atItems[LGObject::iItem]);
						glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 1.0f); glVertex3f (LGObject::vVert1.fX - LGObject::fWidth/2,  LGObject::vVert1.fY + LGObject::fHeight,	LGObject::vVert1.fZ);
							glTexCoord2f(0.0f, 0.0f); glVertex3f (LGObject::vVert1.fX - LGObject::fWidth/2,  LGObject::vVert1.fY,						LGObject::vVert1.fZ);
							glTexCoord2f(1.0f, 0.0f); glVertex3f (LGObject::vVert1.fX + LGObject::fWidth/2,  LGObject::vVert1.fY,						LGObject::vVert1.fZ);
							glTexCoord2f(1.0f, 1.0f); glVertex3f (LGObject::vVert1.fX + LGObject::fWidth/2,  LGObject::vVert1.fY + LGObject::fHeight,	LGObject::vVert1.fZ);
						glEnd();
						break;

					// Critter
					case 3:
						glBindTexture (GL_TEXTURE_2D, atCritters[LGObject::iCritter]);
						glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 1.0f); glVertex3f (LGObject::vVert1.fX - LGObject::fWidth/2,  LGObject::vVert1.fY + LGObject::fHeight,	LGObject::vVert1.fZ);
							glTexCoord2f(0.0f, 0.0f); glVertex3f (LGObject::vVert1.fX - LGObject::fWidth/2,  LGObject::vVert1.fY,						LGObject::vVert1.fZ);
							glTexCoord2f(1.0f, 0.0f); glVertex3f (LGObject::vVert1.fX + LGObject::fWidth/2,  LGObject::vVert1.fY,						LGObject::vVert1.fZ);
							glTexCoord2f(1.0f, 1.0f); glVertex3f (LGObject::vVert1.fX + LGObject::fWidth/2,  LGObject::vVert1.fY + LGObject::fHeight,	LGObject::vVert1.fZ);
						glEnd();
						break;
				}
				break;
		}
	}

	// Check if selected
	if (((LGObject::bSelected) && (iSelectedTool == 0) && (dGlobalTicks%512 > 255)) || (!LGObject::bSelected) || (iSelectedTool != 0)) {

		glPushMatrix ();

		glTranslatef (LGObject::vVert1.fX, LGObject::vVert1.fY, LGObject::vVert1.fZ);

		// Bind texture
		glBindTexture(GL_TEXTURE_2D, atToolbar[17]);

		glBegin (GL_QUADS);
			// Front
			glVertex3f ( 0.1f,  0.1f, -0.1f);
			glVertex3f ( 0.1f, -0.1f, -0.1f);
			glVertex3f (-0.1f, -0.1f, -0.1f);
			glVertex3f (-0.1f,  0.1f, -0.1f);

			// Back
			glVertex3f (-0.1f,  0.1f, 0.1f);
			glVertex3f (-0.1f, -0.1f, 0.1f);
			glVertex3f ( 0.1f, -0.1f, 0.1f);
			glVertex3f ( 0.1f,  0.1f, 0.1f);

			// Left
			glVertex3f (-0.1f,  0.1f, -0.1f);
			glVertex3f (-0.1f, -0.1f, -0.1f);
			glVertex3f (-0.1f, -0.1f,  0.1f);
			glVertex3f (-0.1f,  0.1f,  0.1f);

			// Right
			glVertex3f ( 0.1f,  0.1f,  0.1f);
			glVertex3f ( 0.1f, -0.1f,  0.1f);
			glVertex3f ( 0.1f, -0.1f, -0.1f);
			glVertex3f ( 0.1f,  0.1f, -0.1f);

			// Top
			glVertex3f (-0.1f,  0.1f, -0.1f);
			glVertex3f (-0.1f,  0.1f,  0.1f);
			glVertex3f ( 0.1f,  0.1f,  0.1f);
			glVertex3f ( 0.1f,  0.1f, -0.1f);

			// Bottom
			glVertex3f ( 0.1f, -0.1f, -0.1f);
			glVertex3f ( 0.1f, -0.1f,  0.1f);
			glVertex3f (-0.1f, -0.1f,  0.1f);
			glVertex3f (-0.1f, -0.1f, -0.1f);
		glEnd ();

		glPopMatrix ();
	}

	// Check if selected
	if ((((LGObject::bSelected) && (iSelectedTool == 1) && (dGlobalTicks%512 > 255)) || (!LGObject::bSelected) || (iSelectedTool != 1)) && (LGObject::iType == 0)) {

		glPushMatrix ();

		glTranslatef (LGObject::vVert2.fX, LGObject::vVert2.fY, LGObject::vVert2.fZ);

		// Bind texture
		glBindTexture(GL_TEXTURE_2D, atToolbar[17]);

		glBegin (GL_QUADS);
			// Front
			glVertex3f ( 0.1f,  0.1f, -0.1f);
			glVertex3f ( 0.1f, -0.1f, -0.1f);
			glVertex3f (-0.1f, -0.1f, -0.1f);
			glVertex3f (-0.1f,  0.1f, -0.1f);

			// Back
			glVertex3f (-0.1f,  0.1f, 0.1f);
			glVertex3f (-0.1f, -0.1f, 0.1f);
			glVertex3f ( 0.1f, -0.1f, 0.1f);
			glVertex3f ( 0.1f,  0.1f, 0.1f);

			// Left
			glVertex3f (-0.1f,  0.1f, -0.1f);
			glVertex3f (-0.1f, -0.1f, -0.1f);
			glVertex3f (-0.1f, -0.1f,  0.1f);
			glVertex3f (-0.1f,  0.1f,  0.1f);

			// Right
			glVertex3f ( 0.1f,  0.1f,  0.1f);
			glVertex3f ( 0.1f, -0.1f,  0.1f);
			glVertex3f ( 0.1f, -0.1f, -0.1f);
			glVertex3f ( 0.1f,  0.1f, -0.1f);

			// Top
			glVertex3f (-0.1f,  0.1f, -0.1f);
			glVertex3f (-0.1f,  0.1f,  0.1f);
			glVertex3f ( 0.1f,  0.1f,  0.1f);
			glVertex3f ( 0.1f,  0.1f, -0.1f);

			// Bottom
			glVertex3f ( 0.1f, -0.1f, -0.1f);
			glVertex3f ( 0.1f, -0.1f,  0.1f);
			glVertex3f (-0.1f, -0.1f,  0.1f);
			glVertex3f (-0.1f, -0.1f, -0.1f);
		glEnd ();

		glPopMatrix ();
	}

	// Return on error
	return (0);
}

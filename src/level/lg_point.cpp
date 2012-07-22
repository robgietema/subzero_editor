/*******************************************************************************
* File:		lg_point.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		5 February 2005
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/level/lg_point.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* LGPoint::LGPiont
*******************************************************************************/
LGPoint::LGPoint () {

	// Init values
	LGPoint::bSelected = false;
}

/*******************************************************************************
* LGPoint::~LGPoint
*******************************************************************************/
LGPoint::~LGPoint () {
}

/*******************************************************************************
* LGPoint::initDefaultValues
*******************************************************************************/
int LGPoint::initDefaultValues (float fX, float fY, float fZ) {

	// Print status
	VerbosePrintf ("Init brick with coordinates: %f, %f, %f", fX, fY, fZ);

	// Set values
	LGPoint::vPos.fX = fX;
	LGPoint::vPos.fY = fY;
	LGPoint::vPos.fZ = fZ;

	// Return no error
	return (0);
}

/*******************************************************************************
* LGPoint::draw
*******************************************************************************/
int LGPoint::draw () {
	extern DWORD		dGlobalTicks;	// Ticks
	extern GLuint atToolbar[32];		// Toolbar textures
	extern int iSelectedTool;

	// Check if selected
	if (((LGPoint::bSelected) && ((iSelectedTool == 0) || (iSelectedTool == 3)) && (dGlobalTicks%512 > 255)) || (!LGPoint::bSelected) || (iSelectedTool != 0 && iSelectedTool != 3)) {

		glPushMatrix ();

		glTranslatef (LGPoint::vPos.fX, LGPoint::vPos.fY, LGPoint::vPos.fZ);

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


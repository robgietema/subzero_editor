/*******************************************************************************
* File:		lg_font2d.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		19 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../include/lg_font2d.h"
#include "../include/lg_opengl.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* LGFont2d::LGFont2d
*******************************************************************************/
LGFont2d::LGFont2d () {
}

/*******************************************************************************
* LGFont2d::~LGFont2d
*******************************************************************************/
LGFont2d::~LGFont2d () {

	// Delete display lists
	glDeleteLists (LGFont2d::dlBase, 256);
}

/*******************************************************************************
* LGFont2d::init
*******************************************************************************/
int LGFont2d::init () {

	// Load texture
	LoadTGA ("data/textures/font.tga", LGFont2d::atTextures[0]);

	// Build font
	LGFont2d::buildFont ();

	// Return no error
	return (0);
}

/*******************************************************************************
* LGFont2d::print
*******************************************************************************/
int LGFont2d::print (GLint iX, GLint iY, char *cpString) {

	// Select texture
	glBindTexture (GL_TEXTURE_2D, LGFont2d::atTextures[0]);
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0,1024,0,768,-1,1);							// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glTranslated(iX,iY,0);								// Position The Text (0,0 - Bottom Left)
	glListBase(LGFont2d::dlBase-32);						// Choose The Font Set (0 or 1)
	glCallLists(strlen(cpString),GL_UNSIGNED_BYTE,cpString);// Write The Text To The Screen
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGFont2d::buildFont
*******************************************************************************/
int LGFont2d::buildFont () {
	float	fX;				// Holds Our X Character Coord
	float	fY;				// Holds Our Y Character Coord

	// Creating 256 display lists
	LGFont2d::dlBase = glGenLists(256);

	// Select our font texture
	glBindTexture(GL_TEXTURE_2D, LGFont2d::atTextures[0]);

	// Loop through all 256 lists
	for (int iCount=0; iCount<256; iCount++) {

		// Get coords
		fX=float(iCount%16)/16.0f;
		fY=float(iCount/16)/16.0f;

		// Start building a list
		glNewList(LGFont2d::dlBase+iCount,GL_COMPILE);
			glBegin(GL_QUADS);
				glTexCoord2f(fX,1-fY-0.0625f);			// Texture Coord (Bottom Left)
				glVertex2i(0,0);						// Vertex Coord (Bottom Left)
				glTexCoord2f(fX+0.0625f,1-fY-0.0625f);	// Texture Coord (Bottom Right)
				glVertex2i(12,0);						// Vertex Coord (Bottom Right)
				glTexCoord2f(fX+0.0625f,1-fY);			// Texture Coord (Top Right)
				glVertex2i(12,12);						// Vertex Coord (Top Right)
				glTexCoord2f(fX,1-fY);					// Texture Coord (Top Left)
				glVertex2i(0,12);						// Vertex Coord (Top Left)
			glEnd();
			glTranslated(7,0,0);
		glEndList();
	}	

	// Return no error
	return (0);
}


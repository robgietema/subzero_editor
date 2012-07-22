/*******************************************************************************
* File:		lg_opengl.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		27 November 2003
* Note:		This code is based on the NeHe OpenGL framework
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_OPENGL_H
#define LG_OPENGL_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../include/lg_print.h"
#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/ARB_MULTISAMPLE.h"

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			IsExtensionSupported (char* cpTargetExtension)
* Function:		Check if extension is supported by hardware
* Pre:			-
* Post:			True is returned if hardware supports extension.
*******************************************************************************/
bool IsExtensionSupported (char* cpTargetExtension);

/*******************************************************************************
* Name:			LoadTGA (char *cpFilename, GLuint &uTextureId)
* Function:		Load TGA
* Pre:			-
* Post:			TGA is loaded.
*******************************************************************************/
int LoadTGA (char *cpFilename, GLuint &uTextureId);

/*******************************************************************************
* Name:			LoadAlphaTGA (char *cpFilename, GLuint &uTextureId, LGColor3f cColor)
* Function:		Load Alpha TGA
* Pre:			-
* Post:			TGA is loaded.
*******************************************************************************/
int LoadAlphaTGA (char *cpFilename, GLuint &uTextureId, LGColor3b cColor);

/*******************************************************************************
* Name:			LoadGrayscaleTGA (char *cpFilename, GLuint &uTextureId, LGColor3f cColor)
* Function:		Load Alpha TGA
* Pre:			-
* Post:			TGA is loaded.
*******************************************************************************/
int LoadGrayscaleTGA (char *cpFilename, GLuint &uTextureId, LGColor3b cColor);

/*******************************************************************************
* Name:			BuildTexture (char *szPathName, GLuint &texid)
* Function:		Build the texture.
* Pre:			-
* Post:			Texture is build.
*******************************************************************************/
int BuildTexture (char *szPathName, GLuint &texid);

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

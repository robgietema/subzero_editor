/*******************************************************************************
* File:		lg_image.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		27 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_IMAGE_H
#define LG_IMAGE_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../include/lg_print.h"
#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			DrawLine (int iWidth, int iHeight, int iBeginX, int iBeginY, int iEndX, int iEndY, byte bSide, float fLineWidth, byte* bpBits)
* Function:		Draw a line in the given image
* Pre:			-
* Post:			Line is drawn
*******************************************************************************/
int DrawLine (int iWidth, int iHeight, int iBeginX, int iBeginY, int iEndX, int iEndY, byte bSide, float fLineWidth, byte* bpBits);

/*******************************************************************************
* Name:			Scale (int iOldWidth, int iOldHeight, int iNewWidth, int iNewHeight, byte* bpOldBits, byte* bpNewBits)
* Function:		Scales a function
* Pre:			-
* Post:			Function is scaled
*******************************************************************************/
int Scale (int iOldWidth, int iOldHeight, int iNewWidth, int iNewHeight, byte* bpOldBits, byte* bpNewBits);

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

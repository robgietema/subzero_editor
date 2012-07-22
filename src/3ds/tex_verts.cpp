/*******************************************************************************
* File:		tex_verts.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/tex_verts.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* TEX_VERTS ()
*******************************************************************************/
TEX_VERTS::TEX_VERTS() {

	// Initialize member variables
	TEX_VERTS::iNrOfTexVerts = 0;
	TEX_VERTS::tTexVerts = NULL;
}

/*******************************************************************************
* ~TEX_VERTS ()
*******************************************************************************/
TEX_VERTS::~TEX_VERTS() {

	// If allocated
	if (TEX_VERTS::tTexVerts) {

		// Delete
		delete []TEX_VERTS::tTexVerts;
	}
}

/*******************************************************************************
* Read3DS ()
*******************************************************************************/
int TEX_VERTS::Read3DS (int iNrOfBytes, byte* bp3DSData) {
	int iCount;					// Counter
	int iTexVertsCount;			// Number of tex verts

	// Print status
	VerbosePrintf ("Begin reading TEX_VERTS chunk");
	
	// Check for zero length
	if (iNrOfBytes < (2 + (2 * 3)))
	{
		// Set error file contains no data
		ErrorPrintf ("File contains no data");

		// Return error
		return (-1);
	}

	// Get pointcount
	iTexVertsCount = GetShort (bp3DSData);

	// Set number of points
	TEX_VERTS::iNrOfTexVerts = iTexVertsCount;

	// Check if > 0
	if (iTexVertsCount > 0) {

		// Allocate point list
		TEX_VERTS::tTexVerts = new TEXVERT_3DS[iTexVertsCount];
	}

	// Print status
	VerbosePrintf ("%d points found", iNrOfBytes / 8);

	// Get points from TEX_VERTS chunk
	for (iCount = 0; iCount < iTexVertsCount; iCount++)
	{
		// Get point		
		TEX_VERTS::tTexVerts[iCount].fU = GetFloat (bp3DSData+2+(iCount*8));
		TEX_VERTS::tTexVerts[iCount].fV = GetFloat (bp3DSData+2+(iCount*8)+4);

		// Print status
		VerbosePrintf ("Texture vertex: (%f,%f)", 
			TEX_VERTS::tTexVerts[iCount].fU, TEX_VERTS::tTexVerts[iCount].fV);
	}

	// Print status
	VerbosePrintf ("End reading TEX_VERTS chunk");

	// Return no error
	return (0);
}

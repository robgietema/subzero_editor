/*******************************************************************************
* File:		file_3ds.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (_FILE_3DS_H)
#define _FILE_3DS_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>			// fopen(); fclose(); fseek(); ftell(); fread(); FILE
#include "../../include/3ds/3ds.h"		// byte
#include "../../include/lg_print.h"
#include "../../include/lg_datatypes.h"
#include "../../include/lg_buffer_functions.h"
#include "../../include/3ds/chunks.h"
#include "../../include/3ds/m3dmagic.h"


////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	FILE_3DS                                                       *
* Function:		This class is used to buffer the inputfile and read this file  *
*               into the datastructure                                         *
*******************************************************************************/
class FILE_3DS
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			FILE_3DS ()
		* Function:		Default constructor
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		FILE_3DS ();


		/***********************************************************************
		* Name:			~FILE_3DS ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~FILE_3DS ();


		/***********************************************************************
		* Name:			read3DS (const char *acFileName)
		* Function:		Reads the 3DS file acFileName into memory.
		* Pre:          The file acFileName exists.
		* Post:         The data of the file acFileName is stored in mM3DMagic.
		***********************************************************************/
		int read3DS (const char *acFileName);

		/***********************************************************************
		* Name:			draw ()
		* Function:		Draws the model to the screen.
		* Pre:          Model is loaded.
		* Post:         Model is drawn.
		***********************************************************************/
		int draw (int iWireframe);
		
		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		M3DMAGIC		mM3DMagic;		// M3DMAGIC chunk (top-level chunk)
		LGVertex3f*		vpVertices;		// Vertices
		LGTextureuv*	tpTextures;		// Texture vertices
		int				iNrOfVertices;	// Number of vertices
		unsigned int	uVBOVertices;	// Vertex VBO Name
		unsigned int	uVBOTexCoords;	// Texture Coordinate VBO Name

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
		
}; // End ERRORMESSAGES

////////////////////////////////////////////////////////////////////////////////
#endif 
////////////////////////////////////////////////////////////////////////////////

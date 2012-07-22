/*******************************************************************************
* File:		lg_font2d.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		1 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_FONT2D_H
#define LG_FONT2D_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "lg_datatypes.h"
#include "lg_print.h"
#include "lg_buffer_functions.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

/*******************************************************************************
* Classname:	LGFont2d
* Function:		This class describes an font2d.
*******************************************************************************/
class LGFont2d {
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LGFont2d ()
		* Function:		Constructor
		* Pre:			-
		* Post:			Object is created.
		***********************************************************************/
		LGFont2d ();

		/***********************************************************************
		* Name:			~LGFont2d ()
		* Function:		Destructor
		* Pre:			-
		* Post:			Object is destroyed.
		***********************************************************************/
		virtual ~LGFont2d ();

		/***********************************************************************
		* Name:			print (GLint iX, GLint Y, char *cpString)
		* Function:		Print a string
		* Pre:			-
		* Post:			String is printed
		***********************************************************************/
		int print (GLint iX, GLint Y, char *cpString);

		/***********************************************************************
		* Name:			buildFont ()
		* Function:		Build the font
		* Pre:			-
		* Post:			Font is build
		***********************************************************************/
		int buildFont ();

		/***********************************************************************
		* Name:			init ()
		* Function:		Init font
		* Pre:			-
		* Post:			Font is inited
		***********************************************************************/
		int init ();

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
		GLuint		dlBase;			// Display list
		GLuint		atTextures[1];	// Textures

}; // End LGFont2d

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
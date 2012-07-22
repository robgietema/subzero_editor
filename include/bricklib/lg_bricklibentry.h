/*******************************************************************************
* File:		lg_bricklibentry.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		20 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_BRICKLIBENTRY_H
#define LG_BRICKLIBENTRY_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../lg_datatypes.h"
#include "../lg_print.h"
#include "../lg_buffer_functions.h"
#include "../lg_opengl.h"
#include "../lg_image.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

/*******************************************************************************
* Classname:	LGBrickLibEntry
* Function:		This class describes an brick lib entry.
*******************************************************************************/
class LGBrickLibEntry {
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			LGBrickLibEntry ()
		* Function:		Constructor
		* Pre:			-
		* Post:			Object is created.
		***********************************************************************/
		LGBrickLibEntry ();

		/***********************************************************************
		* Name:			~LGBrickLibEntry ()
		* Function:		Destructor
		* Pre:			-
		* Post:			Object is destroyed.
		***********************************************************************/
		virtual ~LGBrickLibEntry ();

		/***********************************************************************
		* Name:			read (byte* bpData, int iDataSize)
		* Function:		This function reads data into memory.
		* Pre:			-
		* Post:			Data is red into memory.
		***********************************************************************/
		int read (byte* bpData, int iDataSize);

		/***********************************************************************
		* Name:			readFromFile (char* apFilename)
		* Function:		This function reads an file into memory.
		* Pre:			-
		* Post:			File is red into memory.
		***********************************************************************/
		int readFromFile (char* cpFilename);

		/***********************************************************************
		* Name:			write (FILE* fpFile)
		* Function:		This function writes an brick to a filepointer.
		* Pre:			Brick is written into memory.
		* Post:			Data is written.
		***********************************************************************/
		int write (FILE* fpFile);

		/***********************************************************************
		* Name:			writeToFile (char* cpFilename)
		* Function:		This function writes an brick to a file.
		* Pre:			Brick is written into memory.
		* Post:			File is written.
		***********************************************************************/
		int writeToFile (char* cpFilename);

		/***********************************************************************
		* Name:			initDefaultValues (int iEntry)
		* Function:		Init bricklib with default values
		* Pre:			-
		* Post:			Bricklib has default values
		***********************************************************************/
		int initDefaultValues (int iEntry);

		/***********************************************************************
		* Name:			loadTextures ()
		* Function:		Load textures
		* Pre:			-
		* Post:			Textures are loaded
		***********************************************************************/
		int loadTextures ();

		/***********************************************************************
		* Name:			generateDisplayList ()
		* Function:		Generate displaylist
		* Pre:			-
		* Post:			Displaylist is generated
		***********************************************************************/
		int generateDisplayList ();

		/***********************************************************************
		* Name:			generateVertexArray ()
		* Function:		Generate vertex array
		* Pre:			-
		* Post:			Vertex array is generated
		***********************************************************************/
		int generateVertexArray ();

		/***********************************************************************
		* Name:			setVertex (int iIndex, float fX, float fY, float fZ, float fU, float fV)
		* Function:		Set vertex
		* Pre:			-
		* Post:			Vertex is set
		***********************************************************************/
		int setVertex (int iIndex, float fX, float fY, float fZ, float fU, float fV);

		/***********************************************************************
		* Name:			setVertexNormal (int iIndex, float fU, float fV, float fX, float fY, float fZ, float fNormalX, float fNormalY, float fNormalZ)
		* Function:		Set vertex and normal
		* Pre:			-
		* Post:			Vertex and normal are set
		***********************************************************************/
		int setVertexNormal (int iIndex, float fU, float fV, float fX, float fY, float fZ, float fNormalX, float fNormalY, float fNormalZ);

		/***********************************************************************
		* Name:			setFace (int iIndex, unsigned short sA, unsigned short sB, unsigned short sC)
		* Function:		Set face
		* Pre:			-
		* Post:			Face is set
		***********************************************************************/
		int setFace (int iIndex, unsigned short sA, unsigned short sB, unsigned short sC, unsigned short sD);

		/***********************************************************************
		* Name:			draw (int iColor)
		* Function:		Draw bricklibentry
		* Pre:			-
		* Post:			Bricklibentry is drawn
		***********************************************************************/
		int draw (int iColor);

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
		* Name:			createBrick (int iWidth, int iLength, int iHeight)
		* Function:		This function creates the brick coordinates and faces
		* Pre:			-
		* Post:			Brick coordinates and faces are created
		***********************************************************************/
		int createBrick (int iWidth, int iLength, int iHeight);

		/***********************************************************************
		* Name:			createSlope (int iWidth, int iLength, int iHeight)
		* Function:		This function creates the brick coordinates and faces
		* Pre:			-
		* Post:			Brick coordinates and faces are created
		***********************************************************************/
		int createSlope (int iWidth, int iLength, int iHeight);

		/***********************************************************************
		* Name:			createInvertedSlope (int iWidth, int iLength, int iHeight)
		* Function:		This function creates the brick coordinates and faces
		* Pre:			-
		* Post:			Brick coordinates and faces are created
		***********************************************************************/
		int createInvertedSlope (int iWidth, int iLength, int iHeight);

		/***********************************************************************
		* Name:			createBrickWithoutCorner (int iWidth, int iLength, int iHeight)
		* Function:		This function creates the brick coordinates and faces
		* Pre:			-
		* Post:			Brick coordinates and faces are created
		***********************************************************************/
		int createBrickWithoutCorner (int iWidth, int iLength, int iHeight);

		/***********************************************************************
		* Name:			createBrickWithout2Corners (int iWidth, int iLength, int iHeight)
		* Function:		This function creates the brick coordinates and faces
		* Pre:			-
		* Post:			Brick coordinates and faces are created
		***********************************************************************/
		int createBrickWithout2Corners (int iWidth, int iLength, int iHeight);

		/***********************************************************************
		* Name:			createBrickByNumber (int iNumber)
		* Function:		This function creates the brick coordinates and faces
		* Pre:			-
		* Post:			Brick coordinates and faces are created
		***********************************************************************/
		int createBrickByNumber (int iNumber);

		/***********************************************************************
		* Name:			createBasePlate ()
		* Function:		This function creates a baseplate
		* Pre:			-
		* Post:			Baseplate is created
		***********************************************************************/
		int createBasePlate ();

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		int				iNrOfVerticesElements;
		int				iNrOfVerticesArrays;
		int				iNrOfFaces;
		int				iBlockNumber;
		LGFace4s*		fpFaces;
		LGVertex3f*		vpVerticesElements;
		LGVertex3f*		vpNormalsElements;
		LGTextureuv*	tpTexturesElements;
		LGVertex3f*		vpVerticesArrays;
		LGVertex3f*		vpNormalsArrays;
		LGTextureuv*	tpTexturesArrays;
		GLuint*			aiTextures;
		int				iTextureType;
		GLuint			iDisplayList;
		unsigned int	uVBOVertices;	// Vertex VBO Name
		unsigned int	uVBOTexCoords;	// Texture Coordinate VBO Name

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////

}; // End LGBrickLibEntry

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

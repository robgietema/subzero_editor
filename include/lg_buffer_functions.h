/*******************************************************************************
* File:		lg_buffer_functions.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		19 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_BUFFER_FUNCTIONS_H
#define LG_BUFFER_FUNCTIONS_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "lg_datatypes.h"
#include "lg_print.h"
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			Get3DSChunkID (byte* bpData)
* Function:		This function gets a chunkid from a buffer.
* Pre:			Buffer is allocated.
* Post:			ChunkID is returned.
*******************************************************************************/
int Get3DSChunkID (byte* bpData);

/*******************************************************************************
* Name:			GetInt (byte* bpData)
* Function:		This function gets an integer from a buffer.
* Pre:			Buffer is allocated.
* Post:			Integer is returned.
*******************************************************************************/
int GetInt (byte* bpData);

/*******************************************************************************
* Name:			GetShort (byte* bpData)
* Function:		This function gets a short integer from a buffer.
* Pre:			Buffer is allocated.
* Post:			Integer is returned.
*******************************************************************************/
int GetShort (byte* bpData);

/*******************************************************************************
* Name:			GetFloat (byte* bpData)
* Function:		This function gets a float from a buffer.
* Pre:			Buffer is allocated.
* Post:			Float is returned.
*******************************************************************************/
float GetFloat (byte* bpData);

/*******************************************************************************
* Name:			GetString ()
* Function:		This function gets a string from a buffer.
* Pre:          -
* Post:         String is returned.
*******************************************************************************/
int GetString (byte* cpData, char acString[256]);

/*******************************************************************************
* Name:			GetVertex3i (byte* bpData)
* Function:		This function gets a vertex3i from a buffer.
* Pre:			Buffer is allocated.
* Post:			Vertex3i is returned.
*******************************************************************************/
LGVertex3i GetVertex3i (byte* bpData);

/*******************************************************************************
* Name:			GetVertex3f (byte* bpData)
* Function:		This function gets a vertex3f from a buffer.
* Pre:			Buffer is allocated.
* Post:			Vertex3f is returned.
*******************************************************************************/
LGVertex3f GetVertex3f (byte* bpData);

/*******************************************************************************
* Name:			GetVertex3fuv (byte* bpData)
* Function:		This function gets a vertex3fuv from a buffer.
* Pre:			Buffer is allocated.
* Post:			Vertex3fuv is returned.
*******************************************************************************/
LGVertex3fuv GetVertex3fuv (byte* bpData);

/*******************************************************************************
* Name:			GetColor3f (byte* bpData)
* Function:		This function gets a color3f from a buffer.
* Pre:			Buffer is allocated.
* Post:			Color3f is returned.
*******************************************************************************/
LGColor3f GetColor3f (byte* bpData);

/*******************************************************************************
* Name:			GetTextureuv (byte* bpData)
* Function:		This function gets a textureuv from a buffer.
* Pre:			Buffer is allocated.
* Post:			Textureuv is returned.
*******************************************************************************/
LGTextureuv GetTextureuv (byte* bpData);

/*******************************************************************************
* Name:			GetString (byte* bpData, char* cpString)
* Function:		This function gets a string from a buffer.
* Pre:			Buffer is allocated.
* Post:			String is returned.
*******************************************************************************/
int GetString16 (byte* bpData, char* cpString);

/*******************************************************************************
* Name:			PrintInt (FILE* fpFile, int iInteger)
* Function:		This function prints an integer to a file.
* Pre:			File is opened.
* Post:			Integer is printed to file.
*******************************************************************************/
int PrintInt12 (FILE* fpFile, int iInteger);

int PrintBoolInt5 (FILE* fpFile, bool bType, int iInteger);
int PrintInt2Float10 (FILE* fpFile, int iInteger, float fFloat);

/*******************************************************************************
* Name:			PrintInt16 (FILE* fpFile, int iInteger)
* Function:		This function prints a 16-bits integer to a file.
* Pre:			File is opened.
* Post:			Integer is printed to file.
*******************************************************************************/
int PrintInt16 (FILE* fpFile, int iInteger);

/*******************************************************************************
* Name:			PrintFloat (FILE* fpFile, float fFloat)
* Function:		This function prints a float to a file.
* Pre:			File is opened.
* Post:			Float is printed to file.
*******************************************************************************/
int PrintFloat (FILE* fpFile, float fFloat);

/*******************************************************************************
* Name:			PrintVertex3i (FILE* fpFile, LGVertex3i vVertex)
* Function:		This function prints a vertex3i to a file.
* Pre:			File is opened.
* Post:			Vertex3i is printed to file.
*******************************************************************************/
int PrintVertex3i (FILE* fpFile, LGVertex3i vVertex);

/*******************************************************************************
* Name:			PrintVertex3f (FILE* fpFile, LGVertex3f vVertex)
* Function:		This function prints a vertex3f to a file.
* Pre:			File is opened.
* Post:			Vertex3f is printed to file.
*******************************************************************************/
int PrintVertex3f (FILE* fpFile, LGVertex3f vVertex);

/*******************************************************************************
* Name:			PrintVertex3fuv (FILE* fpFile, LGVertex3fuv vVertex)
* Function:		This function prints a vertex3fuv to a file.
* Pre:			File is opened.
* Post:			Vertex3fuv is printed to file.
*******************************************************************************/
int PrintVertex3fuv (FILE* fpFile, LGVertex3fuv vVertex);

/*******************************************************************************
* Name:			PrintColor3f (FILE* fpFile, LGColor3f vVertex)
* Function:		This function prints a color3f to a file.
* Pre:			File is opened.
* Post:			Color3f is printed to file.
*******************************************************************************/
int PrintColor3f (FILE* fpFile, LGColor3f cColor);

/*******************************************************************************
* Name:			PrintTextureuv (FILE* fpFile, LGTextureuv tTexture)
* Function:		This function prints a textureuv to a file.
* Pre:			File is opened.
* Post:			Textureuv is printed to file.
*******************************************************************************/
int PrintTextureuv (FILE* fpFile, LGTextureuv tTexture);

/*******************************************************************************
* Name:			PrintChunkID (FILE* fpFile, char* cpChunk)
* Function:		This function prints a chunkid to a file.
* Pre:			File is opened.
* Post:			Chunkid is printed to file.
*******************************************************************************/
int PrintChunkID (FILE* fpFile, char* cpChunk);

/*******************************************************************************
* Name:			PrintString (FILE* fpFile, char* cpString)
* Function:		This function prints a string to a file.
* Pre:			File is opened.
* Post:			String is printed to file.
*******************************************************************************/
int PrintString16 (FILE* fpFile, char* cpString);

int PrintHeader (FILE* fpFile, char* cpLevel);

int PrintFooter (FILE* fpFile);

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

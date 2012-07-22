/*******************************************************************************
* File:		file_3ds.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/file_3ds.h"
#include "../../include/lg_math.h"
#include <windows.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../../include/glext.h"
#include "../../include/fmod/fmod.h"					// Header file for audio library
#include "../../include/fmod/fmod_errors.h"			// Header file for audio library errors

////////////////////////////////////////////////////////////////////////////////
// Global variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			FILE_3DS ()
*******************************************************************************/
FILE_3DS::FILE_3DS () {
	FILE_3DS::iNrOfVertices = 0;
	FILE_3DS::tpTextures = NULL;
	FILE_3DS::vpVertices = NULL;
	FILE_3DS::uVBOTexCoords = 0;
	FILE_3DS::uVBOVertices = 0;
}

/*******************************************************************************
* Name:			~FILE_3DS ()
*******************************************************************************/
FILE_3DS::~FILE_3DS () {
	extern bool bVBOSupported;
	extern PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;

	// Check if allocated
	if (FILE_3DS::tpTextures) {

		// Delete
		delete []FILE_3DS::tpTextures;
	}

	// Check if allocated
	if (FILE_3DS::vpVertices) {

		// Delete
		delete []FILE_3DS::vpVertices;
	}

	// Check VBO
	if (bVBOSupported) {

		// Delete arrays
		unsigned int uBuffers[2] = { FILE_3DS::uVBOVertices, FILE_3DS::uVBOTexCoords };
		glDeleteBuffersARB (2, uBuffers);
	}
}

/*******************************************************************************
* draw ()
*******************************************************************************/
int FILE_3DS::draw (int iWireframe) {
	extern FSOUND_STREAM	*sStream;							// Stream pointer
	DWORD dAudioTicks = FSOUND_Stream_GetTime (sStream);
	DWORD dTicks = dAudioTicks;
/*
	extern bool bVBOSupported;
	extern PFNGLGENBUFFERSARBPROC glGenBuffersARB;		// VBO Name Generation Procedure
	extern PFNGLBINDBUFFERARBPROC glBindBufferARB;		// VBO Bind Procedure
	extern PFNGLBUFFERDATAARBPROC glBufferDataARB;		// VBO Data Loading Procedure

	// Enable Pointers
	glEnableClientState( GL_VERTEX_ARRAY );						// Enable Vertex Arrays
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );				// Enable Texture Coord Arrays

	// Set Pointers To Our Data
	if (bVBOSupported) {
		glBindBufferARB (GL_ARRAY_BUFFER_ARB, FILE_3DS::uVBOVertices);
		glVertexPointer (3, GL_FLOAT, 0, (char *) NULL);		// Set The Vertex Pointer To The Vertex Buffer
	} else {
		glVertexPointer (3, GL_FLOAT, 0, FILE_3DS::vpVertices); // Set The Vertex Pointer To Our Vertex Data
	}

	glTexCoordPointer (2, GL_FLOAT, 0, FILE_3DS::tpTextures);
	glDrawArrays (GL_TRIANGLES, 0, FILE_3DS::iNrOfVertices);

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );	
*/

	// Cycle through named objects
	for (int iNamedObject = 0; iNamedObject < FILE_3DS::mM3DMagic.dData.iNrOfNamedObjects;iNamedObject++) {

		// Cycle through tri objects
		for (int iTriObject = 0; iTriObject < FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].iNrOfNTriObjects; iTriObject++) {

			// Get points/faces
			POINT_3DS*	pPoints = FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].oNTriObject[iTriObject].pPointArray.pPoints;
			FACE_3DS*	fFaces  = FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].oNTriObject[iTriObject].fFaceArray.fFaces;
			MSH_MAT_GROUP*	mMshMatGroups = FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].oNTriObject[iTriObject].fFaceArray.mMshMatGroups;
			TEXVERT_3DS*	tTexVerts = FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].oNTriObject[iTriObject].tTexVerts.tTexVerts;


			// Cylce through matgroups
			for (int iMatGroup = 0; iMatGroup < FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].oNTriObject[iTriObject].fFaceArray.iNrOfMshMatGroups; iMatGroup++) {

				int iTexture = 0;
				for (int iMaterial = 0; iMaterial < FILE_3DS::mM3DMagic.dData.iNrOfMatEntries; iMaterial++) {
					if (strcmp (mMshMatGroups[iMatGroup].acName, FILE_3DS::mM3DMagic.dData.eMatEntry[iMaterial].nMatName.acName) == 0) {
						iTexture = iMaterial;
					}
				}

//				glBindTexture (GL_TEXTURE_2D, FILE_3DS::mM3DMagic.dData.eMatEntry[iTexture].tMatTex1Map.iTexture);

//				VerbosePrintf ("Draw | %d %d %d %d", iNamedObject, iTriObject, iMatGroup, FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].oNTriObject[iTriObject].fFaceArray.mMshMatGroups[iMatGroup].iNrOfFaces);

				// Cylce through faces
				for (int iFace = 0; iFace < FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].oNTriObject[iTriObject].fFaceArray.mMshMatGroups[iMatGroup].iNrOfFaces; iFace++) {
//					VerbosePrintf ("Face: %d %f", iFace, pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iC].fZ);

					if ((iWireframe == 1) && ((pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iA].fX + pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iB].fX + pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iC].fX) / 3.0f > sin(dTicks % 4500 / 4500.0f * LG_2PI) * 150)) {
						glBegin(GL_LINE_STRIP);
					} else if ((iWireframe == 2) && ((pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iA].fX + pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iB].fX + pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iC].fX) / 3.0f > sin(dTicks % 4500 / 4500.0f * LG_2PI) * 150)) {
						glBegin(GL_POINTS);
					} else if (iWireframe == 3) {
						glBegin(GL_LINE_STRIP);
					} else if (iWireframe == 4) {
						glBegin(GL_POINTS);
					} else {
						glBegin(GL_TRIANGLES);
					}
						if (FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].oNTriObject[iTriObject].tTexVerts.iNrOfTexVerts > 0) {
							glTexCoord2d (tTexVerts[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iA].fU,tTexVerts[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iA].fV);
							glVertex3f (pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iA].fX,pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iA].fY,pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iA].fZ);

							glTexCoord2d (tTexVerts[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iB].fU,tTexVerts[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iB].fV);
							glVertex3f (pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iB].fX,pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iB].fY,pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iB].fZ);

							glTexCoord2d (tTexVerts[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iC].fU,tTexVerts[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iC].fV);
							glVertex3f (pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iC].fX,pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iC].fY,pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iC].fZ);
						} else {
							glTexCoord2d (0,0);
							glVertex3f (pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iA].fX,pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iA].fY,pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iA].fZ);

							glTexCoord2d (1,0);
							glVertex3f (pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iB].fX,pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iB].fY,pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iB].fZ);

							glTexCoord2d (0,1);
							glVertex3f (pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iC].fX,pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iC].fY,pPoints[fFaces[mMshMatGroups[iMatGroup].iFaces[iFace]].iC].fZ);
						}
					glEnd();
				}
			}
		}
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* read3DS ()
*******************************************************************************/
int FILE_3DS::read3DS (const char *acFileName) {
	FILE *fp3DSFile = NULL;		// Pointer 
	byte *bpFileBuffer = NULL;	// Buffer for file.
	long lFileSize = 0;			// Size of 3ds file
	int iItemsRead = 0;			// Items read
	int iCurrentByte = 0;		// Pointer to current byte in chunk
	int iChunkID;				// Chunk id
	long lChunkLength;			// Chunk length
	extern bool bVBOSupported;	// VBO supported
	extern PFNGLGENBUFFERSARBPROC glGenBuffersARB;		// VBO Name Generation Procedure
	extern PFNGLBINDBUFFERARBPROC glBindBufferARB;		// VBO Bind Procedure
	extern PFNGLBUFFERDATAARBPROC glBufferDataARB;		// VBO Data Loading Procedure

	// Print status
	VerbosePrintf ("Begin buffering 3DS file");

	// Open file
	fp3DSFile = fopen (acFileName, "rb");
	
	// Check for error
	if (fp3DSFile == NULL)
	{
		// Error opening 3DS file
		ErrorPrintf ("Error opening file");
		
		return (-1);
	}	
	
	// Get filesize
	fseek (fp3DSFile, 0L, SEEK_END);
	lFileSize = ftell (fp3DSFile);
	fseek (fp3DSFile, 0L, SEEK_SET);
	
	// Print status
	VerbosePrintf ("File \"%s\" opened. Size: %d bytes", acFileName, lFileSize);

	// Allocate filebuffer
	bpFileBuffer = new byte[lFileSize];
	
	// Read file into buffer
	iItemsRead = fread ((void *)bpFileBuffer, (size_t)lFileSize, 1, fp3DSFile);
	
	// Close file
	fclose (fp3DSFile);
		
	if (iItemsRead != 1)
	{
		// Error reading 3DS file
		ErrorPrintf ("Error reading file");
		
		// Free filebuffer
		delete [] bpFileBuffer;
		
		return (-1);
	}
	
	// Print status
	VerbosePrintf ("End buffering 3DS file");

	// Print status
	VerbosePrintf ("Begin reading 3DS data");

	// Check for zero length
	if (lFileSize <= CHUNKHEADER_SIZE)
	{
		// Set error file contains no data
		ErrorPrintf ("File contains no data");

		// Return error
		return (-1);
	}

	// Print status
	VerbosePrintf ("Start reading chunks");

	// Get chunks from 3DS file
	while (iCurrentByte < lFileSize)
	{
		// Get chunk id
		iChunkID = Get3DSChunkID (bpFileBuffer + iCurrentByte);
		iCurrentByte += CHUNKID_SIZE;

		// Get chunk length
		lChunkLength = GetInt (bpFileBuffer + iCurrentByte);
		iCurrentByte += CHUNKLENGTH_SIZE;
		
		// Check if length is correct
		if (lChunkLength > (lFileSize - iCurrentByte + CHUNKHEADER_SIZE))
		{
			// Set error chunk size invalid
			ErrorPrintf ("Chunk size invalid");

			// Return error
			return (-1);
		}

		// Check chunk id
		switch (iChunkID)
		{
			case M3DMAGIC_CHUNK:
				// Print status
				VerbosePrintf ("M3DMAGIC chunk found. Length: %d bytes", lChunkLength);

				// Read M3DMAGIC chunk
				if (FILE_3DS::mM3DMagic.Read3DS (lChunkLength - CHUNKHEADER_SIZE,
					bpFileBuffer + iCurrentByte) != 0) {

					// Return error
					return (-1);
				}				
				break;
			default:
				// Print status
				VerbosePrintf ("Unknown chunk found in FILE_3DS: %x", iChunkID);
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}

	// Nr of vertices
	FILE_3DS::iNrOfVertices = 0;

	// Cycle through named objects
	for (int iNamedObject = 0; iNamedObject < FILE_3DS::mM3DMagic.dData.iNrOfNamedObjects;iNamedObject++) {

		// Cycle through tri objects
		for (int iTriObject = 0; iTriObject < FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].iNrOfNTriObjects; iTriObject++) {

			// Get points/faces
			FILE_3DS::iNrOfVertices += (FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].oNTriObject[iTriObject].fFaceArray.iNrOfFaces*3);
		}
	}
/* BUILD ARRAY'S
	// Check if > 0
	if (FILE_3DS::iNrOfVertices > 0) {

		// Alloc
		FILE_3DS::vpVertices = new LGVertex3f[FILE_3DS::iNrOfVertices];
		FILE_3DS::tpTextures = new LGTextureuv[FILE_3DS::iNrOfVertices];
	}

	// Current vertex
	int iCurVertex = 0;

	// Cycle through named objects
	for (iNamedObject = 0; iNamedObject < FILE_3DS::mM3DMagic.dData.iNrOfNamedObjects;iNamedObject++) {

		// Cycle through tri objects
		for (int iTriObject = 0; iTriObject < FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].iNrOfNTriObjects; iTriObject++) {

			// Get points/faces
			POINT_3DS*	pPoints = FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].oNTriObject[iTriObject].pPointArray.pPoints;
			FACE_3DS*	fFaces  = FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].oNTriObject[iTriObject].fFaceArray.fFaces;
			TEXVERT_3DS*	tTexVerts = FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].oNTriObject[iTriObject].tTexVerts.tTexVerts;

			// Cylce through faces
			for (int iFace = 0; iFace < FILE_3DS::mM3DMagic.dData.oNamedObject[iNamedObject].oNTriObject[iTriObject].fFaceArray.iNrOfFaces; iFace++) {

				// Get vertices
				FILE_3DS::vpVertices[iCurVertex].fX = pPoints[fFaces[iFace].iA].fX;
				FILE_3DS::vpVertices[iCurVertex].fY = pPoints[fFaces[iFace].iA].fY;
				FILE_3DS::vpVertices[iCurVertex].fZ = pPoints[fFaces[iFace].iA].fZ;

				FILE_3DS::vpVertices[iCurVertex+2].fX = pPoints[fFaces[iFace].iC].fX;
				FILE_3DS::vpVertices[iCurVertex+2].fY = pPoints[fFaces[iFace].iC].fY;
				FILE_3DS::vpVertices[iCurVertex+2].fZ = pPoints[fFaces[iFace].iC].fZ;

				FILE_3DS::vpVertices[iCurVertex+1].fX = pPoints[fFaces[iFace].iB].fX;
				FILE_3DS::vpVertices[iCurVertex+1].fY = pPoints[fFaces[iFace].iB].fY;
				FILE_3DS::vpVertices[iCurVertex+1].fZ = pPoints[fFaces[iFace].iB].fZ;

				// Get tex coords
				FILE_3DS::tpTextures[iCurVertex].fU = tTexVerts[fFaces[iFace].iA].fU;
				FILE_3DS::tpTextures[iCurVertex].fV = tTexVerts[fFaces[iFace].iA].fV;

				FILE_3DS::tpTextures[iCurVertex+2].fU = tTexVerts[fFaces[iFace].iC].fU;
				FILE_3DS::tpTextures[iCurVertex+2].fV = tTexVerts[fFaces[iFace].iC].fV;

				FILE_3DS::tpTextures[iCurVertex+1].fU = tTexVerts[fFaces[iFace].iB].fU;
				FILE_3DS::tpTextures[iCurVertex+1].fV = tTexVerts[fFaces[iFace].iB].fV;

				// Inc counter
				iCurVertex += 3;
			}
		}
	}

	// Build VBO's
	if (bVBOSupported) {

		// Generate And Bind The Vertex Buffer
		glGenBuffersARB (1, &(FILE_3DS::uVBOVertices));					// Get A Valid Name
		glBindBufferARB (GL_ARRAY_BUFFER_ARB, FILE_3DS::uVBOVertices);	// Bind The Buffer

		// Load The Data
		glBufferDataARB (GL_ARRAY_BUFFER_ARB, FILE_3DS::iNrOfVertices*3*sizeof(float), FILE_3DS::vpVertices, GL_STATIC_DRAW_ARB);

		// Generate And Bind The Texture Coordinate Buffer
		glGenBuffersARB (1, &(FILE_3DS::uVBOTexCoords));					// Get A Valid Name
		glBindBufferARB (GL_ARRAY_BUFFER_ARB, FILE_3DS::uVBOTexCoords);	// Bind The Buffer

		// Load The Data
		glBufferDataARB( GL_ARRAY_BUFFER_ARB, FILE_3DS::iNrOfVertices*2*sizeof(float), FILE_3DS::tpTextures, GL_STATIC_DRAW_ARB );

		// Our Copy Of The Data Is No Longer Necessary, It Is Safe In The Graphics Card
		delete []FILE_3DS::vpVertices; FILE_3DS::vpVertices = NULL;
		delete []FILE_3DS::tpTextures; FILE_3DS::tpTextures = NULL;
	}
*/
	// Print status
	VerbosePrintf ("End reading 3DS data");

	// Free filebuffer
	delete [] bpFileBuffer;

	// Return no error
	return (0);
}

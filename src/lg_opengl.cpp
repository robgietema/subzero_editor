/*******************************************************************************
* File:		lg_opengl.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		27 November 2003
* Note:		This code is based on the NeHe OpenGL framework
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../include/lg_opengl.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
DWORD	dTicks = 0;							// Milliseconds count
DWORD	dGlobalTicks = 0;							// Milliseconds count
extern bool bVBOSupported = false;			// VBO supported
PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;		// VBO Name Generation Procedure
PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;		// VBO Bind Procedure
PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;		// VBO Data Loading Procedure
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB=NULL;	// VBO Deletion Procedure
PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElementsEXT=NULL;	// VBO Deletion Procedure
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glActiveTextureARB = NULL;
PFNGLACTIVETEXTUREARBPROC glClientActiveTextureARB = NULL;

////////////////////////////////////////////////////////////////////////////////
// Pragma
////////////////////////////////////////////////////////////////////////////////
#pragma comment (lib, "opengl32.lib")		// Search For OpenGL32.lib While Linking
#pragma comment (lib, "glu32.lib")			// Search For GLu32.lib While Linking

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* LoadTGA
*******************************************************************************/
int LoadTGA (char *cpFilename, GLuint &uTextureId) {
	FILE*	fpFile;					// Input file
	int		iFileLength;			// Length of the file
	byte*	bpData;					// Buffer
	int		iCurrentByte = 0;		// Current byte in the buffer
	int		iWidth;					// Image width
	int		iHeight;				// Image height
	byte*	bpBits = 0;				// Pointer To The Bitmap Bits
    int		iHeaderSize = 18;		// Headersize of a targa file

	// Print status
	VerbosePrintf ("Reading texture: %s", cpFilename);

	// Open file
	if ((fpFile  = fopen (cpFilename, "rb" )) == NULL) {

		// Print error
		ErrorPrintf ("Input file could not be opened");

		// Return error
		return (-1);
	}

	// Get file length
	fseek (fpFile, 0, SEEK_END);
	iFileLength = ftell (fpFile);

	// Reset file pointer to begin
	fseek (fpFile, 0, SEEK_SET);

	// Allocate buffer
	bpData = new byte[iFileLength];

	// Read buffer
	fread (bpData, sizeof (char), iFileLength, fpFile);

	// Set height and with
	iWidth = (int)bpData[12] + ((int)bpData[13] * 256);
	iHeight = (int)bpData[14] + ((int)bpData[15] * 256);

	VerbosePrintf ("Width, Height, Bpp: %d, %d, %d", iWidth, iHeight, bpData[16]);

	// Allocate bits
	bpBits = new byte[iWidth*iHeight*4];

	// If targa 32-bits per pixel
	if ((int)bpData[16] == 32) {
		for (int iX = 0; iX < iWidth; iX++) {
			for (int iY = 0; iY < iHeight; iY++) {

				// Get RGB info
				bpBits[((iX+(iY*iWidth))*4)+2] = ((int)(bpData[(iX+(iY*iWidth))*4+iHeaderSize]));
				bpBits[((iX+(iY*iWidth))*4)+1] = ((int)(bpData[(iX+(iY*iWidth))*4+iHeaderSize+1]));
				bpBits[((iX+(iY*iWidth))*4)] = ((int)(bpData[(iX+(iY*iWidth))*4+iHeaderSize+2]));
				bpBits[((iX+(iY*iWidth))*4)+3] = ((int)(bpData[(iX+(iY*iWidth))*4+iHeaderSize+3]));
			}
		}

	// Else if targa 24-bits per pixel
	} else if ((int)bpData[16] == 24) {
		for (int iX = 0; iX < iWidth; iX++) {
			for (int iY = 0; iY < iHeight; iY++) {
				// Get RGB info
				bpBits[((iX+(iY*iWidth))*4)+2] = ((int)(bpData[(iX+(iY*iWidth))*3+iHeaderSize]));
				bpBits[((iX+(iY*iWidth))*4)+1] = ((int)(bpData[(iX+(iY*iWidth))*3+iHeaderSize+1]));
				bpBits[((iX+(iY*iWidth))*4)] = ((int)(bpData[(iX+(iY*iWidth))*3+iHeaderSize+2]));

				// Check transparency
				if ((((int)(bpData[(iX+(iY*iWidth))*3+iHeaderSize])) == 0) &&
					(((int)(bpData[(iX+(iY*iWidth))*3+iHeaderSize+1])) == 0) &&
					(((int)(bpData[(iX+(iY*iWidth))*3+iHeaderSize+2])) == 0)) {
					bpBits[((iX+(iY*iWidth))*4)+3] = 0;
				} else {
					bpBits[((iX+(iY*iWidth))*4)+3] = 255;
				}
			}
		}
	}

	// Free temporary buffer
	delete [] bpData;

	// Create the texture
	glGenTextures (1, &uTextureId);

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, uTextureId);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bpBits);

	// Return no error
	return (0);
}

/*******************************************************************************
* LoadAlphaTGA
*******************************************************************************/
int LoadAlphaTGA (char *cpFilename, GLuint &uTextureId, LGColor3b cColor) {
	FILE*	fpFile;					// Input file
	int		iFileLength;			// Length of the file
	byte*	bpData;					// Buffer
	int		iCurrentByte = 0;		// Current byte in the buffer
	int		iWidth;					// Image width
	int		iHeight;				// Image height
	byte*	bpBits = 0;				// Pointer To The Bitmap Bits
    int		iHeaderSize = 18;		// Headersize of a targa file
	int		iR;						// Red
	int		iG;						// Green
	int		iB;						// Blue

	// Open file
	if ((fpFile  = fopen (cpFilename, "rb" )) == NULL) {

		// Print error
		ErrorPrintf ("Input file could not be opened");

		// Return error
		return (-1);
	}

	// Get file length
	fseek (fpFile, 0, SEEK_END);
	iFileLength = ftell (fpFile);

	// Reset file pointer to begin
	fseek (fpFile, 0, SEEK_SET);

	// Allocate buffer
	bpData = new byte[iFileLength];

	// Read buffer
	fread (bpData, sizeof (char), iFileLength, fpFile);

	// Close file
	fclose (fpFile);

	// Set height and with
	iWidth = (int)bpData[12] + ((int)bpData[13] * 256);
	iHeight = (int)bpData[14] + ((int)bpData[15] * 256);

	VerbosePrintf ("Width, Height, Bpp: %d, %d, %d", iWidth, iHeight, bpData[16]);

	// Allocate bits
	bpBits = new byte[iWidth*iHeight*4];

	// If targa 8-bits per pixel
	if ((int)bpData[16] == 8) {
		for (int iX = 0; iX < iWidth; iX++) {
			for (int iY = 0; iY < iHeight; iY++) {

				// Get factor
				int iFactor = (int)(bpData[(iX+(iY*iWidth))+iHeaderSize]);

				if (iFactor <= 127) {

					iR = (int)(((cColor.bR+1) * (((float)iFactor+1)/128)) -1);
					iG = (int)(((cColor.bG+1) * (((float)iFactor+1)/128)) -1);
					iB = (int)(((cColor.bB+1) * (((float)iFactor+1)/128)) -1);
				} else {

					iR = (int)(((255 - cColor.bR) * (((float)iFactor-127)/128)) + cColor.bR);
					iG = (int)(((255 - cColor.bG) * (((float)iFactor-127)/128)) + cColor.bG);
					iB = (int)(((255 - cColor.bB) * (((float)iFactor-127)/128)) + cColor.bB);
				}

				// Get RGB info
				bpBits[((iX+(iY*iWidth))*4)]   = iR;
				bpBits[((iX+(iY*iWidth))*4)+1] = iG;
				bpBits[((iX+(iY*iWidth))*4)+2] = iB;
				bpBits[((iX+(iY*iWidth))*4)+3] = 255;
			}
		}
	}

	// Free temporary buffer
	delete [] bpData;

	// Create the texture
	glGenTextures (1, &uTextureId);

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, uTextureId);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bpBits);

	// Return no error
	return (0);
}

/*******************************************************************************
* IsExtensionSupported
*******************************************************************************/
bool IsExtensionSupported (char* cpTargetExtension) {
	const unsigned char *bpExtensions = NULL;
	const unsigned char *bpStart;
	unsigned char *bpWhere, *bpTerminator;

	// Extension names should not have spaces
	bpWhere = (unsigned char *) strchr( cpTargetExtension, ' ' );

	// If empty extension
	if (bpWhere || *cpTargetExtension == '\0') {

		// Return false
		return false;
	}

	// Get Extensions String
	bpExtensions = glGetString (GL_EXTENSIONS);

	// Search The Extensions String For An Exact Copy
	bpStart = bpExtensions;
	for(;;) {

		// Go to next
		bpWhere = (unsigned char *) strstr( (const char *) bpStart, cpTargetExtension );

		// If last
		if( !bpWhere )

			// Exit
			break;

		// Get terminator
		bpTerminator = bpWhere + strlen (cpTargetExtension);

		// If found
		if( bpWhere == bpStart || *( bpWhere - 1 ) == ' ' )
			if( *bpTerminator == ' ' || *bpTerminator == '\0' )

				// Return true
				return true;

		// Set start to terminator
		bpStart = bpTerminator;
	}

	// Return false
	return false;
}

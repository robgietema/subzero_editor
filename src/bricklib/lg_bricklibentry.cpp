/*******************************************************************************
* File:		lg_bricklibentry.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		20 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/bricklib/lg_bricklibentry.h"
#include "../../include/glext.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* LGBrickLibEntry::LGBrickLibEntry
*******************************************************************************/
LGBrickLibEntry::LGBrickLibEntry () {
}

/*******************************************************************************
* LGBrickLibEntry::~LGBrickLibEntry
*******************************************************************************/
LGBrickLibEntry::~LGBrickLibEntry () {
}

/*******************************************************************************
* LGBrickLibEntry::read
*******************************************************************************/
int LGBrickLibEntry::read (byte* bpData, int iDataSize) {
	int iCurrentByte=0;		// Current byte

	// Print status
	VerbosePrintf ("Begin BEN");

	// Get values
	LGBrickLibEntry::iNrOfVerticesElements = GetInt (bpData + iCurrentByte);
	iCurrentByte += SIZE_INT;
	LGBrickLibEntry::iBlockNumber = GetInt (bpData + iCurrentByte);
	iCurrentByte += SIZE_INT;

	// Alloc arrays
	LGBrickLibEntry::vpVerticesElements = new LGVertex3f[LGBrickLibEntry::iNrOfVerticesElements];
	LGBrickLibEntry::tpTexturesElements = new LGTextureuv[LGBrickLibEntry::iNrOfVerticesElements];

	// Print vertices
	for (int iCount = 0; iCount < LGBrickLibEntry::iNrOfVerticesElements; iCount++) {

		// Get vertex
		LGBrickLibEntry::vpVerticesElements[iCount] = GetVertex3f (bpData + iCurrentByte);
		iCurrentByte += SIZE_VERTEX3F;
		LGBrickLibEntry::tpTexturesElements[iCount] = GetTextureuv (bpData + iCurrentByte);
		iCurrentByte += SIZE_TEXTUREUV;
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::write
*******************************************************************************/
int LGBrickLibEntry::write (FILE* fpFile) {

	// Print header id
	PrintChunkID (fpFile, "BEN");

	// Print chunk size
	PrintInt (fpFile, LGBrickLibEntry::getChunkSize ());

	// Print data
	PrintInt (fpFile, LGBrickLibEntry::iNrOfVerticesElements);
	PrintInt (fpFile, LGBrickLibEntry::iBlockNumber);

	// Print vertices
	for (int iCount = 0; iCount < LGBrickLibEntry::iNrOfVerticesElements; iCount++) {

		// Print vertex
		PrintVertex3f (fpFile, LGBrickLibEntry::vpVerticesElements[iCount]);
		PrintTextureuv (fpFile, LGBrickLibEntry::tpTexturesElements[iCount]);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::loadTextures
*******************************************************************************/
int LGBrickLibEntry::loadTextures () {
	extern LGColor3b acColors[NR_OF_COLORS];	// Colors
	char acFilename[512];						// Filename
	FILE*	fpFile;								// Input file
	int		iFileLength;						// Length of the file
	byte*	bpData;								// Buffer
	int		iCurrentByte = 0;					// Current byte in the buffer
	int		iWidth;								// Image width
	int		iHeight;							// Image height
	byte*	bpBits = 0;							// Pointer To The Bitmap Bits
	byte*	bpScaledBits = 0;					// Pointer To The Scaled Bitmap Bits
    int		iHeaderSize = 18;					// Headersize of a targa file
	int		iR;									// Red
	int		iG;									// Green
	int		iB;									// Blue
	int		iFactor;							// Factor
	int		iScaledWidth;						// Scaled width
	int		iScaledHeight;						// Scaled height
	int		iLevel;								// Mipmap level
	float	fLineWidth;							// Linewidth
	GLint	unpackrowlength, unpackalignment, unpackskiprows, unpackskippixels;
	GLint	packrowlength, packalignment, packskiprows, packskippixels;

	if (LGBrickLibEntry::iBlockNumber != 3001) {
		return -1;
	}

	if (LGBrickLibEntry::iBlockNumber == 3001) {

		// Set filename
		sprintf (acFilename, "data/textures/bricks/%d.tga", LGBrickLibEntry::iBlockNumber);

	} else {

		// Set default texture
		sprintf (acFilename, "data/textures/bricks/default.tga");
	}

	// Open file
	if ((fpFile  = fopen (acFilename, "rb" )) == NULL) {

		// Set default texture
		sprintf (acFilename, "data/textures/bricks/default.tga");

		// Open file
		if ((fpFile  = fopen (acFilename, "rb" )) == NULL) {

			// Print error
			ErrorPrintf ("Input file could not be opened");

			// Return error
			return (-1);
		}
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

	// Allocate bits
	bpBits = new byte[iWidth*iHeight*4];

	// If targa 8-bits per pixel
	if ((int)bpData[16] == 8) {

		// Set texture type
		LGBrickLibEntry::iTextureType = 0;

		// Alloc colors
		LGBrickLibEntry::aiTextures = new GLuint[NR_OF_COLORS];

		// Loop thru colors
		for (int iColorCount = 0; iColorCount < NR_OF_COLORS; iColorCount++) {

			// Go through pixels
			for (int iX = 0; iX < iWidth; iX++) {
				for (int iY = 0; iY < iHeight; iY++) {

					// Get factor
					iFactor = (int)(bpData[(iX+(iY*iWidth))+iHeaderSize]);

					if (iFactor <= 127) {

						iR = (int)(((acColors[iColorCount].bR+1) * (((float)iFactor+1)/128)) - 1);
						iG = (int)(((acColors[iColorCount].bG+1) * (((float)iFactor+1)/128)) - 1);
						iB = (int)(((acColors[iColorCount].bB+1) * (((float)iFactor+1)/128)) - 1);
					} else {

						iR = (int)(((255 - acColors[iColorCount].bR) * (((float)iFactor-127)/128)) + acColors[iColorCount].bR);
						iG = (int)(((255 - acColors[iColorCount].bG) * (((float)iFactor-127)/128)) + acColors[iColorCount].bG);
						iB = (int)(((255 - acColors[iColorCount].bB) * (((float)iFactor-127)/128)) + acColors[iColorCount].bB);
					}

					// Get RGB info
					bpBits[((iX+(iY*iWidth))*4)]   = iR;
					bpBits[((iX+(iY*iWidth))*4)+1] = iG;
					bpBits[((iX+(iY*iWidth))*4)+2] = iB;
					bpBits[((iX+(iY*iWidth))*4)+3] = 255;
				}
			}

			// Create the texture
			glGenTextures (1, &LGBrickLibEntry::aiTextures[iColorCount]);

			// Typical Texture Generation Using Data From The Bitmap
			glBindTexture(GL_TEXTURE_2D, LGBrickLibEntry::aiTextures[iColorCount]);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bpBits);
//			glTexImage2D(GL_TEXTURE_2D, 0, 1, iWidth, iHeight, 0, GL_COLOR_INDEX, GL_UNSIGNED_BYTE, bpBits);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
//			glTexEnvf(GL_TEXTURE_FILTER_CONTROL_EXT, GL_TEXTURE_LOD_BIAS_EXT, -1);

			GLfloat fLarge;
			glGetFloatv (GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLarge);
			glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLarge);

//			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, iWidth, iHeight, GL_RGBA, GL_UNSIGNED_BYTE, bpBits);

			iScaledWidth = iWidth;
			iScaledHeight = iHeight;
			iLevel = 0;

			// Get current glPixelStore values
			glGetIntegerv (GL_UNPACK_ROW_LENGTH, &unpackrowlength);
			glGetIntegerv (GL_UNPACK_ALIGNMENT, &unpackalignment);
			glGetIntegerv (GL_UNPACK_SKIP_ROWS, &unpackskiprows);
			glGetIntegerv (GL_UNPACK_SKIP_PIXELS, &unpackskippixels);
			glGetIntegerv (GL_PACK_ROW_LENGTH, &packrowlength);
			glGetIntegerv (GL_PACK_ALIGNMENT, &packalignment);
			glGetIntegerv (GL_PACK_SKIP_ROWS, &packskiprows);
			glGetIntegerv (GL_PACK_SKIP_PIXELS, &packskippixels);

			// set pixel packing
			glPixelStorei(GL_PACK_ROW_LENGTH, 0);
			glPixelStorei(GL_PACK_ALIGNMENT, 1);
			glPixelStorei(GL_PACK_SKIP_ROWS, 0);
			glPixelStorei(GL_PACK_SKIP_PIXELS, 0);

			while ((iScaledWidth > 0) && (iScaledHeight > 0)) {

				if (iLevel > 0) {

					// set pixel unpacking
					glPixelStorei (GL_UNPACK_ROW_LENGTH, 0);
					glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
					glPixelStorei (GL_UNPACK_SKIP_ROWS, 0);
					glPixelStorei (GL_UNPACK_SKIP_PIXELS, 0);
				}

				switch (iLevel) {

					case 0:		fLineWidth = 2; break;
					case 1:		fLineWidth = 3; break;
					case 2:		fLineWidth = 4; break;
					case 3:		fLineWidth = 6; break;
					case 4:		fLineWidth = 9; break;
					case 5:		fLineWidth = 12; break;
					default:	fLineWidth = 15; break;
				}

				// DrawLines

				// Short Side horizontal
				DrawLine (256, 512, 0, 102, 127, 102, 1, fLineWidth, bpBits);
				DrawLine (256, 512, 0, 178, 127, 178, 0, fLineWidth, bpBits);

				// Short Side vertical
				DrawLine (256, 512, 0, 102, 0, 178, 1, fLineWidth, bpBits);
				DrawLine (256, 512, 127, 102, 127, 178, 0, fLineWidth, bpBits);

				// Long Side horizontal
				DrawLine (256, 512, 0, 179, 255, 179, 1, fLineWidth, bpBits);
				DrawLine (256, 512, 0, 255, 255, 255, 0, fLineWidth, bpBits);

				// Long Side vertical
				DrawLine (256, 512, 0, 179, 0, 255, 1, fLineWidth, bpBits);
				DrawLine (256, 512, 255, 179, 255, 255, 0, fLineWidth, bpBits);

				// Bottom horizontal
				DrawLine (256, 512, 0, 256, 255, 256, 1, fLineWidth, bpBits);
				DrawLine (256, 512, 0, 383, 255, 383, 0, fLineWidth, bpBits);

				// Bottom vertical
				DrawLine (256, 512, 0, 256, 0, 383, 1, fLineWidth, bpBits);
				DrawLine (256, 512, 255, 256, 255, 383, 0, fLineWidth, bpBits);

				// Top horizontal
				DrawLine (256, 512, 0, 384, 255, 384, 1, fLineWidth, bpBits);
				DrawLine (256, 512, 0, 511, 255, 511, 0, fLineWidth, bpBits);

				// Top vertical
				DrawLine (256, 512, 0, 384, 0, 511, 1, fLineWidth, bpBits);
				DrawLine (256, 512, 255, 384, 255, 511, 0, fLineWidth, bpBits);

				// Scale
				bpScaledBits = new byte[iScaledWidth*iScaledHeight*4];

				gluScaleImage(GL_RGBA, iWidth, iHeight, GL_UNSIGNED_BYTE, bpBits, iScaledWidth, iScaledHeight, GL_UNSIGNED_BYTE, bpScaledBits);
//				Scale (iWidth, iHeight, iScaledWidth, iScaledHeight, bpBits, bpScaledBits);

				glTexImage2D(GL_TEXTURE_2D, iLevel, GL_RGBA, iScaledWidth, iScaledHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bpScaledBits);
				delete []bpScaledBits;

				if ((iScaledWidth == 1) && (iScaledHeight == 1)) {
					iScaledWidth = 0;
					iScaledHeight = 0;
				} else {
					iScaledWidth = iScaledWidth < 2 ? 1 : iScaledWidth / 2;
					iScaledHeight = iScaledHeight < 2 ? 1 : iScaledHeight / 2;
				}
				iLevel++;

			}

			// Restore original glPixelStore state
			glPixelStorei (GL_UNPACK_ROW_LENGTH, unpackrowlength);
			glPixelStorei (GL_UNPACK_ALIGNMENT, unpackalignment);
			glPixelStorei (GL_UNPACK_SKIP_ROWS, unpackskiprows);
			glPixelStorei (GL_UNPACK_SKIP_PIXELS, unpackskippixels);
			glPixelStorei (GL_PACK_ROW_LENGTH, packrowlength);
			glPixelStorei (GL_PACK_ALIGNMENT, packalignment);
			glPixelStorei (GL_PACK_SKIP_ROWS, packskiprows);
			glPixelStorei (GL_PACK_SKIP_PIXELS, packskippixels);
		}

	// Else if targa 24-bits per pixel
	} else if ((int)bpData[16] == 24) {

		// Set texture type
		LGBrickLibEntry::iTextureType = 1;

		// Alloc colors
		LGBrickLibEntry::aiTextures = new GLuint[1];

		// Go through pixels
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

		// Create the texture
		glGenTextures (1, &LGBrickLibEntry::aiTextures[0]);

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, LGBrickLibEntry::aiTextures[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bpBits);

	// Else if targa 32-bits per pixel
	} else if ((int)bpData[16] == 32) {

		// Todo
	}

	// Delete data
	delete []bpBits;

	// Free temporary buffer
	delete []bpData;

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::setVertex
*******************************************************************************/
int LGBrickLibEntry::setVertex (int iIndex, float fU, float fV, float fX, float fY, float fZ) {

	// Set texture coords
	LGBrickLibEntry::tpTexturesElements[iIndex].fU = fU;
	LGBrickLibEntry::tpTexturesElements[iIndex].fV = fV;

	// Set vertex coords
	LGBrickLibEntry::vpVerticesElements[iIndex].fX = fX;
	LGBrickLibEntry::vpVerticesElements[iIndex].fY = fY;
	LGBrickLibEntry::vpVerticesElements[iIndex].fZ = fZ;

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::setVertexNormal
*******************************************************************************/
int LGBrickLibEntry::setVertexNormal (int iIndex, float fU, float fV, float fX, float fY, float fZ, float fNormalX, float fNormalY, float fNormalZ) {

	// Set texture coords
	LGBrickLibEntry::tpTexturesArrays[iIndex].fU = fU;
	LGBrickLibEntry::tpTexturesArrays[iIndex].fV = fV;

	// Set vertex coords
	LGBrickLibEntry::vpVerticesArrays[iIndex].fX = fX;
	LGBrickLibEntry::vpVerticesArrays[iIndex].fY = fY;
	LGBrickLibEntry::vpVerticesArrays[iIndex].fZ = fZ;

	// Set normal coords
	LGBrickLibEntry::vpNormalsArrays[iIndex].fX = fNormalX;
	LGBrickLibEntry::vpNormalsArrays[iIndex].fY = fNormalY;
	LGBrickLibEntry::vpNormalsArrays[iIndex].fZ = fNormalZ;

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::setFace
*******************************************************************************/
int LGBrickLibEntry::setFace (int iIndex, unsigned short sA, unsigned short sB, unsigned short sC, unsigned short sD) {

	// Set texture coords
	LGBrickLibEntry::fpFaces[iIndex].sA = sA;
	LGBrickLibEntry::fpFaces[iIndex].sB = sB;
	LGBrickLibEntry::fpFaces[iIndex].sC = sC;
	LGBrickLibEntry::fpFaces[iIndex].sD = sD;

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::initDefaultValues
*******************************************************************************/
int LGBrickLibEntry::initDefaultValues (int iEntry) {

	// Generate vertex array
	switch (iEntry) {

		// 1 x X bricks
		case  0: LGBrickLibEntry::iBlockNumber = 3005;	LGBrickLibEntry::createBrick (1, 1, 3);	break;	// Brick 1 x 1
		case  1: LGBrickLibEntry::iBlockNumber = 3004;	LGBrickLibEntry::createBrick (1, 2, 3);	break;	// Brick 1 x 2
		case  2: LGBrickLibEntry::iBlockNumber = 3622;	LGBrickLibEntry::createBrick (1, 3, 3);	break;	// Brick 1 x 3
		case  3: LGBrickLibEntry::iBlockNumber = 3010;	LGBrickLibEntry::createBrick (1, 4, 3);	break;	// Brick 1 x 4
		case  4: LGBrickLibEntry::iBlockNumber = 3009;	LGBrickLibEntry::createBrick (1, 6, 3);	break;	// Brick 1 x 6
		case  5: LGBrickLibEntry::iBlockNumber = 3008;	LGBrickLibEntry::createBrick (1, 8, 3);	break;	// Brick 1 x 8
		case  6: LGBrickLibEntry::iBlockNumber = 6111;	LGBrickLibEntry::createBrick (1,10, 3);	break;	// Brick 1 x 10
		case  7: LGBrickLibEntry::iBlockNumber = 6112;	LGBrickLibEntry::createBrick (1,12, 3);	break;	// Brick 1 x 12
		case  8: LGBrickLibEntry::iBlockNumber = 2465;	LGBrickLibEntry::createBrick (1,16, 3);	break;	// Brick 1 x 16

		// 2 x X bricks
		case  9: LGBrickLibEntry::iBlockNumber = 3003;	LGBrickLibEntry::createBrick (2, 2, 3);	break;	// Brick 2 x 2
		case 10: LGBrickLibEntry::iBlockNumber = 3002;	LGBrickLibEntry::createBrick (2, 3, 3);	break;	// Brick 2 x 3
		case 11: LGBrickLibEntry::iBlockNumber = 3001;	LGBrickLibEntry::createBrick (2, 4, 3);	break;	// Brick 2 x 4
		case 12: LGBrickLibEntry::iBlockNumber = 2456;	LGBrickLibEntry::createBrick (2, 6, 3);	break;	// Brick 2 x 6
		case 13: LGBrickLibEntry::iBlockNumber = 3007;	LGBrickLibEntry::createBrick (2, 8, 3);	break;	// Brick 2 x 8
		case 14: LGBrickLibEntry::iBlockNumber = 3006;	LGBrickLibEntry::createBrick (2,10, 3);	break;	// Brick 2 x 10

		// 1 x X plates
		case 15: LGBrickLibEntry::iBlockNumber = 3024;	LGBrickLibEntry::createBrick (1, 1, 1);	break;	// Plate 1 x 1
		case 16: LGBrickLibEntry::iBlockNumber = 3023;	LGBrickLibEntry::createBrick (1, 2, 1);	break;	// Plate 1 x 2
		case 17: LGBrickLibEntry::iBlockNumber = 3623;	LGBrickLibEntry::createBrick (1, 3, 1);	break;	// Plate 1 x 3
		case 18: LGBrickLibEntry::iBlockNumber = 3710;	LGBrickLibEntry::createBrick (1, 4, 1);	break;	// Plate 1 x 4
		case 19: LGBrickLibEntry::iBlockNumber = 3666;	LGBrickLibEntry::createBrick (1, 6, 1);	break;	// Plate 1 x 6
		case 20: LGBrickLibEntry::iBlockNumber = 3460;	LGBrickLibEntry::createBrick (1, 8, 1);	break;	// Plate 1 x 8
		case 21: LGBrickLibEntry::iBlockNumber = 4477;	LGBrickLibEntry::createBrick (1,10, 1);	break;	// Plate 1 x 10
	
		// 2 x X plates
		case 22: LGBrickLibEntry::iBlockNumber = 3022;	LGBrickLibEntry::createBrick (2, 2, 1);	break;	// Plate 2 x 2
		case 23: LGBrickLibEntry::iBlockNumber = 3021;	LGBrickLibEntry::createBrick (2, 3, 1);	break;	// Plate 2 x 3
		case 24: LGBrickLibEntry::iBlockNumber = 3020;	LGBrickLibEntry::createBrick (2, 4, 1);	break;	// Plate 2 x 4
		case 25: LGBrickLibEntry::iBlockNumber = 3795;	LGBrickLibEntry::createBrick (2, 6, 1);	break;	// Plate 2 x 6
		case 26: LGBrickLibEntry::iBlockNumber = 3034;	LGBrickLibEntry::createBrick (2, 8, 1);	break;	// Plate 2 x 8
		case 27: LGBrickLibEntry::iBlockNumber = 3832;	LGBrickLibEntry::createBrick (2,10, 1);	break;	// Plate 2 x 10
		case 28: LGBrickLibEntry::iBlockNumber = 2445;	LGBrickLibEntry::createBrick (2,12, 1);	break;	// Plate 2 x 12
		case 29: LGBrickLibEntry::iBlockNumber = 4282;	LGBrickLibEntry::createBrick (2,16, 1);	break;	// Plate 2 x 16

		// 4 x X plates
		case 30: LGBrickLibEntry::iBlockNumber = 3031;	LGBrickLibEntry::createBrick (4, 4, 1);	break;	// Plate 4 x 4
		case 31: LGBrickLibEntry::iBlockNumber = 3032;	LGBrickLibEntry::createBrick (4, 6, 1);	break;	// Plate 4 x 6
		case 32: LGBrickLibEntry::iBlockNumber = 3035;	LGBrickLibEntry::createBrick (4, 8, 1);	break;	// Plate 4 x 8
		case 33: LGBrickLibEntry::iBlockNumber = 3030;	LGBrickLibEntry::createBrick (4,10, 1);	break;	// Plate 4 x 10
		case 34: LGBrickLibEntry::iBlockNumber = 3029;	LGBrickLibEntry::createBrick (4,12, 1);	break;	// Plate 4 x 12

		// 6 x X plates
		case 35: LGBrickLibEntry::iBlockNumber = 3958;	LGBrickLibEntry::createBrick (6, 6, 1);	break;	// Plate 6 x 6
		case 36: LGBrickLibEntry::iBlockNumber = 3036;	LGBrickLibEntry::createBrick (6, 8, 1);	break;	// Plate 6 x 8
		case 37: LGBrickLibEntry::iBlockNumber = 3033;	LGBrickLibEntry::createBrick (6,10, 1);	break;	// Plate 6 x 10
		case 38: LGBrickLibEntry::iBlockNumber = 3028;	LGBrickLibEntry::createBrick (6,12, 1);	break;	// Plate 6 x 12
		case 39: LGBrickLibEntry::iBlockNumber = 3456;	LGBrickLibEntry::createBrick (6,14, 1);	break;	// Plate 6 x 14
		case 40: LGBrickLibEntry::iBlockNumber = 3027;	LGBrickLibEntry::createBrick (6,16, 1);	break;	// Plate 6 x 16
		case 41: LGBrickLibEntry::iBlockNumber = 3026;	LGBrickLibEntry::createBrick (6,24, 1);	break;	// Plate 6 x 24

		// 8 x X plates
		case 42: LGBrickLibEntry::iBlockNumber = 41539;	LGBrickLibEntry::createBrick (8, 8, 1);	break;	// Plate 8 x 8

		// Other bricks
		case 43: LGBrickLibEntry::iBlockNumber = 2493;	LGBrickLibEntry::iTextureType = 1;	LGBrickLibEntry::createBrick (1, 4,15);	break;	// Window 1 x 4 x 5
		case 44: LGBrickLibEntry::iBlockNumber = 772;	LGBrickLibEntry::iTextureType = 1;	LGBrickLibEntry::createBrick (1, 2, 6);	break;	// Panel 1 x 2 x 2

		// Slopes
		case 45: LGBrickLibEntry::iBlockNumber = 30363;	LGBrickLibEntry::createSlope (2, 4, 3);	break;	// Slope 2x4x1 30363
		case 46: LGBrickLibEntry::iBlockNumber = 4286;	LGBrickLibEntry::createSlope (1, 3, 3);	break;	// Slope 1x3x1 4286
		case 47: LGBrickLibEntry::iBlockNumber = 3298;	LGBrickLibEntry::createSlope (2, 3, 3);	break;	// Slope 2x3x1 3298
		case 48: LGBrickLibEntry::iBlockNumber = 4161;	LGBrickLibEntry::createSlope (3, 3, 3);	break;	// Slope 3x3x1 4161
		case 49: LGBrickLibEntry::iBlockNumber = 3297;	LGBrickLibEntry::createSlope (4, 3, 3);	break;	// Slope 4x3x1 3297
		case 50: LGBrickLibEntry::iBlockNumber = 3040;	LGBrickLibEntry::createSlope (1, 2, 3);	break;	// Slope 1x2x1 3040
		case 51: LGBrickLibEntry::iBlockNumber = 3039;	LGBrickLibEntry::createSlope (2, 2, 3);	break;	// Slope 2x2x1 3039
		case 52: LGBrickLibEntry::iBlockNumber = 2038;	LGBrickLibEntry::createSlope (3, 2, 3);	break;	// Slope 3x2x1 2038
		case 53: LGBrickLibEntry::iBlockNumber = 3037;	LGBrickLibEntry::createSlope (4, 2, 3);	break;	// Slope 4x2x1 3037

		case 54: LGBrickLibEntry::iBlockNumber = 3678;	LGBrickLibEntry::createSlope (2, 2, 6);	break;	// Slope 2x2x2 3678
		case 55: LGBrickLibEntry::iBlockNumber = 4460;	LGBrickLibEntry::createSlope (1, 2, 9);	break;	// Slope 1x2x3 4460
		case 56: LGBrickLibEntry::iBlockNumber = 3684;	LGBrickLibEntry::createSlope (2, 2, 9);	break;	// Slope 2x2x3 3684

		// Inverted slopes
		case 57: LGBrickLibEntry::iBlockNumber = 3747;	LGBrickLibEntry::createInvertedSlope (2, 3, 3);	break;	// Slope inverted 2x3x1
		case 58: LGBrickLibEntry::iBlockNumber = 4287;	LGBrickLibEntry::createInvertedSlope (1, 3, 3);	break;	// Slope inverted 1x3x1
		case 59: LGBrickLibEntry::iBlockNumber = 3665;	LGBrickLibEntry::createInvertedSlope (1, 2, 3);	break;	// Slope inverted 1x2x1
		case 60: LGBrickLibEntry::iBlockNumber = 3660;	LGBrickLibEntry::createInvertedSlope (2, 2, 3);	break;	// Slope inverted 2x2x1

		case 61: LGBrickLibEntry::iBlockNumber = 2449;	LGBrickLibEntry::createInvertedSlope (1, 2, 9);	break;	// Slope inverted 1x2x3

		// Brick without corner
		case 62: LGBrickLibEntry::iBlockNumber = 30505;	LGBrickLibEntry::createBrickWithoutCorner (3, 3, 3);	break;	// Brick 3 x 3 without corner
		case 63: LGBrickLibEntry::iBlockNumber = 2450;	LGBrickLibEntry::createBrickWithoutCorner (3, 3, 1);	break;	// Plate 3 x 3 without corner

		// Other bricks without corner
		case 64: LGBrickLibEntry::iBlockNumber = 6565;	LGBrickLibEntry::createBrickByNumber (6565);	break;	// Brick 2 x 3 without corner
		case 65: LGBrickLibEntry::iBlockNumber = 6564;	LGBrickLibEntry::createBrickByNumber (6564);	break;	// Brick 2 x 3 without corner inverted l<->r
		case 66: LGBrickLibEntry::iBlockNumber = 2419;	LGBrickLibEntry::createBrickWithout2Corners (6, 3, 1);	break;	// Plate 6 x 3 without 2 corners

		case 67: LGBrickLibEntry::iBlockNumber = 3023;	LGBrickLibEntry::createBrick (1, 2, 1);	break;	// Plate 1 x 2 with 1 in the middle
		case 68: LGBrickLibEntry::iBlockNumber = 4176;	LGBrickLibEntry::createSlope (6, 2, 6);	break;	// Windscreen 2 x 6 x 2

		case 69: LGBrickLibEntry::iBlockNumber = 3185;	LGBrickLibEntry::createBrickByNumber (3185);	break;	// Fence 1 x 4 x 2
		case 70: LGBrickLibEntry::iBlockNumber = 3633;	LGBrickLibEntry::createBrickByNumber (3633);	break;	// Fence 1 x 4 x 1
		case 71: LGBrickLibEntry::iBlockNumber = 30413;	LGBrickLibEntry::createBrickByNumber (30413);	break;	// Panel 1 x 4 x 1
		case 72: LGBrickLibEntry::iBlockNumber = 4865;	LGBrickLibEntry::createBrickByNumber (4865);	break;	// Panel 1 x 2 x 1

		case 73: LGBrickLibEntry::iBlockNumber = 608;	LGBrickLibEntry::createBasePlate ();			break;	// Base plate T-junction

		// Windows
		case 74: LGBrickLibEntry::iBlockNumber = 4035;	LGBrickLibEntry::createBrick (1, 2, 9);		break;	// Window 1 x 2 x 3
		case 75: LGBrickLibEntry::iBlockNumber = 27;	LGBrickLibEntry::createBrick (1, 2, 3);		break;	// Window 1 x 2 x 1
		case 76: LGBrickLibEntry::iBlockNumber = 604;	LGBrickLibEntry::createBrick (1, 6, 9);		break;	// Window 1 x 6 x 3
		case 77: LGBrickLibEntry::iBlockNumber = 31;	LGBrickLibEntry::createBrick (1, 3, 6);		break;	// Window 1 x 3 x 2
		case 78: LGBrickLibEntry::iBlockNumber = 6154;	LGBrickLibEntry::createBrick (1, 4, 12);	break;	// Window 1 x 4 x 4

		case 79: LGBrickLibEntry::iBlockNumber = 4865;	LGBrickLibEntry::createBrickByNumber (4865);	break;	// Hollow brick 1 x 2 x 1
		case 80: LGBrickLibEntry::iBlockNumber = 4070;	LGBrickLibEntry::createBrickByNumber (4070);	break;	// Brick 1 x 1 x 1 with side dot
		case 81: LGBrickLibEntry::iBlockNumber = 3788;	LGBrickLibEntry::createBrickByNumber (3788);	break;	// Plate 2 x 4 with wheel slot
		case 82: LGBrickLibEntry::iBlockNumber = 2412;	LGBrickLibEntry::createBrick (1, 2, 1);	break;	// Grill 1 x 2 x 1
		case 83: LGBrickLibEntry::iBlockNumber = 4859;	LGBrickLibEntry::createBrickByNumber (4859);	break;	// Wing 3 x 4

		case 84: LGBrickLibEntry::iBlockNumber = 30355;	LGBrickLibEntry::createBrickByNumber (30355);	break;	// Wing 6 x 12 left
		case 85: LGBrickLibEntry::iBlockNumber = 30356;	LGBrickLibEntry::createBrickByNumber (30356);	break;	// Wing 6 x 12 right
		case 86: LGBrickLibEntry::iBlockNumber = 3933;	LGBrickLibEntry::createBrickByNumber (3933);	break;	// Wing 4 x 8 left
		case 87: LGBrickLibEntry::iBlockNumber = 3934;	LGBrickLibEntry::createBrickByNumber (3934);	break;	// Wing 4 x 8 right
		case 88: LGBrickLibEntry::iBlockNumber = 3045;	LGBrickLibEntry::createBrickByNumber (3045);	break;	// Brick with double slope 2 x 2
		case 89: LGBrickLibEntry::iBlockNumber = 3046;	LGBrickLibEntry::createBrickByNumber (3046);	break;	// Brick with double inset slope 2 x 2
		case 90: LGBrickLibEntry::iBlockNumber = 4864;	LGBrickLibEntry::createBrickByNumber (4864);	break;	// Brick 1 x 2 x 2 hollow
		case 91: LGBrickLibEntry::iBlockNumber = 6231;	LGBrickLibEntry::createBrickByNumber (6231);	break;	// Brick 1 x 1 x 1 hollow corner
		case 92: LGBrickLibEntry::iBlockNumber = 4856;	LGBrickLibEntry::createBrickByNumber (4856);	break;	// Inverse wing 4 x 6
		case 93: LGBrickLibEntry::iBlockNumber = 3823;	LGBrickLibEntry::createSlope (4, 2, 6);	break;	// Windscreen 2 x 4 x 2
		case 94: LGBrickLibEntry::iBlockNumber = 2437;	LGBrickLibEntry::createSlope (4, 3, 4);	break;	// Windscreen 3 x 4 x 1 1/3
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::createBrickByNumber
*******************************************************************************/
int LGBrickLibEntry::createBrickByNumber (int iNumber) {

	/*******************************************************************************
	* Create Displaylist part
	*******************************************************************************/
	LGBrickLibEntry::iDisplayList = glGenLists(1);
	glNewList (LGBrickLibEntry::iDisplayList, GL_COMPILE);

	glBegin(GL_TRIANGLES);

	if (iNumber == 6565) {

		// Slope Face
		glNormal3f( -0.316f, 0.0f, 0.949f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0,					0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,			0.32f * 3,			0.8f * 2);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 3,			0.8f);

		glNormal3f( -0.316f, 0.0f, 0.949f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 3,			0.0f,				0.8f * 2);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,			0.32f * 3,			0.8f * 2);

		// Back Face
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 3,			0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,			0.32f * 3,			0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,			0.32f * 3,			0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 3,			0.0f,				0.0f);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,	0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.32f * 3,	0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,	0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,	0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,			0.32f * 3,	0.8f * 2);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.32f * 3,	0.0f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,			0.0f,				0.8f * 2);

		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,  0.0f,  0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 3,  0.32f * 3,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 0.8f * 3,  0.32f * 3,  0.8f * 2);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,  0.0f,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 0.8f * 3,  0.32f * 3,  0.8f * 2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.8f * 3,  0.0f,  0.8f * 2);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.0f,  0.8f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.32f * 3,  0.8f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.32f * 3,  0.8f);
		glTexCoord2f(0.25f, 0.5f); glVertex3f( 0.0f,  0.32f * 3,  0.0f);
	} else if (iNumber == 6564) {
		// Slope Face
		glNormal3f( -0.316f, 0.0f, -0.949f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0,					0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,			0.32f * 3,			0.0f);

		glNormal3f( -0.316f, 0.0f, -0.949f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,			0.32f * 3,			0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 3,			0.0f,				0.0f);

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				1.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,			0.32f * 3,			1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 3,			1.6f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 3,			0.0f,				1.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,			0.32f * 3,			1.6f);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,	1.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.32f * 3,	0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,	0.8f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,	1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,			0.32f * 3,	0.8f * 2);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.32f * 3,	0.0f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				1.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,			0.0f,				0.8f * 2);

		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,  0.0f,  0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 3,  0.32f * 3,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 0.8f * 3,  0.32f * 3,  0.8f * 2);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,  0.0f,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 0.8f * 3,  0.32f * 3,  0.8f * 2);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.8f * 3,  0.0f,  0.8f * 2);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.8f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.0f,  1.6f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.32f * 3,  1.6f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.8f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.32f * 3,  1.6f);
		glTexCoord2f(0.25f, 0.5f); glVertex3f( 0.0f,  0.32f * 3,  0.8f);

	} else if (iNumber == 3045) {

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.0f,		0.0f,		0.8f * 2);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,	0.0f,		0.8f * 2);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.15f,		0.8f * 2);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.0f,		0.0f,		0.8f * 2);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.15f,		0.8f * 2);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);

		// Front Slope
		glNormal3f( 0.0f, 0.5f, 0.5f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 1);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 1,	0.32f * 3,	0.8f * 1);

		glNormal3f( 0.0f, 0.5f, 0.5f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.15f,		0.8f * 2);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 1);

		// Back Face
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.0f,		0.0f);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.0f,		0.15f,		0.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.8f * 2,	0.0f,		0.0f);

		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.15f,		0.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.0f);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.0f,		0.0f);

		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.15f,		0.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.8f,		0.32f * 3,	0.0f);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.0f);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f,		0.32f * 3,	0.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.8f,		0.32f * 3,	0.8f * 1);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 1);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f,		0.32f * 3,	0.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 1);
		glTexCoord2f(1.0f, 0.5f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.0f);

		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.0f,		0.0f,		0.0f);
		glTexCoord2f(1.0f, 0.5f);	glVertex3f( 0.8f * 2,	0.0f,		0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.0f,		0.8f * 2);

		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.0f,		0.0f,		0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.0f,		0.8f * 2);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.0f,		0.0f,		0.8f * 2);

		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.0f,		0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 2,	0.15f,		0.8f * 2);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.0f,		0.8f * 2);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.0f,		0.0f);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,	0.15f,		0.8f * 2);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,	0.15f,		0.8f * 2);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.0f,		0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.0f,		0.0f,		0.8f * 2);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.0f,		0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.0f,		0.15f,		0.0f);

		// Left Slope
		glNormal3f(-0.5f, 0.5f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.15f,		0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f,		0.32f * 3,	0.0f);

		glNormal3f(-0.5f, 0.5f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f,		0.32f * 3,	0.8f);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f,		0.32f * 3,	0.0f);

	} else if (iNumber == 4856) {

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 3,	0.81f,		0.8f * 4);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 6,	0.0f,		0.8f * 4);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 6,	0.96f,		0.8f * 4);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 3,	0.96f,		0.8f * 4);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 3,	0.81f,		0.8f * 4);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.8f * 6,	0.96f,		0.8f * 4);

		// Front Inside
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.32f * 1,	0.8f * 1);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 6,	0.32f * 3,	0.8f * 1);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 1);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.32f * 1,	0.8f * 1);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 6,	0.32f * 1,	0.8f * 1);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 6,	0.32f * 3,	0.8f * 1);

		// Front Slope
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 0,	0.32f * 3,	0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,	0.81f,		0.8f * 4);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 3,	0.32f * 3,	0.8f * 4);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 0,	0.32f * 3,	0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 0,	0.81f,		0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,	0.81f,		0.8f * 4);

		// Front Double Slope
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 0,	0.81f,		0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,	0.0f,		0.8f * 3);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 3,	0.81f,		0.8f * 4);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 3,	0.81f,		0.8f * 4);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,	0.0f,		0.8f * 3);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 6,	0.0f,		0.8f * 4);

		// Back Face
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 3,	0.81f,		0.8f * 0);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 6,	0.96f,		0.8f * 0);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 6,	0.0f,		0.8f * 0);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 3,	0.96f,		0.8f * 0);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.8f * 6,	0.96f,		0.8f * 0);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 3,	0.81f,		0.8f * 0);

		// Back Inside
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.32f * 1,	0.8f * 3);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 6,	0.32f * 3,	0.8f * 3);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.32f * 1,	0.8f * 3);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 6,	0.32f * 3,	0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 6,	0.32f * 1,	0.8f * 3);

		// Front Slope
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 0,	0.32f * 3,	0.8f * 1);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 3,	0.32f * 3,	0.8f * 0);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,	0.81f,		0.8f * 0);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 0,	0.32f * 3,	0.8f * 1);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,	0.81f,		0.8f * 0);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 0,	0.81f,		0.8f * 1);

		// Back Double Slope
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 0,	0.81f,		0.8f * 1);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 3,	0.81f,		0.8f * 0);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,	0.0f,		0.8f * 1);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 3,	0.81f,		0.8f * 0);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 6,	0.0f,		0.8f * 0);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,	0.0f,		0.8f * 1);

		// Top Face Top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f * 0,	0.32f * 3,	0.8f * 1);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.8f * 6,	0.32f * 3,	0.8f * 1);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 3,	0.32f * 3,	0.8f * 0);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f * 3,	0.32f * 3,	0.8f * 0);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.8f * 6,	0.32f * 3,	0.8f * 1);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 6,	0.32f * 3,	0.8f * 0);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f * 0,	0.32f * 3,	0.8f * 3);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.8f * 3,	0.32f * 3,	0.8f * 4);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 6,	0.32f * 3,	0.8f * 3);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f * 3,	0.32f * 3,	0.8f * 4);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.8f * 6,	0.32f * 3,	0.8f * 4);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 6,	0.32f * 3,	0.8f * 3);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f * 0,	0.32f * 3,	0.8f * 3);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 3);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 1);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f * 0,	0.32f * 3,	0.8f * 3);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 1);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 0,	0.32f * 3,	0.8f * 1);

		// Top Face Center
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f * 2,	0.32f * 2,	0.8f * 3);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.8f * 3,	0.32f * 2,	0.8f * 3);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 3,	0.32f * 2,	0.8f * 1);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f * 2,	0.32f * 2,	0.8f * 3);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.8f * 3,	0.32f * 2,	0.8f * 1);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 2,	0.32f * 2,	0.8f * 1);

		// Top Face Bottom
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f * 3,	0.32f * 1,	0.8f * 3);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.8f * 6,	0.32f * 1,	0.8f * 3);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 6,	0.32f * 1,	0.8f * 1);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f * 3,	0.32f * 1,	0.8f * 3);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.8f * 6,	0.32f * 1,	0.8f * 1);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 3,	0.32f * 1,	0.8f * 1);

		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f * 3,	0.0f,		0.8f * 3);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 3,	0.0f,		0.8f * 1);
		glTexCoord2f(1.0f, 0.5f);	glVertex3f( 0.8f * 6,	0.0f,		0.8f * 0);

		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f * 3,	0.0f,		0.8f * 3);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.8f * 6,	0.0f,		0.8f * 0);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 6,	0.0f,		0.8f * 4);

		// Right face right
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 6,	0.32f,		0.8f * 1);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 6,	0.96f,		0.8f * 0);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 6,	0.96f,		0.8f * 1);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 6,	0.32f,		0.8f * 1);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 6,	0.0f,		0.8f * 0);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 6,	0.96f,		0.8f * 0);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 6,	0.32f,		0.8f * 1);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 6,	0.32f,		0.8f * 3);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 6,	0.0f,		0.8f * 0);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 6,	0.32f,		0.8f * 3);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 6,	0.0f,		0.8f * 4);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 6,	0.0f,		0.8f * 0);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 6,	0.96f,		0.8f * 4);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 6,	0.32f,		0.8f * 3);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 6,	0.96f,		0.8f * 3);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 6,	0.96f,		0.8f * 4);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 6,	0.0f,		0.8f * 4);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 6,	0.32f,		0.8f * 3);

		// Right face inside right
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 3,	0.64f,		0.8f * 3);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 3,	0.32f,		0.8f * 3);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 3,	0.64f,		0.8f * 1);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 3,	0.32f,		0.8f * 3);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 3,	0.32f,		0.8f * 1);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 3,	0.64f,		0.8f * 1);

		// Right face inside left
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.96f,		0.8f * 3);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 2,	0.64f,		0.8f * 3);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.96f,		0.8f * 1);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.64f,		0.8f * 3);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 2,	0.64f,		0.8f * 1);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.96f,		0.8f * 1);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.81f,		0.8f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.0f,		0.81f,		0.8f * 3);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,		0.96f,		0.8f * 3);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.81f,		0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,		0.96f,		0.8f * 3);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.0f,		0.96f,		0.8f);

		// Left Slope
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.81f,		0.8f * 3);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 3,	0.0f,		0.8f * 1);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 3,	0.0f,		0.8f * 3);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,	0.0f,		0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,		0.81f,		0.8f * 3);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.0f,		0.81f,		0.8f);

	} else if (iNumber == 3046) {

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.0f,		0.0f,		0.8f * 2);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,	0.0f,		0.8f * 2);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.0f,		0.8f * 2);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 2);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 2);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 1,	0.32f * 3,	0.8f * 2);

		// Front Slope
		glNormal3f( 0.0f, 0.5f, 0.5f);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 1,	0.32f * 3,	0.8f * 1);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.0f,		0.32f * 3,	0.8f * 1);

		// Back Face
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.0f,		0.0f);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.0f,		0.32f * 3,	0.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.8f * 2,	0.0f,		0.0f);

		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.32f * 3,	0.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.0f);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.0f,		0.0f);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.0f,		0.32f * 3,	0.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 2);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.0f,		0.32f * 3,	0.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.0f,		0.32f * 3,	0.8f);
		glTexCoord2f(1.0f, 0.5f);	glVertex3f( 0.8f,		0.32f * 3,	0.8f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.8f,		0.32f * 3,	0.8f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f,		0.32f * 3,	0.8f * 2);
		glTexCoord2f(1.0f, 0.5f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 2);

		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.0f,		0.0f,		0.0f);
		glTexCoord2f(1.0f, 0.5f);	glVertex3f( 0.8f * 2,	0.0f,		0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.0f,		0.8f * 2);

		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.5f);	glVertex3f( 0.0f,		0.0f,		0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.0f,		0.8f * 2);
		glTexCoord2f(0.0f, 0.75f);	glVertex3f( 0.0f,		0.0f,		0.8f * 2);

		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.0f,		0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 2);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.0f,		0.8f * 2);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f * 2,	0.0f,		0.0f);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,	0.32f * 3,	0.8f * 2);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.0f,		0.0f);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.0f,		0.0f,		0.8f * 2);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.0f,		0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.0f,		0.32f * 3,	0.0f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 1.0f);	glVertex3f( 0.0f,		0.32f * 3,	0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.32f * 3,	0.8f);

		// Left Slope
		glNormal3f(-0.5f, 0.5f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,		0.15f,		0.8f * 2);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f,		0.32f * 3,	0.8f * 2);
		glTexCoord2f(1.0f, 0.75f);	glVertex3f( 0.8f,		0.32f * 3,	0.8f);

	} else if (iNumber == 30355) {

		// Slope Face
		glNormal3f( -0.316f, 0.0f, 0.949f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0,					0.0f,				0.8f * 3);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 9,			0.32f,				0.8f * 6);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.8f * 3);

		glNormal3f( -0.316f, 0.0f, 0.949f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 9,			0.0f,				0.8f * 6);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 9,			0.32f,				0.8f * 6);

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * 9,			0.0f,				0.8f * 6);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 12,			0.32f,				0.8f * 6);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 9,			0.32f,				0.8f * 6);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * 9,			0.0f,				0.8f * 6);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 12,			0.0f,				0.8f * 6);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 12,			0.32f,				0.8f * 6);

		// Back Face
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 12,			0.32f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 12,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 12,			0.0f,				0.0f);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.8f * 3);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 12,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 9,			0.32f,				0.8f * 6);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 12,			0.32f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 9,			0.32f,				0.8f * 6);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f * 12,			0.32f,				0.8f * 6);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 12,			0.32f,				0.0f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 12,			0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f * 3);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 9,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 12,			0.0f,				0.8f * 6);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 9,			0.0f,				0.8f * 6);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 12,			0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f * 12,			0.0f,				0.8f * 6);

		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 12,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 12,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 12,			0.32f,				0.8f * 6);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 12,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 12,			0.32f,				0.8f * 6);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 12,			0.0f,				0.8f * 6);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.8f * 3);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,				0.32f,				0.8f * 3);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f * 3);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.0f);

	} else if (iNumber == 30356) {

		// Slope Face
		glNormal3f( -0.316f, 0.0f, -0.949f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0,					0.0f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.8f * 3);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 9,			0.32f,				0.0f);

		glNormal3f( -0.316f, 0.0f, -0.949f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f * 3);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 9,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 9,			0.0f,				0.0f);

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f * 6);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 12,			0.32f,				0.8f * 6);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.8f * 6);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f * 6);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 12,			0.0f,				0.8f * 6);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 12,			0.32f,				0.8f * 6);

		// Back Face
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * 9,			0.0f,				0.8f * 0);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 9,			0.32f,				0.8f * 0);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 12,			0.32f,				0.8f * 0);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * 9,			0.0f,				0.8f * 0);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 12,			0.32f,				0.8f * 0);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 12,			0.0f,				0.8f * 0);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.8f * 6);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 9,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f * 3);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.8f * 6);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 12,			0.32f,				0.8f * 6);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 9,			0.32f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f * 9,			0.32f,				0.8f * 0);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 12,			0.32f,				0.8f * 6);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 12,			0.32f,				0.0f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f * 6);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.8f * 3);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 9,			0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f * 6);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 9,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 12,			0.0f,				0.8f * 6);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f * 9,			0.0f,				0.8f * 0);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 12,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 12,			0.0f,				0.8f * 6);

		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 12,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 12,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 12,			0.32f,				0.8f * 6);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 12,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 12,			0.32f,				0.8f * 6);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 12,			0.0f,				0.8f * 6);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.8f * 3);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.8f * 6);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f * 6);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.8f * 3);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f * 6);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.8f * 3);

	} else if (iNumber == 3933) {

		// Slope Face
		glNormal3f( -0.316f, 0.0f, 0.949f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0,					0.0f,				0.8f * 1);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 7,			0.32f,				0.8f * 4);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.8f * 1);

		glNormal3f( -0.316f, 0.0f, 0.949f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f * 1);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 7,			0.0f,				0.8f * 4);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 7,			0.32f,				0.8f * 4);

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * 7,			0.0f,				0.8f * 3);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 8,			0.32f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 7,			0.32f,				0.8f * 3);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * 7,			0.0f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 8,			0.0f,				0.8f * 3);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 8,			0.32f,				0.8f * 3);

		// Back Face
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 8,			0.32f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 8,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 8,			0.0f,				0.0f);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 7,			0.32f,				0.8f * 4);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 7,			0.32f,				0.8f * 3);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 7,			0.32f,				0.8f * 3);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 7,			0.32f,				0.8f * 3);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 8,			0.32f,				0.8f * 3);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 8,			0.32f,				0.8f * 3);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 8,			0.32f,				0.0f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 7,			0.0f,				0.8f * 3);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 7,			0.0f,				0.8f * 4);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 7,			0.0f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.8f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 8,			0.0f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 7,			0.0f,				0.8f * 3);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 8,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 8,			0.0f,				0.8f * 3);

		// Right face big
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 8,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 8,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 8,			0.32f,				0.8f * 3);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 8,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 8,			0.32f,				0.8f * 3);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 8,			0.0f,				0.8f * 3);

		// Right face small
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 7,			0.0f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 7,			0.32f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 7,			0.32f,				0.8f * 4);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 7,			0.0f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 7,			0.32f,				0.8f * 4);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 7,			0.0f,				0.8f * 4);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.8f * 1);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,				0.32f,				0.8f * 1);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f * 1);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.0f);

	} else if (iNumber == 3934) {

		// Slope Face
		glNormal3f( -0.316f, 0.0f, -0.949f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0,					0.0f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.8f * 3);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 7,			0.32f,				0.0f);

		glNormal3f( -0.316f, 0.0f, -0.949f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f * 3);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 7,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 7,			0.0f,				0.0f);

		// Back Face
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * 7,			0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 7,			0.32f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 8,			0.32f,				0.8f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * 7,			0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 8,			0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 8,			0.0f,				0.8f);

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f * 4);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 8,			0.32f,				0.8f * 4);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.8f * 4);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f * 4);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 8,			0.0f,				0.8f * 4);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 8,			0.32f,				0.8f * 4);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.8f * 3);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 7,			0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 7,			0.32f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f * 4);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 7,			0.32f,				0.8f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.8f * 4);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 8,			0.32f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 7,			0.32f,				0.8f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.8f * 4);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 8,			0.32f,				0.8f * 4);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 8,			0.32f,				0.8f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f * 3);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 7,			0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 7,			0.0f,				0.8f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f * 3);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 7,			0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.8f * 4);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f * 4);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 7,			0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 8,			0.0f,				0.8f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f * 4);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 8,			0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 8,			0.0f,				0.8f * 4);

		// Right face big
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 8,			0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 8,			0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 8,			0.32f,				0.8f * 4);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 8,			0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 8,			0.32f,				0.8f * 4);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 8,			0.0f,				0.8f * 4);

		// Right face small
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 8,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 8,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 8,			0.32f,				0.8f * 1);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 8,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 8,			0.32f,				0.8f * 1);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 8,			0.0f,				0.8f * 1);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.8f * 3);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.8f * 4);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f * 4);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.8f * 3);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f * 4);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.8f * 3);

	} else if (iNumber == 3185) {

		// Front Face Low
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.8f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 4,			0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f,				0.8f);

		// Front Face Top
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.5f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f * 6,			0.5f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 6,			0.5f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.5f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 4,			0.32f,				0.5f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f * 6,			0.5f);

		// Back Face Low
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 4,			0.0f,				0.0f);

		// Back Face Top
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.3f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 6,			0.3f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f * 6,			0.3f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.3f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f * 6,			0.3f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 4,			0.32f,				0.3f);

		// Top Face Bottom
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.0f);

		// Top Face Top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 6,			0.5f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 6,			0.3f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 6,			0.3f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 6,			0.5f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 6,			0.5f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 6,			0.3f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.0f,				0.8f);

		// Right face Bottom
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 4,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 4,			0.0f,				0.8f);

		// Right face Top
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.32f,				0.3f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 4,			0.32f * 6,			0.3f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 6,			0.5f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.32f,				0.3f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 6,			0.5f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 4,			0.32f,				0.5f);

		// Left face Bottom
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);

		// Left face Top
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.3f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 6,			0.5f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f * 6,			0.3f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.3f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.32f,				0.5f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 6,			0.5f);
	} else if (iNumber == 4859) {

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f,				0.0f,				2.4f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,			0.32f,				2.4f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.32f,				2.4f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f,				0.0f,				2.4f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 3,			0.0f,				2.4f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 3,			0.32f,				2.4f);

		// Back Face Left
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.0f,				0.0f);

		// Back Face Center
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.32f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 2.4f,				0.32f,				0.8f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f,				0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 2.4f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 2.4f,				0.0f,				0.8f);

		// Back Face Right
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 2.4f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 2.4f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 3.2f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 2.4f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 3.2f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 3.2f,				0.0f,				0.0f);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.32f,				2.4f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.32f,				2.4f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.32f,				2.4f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f,				0.32f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.32f,				2.4f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,			0.32f,				0.8f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f * 3,			0.32f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.32f,				2.4f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.0f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.0f,				2.4f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f,				0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.0f,				2.4f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.0f,				2.4f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,			0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.0f,				2.4f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f * 3,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 3,			0.0f,				2.4f);

		// Right face Inside
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,			0.32f,				0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,			0.32f,				0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f,			0.0f,				0.8f);

		// Right face Slope
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 4,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,			0.32f,				2.4f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 3,			0.32f,				2.4f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 3,			0.0f,				2.4f);

		// Left face Inside
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 2.4f,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 2.4f,			0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 2.4f,			0.32f,				0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 2.4f,			0.0f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 2.4f,			0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 2.4f,			0.32f,				0.8f);

		// Left face Slope
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,			0.32f,				2.4f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,			0.32f,				0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,			0.0f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f,			0.0f,				2.4f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,			0.32f,				2.4f);

	} else if (iNumber == 4070) {

		// Front Face Low
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.15f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.15f,				0.8f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.15f,				0.8f);

		// Front Face Top
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.15f,				0.65f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.32f * 3,			0.65f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 3,			0.65f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.15f,				0.65f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.15f,				0.65f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.32f * 3,			0.65f);

		// Back Face
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 3,			0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.32f * 3,			0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.32f * 3,			0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.0f,				0.0f);

		// Top Face Bottom
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.15f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.15f,				0.65f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.15f,				0.65f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.15f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.15f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.15f,				0.65f);

		// Top Face Top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.65f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.32f * 3,			0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.65f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.32f * 3,			0.65f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.32f * 3,			0.0f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.0f,				0.8f);

		// Right face Bottom
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f,				0.15f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.15f,				0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.15f,				0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f,				0.0f,				0.8f);

		// Right face Top
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f,				0.15f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f,				0.32f * 3,			0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.32f * 3,			0.65f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f,				0.15f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.32f * 3,			0.65f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f,				0.15f,				0.65f);

		// Left face Bottom
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.15f,				0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.15f,				0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.15f,				0.8f);

		// Left face Top
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.15f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.65f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.15f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.15f,				0.65f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.65f);
	} else if (iNumber == 3633) {

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.96f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.96f,				0.8f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 4,			0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.96f,				0.8f);

		// Back Face Low
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 4,			0.0f,				0.0f);

		// Back Face Top
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 3,			0.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f * 3,			0.6f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 4,			0.32f,				0.6f);

		// Top Face Bottom
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.0f);

		// Top Face Top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.6f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 3,			0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 3,			0.6f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.0f,				0.8f);

		// Right face Bottom
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 4,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 4,			0.0f,				0.8f);

		// Right face Top
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 4,			0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 3,			0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 3,			0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 4,			0.32f,				0.8f);

		// Left face Bottom
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);

		// Left face Top
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.6f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);

	} else if (iNumber == 6231) {

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.96f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.96f,				0.8f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.96f,				0.8f);

		// Back Face Low
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.0f,				0.0f);

		// Back Face Top
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 3,			0.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.6f,				0.32f * 3,			0.6f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.6f,				0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.6f,				0.32f,				0.6f);

		// Back Face Top Small
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.6f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.6f,				0.32f * 3,			0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.32f * 3,			0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.6f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.32f * 3,			0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.32f,				0.0f);

		// Top Face Bottom
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.6f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.6f,				0.32f,				0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.6f,				0.32f,				0.0f);

		// Top Face Top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.6f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.32f * 3,			0.6f);

		// Top Face Top Small
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.6f,				0.32f * 3,			0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.32f * 3,			0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.6f,				0.32f * 3,			0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.6f,				0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.32f * 3,			0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.32f * 3,			0.0f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.0f,				0.8f);

		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f,				0.32f * 3,			0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.32f * 3,			0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.32f * 3,			0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f,				0.0f,				0.8f);

		// Left face Bottom
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);

		// Left face Top
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.6f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);

		// Left face inside
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.6f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.6f,				0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.6f,				0.32f * 3,			0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.6f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.6f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.6f,				0.32f * 3,			0.6f);

	} else if (iNumber == 4865) {

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.96f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.96f,				0.8f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 2,			0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.96f,				0.8f);

		// Back Face Low
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 2,			0.0f,				0.0f);

		// Back Face Top
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 3,			0.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f * 3,			0.6f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 2,			0.32f,				0.6f);

		// Top Face Bottom
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.0f);

		// Top Face Top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.6f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 3,			0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 3,			0.6f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.0f,				0.8f);

		// Right face Bottom
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 2,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 2,			0.0f,				0.8f);

		// Right face Top
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 2,			0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 3,			0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 3,			0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 2,			0.32f,				0.8f);

		// Left face Bottom
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);

		// Left face Top
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.6f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);

	} else if (iNumber == 4864) {

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f * 6,			0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 6,			0.8f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 2,			0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f * 6,			0.8f);

		// Back Face Low
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 2,			0.0f,				0.0f);

		// Back Face Middle
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				1.77f,				0.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			1.77f,				0.6f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			1.77f,				0.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 2,			0.32f,				0.6f);

		// Back Face Top
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				1.77f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 6,			0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f * 6,			0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				1.77f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f * 6,			0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 2,			1.77f,				0.0f);

		// Top Face Bottom
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.0f);

		// Top Face Top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 6,			0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 6,			0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 6,			0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 6,			0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 6,			0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 6,			0.0f);

		// Bottom Face Bottom
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.0f,				0.8f);

		// Bottom Face Top
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				1.77f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				1.77f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			1.77f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				1.77f,				0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			1.77f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			1.77f,				0.6f);

		// Right face Bottom
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 2,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 2,			0.0f,				0.8f);

		// Right face Center
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 2,			1.77f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			1.77f,				0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			1.77f,				0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 2,			0.32f,				0.8f);

		// Right face Top
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			1.77f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 2,			0.32f * 6,			0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 6,			0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			1.77f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 6,			0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 2,			1.77f,				0.8f);

		// Left face Bottom
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);

		// Left face Center
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				1.77f,				0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				1.77f,				0.6f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				1.77f,				0.8f);

		// Left face Top
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				1.77f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 6,			0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f * 6,			0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				1.77f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				1.77f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 6,			0.8f);

	} else if (iNumber == 30413) {

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.96f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.96f,				0.8f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 4,			0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.96f,				0.8f);

		// Back Face Low
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 4,			0.0f,				0.0f);

		// Back Face Top
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 3,			0.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f * 3,			0.6f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 4,			0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 4,			0.32f,				0.6f);

		// Top Face Bottom
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.0f);

		// Top Face Top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.6f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 3,			0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 3,			0.6f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.0f,				0.8f);

		// Right face Bottom
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 4,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f,				0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 4,			0.0f,				0.8f);

		// Right face Top
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 4,			0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 3,			0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 4,			0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 4,			0.32f * 3,			0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 4,			0.32f,				0.8f);

		// Left face Bottom
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);

		// Left face Top
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.6f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
	} else if (iNumber == 4865) {

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.96f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.96f,				0.8f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 2,			0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.96f,				0.8f);

		// Back Face Low
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 2,			0.0f,				0.0f);

		// Back Face Top
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * 3,			0.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f * 3,			0.6f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * 2,			0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * 2,			0.32f,				0.6f);

		// Top Face Bottom
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.0f);

		// Top Face Top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.6f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 3,			0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 3,			0.6f);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * 2,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.0f,				0.8f);

		// Right face Bottom
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 2,			0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f,				0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 2,			0.0f,				0.8f);

		// Right face Top
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * 2,			0.32f * 3,			0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 3,			0.8f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * 2,			0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * 2,			0.32f * 3,			0.8f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 2,			0.32f,				0.8f);

		// Left face Bottom
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f,				0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f,				0.8f);

		// Left face Top
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.32f * 3,			0.6f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.32f,				0.6f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.32f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * 3,			0.8f);
	} else if (iNumber == 3788) {

		// Front Face Left
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				1.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.64f,				1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.64f,				1.6f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.0f,				1.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.64f,				1.6f);

		// Front Face Left Back
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.49f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.49f,				0.0f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.49f,				0.0f);

		// Front Face Center
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f,				0.0f,				1.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 2.4f,				0.32f,				1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.32f,				1.6f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f,				0.0f,				1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 2.4f,				0.0f,				1.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 2.4f,				0.32f,				1.6f);

		// Front Face Right
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 2.4f,				0.0f,				1.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 3.2f,				0.64f,				1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 2.4f,				0.64f,				1.6f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 2.4f,				0.0f,				1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 3.2f,				0.0f,				1.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 3.2f,				0.64f,				1.6f);

		// Front Face Right Back
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 2.4f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 3.2f,				0.49f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 2.4f,				0.49f,				0.0f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 2.4f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 3.2f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 3.2f,				0.49f,				0.0f);

		// Back Face Left
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.64f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.64f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.64f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.0f,				0.0f);

		// Back Face Left Front
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.64f,				1.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.64f,				1.6f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				1.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f,				0.64f,				1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.0f,				1.6f);

		// Back Face Center
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 2.4f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 2.4f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 2.4f,				0.0f,				0.0f);

		// Back Face Right
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 2.4f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 2.4f,				0.64f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 3.2f,				0.64f,				0.0f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 2.4f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 3.2f,				0.64f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 3.2f,				0.0f,				0.0f);

		// Back Face Right Front
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 2.4f,				0.0f,				1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 2.4f,				0.64f,				1.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 3.2f,				0.64f,				1.6f);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 2.4f,				0.0f,				1.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 3.2f,				0.64f,				1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 3.2f,				0.0f,				1.6f);

		// Top Face Left
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.64f,				1.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.64f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.64f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.64f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.64f,				1.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.64f,				0.0f);

		// Top Face Center
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f,				0.32f,				1.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 2.4f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.32f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 2.4f,				0.32f,				1.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 2.4f,				0.32f,				0.0f);

		// Top Face Right
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 2.4f,				0.64f,				1.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 3.2f,				0.64f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 2.4f,				0.64f,				0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 2.4f,				0.64f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.64f,				1.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 3.2f,				0.64f,				0.0f);

		// Bottom Face Left
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.49f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.49f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.49f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.49f,				1.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f,				0.49f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.49f,				1.6f);

		// Bottom Face Center
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f,				0.0f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 2.4f,				0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f,				0.0f,				1.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 2.4f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 2.4f,				0.0f,				1.6f);

		// Bottom Face Right
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 2.4f,				0.49f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 2.4f,				0.49f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 3.2f,				0.49f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 2.4f,				0.49f,				1.6f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 3.2f,				0.49f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.49f,				1.6f);

		// Right face Back Inside
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.49f,				1.6f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.0f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				1.45f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.49f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				1.45f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.44f,				1.15f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.49f,				1.6f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.44f,				1.15f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.49f,				0.0f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.44f,				1.15f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.44f,				0.45f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.49f,				0.0f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.49f,				0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.44f,				0.45f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.15f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.49f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.15f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);

		// Right face Back
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f,				0.64f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.64f,				1.6f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.64f,				1.6f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f,				0.32f,				1.6f);

		// Right face Inside
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 2.4f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 2.4f,				0.49f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 2.4f,				0.49f,				1.6f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 2.4f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 2.4f,				0.49f,				1.6f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 2.4f,				0.0f,				1.6f);

		// Right face Front
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 3.2f,				0.64f,				1.6f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 3.2f,				0.0f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.0f,				1.45f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 3.2f,				0.64f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.0f,				1.45f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 3.2f,				0.44f,				1.15f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 3.2f,				0.64f,				1.6f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 3.2f,				0.44f,				1.15f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.64f,				0.0f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 3.2f,				0.44f,				1.15f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 3.2f,				0.44f,				0.45f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.64f,				0.0f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.64f,				0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 3.2f,				0.44f,				0.45f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 3.2f,				0.0f,				0.15f);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.64f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 3.2f,				0.0f,				0.15f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 3.2f,				0.0f,				0.0f);

		// Left face Back Inside
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 3.2f,				0.49f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.0f,				1.45f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 3.2f,				0.0f,				1.6f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 3.2f,				0.49f,				1.6f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 3.2f,				0.44f,				1.15f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.0f,				1.45f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 3.2f,				0.49f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.49f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 3.2f,				0.44f,				1.15f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 3.2f,				0.44f,				1.15f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.49f,				0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 3.2f,				0.44f,				0.45f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.49f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 3.2f,				0.0f,				0.15f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 3.2f,				0.44f,				0.45f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 3.2f,				0.49f,				0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 3.2f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 3.2f,				0.0f,				0.15f);

		// Left face Back
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 2.4f,				0.32f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 2.4f,				0.64f,				1.6f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 2.4f,				0.64f,				0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 2.4f,				0.32f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 2.4f,				0.32f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 2.4f,				0.64f,				1.6f);

		// Left face Inside
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.49f,				1.6f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f,				0.49f,				0.0f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f,				0.0f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f,				0.49f,				1.6f);

		// Left face Front
		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.64f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				1.45f);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.0f,				0.0f,				1.6f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.64f,				1.6f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.44f,				1.15f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				1.45f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.64f,				1.6f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.64f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.44f,				1.15f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.44f,				1.15f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.64f,				0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.44f,				0.45f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.64f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.15f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.44f,				0.45f);

		glNormal3f( -1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.64f,				0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.0f,				0.0f,				0.15f);
	}
	glEnd();
	glEndList();

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::createBrickWithoutCorner
*******************************************************************************/
int LGBrickLibEntry::createBrickWithoutCorner (int iWidth, int iLength, int iHeight) {

	/*******************************************************************************
	* Create Displaylist part
	*******************************************************************************/
	LGBrickLibEntry::iDisplayList = glGenLists(1);
	glNewList (LGBrickLibEntry::iDisplayList, GL_COMPILE);

	glBegin(GL_TRIANGLES);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.0f,				0.8f * iWidth);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * (iLength-1),  0.32f * iHeight,	0.8f * iWidth);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.0f,				0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.0f,				0.8f * iWidth);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);

		// Slope Face
		glNormal3f( -0.707f, 0.0f, 0.707f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0,					0.0f,				0.8f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * iHeight,	0.8f);

		glNormal3f( -0.707f, 0.0f, 0.707f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * (iLength-1),	0.0f,				0.8f * iWidth);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.8f * iWidth);

		// Back Face
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * iHeight,	0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.0f,				0.0f);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * iHeight,	0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.32f * iHeight,	0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * iHeight,	0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * iHeight,	0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.0f,				0.0f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.0f,				0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * iLength,		0.0f,				0.8f * iWidth);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,				0.8f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * iLength,		0.0f,				0.8f * iWidth);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * (iLength-1),	0.0f,				0.8f * iWidth);

		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,  0.0f,  0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,  0.0f,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.8f * iLength,  0.0f,  0.8f * iWidth);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.0f,  0.8f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.32f * iHeight,  0.8f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.32f * iHeight,  0.8f);
		glTexCoord2f(0.25f, 0.5f); glVertex3f( 0.0f,  0.32f * iHeight,  0.0f);
	glEnd();
	glEndList();

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::createBrickWithout2Corners
*******************************************************************************/
int LGBrickLibEntry::createBrickWithout2Corners (int iWidth, int iLength, int iHeight) {

	/*******************************************************************************
	* Create Displaylist part
	*******************************************************************************/
	LGBrickLibEntry::iDisplayList = glGenLists(1);
	glNewList (LGBrickLibEntry::iDisplayList, GL_COMPILE);

	glBegin(GL_TRIANGLES);

		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.0f,				0.8f * iWidth);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * (iLength-1),  0.32f * iHeight,	0.8f * iWidth);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.0f,				0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.0f,				0.8f * iWidth);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);

		// Front Slope Face
		glNormal3f( -0.707f, 0.0f, 0.707f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0,					0.0f,				0.8f * (iWidth/2+1));
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * iHeight,	0.8f * (iWidth/2+1));

		glNormal3f( -0.707f, 0.0f, 0.707f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f * (iWidth/2+1));
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * (iLength-1),	0.0f,				0.8f * iWidth);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.8f * iWidth);

		// Back Face
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.0f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.0f,				0.0f);

		// Back Slope Face
		glNormal3f( -0.707f, 0.0f, -0.707f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0,					0.0f,				0.8f * (iWidth/2-1));
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.0f,				0.32f * iHeight,	0.8f * (iWidth/2-1));
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.0f);

		glNormal3f( -0.707f, 0.0f, -0.707f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f * (iWidth/2-1));
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * (iLength-1),	0.0f,				0.0f);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * iHeight,	0.8f * (iWidth/2-1));
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * iHeight,	0.8f * (iWidth/2-1));
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * iHeight,	0.8f * (iWidth/2+1));
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * iHeight,	0.8f * (iWidth/2+1));
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.0f);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * iHeight,	0.8f * (iWidth/2+1));
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);

		// Bottom Face
		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,	0.8f * (iWidth/2-1));
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * (iLength-1),	0.0f,	0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.0f,	0.0f);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,	0.8f * (iWidth/2-1));
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.0f,	0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,	0.8f * (iWidth/2+1));

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,	0.8f * (iWidth/2+1));
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.0f,	0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.0f,	0.8f * iWidth);

		glNormal3f( 0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.0f,	0.8f * (iWidth/2+1));
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * iLength,		0.0f,	0.8f * iWidth);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * (iLength-1),	0.0f,	0.8f * iWidth);

		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,  0.0f,  0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);

		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,  0.0f,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.8f * iLength,  0.0f,  0.8f * iWidth);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.0f,  0.0f,			0.8f * (iWidth/2-1));
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.0f,  0.0f,			0.8f * (iWidth/2+1));
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.32f * iHeight,	0.8f * (iWidth/2+1));

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.0f,  0.0f,			0.8f * (iWidth/2-1));
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.32f * iHeight,	0.8f * (iWidth/2+1));
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,  0.32f * iHeight,	0.8f * (iWidth/2-1));
	glEnd();
	glEndList();

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::createSlope
*******************************************************************************/
int LGBrickLibEntry::createSlope (int iWidth, int iLength, int iHeight) {
	LGVertex3f	vNormal;	// Normal
	GLfloat		fProduct;	// Product

	/*******************************************************************************
	* Create Displaylist part
	*******************************************************************************/
	LGBrickLibEntry::iDisplayList = glGenLists(1);
	glNewList (LGBrickLibEntry::iDisplayList, GL_COMPILE);

	glBegin(GL_TRIANGLES);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.2f,				0.8f * iWidth);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * (iLength-1),  0.32f * iHeight,	0.8f * iWidth);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.2f,				0.8f * iWidth);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,		0.0f,				0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.2f,				0.8f * iWidth);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.0f,				0.8f * iWidth);

		// Back Face
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.2f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * (iLength-1),  0.32f * iHeight,	0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.2f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,		0.0f,				0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.2f,				0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.0f,				0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.0f,				0.0f,				0.0f);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.0f);

		// Slope Face
		vNormal.fX = -0.96f;
		vNormal.fY = 0.8f * (iLength-1);
		vNormal.fZ = 0.0f;

		fProduct = (float)sqrt (vNormal.fX * vNormal.fX + vNormal.fY * vNormal.fY + vNormal.fZ * vNormal.fZ);

		glNormal3f( vNormal.fX / fProduct, vNormal.fY / fProduct, vNormal.fZ / fProduct);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.2f,				0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.0f,				0.2f,				0.8f * iWidth);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.8f * iWidth);

		glNormal3f( vNormal.fX / fProduct, vNormal.fY / fProduct, vNormal.fZ / fProduct);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.2f,				0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * (iLength-1),	0.32f * iHeight,	0.0f);

		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,  0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.8f * iLength,  0.0f,  0.8f * iWidth);

		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.8f * iLength,  0.0f,  0.8f * iWidth);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f,  0.0f,  0.8f * iWidth);

		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,  0.0f,  0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,  0.0f,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.8f * iLength,  0.0f,  0.8f * iWidth);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.0f,  0.8f * iWidth);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.2f,  0.8f * iWidth);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.2f,  0.8f * iWidth);
		glTexCoord2f(0.25f, 0.5f); glVertex3f( 0.0f,  0.2f,  0.0f);
	glEnd();
	glEndList();

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::createInvertedSlope
*******************************************************************************/
int LGBrickLibEntry::createInvertedSlope (int iWidth, int iLength, int iHeight) {
	LGVertex3f	vNormal;	// Normal
	GLfloat		fProduct;	// Product

	/*******************************************************************************
	* Create Displaylist part
	*******************************************************************************/
	LGBrickLibEntry::iDisplayList = glGenLists(1);
	glNewList (LGBrickLibEntry::iDisplayList, GL_COMPILE);

	glBegin(GL_TRIANGLES);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f * iHeight - 0.2f,	0.8f * iWidth);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.0f,					0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.0f,					0.8f * iWidth);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f * iHeight - 0.2f,	0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.0f,					0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,		0.8f * iWidth);

		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f * iHeight - 0.2f,	0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,		0.8f * iWidth);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f * iHeight,		0.8f * iWidth);

		// Back Face
		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f * iHeight - 0.2f,	0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.0f,					0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * (iLength-1),	0.0f,					0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f * iHeight - 0.2f,	0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,		0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.0f,					0.0f);

		glNormal3f( 0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f * iHeight - 0.2f,	0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,				0.32f * iHeight,		0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,		0.32f * iHeight,		0.0f);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * iHeight,	0.0f);
		glTexCoord2f(0.25f, 0.75f);	glVertex3f( 0.0f,				0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f);	glVertex3f( 0.0f,				0.32f * iHeight,	0.0f);
		glTexCoord2f(0.75f, 0.75f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.8f * iWidth);
		glTexCoord2f(0.75f, 0.5f);	glVertex3f( 0.8f * iLength,		0.32f * iHeight,	0.0f);

		// Slope Face
		vNormal.fX = -0.96f;
		vNormal.fY = -0.8f * (iLength-1);
		vNormal.fZ = 0.0f;

		fProduct = (float)sqrt (vNormal.fX * vNormal.fX + vNormal.fY * vNormal.fY + vNormal.fZ * vNormal.fZ);

		glNormal3f( vNormal.fX / fProduct, vNormal.fY / fProduct, vNormal.fZ / fProduct);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.0f,				0.32f * iHeight - 0.2f,	0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * (iLength-1),	0.0f,					0.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * (iLength-1),	0.0f,					0.8f * iWidth);

		glNormal3f( vNormal.fX / fProduct, vNormal.fY / fProduct, vNormal.fZ / fProduct);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.0f,				0.32f * iHeight - 0.2f,	0.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * (iLength-1),	0.0f,					0.8f * iWidth);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.0f,				0.32f * iHeight - 0.2f,	0.8f * iWidth);

		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.8f * (iLength-1),	0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.25f);	glVertex3f( 0.8f * iLength,		0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * iLength,		0.0f,  0.8f * iWidth);

		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f);	glVertex3f( 0.8f * (iLength-1),	0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * iLength,		0.0f,  0.8f * iWidth);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.8f * (iLength-1),	0.0f,  0.8f * iWidth);

		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,  0.0f,  0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,  0.0f,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.8f * iLength,  0.0f,  0.8f * iWidth);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.32f * iHeight - 0.2f,  0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.32f * iHeight - 0.2f,  0.8f * iWidth);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.32f * iHeight,  0.8f * iWidth);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.32f * iHeight - 0.2f,  0.0f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.32f * iHeight,  0.8f * iWidth);
		glTexCoord2f(0.25f, 0.5f); glVertex3f( 0.0f,  0.32f * iHeight,  0.0f);
	glEnd();
	glEndList();

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::createBasePlate
*******************************************************************************/
int LGBrickLibEntry::createBasePlate () {

	/*******************************************************************************
	* Create Displaylist part
	*******************************************************************************/
	LGBrickLibEntry::iDisplayList = glGenLists(1);
	glNewList (LGBrickLibEntry::iDisplayList, GL_COMPILE);

	glBegin(GL_TRIANGLES);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.0f,		0.0f,	0.0f);
		glTexCoord2f(0.0f, 0.0f);	glVertex3f( 0.0f,		0.0f,	0.8f * 32);
		glTexCoord2f(0.5f, 0.0f);	glVertex3f( 0.8f * 32,	0.0f,	0.8f * 32);

		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex3f( 0.0f,		0.0f,	0.0f);
		glTexCoord2f(0.5f, 0.0f);	glVertex3f( 0.8f * 32,	0.0f,	0.8f * 32);
		glTexCoord2f(0.5f, 1.0f);	glVertex3f( 0.8f * 32,	0.0f,	0.0f);

		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.5f, 0.0f);	glVertex3f( 0.0f,		0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex3f( 0.8f * 32,	0.0f,  0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 32,	0.0f,  0.8f * 32);

		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.5f, 0.0f);	glVertex3f( 0.0f,		0.0f,  0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex3f( 0.8f * 32,	0.0f,  0.8f * 32);
		glTexCoord2f(0.5f, 1.0f);	glVertex3f( 0.0f,		0.0f,  0.8f * 32);
	glEnd();
	glEndList();

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::createBrick
*******************************************************************************/
int LGBrickLibEntry::createBrick (int iWidth, int iLength, int iHeight) {

	/*******************************************************************************
	* Create Arrays part
	*******************************************************************************/
	LGBrickLibEntry::iNrOfVerticesArrays = 24;
	LGBrickLibEntry::vpVerticesArrays = new LGVertex3f[LGBrickLibEntry::iNrOfVerticesArrays];
	LGBrickLibEntry::tpTexturesArrays = new LGTextureuv[LGBrickLibEntry::iNrOfVerticesArrays];
	LGBrickLibEntry::vpNormalsArrays = new LGVertex3f[LGBrickLibEntry::iNrOfVerticesArrays];

	float fLength = 0.8f  * iLength;
	float fHeight = 0.32f * iHeight;
	float fWidth  = 0.8f  * iWidth;

	// Front face
	LGBrickLibEntry::setVertexNormal ( 0, 0.75f, 0.50f, fLength,	fHeight,	fWidth,	0.0f, 0.0f, 1.0f);	// Front top right
	LGBrickLibEntry::setVertexNormal ( 1, 0.25f, 0.50f, 0.0f,		fHeight,	fWidth,	0.0f, 0.0f, 1.0f);	// Front top left
	LGBrickLibEntry::setVertexNormal ( 2, 0.00f, 0.25f, 0.0f,		0.00f,		fWidth,	0.0f, 0.0f, 1.0f);	// Front bottom left
	LGBrickLibEntry::setVertexNormal ( 3, 1.00f, 0.25f, fLength,	0.00f,		fWidth,	0.0f, 0.0f, 1.0f);	// Front bottom right

	// Back face
	LGBrickLibEntry::setVertexNormal ( 4, 0.25f, 0.75f, 0.0f,		fHeight,	0.0f,	0.0f, 0.0f, -1.0f);	// Back top left
	LGBrickLibEntry::setVertexNormal ( 5, 0.75f, 0.75f, fLength,	fHeight,	0.0f,	0.0f, 0.0f, -1.0f);	// Back top right
	LGBrickLibEntry::setVertexNormal ( 6, 1.00f, 1.00f, fLength,	0.00f,		0.0f,	0.0f, 0.0f, -1.0f);	// Back bottom right
	LGBrickLibEntry::setVertexNormal ( 7, 0.00f, 1.00f, 0.0f,		0.00f,		0.0f,	0.0f, 0.0f, -1.0f);	// Back bottom left

	// Left face
	LGBrickLibEntry::setVertexNormal ( 8, 0.25f, 0.50f, 0.0f,		fHeight,	fWidth,	-1.0f, 0.0f, 0.0f);	// Front top left
	LGBrickLibEntry::setVertexNormal ( 9, 0.25f, 0.75f, 0.0f,		fHeight,	0.0f,	-1.0f, 0.0f, 0.0f);	// Back top left
	LGBrickLibEntry::setVertexNormal (10, 0.00f, 1.00f, 0.0f,		0.00f,		0.0f,	-1.0f, 0.0f, 0.0f);	// Back bottom left
	LGBrickLibEntry::setVertexNormal (11, 0.00f, 0.25f, 0.0f,		0.00f,		fWidth,	-1.0f, 0.0f, 0.0f);	// Front bottom left

	// Right face
	LGBrickLibEntry::setVertexNormal (12, 0.75f, 0.75f, fLength,	fHeight,	0.0f,	1.0f, 0.0f, 0.0f);	// Back top right
	LGBrickLibEntry::setVertexNormal (13, 0.75f, 0.50f, fLength,	fHeight,	fWidth,	1.0f, 0.0f, 0.0f);	// Front top right
	LGBrickLibEntry::setVertexNormal (14, 1.00f, 0.25f, fLength,	0.00f,		fWidth,	1.0f, 0.0f, 0.0f);	// Front bottom right
	LGBrickLibEntry::setVertexNormal (15, 1.00f, 1.00f, fLength,	0.00f,		0.0f,	1.0f, 0.0f, 0.0f);	// Back bottom right

	// Top face
	LGBrickLibEntry::setVertexNormal (16, 0.75f, 0.75f, fLength,	fHeight,	0.0f,	0.0f, 1.0f, 0.0f);	// Back top right
	LGBrickLibEntry::setVertexNormal (17, 0.25f, 0.75f, 0.0f,		fHeight,	0.0f,	0.0f, 1.0f, 0.0f);	// Back top left
	LGBrickLibEntry::setVertexNormal (18, 0.25f, 0.50f, 0.0f,		fHeight,	fWidth,	0.0f, 1.0f, 0.0f);	// Front top left
	LGBrickLibEntry::setVertexNormal (19, 0.75f, 0.50f, fLength,	fHeight,	fWidth,	0.0f, 1.0f, 0.0f);	// Front top right

	// Bottom face
	LGBrickLibEntry::setVertexNormal (20, 1.00f, 0.25f, fLength,	0.00f,		fWidth,	0.0f, -1.0f, 0.0f);	// Front bottom right
	LGBrickLibEntry::setVertexNormal (21, 0.00f, 0.25f, 0.0f,		0.00f,		fWidth,	0.0f, -1.0f, 0.0f);	// Front bottom left
	LGBrickLibEntry::setVertexNormal (22, 0.00f, 0.00f, 0.0f,		0.00f,		0.0f,	0.0f, -1.0f, 0.0f);	// Back bottom left
	LGBrickLibEntry::setVertexNormal (23, 1.00f, 0.00f, fLength,	0.00f,		0.0f,	0.0f, -1.0f, 0.0f);	// Back bottom right

	/*******************************************************************************
	* Create Elements part
	*******************************************************************************/
	LGBrickLibEntry::iNrOfVerticesElements = 10;
	LGBrickLibEntry::vpVerticesElements = new LGVertex3f[LGBrickLibEntry::iNrOfVerticesElements];
	LGBrickLibEntry::tpTexturesElements = new LGTextureuv[LGBrickLibEntry::iNrOfVerticesElements];
	LGBrickLibEntry::vpNormalsElements = new LGVertex3f[LGBrickLibEntry::iNrOfVerticesElements];
	LGBrickLibEntry::iNrOfFaces = 6;
	LGBrickLibEntry::fpFaces = new LGFace4s[LGBrickLibEntry::iNrOfFaces];

	// Set vertices
	LGBrickLibEntry::setVertex (0, 0.25f, 0.50f, 0.0f,				0.32f * iHeight,	0.8f * iWidth);	// Front top left
	LGBrickLibEntry::setVertex (1, 0.75f, 0.50f, 0.8f * iLength,	0.32f * iHeight,	0.8f * iWidth);	// Front top right
	LGBrickLibEntry::setVertex (2, 1.00f, 0.25f, 0.8f * iLength,	0.00f,				0.8f * iWidth);	// Front bottom right
	LGBrickLibEntry::setVertex (3, 0.00f, 0.25f, 0.0f,				0.00f,				0.8f * iWidth);	// Front bottom left

	LGBrickLibEntry::setVertex (4, 0.25f, 0.75f, 0.0f,				0.32f * iHeight,	0.0f);	// Back top left
	LGBrickLibEntry::setVertex (5, 0.75f, 0.75f, 0.8f * iLength,	0.32f * iHeight,	0.0f);	// Back top right
	LGBrickLibEntry::setVertex (6, 1.00f, 1.00f, 0.8f * iLength,	0.00f,				0.0f);	// Back bottom right
	LGBrickLibEntry::setVertex (7, 0.00f, 1.00f, 0.0f,				0.00f,				0.0f);	// Back bottom left

	LGBrickLibEntry::setVertex (8, 1.00f, 0.00f, 0.8f * iLength,	0.00f,				0.0f);	// Back bottom right
	LGBrickLibEntry::setVertex (9, 0.00f, 0.00f, 0.0f,				0.00f,				0.0f);	// Back bottom left

	// Set faces
	LGBrickLibEntry::setFace (0, 0, 3, 2, 1);	// Front
	LGBrickLibEntry::setFace (1, 1, 2, 6, 5);	// Right
	LGBrickLibEntry::setFace (2, 5, 6, 7, 4);	// Back
	LGBrickLibEntry::setFace (3, 4, 7, 3, 0);	// Left
	LGBrickLibEntry::setFace (4, 0, 1, 5, 4);	// Top
	LGBrickLibEntry::setFace (5, 2, 3, 9, 8);	// Bottom

	// Set normals
	LGBrickLibEntry::vpNormalsElements[0].fX = -1.0f;
	LGBrickLibEntry::vpNormalsElements[0].fY = 1.0f;
	LGBrickLibEntry::vpNormalsElements[0].fZ = 1.0f;

	LGBrickLibEntry::vpNormalsElements[1].fX = 1.0f;
	LGBrickLibEntry::vpNormalsElements[1].fY = 1.0f;
	LGBrickLibEntry::vpNormalsElements[1].fZ = 1.0f;

	LGBrickLibEntry::vpNormalsElements[2].fX = 1.0f;
	LGBrickLibEntry::vpNormalsElements[2].fY = -1.0f;
	LGBrickLibEntry::vpNormalsElements[2].fZ = 1.0f;

	LGBrickLibEntry::vpNormalsElements[3].fX = -1.0f;
	LGBrickLibEntry::vpNormalsElements[3].fY = -1.0f;
	LGBrickLibEntry::vpNormalsElements[3].fZ = 1.0f;

	LGBrickLibEntry::vpNormalsElements[4].fX = 1.0f;
	LGBrickLibEntry::vpNormalsElements[4].fY = 1.0f;
	LGBrickLibEntry::vpNormalsElements[4].fZ = 1.0f;

	LGBrickLibEntry::vpNormalsElements[5].fX = 1.0f;
	LGBrickLibEntry::vpNormalsElements[5].fY = 1.0f;
	LGBrickLibEntry::vpNormalsElements[5].fZ = 1.0f;

	LGBrickLibEntry::vpNormalsElements[6].fX = 1.0f;
	LGBrickLibEntry::vpNormalsElements[6].fY = 1.0f;
	LGBrickLibEntry::vpNormalsElements[6].fZ = 1.0f;

	LGBrickLibEntry::vpNormalsElements[7].fX = 1.0f;
	LGBrickLibEntry::vpNormalsElements[7].fY = 1.0f;
	LGBrickLibEntry::vpNormalsElements[7].fZ = 1.0f;

	LGBrickLibEntry::vpNormalsElements[8].fX = 1.0f;
	LGBrickLibEntry::vpNormalsElements[8].fY = 1.0f;
	LGBrickLibEntry::vpNormalsElements[8].fZ = 1.0f;

	LGBrickLibEntry::vpNormalsElements[9].fX = 1.0f;
	LGBrickLibEntry::vpNormalsElements[9].fY = 1.0f;
	LGBrickLibEntry::vpNormalsElements[9].fZ = 1.0f;

	/*******************************************************************************
	* Create Displaylist part
	*******************************************************************************/
	LGBrickLibEntry::iDisplayList = glGenLists(1);
	glNewList (LGBrickLibEntry::iDisplayList, GL_COMPILE);

	glBegin(GL_TRIANGLES);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.5f); glVertex3f( 0.0f,  0.0f,  0.8f * iWidth);
		glTexCoord2f(1.0f, 0.5f); glVertex3f( 0.8f * iLength,  0.0f,  0.8f * iWidth);
		glTexCoord2f(1.0f, 0.65f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.5f); glVertex3f( 0.0f,  0.0f,  0.8f * iWidth);
		glTexCoord2f(1.0f, 0.65f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);
		glTexCoord2f(0.0f, 0.65f); glVertex3f( 0.0f,  0.32f * iHeight,  0.8f * iWidth);

		// Back Face
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.5f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.65f); glVertex3f( 0.0f,  0.32f * iHeight,  0.0f);
		glTexCoord2f(0.0f, 0.65f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.0f);
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.5f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(0.0f, 0.65f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.0f);
		glTexCoord2f(0.0f, 0.5f); glVertex3f( 0.8f * iLength,  0.0f,  0.0f);

		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.32f * iHeight,  0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f,  0.32f * iHeight,  0.8f * iWidth);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.32f * iHeight,  0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.0f);

		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 0.8f * iLength,  0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.5f); glVertex3f( 0.8f * iLength,  0.0f,  0.8f * iWidth);
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.5f); glVertex3f( 0.8f * iLength,  0.0f,  0.8f * iWidth);
		glTexCoord2f(0.0f, 0.5f); glVertex3f( 0.0f,  0.0f,  0.8f * iWidth);

		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.5f, 0.65f); glVertex3f( 0.8f * iLength,  0.0f,  0.0f);
		glTexCoord2f(0.5f, 0.8f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.0f);
		glTexCoord2f(0.0f, 0.8f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.5f, 0.65f); glVertex3f( 0.8f * iLength,  0.0f,  0.0f);
		glTexCoord2f(0.0f, 0.8f); glVertex3f( 0.8f * iLength,  0.32f * iHeight,  0.8f * iWidth);
		glTexCoord2f(0.0f, 0.65f); glVertex3f( 0.8f * iLength,  0.0f,  0.8f * iWidth);

		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.65f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(0.5f, 0.65f); glVertex3f( 0.0f,  0.0f,  0.8f * iWidth);
		glTexCoord2f(0.5f, 0.8f); glVertex3f( 0.0f,  0.32f * iHeight,  0.8f * iWidth);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.65f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(0.5f, 0.8f); glVertex3f( 0.0f,  0.32f * iHeight,  0.8f * iWidth);
		glTexCoord2f(0.0f, 0.8f); glVertex3f( 0.0f,  0.32f * iHeight,  0.0f);
	glEnd();

/*
	// Enable Pointers
	glEnableClientState( GL_VERTEX_ARRAY );						// Enable Vertex Arrays
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );				// Enable Texture Coord Arrays
	glEnableClientState( GL_NORMAL_ARRAY );						// Enable Normal Arrays

	glVertexPointer (3, GL_FLOAT, 0, LGBrickLibEntry::vpVerticesArrays);	// Set The Vertex Pointer To Our Vertex Data
	glNormalPointer (GL_FLOAT, 0, LGBrickLibEntry::vpNormalsArrays);		// Set The Normal Pointer To Our Normal Data
	glTexCoordPointer (2, GL_FLOAT, 0, LGBrickLibEntry::tpTexturesArrays);

	glDrawArrays (GL_QUADS, 0, 24);

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY );
*/
	glEndList();

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::draw
*******************************************************************************/
int LGBrickLibEntry::draw (int iColor) {
	int	iDrawImmediate = 0;
	int iDrawElements = 0;
	int iDrawArrays = 0;
	int iDrawDisplayList = 1;

	// Bind texture
	if (LGBrickLibEntry::iTextureType == 0) {
		glBindTexture(GL_TEXTURE_2D, LGBrickLibEntry::aiTextures[iColor]);
	} else {
		glBindTexture(GL_TEXTURE_2D, LGBrickLibEntry::aiTextures[0]);
	}

if (iDrawDisplayList) {
	glCallList (LGBrickLibEntry::iDisplayList);
}

if (iDrawImmediate == 1) {
	glBegin(GL_QUADS);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  1.6f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 3.2f,  0.0f,  1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 3.2f,  0.96f,  1.6f);
		glTexCoord2f(0.25f, 0.5f); glVertex3f( 0.0f,  0.96f,  1.6f);
		// Back Face
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.96f,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 3.2f,  0.96f,  0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 3.2f,  0.0f,  0.0f);
		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.5f); glVertex3f( 0.0f,  0.96f,  0.0f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.96f,  1.6f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 3.2f,  0.96f,  1.6f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 3.2f,  0.96f,  0.0f);
		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 3.2f,  0.0f,  0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 3.2f,  0.0f,  1.6f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f,  0.0f,  1.6f);
		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.25f); glVertex3f( 3.2f,  0.0f,  0.0f);
		glTexCoord2f(0.75f, 0.5f); glVertex3f( 3.2f,  0.96f,  0.0f);
		glTexCoord2f(0.75f, 0.75f); glVertex3f( 3.2f,  0.96f,  1.6f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 3.2f,  0.0f,  1.6f);
		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.25f); glVertex3f( 0.0f,  0.0f,  0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.0f,  1.6f);
		glTexCoord2f(0.25f, 0.75f); glVertex3f( 0.0f,  0.96f,  1.6f);
		glTexCoord2f(0.25f, 0.5f); glVertex3f( 0.0f,  0.96f,  0.0f);
	glEnd();
}

if (iDrawElements == 1) {

	// Enable Pointers
	glEnableClientState( GL_VERTEX_ARRAY );						// Enable Vertex Arrays
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );				// Enable Texture Coord Arrays
	glEnableClientState( GL_NORMAL_ARRAY );						// Enable Normal Arrays

	glVertexPointer (3, GL_FLOAT, 0, LGBrickLibEntry::vpVerticesElements);	// Set The Vertex Pointer To Our Vertex Data
	glNormalPointer (GL_FLOAT, 0, LGBrickLibEntry::vpNormalsElements);		// Set The Normal Pointer To Our Normal Data
	glTexCoordPointer (2, GL_FLOAT, 0, LGBrickLibEntry::tpTexturesElements);

	glDrawElements (GL_QUADS, LGBrickLibEntry::iNrOfFaces * 4, GL_UNSIGNED_SHORT, LGBrickLibEntry::fpFaces);

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY );
}

if (iDrawArrays == 1) {

	// Enable Pointers
	glEnableClientState( GL_VERTEX_ARRAY );						// Enable Vertex Arrays
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );				// Enable Texture Coord Arrays
	glEnableClientState( GL_NORMAL_ARRAY );						// Enable Normal Arrays

	glVertexPointer (3, GL_FLOAT, 0, LGBrickLibEntry::vpVerticesArrays);	// Set The Vertex Pointer To Our Vertex Data
	glNormalPointer (GL_FLOAT, 0, LGBrickLibEntry::vpNormalsArrays);		// Set The Normal Pointer To Our Normal Data
	glTexCoordPointer (2, GL_FLOAT, 0, LGBrickLibEntry::tpTexturesArrays);

	glDrawArrays (GL_QUADS, 0, 24);

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY );
}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLibEntry::getChunkHeaderSize
*******************************************************************************/
int LGBrickLibEntry::getChunkHeaderSize () {
	int iChunkHeaderSize = 0;		// Chunk header size

	// Add chunk fields
	iChunkHeaderSize += SIZE_CHUNKID;		// Id
	iChunkHeaderSize += SIZE_INT;			// Chunk size
	iChunkHeaderSize += SIZE_INT;			// Number of vertices
	iChunkHeaderSize += SIZE_INT;			// Block number

	// Return chunk size
	return (iChunkHeaderSize);
}

/*******************************************************************************
* LGBrickLibEntry::getChunkSize
*******************************************************************************/
int LGBrickLibEntry::getChunkSize () {
	int iChunkSize = LGBrickLibEntry::getChunkHeaderSize ();		// Chunk size

	// Add vertices sizes
	for (int iCount = 0; iCount < LGBrickLibEntry::iNrOfVerticesElements; iCount++) {

		// Add vertices
		iChunkSize += SIZE_VERTEX3F;
		iChunkSize += SIZE_TEXTUREUV;
	}

	// Return chunk size
	return (iChunkSize);
}


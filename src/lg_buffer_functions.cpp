/*******************************************************************************
* File:		lg_buffer_functions.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		19 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../include/lg_buffer_functions.h"

#define ASCII_OFFSET 40;

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Get3DSChunkID
*******************************************************************************/
int Get3DSChunkID (byte* bpData) {
	// Return chunk ID
	return ((bpData[1] * 256) +
			(bpData[0]));
}

/*******************************************************************************
* GetInt
*******************************************************************************/
int GetInt (byte* bpData) {
	INT_UNION	iInteger;		// Integer

	// Get data from buffer
	iInteger.abInt[0] = bpData[0];
	iInteger.abInt[1] = bpData[1];
	iInteger.abInt[2] = bpData[2];
	iInteger.abInt[3] = bpData[3];

	// Return integer value
	return (iInteger.iInt);
}

/*******************************************************************************
* GetShort
*******************************************************************************/
int GetShort (byte* bpData) {
	SHORT_UNION	sShort;		// Integer

	// Get data from buffer
	sShort.abShort[0] = bpData[0];
	sShort.abShort[1] = bpData[1];

	// Return integer value
	return (sShort.sShort);
}

/*******************************************************************************
* GetFloat
*******************************************************************************/
float GetFloat (byte* bpData) {
	FLOAT_UNION	fFloat;		// Float

	// Get data from buffer
	fFloat.abFloat[0] = bpData[0];
	fFloat.abFloat[1] = bpData[1];
	fFloat.abFloat[2] = bpData[2];
	fFloat.abFloat[3] = bpData[3];

	// Return integer value
	return (fFloat.fFloat);
}

/*******************************************************************************
* GetString ()
*******************************************************************************/
int GetString (byte* cpData, char acString[256])
{
	int iCount = 0;		// Counter

	// Copy string
	while ((cpData[iCount] != '\0') && (iCount < 255))
	{
		// Copy character
		acString[iCount] = cpData[iCount];
		
		// Increase counter
		iCount++;
	}
	
	// Close string
	acString[iCount] = '\0';
	
	// Return no error
	return (0);
}

/*******************************************************************************
* GetVertex3i
*******************************************************************************/
LGVertex3i GetVertex3i (byte* bpData) {
	INT_UNION	iInt;		// Integer
	LGVertex3i	vVertex;	// Vertex

	// Get x data from buffer
	iInt.abInt[0] = bpData[0];
	iInt.abInt[1] = bpData[1];
	iInt.abInt[2] = bpData[2];
	iInt.abInt[3] = bpData[3];
	vVertex.iX = iInt.iInt;

	// Get y data from buffer
	iInt.abInt[0] = bpData[4];
	iInt.abInt[1] = bpData[5];
	iInt.abInt[2] = bpData[6];
	iInt.abInt[3] = bpData[7];
	vVertex.iY = iInt.iInt;

	// Get z data from buffer
	iInt.abInt[0] = bpData[8];
	iInt.abInt[1] = bpData[9];
	iInt.abInt[2] = bpData[10];
	iInt.abInt[3] = bpData[11];
	vVertex.iZ = iInt.iInt;

	// Return vertex
	return (vVertex);
}

/*******************************************************************************
* GetVertex3f
*******************************************************************************/
LGVertex3f GetVertex3f (byte* bpData) {
	FLOAT_UNION	fFloat;		// Float
	LGVertex3f	vVertex;	// Vertex

	// Get x data from buffer
	fFloat.abFloat[0] = bpData[0];
	fFloat.abFloat[1] = bpData[1];
	fFloat.abFloat[2] = bpData[2];
	fFloat.abFloat[3] = bpData[3];
	vVertex.fX = fFloat.fFloat;

	// Get y data from buffer
	fFloat.abFloat[0] = bpData[4];
	fFloat.abFloat[1] = bpData[5];
	fFloat.abFloat[2] = bpData[6];
	fFloat.abFloat[3] = bpData[7];
	vVertex.fY = fFloat.fFloat;

	// Get z data from buffer
	fFloat.abFloat[0] = bpData[8];
	fFloat.abFloat[1] = bpData[9];
	fFloat.abFloat[2] = bpData[10];
	fFloat.abFloat[3] = bpData[11];
	vVertex.fZ = fFloat.fFloat;

	// Return vertex
	return (vVertex);
}

/*******************************************************************************
* GetVertex3fuv
*******************************************************************************/
LGVertex3fuv GetVertex3fuv (byte* bpData) {
	FLOAT_UNION		fFloat;		// Float
	LGVertex3fuv	vVertex;	// Vertex

	// Get x data from buffer
	fFloat.abFloat[0] = bpData[0];
	fFloat.abFloat[1] = bpData[1];
	fFloat.abFloat[2] = bpData[2];
	fFloat.abFloat[3] = bpData[3];
	vVertex.fX = fFloat.fFloat;

	// Get y data from buffer
	fFloat.abFloat[0] = bpData[4];
	fFloat.abFloat[1] = bpData[5];
	fFloat.abFloat[2] = bpData[6];
	fFloat.abFloat[3] = bpData[7];
	vVertex.fY = fFloat.fFloat;

	// Get z data from buffer
	fFloat.abFloat[0] = bpData[8];
	fFloat.abFloat[1] = bpData[9];
	fFloat.abFloat[2] = bpData[10];
	fFloat.abFloat[3] = bpData[11];
	vVertex.fZ = fFloat.fFloat;

	// Get u data from buffer
	fFloat.abFloat[0] = bpData[12];
	fFloat.abFloat[1] = bpData[13];
	fFloat.abFloat[2] = bpData[14];
	fFloat.abFloat[3] = bpData[15];
	vVertex.fU = fFloat.fFloat;

	// Get v data from buffer
	fFloat.abFloat[0] = bpData[16];
	fFloat.abFloat[1] = bpData[17];
	fFloat.abFloat[2] = bpData[18];
	fFloat.abFloat[3] = bpData[19];
	vVertex.fV = fFloat.fFloat;

	// Return vertex
	return (vVertex);
}

/*******************************************************************************
* GetColor3f
*******************************************************************************/
LGColor3f GetColor3f (byte* bpData) {
	FLOAT_UNION	fFloat;		// Float
	LGColor3f	cColor;		// Color

	// Get r data from buffer
	fFloat.abFloat[0] = bpData[0];
	fFloat.abFloat[1] = bpData[1];
	fFloat.abFloat[2] = bpData[2];
	fFloat.abFloat[3] = bpData[3];
	cColor.fR = fFloat.fFloat;

	// Get g data from buffer
	fFloat.abFloat[0] = bpData[4];
	fFloat.abFloat[1] = bpData[5];
	fFloat.abFloat[2] = bpData[6];
	fFloat.abFloat[3] = bpData[7];
	cColor.fG = fFloat.fFloat;

	// Get b data from buffer
	fFloat.abFloat[0] = bpData[8];
	fFloat.abFloat[1] = bpData[9];
	fFloat.abFloat[2] = bpData[10];
	fFloat.abFloat[3] = bpData[11];
	cColor.fB = fFloat.fFloat;

	// Return vertex
	return (cColor);
}

/*******************************************************************************
* GetTextureuv
*******************************************************************************/
LGTextureuv GetTextureuv (byte* bpData) {
	FLOAT_UNION	fFloat;		// Float
	LGTextureuv	tTexture;	// Texture

	// Get u data from buffer
	fFloat.abFloat[0] = bpData[0];
	fFloat.abFloat[1] = bpData[1];
	fFloat.abFloat[2] = bpData[2];
	fFloat.abFloat[3] = bpData[3];
	tTexture.fU = fFloat.fFloat;

	// Get v data from buffer
	fFloat.abFloat[0] = bpData[4];
	fFloat.abFloat[1] = bpData[5];
	fFloat.abFloat[2] = bpData[6];
	fFloat.abFloat[3] = bpData[7];
	tTexture.fV = fFloat.fFloat;

	// Return vertex
	return (tTexture);
}

/*******************************************************************************
* GetString16
*******************************************************************************/
int GetString16 (byte* bpData, char* cpString) {
	int		iCount;		// Counter

	// Copy string
	for (iCount = 0; iCount < 16; iCount++) {

		// Copy character
		cpString[iCount] = (char)bpData[iCount];
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintInt12
*******************************************************************************/
int PrintInt12 (FILE* fpFile, int iInteger) {
	int	iInt1;
	int	iInt2;

	iInt1 = iInteger / 64 + ASCII_OFFSET;
	iInt2 = iInteger % 64 + ASCII_OFFSET;

	// Print integer to file
	fprintf (fpFile, "%c", iInt1);
	if (iInt1 == '\\') {
		fprintf (fpFile, "%c", iInt1);
	}

	// Print integer to file
	fprintf (fpFile, "%c", iInt2);
	if (iInt2 == '\\') {
		fprintf (fpFile, "%c", iInt2);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintBoolInt5
*******************************************************************************/
int PrintBoolInt5 (FILE* fpFile, bool bType, int iInteger) {
	int	iInt;

	iInt = iInteger;
	VerbosePrintf ("int: %d", iInt);
	if (bType) {
		iInt += 32;
	}
	VerbosePrintf ("bool int: %d", iInt);
	iInt += ASCII_OFFSET;
	VerbosePrintf ("ascii int: %d", iInt);

	// Print integer to file
	fprintf (fpFile, "%c", iInt);
	if (iInt == '\\') {
		fprintf (fpFile, "%c", iInt);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintInt2Float10
*******************************************************************************/
int PrintInt2Float10 (FILE* fpFile, int iInteger, float fFloat) {
	int iInt;
	int	iInt1;
	int	iInt2;

	VerbosePrintf ("float: %f", fFloat);

	iInt = (int)(fFloat*10);

	VerbosePrintf ("int: %d", iInt);

	switch (iInteger) {
		case 1:
			iInt += 1024;
			break;
		case 2:
			iInt += 2048;
			break;
		case 3:
			iInt += 3072;
			break;
	}

	VerbosePrintf ("int2-10: %d %d", iInteger, iInt);

	iInt1 = iInt / 64 + ASCII_OFFSET;
	iInt2 = iInt % 64 + ASCII_OFFSET;

	// Print integer to file
	fprintf (fpFile, "%c", iInt1);
	if (iInt1 == '\\') {
		fprintf (fpFile, "%c", iInt1);
	}

	// Print integer to file
	fprintf (fpFile, "%c", iInt2);
	if (iInt2 == '\\') {
		fprintf (fpFile, "%c", iInt2);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintInt16
*******************************************************************************/
int PrintInt16 (FILE* fpFile, int iInteger) {
	INT_UNION	IInteger;		// Integer

	// Put integer into buffer
	IInteger.iInt = iInteger;

	// Print integer to file
	fprintf (fpFile, "%c%c", IInteger.abInt[0], IInteger.abInt[1]);

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintFloat
*******************************************************************************/
int PrintFloat (FILE* fpFile, float fFloat) {
	int iInt;
	int iInt1;
	int iInt2;

	fFloat *= 10;
	iInt = (int)fFloat;
	iInt1 = iInt / 64 + ASCII_OFFSET;
	iInt2 = iInt % 64 + ASCII_OFFSET;

	// Print integer to file
	fprintf (fpFile, "%c", iInt1);
	if (iInt1 == '\\') {
		fprintf (fpFile, "%c", iInt1);
	}

	// Print integer to file
	fprintf (fpFile, "%c", iInt2);
	if (iInt2 == '\\') {
		fprintf (fpFile, "%c", iInt2);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintVertex3i
*******************************************************************************/
int PrintVertex3i (FILE* fpFile, LGVertex3i vVertex) {
	INT_UNION	IInteger;		// Integer

	// Print x
	IInteger.iInt = vVertex.iX;
	fprintf (fpFile, "%c%c%c%c", IInteger.abInt[0], IInteger.abInt[1], 
		IInteger.abInt[2], IInteger.abInt[3]);

	// Print y
	IInteger.iInt = vVertex.iY;
	fprintf (fpFile, "%c%c%c%c", IInteger.abInt[0], IInteger.abInt[1], 
		IInteger.abInt[2], IInteger.abInt[3]);

	// Print z
	IInteger.iInt = vVertex.iZ;
	fprintf (fpFile, "%c%c%c%c", IInteger.abInt[0], IInteger.abInt[1], 
		IInteger.abInt[2], IInteger.abInt[3]);

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintVertex3f
*******************************************************************************/
int PrintVertex3f (FILE* fpFile, LGVertex3f vVertex) {
	FLOAT_UNION	FFloat;		// Float

	// Print x
	FFloat.fFloat = vVertex.fX;
	fprintf (fpFile, "%c%c%c%c", FFloat.abFloat[0], FFloat.abFloat[1], 
		FFloat.abFloat[2], FFloat.abFloat[3]);

	// Print y
	FFloat.fFloat = vVertex.fY;
	fprintf (fpFile, "%c%c%c%c", FFloat.abFloat[0], FFloat.abFloat[1], 
		FFloat.abFloat[2], FFloat.abFloat[3]);

	// Print z
	FFloat.fFloat = vVertex.fZ;
	fprintf (fpFile, "%c%c%c%c", FFloat.abFloat[0], FFloat.abFloat[1], 
		FFloat.abFloat[2], FFloat.abFloat[3]);

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintVertex3fuv
*******************************************************************************/
int PrintVertex3fuv (FILE* fpFile, LGVertex3fuv vVertex) {
	FLOAT_UNION	FFloat;		// Float

	// Print x
	FFloat.fFloat = vVertex.fX;
	fprintf (fpFile, "%c%c%c%c", FFloat.abFloat[0], FFloat.abFloat[1], 
		FFloat.abFloat[2], FFloat.abFloat[3]);

	// Print y
	FFloat.fFloat = vVertex.fY;
	fprintf (fpFile, "%c%c%c%c", FFloat.abFloat[0], FFloat.abFloat[1], 
		FFloat.abFloat[2], FFloat.abFloat[3]);

	// Print z
	FFloat.fFloat = vVertex.fZ;
	fprintf (fpFile, "%c%c%c%c", FFloat.abFloat[0], FFloat.abFloat[1], 
		FFloat.abFloat[2], FFloat.abFloat[3]);

	// Print u
	FFloat.fFloat = vVertex.fU;
	fprintf (fpFile, "%c%c%c%c", FFloat.abFloat[0], FFloat.abFloat[1], 
		FFloat.abFloat[2], FFloat.abFloat[3]);

	// Print v
	FFloat.fFloat = vVertex.fV;
	fprintf (fpFile, "%c%c%c%c", FFloat.abFloat[0], FFloat.abFloat[1], 
		FFloat.abFloat[2], FFloat.abFloat[3]);

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintColor3f
*******************************************************************************/
int PrintColor3f (FILE* fpFile, LGColor3f cColor) {
	FLOAT_UNION	FFloat;		// Float

	// Print x
	FFloat.fFloat = cColor.fR;
	fprintf (fpFile, "%c%c%c%c", FFloat.abFloat[0], FFloat.abFloat[1], 
		FFloat.abFloat[2], FFloat.abFloat[3]);

	// Print y
	FFloat.fFloat = cColor.fG;
	fprintf (fpFile, "%c%c%c%c", FFloat.abFloat[0], FFloat.abFloat[1], 
		FFloat.abFloat[2], FFloat.abFloat[3]);

	// Print z
	FFloat.fFloat = cColor.fG;
	fprintf (fpFile, "%c%c%c%c", FFloat.abFloat[0], FFloat.abFloat[1], 
		FFloat.abFloat[2], FFloat.abFloat[3]);

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintTextureuv
*******************************************************************************/
int PrintTextureuv (FILE* fpFile, LGTextureuv tTexture) {
	FLOAT_UNION	FFloat;		// Float

	// Print u
	FFloat.fFloat = tTexture.fU;
	fprintf (fpFile, "%c%c%c%c", FFloat.abFloat[0], FFloat.abFloat[1], 
		FFloat.abFloat[2], FFloat.abFloat[3]);

	// Print v
	FFloat.fFloat = tTexture.fV;
	fprintf (fpFile, "%c%c%c%c", FFloat.abFloat[0], FFloat.abFloat[1], 
		FFloat.abFloat[2], FFloat.abFloat[3]);

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintHeader
*******************************************************************************/
int PrintHeader (FILE* fpFile, char* cpLevel) {

	// Print chunk ID to file
	fprintf (fpFile, "alLevel['%s'] = \"", cpLevel);

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintFooter
*******************************************************************************/
int PrintFooter (FILE* fpFile) {

	// Print chunk ID to file
	fprintf (fpFile, "\";");

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintChunkID
*******************************************************************************/
int PrintChunkID (FILE* fpFile, char* cpChunk) {

	// Print chunk ID to file
	fprintf (fpFile, "%s", cpChunk);

	// Return no error
	return (0);
}

/*******************************************************************************
* PrintString16
*******************************************************************************/
int PrintString16 (FILE* fpFile, char* cpString) {
	int iCount;		// Counter

	// Print string
	for (iCount = 0; iCount < 16; iCount++) {

		// Print char
		fprintf (fpFile, "%c", cpString[iCount]);
	}

	// Return no error
	return (0);
}
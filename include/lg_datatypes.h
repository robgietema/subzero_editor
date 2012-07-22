/*******************************************************************************
* File:		lg_datatypes.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		19 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_DATATYPES_H
#define LG_DATATYPES_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////
#define		SIZE_SHORT		2
#define		SIZE_INT		4
#define		SIZE_FLOAT		4
#define		SIZE_CHUNKID	3
#define		SIZE_VERTEX3I	12
#define		SIZE_VERTEX3F	12
#define		SIZE_COLOR3F	12
#define		SIZE_TEXTUREUV	8
#define		SIZE_STRING16	16
#define		UNIT_X			0.8f
#define		UNIT_Y			0.32f
#define		UNIT_Z			0.8f
#define		TUNE_UNIT		0.02f
#define		ANIM_UNIT		0.2f
#define		GROUP_UNIT		0.2f
#define		TUNE_ROTATE		2.0f

#define		NR_OF_COLORS	28

enum {								// Chunk ID's
	SCN_ID,							// Header chunk ID
	OBJ_ID,							// Object chunk ID
	GRP_ID,							// Objectgroup chunk ID
	BRK_ID,							// Brick chunk ID
	BLB_ID,							// Brick lib chunk ID
	BEN_ID,							// Brick lib entry chunk ID
	OBL_ID,							// Object lib chunk ID
	UNKNOWN_ID						// Unknown ID
};

////////////////////////////////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////////////////////////////////
typedef unsigned char byte;			// Byte definition

typedef struct {					// Vector definition of floats
	float	fX;						// X coordinate of vector
	float	fY;						// Y coordinate of vector
} LGVertex2f;

typedef struct {					// Vector definition of floats
	int	iX;							// X coordinate of vector
	int	iY;							// Y coordinate of vector
} LGVertex2i;

typedef struct {					// Vector definition of floats
	float	fX;						// X coordinate of vector
	float	fY;						// Y coordinate of vector
	float	fZ;						// Z coordinate of vector
} LGVertex3f;

typedef struct {					// Texture uv definition
	float	fU;						// U coordinate of vector
	float	fV;						// V coordinate of vector
} LGTextureuv;

typedef struct {					// Vector definition of floats and u,v
	float	fX;						// X coordinate of vector
	float	fY;						// Y coordinate of vector
	float	fZ;						// Z coordinate of vector
	float	fU;						// U coordinate of texture
	float	fV;						// V coordinate of texture
} LGVertex3fuv;

typedef struct {					// Vector definition of integers
	int		iX;						// X coordinate of vector
	int		iY;						// Y coordinate of vector
	int		iZ;						// Z coordinate of vector
} LGVertex3i;

typedef struct {					// Color definition
	float	fR;						// Red value of color
	float	fG;						// Green value of color
	float	fB;						// Blue value of color
} LGColor3f;

typedef struct {					// Color definition
	byte	bR;						// Red value of color
	byte	bG;						// Green value of color
	byte	bB;						// Blue value of color
} LGColor3b;

typedef struct {					// Face definition
	unsigned short sA;				// First vertex
	unsigned short sB;				// Second vertex
	unsigned short sC;				// Third vertex
} LGFace3s;

typedef struct {					// Face definition
	unsigned short sA;				// First vertex
	unsigned short sB;				// Second vertex
	unsigned short sC;				// Third vertex
	unsigned short sD;				// Fourth vertex
} LGFace4s;

////////////////////////////////////////////////////////////////////////////////
// Unions
////////////////////////////////////////////////////////////////////////////////
union SHORT_UNION {					// Integer union

	byte	abShort[2];				// Integer bytes
	unsigned short	sShort;			// Integer value
};

union INT_UNION {					// Integer union

	byte	abInt[4];				// Integer bytes
	int		iInt;					// Integer value
};

union FLOAT_UNION {					// Float union

	byte	abFloat[4];				// Float bytes
	float	fFloat;					// Float value
};

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

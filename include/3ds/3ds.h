/*******************************************************************************
* File:		3ds.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (_3DS_H)
#define _3DS_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////
#define 	WIREFRAME		0
#define		FLATSHADING		1
#define		GOURAND			2
#define 	PHONG			3
#define		METAL			4
#define		RADTODEG		0.0174532925199432957692369076848

////////////////////////////////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////////////////////////////////

typedef struct FACE_3DS		// Struct used to describe a face
{
	unsigned int iA;		// Index into the vertex list of point 1
	unsigned int iB;		// Index into the vertex list of point 2
	unsigned int iC;		// Index into the vertex list of point 3
	unsigned int iEdge;		// 0 = edge CA visible
} FACE_3DS;

typedef struct FACE_MAT		// Struct used to desctibe a face with a material
{
	unsigned int iA;		// Index into the vertex list of point 1
	unsigned int iB;		// Index into the vertex list of point 2
	unsigned int iC;		// Index into the vertex list of point 3
	unsigned int iEdge;		// 0 = edge CA visible
	char		 acMat[16];	// Name of the material of the face
} FACE_MAT;

typedef struct 				// Struct used to describe a 3d-point
{
	float		fX;			// X-Coordinate of point
	float		fY;			// Y-Coordinate of point
	float		fZ;			// Z-Coordinate of point
} POINT_3DS;

typedef struct 				// Struct used to describe a 3d-point
{
	float		fU;			// U-Coordinate of point
	float		fV;			// V-Coordinate of point
} TEXVERT_3DS;

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////


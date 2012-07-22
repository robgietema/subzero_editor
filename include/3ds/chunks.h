/*******************************************************************************
* File:		chunks.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (CHUNKS_H)
#define CHUNKS_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////
#define M3DMAGIC_CHUNK				0x4d4d
#define COLOR_F_CHUNK				0x0010
#define LIN_COLOR_F_CHUNK			0x0013
#define COLOR_24_CHUNK				0x0011
#define LIN_COLOR_24_CHUNK			0x0012
#define INT_PERCENTAGE_CHUNK		0x0030
#define FLOAT_PERCENTAGE_CHUNK		0x0031
#define M3D_VERSION_CHUNK			0x0002
#define MDATA_CHUNK					0x3d3d
#define MESH_VERSION_CHUNK			0x3d3e
#define MASTER_SCALE_CHUNK			0x0100
#define MAT_ENTRY_CHUNK				0xafff
#define MAT_NAME_CHUNK				0xa000
#define MAT_AMBIENT_CHUNK			0xa010
#define MAT_DIFFUSE_CHUNK			0xa020
#define MAT_SPECULAR_CHUNK			0xa030
#define MAT_SHININESS_CHUNK			0xa040
#define MAT_SHIN_STRENGTH_CHUNK		0xa041
#define MAT_TRANSPARENCY_CHUNK		0xa050
#define MAT_TRANS_FALLOFF_CHUNK		0xa052
#define MAT_REFLECT_BLUR_CHUNK		0xa053
#define MAT_SELF_ILLUM_CHUNK		0xa084
#define MAT_TRANS_FALLOFF_IN_CHUNK	0xa08a
#define MAT_WIRE_THICKNESS_CHUNK	0xa087
#define MAT_SHADING_CHUNK			0xa100
#define MAT_TEX1_MAP_CHUNK			0xa200
#define MAT_BUMP_DISPLAY_PER_CHUNK	0xa252
#define MAT_MAP_FILENAME_CHUNK		0xa300
#define MAT_MAP_OPTIONS_CHUNK		0xa351
#define MAT_MAP_BLUR_CHUNK			0xa353
#define MAT_MAP_ROTATION_CHUNK		0xa35c
#define MAT_TEX1_MASK_CHUNK			0xa33e
#define MAT_TEX2_MAP_CHUNK			0xa33a
#define MAT_TEX2_MASK_CHUNK			0xa340
#define MAT_BUMP_MAP_CHUNK			0xa230
#define MAT_BUMP_MASK_CHUNK			0xa344
#define NAMED_OBJECT_CHUNK			0x4000
#define N_TRI_OBJECT_CHUNK			0x4100
#define POINT_ARRAY_CHUNK			0x4110
#define FACE_ARRAY_CHUNK			0x4120
#define MSH_MAT_GROUP_CHUNK			0x4130
#define TEX_VERTS_CHUNK				0x4140
#define FACE_SMOOTHING_CHUNK		0x4150
#define LOCAL_AXIS_CHUNK			0x4160
#define LIGHT_CHUNK					0x4600
#define LIGHT_OFF_CHUNK				0x4620
#define SPOTLIGHT_CHUNK				0x4610
#define CAMERA_CHUNK				0x4700

#define CHUNKID_SIZE			2
#define CHUNKLENGTH_SIZE		4
#define CHUNKHEADER_SIZE		(CHUNKID_SIZE + CHUNKLENGTH_SIZE)

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

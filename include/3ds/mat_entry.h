/*******************************************************************************
* File:		mat_entry.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (MAT_ENTRY_H)
#define MAT_ENTRY_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "../../include/3ds/3ds.h"
#include "../../include/lg_print.h"
#include "../../include/3ds/chunks.h"
#include "../../include/lg_buffer_functions.h"
#include "../../include/3ds/mat_name.h"
#include "../../include/3ds/mat_ambient.h"
#include "../../include/3ds/mat_diffuse.h"
#include "../../include/3ds/mat_specular.h"
#include "../../include/3ds/mat_shininess.h"
#include "../../include/3ds/mat_shin_strength.h"
#include "../../include/3ds/mat_transperancy.h"
#include "../../include/3ds/mat_shading.h"
#include "../../include/3ds/mat_reflect_blur.h"
#include "../../include/3ds/mat_trans_falloff.h"
#include "../../include/3ds/mat_self_illum.h"
#include "../../include/3ds/mat_wire_thickness.h"
#include "../../include/3ds/mat_tex1_map.h"
#include "../../include/3ds/mat_bump_map.h"

////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	MAT_ENTRY
* Function:		This class describes all the information about a material.
*******************************************************************************/
class MAT_ENTRY  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			MAT_ENTRY ()
		* Function:		Constructor 
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		MAT_ENTRY ();

		/***********************************************************************
		* Name:			~MAT_ENTRY ()
		* Function:		Destructor
		* Pre:          -
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~MAT_ENTRY ();

		/***********************************************************************
		* Name:			Read3DSFile (int iNrOfBytes, byte* bp3DSData)
		* Function:		This function reads 3ds data.
		* Pre:          bp3DSData contains the 3DS data and iNrOfBytes
		*				contains the number of bytes in the 3DS data.
		* Post:         3DS data is stored in the datastructure.
		***********************************************************************/
		int Read3DS (int iNrOfBytes, byte* bp3DSData);

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////
		MAT_NAME			nMatName;			// Material name
		MAT_AMBIENT			aMatAmbient;		// Ambient color
		MAT_DIFFUSE			dMatDiffuse;		// Diffuse color
		MAT_SPECULAR		sMatSpecular;		// Specular color
		MAT_SHININESS		sMatShininess;		// Shininess percentage
		MAT_SHIN_STRENGTH	sMatShinStrength;	// Shininess strength percentage
		MAT_TRANSPARENCY	tMatTransparency;	// Transparency percentage
		MAT_SHADING			sMatShading;		// Displaymode
		MAT_TRANS_FALLOFF	tMatTransFalloff;	// Trans falloff
		MAT_REFLECT_BLUR	rMatReflectBlur;	// Reflect blur
		MAT_SELF_ILLUM		sMatSelfIllum;		// Self illum
		MAT_WIRE_THICKNESS	wMatWireThickness;	// Wire thickness
		MAT_TEX1_MAP		tMatTex1Map;		// Texture 1 map
		MAT_BUMP_MAP		bMatBumpMap;		// Bump map
		bool				bTransFalloffIn;	// Trans falloff in

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
}; // End MAT_ENTRY

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

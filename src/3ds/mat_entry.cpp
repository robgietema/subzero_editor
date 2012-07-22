/*******************************************************************************
* File:		mat_entry.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/mat_entry.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MAT_ENTRY ()
*******************************************************************************/
MAT_ENTRY::MAT_ENTRY() {

	// Init default values
	MAT_ENTRY::bTransFalloffIn = false;
}

/*******************************************************************************
* Name:			~MAT_ENTRY ()
*******************************************************************************/
MAT_ENTRY::~MAT_ENTRY()
{

}

/*******************************************************************************
* Name:			Read3DSFile ()
*******************************************************************************/
int MAT_ENTRY::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCurrentByte = 0;	// Pointer to current byte in chunk
	int iChunkID;			// Chunk id
	long lChunkLength;		// Chunk length

	// Print status
	VerbosePrintf ("Begin reading MAT_ENTRY chunk");

	// Check for zero length
	if (iNrOfBytes <= CHUNKHEADER_SIZE)
	{
		// Set error file contains no data
		ErrorPrintf ("File contains no data");

		// Return error
		return (-1);
	}

	// Get chunks from MAT_ENTRY chunk
	while (iCurrentByte < iNrOfBytes)
	{
		// Get chunk id
		iChunkID = Get3DSChunkID (bp3DSData + iCurrentByte);
		iCurrentByte += CHUNKID_SIZE;
		
		// Get chunk length
		lChunkLength = GetInt (bp3DSData + iCurrentByte);
		iCurrentByte += CHUNKLENGTH_SIZE;
		
		// Check if length is correct
		if (lChunkLength > (iNrOfBytes - iCurrentByte + CHUNKHEADER_SIZE))
		{
			// Set error chunk size invalid
			ErrorPrintf ("Chunk size invalid");

			// Return error
			return (-1);
		}
		
		// Check chunk id
		switch (iChunkID)
		{
			case MAT_NAME_CHUNK:
				// Print status
				VerbosePrintf ("MAT_NAME chunk found");

				// Read MAT_NAME chunk
				if (MAT_ENTRY::nMatName.Read3DS (lChunkLength - CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0) {

					// Return error
					return (-1);
				}				
				break;
			case MAT_AMBIENT_CHUNK:
				// Print status
				VerbosePrintf ("MAT_AMBIENT chunk found");

				// Read MAT_AMBIENT chunk
				if (MAT_ENTRY::aMatAmbient.Read3DS (lChunkLength - CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0) {

					// Return error
					return (-1);
				}				
				break;
			case MAT_DIFFUSE_CHUNK:
				// Print status
				VerbosePrintf ("MAT_DIFFUSE chunk found");

				// Read MAT_DIFFUSE chunk
				if (MAT_ENTRY::dMatDiffuse.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MAT_SPECULAR_CHUNK:
				// Print status
				VerbosePrintf ("MAT_SPECULAR chunk found");

				// Read MAT_SPECULAR chunk
				if (MAT_ENTRY::sMatSpecular.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MAT_SHININESS_CHUNK:
				// Print status
				VerbosePrintf ("MAT_SHININESS chunk found");

				// Read MAT_NAME chunk
				if (MAT_ENTRY::sMatShininess.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MAT_SHIN_STRENGTH_CHUNK:
				// Print status
				VerbosePrintf ("MAT_SHIN_STRENGTH chunk found");

				// Read MAT_NAME chunk
				if (MAT_ENTRY::sMatShinStrength.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MAT_TRANSPARENCY_CHUNK:
				// Print status
				VerbosePrintf ("MAT_TRANSPARENCY chunk found");

				// Read MAT_TRANSPARENCY chunk
				if (MAT_ENTRY::tMatTransparency.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MAT_SHADING_CHUNK:
				// Print status
				VerbosePrintf ("MAT_SHADING chunk found");

				// Read MAT_SHADING chunk
				if (MAT_ENTRY::sMatShading.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MAT_REFLECT_BLUR_CHUNK:
				// Print status
				VerbosePrintf ("MAT_REFLECT_BLUR chunk found");

				// Read MAT_REFLECT_BLUR chunk
				if (MAT_ENTRY::rMatReflectBlur.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MAT_TRANS_FALLOFF_CHUNK:
				// Print status
				VerbosePrintf ("MAT_TRANS_FALLOFF chunk found");

				// Read MAT_TRANS_FALLOFF chunk
				if (MAT_ENTRY::tMatTransFalloff.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MAT_SELF_ILLUM_CHUNK:
				// Print status
				VerbosePrintf ("MAT_SELF_ILLUM chunk found");

				// Read MAT_SELF_ILLUM chunk
				if (MAT_ENTRY::sMatSelfIllum.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MAT_TRANS_FALLOFF_IN_CHUNK:
				// Print status
				VerbosePrintf ("MAT_TRANS_FALLOFF_IN chunk found");

				// Set falloff in
				MAT_ENTRY::bTransFalloffIn = true;
				break;
			case MAT_WIRE_THICKNESS_CHUNK:
				// Print status
				VerbosePrintf ("MAT_WIRE_THICKNESS chunk found");

				// Read MAT_WIRE_THICKNESS chunk
				if (MAT_ENTRY::wMatWireThickness.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0) {

					// Return error
					return (-1);
				}				
				break;
			case MAT_TEX1_MAP_CHUNK:
				// Print status
				VerbosePrintf ("MAT_TEX1_MAP chunk found");

				// Read MAT_TEX1_MAP chunk
				if (MAT_ENTRY::tMatTex1Map.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0) {

					// Return error
					return (-1);
				}				
				break;
			case MAT_BUMP_MAP_CHUNK:
				// Print status
				VerbosePrintf ("MAT_BUMP_MAP chunk found");

				// Read MAT_BUMP_MAP chunk
				if (MAT_ENTRY::bMatBumpMap.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0) {

					// Return error
					return (-1);
				}				
				break;
			default:
				// Print status
				VerbosePrintf ("Unknown chunk found in MAT_ENTRY: %x with size: %d", iChunkID, lChunkLength - CHUNKHEADER_SIZE);
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}

	// Print status
	VerbosePrintf ("End reading MAT_ENTRY chunk");

	// Return no error
	return (0);
}

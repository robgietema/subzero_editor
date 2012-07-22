/*******************************************************************************
* File:		msh_mat_group.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/msh_mat_group.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MSH_MAT_GROUP ()
*******************************************************************************/
MSH_MAT_GROUP::MSH_MAT_GROUP()
{
	// Initialize material name
	strcpy (MSH_MAT_GROUP::acName, "");
	
	// Initialize number of faces
	MSH_MAT_GROUP::iNrOfFaces = NULL;
}

/*******************************************************************************
* Name:			~MSH_MAT_GROUP ()
*******************************************************************************/
MSH_MAT_GROUP::~MSH_MAT_GROUP() {

	// If allocated
	if (MSH_MAT_GROUP::iFaces) {

		// Delete
		delete []MSH_MAT_GROUP::iFaces;
	}
}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MSH_MAT_GROUP::Read3DS (int iNrOfBytes, byte* bp3DSData) {
	int iCount;					// Counter
	int iFaceCount;				// Number of faces
	int iNameLength;			// Length of material name

	// Print status
	VerbosePrintf ("Begin reading MSH_MAT_GROUP chunk");

	// Get material name from buffer
	GetString (bp3DSData, MSH_MAT_GROUP::acName);

	// Print status
	VerbosePrintf ("MshMatGroupname: %s", MSH_MAT_GROUP::acName);

	// Get name length
	iNameLength = strlen (MSH_MAT_GROUP::acName);

	// Get facecount
	iFaceCount = GetShort (bp3DSData + iNameLength + 1);

	// Check if > 0
	if (iFaceCount > 0) {

		// Allocate face list
		iFaces = new int[iFaceCount];
	}

	// Print status
	VerbosePrintf ("%d faces found", iFaceCount);
	MSH_MAT_GROUP::iNrOfFaces = iFaceCount;

	// Check if length is correct
	if ((iFaceCount * SIZE_SHORT) + iNameLength + 1 + SIZE_SHORT> iNrOfBytes) {

		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get faces from MSH_MAT_GROUPS chunk
	for (iCount = 0; iCount < iFaceCount; iCount++)	{

		// Get face		
		MSH_MAT_GROUP::iFaces[iCount] = GetShort (bp3DSData + iNameLength + 1 + SIZE_SHORT + (iCount * 2));
			
		// Print status
		VerbosePrintf ("Facenr: %d", MSH_MAT_GROUP::iFaces[iCount]);
	}

	// Print status
	VerbosePrintf ("End reading MSH_MAT_GROUP chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetMaterialName ()
*******************************************************************************/
int MSH_MAT_GROUP::GetMaterialName (int iFace, char acMatName[16])
{
	int iCount;			// Counter

	// Check if the face exists in the face list
	for (iCount = 0; iCount < MSH_MAT_GROUP::iNrOfFaces; iCount++)
	{
		// Check if current face in the list is equal to the parameter
		if (MSH_MAT_GROUP::iFaces[iCount] == iFace)
		{
			// Copy material name to parameter variable
			strcpy (acMatName, MSH_MAT_GROUP::acName);
			
			// return no error
			return (0);
		}
	}

	// Face not found in the list
	strcpy (acMatName, "");

	// return no error
	return (0);
}

/*******************************************************************************
* File:		spotlight.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#if !defined (SPOTLIGHT_H)
#define SPOTLIGHT_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/3ds.h"
#include "../../include/lg_print.h"
#include "../../include/3ds/chunks.h"
#include "../../include/lg_buffer_functions.h"

////////////////////////////////////////////////////////////////////////////////
// Class definition
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Classname:	SPOTLIGHT
* Function:		This class describes a spotlight.
*******************************************************************************/
class SPOTLIGHT  
{
	public:
		////////////////////////////////////////////////////////////////////////
		// Interface functions
		////////////////////////////////////////////////////////////////////////

		/***********************************************************************
		* Name:			SPOTLIGHT ()
		* Function:		Constructor
		* Pre:          -
		* Post:         Object is created.
		***********************************************************************/
		SPOTLIGHT ();

		/***********************************************************************
		* Name:			~SPOTLIGHT ()
		* Function:		Destructor 
		* Pre:          - 
		* Post:         Object is destroyed.
		***********************************************************************/
		virtual ~SPOTLIGHT ();

		/***********************************************************************
		* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData)
		* Function:		This function reads 3ds data.
		* Pre:          bp3DSData contains the 3DS data and iNrOfBytes
		*				contains the number of bytes in the 3DS data.
		* Post:         3DS data is stored in the datastructure.
		***********************************************************************/
		int Read3DS (int iNrOfBytes, byte* bp3DSData);

		/***********************************************************************
		* Name:			Used (void)
		* Function:		This function checks if the spotlight is used.
		* Pre:          -
		* Post:         True is returned if spotlight is used else false.
		***********************************************************************/
		bool Used (void);

		/***********************************************************************
		* Name:			GetSpotLight (float* fTargetX, float* fTargetY,
		*								float* fTargetZ, float* fHotSpot,
		*								float fFalloff)
		* Function:		This function returns spotlight data.
		* Pre:          -
		* Post:         fTargetX contains the x-position of the target,
		*               fTargetY contains the y-position of the target,
		*               fTargetZ contains the z-position of the target,
		*               fHotSpot contains the hotspot data and fFalloff
		*               contains the falloff data.
		***********************************************************************/
		int GetSpotLight (float* fTargetX, float* fTargetY, float* fTargetZ,
							float* fHotSpot, float* fFalloff);

		////////////////////////////////////////////////////////////////////////
		// Public variables
		////////////////////////////////////////////////////////////////////////

	private:
		////////////////////////////////////////////////////////////////////////
		// Private functions
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		// Private variables
		////////////////////////////////////////////////////////////////////////
		float		fTargetX;		// Target position x
		float		fTargetY;		// Target position y
		float		fTargetZ;		// Target position z
		float		fHotSpot;		// Hotspot
		float		fFalloff;		// Falloff
		bool		bUsed;			// True if spot is used
}; // End SPOTLIGHT

////////////////////////////////////////////////////////////////////////////////
#endif 
////////////////////////////////////////////////////////////////////////////////

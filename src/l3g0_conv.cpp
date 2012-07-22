/*******************************************************************************
* File:		l3g0_conv.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		5 January 2004
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../include/l3g0_conv.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
LGColor3b	acColors[NR_OF_COLORS];					// Colors
LGBrickLib	bBrickLib;								// Bricklib
LGObjectLib	oObjectLib;								// Objectlib
LGScene		sScene;									// Scene

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Main
*******************************************************************************/
int main (int argc, char *argv[]) {
	char *cpInput = NULL;		// Filename of directoryname of the input
	char *cpOutput = NULL;		// Filename of directoryname of the output
	int  iCount;				// Counter
	extern bool bVerbose;		// Verbose on / off
	int  iAction = 0;			// Action

	// Init verbose
	bVerbose = false;

	// Init printing
	InitPrintToScreen ();

	// Check parameter options
  	for (iCount = 1; iCount < argc; iCount++)
	{
		// Check parameter
		if ((strcmp (argv[iCount], "-v") == 0) || (strcmp (argv[iCount], "-v") == 0)) {

			// Set verbose on
			bVerbose = true;
		} else if ((strcmp (argv[iCount], "-h") == 0) || (strcmp (argv[iCount], "--help") == 0)) {

			// Print help
			PrintHelp ();    		  	
		} else if ((strcmp (argv[iCount], "-3") == 0) || (strcmp (argv[iCount], "--3dstobrick") == 0)) {

			// Set action
			iAction = 1;    		  	
		} else if ((strcmp (argv[iCount], "-b") == 0) || (strcmp (argv[iCount], "--3dstobricks") == 0)) {

			// Set action
			iAction = 2;    		  	
		} else if ((strcmp (argv[iCount], "-l") == 0) || (strcmp (argv[iCount], "--3dstobricklib") == 0)) {

			// Set action
			iAction = 3;    		  	
		} else if ((strcmp (argv[iCount], "-k") == 0) || (strcmp (argv[iCount], "--brickstobricklib") == 0)) {

			// Set action
			iAction = 4;
		} else if ((strcmp (argv[iCount], "-l") == 0) || (strcmp (argv[iCount], "--objtoobjlib") == 0)) {

			// Set action
			iAction = 5;    		  	
		} else if ((strcmp (argv[iCount], "-o") == 0) || (strcmp (argv[iCount], "--output") == 0)) {

			// Inc counter
			iCount++;

			// Get output file
			cpOutput = new char[strlen (argv[iCount])];
			strcpy (cpOutput, argv[iCount]);
		} else if ((strcmp (argv[iCount], "-i") == 0) || (strcmp (argv[iCount], "--input") == 0)) {{

			// Inc counter
			iCount++;

			// Get input file
			cpInput = new char[strlen (argv[iCount])];
			strcpy (cpInput, argv[iCount]);
		}
  	}

	// Check if input set
	if (cpInput == NULL) {

		// Get action
		switch (iAction) {

			case 1:
				cpInput = new char[strlen ("data/models/3ds/default.3ds") + 1];
				strcpy (cpInput, "data/models/3ds/default.3ds");
				break;
			case 2:
				cpInput = new char[strlen ("data/models/3ds/") + 1];
				strcpy (cpInput, "data/models/3ds/");
				break;
			case 3:
				cpInput = new char[strlen ("data/models/3ds/") + 1];
				strcpy (cpInput, "data/models/3ds/");
				break;
			case 4:
				cpInput = new char[strlen ("data/models/bricks/") + 1];
				strcpy (cpInput, "data/models/bricks/");
				break;
			case 5:
				cpInput = new char[strlen ("data/models/bricks/") + 1];
				strcpy (cpInput, "data/models/bricks/");
				break;
		}
	}

	// Check if output set
	if (cpOutput == NULL) {

		// Get action
		switch (iAction) {

			case 1:
				// find last .
				var iIndex = 0;
				for (var iCount = 0; iCount < strlen (cpInput); iCount++) {
					if (cpInput[iiCount] == '.') {
						iIndex = iCount;
					}
				}
				
				// Build string
				cpOutput = new char[strlen (cpInput) + 1];
				strncpy (cpOutput, cpInput, iIndex);
				strcat (cpOutput, ".brk";

				// Convert
				Convert3dsToBrick (cpInput, cpOutput);
				break;
			case 2:
				cpOutput = new char[strlen ("data/models/bricks/") + 1];
				strcpy (cpOutput, "data/models/3ds/bricks/");

				// Convert
				Convert3dsToBricks (cpInput, cpOutput);
				break;
			case 3:
				cpOutput = new char[strlen ("data/models/bricks/default.blb") + 1];
				strcpy (cpOutput, "data/models/bricks/default.blb");

				// Convert
				Convert3dsToBricklib (cpInput, cpOutput);
				break;
			case 4:
				cpOutput = new char[strlen ("data/models/bricks/default.blb") + 1];
				strcpy (cpOutput, "data/models/bricks/default.blb");

				// Convert
				ConvertBricksToBricklib (cpInput, cpOutput);
				break;
			case 5:
				cpOutput = new char[strlen ("data/models/objects/default.obl") + 1];
				strcpy (cpOutput, "data/models/objects/default.obl");
				break;

				// Convert
				ConvertObjectsToObjectlib (cpInput, cpOutput);
		}
	}
	
	// Check if no action selected
	if (iAction == 0) {

		// Print error
		VerbosePrintf ("No action selected");
		
		// Print help
		PrintHelp ();

		// Return error
		return (0);
	}		

	// Return no error
	return (0);
}

/*******************************************************************************
* Convert3dsToBrick
*******************************************************************************/
int Convert3dsToBrick (char* cpInput, char* cpOutput) {
	LGBrick		bBrick;
	FILE_3DS	fFile3ds;

	// Read 3ds file
	fFile3ds.read3DS (cpInput);

	// Convert

	// Write output
	LGBrick.writeToFile (cpOutput);
}

/*******************************************************************************
* Convert3dsToBricks
*******************************************************************************/
int Convert3dsToBricks (char* cpInput, char* cpOutput) {
}

/*******************************************************************************
* Convert3dsToBricklib
*******************************************************************************/
int Convert3dsToBricklib (char* cpInput, char* cpOutput) {
}

/*******************************************************************************
* ConvertBricksToBricklib
*******************************************************************************/
int ConvertBricksToBricklib (char* cpInput, char* cpOutput) {
}

/*******************************************************************************
* ConvertObjectsToObjectlib
*******************************************************************************/
int ConvertObjectsToObjectlib (char* cpInput, char* cpOutput) {
}

/*******************************************************************************
* PrintHelp
*******************************************************************************/
int PrintHelp (void) {

	// Print help
	printf ("L3G0 Conv can convert files used with the L3G0 engine.\n");
	printf ("\n");
	printf ("Usage: lg30_conv [OPTION]...\n");
	printf ("\n");
	printf ("Examples:\n");
	printf ("\n");
	printf ("Main operation mode:\n");
  	printf ("  -3, --3dstobrick       convert 3ds-file to a brick-file\n");
	printf ("                         - 3ds file must be in data/models/3ds\n");
	printf ("                         - brick file will be placed in data/models/bricks\n");
	printf ("                         - default input is default.3ds\n");
	printf ("                         - default output is <inputfile>.obj\n");
	printf ("  -b, --3dstobricks      convert a directory of 3ds-files to brick-files\n");
	printf ("                         - default input is data/models/3ds\n");
	printf ("                         - default output is data/models/bricks\n");
	printf ("  -l, --3dstobricklib    convert a directory of 3ds-files to a bricklib\n");
	printf ("                         - default input is data/models/3ds\n");
	printf ("                         - default output is data/models/bricks/default.blb\n");
	printf ("  -k, --bricktobricklib  convert a directory of brick-files to a bricklib\n");
	printf ("                         - default input is data/models/bricks\n");
	printf ("                         - default output is data/models/bricks/default.blb\n");
	printf ("  -o, --objtoobjlib      convert a directory of object-files to a objectlib-file\n");
	printf ("                         - default input is data/models/objects\n");
	printf ("                         - default output is data/models/objects/default.obl\n");
	printf ("\n");
	printf ("Operation modifiers:\n");
	printf ("  -i, --input          select inputfile or inputdirectory\n");
	printf ("  -o, --output         select outputfile or outputdirectory\n");
	printf ("\n");
	printf ("Other options:\n");
	printf ("  -v, --verbose        print verbose output\n");
	printf ("  -h, --help           print help\n");
	printf ("\n");

	// Return no error
	return (0);
}

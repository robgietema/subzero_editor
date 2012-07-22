/*******************************************************************************
* File:		lg_print.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		19 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../include/lg_print.h"

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////
bool	bVerbose = true;			// Verbose on / off
FILE*	fpLogFile;					// Logfile
bool	bPrintToScreen = true;		// Print to screen

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* VerbosePrintf
*******************************************************************************/
int VerbosePrintf (char* acFormatString, ...) {
	va_list vaArgumentList;		// Argument list
	char	acPrintBuffer[512];	// Print buffer

	// If verbose is on
	if (bVerbose == true) {

		// Parse function parameters
		va_start (vaArgumentList, acFormatString);
		vsprintf (acPrintBuffer, acFormatString, vaArgumentList);
		va_end (vaArgumentList);
		
		// append newline
		strcat (acPrintBuffer, "\n");
		
		// print message
		if (bPrintToScreen == true) {

			// Print to screen
			printf (acPrintBuffer);
		} else {

			// Print to file
			fprintf (fpLogFile, acPrintBuffer);
		}
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* ErrorPrintf
*******************************************************************************/
int ErrorPrintf (char* acFormatString, ...) {
	va_list vaArgumentList;		// Argument list
	char	acPrintBuffer[512];	// Print buffer

	// Parse function parameters
	va_start (vaArgumentList, acFormatString);
	vsprintf (acPrintBuffer, acFormatString, vaArgumentList);
	va_end (vaArgumentList);
	
	// append newline
	strcat (acPrintBuffer, "\n");
	
	// print message
	if (bPrintToScreen == true) {

		// Print to screen
		printf (acPrintBuffer);
	} else {

		// Print to file
		fprintf (fpLogFile, acPrintBuffer);
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* InitPrint
*******************************************************************************/
int InitPrint () {

	// Open log file
	fpLogFile = fopen (LOG_FILE, "w");

	// Set print to screen
	bPrintToScreen = false;

	// Return no error
	return (0);
}

/*******************************************************************************
* InitPrintToScreen
*******************************************************************************/
int InitPrintToScreen () {

	// Set print to screen
	bPrintToScreen = true;

	// Return no error
	return (0);
}

/*******************************************************************************
* DeInitPrint
*******************************************************************************/
int DeInitPrint () {

	// Check if not print to screen
	if (bPrintToScreen == false) {

		// Close log file
		fclose (fpLogFile);
	}

	// Return no error
	return (0);
}

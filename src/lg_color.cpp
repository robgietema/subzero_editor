/*******************************************************************************
* File:		lg_color.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../include/lg_datatypes.h"

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* InitColors
*******************************************************************************/
int InitColor () {
	extern LGColor3b	acColors[NR_OF_COLORS];	// Colors

	// Medium blue
	acColors[0].bR = 120;
	acColors[0].bG = 150;
	acColors[0].bB = 207;

	// Blue
	acColors[1].bR = 0;
	acColors[1].bG = 87;
	acColors[1].bB = 166;

	// Red
	acColors[2].bR = 189;
	acColors[2].bG = 56;
	acColors[2].bB = 38;

	// Purple
	acColors[3].bR = 110;
	acColors[3].bG = 18;
	acColors[3].bB = 115;

	// Yellow
	acColors[4].bR = 247;
	acColors[4].bG = 209;
	acColors[4].bB = 23;

	// White
	acColors[5].bR = 232;
	acColors[5].bG = 227;
	acColors[5].bB = 217;

	// Orange
	acColors[6].bR = 242;
	acColors[6].bG = 125;
	acColors[6].bB = 0;

	// Green
	acColors[7].bR = 0;
	acColors[7].bG = 130;
	acColors[7].bB = 74;

	// Light Gray
	acColors[8].bR = 163;
	acColors[8].bG = 161;
	acColors[8].bB = 153;

	// Black
	acColors[9].bR = 33;
	acColors[9].bG = 33;
	acColors[9].bB = 33;

	// Dark Gray
	acColors[10].bR = 112;
	acColors[10].bG = 112;
	acColors[10].bB = 97;

	// Brown
	acColors[11].bR = 97;
	acColors[11].bG = 48;
	acColors[11].bB = 5;

	// Tan
	acColors[12].bR = 214;
	acColors[12].bG = 191;
	acColors[12].bB = 145;

	// Light Yellow
	acColors[13].bR = 247;
	acColors[13].bG = 214;
	acColors[13].bB = 125;

	// Sand Blue
	acColors[14].bR = 92;
	acColors[14].bG = 120;
	acColors[14].bB = 143;

	// Sand Green
	acColors[15].bR = 112;
	acColors[15].bG = 130;
	acColors[15].bB = 112;

	// Dark Orange
	acColors[16].bR = 179;
	acColors[16].bG = 84;
	acColors[16].bB = 8;

	// Light Green
	acColors[17].bR = 61;
	acColors[17].bG = 212;
	acColors[17].bB = 133;

	// Teal
	acColors[18].bR = 0;
	acColors[18].bG = 138;
	acColors[18].bB = 128;

	// Lime Green
	acColors[19].bR = 158;
	acColors[19].bG = 171;
	acColors[19].bB = 5;

	// Mearsk Blue
	acColors[20].bR = 92;
	acColors[20].bG = 186;
	acColors[20].bB = 204;

	// Dark Red
	acColors[21].bR = 133;
	acColors[21].bG = 54;
	acColors[21].bB = 15;

	// Dark Blue
	acColors[22].bR = 0;
	acColors[22].bG = 48;
	acColors[22].bB = 92;

	// Swamp Green
	acColors[23].bR = 0;
	acColors[23].bG = 150;
	acColors[23].bB = 69;

	// Dark Pink
	acColors[24].bR = 209;
	acColors[24].bG = 97;
	acColors[24].bB = 156;

	// Light Orange
	acColors[25].bR = 247;
	acColors[25].bG = 163;
	acColors[25].bB = 10;

	// Sand Red
	acColors[26].bR = 153;
	acColors[26].bG = 112;
	acColors[26].bB = 89;

	// Light Violet
	acColors[27].bR = 171;
	acColors[27].bG = 176;
	acColors[27].bB = 199;

	// Return no error
	return (0);
}


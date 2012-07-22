/*******************************************************************************
* File:		l3g0.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		27 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <windows.h>								// Header File For Windows
#include <gl\gl.h>									// Header File For The OpenGL32 Library
#include <gl\glu.h>									// Header File For The GLu32 Library
#include <stdio.h>									// Header File For Standard Input/Output
#include <io.h>										// Header file For Input/Output
#include "../include/lg_opengl.h"					// Header File For NeHeGL
#include "../include/lg_engine.h"					// Header File For NeHeGL
#include "../include/lg_font2d.h"					// Header file for font
#include "../include/lg_color.h"					// Header file for color
#include "../include/glext.h"						// Header file for opengl extensions
#include "../include/level/lg_level.h"				// Header file for level
#include "../include/level/lg_point.h"				// Header file for point
#include "../include/level/lg_object.h"				// Header file for object

float			g_flYRot = 0.0f;						// Rotation
int				g_nFPS = 0, g_nFrames = 0;				// FPS and FPS Counter
DWORD			g_dwLastFPS = 0;						// Last FPS Check Time	
extern DWORD	dTicks;									// Milliseconds count
extern DWORD	dGlobalTicks;							// Milliseconds count
LGLevel			*lLevel;								// Level
LGFont2d		fFont2d;								// Font 2d
GLuint			atSelect[2];							// Selection textures
GLuint			atToolbar[32];							// Toolbar textures
GLuint			atTabs[16];								// Tabs textures

GLuint			atWalls[10];
GLuint			atItems[6];
GLuint			atEnemies[3];
GLuint			atCritters[3];

LGColor3b		acColors[NR_OF_COLORS];					// Colors
int				aiSelected[2];							// Selected brick (objectgroup, brick)
bool			bFSAA=true;								// Anti aliasing
LGVertex3f		avTranslation[4];						// Translation of views
int				iSelectedView=0;						// Selected view
int				iSelectedTab=0;							// Selected view
LGVertex3f		vpVerticesSelect[4];					// Vertices of select box
LGTextureuv		tpTexturesSelect[4];					// UV coords of select box
LGVertex3f		vpVerticesButton[4];					// Vertices of select box
LGTextureuv		tpTexturesButton[4];					// UV coords of select box
LGVertex3f		vpVerticesLabel[4];						// Vertices of select box
LGTextureuv		tpTexturesLabel[4];						// UV coords of select box
LGVertex3f		vpVerticesDialog[4];					// Vertices of select box
LGTextureuv		tpTexturesDialog[4];					// UV coords of select box
LGVertex3f		vpVerticesBrick[4];						// Vertices of select box
LGTextureuv		tpTexturesBrick[4];						// UV coords of select box
int				iSelectedTool=0;						// Selected tool
bool			bPlay=false;
int				iObjectGroupsPage = 0;
int				iBlockTypesPage = 0;
int				iColorsPage = 0;
int				iEntriesPerPage = 22;
bool			bShowDialog = false;
int				iDialog = 0;
char			acDialogString[256];
int				iDialogIndex = 0;
int				iCurrentObjectGroup = 0;
int				iBrickListPage = 0;
bool			bLighting = false;
bool			bDrawLine=false;

int				iTotalTextures = 8;
int				iTotalEnemies = 3;
int				iTotalItems = 5;
int				iTotalCritters = 3;

GLfloat Shine = 10.0;
GLfloat LightAmbient[]= { 0.1f, 0.1f, 0.1f, 1.0f};
GLfloat LightDiffuse[]= { 1.5f, 1.5f, 1.5f, 1.0f};
GLfloat LightPosition[]= { 0.0f, 0.0f, 1.0f, 0.0f };
GLfloat SpecularColor[] = {1.0, 1.0, 1.0};
GLfloat SpotDirection[]= { 1.0f, -1.0f, -1.0f };
GLfloat SpotExponent[] = { 128.0 };
GLfloat SpotCutoff[] = { 50.0 };

/*******************************************************************************
* Initialize
*******************************************************************************/
BOOL Initialize (LGWindow* wWindow, LGKeys* kKeys) {
	float fWidth = 0.0556f;
	float fHeight = 0.0420f;

	// Init translation
	for (int iCount = 0; iCount < 4; iCount++) {

		// Reset values
		avTranslation[0].fX = 0.0f;
		avTranslation[0].fY = 0.0f;
		avTranslation[0].fZ = 0.0f;
	}

	// Init selectbox
	vpVerticesSelect[0].fX = -1 * fWidth;
	vpVerticesSelect[0].fY = -1 * fHeight;
	vpVerticesSelect[0].fZ = 0.0f;
	tpTexturesSelect[0].fU = 0.0f;
	tpTexturesSelect[0].fV = 0.0f;

	vpVerticesSelect[1].fX = fWidth;
	vpVerticesSelect[1].fY = -1 * fHeight;
	vpVerticesSelect[1].fZ = 0.0f;
	tpTexturesSelect[1].fU = 1.0f;
	tpTexturesSelect[1].fV = 0.0f;

	vpVerticesSelect[2].fX = fWidth;
	vpVerticesSelect[2].fY = fHeight;
	vpVerticesSelect[2].fZ = 0.0f;
	tpTexturesSelect[2].fU = 1.0f;
	tpTexturesSelect[2].fV = 1.0f;

	vpVerticesSelect[3].fX = -1 * fWidth;
	vpVerticesSelect[3].fY = fHeight;
	vpVerticesSelect[3].fZ = 0.0f;
	tpTexturesSelect[3].fU = 0.0f;
	tpTexturesSelect[3].fV = 1.0f;

	// Init button
	vpVerticesButton[0].fX = 0.0f;
	vpVerticesButton[0].fY = 0.0f;
	vpVerticesButton[0].fZ = 0.0f;
	tpTexturesButton[0].fU = 0.0f;
	tpTexturesButton[0].fV = 0.0f;

	vpVerticesButton[1].fX = 0.00345f;
	vpVerticesButton[1].fY = 0.0f;
	vpVerticesButton[1].fZ = 0.0f;
	tpTexturesButton[1].fU = 1.0f;
	tpTexturesButton[1].fV = 0.0f;

	vpVerticesButton[2].fX = 0.00345f;
	vpVerticesButton[2].fY = 0.00345f;
	vpVerticesButton[2].fZ = 0.0f;
	tpTexturesButton[2].fU = 1.0f;
	tpTexturesButton[2].fV = 1.0f;

	vpVerticesButton[3].fX = 0.0f;
	vpVerticesButton[3].fY = 0.00345f;
	vpVerticesButton[3].fZ = 0.0f;
	tpTexturesButton[3].fU = 0.0f;
	tpTexturesButton[3].fV = 1.0f;

	// Init label
	vpVerticesLabel[0].fX = 0.0f;
	vpVerticesLabel[0].fY = 0.0f;
	vpVerticesLabel[0].fZ = 0.0f;
	tpTexturesLabel[0].fU = 0.0f;
	tpTexturesLabel[0].fV = 0.0f;

	vpVerticesLabel[1].fX = 0.0138f;
	vpVerticesLabel[1].fY = 0.0f;
	vpVerticesLabel[1].fZ = 0.0f;
	tpTexturesLabel[1].fU = 1.0f;
	tpTexturesLabel[1].fV = 0.0f;

	vpVerticesLabel[2].fX = 0.0138f;
	vpVerticesLabel[2].fY = 0.00345f;
	vpVerticesLabel[2].fZ = 0.0f;
	tpTexturesLabel[2].fU = 1.0f;
	tpTexturesLabel[2].fV = 1.0f;

	vpVerticesLabel[3].fX = 0.0f;
	vpVerticesLabel[3].fY = 0.00345f;
	vpVerticesLabel[3].fZ = 0.0f;
	tpTexturesLabel[3].fU = 0.0f;
	tpTexturesLabel[3].fV = 1.0f;

	// Init dialog
	vpVerticesDialog[0].fX = 0.0f;
	vpVerticesDialog[0].fY = 0.0f;
	vpVerticesDialog[0].fZ = 0.0f;
	tpTexturesDialog[0].fU = 0.0f;
	tpTexturesDialog[0].fV = 0.0f;

	vpVerticesDialog[1].fX = 0.0276f;
	vpVerticesDialog[1].fY = 0.0f;
	vpVerticesDialog[1].fZ = 0.0f;
	tpTexturesDialog[1].fU = 1.0f;
	tpTexturesDialog[1].fV = 0.0f;

	vpVerticesDialog[2].fX = 0.0276f;
	vpVerticesDialog[2].fY = 0.016f;
	vpVerticesDialog[2].fZ = 0.0f;
	tpTexturesDialog[2].fU = 1.0f;
	tpTexturesDialog[2].fV = 1.0f;

	vpVerticesDialog[3].fX = 0.0f;
	vpVerticesDialog[3].fY = 0.016f;
	vpVerticesDialog[3].fZ = 0.0f;
	tpTexturesDialog[3].fU = 0.0f;
	tpTexturesDialog[3].fV = 1.0f;

	// Init brick
	vpVerticesBrick[0].fX = 0.0f;
	vpVerticesBrick[0].fY = 0.0f;
	vpVerticesBrick[0].fZ = 0.0f;
	tpTexturesBrick[0].fU = 0.0f;
	tpTexturesBrick[0].fV = 0.0f;

	vpVerticesBrick[1].fX = 0.0069f;
	vpVerticesBrick[1].fY = 0.0f;
	vpVerticesBrick[1].fZ = 0.0f;
	tpTexturesBrick[1].fU = 1.0f;
	tpTexturesBrick[1].fV = 0.0f;

	vpVerticesBrick[2].fX = 0.0069f;
	vpVerticesBrick[2].fY = 0.0069f;
	vpVerticesBrick[2].fZ = 0.0f;
	tpTexturesBrick[2].fU = 1.0f;
	tpTexturesBrick[2].fV = 1.0f;

	vpVerticesBrick[3].fX = 0.0f;
	vpVerticesBrick[3].fY = 0.0069f;
	vpVerticesBrick[3].fZ = 0.0f;
	tpTexturesBrick[3].fU = 0.0f;
	tpTexturesBrick[3].fV = 1.0f;

	// Init selected
	aiSelected[0] = 0;
	aiSelected[1] = 0;

	InitPrint ();
	InitColor ();
	fFont2d.init ();

	// Load select textures
	LoadTGA ("data/textures/editor/select_selected.tga", atSelect[0]);
	LoadTGA ("data/textures/editor/select.tga", atSelect[1]);

	// Load level textures
	LoadTGA ("data/textures/walls/t00.tga", atWalls[0]);
	LoadTGA ("data/textures/walls/t10.tga", atWalls[1]);
	LoadTGA ("data/textures/walls/t20.tga", atWalls[2]);
	LoadTGA ("data/textures/walls/t30.tga", atWalls[3]);
	LoadTGA ("data/textures/walls/t40.tga", atWalls[4]);
	LoadTGA ("data/textures/walls/t50.tga", atWalls[5]);
	LoadTGA ("data/textures/walls/t60.tga", atWalls[6]);
	LoadTGA ("data/textures/walls/t70.tga", atWalls[7]);

	LoadTGA ("data/textures/items/i0.tga", atItems[0]);
	LoadTGA ("data/textures/items/i1.tga", atItems[1]);
	LoadTGA ("data/textures/items/i2.tga", atItems[2]);
	LoadTGA ("data/textures/items/i3.tga", atItems[3]);
	LoadTGA ("data/textures/items/i4.tga", atItems[4]);

	LoadTGA ("data/textures/enemies/s0.tga", atEnemies[0]);
	LoadTGA ("data/textures/enemies/s1.tga", atEnemies[1]);
	LoadTGA ("data/textures/enemies/s2.tga", atEnemies[2]);

	LoadTGA ("data/textures/critters/c0.tga", atCritters[0]);
	LoadTGA ("data/textures/critters/c1.tga", atCritters[1]);
	LoadTGA ("data/textures/critters/c2.tga", atCritters[2]);

	// Load toolbar textures
	LoadTGA ("data/textures/editor/new.tga", atToolbar[0]);
	LoadTGA ("data/textures/editor/open.tga", atToolbar[1]);
	LoadTGA ("data/textures/editor/save.tga", atToolbar[2]);
	LoadTGA ("data/textures/editor/verts.tga", atToolbar[3]);
	LoadTGA ("data/textures/editor/verts_selected.tga", atToolbar[4]);
	LoadTGA ("data/textures/editor/verts_tune.tga", atToolbar[5]);
	LoadTGA ("data/textures/editor/verts_tune_selected.tga", atToolbar[6]);
	LoadTGA ("data/textures/editor/objects.tga", atToolbar[7]);
	LoadTGA ("data/textures/editor/objects_selected.tga", atToolbar[8]);
	LoadTGA ("data/textures/editor/cammove.tga", atToolbar[9]);
	LoadTGA ("data/textures/editor/cammove_selected.tga", atToolbar[10]);

	LoadTGA ("data/textures/editor/animpoint.tga", atToolbar[17]);
	LoadTGA ("data/textures/editor/range.tga", atToolbar[18]);
	LoadTGA ("data/textures/editor/framesperbrick.tga", atToolbar[19]);
	LoadTGA ("data/textures/editor/framesbetweenbricks.tga", atToolbar[20]);
	LoadTGA ("data/textures/editor/group_move.tga", atToolbar[21]);
	LoadTGA ("data/textures/editor/group_move_selected.tga", atToolbar[22]);
	LoadTGA ("data/textures/editor/group_rotate.tga", atToolbar[23]);
	LoadTGA ("data/textures/editor/group_rotate_selected.tga", atToolbar[24]);
	LoadTGA ("data/textures/editor/group_rotatepoint.tga", atToolbar[25]);
	LoadTGA ("data/textures/editor/group_rotatepoint_selected.tga", atToolbar[26]);
	LoadTGA ("data/textures/editor/sortbricks.tga", atToolbar[27]);
	LoadTGA ("data/textures/editor/group_tune.tga", atToolbar[28]);
	LoadTGA ("data/textures/editor/group_tune_selected.tga", atToolbar[29]);
	LoadTGA ("data/textures/editor/clonegroup.tga", atToolbar[30]);
	LoadTGA ("data/textures/editor/replacecolor.tga", atToolbar[31]);

	// Load tabs textures
	LoadTGA ("data/textures/editor/objectgroups.tga", atTabs[0]);
	LoadTGA ("data/textures/editor/objectgroups_selected.tga", atTabs[1]);
	LoadTGA ("data/textures/editor/blocktypes.tga", atTabs[2]);
	LoadTGA ("data/textures/editor/blocktypes_selected.tga", atTabs[3]);
	LoadTGA ("data/textures/editor/colors.tga", atTabs[4]);
	LoadTGA ("data/textures/editor/colors_selected.tga", atTabs[5]);
	LoadTGA ("data/textures/editor/objectgroup.tga", atTabs[6]);
	LoadTGA ("data/textures/editor/objectgroup_selected.tga", atTabs[7]);
	LoadTGA ("data/textures/editor/editname.tga", atTabs[8]);
	LoadTGA ("data/textures/editor/edittime.tga", atTabs[9]);
	LoadTGA ("data/textures/editor/hide.tga", atTabs[10]);
	LoadTGA ("data/textures/editor/hide_selected.tga", atTabs[11]);
	LoadTGA ("data/textures/editor/prevpage.tga", atTabs[12]);
	LoadTGA ("data/textures/editor/nextpage.tga", atTabs[13]);
	LoadTGA ("data/textures/editor/newgroup.tga", atTabs[14]);
	LoadTGA ("data/textures/editor/deletegroup.tga", atTabs[15]);

	lLevel = new LGLevel[1];
	lLevel[0].initDefaultValues ();
//	lLevel[0].readFromFile ("data/objects/object1.obj");

	lLevel[0].ppPoints[aiSelected[0]].bSelected = true;
	lLevel[0].opObjects[aiSelected[1]].bSelected = true;

	// Setup GL States
	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);						// Black Background
	glClearDepth (1.0f);										// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);			// Select The Type Of Blending
	glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
	glDisable (GL_BLEND);
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate
	glEnable( GL_TEXTURE_2D );									// Enable Textures
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );						// Set The Color To White
	glEnable(GL_CULL_FACE);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);

	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularColor);
	glMaterialfv(GL_FRONT, GL_SHININESS, &Shine);

	glEnable(GL_LIGHT1);

	// Goto begin
	dTicks = 0;

	// Return no error
	return TRUE;												// Return TRUE (Initialization Successful)
}

/*******************************************************************************
* Deinitialize
*******************************************************************************/
void Deinitialize () {

	// De init print
	DeInitPrint ();
}

/*******************************************************************************
* OnKeyDown
*******************************************************************************/
void OnKeyDown (WPARAM wParam, LGWindow* wWindow) {

	// Get key
	switch (wParam) {
		case VK_ESCAPE:

			// Terminate the program
			TerminateApplication (wWindow);
			break;
		case VK_F1:

			// Set tool
			iSelectedTool = 0;
			break;
		case VK_F2:

			// Set tool
			iSelectedTool = 1;
			break;
		case VK_F3:

			// Set tool
			iSelectedTool = 2;
			break;
		case VK_F4:

			// Set tool
			iSelectedTool = 3;
			break;
		case VK_TAB:

			// Toggle Fullscreen Mode
			ToggleFullscreen (wWindow);
			break;
		case VK_UP:

			// If point move
			if (iSelectedTool == 0) {
				switch (iSelectedView) {
					case 0:
					case 1:
						lLevel[0].opObjects[aiSelected[1]].vVert1.fY += 0.1f;
						break;
					case 2:
					case 3:
						lLevel[0].opObjects[aiSelected[1]].vVert1.fZ -= 0.1f;
						break;
				}
			} else if (iSelectedTool == 1) {
				switch (iSelectedView) {
					case 0:
					case 1:
						lLevel[0].opObjects[aiSelected[1]].vVert2.fY += 0.1f;
						break;
					case 2:
					case 3:
						lLevel[0].opObjects[aiSelected[1]].vVert2.fZ -= 0.1f;
						break;
				}
			}
			break;
		case VK_DOWN:

			// If brick move
			if (iSelectedTool == 0) {
				switch (iSelectedView) {
					case 0:
					case 1:
						lLevel[0].opObjects[aiSelected[1]].vVert1.fY -= 0.1f;
						break;
					case 2:
					case 3:
						lLevel[0].opObjects[aiSelected[1]].vVert1.fZ += 0.1f;
						break;
				}
			} else if (iSelectedTool == 1) {
				switch (iSelectedView) {
					case 0:
					case 1:
						lLevel[0].opObjects[aiSelected[1]].vVert2.fY -= 0.1f;
						break;
					case 2:
					case 3:
						lLevel[0].opObjects[aiSelected[1]].vVert2.fZ += 0.1f;
						break;
				}
			}
			break;
		case VK_LEFT:

			// If brick move
			if (iSelectedTool == 0) {
				switch (iSelectedView) {
					case 0:
					case 3:
					case 2:
						lLevel[0].opObjects[aiSelected[1]].vVert1.fX -= 0.1f;
						break;
					case 1:
						lLevel[0].opObjects[aiSelected[1]].vVert1.fZ -= 0.1f;
						break;
				}
			} else if (iSelectedTool == 1) {
				switch (iSelectedView) {
					case 0:
					case 3:
					case 2:
						lLevel[0].opObjects[aiSelected[1]].vVert2.fX -= 0.1f;
						break;
					case 1:
						lLevel[0].opObjects[aiSelected[1]].vVert2.fZ -= 0.1f;
						break;
				}
			}
			break;
		case VK_RIGHT:

			// If brick move
			if (iSelectedTool == 0) {
				switch (iSelectedView) {
					case 0:
					case 3:
					case 2:
						lLevel[0].opObjects[aiSelected[1]].vVert1.fX += 0.1f;
						break;
					case 1:
						lLevel[0].opObjects[aiSelected[1]].vVert1.fZ += 0.1f;
						break;
				}
			} else if (iSelectedTool == 1) {
				switch (iSelectedView) {
					case 0:
					case 3:
					case 2:
						lLevel[0].opObjects[aiSelected[1]].vVert2.fX += 0.1f;
						break;
					case 1:
						lLevel[0].opObjects[aiSelected[1]].vVert2.fZ += 0.1f;
						break;
				}
			}
			break;
		case VK_PRIOR:

			// If brick move
			if (iSelectedTool == 0) {
				if (iSelectedView == 2) {
					lLevel[0].opObjects[aiSelected[1]].vVert1.fY += 0.1f;
				}
			} else if (iSelectedTool == 1) {
				if (iSelectedView == 2) {
					lLevel[0].opObjects[aiSelected[1]].vVert2.fY += 0.1f;
				}
			}
			break;
		case VK_NEXT:

			// If brick move
			if (iSelectedTool == 0) {
				if (iSelectedView == 2) {
					lLevel[0].opObjects[aiSelected[1]].vVert1.fY -= 0.1f;
				}
			} else if (iSelectedTool == 1) {
				if (iSelectedView == 2) {
					lLevel[0].opObjects[aiSelected[1]].vVert2.fY -= 0.1f;
				}
			}
			break;
		case 'L':
			if (bShowDialog == false) {
				if (bLighting == true) {
					bLighting = false;
				} else {
					bLighting = true;
				}
			}
			break;
		case 'Q':
			if (bShowDialog == false) {
				if (iSelectedTool == 0 || iSelectedTool == 1 || iSelectedTool == 2) {
					lLevel[0].opObjects[aiSelected[1]].bSelected = false;
					aiSelected[1] += lLevel[0].iNrOfObjects - 1;
					aiSelected[1] %= lLevel[0].iNrOfObjects;
					lLevel[0].opObjects[aiSelected[1]].bSelected = true;
				}
			}
			break;
		case 'W':
			if (bShowDialog == false) {
				if (iSelectedTool == 0 || iSelectedTool == 1 || iSelectedTool == 2) {
					lLevel[0].opObjects[aiSelected[1]].bSelected = false;
					aiSelected[1]++;
					aiSelected[1] %= lLevel[0].iNrOfObjects;
					lLevel[0].opObjects[aiSelected[1]].bSelected = true;
				}
			}
			break;
		case 'E':
			if (bShowDialog == false) {
				if (iSelectedTool == 0 || iSelectedTool == 1 || iSelectedTool == 2) {
					lLevel[0].opObjects[aiSelected[1]].fHeight += 0.1f;
				}
			}
			break;
		case 'D':
			if (bShowDialog == false) {
				if (iSelectedTool == 0 || iSelectedTool == 1 || iSelectedTool == 2) {
					lLevel[0].opObjects[aiSelected[1]].fHeight -= 0.1f;
				}
			}
			break;
		case 'T':
			if (bShowDialog == false) {
				if (iSelectedTool == 0 || iSelectedTool == 1 || iSelectedTool == 2) {
					if (lLevel[0].opObjects[aiSelected[1]].iType == 0) {
						lLevel[0].opObjects[aiSelected[1]].iTexture++;
						lLevel[0].opObjects[aiSelected[1]].iTexture%=iTotalTextures;
					} else {
						switch (lLevel[0].opObjects[aiSelected[1]].iSubType) {
							case 0:
								lLevel[0].opObjects[aiSelected[1]].iEnemy++;
								lLevel[0].opObjects[aiSelected[1]].iEnemy%=iTotalEnemies;
								break;
							case 2:
								lLevel[0].opObjects[aiSelected[1]].iItem++;
								lLevel[0].opObjects[aiSelected[1]].iItem%=iTotalItems;
								break;
							case 3:
								lLevel[0].opObjects[aiSelected[1]].iCritter++;
								lLevel[0].opObjects[aiSelected[1]].iCritter%=iTotalCritters;
								break;
						}
					}
				}
			}
			break;
		case 'S':
			if (bShowDialog == false) {
				if (iSelectedTool == 0 || iSelectedTool == 1 || iSelectedTool == 2) {
					lLevel[0].opObjects[aiSelected[1]].fWidth -= 0.1f;
				}
			}
			break;
		case 'F':
			if (bShowDialog == false) {
				if (iSelectedTool == 0 || iSelectedTool == 1 || iSelectedTool == 2) {
					lLevel[0].opObjects[aiSelected[1]].fWidth += 0.1f;
				}
			}
			break;
		case 'Y':
			if (bShowDialog == false) {
				if (iSelectedTool == 0 || iSelectedTool == 1 || iSelectedTool == 2) {
					lLevel[0].opObjects[aiSelected[1]].iType++;
					lLevel[0].opObjects[aiSelected[1]].iType%=2;
				}
			}
			break;
		case 'H':
			if (bShowDialog == false) {
				if (iSelectedTool == 0 || iSelectedTool == 1 || iSelectedTool == 2) {
					if (lLevel[0].opObjects[aiSelected[1]].iSubType == 0) {
						lLevel[0].opObjects[aiSelected[1]].iSubType = 2;
					} else if (lLevel[0].opObjects[aiSelected[1]].iSubType == 2) {
						lLevel[0].opObjects[aiSelected[1]].iSubType = 3;
					} else if (lLevel[0].opObjects[aiSelected[1]].iSubType == 3) {
						lLevel[0].opObjects[aiSelected[1]].iSubType = 0;
					}
				}
			}
			break;
		case '1':
			iSelectedView = 0;
			break;
		case '2':
			iSelectedView = 1;
			break;
		case '3':
			iSelectedView = 3;
			break;
		case '4':
			iSelectedView = 2;
			break;
		case VK_DELETE:

			if (iSelectedTool == 0 || iSelectedTool == 1 || iSelectedTool == 2) {
				// Delete object
				if (lLevel[0].iNrOfObjects > 1) {
					lLevel[0].deleteObject (aiSelected[1]);
				}

				// Check selection
				if (aiSelected[1] > lLevel[0].iNrOfObjects-1) {
					aiSelected[1] = lLevel[0].iNrOfObjects-1;
				}
				lLevel[0].opObjects[aiSelected[1]].bSelected = true;
			}
			break;
		case VK_INSERT:

			if (iSelectedTool == 0 || iSelectedTool == 1 || iSelectedTool == 2) {
				lLevel[0].insertObject (aiSelected[1]);
				lLevel[0].opObjects[aiSelected[1]+1].bSelected = false;
			}
			break;
	}

	if (bShowDialog == true) {
		if ((((char)wParam >= 'A') &&((char)wParam <= 'Z')) || (((char)wParam >= '0') && ((char)wParam <= '9')) || ((char)wParam == ' ')) {
			char aNew[2];
			aNew[0] = tolower ((char)wParam);
			aNew[1] = '\0';
			if (strlen (acDialogString) < 15) {
				strcat (acDialogString, aNew);
			}
		}
		if (wParam == VK_BACK) {
			if (strlen (acDialogString) > 0) {
				acDialogString[strlen (acDialogString) - 1] = '\0';
			}
		}
		if (wParam == VK_RETURN) {
			switch (iDialog) {
				case 6:
					lLevel[0].writeToFile (acDialogString);
					break;
			}
			bShowDialog = false;
		}
	}
}

/*******************************************************************************
* Update
*******************************************************************************/
void Update (DWORD dMilliseconds, LGWindow* wWindow, LGKeys* kKeys) {
	extern int iMouseX;								// Mouse x position
	extern int iMouseY;								// Mouse y position
	extern int iMouseButtonRight;					// Right button pressed
	extern int iMouseButtonLeft;					// Left button pressed
	extern int iMouseButtonMiddle;					// Middle button pressed
	extern int iMouseDownX;							// X of mouse down
	extern int iMouseDownY;							// Y of mouse down

	// Update global ticks
	dGlobalTicks += dMilliseconds;

	// If up pressed
	if (kKeys->abKeyDown [VK_UP] == TRUE) {

		// Get tool
		switch (iSelectedTool) {
			case 3:
				// Translate
				avTranslation[iSelectedView].fZ -= 1.0f;
				break;
		}
	}

	// If down pressed
	if (kKeys->abKeyDown [VK_DOWN] == TRUE) {

		// Get tool
		switch (iSelectedTool) {
			case 3:
				// Translate
				avTranslation[iSelectedView].fZ += 1.0f;
				break;
		}
	}

	// If left pressed
	if (kKeys->abKeyDown [VK_LEFT] == TRUE) {

		// Get tool
		switch (iSelectedTool) {
			case 3:
				// Translate
				avTranslation[iSelectedView].fX -= 1.0f;
				break;
		}
	}

	// If right pressed
	if (kKeys->abKeyDown [VK_RIGHT] == TRUE) {

		// Get tool
		switch (iSelectedTool) {
			case 3:
				// Translate
				avTranslation[iSelectedView].fX += 1.0f;
				break;
		}
	}

	// If pgup pressed
	if (kKeys->abKeyDown [VK_PRIOR] == TRUE) {

		// Get tool
		switch (iSelectedTool) {
			case 3:
				// Translate
				avTranslation[iSelectedView].fY += 1.0f;
				break;
		}
	}

	// If pgdn pressed
	if (kKeys->abKeyDown [VK_NEXT] == TRUE) {

		// Get tool
		switch (iSelectedTool) {
			case 3:
				// Translate
				avTranslation[iSelectedView].fY -= 1.0f;
				break;
		}
	}

	// If home pressed
	if (kKeys->abKeyDown [VK_HOME] == TRUE) {

		// Get tool
		switch (iSelectedTool) {
			case 3:
				// Translate
				avTranslation[iSelectedView].fX = 0.0f;
				avTranslation[iSelectedView].fY = 0.0f;
				avTranslation[iSelectedView].fZ = 0.0f;
				break;
		}
	}
}

/*******************************************************************************
* OnMouseDown
*******************************************************************************/
void OnMouseDown (int iButton, int iMouseX, int iMouseY) {

	// Check if left button pressed
	if (iButton == 0) {
		VerbosePrintf ("Mouse pos: %d, %d", iMouseX, iMouseY);
		// Check if in top left window
		if ((iMouseX > 0) && (iMouseX < 400) && (iMouseY > 32) && (iMouseY < 332)) {

			// Set selected view
			iSelectedView = 0;
		}

		// Check if in top right window
		if ((iMouseX > 400) && (iMouseX < 800) && (iMouseY > 32) && (iMouseY < 332)) {

			// Set selected view
			iSelectedView = 1;
		}

		// Check if in bottom left window
		if ((iMouseX > 0) && (iMouseX < 400) && (iMouseY > 332) && (iMouseY < 632)) {

			// Set selected view
			iSelectedView = 3;
		}

		// Check if in bottom right window
		if ((iMouseX > 400) && (iMouseX < 800) && (iMouseY > 332) && (iMouseY < 632)) {

			// Set selected view
			iSelectedView = 2;
		}

		// Check if new button
		if ((iMouseX > 0) && (iMouseX < 32) && (iMouseY > 0) && (iMouseY < 32)) {
/*
			// Delete object
			delete []oObject;

			// Create new
			oObject = new LGObject[1];
			oObject[0].createNew ();

			// Set selected
			aiSelected[0] = 0;
			aiSelected[1] = 0;
			oObject[0].gpObjectGroups[aiSelected[0]].bpBricks[aiSelected[1]].bSelected = true;
*/
		}

		// Check if open button
		if ((iMouseX > 32) && (iMouseX < 64) && (iMouseY > 0) && (iMouseY < 32)) {

			// Open object
			iDialog = 5;
			bShowDialog = true;

			// Set empty string
			strcpy (acDialogString, "");
		}

		// Check if save button
		if ((iMouseX > 64) && (iMouseX < 96) && (iMouseY > 0) && (iMouseY < 32)) {

			// Save object
			iDialog = 6;
			bShowDialog = true;

			// Set empty string
			strcpy (acDialogString, "");
		}

		// Check if point
		if ((iMouseX > 128) && (iMouseX < 160) && (iMouseY > 0) && (iMouseY < 32)) {

			// Set selected tool
			iSelectedTool = 0;
		}

		// Check if object
		if ((iMouseX > 160) && (iMouseX < 192) && (iMouseY > 0) && (iMouseY < 32)) {

			// Set selected tool
			iSelectedTool = 1;
		}

		// Check if cam
		if ((iMouseX > 192) && (iMouseX < 224) && (iMouseY > 0) && (iMouseY < 32)) {

			// Set selected tool
			iSelectedTool = 2;
		}

		// Check if points tune
		if ((iMouseX > 224) && (iMouseX < 256) && (iMouseY > 0) && (iMouseY < 32)) {

			// Set selected tool
			iSelectedTool = 3;
		}

		// Check if object groups
		if ((iMouseX > 800) && (iMouseX < 832) && (iMouseY > 0) && (iMouseY < 32)) {

			// Set selected tool
			iSelectedTab = 0;
		}

		// Check if blocktypes
		if ((iMouseX > 832) && (iMouseX < 864) && (iMouseY > 0) && (iMouseY < 32)) {

			// Set selected tool
			iSelectedTab = 1;
		}

		// Check if colors
		if ((iMouseX > 864) && (iMouseX < 896) && (iMouseY > 0) && (iMouseY < 32)) {

			// Set selected tool
			iSelectedTab = 2;
		}
/*
		// Check if prev objectgroup
		if ((iMouseX > 0) && (iMouseX < 32) && (iMouseY > 632) && (iMouseY < 664)) {

			// Decrease objectgroup
			iCurrentObjectGroup--;
			if (iCurrentObjectGroup < 0) {
				iCurrentObjectGroup = oObject[0].iNrOfObjectGroups - 1;
			}
		}

		// Check if next objectgroup
		if ((iMouseX > 160) && (iMouseX < 192) && (iMouseY > 632) && (iMouseY < 664)) {

			// Increase objectgroup
			iCurrentObjectGroup++;
			if (iCurrentObjectGroup > oObject[0].iNrOfObjectGroups - 1) {
				iCurrentObjectGroup = 0;
			}
		}

		// Check if new objectgroup
		if ((iMouseX > 192) && (iMouseX < 224) && (iMouseY > 632) && (iMouseY < 664)) {

			// New Objectgroup
			iDialog = 2;
			bShowDialog = true;

			// Set empty string
			strcpy (acDialogString, "");
		}

		// Check if delete objectgroup
		if ((iMouseX > 224) && (iMouseX < 256) && (iMouseY > 632) && (iMouseY < 664)) {

			// Check if not last
			if ((oObject[0].iNrOfObjectGroups > 1) && (oObject[0].getNrOfBricks () - oObject[0].gpObjectGroups[iCurrentObjectGroup].iNrOfBricks >= 1)) {
				
				// Delete objectgroup
				oObject[0].deleteObjectGroup (iCurrentObjectGroup);

				// Check if index after last group
				if (iCurrentObjectGroup > oObject[0].iNrOfObjectGroups - 1) {

					// Set to max
					iCurrentObjectGroup = oObject[0].iNrOfObjectGroups - 1;
				}

				// Check if index after last group
				if (aiSelected[0] > oObject[0].iNrOfObjectGroups - 1) {

					// Cycle through object groups
					for (int iCount = 0; iCount < oObject[0].iNrOfObjectGroups; iCount++) {

						// Check if bricks in group
						if (oObject[0].gpObjectGroups[iCount].iNrOfBricks > 0) {

							// Set new selected group
							aiSelected[0] = iCount;
						}
					}

					// Set first brick in group to selected
					aiSelected[1] = 0;
				}
			}
		}

		// Check if edit frames per brick
		if ((iMouseX > 288) && (iMouseX < 320) && (iMouseY > 632) && (iMouseY < 664)) {

			// Show dialog
			bShowDialog = true;

			// Set dialog type
			iDialog = 3;

			// Set string
			sprintf (acDialogString, "%d", oObject[0].iFramesPerBrick);
		}

		// Check if edit frames between bricks
		if ((iMouseX > 320) && (iMouseX < 352) && (iMouseY > 632) && (iMouseY < 664)) {

			// Show dialog
			bShowDialog = true;

			// Set dialog type
			iDialog = 4;

			// Set string
			sprintf (acDialogString, "%d", oObject[0].iFramesBetweenBricks);
		}

		// Check if sort bricks
		if ((iMouseX > 352) && (iMouseX < 384) && (iMouseY > 632) && (iMouseY < 664)) {

			// Sort objectgroup
			oObject[0].gpObjectGroups[iCurrentObjectGroup].sort ();
		}

		// Check if clonegroup
		if ((iMouseX > 384) && (iMouseX < 416) && (iMouseY > 632) && (iMouseY < 664)) {

			// Sort objectgroup
			oObject[0].cloneObjectGroup (iCurrentObjectGroup);
		}

		// Check if replace color
		if ((iMouseX > 416) && (iMouseX < 448) && (iMouseY > 632) && (iMouseY < 664)) {

			// Replace color
			iDialog = 7;
			bShowDialog = true;

			// Set empty string
			strcpy (acDialogString, "");
		}

		// Check if prev brick in bricklist
		if ((iMouseX > 704) && (iMouseX < 736) && (iMouseY > 632) && (iMouseY < 664)) {

			// Decrease bricklistpage
			iBrickListPage--;
			if (iBrickListPage < 0) {
				iBrickListPage = oObject[0].gpObjectGroups[iCurrentObjectGroup].iNrOfBricks / 12;
			}
		}

		// Check if next brick in bricklist
		if ((iMouseX > 736) && (iMouseX < 768) && (iMouseY > 632) && (iMouseY < 664)) {

			// Increase bricklistpage
			iBrickListPage++;
			if (iBrickListPage > oObject[0].gpObjectGroups[iCurrentObjectGroup].iNrOfBricks / 12) {
				iBrickListPage = 0;
			}
		}

		// Check if brick list entry
		if ((iMouseX > 0) && (iMouseX < 768) && (iMouseY > 664) && (iMouseY < 728)) {

			// Deselect brick
			oObject[0].gpObjectGroups[aiSelected[0]].bpBricks[aiSelected[1]].bSelected = false;

			// Set new brick
			aiSelected[1] = ((iMouseX / 64) + (iBrickListPage * 12));

			// Set new group
			aiSelected[0] = iCurrentObjectGroup;

			// Select brick
			oObject[0].gpObjectGroups[aiSelected[0]].bpBricks[aiSelected[1]].bSelected = true;
		}

		// Check if prev page
		if ((iMouseX > 960) && (iMouseX < 992) && (iMouseY > 0) && (iMouseY < 32)) {

			// Get tab
			switch (iSelectedTab) {
				case 0:
					iObjectGroupsPage--;
					if (iObjectGroupsPage < 0) {
						iObjectGroupsPage = oObject[0].iNrOfObjectGroups / iEntriesPerPage;
					}
					break;
				case 1:
					iBlockTypesPage--;
					if (iBlockTypesPage < 0) {
						iBlockTypesPage = bBrickLib.iNrOfEntries / iEntriesPerPage;
					}
					break;
				case 2:
					iColorsPage--;
					if (iColorsPage < 0) {
						iColorsPage = NR_OF_COLORS / iEntriesPerPage;
					}
					break;
			}
		}

		// Check if next page
		if ((iMouseX > 992) && (iMouseX < 1024) && (iMouseY > 0) && (iMouseY < 32)) {

			// Get tab
			switch (iSelectedTab) {
				case 0:
					iObjectGroupsPage++;
					if (iObjectGroupsPage > oObject[0].iNrOfObjectGroups / iEntriesPerPage) {
						iObjectGroupsPage = 0;
					}
					break;
				case 1:
					iBlockTypesPage++;
					if (iBlockTypesPage > bBrickLib.iNrOfEntries / iEntriesPerPage) {
						iBlockTypesPage = 0;
					}
					break;
				case 2:
					iColorsPage++;
					if (iColorsPage > NR_OF_COLORS / iEntriesPerPage) {
						iColorsPage = 0;
					}
					break;
			}
		}

		// Check selected tab
		if (iSelectedTab == 0) {

			// Check if objectgroup select
			if ((iMouseX > 800) && (iMouseX < 928) && (iMouseY > 32) && (iMouseY < 736)) {

				// Get new objectgroup
				int iNewObjectGroup = (iMouseY - 32) / 32 + (iObjectGroupsPage * iEntriesPerPage);

				// Add brick to new group
				oObject[0].gpObjectGroups[iNewObjectGroup].addBrick (oObject[0].gpObjectGroups[aiSelected[0]].bpBricks[aiSelected[1]]);

				// Delete brick
				oObject[0].gpObjectGroups[aiSelected[0]].deleteBrick (aiSelected[1]);

				// Set new selected
				aiSelected[0] = iNewObjectGroup;
				aiSelected[1] = oObject[0].gpObjectGroups[iNewObjectGroup].iNrOfBricks - 1;
				oObject[0].calcAnimStart (aiSelected[0], aiSelected[1]);
			}

			// Toggle hidden
			if ((iMouseX > 928) && (iMouseX < 960) && (iMouseY > 32) && (iMouseY < 736)) {

				// Get new objectgroup
				int iNewObjectGroup = (iMouseY - 32) / 32 + (iObjectGroupsPage * iEntriesPerPage);

				// Toggle hidden
				if (oObject[0].gpObjectGroups[iNewObjectGroup].bHide == false) {

					// Set hidden
					oObject[0].gpObjectGroups[iNewObjectGroup].bHide = true;
				} else {

					// Set visible
					oObject[0].gpObjectGroups[iNewObjectGroup].bHide = false;
				}
			}

			// Edit name
			if ((iMouseX > 960) && (iMouseX < 992) && (iMouseY > 32) && (iMouseY < 736)) {

				// Get new objectgroup
				int iNewObjectGroup = (iMouseY - 32) / 32 + (iObjectGroupsPage * iEntriesPerPage);

				// Show dialog
				bShowDialog = true;

				// Set dialog type
				iDialog = 0;

				// Set string
				strcpy (acDialogString, oObject[0].gpObjectGroups[iNewObjectGroup].acName);

				// Dialog item
				iDialogIndex = iNewObjectGroup;
			}

			// Edit time
			if ((iMouseX > 992) && (iMouseX < 1024) && (iMouseY > 32) && (iMouseY < 736)) {

				// Get new objectgroup
				int iNewObjectGroup = (iMouseY - 32) / 32 + (iObjectGroupsPage * iEntriesPerPage);

				// Show dialog
				bShowDialog = true;

				// Set dialog type
				iDialog = 1;

				// Set string
				sprintf (acDialogString, "%d", oObject[0].gpObjectGroups[iNewObjectGroup].iTime);

				// Dialog item
				iDialogIndex = iNewObjectGroup;
			}
		} else if (iSelectedTab == 1) {

			// Check if block types
			if ((iMouseX > 800) && (iMouseX < 928) && (iMouseY > 32) && (iMouseY < 736)) {

				// Get new block type
				int iNewBlockType = (iMouseY - 32) / 32 + (iBlockTypesPage * iEntriesPerPage);

				// Set new block type
				oObject[0].gpObjectGroups[aiSelected[0]].bpBricks[aiSelected[1]].iType = iNewBlockType;
				oObject[0].gpObjectGroups[aiSelected[0]].bpBricks[aiSelected[1]].iBlockNumber = bBrickLib.epBricks[oObject[0].gpObjectGroups[aiSelected[0]].bpBricks[aiSelected[1]].iType].iBlockNumber;
			}
		} else if (iSelectedTab == 2) {

			// Check if colors
			if ((iMouseX > 800) && (iMouseX < 928) && (iMouseY > 32) && (iMouseY < 736)) {

				// Get new color
				int iNewColor = (iMouseY - 32) / 32 + (iColorsPage * iEntriesPerPage);

				// Set new color
				oObject[0].gpObjectGroups[aiSelected[0]].bpBricks[aiSelected[1]].iColor = iNewColor;
			}
		}
*/
	}
}

/*******************************************************************************
* DrawButton
*******************************************************************************/
void DrawButton () {
	// Enable Pointers
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glVertexPointer (3, GL_FLOAT, 0, vpVerticesButton);
	glTexCoordPointer (2, GL_FLOAT, 0, tpTexturesButton);
	glDrawArrays (GL_QUADS, 0, 4);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );	
}

/*******************************************************************************
* DrawBrick
*******************************************************************************/
void DrawBrick () {
	// Enable Pointers
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glVertexPointer (3, GL_FLOAT, 0, vpVerticesBrick);
	glTexCoordPointer (2, GL_FLOAT, 0, tpTexturesBrick);
	glDrawArrays (GL_QUADS, 0, 4);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );	
}

/*******************************************************************************
* DrawLabel
*******************************************************************************/
void DrawLabel () {
	// Enable Pointers
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glVertexPointer (3, GL_FLOAT, 0, vpVerticesLabel);
	glTexCoordPointer (2, GL_FLOAT, 0, tpTexturesLabel);
	glDrawArrays (GL_QUADS, 0, 4);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );	
}

/*******************************************************************************
* DrawAnimPoint
*******************************************************************************/
void DrawAnimPoint () {

	// Bind texture
	glBindTexture(GL_TEXTURE_2D, atToolbar[17]);

	glBegin (GL_QUADS);
		// Front
		glVertex3f ( 0.5f,  0.5f, -0.5f);
		glVertex3f ( 0.5f, -0.5f, -0.5f);
		glVertex3f (-0.5f, -0.5f, -0.5f);
		glVertex3f (-0.5f,  0.5f, -0.5f);

		// Back
		glVertex3f (-0.5f,  0.5f, 0.5f);
		glVertex3f (-0.5f, -0.5f, 0.5f);
		glVertex3f ( 0.5f, -0.5f, 0.5f);
		glVertex3f ( 0.5f,  0.5f, 0.5f);

		// Left
		glVertex3f (-0.5f,  0.5f, -0.5f);
		glVertex3f (-0.5f, -0.5f, -0.5f);
		glVertex3f (-0.5f, -0.5f,  0.5f);
		glVertex3f (-0.5f,  0.5f,  0.5f);

		// Right
		glVertex3f ( 0.5f,  0.5f,  0.5f);
		glVertex3f ( 0.5f, -0.5f,  0.5f);
		glVertex3f ( 0.5f, -0.5f, -0.5f);
		glVertex3f ( 0.5f,  0.5f, -0.5f);

		// Top
		glVertex3f (-0.5f,  0.5f, -0.5f);
		glVertex3f (-0.5f,  0.5f,  0.5f);
		glVertex3f ( 0.5f,  0.5f,  0.5f);
		glVertex3f ( 0.5f,  0.5f, -0.5f);

		// Bottom
		glVertex3f ( 0.5f, -0.5f, -0.5f);
		glVertex3f ( 0.5f, -0.5f,  0.5f);
		glVertex3f (-0.5f, -0.5f,  0.5f);
		glVertex3f (-0.5f, -0.5f, -0.5f);
	glEnd ();
}

/*******************************************************************************
* DrawToolbar
*******************************************************************************/
void DrawToolbar () {

	// Reset The Modelview Matrix
	glLoadIdentity ();

	// Translate to new object start point
	glTranslatef (0.0f, 0.0f, -0.1f);

	// New
	glTranslatef (-0.05518f, 0.038f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atToolbar[0]);
	DrawButton ();

	// Open
	glTranslatef (0.00345f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atToolbar[1]);
	DrawButton ();

	// Save
	glTranslatef (0.00345f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atToolbar[2]);
	DrawButton ();

	// Verts
	glTranslatef (0.0069f, 0.0f, 0.0f);
	if (iSelectedTool == 0) {
		glBindTexture(GL_TEXTURE_2D, atToolbar[4]);
	} else {
		glBindTexture(GL_TEXTURE_2D, atToolbar[3]);
	}
	DrawButton ();

	// Objects
	glTranslatef (0.00345f, 0.0f, 0.0f);
	if (iSelectedTool == 1) {
		glBindTexture(GL_TEXTURE_2D, atToolbar[6]);
	} else {
		glBindTexture(GL_TEXTURE_2D, atToolbar[5]);
	}
	DrawButton ();

	// Cam
	glTranslatef (0.00345f, 0.0f, 0.0f);
	if (iSelectedTool == 2) {
		glBindTexture(GL_TEXTURE_2D, atToolbar[8]);
	} else {
		glBindTexture(GL_TEXTURE_2D, atToolbar[7]);
	}
	DrawButton ();

	// Points tune
	glTranslatef (0.00345f, 0.0f, 0.0f);
	if (iSelectedTool == 3) {
		glBindTexture(GL_TEXTURE_2D, atToolbar[10]);
	} else {
		glBindTexture(GL_TEXTURE_2D, atToolbar[9]);
	}
	DrawButton ();
}

/*******************************************************************************
* DrawObjectGroups
*******************************************************************************/
void DrawObjectGroups () {
/*
	// Reset The Modelview Matrix
	glLoadIdentity ();

	// Translate to new object start point
	glTranslatef (0.0f, 0.0f, -0.1f);

	// Objectgroups
	glTranslatef (0.031f, 0.038f, 0.0f);

	// Count
	for (int iCount = 0; ((iCount < iEntriesPerPage) && (iCount < oObject[0].iNrOfObjectGroups - (iObjectGroupsPage * iEntriesPerPage))); iCount++) {

		// Move to next
		glTranslatef (0.0f, -0.00345f, 0.0f);

		if (aiSelected[0] == iCount + (iObjectGroupsPage * iEntriesPerPage)) {
			glBindTexture(GL_TEXTURE_2D, atTabs[7]);
		} else {
			glBindTexture(GL_TEXTURE_2D, atTabs[6]);
		}
		DrawLabel ();

		glPushMatrix ();
			// Hide
			glTranslatef (0.0138f, 0.0f, 0.0f);
			if (oObject[0].gpObjectGroups[iCount + (iObjectGroupsPage * iEntriesPerPage)].bHide == true) {
				glBindTexture(GL_TEXTURE_2D, atTabs[11]);
			} else {
				glBindTexture(GL_TEXTURE_2D, atTabs[10]);
			}
			DrawButton ();
			
			// Edit name
			glTranslatef (0.00345f, 0.0f, 0.0f);
			glBindTexture(GL_TEXTURE_2D, atTabs[8]);
			DrawButton ();

			// Edit time
			glTranslatef (0.00345f, 0.0f, 0.0f);
			glBindTexture(GL_TEXTURE_2D, atTabs[9]);
			DrawButton ();
		glPopMatrix ();

		fFont2d.print (810, 714 - (iCount * 32), oObject[0].gpObjectGroups[iCount + (iObjectGroupsPage * iEntriesPerPage)].acName);
	}
*/
}

/*******************************************************************************
* DrawBlockTypes
*******************************************************************************/
void DrawBlockTypes () {
/*
	// Reset The Modelview Matrix
	glLoadIdentity ();

	// Translate to new object start point
	glTranslatef (0.0f, 0.0f, -0.1f);

	// Objectgroups
	glTranslatef (0.031f, 0.038f, 0.0f);

	// Count
	for (int iCount = 0; ((iCount < iEntriesPerPage) && (iCount < bBrickLib.iNrOfEntries - (iBlockTypesPage * iEntriesPerPage))); iCount++) {

		// Move to next
		glTranslatef (0.0f, -0.00345f, 0.0f);

		// Draw frame
		if (oObject[0].gpObjectGroups[aiSelected[0]].bpBricks[aiSelected[1]].iType == iCount + (iBlockTypesPage * iEntriesPerPage)) {
			glBindTexture(GL_TEXTURE_2D, atTabs[7]);
		} else {
			glBindTexture(GL_TEXTURE_2D, atTabs[6]);
		}
		DrawLabel ();

		// Push matrix
		glPushMatrix ();

		// Translate to new object start point
		glTranslatef (34.0f, 35.5f - (3.45f * iCount), -100.0f);

		// Rotate
		glRotatef (30, 1.0f, 0.0f, 0.0f);
		glRotatef (45, 0.0f, 1.0f, 0.0f);

		// Draw brick
		bBrickLib.epBricks[iCount + iBlockTypesPage * iEntriesPerPage].draw (oObject[0].gpObjectGroups[aiSelected[0]].bpBricks[aiSelected[1]].iColor);

		// Pop matrix
		glPopMatrix ();
	}
*/
}

/*******************************************************************************
* DrawColors
*******************************************************************************/
void DrawColors () {
/*
	// Reset The Modelview Matrix
	glLoadIdentity ();

	// Translate to new object start point
	glTranslatef (0.0f, 0.0f, -0.1f);

	// Objectgroups
	glTranslatef (0.031f, 0.038f, 0.0f);

	// Count
	for (int iCount = 0; ((iCount < iEntriesPerPage) && (iCount < NR_OF_COLORS - (iColorsPage * iEntriesPerPage))); iCount++) {

		// Move to next
		glTranslatef (0.0f, -0.00345f, 0.0f);

		// Draw frame
		if (oObject[0].gpObjectGroups[aiSelected[0]].bpBricks[aiSelected[1]].iColor == iCount + (iColorsPage * iEntriesPerPage)) {
			glBindTexture(GL_TEXTURE_2D, atTabs[7]);
		} else {
			glBindTexture(GL_TEXTURE_2D, atTabs[6]);
		}
		DrawLabel ();

		// Push matrix
		glPushMatrix ();

		// Translate to new object start point
		glTranslatef (34.0f, 35.5f - (3.45f * iCount), -100.0f);

		// Rotate
		glRotatef (30, 1.0f, 0.0f, 0.0f);
		glRotatef (45, 0.0f, 1.0f, 0.0f);

		// Draw brick
		bBrickLib.epBricks[oObject[0].gpObjectGroups[aiSelected[0]].bpBricks[aiSelected[1]].iType].draw (iCount + (iColorsPage * iEntriesPerPage));

		// Pop matrix
		glPopMatrix ();
	}
*/
}

/*******************************************************************************
* DrawTabs
*******************************************************************************/
void DrawTabs () {

	// Reset The Modelview Matrix
	glLoadIdentity ();

	// Translate to new object start point
	glTranslatef (0.0f, 0.0f, -0.1f);

	// Objectgroups
	glTranslatef (0.031f, 0.038f, 0.0f);
	if (iSelectedTab == 0) {
		glBindTexture(GL_TEXTURE_2D, atTabs[1]);
	} else {
		glBindTexture(GL_TEXTURE_2D, atTabs[0]);
	}
	DrawButton ();

	// Blocktypes
	glTranslatef (0.00345f, 0.0f, 0.0f);
	if (iSelectedTab == 1) {
		glBindTexture(GL_TEXTURE_2D, atTabs[3]);
	} else {
		glBindTexture(GL_TEXTURE_2D, atTabs[2]);
	}
	DrawButton ();

	// Colors
	glTranslatef (0.00345f, 0.0f, 0.0f);
	if (iSelectedTab == 2) {
		glBindTexture(GL_TEXTURE_2D, atTabs[5]);
	} else {
		glBindTexture(GL_TEXTURE_2D, atTabs[4]);
	}
	DrawButton ();

	// Prev page
	glTranslatef (0.01035f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atTabs[12]);
	DrawButton ();

	// Next page
	glTranslatef (0.00345f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atTabs[13]);
	DrawButton ();

	// String
	char acString[256];

	// Draw tab content
	switch (iSelectedTab) {
		case 0:
			DrawObjectGroups ();
//			sprintf (acString, "%i/%i", iObjectGroupsPage + 1, (oObject[0].iNrOfObjectGroups / iEntriesPerPage) + 1);
			break;
		case 1:
			DrawBlockTypes ();
//			sprintf (acString, "%i/%i", iBlockTypesPage + 1, (bBrickLib.iNrOfEntries / iEntriesPerPage) + 1);
			break;
		case 2:
			DrawColors ();
//			sprintf (acString, "%i/%i", iColorsPage + 1, (NR_OF_COLORS / iEntriesPerPage) + 1);
			break;
	}

	// Print page
	fFont2d.print (906, 746, acString);
}

/*******************************************************************************
* DrawBrickList
*******************************************************************************/
void DrawBrickList () {
/*
	int iCount;		// Counter

	// Reset The Modelview Matrix
	glLoadIdentity ();

	// Translate to new object start point
	glTranslatef (0.0f, 0.0f, -0.1f);

	// Prev objectgroup
	glTranslatef (-0.055251f, -0.0302f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atTabs[12]);
	DrawButton ();

	// Save coords
	glPushMatrix ();

	// Object label
	glTranslatef (0.00345f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atTabs[6]);
	DrawLabel ();

	// Print page
	fFont2d.print (42, 114, oObject[0].gpObjectGroups[iCurrentObjectGroup].acName);

	// Next objectgroup
	glTranslatef (0.0138f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atTabs[13]);
	DrawButton ();

	// New group
	glTranslatef (0.00345f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atTabs[14]);
	DrawButton ();

	// Delete group
	glTranslatef (0.00345f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atTabs[15]);
	DrawButton ();

	// Edit frames per brick
	glTranslatef (0.0069f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atToolbar[19]);
	DrawButton ();

	// Edit frames between brick
	glTranslatef (0.00345f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atToolbar[20]);
	DrawButton ();

	// Sort bricks
	glTranslatef (0.00345f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atToolbar[27]);
	DrawButton ();

	// Clone groups
	glTranslatef (0.00345f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atToolbar[30]);
	DrawButton ();

	// Replace color
	glTranslatef (0.00345f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atToolbar[31]);
	DrawButton ();

	// Prev page
	glTranslatef (0.03105f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atTabs[12]);
	DrawButton ();

	// Next page
	glTranslatef (0.00345f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atTabs[13]);
	DrawButton ();

	// Reload coords
	glPopMatrix ();

	// Go down
	glTranslatef (0.0f, -0.0069f, 0.0f);

	// String
	char acString[256];
	sprintf (acString, "%i/%i", iBrickListPage + 1, (oObject[0].gpObjectGroups[aiSelected[0]].iNrOfBricks / 12) + 1);

	// Print page
	fFont2d.print (650, 114, acString);

	// Count
	for (iCount = 0; ((iCount < 12) && (iCount < oObject[0].gpObjectGroups[iCurrentObjectGroup].iNrOfBricks - (iBrickListPage * 12))); iCount++) {

		// Push matrix
		glPushMatrix ();

		// Translate to new object start point
		glTranslatef (-54.0f + (6.9f * iCount), -35.5f, -100.0f);

		// Rotate
		glRotatef (30, 1.0f, 0.0f, 0.0f);
		glRotatef (45, 0.0f, 1.0f, 0.0f);

		// Draw brick
		bBrickLib.epBricks[oObject[0].gpObjectGroups[iCurrentObjectGroup].bpBricks[iCount + (iBrickListPage * 12)].iType].draw (oObject[0].gpObjectGroups[iCurrentObjectGroup].bpBricks[iCount + (iBrickListPage * 12)].iColor);

		// Pop matrix
		glPopMatrix ();
	}

	// Push matrix
	glPushMatrix ();

	// Count
	for (iCount = 0; ((iCount < 12) && (iCount < oObject[0].gpObjectGroups[iCurrentObjectGroup].iNrOfBricks - (iBrickListPage * 12))); iCount++) {

		// Draw frame
		if ((aiSelected[0] == iCurrentObjectGroup) && (aiSelected[1] == iCount + (iBrickListPage * 12))) {
			glBindTexture(GL_TEXTURE_2D, atTabs[7]);
		} else {
			glBindTexture(GL_TEXTURE_2D, atTabs[6]);
		}
		DrawBrick ();

		// Move to next
		glTranslatef (0.0069f, 0.0f, 0.0f);
	}

	// Pop matrix
	glPopMatrix ();
*/
}

/*******************************************************************************
* DrawDialog
*******************************************************************************/
void DrawDialog () {

	// Reset The Modelview Matrix
	glLoadIdentity ();

	// Translate to new object start point
	glTranslatef (0.0f, 0.0f, -0.1f);

	// Objectgroups
	glTranslatef (-0.0138f, -0.008f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, atTabs[6]);

	// Enable Pointers
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glVertexPointer (3, GL_FLOAT, 0, vpVerticesDialog);
	glTexCoordPointer (2, GL_FLOAT, 0, tpTexturesDialog);
	glDrawArrays (GL_QUADS, 0, 4);
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );	

	// Enable blend
	glEnable(GL_BLEND);

	// Title
	char acTitle[256];

	// Print title
	switch (iDialog) {
		case 0:
		case 2:
			strcpy (acTitle, "Objectgroupname:");
			break;
		case 1:
			strcpy (acTitle, "Time offset:");
			break;
		case 3:
			strcpy (acTitle, "Frames per brick:");
			break;
		case 4:
			strcpy (acTitle, "Frames between bricks:");
			break;
		case 5:
			strcpy (acTitle, "Enter file to open:");
			break;
		case 6:
			strcpy (acTitle, "Enter file to save:");
			break;
		case 7:
			strcpy (acTitle, "Enter new color (0 - 27):");
			break;
	}
	fFont2d.print (394, 426, acTitle);

	fFont2d.print (394, 362, acDialogString);

	// Disable blend
	glDisable(GL_BLEND);
}

/*******************************************************************************
* Draw
*******************************************************************************/
void Draw (LGWindow* wWindow) {
	RECT	rRect;				// Holds Coordinates Of A Rectangle

	// Get window dimensions
	GetClientRect(wWindow->hWnd, &rRect);
	int iWindowWidth = rRect.right-rRect.left;
	int iWindowHeight = rRect.bottom-rRect.top;

	// Check if fsaa supported
	if (bFSAA) {

		// Enable multisample
		glEnable(GL_MULTISAMPLE_ARB);
	}

	// Clear screen and depth buffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// If second has passed
	if (GetTickCount() - g_dwLastFPS >= 1000) {

		// Update our time variable
		g_dwLastFPS = GetTickCount();

		// Save the FPS
		g_nFPS = g_nFrames;

		// Reset the FPS
		g_nFrames = 0;
	}

	// Loop 4 times
	for (int iLoop = 0; iLoop < 4; iLoop++) {

		if (iLoop==0) {
			// Set The Viewport To The Top Left.
			glViewport (0, 436, 400, 300);
			glMatrixMode (GL_PROJECTION);								// Select The Projection Matrix
			glLoadIdentity ();											// Reset The Projection Matrix
			// Set Up Ortho Mode To Fit 1/4 The Screen (Size Of A Viewport)
			gluPerspective( 45.0, (GLfloat)(iWindowWidth*0.390625)/(GLfloat)(iWindowHeight*0.390625), 0.1f, 500.0 ); 
		}

		if (iLoop==1) {
			// Set The Viewport To The Top Right.
			glViewport (400, 436, 400, 300);
			glMatrixMode (GL_PROJECTION);								// Select The Projection Matrix
			glLoadIdentity ();											// Reset The Projection Matrix
			// Set Up Perspective Mode To Fit 1/4 The Screen (Size Of A Viewport)
			gluPerspective( 45.0, (GLfloat)(iWindowWidth*0.390625)/(GLfloat)(iWindowHeight*0.390625), 0.1f, 500.0 ); 
		}

		if (iLoop==2) {
			// Set The Viewport To The Bottom Right.
			glViewport (400, 136, 400, 300);
			glMatrixMode (GL_PROJECTION);								// Select The Projection Matrix
			glLoadIdentity ();											// Reset The Projection Matrix
			// Set Up Perspective Mode To Fit 1/4 The Screen (Size Of A Viewport)
			gluPerspective( 45.0, (GLfloat)(iWindowWidth*0.390625)/(GLfloat)(iWindowHeight*0.390625), 0.1f, 500.0 ); 
		}

		if (iLoop==3) {
			// Set The Viewport To The Bottom Left.
			glViewport (0, 136, 400, 300);
			glMatrixMode (GL_PROJECTION);								// Select The Projection Matrix
			glLoadIdentity ();											// Reset The Projection Matrix
			// Set Up Perspective Mode To Fit 1/4 The Screen (Size Of A Viewport)
			gluPerspective( 45.0, (GLfloat)(iWindowWidth*0.390625)/(GLfloat)(iWindowHeight*0.390625), 0.1f, 500.0 ); 
		}

		glMatrixMode (GL_MODELVIEW);									// Select The Modelview Matrix
		glLoadIdentity ();												// Reset The Modelview Matrix

		// Translate screen
		glTranslatef (-1 * avTranslation[iLoop].fX, -1 * avTranslation[iLoop].fY, -1 * avTranslation[iLoop].fZ);

		// Translate to new object start point
		glTranslatef (-16.0f, 0.0f, -40.0f);

		if (iLoop==1) {
			glRotatef (90, 0.0f, 1.0f, 0.0f);
		}
		if (iLoop==3) {
			glRotatef (90, 1.0f, 0.0f, 0.0f);
		}
		if (iLoop==2) {
			glRotatef (45, 1.0f, 0.0f, 0.0f);
			glRotatef (45, 0.0f, 1.0f, 0.0f);
		}

		if (bLighting) {
			glEnable(GL_LIGHTING);
		}

		// Draw level
		lLevel[0].draw ();

		if (bLighting) {
			glDisable(GL_LIGHTING);
		}

		glLoadIdentity ();												// Reset The Modelview Matrix

		// Translate to new object start point
		glTranslatef (0.0f, 0.0f, -0.1f);

		// Enabable blending
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);

		// Check if selected
		if (iLoop == iSelectedView) {

			// Bind texture
			glBindTexture(GL_TEXTURE_2D, atSelect[0]);
		} else {

			// Bind texture
			glBindTexture(GL_TEXTURE_2D, atSelect[1]);
		}

		// Enable Pointers
		glEnableClientState( GL_VERTEX_ARRAY );						// Enable Vertex Arrays
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );				// Enable Texture Coord Arrays
		glVertexPointer (3, GL_FLOAT, 0, vpVerticesSelect);			// Set The Vertex Pointer To Our Vertex Data
		glTexCoordPointer (2, GL_FLOAT, 0, tpTexturesSelect);
		glDrawArrays (GL_QUADS, 0, 4);
		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );	

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}

	// Set The Viewport To The Bottom Left.
	glViewport (0, 0, 1024, 768);
	glMatrixMode (GL_PROJECTION);								// Select The Projection Matrix
	glLoadIdentity ();											// Reset The Projection Matrix
	gluPerspective( 45.0, (GLfloat)(iWindowWidth*0.390625)/(GLfloat)(iWindowHeight*0.390625), 0.1f, 500.0 ); 
//	gluPerspective( 45.0, 1024/768, 0.1f, 500.0 ); 

	glMatrixMode (GL_MODELVIEW);									// Select The Modelview Matrix

	// Enabable blending
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	DrawToolbar ();
	DrawTabs ();
	DrawBrickList ();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	if (bShowDialog == true) {
		DrawDialog ();
	}

	// Inc fps counter
	g_nFrames++;

		// Check if fsaa supported
	if (bFSAA) {

		// Disable multisample
		glDisable(GL_MULTISAMPLE_ARB);
	}
}

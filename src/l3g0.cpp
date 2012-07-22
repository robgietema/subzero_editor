/*******************************************************************************
* File:		l3g0.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		27 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <math.h>
#include <gl/gl.h>									// Header File For The OpenGL32 Library
#include <gl/glu.h>									// Header File For The GLu32 Library
#include <stdio.h>									// Header File For Standard Input/Output
#include <conio.h>
#include "../include/lg_opengl.h"					// Header File For NeHeGL
#include "../include/lg_engine.h"					// Header File For NeHeGL
#include "../include/lg_font2d.h"					// Header File For font 2d
#include "../include/lg_color.h"					// Header file for color
#include "../include/glext.h"						// Header file for opengl extensions
#include "../include/scene/lg_scene.h"				// Header file for scene
#include "../include/bricklib/lg_bricklib.h"		// Header file for bricklib
#include "../include/objectlib/lg_objectlib.h"		// Header file for objectlib
#include "../include/3ds/file_3ds.h"				// Header file for 3ds file
#include "../include/fmod/fmod.h"					// Header file for audio library
#include "../include/fmod/fmod_errors.h"			// Header file for audio library errors

float			g_flYRot = 0.0f;						// Rotation
int				g_nFPS = 0, g_nFrames = 0;				// FPS and FPS Counter
DWORD			g_dwLastFPS = 0;						// Last FPS Check Time	
extern DWORD	dTicks;									// Milliseconds count
extern DWORD	dGlobalTicks;							// Global ticks
LGScene			sScene;									// Scene
LGObject		oObject1;								// Object
LGObject		oObject2;								// Object
LGObject		oObject3;								// Object
LGObject		oObject4;								// Object
LGObject		oObject5;								// Object
LGObject		oObject6;								// Object
LGObject		oObject7;								// Object
LGBrickLib		bBrickLib;								// Bricklib
LGObjectLib		oObjectLib;								// Objectlib
LGFont2d		fFont2d;								// Font 2d
LGVertex3f		vOffset;								// Offset
LGVertex3f		vRotate;								// Rotation
LGColor3b		acColors[NR_OF_COLORS];					// Colors
extern bool		bVBOSupported;							// VBO supported
bool			bFSAA=true;								// Anti aliasing
bool			bLighting=true;
bool			bAnim=false;
bool			bRotate=false;
bool			bDrawLine=false;
FILE_3DS		fFile3DS;
int iGlobalTexture=1;

int				iChannel;								// Audio channel
FSOUND_STREAM	*sStream;								// Stream pointer
FSOUND_SAMPLE	*sSample;								// Sample pointer

// Lights bay
GLfloat Shine = 10.0;
GLfloat LightAmbient[]= { 0.1f, 0.1f, 0.1f, 1.0f};
GLfloat LightDiffuse[]= { 1.5f, 1.5f, 1.5f, 1.0f};
GLfloat LightPosition[]= { 0.0f, 1.0f, 1.0f, 0.0f };
GLfloat SpecularColor[] = {1.0, 1.0, 1.0};
GLfloat SpotDirection[]= { 1.0f, -1.0f, -1.0f };
GLfloat SpotExponent[] = { 128.0 };
GLfloat SpotCutoff[] = { 50.0 };

// VBO Extension Function Pointers
extern PFNGLGENBUFFERSARBPROC glGenBuffersARB;				// VBO Name Generation Procedure
extern PFNGLBINDBUFFERARBPROC glBindBufferARB;				// VBO Bind Procedure
extern PFNGLBUFFERDATAARBPROC glBufferDataARB;				// VBO Data Loading Procedure
extern PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;		// VBO Deletion Procedure
extern PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElementsEXT;	// VBO Deletion Procedure
extern PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
extern PFNGLCLIENTACTIVETEXTUREARBPROC glActiveTextureARB;
extern PFNGLACTIVETEXTUREARBPROC glClientActiveTextureARB;

/*******************************************************************************
* Initialize
*******************************************************************************/
BOOL Initialize (LGWindow* wWindow, LGKeys* kKeys) {

	// Init print
	InitPrint ();

/*
	// Init audio
	VerbosePrintf ("Init Audio");
	if (FSOUND_GetVersion () < FMOD_VERSION) {
		VerbosePrintf ("You are using the wrong DLL version!  You should be using FMOD %.02f\n", FMOD_VERSION);
	}
	FSOUND_SetOutput (FSOUND_OUTPUT_WINMM);
	FSOUND_SetDriver (0);
	if (!FSOUND_Init (44100, 32, 0)) {
		VerbosePrintf ("Error initing audio");
	}
	FSOUND_Stream_SetBufferSize(1000);
	sStream = FSOUND_Stream_Open ("data/audio/background.mp3", FSOUND_NORMAL | FSOUND_MPEGACCURATE, 0, 0);
	if (!sStream) {
        VerbosePrintf ("Error %s\n", FMOD_ErrorString (FSOUND_GetError ()));
	}
	sSample = FSOUND_Stream_GetSample (sStream);
	if (sSample) {
        int iFreq;
        FSOUND_Sample_GetDefaults (sSample, &iFreq, NULL, NULL, NULL);
        VerbosePrintf ("Name      : %s", FSOUND_Sample_GetName(sSample));
        VerbosePrintf ("Frequency : %d", iFreq);
    }
	iChannel = FSOUND_Stream_PlayEx(FSOUND_FREE, sStream, NULL, TRUE);
	FSOUND_SetPaused (iChannel, FALSE);
*/

	// Check for vbo support
//	bVBOSupported = IsExtensionSupported ("GL_ARB_vertex_buffer_object");
	bVBOSupported = false;
	if (bVBOSupported) {

		// Get Pointers To The GL Functions
		glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
		glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
		glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) wglGetProcAddress("glDeleteBuffersARB");
	}
    glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC) wglGetProcAddress("glMultiTexCoord2f");
	glActiveTextureARB = (PFNGLCLIENTACTIVETEXTUREARBPROC) wglGetProcAddress("glActiveTexture");
    glClientActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC) wglGetProcAddress("glClientActiveTexture");
	glDrawRangeElementsEXT = (PFNGLDRAWRANGEELEMENTSPROC) wglGetProcAddress("glDrawRangeElementsEXT");

	// Reset offset
	vOffset.fX = 0.0f;
	vOffset.fY = 0.0f;
	vOffset.fZ = 0.0f;

	// Reset rotate
	vRotate.fX = 0.0f;
	vRotate.fY = 0.0f;
	vRotate.fZ = 0.0f;

	InitColor ();
	fFont2d.init ();

	bBrickLib.initDefaultValues ();
//	bBrickLib.readFromFile ("data/bricks/bricks.blb");
//	bBrickLib.writeToFile ("data/bricks/bricks.blb");

	oObjectLib.initDefaultValues ();
//	oObjectLib.readFromFile ("data/objects/default.obl");
//	oObjectLib.writeToFile ("data/objects/default.obl");

//	sScene.initDefaultValues ();
//	sScene.readFromFile ("data/scenes/scene1.scn");
//	sScene.writeToFile ("data/scenes/scene1.scn");

	oObject1.readFromFile ("data/objects/building1.obj");
	oObject2.readFromFile ("data/objects/building2.obj");
	oObject3.readFromFile ("data/objects/building3.obj");
	oObject4.readFromFile ("data/objects/blocks.obj");
	oObject5.readFromFile ("data/objects/parking.obj");
	oObject6.readFromFile ("data/objects/hq.obj");
	oObject7.readFromFile ("data/objects/f17.obj");

	fFile3DS.read3DS ("data/models/legoman.3ds");

	// Setup GL States
	glClearColor (1.0f, 1.0f, 1.0f, 0.0f);					// Black Background
	glClearDepth (1.0f);									// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);								// The Type Of Depth Testing (Less Or Equal)
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);		// Select The Type Of Blending
	glEnable (GL_DEPTH_TEST);								// Enable Depth Testing
	glShadeModel (GL_SMOOTH);								// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		// Set Perspective Calculations To Most Accurate
	glEnable( GL_TEXTURE_2D );								// Enable Textures
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );					// Set The Color To White
	glEnable(GL_CULL_FACE);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
//	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,SpotDirection);
//	glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT,SpotExponent);
//	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF,SpotCutoff);
	glEnable(GL_LIGHT1);
//	glDisable(GL_LIGHT1);

	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecularColor);
	glMaterialfv(GL_FRONT, GL_SHININESS, &Shine);

//FSOUND_Stream_SetTime (sStream, 122000);

	// Return no error
	return TRUE;											// Return TRUE (Initialization Successful)
}

/*******************************************************************************
* Deinitialize
*******************************************************************************/
void Deinitialize () {

	// De init print
	DeInitPrint ();

	// De init audio
//    FSOUND_Stream_Close (sStream);
//    FSOUND_Close ();
}

/*******************************************************************************
* Update
*******************************************************************************/
void Update (DWORD dMilliseconds, LGWindow* wWindow, LGKeys* kKeys) {

	// Update ticks
	dGlobalTicks += dMilliseconds;
	dTicks += dMilliseconds;

	// If escape pressed
	if (kKeys->abKeyDown [VK_ESCAPE] == TRUE) {

		// Terminate the program
		TerminateApplication (wWindow);
	}

	// If f1 pressed
	if (kKeys->abKeyDown [VK_F1] == TRUE) {

		// Toggle Fullscreen Mode
		ToggleFullscreen (wWindow);
	}

	// If f3 pressed
	if (kKeys->abKeyDown [VK_F3] == TRUE) {

		// Toggle Anim
		if (bAnim == true) {
			bAnim = false;
		} else {
			bAnim = true;
		}
	}

	// If f4 pressed
	if (kKeys->abKeyDown [VK_F4] == TRUE) {

		// Toggle Anim
		if (bRotate == true) {
			bRotate = false;
		} else {
			bRotate = true;
		}
	}

	// If f5 pressed
	if (kKeys->abKeyDown [VK_F5] == TRUE) {

		// Toggle Anim
		if (bDrawLine == true) {
			bDrawLine = false;
		} else {
			bDrawLine = true;
		}
	}

	if (kKeys->abKeyDown [VK_UP] == TRUE) {

		// Move forward
		vOffset.fZ += 5.0f;
	}

	if (kKeys->abKeyDown [VK_DOWN] == TRUE) {

		// Move backward
		vOffset.fZ -= 5.0f;
	}

	if (kKeys->abKeyDown [VK_LEFT] == TRUE) {

		// Move left
		vOffset.fX += 5.0f;
	}

	if (kKeys->abKeyDown [VK_RIGHT] == TRUE) {

		// Move left
		vOffset.fX -= 5.0f;
	}

	if (kKeys->abKeyDown [VK_NEXT] == TRUE) {

		// Move up
		vOffset.fY += 5.0f;
	}

	if (kKeys->abKeyDown [VK_PRIOR] == TRUE) {

		// Move down
		vOffset.fY -= 5.0f;
	}

	if (kKeys->abKeyDown ['L'] == TRUE) {

		if (bLighting == true) {
			bLighting = false;
		} else {
			bLighting = true;
		}
	}

	if (kKeys->abKeyDown [VK_F2] == TRUE) {

		if (bFSAA) {
			bFSAA = false;
		} else {
			bFSAA = true;
		}
	}

}

/*******************************************************************************
* Draw
*******************************************************************************/
void Draw (LGWindow* wWindow) {
	int iAnimFrame = 0;
	float fRotate = 0;
	if (bRotate == true) {
		fRotate = (float)(dTicks % 36000 / 100);
	}
	if (bAnim == true) {
		iAnimFrame = (dTicks%12800)/128;
	}

	// Check if fsaa supported
	if (bFSAA) {

		// Enable multisample
		glEnable(GL_MULTISAMPLE_ARB);
	}

	// Clear screen and depth buffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset the modelview matrix
	glLoadIdentity ();

	// If second has passed
	if (GetTickCount() - g_dwLastFPS >= 1000) {

		// Update our time variable
		g_dwLastFPS = GetTickCount();

		// Save the FPS
		g_nFPS = g_nFrames;

		// Reset the FPS
		g_nFrames = 0;
	}

	// Inc fps counter
	g_nFrames++;

	// Translate
	glTranslatef (vOffset.fX, vOffset.fY, vOffset.fZ);

	glTranslatef (0.0f, -0.0f, -250.0f);

	if (bLighting) {
		glEnable(GL_LIGHTING);
	}

	iGlobalTexture = 0;
	glTranslatef (100.0f, 0.0f, 0.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	glTranslatef (0.0f, 0.0f, 50.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	glTranslatef (0.0f, 0.0f, 50.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	glTranslatef (0.0f, 0.0f, 50.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	iGlobalTexture = 1;
	glTranslatef (-70.0f, 0.0f, -150.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	glTranslatef (0.0f, 0.0f, 50.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	glTranslatef (0.0f, 0.0f, 50.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	glTranslatef (0.0f, 0.0f, 50.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	iGlobalTexture = 2;
	glTranslatef (-70.0f, 0.0f, -150.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	glTranslatef (0.0f, 0.0f, 50.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	glTranslatef (0.0f, 0.0f, 50.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	glTranslatef (0.0f, 0.0f, 50.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	iGlobalTexture = 3;
	glTranslatef (-70.0f, 0.0f, -150.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	glTranslatef (0.0f, 0.0f, 50.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	glTranslatef (0.0f, 0.0f, 50.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

	glTranslatef (0.0f, 0.0f, 50.0f);
	glPushMatrix ();glRotatef ((float)(fRotate), 0.0f, 0.1f, 0.0f);
	oObject4.draw (iAnimFrame);
	glPopMatrix ();

/*
	// Translate
	glTranslatef (vOffset.fX, vOffset.fY, vOffset.fZ);

	// Translate
	glTranslatef (-16.0f, 0.0f, -256.0f);

	glTranslatef (0.0f, -30.0f, -150.0f);

//	glRotatef ((float)(dTicks % 3600 / 10), 0.0f, 0.1f, 0.0f);
	
	if (bLighting) {
		glEnable(GL_LIGHTING);
	}

	glTranslatef (140.0f, 0.0f, 0.0f);

	// Draw scene
	oObject1.draw (dTicks/64);

	glTranslatef (-20.0f, 0.0f, 0.0f);
	oObject2.draw (0);

	glTranslatef (-20.0f, 0.0f, 0.0f);
	oObject3.draw (0);

	glTranslatef (-25.0f, 0.0f, 0.0f);
	oObject1.draw (2000);

	glTranslatef (-20.0f, 0.0f, 0.0f);
	oObject2.draw (0);

	glTranslatef (-20.0f, 0.0f, 0.0f);
	oObject3.draw (0);

	glTranslatef (-25.0f, 0.0f, 0.0f);
	oObject1.draw (dTicks/64);

	glTranslatef (-20.0f, 0.0f, 0.0f);
	oObject2.draw (dTicks/64 % 100);

	glTranslatef (-20.0f, 0.0f, 0.0f);
//	oObject3.draw (0);

	glTranslatef (-25.0f, 0.0f, 0.0f);
//	oObject1.draw (2000);

	glTranslatef (-20.0f, 0.0f, 0.0f);
//	oObject5.draw (0);

	glTranslatef (-20.0f, 0.0f, 0.0f);
	oObject6.draw (10000);

	glTranslatef (-25.0f, 0.0f, 0.0f);
	oObject1.draw (2000);

	glTranslatef (-20.0f, 0.0f, 0.0f);
	oObject2.draw (0);

	glTranslatef (-20.0f, 0.0f, 0.0f);
	oObject3.draw (0);

	glTranslatef (140.0f, 60.0f, 0.0f);
	glRotatef (20.0f, 1.0f, 0.0f, 0.0f);
	glRotatef (25.0f, 0.0f, 1.0f, 0.0f);
	oObject4.draw (0);

	glTranslatef (0.0f, 30.0f, 0.0f);
	oObject7.draw (0);

	// Draw 3ds file
	glRotatef (270.0f, 1.0f, 0.0f, 0.0f);
	glRotatef (180.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef (0.0f, 30.0f, 0.0f);
	fFile3DS.draw (0);
*/
	if (bLighting) {
		glDisable(GL_LIGHTING);
	}

	char szTitle[256] = {0};
	sprintf( szTitle, "%d FPS", g_nFPS);

	char szBricks[256] = {0};
	sprintf( szBricks, "%d bricks", oObject6.getNrOfBricks ());

	glEnable(GL_BLEND);
	glColor3f (1.0f,1.0f,1.0f);							// Set Color To White
	fFont2d.print (2, 750, szTitle);
	fFont2d.print (2, 720, szBricks);

	// Check if fsaa supported
	if (bFSAA) {

		// Disable multisample
		glDisable(GL_MULTISAMPLE_ARB);
	}
}

/*******************************************************************************
* OnMouseDown
*******************************************************************************/
void OnMouseDown (int iButton, int iMouseX, int iMouseY) {
}

/*******************************************************************************
* OnKeyDown
*******************************************************************************/
void OnKeyDown (WPARAM wParam, LGWindow* wWindow) {
}
/*******************************************************************************
* File:		lg_engine.h
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		5 January 2004
* Note:		This code is based on the NeHe OpenGL framework
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef LG_ENGINE_H
#define LG_ENGINE_H
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../include/lg_print.h"
#include "../include/lg_opengl.h"
#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/ARB_MULTISAMPLE.h"

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////
#define WM_TOGGLEFULLSCREEN (WM_USER+1)			// Application Define Message For Toggling

////////////////////////////////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////////////////////////////////
typedef struct {							// Structure For Keyboard Stuff
	BOOL abKeyDown[256];					// Holds TRUE / FALSE For Each Key
} LGKeys;	

typedef struct {							// Contains Information Vital To Applications
	HINSTANCE		hInstance;				// Application Instance
	const char*		csClassName;			// Application ClassName
} LGApplication;

typedef struct {							// Window Creation Info
	LGApplication*	aApplication;			// Application Structure
	char*			cpTitle;				// Window Title
	int				iWidth;					// Width
	int				iHeight;				// Height
	int				iBitsPerPixel;			// Bits Per Pixel
	BOOL			bIsFullScreen;			// FullScreen?
} LGWindowInit;

typedef struct {							// Contains Information Vital To A Window
	LGKeys*			kpKeys;					// Key Structure
	HWND			hWnd;					// Window Handle
	HDC				hDC;					// Device Context
	HGLRC			hRC;					// Rendering Context
	LGWindowInit	wInit;					// Window Init
	BOOL			bIsVisible;				// Window Visible?
	DWORD			dLastTickCount;			// Tick Counter
} LGWindow;

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			TerminateApplication (LGWindow* wWindow)
* Function:		Terminate the Application.
* Pre:			-
* Post:			Application is terminated.
*******************************************************************************/
void TerminateApplication (LGWindow* window);

/*******************************************************************************
* Name:			ToggleFullscreen (LGWindow* wWindow)
* Function:		Toggle fullscreen/window mode.
* Pre:			-
* Post:			Fullscreen is toggled.
*******************************************************************************/
void ToggleFullscreen (LGWindow* window);

/*******************************************************************************
* Name:			Initialize (LGWindow* wWindow, LGKeys* kKeys)
* Function:		Performs initialization.
* Pre:			-
* Post:			Init is performed
*******************************************************************************/
BOOL Initialize (LGWindow* wWindow, LGKeys* kKeys);

/*******************************************************************************
* Name:			DeInitialize ()
* Function:		Performs deinitialization.
* Pre:			-
* Post:			Deinit is performed.
*******************************************************************************/
void Deinitialize ();

/*******************************************************************************
* Name:			Update (DWORD dMilliseconds)
* Function:		Performs motion updates.
* Pre:			-
* Post:			Scene is updated.
*******************************************************************************/
void Update (DWORD dMilliseconds, LGWindow* wWindow, LGKeys* kKeys);

/*******************************************************************************
* Name:			Draw ()
* Function:		Performs all your scene drawing.
* Pre:			-
* Post:			Scene is drawn.
*******************************************************************************/
void Draw (LGWindow* wWindow);

/*******************************************************************************
* Name:			OnKeyDown (WPARAM wParam, LGWindow* wWindow)
* Function:		Key down handler.
* Pre:			-
* Post:			Key down event is handled.
*******************************************************************************/
void OnKeyDown (WPARAM wParam, LGWindow* wWindow);

/*******************************************************************************
* Name:			OnMouseDown (int iButton, int iMouseX, int iMouseY)
* Function:		Mouse down handler.
* Pre:			-
* Post:			Mouse down event is handled.
*******************************************************************************/
void OnMouseDown (int iButton, int iMouseX, int iMouseY);

/*******************************************************************************
* Name:			DestroyWindowGL (LGWindow* wWindow)
* Function:		Destroy window.
* Pre:			-
* Post:			Window is destroyed.
*******************************************************************************/
BOOL DestroyWindowGL (LGWindow* wWindow);

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////

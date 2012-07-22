/*******************************************************************************
* File:		lg_engine.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		27 November 2003
* Note:		This code is based on the NeHe OpenGL framework
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../include/lg_engine.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
static BOOL	bIsProgramLooping;					// Window Creation Loop
static BOOL	bCreateFullScreen;					// If TRUE, Then Create Fullscreen
int			iMouseX;							// Mouse x position
int			iMouseY;							// Mouse y position
int			iMouseButtonRight = 0;				// Right button pressed
int			iMouseButtonLeft = 0;				// Left button pressed
int			iMouseButtonMiddle = 0;				// Middle button pressed
int			iMouseDownX;						// X of mouse down
int			iMouseDownY;						// Y of mouse down

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* TerminateApplication
*******************************************************************************/
void TerminateApplication (LGWindow* wWindow) {

	// Send a WM_QUIT message
	PostMessage (wWindow->hWnd, WM_QUIT, 0, 0);

	// Stop looping of the program
	bIsProgramLooping = FALSE;
}

/*******************************************************************************
* ToggleFullscreen
*******************************************************************************/
void ToggleFullscreen (LGWindow* wWindow) {

	// Send A WM_TOGGLEFULLSCREEN Message
	PostMessage (wWindow->hWnd, WM_TOGGLEFULLSCREEN, 0, 0);
}

/*******************************************************************************
* ReshapeGL
*******************************************************************************/
void ReshapeGL (int iWidth, int iHeight) {

	// Reset the current viewport
	glViewport (0, 0, (GLsizei)(iWidth), (GLsizei)(iHeight));

	// Select the projection matrix
	glMatrixMode (GL_PROJECTION);

	// Reset the projection matrix
	glLoadIdentity ();

	// Calculate the aspect ratio of the window
	gluPerspective (45.0f, (GLfloat)(iWidth)/(GLfloat)(iHeight), 1.0f, 1000.0f);

	// Select the modelview matrix
	glMatrixMode (GL_MODELVIEW);

	// Reset the modelview matrix
	glLoadIdentity ();
}

/*******************************************************************************
* ChangeScreenResolution
*******************************************************************************/
BOOL ChangeScreenResolution (int iWidth, int iHeight, int iBitsPerPixel) {

	// Device mode
	DEVMODE dmScreenSettings;

	// Make sure memory is cleared
	ZeroMemory (&dmScreenSettings, sizeof (DEVMODE));

	// Size of the devmode structure
	dmScreenSettings.dmSize = sizeof (DEVMODE);

	// Select screen width
	dmScreenSettings.dmPelsWidth = iWidth;

	// Select screen height
	dmScreenSettings.dmPelsHeight = iHeight;

	// Select bits per pixel
	dmScreenSettings.dmBitsPerPel = iBitsPerPixel;
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	// If succesful
	if (ChangeDisplaySettings (&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {

		// Display change failed
		return FALSE;
	}

	// Display change was succesful
	return TRUE;
}

/*******************************************************************************
* CreateWindowGL
*******************************************************************************/
BOOL CreateWindowGL (LGWindow* wWindow) {

	// Define our window style
	DWORD wWindowStyle = WS_OVERLAPPEDWINDOW;

	// Define the window's extended style
	DWORD wWindowExtendedStyle = WS_EX_APPWINDOW;

	// pPixelFormat tells windows how we want things to be
	PIXELFORMATDESCRIPTOR pPixelFormat = {
		sizeof (PIXELFORMATDESCRIPTOR),		// Size Of This Pixel Format Descriptor
		1,									// Version Number
		PFD_DRAW_TO_WINDOW |				// Format Must Support Window
		PFD_SUPPORT_OPENGL |				// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,					// Must Support Double Buffering
		PFD_TYPE_RGBA,						// Request An RGBA Format
		wWindow->wInit.iBitsPerPixel,		// Select Our Color Depth
		0, 0, 0, 0, 0, 0,					// Color Bits Ignored
		0,									// No Alpha Buffer
		0,									// Shift Bit Ignored
		0,									// No Accumulation Buffer
		0, 0, 0, 0,							// Accumulation Bits Ignored
		16,									// 16Bit Z-Buffer (Depth Buffer)  
		0,									// No Stencil Buffer
		0,									// No Auxiliary Buffer
		PFD_MAIN_PLANE,						// Main Drawing Layer
		0,									// Reserved
		0, 0, 0								// Layer Masks Ignored
	};

	// Define our window coordinates
	RECT rWindowRect = {0, 0, wWindow->wInit.iWidth, wWindow->wInit.iHeight};

	// Will hold the selected pixel format
	GLuint uPixelFormat;

	// Fullscreen requested, try changing video modes
	if (wWindow->wInit.bIsFullScreen == TRUE) {

		// If fullscreen mode failed
		if (ChangeScreenResolution (wWindow->wInit.iWidth, wWindow->wInit.iHeight, wWindow->wInit.iBitsPerPixel) == FALSE) {

			// Run In Windowed Mode Instead
			MessageBox (HWND_DESKTOP, "Mode Switch Failed.\nRunning In Windowed Mode.", "Error", MB_OK | MB_ICONEXCLAMATION);

			// Set fullscreen to false
			wWindow->wInit.bIsFullScreen = TRUE;

		// Otherwise fullscreen was successful
		} else {

			// Turn off the cursor
			ShowCursor (TRUE);

			// Set the windowstyle to WS_POPUP
			wWindowStyle = WS_POPUP;

			// Set the extended window style to WS_EX_TOPMOST
			wWindowExtendedStyle |= WS_EX_TOPMOST;
		}
	
	// Fullscreen nog selected
	} else {

		// Adjust Window, Account For Window Borders
		AdjustWindowRectEx (&rWindowRect, wWindowStyle, 0, wWindowExtendedStyle);
	}

	// Create The OpenGL Window
	wWindow->hWnd = CreateWindowEx (wWindowExtendedStyle,						// Extended Style
								   wWindow->wInit.aApplication->csClassName,	// Class Name
								   wWindow->wInit.cpTitle,						// Window Title
								   wWindowStyle,								// Window Style
								   0, 0,										// Window X,Y Position
								   rWindowRect.right - rWindowRect.left,		// Window Width
								   rWindowRect.bottom - rWindowRect.top,		// Window Height
								   HWND_DESKTOP,								// Desktop Is Window's Parent
								   0,											// No Menu
								   wWindow->wInit.aApplication->hInstance,		// Pass The Window Instance
								   wWindow);

	// If window creation no success
	if (wWindow->hWnd == 0) {

		// Return false
		return FALSE;
	}

	// Grab a device context for this window
	wWindow->hDC = GetDC (wWindow->hWnd);

	// Did we get a device context
	if (wWindow->hDC == 0) {

		// Destroy the window
		DestroyWindow (wWindow->hWnd);

		// Zero the window handle
		wWindow->hWnd = 0;

		// Return false
		return FALSE;
	}

	// Check if fsaa supported
	if(!arbMultisampleSupported) {

		// Find a compatible pixel format
		uPixelFormat = ChoosePixelFormat (wWindow->hDC, &pPixelFormat);

		// Did we find a compatible format
		if (uPixelFormat == 0) {

			// Release our device context
			ReleaseDC (wWindow->hWnd, wWindow->hDC);

			// Zero the device context
			wWindow->hDC = 0;

			// Destroy the window
			DestroyWindow (wWindow->hWnd);

			// Zero the window handle
			wWindow->hWnd = 0;

			// Return false
			return FALSE;
		}
	} else {

		// Set multisample
		uPixelFormat = arbMultisampleFormat;
	}

	// Try to set the pixel format
	if (SetPixelFormat (wWindow->hDC, uPixelFormat, &pPixelFormat) == FALSE) {

		// Release our device context
		ReleaseDC (wWindow->hWnd, wWindow->hDC);

		// Zero the device context
		wWindow->hDC = 0;

		// Detroy the window
		DestroyWindow (wWindow->hWnd);

		// Zero the window handle
		wWindow->hWnd = 0;

		// Return false
		return FALSE;
	}

	// Try to get a rendering context
	wWindow->hRC = wglCreateContext (wWindow->hDC);

	// No rendering context
	if (wWindow->hRC == 0) {

		// Release our device context
		ReleaseDC (wWindow->hWnd, wWindow->hDC);

		// Zero the device context
		wWindow->hDC = 0;

		// Destroy the window
		DestroyWindow (wWindow->hWnd);

		// Zero the window handle
		wWindow->hWnd = 0;

		// Return false
		return FALSE;
	}

	// Make The Rendering Context Our Current Rendering Context
	if (wglMakeCurrent (wWindow->hDC, wWindow->hRC) == FALSE) {

		// Delete the rendering context
		wglDeleteContext (wWindow->hRC);

		// Zero the rendering context
		wWindow->hRC = 0;

		// Release our device context
		ReleaseDC (wWindow->hWnd, wWindow->hDC);

		// Zero the device context
		wWindow->hDC = 0;

		// Destroy the window
		DestroyWindow (wWindow->hWnd);

		// Zero the window handle
		wWindow->hWnd = 0;

		// Return false
		return FALSE;
	}

	// If multi sample supported
	if (!arbMultisampleSupported && CHECK_FOR_MULTISAMPLE) {
	
		// If init fails
		if(InitMultisample(wWindow->wInit.aApplication->hInstance,wWindow->hWnd,pPixelFormat)) {

			// Exit
			DestroyWindowGL (wWindow);
			return CreateWindowGL(wWindow);
		}
	}

	// Make the window visible
	ShowWindow (wWindow->hWnd, SW_NORMAL);

	// Set visible to true
	wWindow->bIsVisible = TRUE;

	// Reshape our gl window
	ReshapeGL (wWindow->wInit.iWidth, wWindow->wInit.iHeight);

	// Clear all keys
	ZeroMemory (wWindow->kpKeys, sizeof (LGKeys));

	// Get tich count
	wWindow->dLastTickCount = GetTickCount ();

	// Window creating was a success
	return TRUE;
}

/*******************************************************************************
* DestroyWindowGL
*******************************************************************************/
BOOL DestroyWindowGL (LGWindow* wWindow) {

	// Does the window have a handle
	if (wWindow->hWnd != 0) {

		// Does the window have a device context
		if (wWindow->hDC != 0) {

			// Set the current active rendering context to zero
			wglMakeCurrent (wWindow->hDC, 0);

			// Does the window have a rendering context
			if (wWindow->hRC != 0) {

				// Release the rendering context
				wglDeleteContext (wWindow->hRC);

				// Zero the rendering context
				wWindow->hRC = 0;
			}

			// Release the device context
			ReleaseDC (wWindow->hWnd, wWindow->hDC);

			// Zero the device context
			wWindow->hDC = 0;
		}

		// Destroy the window
		DestroyWindow (wWindow->hWnd);

		// Zero the window handle
		wWindow->hWnd = 0;
	}

	// Is window in fullscreen mode
	if (wWindow->wInit.bIsFullScreen) {

		// Switch back to desktop resolution
		ChangeDisplaySettings (NULL,0);

		// Show the cursor
		ShowCursor (TRUE);
	}	

	// Return true
	return TRUE;
}

/*******************************************************************************
* WindowProc
*******************************************************************************/
LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	// Get The Window Context
	LGWindow* wWindow = (LGWindow*)(GetWindowLong (hWnd, GWL_USERDATA));

	// Evaluate window message
	switch (uMsg) {

		// Intercept system commands
		case WM_SYSCOMMAND: {

			// Check system calls
			switch (wParam) {

				// Screensaver trying to start
				case SC_SCREENSAVE:

				// Monitor trying to enter powersave
				case SC_MONITORPOWER:

				// Prevent from happening
				return 0;
			}
			break;
		}

		// Return 0
		return 0;

		// Window creation
		case WM_CREATE: {

			// Store window structure pointer
			CREATESTRUCT* creation = (CREATESTRUCT*)(lParam);
			wWindow = (LGWindow*)(creation->lpCreateParams);
			SetWindowLong (hWnd, GWL_USERDATA, (LONG)(wWindow));
		}

		// Return 0
		return 0;

		// Closing the window
		case WM_CLOSE:

			// Terminate the application
			TerminateApplication(wWindow);

		// Return 0
		return 0;

		// Size action has taken place
		case WM_SIZE:

			// Evaluate size action
			switch (wParam) {

				// Was window minimized
				case SIZE_MINIMIZED:

					// Set visible to false
					wWindow->bIsVisible = FALSE;

				// Return 0
				return 0;

				// Was window maximized
				case SIZE_MAXIMIZED:

					// Set visible to true
					wWindow->bIsVisible = TRUE;

					// Reshape window - loword=width, hiword=height
					ReshapeGL (LOWORD (lParam), HIWORD (lParam));

				// Return 0
				return 0;

				// Was window restored
				case SIZE_RESTORED:

					// Set visible to true
					wWindow->bIsVisible = TRUE;

					// Reshape window - loword=width, hiword=height
					ReshapeGL (LOWORD (lParam), HIWORD (lParam));

				// Return 0
				return 0;
			}

		// Break
		break;

		// Update keyboard buffers for keys pressed
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:

			// Is key in a valid range
			if ((wParam >= 0) && (wParam <= 255)) {

				// Set the selected key to true
				wWindow->kpKeys->abKeyDown [wParam] = TRUE;

				// OnKeyDown event handler
				OnKeyDown (wParam, wWindow);

				// Return 0
				return 0;
			}

		// Break
		break;

		// Update keyboard buffers for keys released
		case WM_KEYUP:

			// Is key in a valid range
			if ((wParam >= 0) && (wParam <= 255)) {

				// Set the selected key to false
				wWindow->kpKeys->abKeyDown [wParam] = FALSE;

				// Return 0
				return 0;
			}

		// Break
		break;

		// Toggle fullscreen mode on/off
		case WM_TOGGLEFULLSCREEN:

			// Toggle fullscreen
			bCreateFullScreen = (bCreateFullScreen == TRUE) ? FALSE : TRUE;

			// Quit
			PostMessage (hWnd, WM_QUIT, 0, 0);

		// Break
		break;

		// Left button down
		case WM_LBUTTONDOWN:
			{
	            iMouseDownX = iMouseX = LOWORD(lParam);          
				iMouseDownY = iMouseY = HIWORD(lParam);
				iMouseButtonLeft = 1;
			}
			OnMouseDown (0, iMouseX, iMouseY);
		// Break
		break;

		// Left button up
		case WM_LBUTTONUP:
			{
	            iMouseX = LOWORD(lParam);          
				iMouseY = HIWORD(lParam);
				iMouseButtonLeft = 0;
			}
		// Break
		break;

		// Right button down
		case WM_RBUTTONDOWN:
			{
	            iMouseDownX = iMouseX = LOWORD(lParam);
				iMouseDownY = iMouseY = HIWORD(lParam);
				iMouseButtonRight = 1;
			}
			OnMouseDown (2, iMouseX, iMouseY);
		// Break
		break;

		// Right button up
		case WM_RBUTTONUP:
			{
	            iMouseX = LOWORD(lParam);
				iMouseY = HIWORD(lParam);
				iMouseButtonRight = 0;
			}
		// Break
		break;

		// Middle button down
		case WM_MBUTTONDOWN:
			{
	            iMouseDownX = iMouseX = LOWORD(lParam);
				iMouseDownY = iMouseY = HIWORD(lParam);
				iMouseButtonMiddle = 1;
			}
			OnMouseDown (1, iMouseX, iMouseY);
		// Break
		break;

		// Middle button up
		case WM_MBUTTONUP:
			{
	            iMouseX = LOWORD(lParam);
				iMouseY = HIWORD(lParam);
				iMouseButtonMiddle = 0;
			}
		// Break
		break;

		// Mouse move
		case WM_MOUSEMOVE:
			{
	            iMouseX = LOWORD(lParam);          
				iMouseY = HIWORD(lParam);
			}
		// Break
		break;	
	}

	// Pass unhandled messages to defwindowproc
	return DefWindowProc (hWnd, uMsg, wParam, lParam);
}

/*******************************************************************************
* RegisterWindowClass
*******************************************************************************/
BOOL RegisterWindowClass (LGApplication* aApplication) {

	// Register A Window Class
	WNDCLASSEX wWindowClass;									// Window Class
	ZeroMemory (&wWindowClass, sizeof (WNDCLASSEX));			// Make Sure Memory Is Cleared
	wWindowClass.cbSize = sizeof (WNDCLASSEX);					// Size Of The wWindowClass Structure
	wWindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraws The Window For Any Movement / Resizing
	wWindowClass.lpfnWndProc = (WNDPROC)(WindowProc);			// WindowProc Handles Messages
	wWindowClass.hInstance = aApplication->hInstance;			// Set The Instance
	wWindowClass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);	// Class Background Brush Color
	wWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wWindowClass.lpszClassName = aApplication->csClassName;		// Sets The Applications Classname

	// Did registering the class fail
	if (RegisterClassEx (&wWindowClass) == 0) {

		// NOTE: Failure, Should Never Happen
		MessageBox (HWND_DESKTOP, "RegisterClassEx Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// Return true
	return TRUE;
}

/*******************************************************************************
* WinMain
*******************************************************************************/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	extern PFNGLGENBUFFERSARBPROC glGenBuffersARB;				// VBO Name Generation Procedure
	extern PFNGLBINDBUFFERARBPROC glBindBufferARB;				// VBO Bind Procedure
	extern PFNGLBUFFERDATAARBPROC glBufferDataARB;				// VBO Data Loading Procedure
	extern PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;		// VBO Deletion Procedure
	extern PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElementsEXT;	// VBO Deletion Procedure
	extern bool bVBOSupported;									// VBO supported
	LGApplication	aApplication;				// Application Structure
	LGWindow		wWindow;					// Window Structure
	LGKeys			kpKeys;						// Key Structure
	BOOL			bIsMessagePumpActive;		// Message Pump Active?
	MSG				mMsg;						// Window Message Structure
	DWORD			dTickCount;					// Used For The Tick Counter

	// Fill Out Application Data
	aApplication.csClassName = "OpenGL";
	aApplication.hInstance = hInstance;

	// Fill Out Window
	ZeroMemory (&wWindow, sizeof (LGWindow));		// Make Sure Memory Is Zeroed
	wWindow.kpKeys = &kpKeys;						// Window Key Structure
	wWindow.wInit.aApplication = &aApplication;		// Window Application
	wWindow.wInit.cpTitle = "L3G0";					// Window Title
	wWindow.wInit.iWidth = 1024;					// Window Width
	wWindow.wInit.iHeight = 768;					// Window Height
	wWindow.wInit.iBitsPerPixel = 32;				// Bits Per Pixel
	wWindow.wInit.bIsFullScreen = FALSE;			// Fullscreen? (Set To TRUE)

	// Zero kpKeys structure
	ZeroMemory (&kpKeys, sizeof (LGKeys));

	// Ask The User If They Want To Start In FullScreen Mode?
//	if (MessageBox (HWND_DESKTOP, "Would You Like To Run In Fullscreen Mode?", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDNO) {

		// If not, run in windowed mode
		wWindow.wInit.bIsFullScreen = FALSE;
//	}

	// Register A Class For Our Window To Use
	if (RegisterWindowClass (&aApplication) == FALSE) {

		// Failure
		MessageBox (HWND_DESKTOP, "Error Registering Window Class!", "Error", MB_OK | MB_ICONEXCLAMATION);

		// Terminate application
		return -1;
	}

	// Program looping is set to true
	bIsProgramLooping = TRUE;

	// Fullscreen is set to default
	bCreateFullScreen = wWindow.wInit.bIsFullScreen;

	// Loop until WM_QUIT is recieved
	while (bIsProgramLooping) {

		// Create A Window
		wWindow.wInit.bIsFullScreen = bCreateFullScreen;

		// Was window creation successful
		if (CreateWindowGL (&wWindow) == TRUE) {

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
			glDrawRangeElementsEXT = (PFNGLDRAWRANGEELEMENTSPROC) wglGetProcAddress("glDrawRangeElementsEXT");

			// Call user initialization
			if (Initialize (&wWindow, &kpKeys) == FALSE) {

				// Failure
				TerminateApplication (&wWindow);

			// Otherwise start the message pump
			} else {

				// Set message pump active to true
				bIsMessagePumpActive = TRUE;

				// While the message pump is active
				while (bIsMessagePumpActive == TRUE) {

					// Success Creating Window.  Check For Window Messages
					if (PeekMessage (&mMsg, wWindow.hWnd, 0, 0, PM_REMOVE) != 0) {

						// Check For WM_QUIT Message
						if (mMsg.message != WM_QUIT) {

							// Dispatch the message
							DispatchMessage (&mMsg);

						// Otherwise if WM_QUIT
						} else {

							// Terminate the message pump
							bIsMessagePumpActive = FALSE;
						}

					// If there are no messages
					} else {

						// If window is not visible
						if (wWindow.bIsVisible == FALSE) {

							// Application is minimized wait for a message
							WaitMessage ();

						// If window is visible
						} else {

							// Get the tick count
							dTickCount = GetTickCount ();

							// Update the counter
							Update (dTickCount - wWindow.dLastTickCount, &wWindow, &kpKeys);

							// Set last count to current count
							wWindow.dLastTickCount = dTickCount;

							// Draw our scene
							Draw (&wWindow);

							// Swap buffers
							SwapBuffers (wWindow.hDC);
						}
					}
				}
			}

			// Application Is Finished
			Deinitialize ();

			// Destroy the active window
			DestroyWindowGL (&wWindow);

		// If window creation failed
		} else {

			// Error Creating Window
			MessageBox (HWND_DESKTOP, "Error Creating OpenGL Window", "Error", MB_OK | MB_ICONEXCLAMATION);

			// Terminate the loop
			bIsProgramLooping = FALSE;
		}
	}

	// Unregister window class
	UnregisterClass (aApplication.csClassName, aApplication.hInstance);

	// Return 0
	return 0;
}

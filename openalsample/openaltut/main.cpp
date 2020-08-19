/*
OpenAL test code using OpenGL
Based on OpenGL basecode from nehe.gamedev.net
 */

#include <windows.h>									// Header File For Windows
#include <math.h>										// Math Library Header File
#include <stdio.h>										// Header File For Standard Input/Output
#include <gl\gl.h>										// Header File For The OpenGL32 Library
#include <gl\glu.h>										// Header File For The GLu32 Library
#include <gl\glaux.h>									// Header File For The Glaux Library
#include <dinput.h>										// Direct Input Functions ( Add )
#include <alut.h>
#include <alc.h>
#include "alsound.h"

extern int DI_Init(HINSTANCE hInstance, HWND hWnd);
extern void DX_End();

//functions to set listener properties
extern void SetListenerPosition(float x, float y, float z);
extern void SetListenerOrientation(float fx, float fy, float fz, float ux, float uy, float uz);

extern LPDIRECTINPUTDEVICE8	g_KDIDev;

HDC			hDC=NULL;									// Private GDI Device Context
HGLRC		hRC=NULL;									// Permanent Rendering Context
HWND		hWnd=NULL;									// Holds Our Window Handle
HINSTANCE	hInstance;									// Holds The Instance Of The Application

BYTE	buffer[256];									// (Modified... Removed 'keys[]')
bool	active=TRUE;									// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;								// Fullscreen Flag Set To Fullscreen Mode By Default
bool	blend;											// Blending ON/OFF
bool	bp;												// Blend Button Pressed? (Modified, Just The Caption)
bool	fp;												// F1 Button Pressed?

const	float piover180 = 0.0174532925f;
float	heading;
float	xpos;
float   ypos;
float	zpos;

GLfloat	yrot;											// Y Rotation
GLfloat	lookupdown = 0.0f;

float wateroffset=0.0f;

GLuint	texture[6];										// Storage For 5 Textures (Modified... We'll Need This Later)

int textviewwidth=640;
int textviewheight=480;

//structure to hold our sounds
Sound sounds[5];

int collarray[18][19];

struct polygon
{
	float x[4], y[4], z[4];
	float u[4], v[4];
	int texnum;
};

polygon *polys;
polygon *waterpolys;
int numpolygons=0;
int numwaterpolygons=0;

// Create A Structure For The Timer Information
struct
{
  __int64       frequency;								// Timer Frequency
  float         resolution;								// Timer Resolution
  unsigned long mm_timer_start;     
  
  // Multimedia Timer Start Value
  unsigned long mm_timer_elapsed;						// Multimedia Timer Elapsed Time
  bool   performance_timer;    
  
  // Using The Performance Timer?
  __int64       performance_timer_start;				// Performance Timer Start Value
  __int64       performance_timer_elapsed;				// Performance Timer Elapsed Time
} timer;												// Structure Is Named 'timer'


LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

void TimerInit(void)
{
     memset(&timer, 0, sizeof(timer));   
	 // Clear Our Timer Structure
     // Check To See If A Performance Counter Is Available
     // If One Is Available The Timer Frequency Will Be Updated
     if (!QueryPerformanceFrequency((LARGE_INTEGER *) &timer.frequency))
     {
          // No Performace Counter Available
          timer.performance_timer = FALSE;  
		  // Set Performance Timer To FALSE
          timer.mm_timer_start = timeGetTime();			// Use timeGetTime() To Get Current Time
          timer.resolution  = 1.0f/1000.0f;				// Set Our Timer Resolution To .001f
          timer.frequency   = 1000;   
		  // Set Our Timer Frequency To 1000
          timer.mm_timer_elapsed = timer.mm_timer_start;	// Set The Elapsed Time To The Current Time
     }
     else
     {
          // Performance Counter Is Available, Use It Instead Of The Multimedia Timer
          // Get The Current Time And Store It In performance_timer_start
          QueryPerformanceCounter((LARGE_INTEGER *) &timer.performance_timer_start);
          timer.performance_timer   = TRUE;    // Set Performance Timer To TRUE
          // Calculate The Timer Resolution Using The Timer Frequency
          timer.resolution    = (float) (((double)1.0f)/((double)timer.frequency));
          // Set The Elapsed Time To The Current Time
          timer.performance_timer_elapsed = timer.performance_timer_start;
     }
}

// Get Time In Milliseconds ( Add )
float TimerGetTime()
{
     __int64 time;        
	// 'time' Will Hold A 64 Bit Integer
     if (timer.performance_timer)						// Are We Using The Performance Timer?
     {
          QueryPerformanceCounter((LARGE_INTEGER *) &time);	// Grab The Current Performance Time
          // Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
          return ( (float) ( time - timer.performance_timer_start) * timer.resolution)*1000.0f;
     }
     else
     {
          // Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
          return( (float) ( timeGetTime() - timer.mm_timer_start) * timer.resolution)*1000.0f;
     }
}


AUX_RGBImageRec *LoadBMP(char *Filename)                // Loads A Bitmap Image
{
        FILE *File=NULL;                                // File Handle

        if (!Filename)                                  // Make Sure A Filename Was Given
        {
                return NULL;                            // If Not Return NULL
        }

        File=fopen(Filename,"r");                       // Check To See If The File Exists

        if (File)                                       // Does The File Exist?
        {
                fclose(File);                           // Close The Handle
                return auxDIBImageLoad(Filename);       // Load The Bitmap And Return A Pointer
        }
        return NULL;                                    // If Load Failed Return NULL
}

int LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
{
    int Status=FALSE;									// Status Indicator
    AUX_RGBImageRec *TextureImage[6];					// Create Storage Space For The Textures
    memset(TextureImage,0,sizeof(void *)*6);			// Set The Pointer To NULL
    if ((TextureImage[0]=LoadBMP("Data/grass.bmp")) &&	// Load The Floor Texture
        (TextureImage[1]=LoadBMP("Data/evgreen.bmp")) &&	// Load the Light Texture
        (TextureImage[2]=LoadBMP("Data/rocks.bmp")) &&	// Load the Wall Texture
        (TextureImage[3]=LoadBMP("Data/water.bmp")) &&	// Load the Crate Texture
        (TextureImage[4]=LoadBMP("Data/dirt.bmp")) &&	// Load the Crate Texture
        (TextureImage[5]=LoadBMP("Data/wood.bmp")))	// Load the Ceiling Texture
	{   
		Status=TRUE;									// Set The Status To TRUE
		glGenTextures(6, &texture[0]);					// Create The Texture
		for (int loop1=0; loop1<6; loop1++)				// Loop Through 5 Textures
		{
			glBindTexture(GL_TEXTURE_2D, texture[loop1]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[loop1]->sizeX, TextureImage[loop1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[loop1]->data);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
		for (loop1=0; loop1<6; loop1++)					// Loop Through 5 Textures
		{
			if (TextureImage[loop1])					// If Texture Exists
			{
				if (TextureImage[loop1]->data)			// If Texture Image Exists
				{
					free(TextureImage[loop1]->data);	// Free The Texture Image Memory
				}
				free(TextureImage[loop1]);				// Free The Image Structure 
			}
		}
	}
	return Status;										// Return The Status
}


GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,2000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int RoundUp(float x)
{
	int n;

	if (x<0)
		n = (int)x;
	else
		n = (int)x +1;
	return(n);
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	if (!LoadGLTextures())								// Jump To Texture Loading Routine
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency
	glClearColor(0.0f, 0.8f, 1.0f, 0.0f);				// This Will Clear The Background Color To Black
	glClearDepth(1.0);									// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);								// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glShadeModel(GL_SMOOTH);							// Enables Smooth Color Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	return TRUE;										// Initialization Went OK
}

void DrawLevel()
{
	int i, j;
	//draw the standard area polygons
	for (i=0; i<numpolygons; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texture[polys[i].texnum]);

		glBegin(GL_QUADS);
		for (j=0; j<4; j++)
		{
			glTexCoord2f(polys[i].u[j],polys[i].v[j]);
			glVertex3f(polys[i].x[j],polys[i].y[j],polys[i].z[j]);
		}
		glEnd();
	}

}

void DrawWater()
{
	int i, j;

	//enable blending
	glEnable(GL_BLEND);

	//now draw the water polygons
	for (i=0; i<numwaterpolygons; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texture[waterpolys[i].texnum]);

		glBegin(GL_QUADS);
		for (j=0; j<4; j++)
		{
			glTexCoord2f(waterpolys[i].u[j],waterpolys[i].v[j]+wateroffset);
			glVertex3f(waterpolys[i].x[j],waterpolys[i].y[j],waterpolys[i].z[j]);
		}
		glEnd();
	}

	//disable blending
	glDisable(GL_BLEND);

}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View

	GLfloat sceneroty = 360.0f - yrot;

	glRotatef(lookupdown,1.0f,0,0);
	glRotatef(sceneroty,0,1.0f,0);
	
	//move the player
	glTranslatef(-xpos,-ypos,-zpos);

	DrawLevel();
	DrawWater();

	//get current view matrix
	double mMatrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX,mMatrix);

	//set listener properties
	SetListenerPosition(xpos,ypos,zpos);
	//set listener orientation, first 3 numbers are for the forward vector, last three are for the up vector
	SetListenerOrientation(-mMatrix[2],-mMatrix[6],-mMatrix[10],mMatrix[1],mMatrix[5],mMatrix[9]);

	return TRUE;										// Everything Went OK
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}
	
	ShowCursor(FALSE);    // Hide Mouse Pointer (Modified)

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop
	ALCcontext *Context;
	ALCdevice *Device;
	FILE *fp;

	//mouse pointer
	POINT mpos;

	//new variables for movement
	float ctimer; //used to check the current time
	float timerdiff; //used to determine the time elapsed
	float secsperframe; //used to hold the value for how many seconds have elapsed between frames
	float desireddistance; //desired distance to move in a second
	float movementvalue; //value to move by each frame
	float ntime;
	int i, j;
	int xp, zp;

	desireddistance=2.0f;

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("OpenAL Tutorial",640,480,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	if (DI_Init(hInstance, hWnd)!=0)
	{
		return 0;									// Couldn't Initialize, Quit
	}

	//initialize OpenAL

	//Open device
	Device = alcOpenDevice((ALubyte*)"DirectSound3D");

	if (Device == NULL)
	{
		//we failed to initialize the device
		exit(-1);
	}

	//Create context(s)
	Context=alcCreateContext(Device,NULL);
	//Set active context
	alcMakeContextCurrent(Context);

	// Clear Error Code
	alGetError();

	//open up main data file
	fp = fopen("data/level.txt","r");
	fscanf(fp,"%d\n",&numpolygons);
	polys = new polygon[numpolygons];
	for (i=0; i<numpolygons; i++)
	{
		for (j=0; j<4; j++)
		{
			fscanf(fp,"%f %f %f %f %f %d\n",&polys[i].x[j],&polys[i].y[j],&polys[i].z[j],&polys[i].u[j],&polys[i].v[j],&polys[i].texnum);
		}
	}
	fclose(fp);

	//open up water data file
	fp = fopen("data/water.txt","r");
	fscanf(fp,"%d\n",&numwaterpolygons);
	waterpolys = new polygon[numwaterpolygons];
	for (i=0; i<numwaterpolygons; i++)
	{
		for (j=0; j<4; j++)
		{
			fscanf(fp,"%f %f %f %f %f %d\n",&waterpolys[i].x[j],&waterpolys[i].y[j],&waterpolys[i].z[j],&waterpolys[i].u[j],&waterpolys[i].v[j],&waterpolys[i].texnum);
		}
	}
	fclose(fp);

	//open up collision file for collision detection info
	fp = fopen("data/collision.txt","r");
	for (i=17; i>=0; i--)
	{
		for (j=18; j>=0; j--)
		{
			fscanf(fp,"%d ",&collarray[i][j]);
		}
		fscanf(fp,"\n");
	}
	fclose(fp);

	//set out initial position in the game world
	xpos = 3.0f;
	ypos = 1.0f;
	zpos = 5.0f;

	//load up our water sound
	sounds[0].LoadSound("data/water.wav",1);

	//set the position of the sound effect
	sounds[0].SetProperties(8.5f,0.0f,15.0f,0.0f,0.0f,0.0f);
	//sounds[0].SetMaxDistance(10.0f);
	sounds[0].PlaySound();


	//set the initial listener position
	SetListenerPosition(xpos,ypos,zpos);

	//intialize the timer
	TimerInit();
	ctimer = TimerGetTime();

	while(!done)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else
		{

			if ((active && !DrawGLScene()))		
			{
				done=TRUE;
			}
			else
			{

				//first determine how many seconds elapsed
				ntime = TimerGetTime();

				timerdiff = ntime-ctimer;

				//the function reads in milliseconds so convert to seconds
				secsperframe=(float)(timerdiff/1000.0f);

				//update the water texture offset, this creates the effect of the water moving
				wateroffset+= (secsperframe/2.0f);
				if (wateroffset>=1.0f)
					wateroffset-=1.0f;

				//now compute the movement value
				movementvalue = (float)(desireddistance*secsperframe);

				//get the new time
				ctimer = ntime;

				SwapBuffers(hDC);
				GetCursorPos(&mpos);

				SetCursorPos(320,240);

				//compute our new direction
				heading += (float)(320 - mpos.x)/100 * 5;
				yrot = heading;
				lookupdown -= (float)(240 - mpos.y)/100 * 5;

				HRESULT hr = g_KDIDev->GetDeviceState(sizeof(buffer), &buffer);

				if ( buffer[DIK_ESCAPE] & 0x80 )
				{
					done=TRUE;
				}

				if ( buffer[DIK_UP] & 0x80 )
				{
					float newx, newz;

					//first move in the x direction and check for collision
					newx = xpos - ((float)sin(heading*piover180) * movementvalue);
					newz = zpos;

					xp = RoundUp(newx);
					zp = RoundUp(newz);

					if (collarray[zp][xp]==1)
					{
						//if collision
						//reset value to just x position
						newx = xpos;
					}
					else
					{
						//no collision so move in the x direction
						xpos -= (float)sin(heading*piover180) * movementvalue;
					}


					//get new z position
					newz = zpos - ((float)cos(heading*piover180) * movementvalue);

					xp = RoundUp(newx);
					zp = RoundUp(newz);

					if (collarray[zp][xp]==1)
					{
						//if collision, reset value
						newz = zpos;
					}
					else
					{
						//no collision so move in the z direction
						zpos -= (float)cos(heading*piover180) * movementvalue;
					}

				}

				if ( buffer[DIK_DOWN] & 0x80 )
				{
					float newx, newz;

					//move in x direction and look for collision
					newx = xpos + (float)sin(heading*piover180) * movementvalue;
					newz = zpos;

					xp = RoundUp(newx);
					zp = RoundUp(newz);

					if (collarray[zp][xp]==1)
					{
						//if collision
						//reset value to just x position
						newx = xpos;
					}
					else
					{
						//no collision so move in the x direction
						xpos += (float)sin(heading*piover180) * movementvalue;
					}

					//get new z position
					newz = zpos + (float)cos(heading*piover180) * movementvalue;

					xp = RoundUp(newx);
					zp = RoundUp(newz);

					if (collarray[zp][xp]==1)
					{
						//if collision, reset value
						newz = zpos;
					}
					else
					{
						//no collision so move in the z direction
						zpos += (float)cos(heading*piover180) * movementvalue;
					}

				}

				if ( buffer[DIK_LEFT] & 0x80 )
				{
					float newx, newz;

					//first move in the x direction and check for collision
					newx = xpos + (float)sin((heading - 90)*piover180) * movementvalue;
					newz = zpos;

					xp = RoundUp(newx);
					zp = RoundUp(newz);

					if (collarray[zp][xp]==1)
					{
						//if collision
						//reset value to just x position
						newx = xpos;
					}
					else
					{
						//no collision so move in the x direction
						xpos += (float)sin((heading - 90)*piover180) * movementvalue;
					}


					//get new z position
					newz = zpos + (float)cos((heading - 90)*piover180) * movementvalue;

					xp = RoundUp(newx);
					zp = RoundUp(newz);

					if (collarray[zp][xp]==1)
					{
						//if collision, reset value
						newz = zpos;
					}
					else
					{
						//no collision so move in the z direction
						zpos += (float)cos((heading - 90)*piover180) * movementvalue;
					}

				}

				if ( buffer[DIK_RIGHT] & 0x80 )
				{
					float newx, newz;

					//first move in the x direction and check for collision
					newx = xpos + (float)sin((heading + 90)*piover180) * movementvalue;
					newz = zpos;

					xp = RoundUp(newx);
					zp = RoundUp(newz);

					if (collarray[zp][xp]==1)
					{
						//if collision
						//reset value to just x position
						newx = xpos;
					}
					else
					{
						//no collision so move in the x direction
						xpos += (float)sin((heading + 90)*piover180) * movementvalue;
					}


					//get new z position
					newz = zpos + (float)cos((heading + 90)*piover180) * movementvalue;

					xp = RoundUp(newx);
					zp = RoundUp(newz);

					if (collarray[zp][xp]==1)
					{
						//if collision, reset value
						newz = zpos;
					}
					else
					{
						//no collision so move in the z direction
						zpos += (float)cos((heading + 90)*piover180) * movementvalue;
					}

				}


			}
		}
	}

	//destroy our sound
	sounds[0].DestroySound();

	// Shutdown
	//Get active context
	Context=alcGetCurrentContext();
	//Get device for active context
	Device=alcGetContextsDevice(Context);
	//Disable context
	alcMakeContextCurrent(NULL);
	//Release context(s)
	alcDestroyContext(Context);
	//Close device
	alcCloseDevice(Device);

	DX_End();
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}

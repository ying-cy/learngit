#define STRICT

#include <windows.h>
#include <basetsd.h>
#include <dinput.h>
#include <dxerr8.h>
#include <stdio.h>

LPDIRECTINPUT8       g_DI              = NULL;         
LPDIRECTINPUTDEVICE8	g_KDIDev;
DIDEVCAPS            g_diDevCaps;

int DI_Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;


	hr= (DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
						   IID_IDirectInput8, (void**)&g_DI, NULL));
	if(FAILED(hr))
	{
		return 1;
	}

	//Create the keyboard's device object
	hr= (g_DI->CreateDevice(GUID_SysKeyboard, &g_KDIDev, NULL));
	if(FAILED(hr))
	{
		return 2;
	}

    if ( g_KDIDev->SetDataFormat(&c_dfDIKeyboard) )	// Set The Keyboard Data Format
    {
		// Couldn't Set The Data Format
        return 2;						// Failed, Return False
    }

    // Set The Cooperative Level
    if ( g_KDIDev->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE) )
    {
		// Couldn't Set The Cooperative Level
        return 2;							// Failed, Return False
    }

    if (g_KDIDev)									// Did We Create The Keyboard Device?
        g_KDIDev->Acquire();						// If So, Acquire It
    else
        return 2;								// If Not, Return False


	return(0);
}

void DX_End()
{
    if (g_DI)
    {
        if (g_KDIDev)
        {
            g_KDIDev->Unacquire();
            g_KDIDev->Release();
            g_KDIDev = NULL;
        }
        g_DI->Release();
        g_DI = NULL;
    }
}

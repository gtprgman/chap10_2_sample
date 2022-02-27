// chap10_win32_project_02.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <windows.h>
#include <Windowsx.h>

#include <CommCtrl.h>
#include <WinUser.h>


#include "chap10_win32_project_02.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


// child window's handle
HWND winChild = NULL;

// reserved handle to window procedure
WNDPROC winOldProc;
// reserved window style
LONG winOldStyle = 0;
// to keep number of wndproc changes
int nProcChanges = 0;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LONG_PTR CALLBACK    BtnProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CHAP10_WIN32_PROJECT_02, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	
	
	
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHAP10_WIN32_PROJECT_02));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHAP10_WIN32_PROJECT_02));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CHAP10_WIN32_PROJECT_02);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_GUI_CHANGEWINDOW:
			{
				if (!winOldStyle) {
					winOldStyle = SetWindowLongPtrW(winChild, GWL_STYLE, WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_BITMAP | BS_ICON | BS_TEXT );
					SetWindowPos(winChild, HWND_NOTOPMOST, 10, 10, 60, 60, SWP_FRAMECHANGED | SWP_DRAWFRAME | SWP_SHOWWINDOW);
				}
				else
				{
					SetWindowLongPtrW(winChild, GWL_STYLE, winOldStyle);
					SetWindowPos(winChild, HWND_NOTOPMOST, 10, 10, 60, 60, SWP_FRAMECHANGED | SWP_DRAWFRAME | SWP_SHOWWINDOW); winOldStyle = 0;
				}

				InvalidateRect(winChild, nullptr, TRUE);

			}
			break;

			case ID_GUI_CHANGEWINDOW32772:
			{
				if (!nProcChanges) {
					winOldProc = (WNDPROC)SetWindowLongPtrW(winChild, GWLP_WNDPROC, (LONG)BtnProc);
					SetWindowPos(winChild, HWND_NOTOPMOST, 10, 10, 60, 60, SWP_DRAWFRAME | SWP_SHOWWINDOW);

					nProcChanges = -1;
				}
				else {
					SetWindowLongPtrW(winChild, GWLP_WNDPROC, (LONG)winOldProc);
					SetWindowPos(winChild, HWND_NOTOPMOST, 10, 10, 60, 60, SWP_DRAWFRAME | SWP_SHOWWINDOW);
				
					nProcChanges = 0;
				}

			}
			break;

			case BN_CLICKED:
				MessageBoxExW(NULL, TEXT("Button Clicked !"), TEXT("Action Info"), MB_OK, NULL);
				break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

	case WM_CREATE:
	{
		winChild = CreateWindowW(TEXT("Button"), TEXT("Ok"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 10, 10, 60, 60,
			hWnd, NULL, GetModuleHandle(NULL), NULL);


		if (winChild) {
			ShowWindow(winChild, SW_SHOW);
			UpdateWindow(winChild);
		}

	}
	break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


LONG_PTR CALLBACK BtnProc(HWND hwndButton, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case BM_SETSTATE:
		MessageBoxExW(nullptr, TEXT("Button State Changed ! "), TEXT("In Replacement WNDPROC .. "), MB_OK, NULL);
		break;
	default:
		return CallWindowProcW(winOldProc, winChild, uMsg, wParam, lParam);
	}

	return 0;
}

/*
* Mon: Lap trinh huong doi tuong
* Bai tap lon: bai 3
* Giang vien: Ths. Nguyen Ngoc Long
* Nhom: N1
* Sinh vien 1: Du Tu Tinh, MSSV: 19110475
* Sinh vien 2: Huynh Thi Bao Tran, MSSV: 19110482
* Microsoft Visual Studio 2019
*/
//===============================================

// drawShapeApp.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"
#include "drawShapeApp.h"
#include "cShape.h"
#include "cPolygon.h"
#include "cTriangle.h"
#include "cRectangle.h"
#include "cSquare.h"
#include "cEllipse.h"
#include "cCircle.h"
#include "cSemicircle.h"

#define MAX_LOADSTRING 500

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_DRAWSHAPEAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAWSHAPEAPP));

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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAWSHAPEAPP));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DRAWSHAPEAPP);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    
    //thong diep
    static wchar_t szItsMessage[MAX_LOADSTRING] = L"";
    static wchar_t szInfor[] = L"Drawing and manipulating program";
    static wchar_t szInfor1[] = L"Arrow keys(Move) - Tab key(Change object of shape 1) - '-' key(Zoom out) - '+' key(Zoom in) - 'l' key(Rotate left) - 'r' key(Rotate right) - 'C + key' (Change to shape 2)";
    
    //brush and pen
    static HBRUSH hbr1, hbr2;
    static HPEN hPenDot, penBorder1, penBorder2, penBorder;
    
    //cursor
    static HCURSOR hCursorMove, hCursorCross;
    
    //variable
    static const int MAX_SHAPE = 50;
    static int xc, yc, px, py;
    static INT nCur = -1;
    int dx, dy;
    RECT rt;
    
    //objects
    static cPoint p[3] = { cPoint(100,300), cPoint(500, 300), cPoint(300,100) };
    static cPoint p2[3] = { cPoint(500,500), cPoint(700, 200), cPoint(800,500) };
    static cPoint plg1[5] = { cPoint(200,200), cPoint(500, 200), cPoint(600, 400), cPoint(350, 500), cPoint(100, 400) };
    static cPoint plg2[6] = { cPoint(600,300), cPoint(750, 250), cPoint(800, 350), cPoint(700, 400), cPoint(600, 350), cPoint(600, 300) };
    static cSquare A;
    static cShape* aS1[] = {
        new cPolygon(5, plg1),
        new cSemicircle(300,300,200),
        new cEllipse(300,250,200,100),
        new cRectangle(200, 100, 300, 200),
        new cCircle(200, 200, 150),
        new cTriangle(p),
        new cSquare(100, 100, 200)
    };
    static cShape* aS2[] = {
        new cPolygon(6, plg2),
        new cSemicircle(600,600,200),
        new cEllipse(800,250,200,100),
        new cRectangle(600, 100, 300, 200),
        new cCircle(600, 200, 150),
        new cTriangle(p2),
        new cSquare(700, 100, 200)
    };
    static int h = 0, h2 = 0;
    const int n = sizeof(aS1) / sizeof(aS1[0]), n2 = sizeof(aS2) / sizeof(aS2[0]);
    static cShape* pS = aS1[h];
    static cShape* pS2 = aS2[h2];
    
    switch (message)
    {
    case WM_CREATE:
        GetClientRect(hWnd, &rt);
        hbr1 = CreateSolidBrush(RGB(167, 210, 120));
        hbr2 = CreateSolidBrush(RGB(179, 208, 145));
        hCursorMove = LoadCursor(NULL, IDC_SIZEALL);
        hCursorCross = LoadCursor(NULL, IDC_CROSS);
        penBorder = CreatePen(PS_SOLID, 4, RGB(226, 238, 202));
        penBorder1 = CreatePen(PS_SOLID, 2, RGB(50, 160, 55));
        penBorder2 = CreatePen(PS_SOLID, 2, RGB(44, 137, 66));
        break;

    case WM_LBUTTONDOWN:
        xc = GET_X_LPARAM(lParam); yc = GET_Y_LPARAM(lParam);
        if (aS1[h]->isPointInside(cPoint(xc, yc)))
        {
            hdc = GetDC(hWnd);
            SelectObject(hdc, hPenDot);
            SetROP2(hdc, R2_NOTXORPEN);
            aS1[h]->draw(hdc);
            SetCursor(hCursorMove);
            SetCapture(hWnd);
        }
        if (aS2[h2]->isPointInside(cPoint(xc, yc)))
        {
            hdc = GetDC(hWnd);
            SelectObject(hdc, hPenDot);
            SetROP2(hdc, R2_NOTXORPEN);
            aS2[h2]->draw(hdc);
            SetCursor(hCursorMove);
            SetCapture(hWnd);
        }
        break;

    case WM_MOUSEMOVE:
        if (GetCapture() == hWnd)
        {
            px = xc; py = yc;
            xc = GET_X_LPARAM(lParam); yc = GET_Y_LPARAM(lParam);
            dx = xc - px; dy = yc - py;
            if (pS->isPointInside(cPoint(px, py)))
            {
                hdc = GetDC(hWnd);
                SelectObject(hdc, hPenDot);
                SetROP2(hdc, R2_NOTXORPEN);
                aS1[h]->draw(hdc);
                aS1[h]->move(dx, dy);
                aS1[h]->draw(hdc);
            }
            if (pS2->isPointInside(cPoint(px, py)))
            {
                hdc = GetDC(hWnd);
                SelectObject(hdc, hPenDot);
                SetROP2(hdc, R2_NOTXORPEN);
                aS2[h2]->draw(hdc);
                aS2[h2]->move(dx, dy);
                aS2[h2]->draw(hdc);
            }
        }
        break;

    case WM_LBUTTONUP:
        if (GetCapture() == hWnd)
        {
            ReleaseCapture();
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_COMMAND:
    {
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_CHAR:
        switch (TCHAR(wParam))
        {
        case '\t':
            if (GetAsyncKeyState(0x43))
            {
                if (++h2 == n2) h2 = 0;
                pS2 = aS2[h2];
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            else
            {
                if (++h == n) h = 0;
                pS = aS1[h];
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }

        case '+':
            if (GetAsyncKeyState(0x43))
            {
                pS2->scale(1.2);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            else
            {
                pS->scale(1.2);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }

        case '-':
            if (GetAsyncKeyState(0x43))
            {
                pS2->scale(1 / 1.2);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            else
            {
                pS->scale(1 / 1.2);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
        }
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case 0x4C:
            if (GetAsyncKeyState(0x43))
            {
                pS2->rotate(-90);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            else
            {
                pS->rotate(-90);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }

        case 0x52:
            if (GetAsyncKeyState(0x43))
            {
                pS2->rotate(90);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            else
            {
                pS->rotate(90);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }

        case VK_LEFT:
            if (GetAsyncKeyState(0x43))
            {
                pS2->move(-10, 0);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            else
            {
                pS->move(-10, 0);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }

        case VK_RIGHT:
            if (GetAsyncKeyState(0x43))
            {
                pS2->move(10, 0);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            else
            {
                pS->move(10, 0);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }

        case VK_UP:
            if (GetAsyncKeyState(0x43))
            {
                pS2->move(0, -10);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            else {
                pS->move(0, -10);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }

        case VK_DOWN:
            if (GetAsyncKeyState(0x43))
            {
                pS2->move(0, 10);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
            else {
                pS->move(0, 10);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
        }

    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        GetClientRect(hWnd, &rt);
        DrawText(hdc, szInfor, lstrlen(szInfor), &rt, DT_LEFT | DT_TOP);
        DrawText(hdc, szInfor1, lstrlen(szInfor1), &rt, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
        
        //draw object 1
        SelectObject(hdc, hbr1);
        SelectObject(hdc, penBorder1);
        pS->draw(hdc);
        
        //draw object 2
        SelectObject(hdc, hbr2);
        SelectObject(hdc, penBorder2);
        pS2->draw(hdc);
        
        //intersect
        SelectObject(hdc, penBorder);
        if (pS2->isIntersect(pS, hdc))
        {
            swprintf_s(szItsMessage, L"Intersect!");
        }
        else
            swprintf_s(szItsMessage, L"Not intersect!");
        DrawText(hdc, szItsMessage, lstrlen(szItsMessage), &rt, DT_CENTER | DT_TOP);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_DESTROY:
        delete[] pS;
        delete[] pS2;
        DeleteObject(hbr1);
        DeleteObject(hbr2);
        DeleteObject(hPenDot);
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

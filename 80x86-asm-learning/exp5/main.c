#include <Windows.h>
#include <tchar.h>

#define EVENT_ID_EXIT 1
#define EVENT_ID_AVER 2
#define EVENT_ID_LIST 3
#define EVENT_ID_ABOUT 4

#define EDIT_AREA_EDGE 10

HWND hShowWin = NULL;
void calc_average();
void show_list();

LRESULT WINAPI mainWinProc(
   HWND    hWnd,
   UINT    uMsg,
   WPARAM  wParam,
   LPARAM  lParam
) {
    switch(uMsg) {
    case WM_CREATE:
        DrawMenuBar(hWnd);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hDc = BeginPaint(hWnd, &ps);
        FillRect(hDc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_SIZE:
        SetWindowPos(hShowWin, NULL, EDIT_AREA_EDGE, EDIT_AREA_EDGE, LOWORD(lParam)-2*EDIT_AREA_EDGE, HIWORD(lParam)-2*EDIT_AREA_EDGE, (UINT)NULL);
        break;
    case WM_COMMAND:
        switch(LOWORD(wParam)) {
        case EVENT_ID_EXIT:
            PostMessage(hWnd, WM_CLOSE, (LPARAM)NULL, (WPARAM)NULL);
            break;
        case EVENT_ID_AVER:
            calc_average();
            break;
        case EVENT_ID_LIST:
            show_list();
            break;
        case EVENT_ID_ABOUT:
            MessageBox(hWnd, TEXT("By Bensong Liu <root@recolic.net>, Licensed under Modified Mozilla Public License 2.0."), TEXT("Hi"), MB_OK);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

INT CALLBACK _tWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR     lpCmdLine,
    int       nCmdShow
) {
    TCHAR clsName[] = TEXT("rwin-classc-01");

    WNDCLASS wcMainWin = {0};
    wcMainWin.lpfnWndProc = mainWinProc;
    wcMainWin.hInstance = hInstance;
    wcMainWin.lpszClassName = clsName;
    RegisterClass(&wcMainWin);

    HMENU hmBarMain = CreateMenu();
    HMENU hmFile = CreatePopupMenu();
    HMENU hmAction = CreatePopupMenu();
    HMENU hmHelp = CreatePopupMenu();

    AppendMenu(hmBarMain, MF_POPUP, (UINT_PTR)hmFile, TEXT("File"));
    AppendMenu(hmBarMain, MF_POPUP, (UINT_PTR)hmAction, TEXT("Action"));
    AppendMenu(hmBarMain, MF_POPUP, (UINT_PTR)hmHelp, TEXT("Help"));

    AppendMenu(hmFile, MF_STRING, EVENT_ID_EXIT, TEXT("Exit"));
    AppendMenu(hmAction, MF_STRING, EVENT_ID_AVER, TEXT("Average"));
    AppendMenu(hmAction, MF_STRING, EVENT_ID_LIST, TEXT("List"));
    AppendMenu(hmHelp, MF_STRING, EVENT_ID_ABOUT, TEXT("About"));

    HWND hMainWin = CreateWindow(clsName, TEXT("Recolic's Homework"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, hmBarMain, hInstance, NULL);
    hShowWin = CreateWindow("EDIT", TEXT("Ready."), WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 
        10,10,1000,1000, hMainWin, NULL, hInstance, NULL);

    DrawMenuBar(hMainWin);
    
    ShowWindow(hMainWin, SW_SHOW);
    ShowWindow(hShowWin, SW_SHOW);
    UpdateWindow(hMainWin);
    UpdateWindow(hShowWin);

    MSG msg;  
    while (GetMessage(&msg, NULL, 0, 0))  
    {  
        TranslateMessage(&msg);  
        DispatchMessage(&msg);  
    }
    
    return 0;
}


/* ProjectorScaler Portable - native Win64 GDI implementation, no external runtime.
 * (c) 2026. Source supplied with the portable executable.
 * Build: see build-native.sh. Windows 10 1703+/Windows 11 x64.
 * Extender is used for the actual projection; Duplicar may be converted with confirmation.
 */
#define WIN32_LEAN_AND_MEAN 1

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef long LONG;
typedef int BOOL;
typedef unsigned short WCHAR;
typedef __SIZE_TYPE__ SIZE_T;
typedef long long LONG_PTR;
typedef unsigned long long ULONG_PTR;
typedef ULONG_PTR WPARAM;
typedef LONG_PTR LPARAM;
typedef LONG_PTR LRESULT;
typedef void* HANDLE;
typedef HANDLE HWND;
typedef HANDLE HINSTANCE;
typedef HANDLE HDC;
typedef HANDLE HGDIOBJ;
typedef HANDLE HBITMAP;
typedef HANDLE HBRUSH;
typedef HANDLE HFONT;
typedef HANDLE HICON;
typedef HANDLE HCURSOR;
typedef HANDLE HMONITOR;

typedef struct { LONG x, y; } POINT;
typedef struct { LONG left, top, right, bottom; } RECT;
typedef struct { HWND hwnd; UINT message; WPARAM wParam; LPARAM lParam; DWORD time; POINT pt; DWORD lPrivate; } MSG;
typedef struct { HDC hdc; BOOL fErase; RECT rcPaint; BOOL fRestore; BOOL fIncUpdate; BYTE rgbReserved[32]; } PAINTSTRUCT;
typedef struct { DWORD cbSize; RECT rcMonitor; RECT rcWork; DWORD dwFlags; WCHAR szDevice[32]; } MONITORINFOEXW;
typedef struct { DWORD cbSize; DWORD flags; HCURSOR hCursor; POINT ptScreenPos; } CURSORINFO;
typedef struct { BOOL fIcon; DWORD xHotspot; DWORD yHotspot; HBITMAP hbmMask; HBITMAP hbmColor; } ICONINFO;
typedef LRESULT (__stdcall *WNDPROC)(HWND,UINT,WPARAM,LPARAM);
typedef struct { UINT cbSize; UINT style; WNDPROC lpfnWndProc; int cbClsExtra; int cbWndExtra; HINSTANCE hInstance; HICON hIcon; HCURSOR hCursor; HBRUSH hbrBackground; const WCHAR* lpszMenuName; const WCHAR* lpszClassName; HICON hIconSm; } WNDCLASSEXW;
typedef BOOL (__stdcall *MONITORENUMPROC)(HMONITOR,HDC,RECT*,LPARAM);

#define IN(import) __declspec(dllimport) import
#define API(ret,name,args) IN(ret __stdcall name args)
/* kernel32 */
API(void,ExitProcess,(UINT));
API(HINSTANCE,GetModuleHandleW,(const WCHAR*));
API(DWORD,GetModuleFileNameW,(HINSTANCE,WCHAR*,DWORD));
API(UINT,GetPrivateProfileIntW,(const WCHAR*,const WCHAR*,int,const WCHAR*));
API(DWORD,GetPrivateProfileStringW,(const WCHAR*,const WCHAR*,const WCHAR*,WCHAR*,DWORD,const WCHAR*));
API(DWORD,GetPrivateProfileSectionNamesW,(WCHAR*,DWORD,const WCHAR*));
API(BOOL,WritePrivateProfileStringW,(const WCHAR*,const WCHAR*,const WCHAR*,const WCHAR*));
API(DWORD,GetTickCount,(void));
API(WORD,GetUserDefaultUILanguage,(void));
/* user32 */
API(int,MessageBoxW,(HWND,const WCHAR*,const WCHAR*,UINT));
API(unsigned short,RegisterClassExW,(const WNDCLASSEXW*));
API(HWND,CreateWindowExW,(DWORD,const WCHAR*,const WCHAR*,DWORD,int,int,int,int,HWND,HANDLE,HINSTANCE,void*));
API(LRESULT,DefWindowProcW,(HWND,UINT,WPARAM,LPARAM));
API(BOOL,DestroyWindow,(HWND));
API(BOOL,ShowWindow,(HWND,int));
API(BOOL,UpdateWindow,(HWND));
API(BOOL,GetMessageW,(MSG*,HWND,UINT,UINT));
API(BOOL,TranslateMessage,(const MSG*));
API(LRESULT,DispatchMessageW,(const MSG*));
API(void,PostQuitMessage,(int));
API(LRESULT,SendMessageW,(HWND,UINT,WPARAM,LPARAM));
API(BOOL,SetWindowTextW,(HWND,const WCHAR*));
API(int,GetWindowTextW,(HWND,WCHAR*,int));
API(BOOL,SetWindowPos,(HWND,HWND,int,int,int,int,UINT));
API(BOOL,EnableWindow,(HWND,BOOL));
API(BOOL,InvalidateRect,(HWND,const RECT*,BOOL));
API(BOOL,GetClientRect,(HWND,RECT*));
API(HDC,GetDC,(HWND));
API(int,ReleaseDC,(HWND,HDC));
API(HDC,BeginPaint,(HWND,PAINTSTRUCT*));
API(BOOL,EndPaint,(HWND,const PAINTSTRUCT*));
API(ULONG_PTR,SetTimer,(HWND,ULONG_PTR,UINT,void*));
API(BOOL,KillTimer,(HWND,ULONG_PTR));
API(BOOL,EnumDisplayMonitors,(HDC,const RECT*,MONITORENUMPROC,LPARAM));
API(BOOL,GetMonitorInfoW,(HMONITOR,MONITORINFOEXW*));
API(BOOL,GetCursorInfo,(CURSORINFO*));
API(BOOL,GetIconInfo,(HICON,ICONINFO*));
API(BOOL,DrawIconEx,(HDC,int,int,HICON,int,int,UINT,HBRUSH,UINT));
API(BOOL,SetProcessDpiAwarenessContext,(void*));
API(HMONITOR,MonitorFromWindow,(HWND,DWORD));
API(LONG,GetDisplayConfigBufferSizes,(UINT,UINT*,UINT*));
API(LONG,QueryDisplayConfig,(UINT,UINT*,void*,UINT*,void*,void*));
API(LONG,SetDisplayConfig,(UINT,void*,UINT,void*,UINT));
API(int,FillRect,(HDC,const RECT*,HBRUSH));
API(int,DrawTextW,(HDC,const WCHAR*,int,RECT*,UINT));
API(BOOL,RegisterHotKey,(HWND,int,UINT,UINT));
API(BOOL,UnregisterHotKey,(HWND,int));
API(HCURSOR,LoadCursorW,(HINSTANCE,const WCHAR*));
API(UINT,GetDpiForWindow,(HWND));
API(BOOL,GetWindowRect,(HWND,RECT*));
API(BOOL,IsDialogMessageW,(HWND,MSG*));
API(BOOL,DrawFocusRect,(HDC,const RECT*));
API(HANDLE,LoadImageW,(HINSTANCE,const WCHAR*,UINT,int,int,UINT));
API(int,GetSystemMetrics,(int));
API(HCURSOR,SetCursor,(HCURSOR));
API(HWND,SetCapture,(HWND));
API(BOOL,ReleaseCapture,(void));
API(BOOL,GetCursorPos,(POINT*));
typedef BOOL (__stdcall *WNDENUMPROC)(HWND,LPARAM);
API(BOOL,EnumWindows,(WNDENUMPROC,LPARAM));
API(BOOL,IsWindowVisible,(HWND));
API(int,GetWindowTextLengthW,(HWND));
API(HWND,GetWindow,(HWND,UINT));
API(LONG_PTR,GetWindowLongPtrW,(HWND,int));
API(BOOL,IsWindow,(HWND));
API(BOOL,IsIconic,(HWND));
API(BOOL,PrintWindow,(HWND,HDC,UINT));
API(int,SetScrollInfo,(HWND,int,const void*,BOOL));
API(HWND,SetFocus,(HWND));
API(int,GetClassNameW,(HWND,WCHAR*,int));
API(DWORD,GetWindowThreadProcessId,(HWND,DWORD*));
API(BOOL,IsHungAppWindow,(HWND));
API(HANDLE,OpenProcess,(DWORD,BOOL,DWORD));
API(BOOL,QueryFullProcessImageNameW,(HANDLE,DWORD,WCHAR*,DWORD*));
API(BOOL,CloseHandle,(HANDLE));
API(void,Sleep,(DWORD));
API(LONG,CoInitializeEx,(void*,DWORD));
API(LONG,CoCreateInstance,(const void*,void*,DWORD,const void*,void**));
API(void,SysFreeString,(WCHAR*));
API(BOOL,SetLayeredWindowAttributes,(HWND,DWORD,BYTE,DWORD));
API(LONG_PTR,SetWindowLongPtrW,(HWND,int,LONG_PTR));
API(BOOL,MagInitialize,(void));
API(BOOL,MagUninitialize,(void));
API(BOOL,MagSetWindowSource,(HWND,RECT));
API(BOOL,MagSetWindowTransform,(HWND,float*));
IN(HANDLE __stdcall ShellExecuteW(HWND,const WCHAR*,const WCHAR*,const WCHAR*,const WCHAR*,int));
API(BOOL,ClientToScreen,(HWND,POINT*));
/* dwmapi */
API(LONG,DwmGetWindowAttribute,(HWND,DWORD,void*,DWORD));
/* gdi32 */
API(HDC,CreateCompatibleDC,(HDC));
API(BOOL,DeleteDC,(HDC));
API(HBITMAP,CreateCompatibleBitmap,(HDC,int,int));
API(HGDIOBJ,SelectObject,(HDC,HGDIOBJ));
API(BOOL,DeleteObject,(HGDIOBJ));
API(BOOL,BitBlt,(HDC,int,int,int,int,HDC,int,int,DWORD));
API(BOOL,StretchBlt,(HDC,int,int,int,int,HDC,int,int,int,int,DWORD));
API(BOOL,PatBlt,(HDC,int,int,int,int,DWORD));
API(int,SetStretchBltMode,(HDC,int));
API(HGDIOBJ,GetStockObject,(int));
API(HBRUSH,CreateSolidBrush,(DWORD));
API(HFONT,CreateFontW,(int,int,int,int,int,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,const WCHAR*));
API(DWORD,SetTextColor,(HDC,DWORD));
API(int,SetBkMode,(HDC,int));
API(BOOL,RoundRect,(HDC,int,int,int,int,int,int));
API(BOOL,Rectangle,(HDC,int,int,int,int));
API(BOOL,SetBrushOrgEx,(HDC,int,int,POINT*));
/* Start with Windows and updates from GitHub. Prototypes and constants as in the mingw-w64
 * headers (winbase.h, fileapi.h, winuser.h, winreg.h, winhttp.h). */
typedef DWORD (__stdcall *THREADPROC)(void*);
API(HANDLE,CreateThread,(void*,SIZE_T,THREADPROC,void*,DWORD,DWORD*));
API(HANDLE,CreateFileW,(const WCHAR*,DWORD,DWORD,void*,DWORD,DWORD,HANDLE));
API(BOOL,WriteFile,(HANDLE,const void*,DWORD,DWORD*,void*));
API(BOOL,MoveFileExW,(const WCHAR*,const WCHAR*,DWORD));
API(BOOL,DeleteFileW,(const WCHAR*));
API(WCHAR*,GetCommandLineW,(void));
typedef struct {DWORD cb;WCHAR* lpReserved;WCHAR* lpDesktop;WCHAR* lpTitle;DWORD dwX,dwY,dwXSize,dwYSize,dwXCountChars,dwYCountChars,dwFillAttribute,dwFlags;
                WORD wShowWindow,cbReserved2;BYTE* lpReserved2;HANDLE hStdInput,hStdOutput,hStdError;} STARTUPINFOW_;
typedef struct {HANDLE hProcess,hThread;DWORD dwProcessId,dwThreadId;} PROCESS_INFORMATION_;
API(BOOL,CreateProcessW,(const WCHAR*,WCHAR*,void*,void*,BOOL,DWORD,void*,const WCHAR*,STARTUPINFOW_*,PROCESS_INFORMATION_*));
typedef HANDLE HMENU;
API(BOOL,PostMessageW,(HWND,UINT,WPARAM,LPARAM));
API(HMENU,CreatePopupMenu,(void));
API(BOOL,AppendMenuW,(HMENU,UINT,ULONG_PTR,const WCHAR*));
API(BOOL,TrackPopupMenu,(HMENU,UINT,int,int,int,HWND,const RECT*));
API(BOOL,DestroyMenu,(HMENU));
typedef HANDLE HKEY;
API(LONG,RegOpenKeyExW,(HKEY,const WCHAR*,DWORD,DWORD,HKEY*));
API(LONG,RegCreateKeyExW,(HKEY,const WCHAR*,DWORD,WCHAR*,DWORD,DWORD,void*,HKEY*,DWORD*));
API(LONG,RegQueryValueExW,(HKEY,const WCHAR*,DWORD*,DWORD*,BYTE*,DWORD*));
API(LONG,RegSetValueExW,(HKEY,const WCHAR*,DWORD,DWORD,const BYTE*,DWORD));
API(LONG,RegDeleteValueW,(HKEY,const WCHAR*));
API(LONG,RegCloseKey,(HKEY));
typedef void* HINTERNET;
API(HINTERNET,WinHttpOpen,(const WCHAR*,DWORD,const WCHAR*,const WCHAR*,DWORD));
API(HINTERNET,WinHttpConnect,(HINTERNET,const WCHAR*,WORD,DWORD));
API(HINTERNET,WinHttpOpenRequest,(HINTERNET,const WCHAR*,const WCHAR*,const WCHAR*,const WCHAR*,const WCHAR**,DWORD));
API(BOOL,WinHttpSendRequest,(HINTERNET,const WCHAR*,DWORD,void*,DWORD,DWORD,ULONG_PTR));
API(BOOL,WinHttpReceiveResponse,(HINTERNET,void*));
API(BOOL,WinHttpQueryHeaders,(HINTERNET,DWORD,const WCHAR*,void*,DWORD*,DWORD*));
API(BOOL,WinHttpReadData,(HINTERNET,void*,DWORD,DWORD*));
API(BOOL,WinHttpSetTimeouts,(HINTERNET,int,int,int,int));
API(BOOL,WinHttpCloseHandle,(HINTERNET));
#define HKEY_CURRENT_USER ((HKEY)(ULONG_PTR)((LONG)0x80000001)) /* sign-extended on x64 */
#define KEY_QUERY_VALUE 0x0001u
#define KEY_SET_VALUE 0x0002u
#define REG_SZ 1u
#define GENERIC_WRITE 0x40000000u
#define CREATE_ALWAYS 2u
#define FILE_ATTRIBUTE_NORMAL 0x80u
#define INVALID_HANDLE ((HANDLE)(LONG_PTR)-1)
#define MOVEFILE_REPLACE_EXISTING 0x1u
#define MOVEFILE_WRITE_THROUGH 0x8u
#define MF_STRING 0x0u
#define MF_GRAYED 0x1u
#define MF_CHECKED 0x8u
#define MF_SEPARATOR 0x800u
#define TPM_RIGHTALIGN 0x8u
#define TPM_RETURNCMD 0x100u
#define WM_APP 0x8000u
#define WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY 4u
#define WINHTTP_FLAG_SECURE 0x00800000u
#define WINHTTP_QUERY_STATUS_CODE 19u
#define WINHTTP_QUERY_FLAG_NUMBER 0x20000000u

#define WS_OVERLAPPEDWINDOW 0x00CF0000u
#define WS_VISIBLE 0x10000000u
#define WS_CHILD 0x40000000u
#define WS_POPUP 0x80000000u
#define WS_TABSTOP 0x00010000u
#define WS_BORDER 0x00800000u
#define WS_VSCROLL 0x00200000u
#define WS_EX_TOPMOST 0x00000008u
#define WS_EX_TOOLWINDOW 0x00000080u
#define WS_EX_NOACTIVATE 0x08000000u
#define WS_EX_CLIENTEDGE 0x00000200u
#define SS_LEFT 0x00000000u
#define BS_PUSHBUTTON 0x00000000u
#define BS_AUTOCHECKBOX 0x00000003u
#define BS_OWNERDRAW 0x0000000Bu
#define WM_DRAWITEM 0x002Bu
#define WM_HOTKEY 0x0312u
#define MOD_ALT 1u
#define MOD_CONTROL 2u
#define MOD_SHIFT 4u
#define ID_EMERGENCY 345
#define WM_DPICHANGED 0x02E0u
#define SWP_NOZORDER 0x0004u
#define ODS_FOCUS 0x0010u
#define SW_HIDE 0
#define WM_SETCURSOR 0x0020u
#define WM_MOUSEMOVE 0x0200u
#define WM_LBUTTONDOWN 0x0201u
#define WM_LBUTTONUP 0x0202u
#define WM_CAPTURECHANGED 0x0215u
#define MK_SHIFT 0x0004u
#define HTCLIENT 1
#define IMAGE_ICON 1u
#define SM_CXICON 11
#define SM_CYICON 12
#define SM_CXSMICON 49
#define SM_CYSMICON 50
#define IDI_APP 1
#define CURSOR_ID(n) ((const WCHAR*)(ULONG_PTR)(n))
#define GW_OWNER 4u
#define GWL_EXSTYLE (-20)
#define PW_CLIENTONLY 1u
#define PW_RENDERFULLCONTENT 2u
#define WM_SIZE 0x0005u
#define WM_VSCROLL 0x0115u
#define WM_MOUSEWHEEL 0x020Au
#define SB_VERT 1
#define SB_LINEUP 0
#define SB_LINEDOWN 1
#define SB_PAGEUP 2
#define SB_PAGEDOWN 3
#define SB_THUMBPOSITION 4
#define SB_THUMBTRACK 5
#define SIF_RANGE 1u
#define SIF_PAGE 2u
#define SIF_POS 4u
#define DT_NOPREFIX 0x0800u
#define DT_CALCRECT 0x0400u
#define DT_RIGHT 0x0002u
#define DT_END_ELLIPSIS 0x8000u
typedef struct {UINT cbSize,fMask;int nMin,nMax;UINT nPage;int nPos,nTrackPos;} SCROLLINFO;
#define MAXTILES 64
#define TILE_SCREEN 0
#define TILE_WINDOW 1
#define TILE_TAB 2
#define IDC_HAND ((const WCHAR*)(ULONG_PTR)32649)
#define DWMWA_CLOAKED 14u
#define CBN_DROPDOWN 7
#define CB_SETDROPPEDWIDTH 0x0160u
#define MAXWIN 48
#define WM_CTLCOLORSTATIC 0x0138u
#define WM_CTLCOLOREDIT 0x0133u
#define ODS_DISABLED 0x0004u
#define ODS_SELECTED 0x0001u
#define DT_CENTER 0x0001u
#define DT_VCENTER 0x0004u
#define DT_SINGLELINE 0x0020u
#define DT_WORDBREAK 0x0010u
#define TRANSPARENT 1
#define MONITORINFOF_PRIMARY 1u
#define MONITOR_DEFAULTTONEAREST 2u
#define IDYES 6
#define MB_YESNO 4u
#define MB_ICONQUESTION 0x20u
#define MB_ICONWARNING 0x30u
#define SDC_APPLY 0x80u
#define SDC_VALIDATE 0x40u
#define SDC_TOPOLOGY_CLONE 0x2u
#define SDC_TOPOLOGY_EXTEND 0x4u
#define QDC_ONLY_ACTIVE_PATHS 0x2u
#define CBS_DROPDOWNLIST 0x0003u
#define ES_NUMBER 0x00002000u
#define WM_CREATE 0x0001u
#define WM_DESTROY 0x0002u
#define WM_PAINT 0x000Fu
#define WM_ERASEBKGND 0x0014u
#define WM_COMMAND 0x0111u
#define WM_TIMER 0x0113u
#define WM_DISPLAYCHANGE 0x007Eu
#define WM_SETFONT 0x0030u
#define BM_GETCHECK 0x00F0u
#define BM_SETCHECK 0x00F1u
#define BST_CHECKED 1
#define CB_ADDSTRING 0x0143u
#define CB_GETCURSEL 0x0147u
#define CB_RESETCONTENT 0x014Bu
#define CB_SETCURSEL 0x014Eu
#define CBN_SELCHANGE 1
#define EN_CHANGE 0x0300
#define SW_SHOW 5
#define SWP_NOACTIVATE 0x0010u
#define SWP_SHOWWINDOW 0x0040u
#define SRCCOPY 0x00CC0020u
#define CAPTUREBLT 0x40000000u
#define BLACKNESS 0x00000042u
#define HALFTONE 4
#define DI_NORMAL 0x0003u
#define IDC_ARROW ((const WCHAR*)(ULONG_PTR)32512)
#define HWND_TOPMOST ((HWND)(LONG_PTR)-1)
#define DEFAULT_GUI_FONT 17
#define W(x) ((const WCHAR*)L##x)
/* Every user-facing text is written in both languages at the place it is used. */
#define L(es,en) (g_lang?W(en):W(es))
#define SIZEOF(x) (sizeof(x)/sizeof((x)[0]))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

#define ID_SOURCE 101
#define ID_TARGET 102
#define ID_ZOOM 103
#define ID_X 104
#define ID_Y 105
#define ID_ASPECT 106
#define ID_CW 107
#define ID_CH 108
#define ID_FIT 109
#define ID_CURSOR 110
#define ID_APPLY 111
#define ID_START 112
#define ID_BLACK 113
#define ID_CINEMA 114
#define ID_CONF 115
#define ID_SMALL 116
#define ID_RELOAD 117
#define ID_SAVE 118
#define ID_STATUS 119
#define ID_PROFILE 120
#define ID_SAVE_PROFILE 121
#define ID_LOAD_PROFILE 122
#define ID_IDENTIFY 123
#define ID_RESTORE_CLONE 124
#define ID_MODE 125
#define ID_TOPOLOGY 126
#define ID_EDITFRAME 127
#define ID_UI_BASIC 128
#define ID_UI_ADV 129
#define ID_LANG_ES 130
#define ID_LANG_EN 131
#define ID_CENTER 132
#define ID_FILL 133
#define ID_PREVIEW 134
#define ID_SIZE 135
#define ID_TAB0 136 /* 136-138: Pantallas, Ventanas, Pestañas */
#define ID_TILES 139
#define ID_SRCHINT 140
#define ID_THUMBS 235
#define ID_TABGUARD 236
#define ID_PREVIEW_TICK 234
#define ID_HIDEIDS 230
#define ID_BEGIN_AFTER_EXTEND 231
#define ID_DISPLAY_SETTLE 232
#define ID_STARTUP_CHECK 233
#define ID_MENU 141          /* header button with the options menu */
#define ID_M_AUTOSTART 150   /* its items */
#define ID_M_CHECKUPD 151
#define ID_M_CHECKNOW 152
#define ID_UPDATE_CHECK 237  /* timer: the check at startup */
#define ID_UPDATE_WAIT 238   /* timer: an update waits for the projection to stop */
#define WM_UPDATE_CHECKED (WM_APP+1) /* worker thread -> window: wParam = UPD_* */
#define WM_UPDATE_FETCHED (WM_APP+2) /* worker thread -> window: wParam = DL_* */
#define APP_VERSION L"2.3"   /* release tags are v<APP_VERSION>: the release workflow checks it */
#define REPO_PATH L"/repos/cmmendel/ProjectorScaler/releases/latest"
#define RELEASES_PAGE L"https://github.com/cmmendel/ProjectorScaler/releases/latest"
#define ASSET_NAME "ProjectorScalerPortable.exe"
#ifndef UPD_TEST_PORT        /* -DUPD_TEST_PORT=n: a test build that asks plain HTTP on 127.0.0.1:n instead */
#define API_HOST L"api.github.com"
#define DL_HOST L"github.com"
#define UPD_PORT 443
#define UPD_FLAGS WINHTTP_FLAG_SECURE
#else
#define API_HOST L"127.0.0.1"
#define DL_HOST L"127.0.0.1"
#define UPD_PORT UPD_TEST_PORT
#define UPD_FLAGS 0u
#endif
#define RGB3(r,g,b) ((DWORD)((r)|((g)<<8)|((b)<<16)))

/* Layout is written at 96 DPI and scaled per monitor (per-monitor-v2 awareness). */
#define BASE_CW 777
#define BASIC_CH 570
#define ADV_CH 939
#define BASE_CH (g_uiMode?ADV_CH:BASIC_CH)
#define MAXCTL 96
#define FONT_UI 0
#define FONT_TITLE 1
#define FONT_TINY 2
#define FRAME_MIN_MS 50
#define MAG_FRAME_MS 15 /* the magnifier path: about the screen's refresh rate */
#define WS_EX_LAYERED 0x00080000u
#define LWA_ALPHA 2u
#define SW_SHOWNA 8
#define GWL_STYLE (-16)
#define MS_SHOWMAGNIFIEDCURSOR 1u
#define FRAME_MAX_MS 250
#define ASPECT_FREE 6     /* frame set by dragging on the projector */
#define FREE_UNIT 10000   /* free frame stored in 1/10000 of the target screen */
#define HIT_NONE 0
#define HIT_MOVE 1
#define HIT_L 2
#define HIT_R 3
#define HIT_T 4
#define HIT_B 5
#define HIT_TL 6
#define HIT_TR 7
#define HIT_BL 8
#define HIT_BR 9

static HINSTANCE g_inst;
static HWND g_main, g_output;
static HWND g_source,g_target,g_zoom,g_x,g_y,g_aspect,g_customW,g_customH,g_fit,g_cursor;
static HWND g_apply,g_start,g_black,g_status,g_profile,g_restoreBox,g_modeLabel;
static HWND g_ids[16];
static HFONT g_fontUi,g_fontHeader,g_fontTitle,g_fontTiny,g_fontOverlay,g_fontOverlaySmall;
static HBRUSH g_brWhite,g_brWindow;
static int g_wasClone=0,g_switching=0,g_pending=0,g_restoreClone=1;
static MONITORINFOEXW g_monitors[16];
static HMONITOR g_handles[16];
static BYTE g_pathBuf[2048],g_modeBuf[4096];
static int g_monitorCount=0, g_sourceIndex=0, g_targetIndex=1;
static int g_zoomValue=60, g_xValue=50, g_yValue=50, g_aspectIndex=0, g_fitIndex=0, g_cw=3,g_ch=2,g_showCursor=1;
static int g_isBlack=0, g_isRunning=0;
static WCHAR g_ini[1024];
static int g_iniError=0;
static HDC g_capDC=0,g_bufDC=0;
static HBITMAP g_capBmp=0,g_bufBmp=0;
static HGDIOBJ g_capOld=0,g_bufOld=0;
static int g_sw=0,g_sh=0,g_tw=0,g_th=0;
static int g_frameMs=FRAME_MIN_MS;
static int g_hotkey=0; /* 0 = none, 1 = Ctrl+Alt+P, 2 = Ctrl+Alt+Shift+P */
typedef struct { HWND h; int x,y,w,hh,font; } LAYOUT;
static LAYOUT g_layout[MAXCTL];
static int g_layoutCount=0;
static int g_scale=1000; /* per mille of 96 DPI */
static UINT g_dpi=96;
static HWND g_topoBtn,g_editBtn;
static int g_editFrame=0,g_drag=HIT_NONE,g_dragRect[4],g_tOrgX=0,g_tOrgY=0;
static POINT g_dragFrom;
static int g_free[4]={1500,1500,8500,8500}; /* left, top, right, bottom */
/* Source can be a whole monitor (g_srcWindow == 0) or one window, listed after the monitors. */
static HWND g_srcWindow=0,g_winList[MAXWIN];
static int g_winCount=0,g_srcLost=0;
static int g_lang=0;      /* 0 = Spanish, 1 = English */
static int g_uiMode=0;    /* 0 = basic, 1 = advanced */
static int g_runBasic=0;  /* the running projection was started from the basic mode */
static int g_basicFree[4]={1000,1000,9000,9000}; /* basic frame, FREE_UNIT of the projector */
static HWND g_preview,g_sizeLbl,g_hintLbl;
static int g_pDrag=0,g_pStart[4];
static POINT g_pFrom;
static WCHAR g_statusText[400];
/* One tile of the advanced source picker. A tab tile points at its browser window; crop is
 * the page inside that window's client area. */
typedef struct {int kind,mon,thumbDone,thumbW,thumbH;HWND hwnd;HBITMAP thumb;RECT crop;WCHAR title[128],sub[64];} TILE;
static TILE g_tiles[MAXTILES];
static int g_tileCount=0,g_thumbNext=0,g_tileScroll=0,g_tileTab=0,g_tabCount=-1;
static int g_srcKind=TILE_SCREEN; /* what g_srcWindow is when it is set: a window or a browser tab */
static HWND g_tilesWnd,g_tabBtn[3],g_srcHint;
static WCHAR g_srcTabTitle[128];
static RECT g_tabCrop;      /* the chosen tab's page, in its browser window's client coordinates */
static int g_tabFrozen=0;   /* the chosen tab is not confirmed on show: keep the last picture */
static WCHAR g_tabExpect[256]; /* the browser's title when the tab was last confirmed */
static HDC g_tabDC;static HBITMAP g_tabBmp;static HGDIOBJ g_tabOld;static int g_tabBw,g_tabBh;
static void* g_tabSel; /* the chosen tab's SelectionItem pattern (UI Automation) */
static void tabRelease(void);
static int g_pickerOpen=0;     /* advanced: 01 opened tall, 02-04 folded to their titles */
static int g_advFold0=0,g_advFold1=0; /* g_layout range of the controls of 02-04 */
static HWND g_advSec[3];        /* the titles of 02, 03 and 04 */
/* A whole screen is mirrored by the Windows magnifier control, which DWM draws on the GPU at
 * about the refresh rate. GDI capture stays for windows, tabs, black and frame adjusting. */
static HWND g_mag=0;
static int g_magInit=0;  /* 0 not tried, 1 ready, -1 unavailable */
static int g_magShown=0,g_magCursor=-1;
static RECT g_magDst;
static RECT g_linkRect; /* "Colegio Mayor Mendel" in the footer, a link to cmmendel.com */
static int g_overLink=0;
static const WCHAR* g_tabError=0; /* why the Pestañas tab is empty, when it is not just "no tabs" */
static void fillTiles(void);
static void tilesClear(void);

/* No CRT: the compiler may emit calls to these for zeroing and struct copies. */
void* memset(void* ptr,int c,SIZE_T len){BYTE* p=(BYTE*)ptr;for(SIZE_T i=0;i<len;i++)p[i]=(BYTE)c;return ptr;}
void* memcpy(void* dst,const void* src,SIZE_T len){BYTE* d=(BYTE*)dst;const BYTE* s=(const BYTE*)src;for(SIZE_T i=0;i<len;i++)d[i]=s[i];return dst;}
static int S(int v){return (v*g_scale+(v>=0?500:-500))/1000;}
static void appendw(WCHAR* out,const WCHAR* text,int cap){int j=0,i=0;while(j<cap-1&&out[j])j++;while(text&&text[i]&&j<cap-1)out[j++]=text[i++];out[j]=0;}
static void appendi(WCHAR* out,int n,int cap){WCHAR t[32];int k=0,j=0; if(n<0)n=0; do{t[k++]=(WCHAR)('0'+n%10);n/=10;}while(n&&k<31); while(j<cap-1&&out[j])j++; while(k&&j<cap-1)out[j++]=t[--k];out[j]=0;}
static void copyw(WCHAR* dest,const WCHAR* src,int max){ int i=0; if(!src){dest[0]=0;return;} while(i<max-1&&src[i]){dest[i]=src[i];i++;} dest[i]=0; }
static int eqw(const WCHAR* a,const WCHAR* b){int i=0;while(a[i]&&b[i]&&a[i]==b[i])i++; return a[i]==b[i];}
static void intw(WCHAR* out,int v){WCHAR t[24];int n=0,i=0;if(v<0){*out++='-';v=-v;} do{t[n++]=(WCHAR)('0'+v%10);v/=10;}while(v&&n<23);while(n)out[i++]=t[--n];out[i]=0;}
static int parseint(const WCHAR* s,int fallback){int v=0,i=0,any=0;while(s[i]>= '0'&&s[i]<='9'&&i<7){v=v*10+s[i]-'0';i++;any=1;}return any?v:fallback;}
static int getint(HWND h,int fallback,int mn,int mx){WCHAR b[32];GetWindowTextW(h,b,32);return MAX(mn,MIN(mx,parseint(b,fallback)));}
static void setint(HWND h,int n){WCHAR b[24];intw(b,n);SetWindowTextW(h,b);}
/* The last status line survives a rebuild of the panel (mode or language change). */
static void status(const WCHAR* s){copyw(g_statusText,s,400);if(g_status)SetWindowTextW(g_status,s);}
static const WCHAR* startLabel(int running){
    if(g_uiMode==0)return running?L("Detener","Stop"):L("Proyectar","Project");
    return running?L("Detener proyección","Stop projection"):L("Iniciar proyección","Start projection");
}
static int comboindex(HWND h){LRESULT v=SendMessageW(h,CB_GETCURSEL,0,0);return v<0?0:(int)v;}
static void comboselect(HWND h,int v){SendMessageW(h,CB_SETCURSEL,(WPARAM)v,0);}
static HFONT fontOf(int kind){HFONT f=kind==FONT_TITLE?g_fontTitle:kind==FONT_TINY?g_fontTiny:g_fontUi;return f?f:(HFONT)GetStockObject(DEFAULT_GUI_FONT);}
static HWND ctrl(const WCHAR* cls,const WCHAR* text,DWORD style,int x,int y,int w,int h,int id){
    HWND p=CreateWindowExW(0,cls,text,style|WS_CHILD|WS_VISIBLE,S(x),S(y),S(w),S(h),g_main,(HANDLE)(ULONG_PTR)id,g_inst,0);
    if(p){
        SendMessageW(p,WM_SETFONT,(WPARAM)fontOf(FONT_UI),1);
        if(g_layoutCount<MAXCTL){LAYOUT* e=&g_layout[g_layoutCount++];e->h=p;e->x=x;e->y=y;e->w=w;e->hh=h;e->font=FONT_UI;}
    }
    return p;
}
static void setFontKind(HWND h,int kind){
    for(int i=0;i<g_layoutCount;i++)if(g_layout[i].h==h)g_layout[i].font=kind;
    if(h)SendMessageW(h,WM_SETFONT,(WPARAM)fontOf(kind),1);
}
static void applyLayout(void){
    for(int i=0;i<g_layoutCount;i++){
        LAYOUT* e=&g_layout[i];
        SetWindowPos(e->h,0,S(e->x),S(e->y),S(e->w),S(e->hh),SWP_NOZORDER|SWP_NOACTIVATE);
        SendMessageW(e->h,WM_SETFONT,(WPARAM)fontOf(e->font),1);
    }
}
static void lbl(const WCHAR* s,int x,int y,int w){ctrl(W("STATIC"),s,SS_LEFT,x,y,w,22,0);}
static void section(const WCHAR* s,int x,int y,int w){HWND h=ctrl(W("STATIC"),s,SS_LEFT,x,y,w,29,0);setFontKind(h,FONT_TITLE);}
static HWND edit(int id,int x,int y,int w){return ctrl(W("EDIT"),W(""),WS_BORDER|WS_TABSTOP|ES_NUMBER,x,y,w,24,id);}
static HWND button(const WCHAR* s,int id,int x,int y,int w){return ctrl(W("BUTTON"),s,WS_TABSTOP|BS_OWNERDRAW,x,y,w,34,id);}
static HWND combo(int id,int x,int y,int w){return ctrl(W("COMBOBOX"),W(""),WS_TABSTOP|CBS_DROPDOWNLIST|WS_VSCROLL,x,y,w,180,id);}
static void add(HWND h,const WCHAR* s){SendMessageW(h,CB_ADDSTRING,0,(LPARAM)s);}
static int __stdcall enumMon(HMONITOR h,HDC dc,RECT* r,LPARAM user){(void)dc;(void)r;(void)user; if(g_monitorCount>=16)return 1;MONITORINFOEXW m={0};m.cbSize=sizeof(m);if(GetMonitorInfoW(h,&m)){g_handles[g_monitorCount]=h;g_monitors[g_monitorCount++]=m;}return 1;}
static int primaryIndex(void){for(int i=0;i<g_monitorCount;i++)if(g_monitors[i].dwFlags&MONITORINFOF_PRIMARY)return i;return 0;}
static int controllingIndex(void){HMONITOR h=MonitorFromWindow(g_main,MONITOR_DEFAULTTONEAREST);for(int i=0;i<g_monitorCount;i++)if(g_handles[i]==h)return i;return -1;}
static int topologyMode(void){
    if(g_monitorCount>=2)return 2; /* EXTENDER / escritorios separados */
    UINT paths=0,modes=0;
    if(GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS,&paths,&modes)==0 && paths>=2 && paths<=16 && modes<=32){
        if(QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS,&paths,g_pathBuf,&modes,g_modeBuf,0)==0 && paths>=2)return 1; /* DUPLICAR */
    }
    return 0; /* solo un escritorio disponible */
}
static void updateModeLabel(void){
    if(!g_modeLabel)return;
    int mode=topologyMode();
    SetWindowTextW(g_modeLabel,mode==2?L("Modo actual: EXTENDER · salida independiente","Current mode: EXTEND · separate output"):
        mode==1?L("Modo actual: DUPLICAR · se extenderá al proyectar","Current mode: DUPLICATE · extends when projecting"):
        L("Modo actual: una sola pantalla activa","Current mode: one screen only"));
    if(g_topoBtn)SetWindowTextW(g_topoBtn,mode==2?L("Pasar a DUPLICAR","Switch to DUPLICATE"):L("Pasar a EXTENDER","Switch to EXTEND"));
}
static void monitorName(int i,WCHAR* name){
    RECT r=g_monitors[i].rcMonitor;name[0]=0;
    appendi(name,i+1,150);appendw(name,W("  |  "),150);
    appendw(name,(g_monitors[i].dwFlags&MONITORINFOF_PRIMARY)?L("PRINCIPAL","MAIN"):L("Secundaria","Secondary"),150);
    appendw(name,W("  "),150);appendi(name,(int)(r.right-r.left),150);appendw(name,W(" x "),150);appendi(name,(int)(r.bottom-r.top),150);
    appendw(name,W("  "),150);appendw(name,g_monitors[i].szDevice,150);
}
/* Windows a person would call "a window": visible, titled, not owned, not a tool window,
 * not cloaked by DWM (hidden UWP frames), and not ProjectorScaler itself. */
static BOOL __stdcall enumWin(HWND h,LPARAM user){
    (void)user;
    if(g_winCount>=MAXWIN)return 0;
    if(h==g_main||h==g_output||!IsWindowVisible(h)||GetWindowTextLengthW(h)<1)return 1;
    if(GetWindow(h,GW_OWNER))return 1;
    if(GetWindowLongPtrW(h,GWL_EXSTYLE)&WS_EX_TOOLWINDOW)return 1;
    DWORD cloaked=0;
    if(DwmGetWindowAttribute(h,DWMWA_CLOAKED,&cloaked,sizeof(cloaked))==0&&cloaked)return 1;
    WCHAR t[32];GetWindowTextW(h,t,32);
    if(eqw(t,W("Program Manager")))return 1;
    g_winList[g_winCount++]=h;
    return 1;
}
/* Monitors first, then windows in Z order. Keeps the chosen window while its handle lives. */
static void fillSourceCombo(void){
    SendMessageW(g_source,CB_RESETCONTENT,0,0);
    for(int i=0;i<g_monitorCount;i++){WCHAR name[150];monitorName(i,name);add(g_source,name);}
    g_winCount=0;EnumWindows(enumWin,0);
    int sel=g_sourceIndex,found=0;
    for(int i=0;i<g_winCount;i++){
        WCHAR title[100]={0},line[150]={0};GetWindowTextW(g_winList[i],title,100);
        appendw(line,L("Ventana  ·  ","Window ·  "),150);appendw(line,title,150);
        if(IsIconic(g_winList[i]))appendw(line,L("  (minimizada)","  (minimised)"),150);
        add(g_source,line);
        if(g_srcWindow&&g_winList[i]==g_srcWindow){sel=g_monitorCount+i;found=1;}
    }
    if(g_srcWindow&&!found)g_srcWindow=0;
    comboselect(g_source,sel);
}
/* Rebuilds both combos, keeping the current g_sourceIndex/g_targetIndex by device name.
 * Returns 1 when both previous choices still exist. A kept choice is never changed here:
 * startOutput() is the one that refuses an unsafe target and tells the user why. */
static int refreshMonitors(void){
    WCHAR srcName[32]={0},dstName[32]={0};
    int oldCount=g_monitorCount;
    if(oldCount && g_sourceIndex>=0 && g_sourceIndex<oldCount)copyw(srcName,g_monitors[g_sourceIndex].szDevice,32);
    if(oldCount && g_targetIndex>=0 && g_targetIndex<oldCount)copyw(dstName,g_monitors[g_targetIndex].szDevice,32);
    g_monitorCount=0;EnumDisplayMonitors(0,0,enumMon,0);
    SendMessageW(g_target,CB_RESETCONTENT,0,0);
    int p=primaryIndex(),matchedS=0,matchedT=0;
    g_sourceIndex=p;g_targetIndex=(p==0&&g_monitorCount>1)?1:0;
    for(int i=0;i<g_monitorCount;i++){
        WCHAR name[150];monitorName(i,name);add(g_target,name);
        if(srcName[0]&&eqw(g_monitors[i].szDevice,srcName)){g_sourceIndex=i;matchedS=1;}
        if(dstName[0]&&eqw(g_monitors[i].szDevice,dstName)){g_targetIndex=i;matchedT=1;}
    }
    /* In DUPLICAR there is one desktop, so source and target are saved as the same device;
     * after the switch to EXTENDER that must not count as a kept target. */
    if(matchedT&&!g_srcWindow&&g_targetIndex==g_sourceIndex)matchedT=0;
    if(!matchedT&&g_monitorCount>1){
        int ctl=controllingIndex(),pick=-1;
        for(int i=0;i<g_monitorCount&&pick<0;i++)if(i!=g_sourceIndex&&i!=ctl)pick=i;
        for(int i=0;i<g_monitorCount&&pick<0;i++)if(i!=g_sourceIndex)pick=i;
        g_targetIndex=pick<0?0:pick;
    }
    if(g_source)fillSourceCombo();
    if(g_target)comboselect(g_target,g_targetIndex);
    if(g_tilesWnd&&g_tileTab==0&&(oldCount!=g_monitorCount||!matchedS))fillTiles();
    updateModeLabel();
    return matchedS&&matchedT;
}
static void takeComboSelection(void){
    if(g_monitorCount<1)return;
    if(g_source){ /* the tiles set the source directly; this only reads a source combo if one exists */
        int sel=comboindex(g_source);
        if(sel<g_monitorCount){g_sourceIndex=sel;g_srcWindow=0;}
        else if(sel-g_monitorCount<g_winCount)g_srcWindow=g_winList[sel-g_monitorCount];
    }
    if(g_target)g_targetIndex=MIN(comboindex(g_target),g_monitorCount-1);
}
static void dismissIds(void){KillTimer(g_main,ID_HIDEIDS);for(int i=0;i<16;i++)if(g_ids[i]){DestroyWindow(g_ids[i]);g_ids[i]=0;}}
static void identifyScreens(void){
    dismissIds();refreshMonitors();
    if(!g_monitorCount)return;
    if(topologyMode()==1){
        MessageBoxW(g_main,L("Las pantallas están DUPLICADAS: Windows muestra exactamente la misma imagen en ambas.\n\nPulsa Iniciar proyección para pasar temporalmente a EXTENDER y entonces podrás identificar y elegir cada salida.","The screens are DUPLICATED: Windows shows exactly the same picture on both.\n\nPress Start projection to switch temporarily to EXTEND; then you can identify and choose each output."),L("Identificación de pantallas","Identify screens"),0x40);
        return;
    }
    for(int i=0;i<g_monitorCount;i++){
        RECT r=g_monitors[i].rcMonitor;
        g_ids[i]=CreateWindowExW(WS_EX_TOPMOST|WS_EX_TOOLWINDOW|WS_EX_NOACTIVATE,W("ProjectorScalerIdentify"),L("Identificación","Identification"),WS_POPUP,(int)r.left,(int)r.top,(int)(r.right-r.left),(int)(r.bottom-r.top),0,0,g_inst,0);
        if(g_ids[i]){ShowWindow(g_ids[i],SW_SHOW);SetWindowPos(g_ids[i],HWND_TOPMOST,r.left,r.top,r.right-r.left,r.bottom-r.top,SWP_NOACTIVATE|SWP_SHOWWINDOW);}
    }
    SetTimer(g_main,ID_HIDEIDS,5000,0);
    status(L("Identificación activa 5 segundos. Localiza el número de cada pantalla.","Identification on for 5 seconds. Find the number on each screen."));
}
/* The free frame must be a real rectangle inside the screen; anything else falls back. */
static void readFree(const WCHAR* section){
    int f[4];
    f[0]=(int)GetPrivateProfileIntW(section,W("FreeLeft"),1500,g_ini);
    f[1]=(int)GetPrivateProfileIntW(section,W("FreeTop"),1500,g_ini);
    f[2]=(int)GetPrivateProfileIntW(section,W("FreeRight"),8500,g_ini);
    f[3]=(int)GetPrivateProfileIntW(section,W("FreeBottom"),8500,g_ini);
    for(int i=0;i<4;i++)f[i]=MAX(0,MIN(f[i],FREE_UNIT));
    if(f[2]-f[0]<100||f[3]-f[1]<100){f[0]=1500;f[1]=1500;f[2]=8500;f[3]=8500;}
    for(int i=0;i<4;i++)g_free[i]=f[i];
}
static void readConfig(void){
    g_zoomValue=(int)GetPrivateProfileIntW(W("Settings"),W("Zoom"),60,g_ini);
    g_xValue=(int)GetPrivateProfileIntW(W("Settings"),W("PositionX"),50,g_ini);
    g_yValue=(int)GetPrivateProfileIntW(W("Settings"),W("PositionY"),50,g_ini);
    g_aspectIndex=(int)GetPrivateProfileIntW(W("Settings"),W("Aspect"),0,g_ini);
    g_fitIndex=(int)GetPrivateProfileIntW(W("Settings"),W("Fit"),0,g_ini);
    g_cw=(int)GetPrivateProfileIntW(W("Settings"),W("CustomWidth"),3,g_ini);
    g_ch=(int)GetPrivateProfileIntW(W("Settings"),W("CustomHeight"),2,g_ini);
    g_showCursor=(int)GetPrivateProfileIntW(W("Settings"),W("ShowCursor"),1,g_ini);
    g_zoomValue=MAX(20,MIN(g_zoomValue,100));g_xValue=MAX(0,MIN(g_xValue,100));g_yValue=MAX(0,MIN(g_yValue,100));
    g_aspectIndex=MAX(0,MIN(g_aspectIndex,ASPECT_FREE));g_fitIndex=MAX(0,MIN(g_fitIndex,2));
    g_cw=MAX(1,MIN(g_cw,1000));g_ch=MAX(1,MIN(g_ch,1000));
    readFree(W("Settings"));
}
static void syncControls(void){
    if(!g_zoom)return; /* the basic mode has none of these fields */
    setint(g_zoom,g_zoomValue);setint(g_x,g_xValue);setint(g_y,g_yValue);
    setint(g_customW,g_cw);setint(g_customH,g_ch);
    comboselect(g_aspect,g_aspectIndex);comboselect(g_fit,g_fitIndex);
    SendMessageW(g_cursor,BM_SETCHECK,g_showCursor?BST_CHECKED:0,0);
    /* With a free frame, size and position come from the mouse, not from these fields. */
    int fixed=g_aspectIndex!=ASPECT_FREE;
    EnableWindow(g_zoom,fixed);EnableWindow(g_x,fixed);EnableWindow(g_y,fixed);
}
static void readControls(void){
    if(!g_zoom)return;
    g_zoomValue=getint(g_zoom,g_zoomValue,20,100);
    g_xValue=getint(g_x,g_xValue,0,100);g_yValue=getint(g_y,g_yValue,0,100);
    g_cw=getint(g_customW,g_cw,1,1000);g_ch=getint(g_customH,g_ch,1,1000);
    g_aspectIndex=comboindex(g_aspect);g_fitIndex=comboindex(g_fit);
    g_showCursor=(SendMessageW(g_cursor,BM_GETCHECK,0,0)==BST_CHECKED);
}
/* Every INI write goes through here so a read-only folder is reported, not hidden. */
static void iniWrite(const WCHAR* section,const WCHAR* key,const WCHAR* value){
    if(!WritePrivateProfileStringW(section,key,value,g_ini))g_iniError=1;
}
static void writeOne(const WCHAR* section,const WCHAR* key,int value){
    WCHAR n[32];intw(n,value);iniWrite(section,key,n);
}
static void writeFree(const WCHAR* section){
    writeOne(section,W("FreeLeft"),g_free[0]);writeOne(section,W("FreeTop"),g_free[1]);
    writeOne(section,W("FreeRight"),g_free[2]);writeOne(section,W("FreeBottom"),g_free[3]);
}
static void writeConfig(void){
    const WCHAR* s=W("Settings");
    writeOne(s,W("Zoom"),g_zoomValue);writeOne(s,W("PositionX"),g_xValue);writeOne(s,W("PositionY"),g_yValue);
    writeOne(s,W("Aspect"),g_aspectIndex);writeOne(s,W("Fit"),g_fitIndex);writeOne(s,W("CustomWidth"),g_cw);writeOne(s,W("CustomHeight"),g_ch);
    writeOne(s,W("ShowCursor"),g_showCursor);
    writeFree(s);
    if(g_runBasic)return; /* the basic mode picks its own pair; keep the advanced choice */
    if(g_monitorCount>g_sourceIndex)iniWrite(s,W("Source"),g_monitors[g_sourceIndex].szDevice);
    if(g_monitorCount>g_targetIndex)iniWrite(s,W("Target"),g_monitors[g_targetIndex].szDevice);
}
static const WCHAR* iniErrorText(void){
    return L("No se pudo escribir ProjectorScaler.ini: la carpeta del programa no admite escritura. Los ajustes no se guardarán.","Could not write ProjectorScaler.ini: the program folder is read-only. Settings will not be saved.");
}
static void loadSavedMonitors(void){
    WCHAR s[64],t[64];GetPrivateProfileStringW(W("Settings"),W("Source"),W(""),s,64,g_ini);
    GetPrivateProfileStringW(W("Settings"),W("Target"),W(""),t,64,g_ini);
    for(int i=0;i<g_monitorCount;i++){
        if(eqw(g_monitors[i].szDevice,s))g_sourceIndex=i;
        if(eqw(g_monitors[i].szDevice,t))g_targetIndex=i;
    }
    if(g_sourceIndex==g_targetIndex && g_monitorCount>1)g_targetIndex=(g_sourceIndex+1)%g_monitorCount;
    comboselect(g_source,g_sourceIndex);comboselect(g_target,g_targetIndex);
}
static void freeTabScratch(void){
    if(g_tabDC){SelectObject(g_tabDC,g_tabOld);DeleteDC(g_tabDC);g_tabDC=0;}
    if(g_tabBmp){DeleteObject(g_tabBmp);g_tabBmp=0;}
    g_tabBw=g_tabBh=0;
}
static void clearRender(void){
    freeTabScratch();
    if(g_capDC){if(g_capOld)SelectObject(g_capDC,g_capOld);if(g_capBmp)DeleteObject(g_capBmp);DeleteDC(g_capDC);}
    if(g_bufDC){if(g_bufOld)SelectObject(g_bufDC,g_bufOld);if(g_bufBmp)DeleteObject(g_bufBmp);DeleteDC(g_bufDC);}
    g_capDC=g_bufDC=0;g_capBmp=g_bufBmp=0;g_capOld=g_bufOld=0;
}
static void refreshRunState(void);
static void stopOutput(void){
    if(g_output){KillTimer(g_output,1);DestroyWindow(g_output);g_output=0;} /* takes the magnifier with it */
    g_mag=0;g_magShown=0;g_magCursor=-1;
    clearRender();g_isRunning=0;g_isBlack=0;g_frameMs=FRAME_MIN_MS;
    if(g_start)SetWindowTextW(g_start,startLabel(0));
    if(g_black){SetWindowTextW(g_black,L("Pantalla negra","Black screen"));EnableWindow(g_black,0);}
    g_editFrame=0;g_drag=HIT_NONE;
    if(g_editBtn){SetWindowTextW(g_editBtn,L("Ajustar con el ratón","Adjust with the mouse"));EnableWindow(g_editBtn,0);}
}
static void computeFrame(int* ox,int* oy,int* ow,int* oh){
    if(g_aspectIndex==ASPECT_FREE||g_runBasic){
        const int* f=g_runBasic?g_basicFree:g_free;
        int l=(f[0]*g_tw+FREE_UNIT/2)/FREE_UNIT,t=(f[1]*g_th+FREE_UNIT/2)/FREE_UNIT;
        int r=(f[2]*g_tw+FREE_UNIT/2)/FREE_UNIT,b=(f[3]*g_th+FREE_UNIT/2)/FREE_UNIT;
        *ox=l;*oy=t;*ow=MAX(1,r-l);*oh=MAX(1,b-t);return;
    }
    double r;
    switch(g_aspectIndex){case 1:r=16.0/10;break;case 2:r=4.0/3;break;case 3:r=21.0/9;break;case 4:r=1.0;break;case 5:r=(double)g_cw/(double)g_ch;break;default:r=16.0/9;}
    double w=(double)g_tw;double h=w/r;
    if(h>g_th){h=g_th;w=h*r;}
    w*=g_zoomValue/100.0;h*=g_zoomValue/100.0;
    *ow=(int)(w+0.5);*oh=(int)(h+0.5);
    *ow=MAX(1,MIN(*ow,g_tw));*oh=MAX(1,MIN(*oh,g_th));
    *ox=(g_tw-*ow)*g_xValue/100;*oy=(g_th-*oh)*g_yValue/100;
}
/* (ox,oy) is the screen position of the capture's top-left pixel; w x h its size. */
static void drawCursorOnCapture(int ox,int oy,int w,int h){
    if(!g_showCursor)return;
    CURSORINFO ci={0};ci.cbSize=sizeof(ci);
    if(!GetCursorInfo(&ci) || !(ci.flags&1))return;
    RECT r={ox,oy,ox+w,oy+h};
    if(ci.ptScreenPos.x<r.left||ci.ptScreenPos.x>=r.right||ci.ptScreenPos.y<r.top||ci.ptScreenPos.y>=r.bottom)return;
    ICONINFO info={0};int hotX=0,hotY=0;
    if(GetIconInfo(ci.hCursor,&info)){
        hotX=(int)info.xHotspot;hotY=(int)info.yHotspot;
        if(info.hbmMask)DeleteObject(info.hbmMask);
        if(info.hbmColor)DeleteObject(info.hbmColor);
    }
    DrawIconEx(g_capDC,(int)ci.ptScreenPos.x-r.left-hotX,(int)ci.ptScreenPos.y-r.top-hotY,(HICON)ci.hCursor,0,0,0,0,DI_NORMAL);
}
/* Capture runs on the UI thread. After each timed frame the interval is moved so that
 * capture takes at most about half the thread's time (50-250 ms), keeping the panel usable
 * on slow machines or large sources. */
static void adaptFrameRate(DWORD elapsed){
    if(!g_output)return;
    int want=(int)MIN(elapsed,(DWORD)FRAME_MAX_MS)*2;
    want=MAX(FRAME_MIN_MS,MIN(want,FRAME_MAX_MS));
    if(want>g_frameMs+15||want<g_frameMs-15){g_frameMs=want;SetTimer(g_output,1,(UINT)g_frameMs,0);}
}
/* Keeps the capture bitmap the size of the window's client area as the window is resized. */
static int ensureCaptureSize(int w,int h){
    if(w==g_sw&&h==g_sh)return 1;
    HDC screen=GetDC(0);if(!screen)return 0;
    HBITMAP bmp=CreateCompatibleBitmap(screen,w,h);ReleaseDC(0,screen);
    if(!bmp)return 0;
    SelectObject(g_capDC,bmp);if(g_capBmp)DeleteObject(g_capBmp);
    g_capBmp=bmp;g_sw=w;g_sh=h;return 1;
}
/* One window: PrintWindow asks the window to draw itself, so it works even when other
 * windows cover it; if the window refuses, copy its area from the screen instead.
 * A minimised window keeps its last frame; a closed one keeps it and says so once. */
/* Fail closed: no confirmed tab, or a browser title that changed since the guard last
 * confirmed the tab, keeps the last picture until the guard confirms it again. */
static void captureTab(void){
    if(!g_tabSel||g_tabFrozen)return;
    WCHAR now[256];GetWindowTextW(g_srcWindow,now,256);
    if(!eqw(now,g_tabExpect)){g_tabFrozen=1;return;}
    RECT cr={0};GetClientRect(g_srcWindow,&cr);int w=(int)cr.right,h=(int)cr.bottom;
    RECT c=g_tabCrop;
    if(c.right>cr.right)c.right=cr.right;
    if(c.bottom>cr.bottom)c.bottom=cr.bottom;
    int cw=(int)(c.right-c.left),ch=(int)(c.bottom-c.top);
    if(w<2||h<2||cw<2||ch<2)return;
    if(w!=g_tabBw||h!=g_tabBh){
        freeTabScratch();
        HDC screen=GetDC(0);if(!screen)return;
        g_tabDC=CreateCompatibleDC(screen);g_tabBmp=CreateCompatibleBitmap(screen,w,h);ReleaseDC(0,screen);
        if(!g_tabDC||!g_tabBmp){freeTabScratch();return;}
        g_tabOld=SelectObject(g_tabDC,g_tabBmp);g_tabBw=w;g_tabBh=h;
    }
    /* No copy from the screen here: whatever covers the browser would be projected. */
    if(!PrintWindow(g_srcWindow,g_tabDC,PW_CLIENTONLY|PW_RENDERFULLCONTENT))return;
    GetWindowTextW(g_srcWindow,now,256);
    if(!eqw(now,g_tabExpect)){g_tabFrozen=1;return;}
    if(!ensureCaptureSize(cw,ch))return;
    BitBlt(g_capDC,0,0,cw,ch,g_tabDC,(int)c.left,(int)c.top,SRCCOPY);
    POINT o={0,0};ClientToScreen(g_srcWindow,&o);
    drawCursorOnCapture((int)o.x+(int)c.left,(int)o.y+(int)c.top,cw,ch);
}
static void captureWindow(void){
    if(!IsWindow(g_srcWindow)){
        if(!g_srcLost){g_srcLost=1;status(L("La ventana proyectada se ha cerrado: se mantiene la última imagen. Elige otro origen.","The projected window was closed: the last picture stays. Choose another source."));}
        return;
    }
    if(IsIconic(g_srcWindow))return;
    if(g_srcKind==TILE_TAB){captureTab();return;}
    RECT cr={0};GetClientRect(g_srcWindow,&cr);
    int w=(int)cr.right,h=(int)cr.bottom;
    if(w<2||h<2||!ensureCaptureSize(w,h))return;
    POINT o={0,0};ClientToScreen(g_srcWindow,&o);
    if(!PrintWindow(g_srcWindow,g_capDC,PW_CLIENTONLY|PW_RENDERFULLCONTENT)){
        HDC desktop=GetDC(0);
        if(desktop){BitBlt(g_capDC,0,0,w,h,desktop,(int)o.x,(int)o.y,SRCCOPY|CAPTUREBLT);ReleaseDC(0,desktop);}
    }
    drawCursorOnCapture((int)o.x,(int)o.y,w,h);
}
static void captureSource(void){
    if(g_srcWindow){captureWindow();return;}
    HDC desktop=GetDC(0);
    if(!desktop)return;
    RECT r=g_monitors[g_sourceIndex].rcMonitor;
    BitBlt(g_capDC,0,0,g_sw,g_sh,desktop,r.left,r.top,SRCCOPY|CAPTUREBLT);
    ReleaseDC(0,desktop);
    drawCursorOnCapture((int)r.left,(int)r.top,g_sw,g_sh);
}
static void fillBox(int l,int t,int r,int b,DWORD colour){
    RECT rc={l,t,r,b};HBRUSH br=CreateSolidBrush(colour);FillRect(g_bufDC,&rc,br);DeleteObject(br);
}
static int handleHalf(void){return MAX(6,g_th/140);}
static HFONT g_hintFont=0;
static int g_hintHeight=0;
static HFONT hintFont(int height){
    if(!g_hintFont||g_hintHeight!=height){
        if(g_hintFont)DeleteObject(g_hintFont);
        g_hintFont=CreateFontW(-height,0,0,0,650,0,0,0,1,0,0,0,0,W("Segoe UI"));g_hintHeight=height;
    }
    return g_hintFont;
}
/* Drawn only while "Ajustar con el ratón" is on: amber outline, eight handles and a hint. */
static void drawEditOverlay(int fx,int fy,int fw,int fh){
    DWORD amber=RGB3(245,166,35),white=RGB3(255,255,255),navy=RGB3(19,46,78);
    /* Outline inside the frame, so it stays visible when the frame fills the screen. */
    int b=MAX(2,g_th/360);
    fillBox(fx,fy,fx+fw,fy+b,amber);fillBox(fx,fy+fh-b,fx+fw,fy+fh,amber);
    fillBox(fx,fy,fx+b,fy+fh,amber);fillBox(fx+fw-b,fy,fx+fw,fy+fh,amber);
    int h=handleHalf(),xs[3]={fx,fx+fw/2,fx+fw},ys[3]={fy,fy+fh/2,fy+fh};
    for(int i=0;i<3;i++){xs[i]=MAX(h+2,MIN(xs[i],g_tw-h-2));ys[i]=MAX(h+2,MIN(ys[i],g_th-h-2));}
    for(int i=0;i<3;i++)for(int j=0;j<3;j++){
        if(i==1&&j==1)continue;
        fillBox(xs[i]-h-2,ys[j]-h-2,xs[i]+h+2,ys[j]+h+2,navy);
        fillBox(xs[i]-h,ys[j]-h,xs[i]+h,ys[j]+h,white);
    }
    /* Hint sized to the projector: ~27 px on 1080 lines, still one line on 1024 x 768. */
    int textH=MAX(14,g_th/40),top=MAX(6,g_th/120),band=textH*2;
    fillBox(0,top,g_tw,top+band,navy);
    RECT tr={0,top,g_tw,top+band};
    HGDIOBJ old=SelectObject(g_bufDC,hintFont(textH));
    SetBkMode(g_bufDC,TRANSPARENT);SetTextColor(g_bufDC,amber);
    DrawTextW(g_bufDC,L("AJUSTE  ·  centro: mover  ·  bordes y esquinas: estirar  ·  Mayús: proporción","ADJUST · middle: move · edges and corners: stretch · Shift: proportions"),-1,&tr,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    SelectObject(g_bufDC,old);
}
/* Puts the last capture into the frame. Cheap enough to call on every mouse move. */
/* Which part of the source (s*) lands where on the projector (d*), for the frame f*. */
static void pictureRects(int fx,int fy,int fw,int fh,int* sx,int* sy,int* sw,int* sh,int* dx,int* dy,int* dw,int* dh){
    *sx=0;*sy=0;*sw=g_sw;*sh=g_sh;*dx=fx;*dy=fy;*dw=fw;*dh=fh;
    int fit=g_runBasic?0:g_fitIndex;
    if(fit==0){
        double ar=(double)g_sw/g_sh,fr=(double)fw/fh;
        if(ar>fr){*dh=MAX(1,(int)(fw/ar+0.5));*dy=fy+(fh-*dh)/2;}
        else {*dw=MAX(1,(int)(fh*ar+0.5));*dx=fx+(fw-*dw)/2;}
    }else if(fit==1){
        double ar=(double)g_sw/g_sh,fr=(double)fw/fh;
        if(ar>fr){*sw=MAX(1,(int)(g_sh*fr+0.5));*sx=(g_sw-*sw)/2;}
        else {*sh=MAX(1,(int)(g_sw/fr+0.5));*sy=(g_sh-*sh)/2;}
    }
}
static void compose(void){
    if(!g_isRunning||!g_bufDC)return;
    PatBlt(g_bufDC,0,0,g_tw,g_th,BLACKNESS);
    int fx,fy,fw,fh;computeFrame(&fx,&fy,&fw,&fh);
    if(!g_isBlack){
        int sx,sy,sw,sh,dx,dy,dw,dh;pictureRects(fx,fy,fw,fh,&sx,&sy,&sw,&sh,&dx,&dy,&dw,&dh);
        SetStretchBltMode(g_bufDC,HALFTONE);
        SetBrushOrgEx(g_bufDC,0,0,0); /* required by GDI after selecting HALFTONE */
        StretchBlt(g_bufDC,dx,dy,dw,dh,g_capDC,sx,sy,sw,sh,SRCCOPY);
    }
    if(g_editFrame)drawEditOverlay(fx,fy,fw,fh);
    InvalidateRect(g_output,0,0);
}
static void magCreate(void){
    if(g_srcWindow||!g_output)return;
    if(g_magInit==0)g_magInit=MagInitialize()?1:-1;
    if(g_magInit!=1)return;
    g_mag=CreateWindowExW(0,W("Magnifier"),W(""),WS_CHILD,0,0,1,1,g_output,0,g_inst,0);
    g_magShown=0;g_magCursor=-1;g_magDst.left=g_magDst.top=g_magDst.right=g_magDst.bottom=0;
}
/* Draws this frame with the magnifier when it can; 0 means the GDI path has to. */
static int magRender(void){
    int want=g_mag&&!g_srcWindow&&!g_isBlack&&!g_editFrame&&g_sourceIndex<g_monitorCount;
    if(!want){
        if(g_magShown){ShowWindow(g_mag,SW_HIDE);g_magShown=0;}
        return 0;
    }
    int fx,fy,fw,fh;computeFrame(&fx,&fy,&fw,&fh);
    int sx,sy,sw,sh,dx,dy,dw,dh;pictureRects(fx,fy,fw,fh,&sx,&sy,&sw,&sh,&dx,&dy,&dw,&dh);
    RECT dst={dx,dy,dx+dw,dy+dh};
    if(!g_magShown||dst.left!=g_magDst.left||dst.top!=g_magDst.top||dst.right!=g_magDst.right||dst.bottom!=g_magDst.bottom){
        float m[9]={(float)dw/(float)sw,0,0, 0,(float)dh/(float)sh,0, 0,0,1};
        if(!MagSetWindowTransform(g_mag,m))return 0;
        SetWindowPos(g_mag,0,dx,dy,dw,dh,SWP_NOZORDER|SWP_NOACTIVATE);
        g_magDst=dst;
        PatBlt(g_bufDC,0,0,g_tw,g_th,BLACKNESS);InvalidateRect(g_output,0,0); /* black around the picture */
    }
    if(g_magCursor!=g_showCursor){
        LONG_PTR st=GetWindowLongPtrW(g_mag,GWL_STYLE);
        SetWindowLongPtrW(g_mag,GWL_STYLE,g_showCursor?(st|MS_SHOWMAGNIFIEDCURSOR):(st&~(LONG_PTR)MS_SHOWMAGNIFIEDCURSOR));
        g_magCursor=g_showCursor;
    }
    RECT m=g_monitors[g_sourceIndex].rcMonitor;
    RECT src={m.left+sx,m.top+sy,m.left+sx+sw,m.top+sy+sh};
    /* MagSetWindowSource redraws the control itself and waits for the next vertical blank.
     * Do not also InvalidateRect(g_mag): its WM_PAINT waits for a second blank, halving the rate
     * (measured: 29 frames per second with it, 55.7 without). */
    if(!MagSetWindowSource(g_mag,src)){ShowWindow(g_mag,SW_HIDE);g_magShown=0;return 0;}
    if(!g_magShown){ShowWindow(g_mag,SW_SHOWNA);g_magShown=1;}
    return 1;
}
static void render(void){
    if(!g_isRunning||!g_bufDC)return;
    if(magRender())return;
    if(!g_isBlack)captureSource();
    compose();
}
static int switchToExtend(void){
    if(g_uiMode!=0&&MessageBoxW(g_main,L("Windows está en modo DUPLICAR.\n\nPara mostrar una imagen reducida SOLO en el proyector es necesario pasar TEMPORALMENTE a EXTENDER.\n\nLa aplicación podrá restaurar DUPLICAR al detener la proyección.\n\n¿Quieres cambiar ahora a EXTENDER?","Windows is in DUPLICATE mode.\n\nTo show a reduced picture ONLY on the projector, Windows has to switch TEMPORARILY to EXTEND.\n\nThe app can restore DUPLICATE when the projection stops.\n\nSwitch to EXTEND now?"),L("Cambiar modo de pantalla","Change display mode"),MB_YESNO|MB_ICONQUESTION)!=IDYES)return 0;
    if(SetDisplayConfig(0,0,0,0,SDC_VALIDATE|SDC_TOPOLOGY_EXTEND)!=0){
        MessageBoxW(g_main,L("Windows no admite el modo EXTENDER con esta conexión. Comprueba los adaptadores HDMI y la configuración de pantalla.","Windows does not support EXTEND with this connection. Check the HDMI adapters and the display settings."),L("No se puede extender","Cannot extend"),0x30);return 0;
    }
    g_switching=1;
    if(SetDisplayConfig(0,0,0,0,SDC_APPLY|SDC_TOPOLOGY_EXTEND)!=0){
        g_switching=0;MessageBoxW(g_main,L("Windows no pudo cambiar a EXTENDER. Puedes intentar Win + P > Extender.","Windows could not switch to EXTEND. You can try Win + P > Extend."),L("Error de pantalla","Display error"),0x30);return 0;
    }
    g_wasClone=1;g_pending=0;EnableWindow(g_start,0);SetTimer(g_main,ID_BEGIN_AFTER_EXTEND,850,0);
    /* Survives a crash or a forced close: the next start offers to put DUPLICAR back. */
    iniWrite(W("Settings"),W("PendingRestoreClone"),W("1"));
    status(L("Cambiando de DUPLICAR a EXTENDER... Se abrirá la proyección en el monitor secundario.","Switching from DUPLICATE to EXTEND... The projection opens on the secondary screen."));
    return 1;
}
static void restoreIfNeeded(void){
    KillTimer(g_main,ID_BEGIN_AFTER_EXTEND);g_pending=0;g_switching=0;EnableWindow(g_start,1);
    if(!g_wasClone)return;
    g_wasClone=0;
    iniWrite(W("Settings"),W("PendingRestoreClone"),W("0"));
    if(g_restoreClone||g_uiMode==0){ /* the basic mode always puts DUPLICATE back */
        LONG result=SetDisplayConfig(0,0,0,0,SDC_APPLY|SDC_TOPOLOGY_CLONE);
        if(result!=0)MessageBoxW(g_main,L("No se pudo restaurar DUPLICAR automáticamente. Usa Win + P > Duplicar.","Could not restore DUPLICATE automatically. Use Win + P > Duplicate."),L("Restaurar pantallas","Restore screens"),0x30);
    }
    refreshMonitors();
}
/* ---- Basic mode: "your screen" mirrored onto the projector, sized with a frame ----
 * The frame lives in g_basicFree (FREE_UNIT of the projector) and always keeps the
 * screen's proportions, so what the preview shows is exactly where the picture lands. */
static int basicSourceIndex(void){int c=controllingIndex();return c<0?primaryIndex():c;}
static int basicTargetIndex(void){int s=basicSourceIndex();for(int i=0;i<g_monitorCount;i++)if(i!=s)return i;return s;}
static void basicSelect(void){g_srcWindow=0;g_srcKind=TILE_SCREEN;g_sourceIndex=basicSourceIndex();g_targetIndex=basicTargetIndex();}
/* In DUPLICATE only one desktop is listed, so the projector is assumed to have the
 * screen's shape until EXTEND reveals it; startOutput() re-derives the frame then. */
static void basicSizes(double* sa,double* tw,double* th){
    *sa=16.0/9;*tw=16;*th=9;
    if(g_monitorCount<1)return;
    RECT s=g_monitors[basicSourceIndex()].rcMonitor,t=g_monitors[basicTargetIndex()].rcMonitor;
    double sw=(double)(s.right-s.left),sh=(double)(s.bottom-s.top);
    if(sw>0&&sh>0)*sa=sw/sh;
    *tw=(double)(t.right-t.left);*th=(double)(t.bottom-t.top);
    if(*tw<1||*th<1){*tw=sw;*th=sh;}
    if(*tw<1||*th<1){*tw=16;*th=9;}
}
/* Width/height of an undistorted frame, measured in FREE_UNIT on both axes. */
static double basicRatio(void){double sa,tw,th;basicSizes(&sa,&tw,&th);return sa*th/tw;}
static void basicSet(double l,double t,double w,double h){
    if(w>FREE_UNIT){h*=FREE_UNIT/w;w=FREE_UNIT;}
    if(h>FREE_UNIT){w*=FREE_UNIT/h;h=FREE_UNIT;}
    l=MAX(0.0,MIN(l,FREE_UNIT-w));t=MAX(0.0,MIN(t,FREE_UNIT-h));
    g_basicFree[0]=(int)(l+0.5);g_basicFree[1]=(int)(t+0.5);
    g_basicFree[2]=(int)(l+w+0.5);g_basicFree[3]=(int)(t+h+0.5);
}
static double basicFullWidth(void){double a=basicRatio(),w=FREE_UNIT,h=w/a;if(h>FREE_UNIT){h=FREE_UNIT;w=h*a;}return w;}
/* Keeps the width and the centre and re-derives the height for the current shapes. */
static void basicNormalize(void){
    double a=basicRatio(),w=g_basicFree[2]-g_basicFree[0];
    double cx=(g_basicFree[0]+g_basicFree[2])/2.0,cy=(g_basicFree[1]+g_basicFree[3])/2.0;
    w=MAX(w,500.0);w=MIN(w,basicFullWidth());
    double h=w/a;
    basicSet(cx-w/2,cy-h/2,w,h);
}
static void basicCenter(void){double w=g_basicFree[2]-g_basicFree[0],h=g_basicFree[3]-g_basicFree[1];basicSet((FREE_UNIT-w)/2,(FREE_UNIT-h)/2,w,h);}
static void basicFill(void){double w=basicFullWidth(),h=w/basicRatio();basicSet((FREE_UNIT-w)/2,(FREE_UNIT-h)/2,w,h);}
static int basicPercent(void){return (int)((g_basicFree[2]-g_basicFree[0])*100.0/basicFullWidth()+0.5);}
static void readBasic(void){
    int f[4];
    f[0]=(int)GetPrivateProfileIntW(W("Settings"),W("BasicLeft"),1000,g_ini);
    f[1]=(int)GetPrivateProfileIntW(W("Settings"),W("BasicTop"),1000,g_ini);
    f[2]=(int)GetPrivateProfileIntW(W("Settings"),W("BasicRight"),9000,g_ini);
    f[3]=(int)GetPrivateProfileIntW(W("Settings"),W("BasicBottom"),9000,g_ini);
    for(int i=0;i<4;i++)f[i]=MAX(0,MIN(f[i],FREE_UNIT));
    if(f[2]-f[0]<300||f[3]-f[1]<300){f[0]=1000;f[1]=1000;f[2]=9000;f[3]=9000;}
    for(int i=0;i<4;i++)g_basicFree[i]=f[i];
    basicNormalize();
}
static void writeBasic(void){
    writeOne(W("Settings"),W("BasicLeft"),g_basicFree[0]);writeOne(W("Settings"),W("BasicTop"),g_basicFree[1]);
    writeOne(W("Settings"),W("BasicRight"),g_basicFree[2]);writeOne(W("Settings"),W("BasicBottom"),g_basicFree[3]);
}
static void updateSizeLabel(void){
    if(!g_sizeLbl)return;
    WCHAR b[64]={0};appendw(b,L("Tamaño: ","Size: "),64);appendi(b,basicPercent(),64);appendw(b,W(" %"),64);
    SetWindowTextW(g_sizeLbl,b);
}
/* After any change of the basic frame: preview, label, live picture. */
static void basicChanged(void){
    if(g_preview)InvalidateRect(g_preview,0,0);
    updateSizeLabel();
    if(g_isRunning&&g_runBasic)compose();
}
static int startOutput(void){
    if(g_uiMode==0)basicSelect();else takeComboSelection();
    g_runBasic=g_uiMode==0;
    int win=g_srcWindow!=0;
    if(g_monitorCount<2 || g_targetIndex>=g_monitorCount || (!win && (g_sourceIndex==g_targetIndex || g_sourceIndex>=g_monitorCount))){
        MessageBoxW(g_main,L("No hay dos escritorios independientes. Comprueba el modo EXTENDER y pulsa Actualizar.","There are not two separate desktops. Check EXTEND mode and press Refresh."),W("ProjectorScaler"),0x30);return 0;
    }
    if(g_targetIndex==controllingIndex()){
        MessageBoxW(g_main,L("PROTECCIÓN ACTIVADA: el destino es la pantalla donde estás manejando ProjectorScaler.\n\nElige la otra pantalla como destino para no ocultar el panel de control.","PROTECTION ON: the target is the screen where you are using ProjectorScaler.\n\nChoose the other screen as the target so the control panel is not covered."),L("Selección de destino incorrecta","Wrong target"),0x30);return 0;
    }
    if(win&&!IsWindow(g_srcWindow)){
        MessageBoxW(g_main,L("La ventana elegida ya no existe. Pulsa Actualizar y elígela de nuevo.","The chosen window no longer exists. Press Refresh and choose it again."),W("ProjectorScaler"),0x30);return 0;
    }
    RECT s=g_monitors[g_sourceIndex].rcMonitor,t=g_monitors[g_targetIndex].rcMonitor;
    g_sw=(int)(s.right-s.left);g_sh=(int)(s.bottom-s.top);
    if(win){
        /* Start at the window's client size; a minimised window starts at 16:9 until restored. */
        RECT cr={0};GetClientRect(g_srcWindow,&cr);
        g_sw=(int)cr.right;g_sh=(int)cr.bottom;
        if(IsIconic(g_srcWindow)||g_sw<2||g_sh<2){g_sw=1280;g_sh=720;}
        if(g_srcKind==TILE_TAB&&g_tabCrop.right-g_tabCrop.left>=16&&g_tabCrop.bottom-g_tabCrop.top>=16){
            g_sw=(int)(g_tabCrop.right-g_tabCrop.left);g_sh=(int)(g_tabCrop.bottom-g_tabCrop.top);
        }
    }
    g_srcLost=0;
    g_tw=(int)(t.right-t.left);g_th=(int)(t.bottom-t.top);g_tOrgX=(int)t.left;g_tOrgY=(int)t.top;
    if(g_sw<2||g_sh<2||g_tw<2||g_th<2){status(L("Error: resolución de monitor incorrecta.","Error: wrong screen resolution."));return 0;}
    HDC screen=GetDC(0);
    if(!screen)return 0;
    g_capDC=CreateCompatibleDC(screen);g_bufDC=CreateCompatibleDC(screen);
    if(g_capDC)g_capBmp=CreateCompatibleBitmap(screen,g_sw,g_sh);
    if(g_bufDC)g_bufBmp=CreateCompatibleBitmap(screen,g_tw,g_th);
    ReleaseDC(0,screen);
    if(!g_capDC||!g_bufDC||!g_capBmp||!g_bufBmp){clearRender();status(L("Error: no se pudieron crear las superficies GDI.","Error: the GDI surfaces could not be created."));return 0;}
    g_capOld=SelectObject(g_capDC,g_capBmp);g_bufOld=SelectObject(g_bufDC,g_bufBmp);
    g_output=CreateWindowExW(WS_EX_TOPMOST|WS_EX_TOOLWINDOW|WS_EX_NOACTIVATE|WS_EX_LAYERED,W("ProjectorScalerOutput"),W("ProjectorScaler salida"),WS_POPUP,(int)t.left,(int)t.top,g_tw,g_th,0,0,g_inst,0);
    if(!g_output){clearRender();status(L("Error al crear la ventana HDMI.","Error creating the HDMI window."));return 0;}
    SetLayeredWindowAttributes(g_output,0,255,LWA_ALPHA); /* a layered window is invisible until this */
    PatBlt(g_bufDC,0,0,g_tw,g_th,BLACKNESS);
    magCreate();
    SetWindowPos(g_output,HWND_TOPMOST,t.left,t.top,g_tw,g_th,SWP_NOACTIVATE|SWP_SHOWWINDOW);
    g_isRunning=1;g_isBlack=0;
    render();SetTimer(g_output,1,g_magShown?MAG_FRAME_MS:FRAME_MIN_MS,0);g_frameMs=g_magShown?MAG_FRAME_MS:FRAME_MIN_MS;
    refreshRunState();
    status(g_hotkey==1?L("Proyección activa. Parada de emergencia: Ctrl + Alt + P.","Projecting. Emergency stop: Ctrl + Alt + P."):
           g_hotkey==2?L("Proyección activa. Parada de emergencia: Ctrl + Alt + Mayús + P (Ctrl + Alt + P la usa otro programa).","Projecting. Emergency stop: Ctrl + Alt + Shift + P (another program uses Ctrl + Alt + P)."):
           L("Proyección activa. AVISO: no hay tecla de emergencia; detén con el botón Detener proyección.","Projecting. WARNING: no emergency key; stop with the Stop projection button."));
    if(g_runBasic){basicNormalize();basicChanged();}
    writeConfig();return 1;
}
#define IABS(v) ((v)<0?-(v):(v))
/* Which part of the frame is under (x,y), in target-screen pixels. */
static int hitFrame(int x,int y){
    int fx,fy,fw,fh;computeFrame(&fx,&fy,&fw,&fh);
    int g=MAX(12,handleHalf()*2),l=fx,t=fy,r=fx+fw,b=fy+fh;
    if(x<l-g||x>r+g||y<t-g||y>b+g)return HIT_NONE;
    int nl=IABS(x-l)<=g,nr=IABS(x-r)<=g,nt=IABS(y-t)<=g,nb=IABS(y-b)<=g;
    if(nt&&nl)return HIT_TL;
    if(nt&&nr)return HIT_TR;
    if(nb&&nl)return HIT_BL;
    if(nb&&nr)return HIT_BR;
    if(nl)return HIT_L;
    if(nr)return HIT_R;
    if(nt)return HIT_T;
    if(nb)return HIT_B;
    return (x>l&&x<r&&y>t&&y<b)?HIT_MOVE:HIT_NONE;
}
static const WCHAR* cursorFor(int hit){
    switch(hit){
    case HIT_MOVE:return CURSOR_ID(32646);              /* IDC_SIZEALL */
    case HIT_L:case HIT_R:return CURSOR_ID(32644);      /* IDC_SIZEWE */
    case HIT_T:case HIT_B:return CURSOR_ID(32645);      /* IDC_SIZENS */
    case HIT_TL:case HIT_BR:return CURSOR_ID(32642);    /* IDC_SIZENWSE */
    case HIT_TR:case HIT_BL:return CURSOR_ID(32643);    /* IDC_SIZENESW */
    }
    return IDC_ARROW;
}
/* New frame from the rectangle at drag start plus the mouse offset; always inside the screen. */
static void dragTo(int x,int y,int keepAspect){
    int l=g_dragRect[0],t=g_dragRect[1],r=g_dragRect[2],b=g_dragRect[3];
    int dx=x-(int)g_dragFrom.x,dy=y-(int)g_dragFrom.y,minW=MAX(32,g_tw/40),minH=MAX(24,g_th/40),h=g_drag;
    if(h==HIT_MOVE){
        dx=MAX(-l,MIN(dx,g_tw-r));dy=MAX(-t,MIN(dy,g_th-b));
        l+=dx;r+=dx;t+=dy;b+=dy;
    }else{
        if(h==HIT_L||h==HIT_TL||h==HIT_BL)l=MIN(MAX(0,l+dx),r-minW);
        if(h==HIT_R||h==HIT_TR||h==HIT_BR)r=MAX(MIN(g_tw,r+dx),l+minW);
        if(h==HIT_T||h==HIT_TL||h==HIT_TR)t=MIN(MAX(0,t+dy),b-minH);
        if(h==HIT_B||h==HIT_BL||h==HIT_BR)b=MAX(MIN(g_th,b+dy),t+minH);
        if(keepAspect&&h>=HIT_TL){
            /* Shift on a corner: keep the start proportions, anchored at the opposite corner. */
            double w0=g_dragRect[2]-g_dragRect[0],h0=g_dragRect[3]-g_dragRect[1],ar=w0/h0;
            double w=r-l,hh=b-t;
            if(w/w0>hh/h0)hh=w/ar;else w=hh*ar;
            int left=(h==HIT_TL||h==HIT_BL),up=(h==HIT_TL||h==HIT_TR);
            int ax=left?g_dragRect[2]:g_dragRect[0],ay=up?g_dragRect[3]:g_dragRect[1];
            double roomW=left?ax:g_tw-ax,roomH=up?ay:g_th-ay,k=1.0;
            if(w>roomW)k=MIN(k,roomW/w);
            if(hh>roomH)k=MIN(k,roomH/hh);
            w*=k;hh*=k;
            if(left){r=ax;l=ax-(int)(w+0.5);}else{l=ax;r=ax+(int)(w+0.5);}
            if(up){b=ay;t=ay-(int)(hh+0.5);}else{t=ay;b=ay+(int)(hh+0.5);}
        }
    }
    g_free[0]=(int)(((long long)l*FREE_UNIT+g_tw/2)/g_tw);g_free[1]=(int)(((long long)t*FREE_UNIT+g_th/2)/g_th);
    g_free[2]=(int)(((long long)r*FREE_UNIT+g_tw/2)/g_tw);g_free[3]=(int)(((long long)b*FREE_UNIT+g_th/2)/g_th);
    compose();
}
static LRESULT __stdcall outputProc(HWND hwnd,UINT msg,WPARAM w,LPARAM l){
    int mx=(int)(short)(l&0xffff),my=(int)(short)((l>>16)&0xffff);
    switch(msg){
    case WM_TIMER:if(w==1){
        DWORD t0=GetTickCount();render();
        if(g_magShown){if(g_frameMs!=MAG_FRAME_MS){g_frameMs=MAG_FRAME_MS;SetTimer(g_output,1,MAG_FRAME_MS,0);}}
        else adaptFrameRate(GetTickCount()-t0);
    }return 0;
    case WM_ERASEBKGND:return 1;
    case WM_PAINT:{PAINTSTRUCT ps;HDC dc=BeginPaint(hwnd,&ps);if(g_bufDC&&dc)BitBlt(dc,0,0,g_tw,g_th,g_bufDC,0,0,SRCCOPY);EndPaint(hwnd,&ps);return 0;}
    case WM_SETCURSOR:
        if(g_editFrame&&(l&0xffff)==HTCLIENT){
            POINT p;GetCursorPos(&p);
            int hit=g_drag?g_drag:hitFrame((int)p.x-g_tOrgX,(int)p.y-g_tOrgY);
            SetCursor(LoadCursorW(0,cursorFor(hit)));return 1;
        }
        break;
    case WM_LBUTTONDOWN:
        if(g_editFrame){
            int hit=hitFrame(mx,my);
            if(hit==HIT_NONE)return 0;
            /* Any drag turns the frame into a free one, starting from what is on screen now. */
            int fx,fy,fw,fh;computeFrame(&fx,&fy,&fw,&fh);
            g_dragRect[0]=fx;g_dragRect[1]=fy;g_dragRect[2]=fx+fw;g_dragRect[3]=fy+fh;
            g_aspectIndex=ASPECT_FREE;syncControls();
            g_dragFrom.x=mx;g_dragFrom.y=my;g_drag=hit;SetCapture(hwnd);
            dragTo(mx,my,0);
        }
        return 0;
    case WM_MOUSEMOVE:
        if(g_drag)dragTo(mx,my,(w&MK_SHIFT)!=0);
        return 0;
    case WM_LBUTTONUP:
        if(g_drag){
            dragTo(mx,my,(w&MK_SHIFT)!=0);
            g_drag=HIT_NONE;ReleaseCapture();
            g_iniError=0;writeConfig();
            status(g_iniError?iniErrorText():L("Encuadre libre guardado. Pulsa Terminar ajuste cuando acabes.","Free frame saved. Press Finish adjusting when you are done."));
        }
        return 0;
    case WM_CAPTURECHANGED:
        g_drag=HIT_NONE;return 0;
    }
    return DefWindowProcW(hwnd,msg,w,l);
}
static void applySettings(void){
    readControls();syncControls();g_iniError=0;writeConfig();if(g_isRunning)render();
    status(g_iniError?iniErrorText():L("Ajustes aplicados y guardados. Se actualiza la imagen en directo.","Settings applied and saved. The picture updates live."));
}

static void profileSection(const WCHAR* name,WCHAR* result){
    const WCHAR* prefix=W("Perfil_");int j=0,i=0;
    while(prefix[j] && j<80){result[j]=prefix[j];j++;}
    while(name[i] && j<80){
        WCHAR c=name[i++];
        if(c==']'||c=='['||c=='\\'||c=='/'||c==';'||c=='=')continue;
        result[j++]=c;
    }
    result[j]=0;
}
static void listProfiles(void){
    static WCHAR all[4096];all[0]=0;
    GetPrivateProfileSectionNamesW(all,4096,g_ini);
    SendMessageW(g_profile,CB_RESETCONTENT,0,0);
    for(int i=0;i<4000&&all[i];){
        if(all[i]=='P'&&all[i+1]=='e'&&all[i+2]=='r'&&all[i+3]=='f'&&all[i+4]=='i'&&all[i+5]=='l'&&all[i+6]=='_'){
            add(g_profile,all+i+7);
        }
        while(i<4000&&all[i])i++;
        i++;
    }
}
static void saveProfile(void){
    WCHAR name[64],sect[96];GetWindowTextW(g_profile,name,64);
    if(!name[0]){MessageBoxW(g_main,L("Escribe un nombre para guardar el perfil.","Type a name to save the profile."),W("ProjectorScaler"),0x40);return;}
    readControls();
    profileSection(name,sect);g_iniError=0;
    writeOne(sect,W("Zoom"),g_zoomValue);writeOne(sect,W("X"),g_xValue);writeOne(sect,W("Y"),g_yValue);
    writeOne(sect,W("Aspect"),g_aspectIndex);writeOne(sect,W("Fit"),g_fitIndex);
    writeOne(sect,W("CustomWidth"),g_cw);writeOne(sect,W("CustomHeight"),g_ch);
    writeOne(sect,W("Cursor"),g_showCursor);
    writeFree(sect);
    listProfiles();SetWindowTextW(g_profile,name);
    status(g_iniError?iniErrorText():L("Perfil personalizado guardado en el archivo INI.","Custom profile saved in the INI file."));
}
static void loadProfile(void){
    WCHAR name[64],sect[96],sentinel[12];GetWindowTextW(g_profile,name,64);
    if(!name[0]){status(L("Selecciona un perfil antes de cargarlo.","Choose a profile before loading it."));return;}
    profileSection(name,sect);
    GetPrivateProfileStringW(sect,W("Zoom"),W("no-existe"),sentinel,12,g_ini);
    if(sentinel[0]=='n'){status(L("No se encuentra el perfil seleccionado.","The selected profile was not found."));return;}
    g_zoomValue=(int)GetPrivateProfileIntW(sect,W("Zoom"),60,g_ini);
    g_xValue=(int)GetPrivateProfileIntW(sect,W("X"),50,g_ini);
    g_yValue=(int)GetPrivateProfileIntW(sect,W("Y"),50,g_ini);
    g_aspectIndex=(int)GetPrivateProfileIntW(sect,W("Aspect"),0,g_ini);
    g_fitIndex=(int)GetPrivateProfileIntW(sect,W("Fit"),0,g_ini);
    g_cw=(int)GetPrivateProfileIntW(sect,W("CustomWidth"),3,g_ini);
    g_ch=(int)GetPrivateProfileIntW(sect,W("CustomHeight"),2,g_ini);
    g_showCursor=(int)GetPrivateProfileIntW(sect,W("Cursor"),1,g_ini);
    if(g_aspectIndex==ASPECT_FREE)readFree(sect);
    g_zoomValue=MAX(20,MIN(g_zoomValue,100));g_xValue=MAX(0,MIN(g_xValue,100));g_yValue=MAX(0,MIN(g_yValue,100));
    g_aspectIndex=MAX(0,MIN(g_aspectIndex,ASPECT_FREE));g_fitIndex=MAX(0,MIN(g_fitIndex,2));
    g_cw=MAX(1,MIN(g_cw,1000));g_ch=MAX(1,MIN(g_ch,1000));
    syncControls();applySettings();if(!g_iniError)status(L("Perfil cargado y aplicado.","Profile loaded and applied."));
}

static void preset(int zoom,int aspect){g_zoomValue=zoom;g_xValue=50;g_yValue=50;g_aspectIndex=aspect;g_fitIndex=0;syncControls();applySettings();}
/* Picks the scale for this DPI, shrinking it if the panel would not fit the monitor's work
 * area (a 1366x768 laptop above its taskbar), then re-creates the fonts and moves every control. */
static void fitWindow(HWND hwnd,UINT dpi,const RECT* suggested){
    RECT wr={0},cr={0};GetWindowRect(hwnd,&wr);GetClientRect(hwnd,&cr);
    int frameW=(int)((wr.right-wr.left)-cr.right),frameH=(int)((wr.bottom-wr.top)-cr.bottom);
    if(g_dpi&&dpi!=g_dpi){frameW=frameW*(int)dpi/(int)g_dpi;frameH=frameH*(int)dpi/(int)g_dpi;}
    MONITORINFOEXW mi={0};mi.cbSize=sizeof(mi);
    RECT work={0,0,BASE_CW+frameW,BASE_CH+frameH};
    if(GetMonitorInfoW(MonitorFromWindow(hwnd,MONITOR_DEFAULTTONEAREST),&mi))work=mi.rcWork;
    int scale=(int)dpi*1000/96;
    int fitH=((int)(work.bottom-work.top)-frameH)*1000/BASE_CH;
    int fitW=((int)(work.right-work.left)-frameW)*1000/BASE_CW;
    scale=MIN(scale,MIN(fitH,fitW));
    g_scale=MAX(500,scale);g_dpi=dpi;

    HFONT old[4]={g_fontUi,g_fontTitle,g_fontHeader,g_fontTiny};
    g_fontUi=CreateFontW(S(-17),0,0,0,400,0,0,0,1,0,0,0,0,W("Segoe UI"));
    g_fontTitle=CreateFontW(S(-20),0,0,0,700,0,0,0,1,0,0,0,0,W("Segoe UI"));
    g_fontHeader=CreateFontW(S(-29),0,0,0,700,0,0,0,1,0,0,0,0,W("Segoe UI"));
    g_fontTiny=CreateFontW(S(-15),0,0,0,400,0,0,0,1,0,0,0,0,W("Segoe UI"));
    applyLayout();
    for(int i=0;i<4;i++)if(old[i])DeleteObject(old[i]);

    int w=S(BASE_CW)+frameW,h=S(BASE_CH)+frameH;
    int x=suggested?(int)suggested->left:(int)wr.left,y=suggested?(int)suggested->top:(int)wr.top;
    if(!suggested){ /* while dragging across monitors, follow Windows' suggested position */
        x=MAX((int)work.left,MIN(x,(int)work.right-w));y=MAX((int)work.top,MIN(y,(int)work.bottom-h));
    }
    SetWindowPos(hwnd,0,x,y,w,h,SWP_NOZORDER|SWP_NOACTIVATE);
    InvalidateRect(hwnd,0,1);
}
static void initResources(void){
    g_fontOverlay=CreateFontW(-168,0,0,0,800,0,0,0,1,0,0,0,0,W("Segoe UI"));
    g_fontOverlaySmall=CreateFontW(-30,0,0,0,650,0,0,0,1,0,0,0,0,W("Segoe UI"));
    g_brWhite=CreateSolidBrush(RGB3(255,255,255));g_brWindow=CreateSolidBrush(RGB3(239,243,248));
}
/* __DATE__ is "Nov 15 2026" (a single-digit day is padded with a space). */
static void buildDate(WCHAR* out,int cap){
    const char* d=__DATE__;const char* m="JanFebMarAprMayJunJulAugSepOctNovDec";
    const WCHAR* en[12]={W("Jan"),W("Feb"),W("Mar"),W("Apr"),W("May"),W("Jun"),W("Jul"),W("Aug"),W("Sep"),W("Oct"),W("Nov"),W("Dec")};
    int mon=1;for(int i=0;i<12;i++)if(d[0]==m[i*3]&&d[1]==m[i*3+1]&&d[2]==m[i*3+2])mon=i+1;
    int day=(d[4]==' '?0:(d[4]-'0')*10)+(d[5]-'0');
    WCHAR y[5]={(WCHAR)d[7],(WCHAR)d[8],(WCHAR)d[9],(WCHAR)d[10],0};
    out[0]=0;
    if(g_lang){appendi(out,day,cap);appendw(out,W(" "),cap);appendw(out,en[mon-1],cap);appendw(out,W(" "),cap);appendw(out,y,cap);}
    else{
        if(day<10)appendw(out,W("0"),cap);appendi(out,day,cap);appendw(out,W("/"),cap);
        if(mon<10)appendw(out,W("0"),cap);appendi(out,mon,cap);appendw(out,W("/"),cap);appendw(out,y,cap);
    }
}
static void creditTail(WCHAR* out,int cap){
    WCHAR date[32];buildDate(date,32);out[0]=0;
    appendw(out,W("  ·  v"),cap);appendw(out,(const WCHAR*)APP_VERSION,cap);
    appendw(out,L(", compilada el ",", built on "),cap);appendw(out,date,cap);
}
/* Small centred footer: "Desarrollado con Claude Code para <Colegio Mayor Mendel> · compilado el ...",
 * the college's name underlined and clickable. Remembers where the link was drawn. */
static void paintCredit(HDC dc,int left,int top,int right,int bottom){
    int px=MAX(9,S(11));
    HFONT plain=CreateFontW(-px,0,0,0,400,0,0,0,1,0,0,0,0,W("Segoe UI"));
    HFONT link=CreateFontW(-px,0,0,0,400,0,1,0,1,0,0,0,0,W("Segoe UI"));
    const WCHAR* head=L("Desarrollado con Claude Code para ","Developed with Claude Code for ");
    const WCHAR* name=W("Colegio Mayor Mendel");
    WCHAR tail[64];creditTail(tail,64);
    const WCHAR* part[3]={head,name,tail};HFONT font[3]={plain,link,plain};int w[3];
    HGDIOBJ old=SelectObject(dc,plain);
    for(int i=0;i<3;i++){RECT m={0,0,0,0};SelectObject(dc,font[i]);DrawTextW(dc,part[i],-1,&m,DT_CALCRECT|DT_SINGLELINE|DT_NOPREFIX);w[i]=(int)m.right;}
    int x=(left+right-(w[0]+w[1]+w[2]))/2;
    for(int i=0;i<3;i++){
        RECT r={x,top,x+w[i],bottom};SelectObject(dc,font[i]);
        SetTextColor(dc,i==1?RGB3(26,107,181):RGB3(96,110,128));
        DrawTextW(dc,part[i],-1,&r,DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);
        if(i==1){g_linkRect=r;}
        x+=w[i];
    }
    SelectObject(dc,old);DeleteObject(plain);DeleteObject(link);
}
static const WCHAR* hotkeyHint(void){
    return g_hotkey==1?L("Ctrl + Alt + P detiene la proyección al instante.","Ctrl + Alt + P stops the projection at once."):
           g_hotkey==2?L("Ctrl + Alt + Mayús + P detiene la proyección al instante.","Ctrl + Alt + Shift + P stops the projection at once."):
           L("Sin tecla de emergencia: detén con el botón.","No emergency key: stop with the button.");
}
/* Button texts and enabled states that follow the projection, after any rebuild. */
static void refreshRunState(void){
    if(g_start){SetWindowTextW(g_start,startLabel(g_isRunning));EnableWindow(g_start,!g_pending);}
    if(g_black){EnableWindow(g_black,g_isRunning);SetWindowTextW(g_black,g_isBlack?L("Reanudar imagen","Resume picture"):L("Pantalla negra","Black screen"));}
    if(g_editBtn){EnableWindow(g_editBtn,g_isRunning);SetWindowTextW(g_editBtn,g_editFrame?L("Terminar ajuste","Finish adjusting"):L("Ajustar con el ratón","Adjust with the mouse"));}
    if(g_hintLbl)SetWindowTextW(g_hintLbl,hotkeyHint());
    if(g_status&&g_statusText[0])SetWindowTextW(g_status,g_statusText);
}
static HWND g_menuBtn;
static void createHeader(void){
    ctrl(W("BUTTON"),L("Básico","Basic"),WS_TABSTOP|BS_OWNERDRAW,404,18,104,32,ID_UI_BASIC);
    ctrl(W("BUTTON"),L("Avanzado","Advanced"),WS_TABSTOP|BS_OWNERDRAW,508,18,104,32,ID_UI_ADV);
    ctrl(W("BUTTON"),W("ES"),WS_TABSTOP|BS_OWNERDRAW,628,18,40,32,ID_LANG_ES);
    ctrl(W("BUTTON"),W("EN"),WS_TABSTOP|BS_OWNERDRAW,668,18,40,32,ID_LANG_EN);
    /* Drawn as a gear; the text is for screen readers. */
    g_menuBtn=ctrl(W("BUTTON"),L("Opciones","Options"),WS_TABSTOP|BS_OWNERDRAW,716,18,40,32,ID_MENU);
}
static void createBasic(void){
    section(L("LO QUE SE VE EN EL PROYECTOR","WHAT THE PROJECTOR SHOWS"),40,90,690);
    lbl(L("Proyector  ·  arrastra el centro o las esquinas","Projector  ·  drag the middle or the corners"),40,126,420);
    g_preview=ctrl(W("ProjectorScalerPreview"),W(""),0,40,152,420,236,ID_PREVIEW);
    HWND d=ctrl(W("STATIC"),L("El proyector muestra lo mismo que tu pantalla. Arrastra el marco para encajar la imagen en la pared.",
                              "The projector shows the same as your screen. Drag the frame to fit the picture on the wall."),SS_LEFT,484,152,253,92,0);
    setFontKind(d,FONT_TINY);
    g_sizeLbl=ctrl(W("STATIC"),W(""),SS_LEFT,484,268,253,24,ID_SIZE);
    button(L("Centrar","Centre"),ID_CENTER,484,302,253);
    button(L("Ocupar todo","Fill screen"),ID_FILL,484,346,253);
    g_start=ctrl(W("BUTTON"),startLabel(0),WS_TABSTOP|BS_OWNERDRAW,40,436,250,44,ID_START);
    g_black=ctrl(W("BUTTON"),L("Pantalla negra","Black screen"),WS_TABSTOP|BS_OWNERDRAW,300,436,190,44,ID_BLACK);
    g_hintLbl=ctrl(W("STATIC"),W(""),SS_LEFT,504,437,233,44,0);setFontKind(g_hintLbl,FONT_TINY); /* two lines */
    g_status=ctrl(W("STATIC"),L("Pulsa Proyectar. Si Windows está en Duplicar, la app pasa un momento a Extender y vuelve a Duplicar al detener.",
                                "Press Project. If Windows is in Duplicate, the app switches to Extend for the projection and back to Duplicate when it stops."),0,40,486,697,44,ID_STATUS);
    setFontKind(g_status,FONT_TINY);
    updateSizeLabel();
}
static void createAdvanced(void){
    section(L("01   QUÉ PROYECTAR","01   WHAT TO PROJECT"),40,81,290);
    for(int i=0;i<3;i++)g_tabBtn[i]=ctrl(W("BUTTON"),W(""),WS_TABSTOP|BS_OWNERDRAW,336+i*135,80,129,32,ID_TAB0+i);
    g_tilesWnd=ctrl(W("ProjectorScalerTiles"),W(""),WS_VSCROLL|WS_TABSTOP,40,118,697,150,ID_TILES);
    g_srcHint=ctrl(W("STATIC"),W(""),SS_LEFT,40,276,697,24,ID_SRCHINT);setFontKind(g_srcHint,FONT_TINY);

    g_advFold0=g_layoutCount;
    section(L("02   PROYECTOR","02   PROJECTOR"),40,319,290);g_advSec[0]=g_layout[g_layoutCount-1].h;
    g_topoBtn=button(L("Pasar a EXTENDER","Switch to EXTEND"),ID_TOPOLOGY,336,317,190);
    g_modeLabel=ctrl(W("STATIC"),L("Comprobando configuración...","Checking display settings..."),0,536,315,201,42,ID_MODE); /* two lines */
    setFontKind(g_modeLabel,FONT_TINY);
    lbl(L("Destino:","Target:"),40,368,88);
    g_target=combo(ID_TARGET,130,363,260);
    button(L("IDENTIFICAR","IDENTIFY"),ID_IDENTIFY,400,362,160);
    button(L("Actualizar","Refresh"),ID_RELOAD,568,362,169);

    section(L("03   IMAGEN Y GEOMETRÍA","03   PICTURE AND GEOMETRY"),40,425,470);g_advSec[1]=g_layout[g_layoutCount-1].h;
    lbl(L("Tamaño (%)","Size (%)"),41,460,168);g_zoom=edit(ID_ZOOM,40,484,142);
    lbl(L("Horizontal (0-100)","Horizontal (0-100)"),232,460,188);g_x=edit(ID_X,231,484,142);
    lbl(L("Vertical (0-100)","Vertical (0-100)"),423,460,174);g_y=edit(ID_Y,422,484,142);
    lbl(L("Relación de aspecto","Aspect ratio"),40,526,216);g_aspect=combo(ID_ASPECT,40,552,191);
    add(g_aspect,L("16:9 · Pantalla ancha","16:9 · Widescreen"));add(g_aspect,W("16:10"));add(g_aspect,L("4:3 · Clásico","4:3 · Classic"));
    add(g_aspect,L("21:9 · Cine","21:9 · Cinema"));add(g_aspect,L("1:1 · Cuadrada","1:1 · Square"));add(g_aspect,L("Personalizada","Custom"));
    add(g_aspect,L("Libre (con el ratón)","Free (with the mouse)"));
    lbl(L("Ancho : Alto","Width : Height"),249,526,178);g_customW=edit(ID_CW,248,552,67);lbl(W(":"),322,554,21);g_customH=edit(ID_CH,342,552,67);
    lbl(L("Adaptación","Fit"),427,526,225);g_fit=combo(ID_FIT,427,552,310);
    add(g_fit,L("Ajustar · Sin deformar","Fit · No distortion"));add(g_fit,L("Rellenar · Con recorte","Fill · Crops"));add(g_fit,L("Estirar · Puede deformar","Stretch · May distort"));
    g_cursor=ctrl(W("BUTTON"),L("Mostrar puntero","Show pointer"),BS_AUTOCHECKBOX|WS_TABSTOP,40,595,160,29,ID_CURSOR);
    g_editBtn=button(L("Ajustar con el ratón","Adjust with the mouse"),ID_EDITFRAME,208,593,262);
    g_apply=button(L("Aplicar y guardar","Apply and save"),ID_APPLY,478,593,259);

    section(L("04   PERFILES DE PROYECCIÓN","04   PROJECTION PROFILES"),40,643,466);g_advSec[2]=g_layout[g_layoutCount-1].h;
    button(L("Cine 16:9","Cinema 16:9"),ID_CINEMA,40,678,211);
    button(L("Conferencia 4:3","Lecture 4:3"),ID_CONF,262,678,233);
    button(L("Imagen pequeña","Small picture"),ID_SMALL,507,678,230);
    lbl(L("Perfil personalizado:","Custom profile:"),40,723,186);
    g_profile=ctrl(W("COMBOBOX"),W(""),WS_TABSTOP|WS_VSCROLL|0x0002u,212,723,205,150,ID_PROFILE);
    button(L("Guardar perfil","Save profile"),ID_SAVE_PROFILE,428,720,149);
    button(L("Cargar perfil","Load profile"),ID_LOAD_PROFILE,588,720,149);

    g_advFold1=g_layoutCount;g_pickerOpen=0;
    g_start=button(startLabel(0),ID_START,40,784,343);
    g_black=button(L("Pantalla negra","Black screen"),ID_BLACK,400,784,337);
    g_restoreBox=ctrl(W("BUTTON"),L("Restaurar DUPLICAR al terminar (si se cambió automáticamente)","Restore DUPLICATE when finished (if it was changed automatically)"),BS_AUTOCHECKBOX|WS_TABSTOP,40,825,700,25,ID_RESTORE_CLONE);
    g_status=ctrl(W("STATIC"),L("Elige qué proyectar arriba y la pantalla del proyector como destino.","Choose what to project above and the projector screen as the target."),0,40,857,695,38,ID_STATUS);
    setFontKind(g_status,FONT_TINY);
    refreshMonitors();syncControls();listProfiles();
    SendMessageW(g_restoreBox,BM_SETCHECK,g_restoreClone?BST_CHECKED:0,0);
    updateModeLabel();
    fillTiles();
}
/* The panel is rebuilt, not shown and hidden, when the mode or the language changes. */
static void createUI(void){
    g_layoutCount=0;
    createHeader();
    if(g_uiMode==0)createBasic();else createAdvanced();
    refreshRunState();
}
static void destroyUI(void){
    for(int i=0;i<g_layoutCount;i++)if(g_layout[i].h)DestroyWindow(g_layout[i].h);
    g_layoutCount=0;
    g_source=g_target=g_zoom=g_x=g_y=g_aspect=g_customW=g_customH=g_fit=g_cursor=0;
    g_apply=g_start=g_black=g_status=g_profile=g_restoreBox=g_modeLabel=0;
    g_topoBtn=g_editBtn=g_preview=g_sizeLbl=g_hintLbl=g_menuBtn=0;
    KillTimer(g_main,ID_THUMBS);tilesClear();
    g_tilesWnd=g_srcHint=g_tabBtn[0]=g_tabBtn[1]=g_tabBtn[2]=0;
}
static void paintCard(HDC dc,int x,int y,int w,int h){RECT r={S(x),S(y),S(x+w),S(y+h)};FillRect(dc,&r,g_brWhite);}
static void boxOn(HDC dc,int l,int t,int r,int b,DWORD colour){RECT rc={l,t,r,b};HBRUSH br=CreateSolidBrush(colour);FillRect(dc,&rc,br);DeleteObject(br);}
/* ---- Advanced-mode source picker: three tabs of tiles, each with a still of its source ---- */
static void tilesClear(void){
    for(int i=0;i<g_tileCount;i++)if(g_tiles[i].thumb){DeleteObject(g_tiles[i].thumb);g_tiles[i].thumb=0;}
    g_tileCount=0;g_thumbNext=0;
}
/* Copies one source into a small bitmap. Windows draw themselves (PrintWindow), so a
 * covered window still gets a real picture; a minimised one gets none. */
static void makeThumb(int i){
    TILE* t=&g_tiles[i];t->thumbDone=1;
    HDC screen=GetDC(0);if(!screen)return;
    HDC src=screen,mem=0;HBITMAP memBmp=0;HGDIOBJ memOld=0;
    int sw=0,sh=0,sx=0,sy=0;
    if(t->kind==TILE_SCREEN){
        if(t->mon>=g_monitorCount){ReleaseDC(0,screen);return;}
        RECT r=g_monitors[t->mon].rcMonitor;sx=(int)r.left;sy=(int)r.top;sw=(int)(r.right-r.left);sh=(int)(r.bottom-r.top);
    }else{
        if(!IsWindow(t->hwnd)||IsIconic(t->hwnd)){ReleaseDC(0,screen);return;}
        RECT cr={0};GetClientRect(t->hwnd,&cr);sw=(int)cr.right;sh=(int)cr.bottom;
        if(sw<2||sh<2){ReleaseDC(0,screen);return;}
        mem=CreateCompatibleDC(screen);memBmp=CreateCompatibleBitmap(screen,sw,sh);
        if(!mem||!memBmp){if(memBmp)DeleteObject(memBmp);if(mem)DeleteDC(mem);ReleaseDC(0,screen);return;}
        memOld=SelectObject(mem,memBmp);
        if(!PrintWindow(t->hwnd,mem,PW_CLIENTONLY|PW_RENDERFULLCONTENT)){
            POINT o={0,0};ClientToScreen(t->hwnd,&o);BitBlt(mem,0,0,sw,sh,screen,(int)o.x,(int)o.y,SRCCOPY|CAPTUREBLT);
        }
        if(t->kind==TILE_TAB&&t->crop.right>t->crop.left&&t->crop.bottom>t->crop.top){
            sx=(int)t->crop.left;sy=(int)t->crop.top;sw=(int)(t->crop.right-t->crop.left);sh=(int)(t->crop.bottom-t->crop.top);
        }
        src=mem;
    }
    if(sw>1&&sh>1){
        int w=S(200),h=(int)((double)w*sh/sw+0.5);if(h>S(112)){h=S(112);w=(int)((double)h*sw/sh+0.5);}
        HDC dst=CreateCompatibleDC(screen);HBITMAP bmp=CreateCompatibleBitmap(screen,MAX(1,w),MAX(1,h));
        if(dst&&bmp){
            HGDIOBJ old=SelectObject(dst,bmp);
            SetStretchBltMode(dst,HALFTONE);SetBrushOrgEx(dst,0,0,0);
            StretchBlt(dst,0,0,w,h,src,sx,sy,sw,sh,SRCCOPY);
            SelectObject(dst,old);t->thumb=bmp;t->thumbW=MAX(1,w);t->thumbH=MAX(1,h);bmp=0;
        }
        if(bmp)DeleteObject(bmp);
        if(dst)DeleteDC(dst);
    }
    if(mem){SelectObject(mem,memOld);DeleteObject(memBmp);DeleteDC(mem);}
    ReleaseDC(0,screen);
}
/* Four tiles a row; the still keeps a fixed height so names line up. */
static void tileMetrics(int* cols,int* tw,int* th,int* rowH,int* gap,int* pad){
    RECT r={0};if(g_tilesWnd)GetClientRect(g_tilesWnd,&r);
    *pad=S(4);*gap=S(10);*cols=4;
    *tw=MAX(S(60),((int)r.right-2*(*pad)-*gap*(*cols-1))/(*cols));
    *th=S(78);*rowH=*th+S(46)+*gap;
}
static void tilesLayout(void){
    if(!g_tilesWnd)return;
    int cols,tw,th,rowH,gap,pad;tileMetrics(&cols,&tw,&th,&rowH,&gap,&pad);
    RECT r={0};GetClientRect(g_tilesWnd,&r);
    int rows=(g_tileCount+cols-1)/cols,content=rows*rowH-gap+2*pad;
    int maxScroll=MAX(0,content-(int)r.bottom);
    g_tileScroll=MAX(0,MIN(g_tileScroll,maxScroll));
    SCROLLINFO si={0};si.cbSize=sizeof(si);si.fMask=SIF_RANGE|SIF_PAGE|SIF_POS;
    si.nMin=0;si.nMax=MAX(0,content-1);si.nPage=(UINT)MAX(1,(int)r.bottom);si.nPos=g_tileScroll;
    SetScrollInfo(g_tilesWnd,SB_VERT,&si,1);
}
static int tileSelected(const TILE* t){
    if(t->kind==TILE_SCREEN)return !g_srcWindow&&t->mon==g_sourceIndex;
    if(t->kind==TILE_WINDOW)return g_srcWindow&&g_srcKind!=TILE_TAB&&t->hwnd==g_srcWindow;
    return g_srcWindow&&g_srcKind==TILE_TAB&&t->hwnd==g_srcWindow&&eqw(t->title,g_srcTabTitle);
}
static void tabsPopulate(void); /* browser tabs; defined with the UI Automation code */
static const WCHAR* tileHint(void){
    if(g_tileTab==0)return L("Se proyecta la pantalla entera, con todo lo que tenga abierto.",
                             "The whole screen is projected, with everything open on it.");
    if(g_tileTab==1)return L("Se proyecta sólo esa ventana, aunque otras la tapen. Minimizada, se congela la última imagen.",
                             "Only that window is projected, even when others cover it. Minimised, the last picture stays.");
    return L("Se proyecta el contenido de la pestaña, sin barras ni otras pestañas del navegador.",
             "The page in that tab is projected, without the browser's bars or other tabs.");
}
static void tilesTabLabels(void){
    const WCHAR* name[3]={L("Pantallas","Screens"),L("Ventanas","Windows"),L("Pestañas","Tabs")};
    int count[3]={g_monitorCount,g_winCount,g_tabCount};
    for(int i=0;i<3;i++){
        if(!g_tabBtn[i])continue;
        WCHAR b[48]={0};appendw(b,name[i],48);
        if(count[i]>=0){appendw(b,W("  ·  "),48);appendi(b,count[i],48);}
        SetWindowTextW(g_tabBtn[i],b);InvalidateRect(g_tabBtn[i],0,0);
    }
    if(g_srcHint)SetWindowTextW(g_srcHint,tileHint());
}
static void fillTiles(void){
    if(!g_tilesWnd)return;
    tilesClear();KillTimer(g_main,ID_THUMBS);
    g_winCount=0;EnumWindows(enumWin,0); /* the Ventanas count stays current on every tab */
    if(g_tileTab==0){
        for(int i=0;i<g_monitorCount&&g_tileCount<MAXTILES;i++){
            TILE* t=&g_tiles[g_tileCount++];memset(t,0,sizeof(*t));
            t->kind=TILE_SCREEN;t->mon=i;RECT r=g_monitors[i].rcMonitor;
            appendw(t->title,L("Pantalla ","Screen "),128);appendi(t->title,i+1,128);
            appendw(t->sub,(g_monitors[i].dwFlags&MONITORINFOF_PRIMARY)?L("Principal","Main"):L("Secundaria","Secondary"),64);
            appendw(t->sub,W(" · "),64);appendi(t->sub,(int)(r.right-r.left),64);appendw(t->sub,W("×"),64);appendi(t->sub,(int)(r.bottom-r.top),64);
        }
    }else if(g_tileTab==1){
        for(int i=0;i<g_winCount&&g_tileCount<MAXTILES;i++){
            TILE* t=&g_tiles[g_tileCount++];memset(t,0,sizeof(*t));
            t->kind=TILE_WINDOW;t->hwnd=g_winList[i];GetWindowTextW(t->hwnd,t->title,128);
            if(IsIconic(t->hwnd))appendw(t->sub,L("Minimizada","Minimised"),64);
            else{RECT cr={0};GetClientRect(t->hwnd,&cr);appendi(t->sub,(int)cr.right,64);appendw(t->sub,W("×"),64);appendi(t->sub,(int)cr.bottom,64);}
        }
    }else tabsPopulate();
    g_tileScroll=0;tilesLayout();tilesTabLabels();
    if(g_tileCount)SetTimer(g_main,ID_THUMBS,15,0);
    InvalidateRect(g_tilesWnd,0,0);
}
/* One still per timer tick, so a long list never freezes the panel. */
static void thumbStep(void){
    while(g_thumbNext<g_tileCount&&g_tiles[g_thumbNext].thumbDone)g_thumbNext++;
    if(g_thumbNext>=g_tileCount){KillTimer(g_main,ID_THUMBS);return;}
    makeThumb(g_thumbNext++);
    if(g_tilesWnd)InvalidateRect(g_tilesWnd,0,0);
}
/* Clicking a tab, even the open one, lists its sources again. */
/* Moves one panel control, keeping its base position for later DPI changes. */
static void moveCtl(HWND h,int x,int y,int w,int hh){
    for(int i=0;i<g_layoutCount;i++)if(g_layout[i].h==h){LAYOUT* e=&g_layout[i];e->x=x;e->y=y;e->w=w;e->hh=hh;}
    if(h)SetWindowPos(h,0,S(x),S(y),S(w),S(hh),SWP_NOZORDER|SWP_NOACTIVATE);
}
static void setPicker(int open){
    if(g_uiMode!=1||!g_tilesWnd||open==g_pickerOpen)return;
    g_pickerOpen=open;
    for(int i=g_advFold0;i<g_advFold1;i++){
        HWND h=g_layout[i].h;
        if(h==g_advSec[0]||h==g_advSec[1]||h==g_advSec[2])continue;
        ShowWindow(h,open?SW_HIDE:SW_SHOW);
    }
    moveCtl(g_advSec[0],40,open?645:319,open?340:290,29);
    moveCtl(g_advSec[1],40,open?691:425,open?340:470,29);
    moveCtl(g_advSec[2],40,open?737:643,open?340:466,29);
    moveCtl(g_tilesWnd,40,118,697,open?474:150);
    moveCtl(g_srcHint,40,open?600:276,697,24);
    InvalidateRect(g_main,0,1);
}
/* Would this list need the scroll bar in the normal, short picker? */
static int tilesNeedScroll(void){
    int cols,tw,th,rowH,gap,pad;tileMetrics(&cols,&tw,&th,&rowH,&gap,&pad);
    int rows=(g_tileCount+cols-1)/cols;
    return rows*rowH-gap+2*pad>S(150);
}
static void setTileTab(int tab){
    g_tileTab=tab<0||tab>2?0:tab;
    for(int i=0;i<3;i++)if(g_tabBtn[i])InvalidateRect(g_tabBtn[i],0,0);
    fillTiles();
    setPicker(tilesNeedScroll());
}
static int tabActivate(TILE* t); /* brings the browser tab to the front; with the UI Automation code */
static void selectTile(int i){
    if(i<0||i>=g_tileCount)return;
    TILE* t=&g_tiles[i];
    if(t->kind!=TILE_SCREEN&&!IsWindow(t->hwnd)){
        status(L("Esa ventana ya no existe: lista actualizada.","That window no longer exists: list refreshed."));fillTiles();return;
    }
    WCHAR title[128];copyw(title,t->title,128);
    if(t->kind!=TILE_TAB)tabRelease();
    else if(!tabActivate(t)){fillTiles();return;} /* tabActivate says why */
    g_srcKind=t->kind;
    if(t->kind==TILE_SCREEN){g_srcWindow=0;g_sourceIndex=t->mon;}
    else g_srcWindow=t->hwnd;
    InvalidateRect(g_tilesWnd,0,0);
    setPicker(0);
    WCHAR msg[220]={0};appendw(msg,L("Origen: ","Source: "),220);appendw(msg,title,220);
    if(g_isRunning){
        stopOutput();
        if(startOutput())appendw(msg,L("  ·  proyección reiniciada.","  ·  projection restarted."),220);
        else{msg[0]=0;appendw(msg,L("Proyección detenida: el nuevo origen no es válido. Elige otro y pulsa Iniciar.","Projection stopped: the new source is not valid. Choose another and press Start."),220);}
    }
    status(msg);
}
static int tileAt(int x,int y){
    int cols,tw,th,rowH,gap,pad;tileMetrics(&cols,&tw,&th,&rowH,&gap,&pad);
    x-=pad;y+=g_tileScroll-pad;if(x<0||y<0)return -1;
    int c=x/(tw+gap),r=y/rowH;
    if(c>=cols||x-c*(tw+gap)>tw||y-r*rowH>rowH-gap)return -1;
    int i=r*cols+c;return i<g_tileCount?i:-1;
}
static void drawTextIn(HDC dc,const WCHAR* s,int l,int t,int r,int b,HFONT f,DWORD colour,UINT fmt){
    RECT rc={l,t,r,b};HGDIOBJ old=SelectObject(dc,f);SetTextColor(dc,colour);DrawTextW(dc,s,-1,&rc,fmt);SelectObject(dc,old);
}
static void scrollTiles(int to){g_tileScroll=to;tilesLayout();InvalidateRect(g_tilesWnd,0,0);}
static LRESULT __stdcall tilesProc(HWND hwnd,UINT msg,WPARAM w,LPARAM l){
    int mx=(int)(short)(l&0xffff),my=(int)(short)((l>>16)&0xffff);
    switch(msg){
    case WM_ERASEBKGND:return 1;
    case WM_SIZE:tilesLayout();return 0;
    case WM_PAINT:{
        PAINTSTRUCT ps;HDC dc=BeginPaint(hwnd,&ps);RECT r={0};GetClientRect(hwnd,&r);
        HDC mem=CreateCompatibleDC(dc);HBITMAP bm=CreateCompatibleBitmap(dc,MAX(1,(int)r.right),MAX(1,(int)r.bottom));
        if(mem&&bm){
            HGDIOBJ old=SelectObject(mem,bm);
            boxOn(mem,0,0,(int)r.right,(int)r.bottom,RGB3(255,255,255));
            SetBkMode(mem,TRANSPARENT);
            int cols,tw,th,rowH,gap,pad;tileMetrics(&cols,&tw,&th,&rowH,&gap,&pad);
            for(int i=0;i<g_tileCount;i++){
                int x=pad+(i%cols)*(tw+gap),y=pad+(i/cols)*rowH-g_tileScroll,bottom=y+rowH-gap;
                if(y>r.bottom||bottom<0)continue;
                TILE* t=&g_tiles[i];
                if(tileSelected(t))boxOn(mem,x-S(3),y-S(3),x+tw+S(3),bottom+S(3),RGB3(26,107,181));
                boxOn(mem,x,y,x+tw,bottom,RGB3(233,239,247));
                int ax=x+S(6),ay=y+S(6),aw=tw-S(12),ah=th-S(6);
                boxOn(mem,ax,ay,ax+aw,ay+ah,RGB3(208,217,228));
                if(t->thumb){
                    int dw=aw,dh=(int)((double)aw*t->thumbH/t->thumbW+0.5);if(dh>ah){dh=ah;dw=(int)((double)ah*t->thumbW/t->thumbH+0.5);}
                    HDC tdc=CreateCompatibleDC(dc);
                    if(tdc){
                        HGDIOBJ to=SelectObject(tdc,t->thumb);SetStretchBltMode(mem,HALFTONE);SetBrushOrgEx(mem,0,0,0);
                        StretchBlt(mem,ax+(aw-dw)/2,ay+(ah-dh)/2,dw,dh,tdc,0,0,t->thumbW,t->thumbH,SRCCOPY);
                        SelectObject(tdc,to);DeleteDC(tdc);
                    }
                }else{
                    const WCHAR* ph=!t->thumbDone?W("…"):t->kind==TILE_TAB?L("En segundo plano","In background"):L("Sin vista previa","No preview");
                    drawTextIn(mem,ph,ax,ay,ax+aw,ay+ah,g_fontTiny,RGB3(96,110,128),DT_CENTER|DT_VCENTER|DT_SINGLELINE);
                }
                drawTextIn(mem,t->title,x+S(7),y+th+S(4),x+tw-S(7),y+th+S(24),g_fontTiny,RGB3(25,48,77),DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX);
                drawTextIn(mem,t->sub,x+S(7),y+th+S(23),x+tw-S(7),y+th+S(42),g_fontTiny,RGB3(96,110,128),DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX);
            }
            if(!g_tileCount){
                const WCHAR* e=g_tileTab==2?(g_tabError?g_tabError:L("No hay pestañas de Chrome ni de Edge abiertas.","No Chrome or Edge tabs are open.")):
                                            L("No hay nada que mostrar.","Nothing to show.");
                drawTextIn(mem,e,S(8),0,(int)r.right-S(8),(int)r.bottom,g_fontTiny,RGB3(96,110,128),DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
            }
            BitBlt(dc,0,0,(int)r.right,(int)r.bottom,mem,0,0,SRCCOPY);
            SelectObject(mem,old);
        }
        if(bm)DeleteObject(bm);
        if(mem)DeleteDC(mem);
        EndPaint(hwnd,&ps);return 0;
    }
    case WM_LBUTTONDOWN:SetFocus(hwnd);selectTile(tileAt(mx,my));return 0;
    case WM_MOUSEWHEEL:{
        int delta=(int)(short)((w>>16)&0xffff);
        int cols,tw,th,rowH,gap,pad;tileMetrics(&cols,&tw,&th,&rowH,&gap,&pad);
        scrollTiles(g_tileScroll-delta*rowH/(2*120));return 0;
    }
    case WM_VSCROLL:{
        int cols,tw,th,rowH,gap,pad;tileMetrics(&cols,&tw,&th,&rowH,&gap,&pad);
        RECT r={0};GetClientRect(hwnd,&r);int code=(int)(w&0xffff),to=g_tileScroll;
        if(code==SB_LINEUP)to-=rowH/3;
        else if(code==SB_LINEDOWN)to+=rowH/3;
        else if(code==SB_PAGEUP)to-=(int)r.bottom;
        else if(code==SB_PAGEDOWN)to+=(int)r.bottom;
        else if(code==SB_THUMBTRACK||code==SB_THUMBPOSITION)to=(int)((w>>16)&0xffff);
        scrollTiles(to);return 0;
    }
    }
    return DefWindowProcW(hwnd,msg,w,l);
}
/* ---- Browser tabs (Chrome, Edge) through UI Automation ----
 * The tab strip of a Chromium browser exposes each tab as a TabItem with a SelectionItem
 * pattern, and the page on show as a Document element. Choosing a tab selects it, and the
 * projection is the browser window cropped to that Document. The chosen TabItem element is
 * kept: it is the tab's identity, and the guard asks it every half second whether it is still
 * the selected tab. Anything that cannot be confirmed freezes the picture (fail closed). */
typedef struct {DWORD a;WORD b,c;BYTE d[8];} GUID_;
typedef struct {WORD vt,r1,r2,r3;LONG lVal;LONG pad1;void* pad2;} VARIANT_; /* 24 bytes on x64 */
static const GUID_ CLSID_CUIAutomation_={0xff48dba4,0x60ef,0x4201,{0xaa,0x87,0x54,0x10,0x3e,0xef,0x59,0x4e}};
static const GUID_ IID_IUIAutomation_={0x30cbe57d,0xd9d0,0x452a,{0xab,0x13,0x7a,0xc5,0xac,0x48,0x25,0xee}};
static const GUID_ IID_SelectionItem_={0xa8efa66a,0x0fda,0x421a,{0x91,0x94,0x38,0x02,0x1f,0x35,0x78,0xea}};
#define VTBL(o) (*(void***)(o))
#define UIA_CONTROLTYPE 30003
#define UIA_TABITEM 50019
#define UIA_DOCUMENT 50030
#define UIA_SELECTIONITEM 10010
#define SCOPE_DESCENDANTS 4
typedef unsigned long (__stdcall *ReleaseFn)(void*);
typedef LONG (__stdcall *FromHandleFn)(void*,HWND,void**);
typedef LONG (__stdcall *PropCondFn)(void*,int,VARIANT_,void**);
typedef LONG (__stdcall *FindAllFn)(void*,int,void*,void**);
typedef LONG (__stdcall *PatternAsFn)(void*,int,const GUID_*,void**);
typedef LONG (__stdcall *NameFn)(void*,WCHAR**);
typedef LONG (__stdcall *RectFn)(void*,RECT*);
typedef LONG (__stdcall *BoolFn)(void*,BOOL*);
typedef LONG (__stdcall *LengthFn)(void*,int*);
typedef LONG (__stdcall *GetElemFn)(void*,int,void**);
typedef LONG (__stdcall *SelectFn)(void*);
static void* g_uia;
static void* g_condTab;
static void* g_condDoc;
static void* g_tabElem;   /* the chosen TabItem */
static void* g_tabWinElem;/* the browser window, to look for the page again */
static void* g_tabDoc;    /* the page on show */
static UINT g_guardMs=500;
static int g_tabLostShown=0;

static void comRelease(void** p){if(*p){((ReleaseFn)VTBL(*p)[2])(*p);*p=0;}}
static void tabRelease(void){
    comRelease(&g_tabDoc);comRelease(&g_tabSel);comRelease(&g_tabElem);comRelease(&g_tabWinElem);
    if(g_main)KillTimer(g_main,ID_TABGUARD);
    g_tabFrozen=0;g_tabLostShown=0;g_tabExpect[0]=0;g_srcTabTitle[0]=0;
}
static int uiaInit(void){
    static int tried=0;
    if(g_uia)return 1;
    if(tried)return 0;
    tried=1;
    LONG hr=CoInitializeEx(0,2); /* COINIT_APARTMENTTHREADED; S_FALSE when already done */
    if(hr<0&&hr!=(LONG)0x80010106)return 0;
    if(CoCreateInstance(&CLSID_CUIAutomation_,0,1,&IID_IUIAutomation_,&g_uia)<0||!g_uia){g_uia=0;return 0;}
    VARIANT_ v;memset(&v,0,sizeof(v));v.vt=3;/* VT_I4 */
    v.lVal=UIA_TABITEM;((PropCondFn)VTBL(g_uia)[23])(g_uia,UIA_CONTROLTYPE,v,&g_condTab);
    v.lVal=UIA_DOCUMENT;((PropCondFn)VTBL(g_uia)[23])(g_uia,UIA_CONTROLTYPE,v,&g_condDoc);
    if(!g_condTab||!g_condDoc){comRelease(&g_condTab);comRelease(&g_condDoc);comRelease(&g_uia);return 0;}
    return 1;
}
/* 1 = Chrome, 2 = Edge, 0 = anything else. Electron apps share Chrome's window class, so the
 * process image decides. */
static int browserKind(HWND h){
    WCHAR cls[40]={0};GetClassNameW(h,cls,40);
    if(!eqw(cls,W("Chrome_WidgetWin_1")))return 0;
    DWORD pid=0;GetWindowThreadProcessId(h,&pid);if(!pid)return 0;
    HANDLE p=OpenProcess(0x1000,0,pid); /* PROCESS_QUERY_LIMITED_INFORMATION */
    if(!p)return 0;
    WCHAR path[300]={0};DWORD n=300;int kind=0;
    if(QueryFullProcessImageNameW(p,0,path,&n)){
        int i=(int)n;while(i>0&&path[i-1]!='\\')i--;
        WCHAR exe[40]={0};int j=0;
        for(;path[i]&&j<39;i++,j++){WCHAR c=path[i];exe[j]=(c>='A'&&c<='Z')?(WCHAR)(c+32):c;}
        if(eqw(exe,W("chrome.exe")))kind=1;else if(eqw(exe,W("msedge.exe")))kind=2;
    }
    CloseHandle(p);
    return kind;
}
static int findw(const WCHAR* s,const WCHAR* sub){
    for(int i=0;s[i];i++){int j=0;while(sub[j]&&s[i+j]==sub[j])j++;if(!sub[j])return i;}
    return -1;
}
/* Tab names can carry the browser's memory note ("… - Uso de memoria - 20,3 MB"). */
static void cleanTabName(const WCHAR* raw,WCHAR* out,int cap){
    copyw(out,raw,cap);
    const WCHAR* marks[4]={W("Uso de memoria"),W("Memory usage"),W("uso de memoria"),W("memory usage")};
    int cut=-1;
    for(int k=0;k<4;k++){int at=findw(out,marks[k]);if(at>=0&&(cut<0||at<cut))cut=at;}
    if(cut<0)return;
    int end=cut;
    while(end>0&&(out[end-1]==' '||out[end-1]=='-'||out[end-1]==':'||out[end-1]==0x2013||out[end-1]==0x2014))end--;
    if(end>0){out[end]=0;return;}
    copyw(out,raw,cap); /* the note came first: keep the whole name rather than nothing */
}
static int tabName(void* elem,WCHAR* out,int cap){
    WCHAR* b=0;out[0]=0;
    if(((NameFn)VTBL(elem)[23])(elem,&b)<0||!b)return 0;
    cleanTabName(b,out,cap);SysFreeString(b);return out[0]!=0;
}
static int isSelectedTab(void* elem){
    void* sel=0;BOOL on=0;
    if(((PatternAsFn)VTBL(elem)[14])(elem,UIA_SELECTIONITEM,&IID_SelectionItem_,&sel)<0||!sel)return 0;
    LONG hr=((BoolFn)VTBL(sel)[6])(sel,&on);comRelease(&sel);
    return hr>=0&&on;
}
/* A screen rectangle into hwnd's client coordinates, clamped to the client area. */
static int toClient(HWND hwnd,RECT s,RECT* out){
    POINT o={0,0};ClientToScreen(hwnd,&o);RECT cr={0};GetClientRect(hwnd,&cr);
    RECT r={s.left-o.x,s.top-o.y,s.right-o.x,s.bottom-o.y};
    if(r.left<0)r.left=0;
    if(r.top<0)r.top=0;
    if(r.right>cr.right)r.right=cr.right;
    if(r.bottom>cr.bottom)r.bottom=cr.bottom;
    if(r.right-r.left<16||r.bottom-r.top<16)return 0;
    *out=r;return 1;
}
/* The page on show: the largest on-screen Document under the window. Returns it AddRef'd. */
static void* findPage(void* winElem,HWND hwnd,RECT* crop){
    void* arr=0;int n=0;void* best=0;LONG bestArea=0;RECT bestRect={0};
    if(((FindAllFn)VTBL(winElem)[6])(winElem,SCOPE_DESCENDANTS,g_condDoc,&arr)<0||!arr)return 0;
    ((LengthFn)VTBL(arr)[3])(arr,&n);
    for(int i=0;i<n&&i<64;i++){
        void* e=0;if(((GetElemFn)VTBL(arr)[4])(arr,i,&e)<0||!e)continue;
        BOOL off=1;RECT r={0};
        if(((BoolFn)VTBL(e)[38])(e,&off)>=0&&!off&&((RectFn)VTBL(e)[43])(e,&r)>=0){
            LONG area=(r.right-r.left)*(r.bottom-r.top);
            if(area>bestArea){comRelease(&best);best=e;e=0;bestArea=area;bestRect=r;}
        }
        comRelease(&e);
    }
    comRelease(&arr);
    if(best&&!toClient(hwnd,bestRect,crop))comRelease(&best);
    return best;
}
static void tabsPopulate(void){
    g_tabCount=0;g_tabError=0;
    if(!uiaInit()){g_tabError=L("Windows no deja leer las pestañas (UI Automation no disponible).","Windows does not allow reading the tabs (UI Automation unavailable).");return;}
    for(int w=0;w<g_winCount&&g_tileCount<MAXTILES;w++){
        HWND h=g_winList[w];int kind=browserKind(h);if(!kind)continue;
        void* win=0;if(((FromHandleFn)VTBL(g_uia)[6])(g_uia,h,&win)<0||!win)continue;
        void* arr=0;int n=0;
        if(((FindAllFn)VTBL(win)[6])(win,SCOPE_DESCENDANTS,g_condTab,&arr)>=0&&arr){
            ((LengthFn)VTBL(arr)[3])(arr,&n);
            int iconic=IsIconic(h)!=0;
            for(int i=0;i<n&&g_tileCount<MAXTILES;i++){
                void* e=0;if(((GetElemFn)VTBL(arr)[4])(arr,i,&e)<0||!e)continue;
                TILE* t=&g_tiles[g_tileCount];memset(t,0,sizeof(*t));
                if(tabName(e,t->title,128)){
                    t->kind=TILE_TAB;t->hwnd=h;t->mon=i; /* position in the strip */
                    int on=isSelectedTab(e);
                    appendw(t->sub,kind==1?W("Chrome"):W("Edge"),64);
                    if(iconic)appendw(t->sub,L(" · minimizado"," · minimised"),64);
                    else if(on)appendw(t->sub,L(" · a la vista"," · on show"),64);
                    /* Only the tab on show has a picture: a background tab would show the other one. */
                    t->thumbDone=1;
                    if(on&&!iconic){void* doc=findPage(win,h,&t->crop);if(doc){t->thumbDone=0;comRelease(&doc);}}
                    g_tileCount++;g_tabCount++;
                }
                comRelease(&e);
            }
            comRelease(&arr);
        }
        comRelease(&win);
    }
}
/* The TabItem for this tile, looked up again: by its place in the strip, else by name. */
static void* findTabElem(void* win,const TILE* t){
    void* arr=0;int n=0;void* hit=0;
    if(((FindAllFn)VTBL(win)[6])(win,SCOPE_DESCENDANTS,g_condTab,&arr)<0||!arr)return 0;
    ((LengthFn)VTBL(arr)[3])(arr,&n);
    for(int pass=0;pass<2&&!hit;pass++)
        for(int i=0;i<n&&!hit;i++){
            if(pass==0&&i!=t->mon)continue;
            void* e=0;WCHAR name[128];
            if(((GetElemFn)VTBL(arr)[4])(arr,i,&e)<0||!e)continue;
            if(tabName(e,name,128)&&eqw(name,t->title)){hit=e;e=0;}
            comRelease(&e);
        }
    comRelease(&arr);
    return hit;
}
static int tabActivate(TILE* t){
    tabRelease();
    if(!uiaInit()){status(L("No se puede elegir la pestaña: UI Automation no disponible.","The tab cannot be chosen: UI Automation unavailable."));return 0;}
    if(((FromHandleFn)VTBL(g_uia)[6])(g_uia,t->hwnd,&g_tabWinElem)<0||!g_tabWinElem){tabRelease();status(L("No se pudo leer la ventana del navegador.","The browser window could not be read."));return 0;}
    g_tabElem=findTabElem(g_tabWinElem,t);
    if(!g_tabElem){tabRelease();status(L("Esa pestaña ya no está abierta: lista actualizada.","That tab is no longer open: list refreshed."));return 0;}
    if(((PatternAsFn)VTBL(g_tabElem)[14])(g_tabElem,UIA_SELECTIONITEM,&IID_SelectionItem_,&g_tabSel)<0||!g_tabSel){
        tabRelease();status(L("El navegador no deja elegir esa pestaña.","The browser does not allow choosing that tab."));return 0;
    }
    if(IsIconic(t->hwnd))ShowWindow(t->hwnd,4); /* SW_SHOWNOACTIVATE: a minimised browser draws nothing */
    ((SelectFn)VTBL(g_tabSel)[3])(g_tabSel);
    RECT crop={0};BOOL on=0;
    for(int k=0;k<12&&!g_tabDoc;k++){ /* the page can take a moment to come forward */
        if(((BoolFn)VTBL(g_tabSel)[6])(g_tabSel,&on)>=0&&on)g_tabDoc=findPage(g_tabWinElem,t->hwnd,&crop);
        if(!g_tabDoc)Sleep(60);
    }
    if(!g_tabDoc){tabRelease();status(L("La pestaña no llegó a mostrarse: prueba otra vez.","The tab did not come forward: try again."));return 0;}
    g_tabCrop=crop;GetWindowTextW(t->hwnd,g_tabExpect,256);
    copyw(g_srcTabTitle,t->title,128);g_tabFrozen=0;g_tabLostShown=0;g_guardMs=500;
    SetTimer(g_main,ID_TABGUARD,g_guardMs,0);
    return 1;
}
static void tabFreeze(const WCHAR* why){
    g_tabFrozen=1;
    if(!g_tabLostShown){g_tabLostShown=1;status(why);}
}
/* Every half second: is the chosen tab still the one on show? The UI thread also serves the
 * emergency key, so a hung browser is never asked, and slow answers slow the guard down. */
static void tabGuard(void){
    if(!(g_srcWindow&&g_srcKind==TILE_TAB&&g_tabSel)){tabRelease();return;}
    HWND h=g_srcWindow;
    if(!IsWindow(h)){tabFreeze(L("El navegador se ha cerrado: imagen congelada. Elige otro origen.","The browser was closed: picture frozen. Choose another source."));return;}
    if(IsHungAppWindow(h)){tabFreeze(L("El navegador no responde: imagen congelada.","The browser is not responding: picture frozen."));return;}
    DWORD t0=GetTickCount();
    BOOL on=0;LONG hr=((BoolFn)VTBL(g_tabSel)[6])(g_tabSel,&on);
    if(hr<0||!on){
        tabFreeze(L("La pestaña elegida ya no está a la vista: imagen congelada. Vuelve a ella en el navegador o elige otro origen.",
                    "The chosen tab is no longer on show: picture frozen. Go back to it in the browser or choose another source."));
    }else{
        RECT s={0},crop={0};int ok=0;
        if(g_tabDoc&&((RectFn)VTBL(g_tabDoc)[43])(g_tabDoc,&s)>=0)ok=toClient(h,s,&crop);
        if(!ok){comRelease(&g_tabDoc);g_tabDoc=findPage(g_tabWinElem,h,&crop);ok=g_tabDoc!=0;}
        if(!ok)tabFreeze(L("No se encuentra la página de la pestaña: imagen congelada.","The tab's page cannot be found: picture frozen."));
        else{
            g_tabCrop=crop;GetWindowTextW(h,g_tabExpect,256);
            if(g_tabFrozen&&g_tabLostShown)status(L("La pestaña elegida vuelve a estar a la vista: proyección reanudada.","The chosen tab is on show again: projection resumed."));
            g_tabFrozen=0;g_tabLostShown=0;
        }
    }
    DWORD took=GetTickCount()-t0;
    UINT want=took>400?2000:took>150?1000:500;
    if(want!=g_guardMs){g_guardMs=want;SetTimer(g_main,ID_TABGUARD,g_guardMs,0);}
}
/* ---- Start with Windows: a value under HKCU\...\Run, written only from the options menu ---- */
#define RUN_KEY W("Software\\Microsoft\\Windows\\CurrentVersion\\Run")
#define APPROVED_KEY W("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\StartupApproved\\Run")
#define RUN_VALUE W("ProjectorScaler")
#define PATHCAP 1100
static WCHAR g_exe[1024];   /* this EXE's full path */
static int g_autostarted=0; /* started by Windows at sign-in (--autostart) */
static WCHAR g_runHave[PATHCAP],g_runWant[PATHCAP];
static void runCommand(WCHAR* out){out[0]=0;appendw(out,W("\""),PATHCAP);appendw(out,g_exe,PATHCAP);appendw(out,W("\" --autostart"),PATHCAP);}
static int lowerw(int c){return c>='A'&&c<='Z'?c+32:c;}
static int eqwi(const WCHAR* a,const WCHAR* b){int i=0;while(a[i]&&b[i]&&lowerw(a[i])==lowerw(b[i]))i++;return a[i]==b[i];}
/* On only when the value starts this very EXE: the app is portable, an old copy's entry does not count. */
static int autostartOn(void){
    HKEY k=0;DWORD type=0,size=(DWORD)sizeof(g_runHave)-(DWORD)sizeof(WCHAR);int on=0;
    if(RegOpenKeyExW(HKEY_CURRENT_USER,RUN_KEY,0,KEY_QUERY_VALUE,&k)!=0)return 0;
    if(RegQueryValueExW(k,RUN_VALUE,0,&type,(BYTE*)g_runHave,&size)==0&&type==REG_SZ){
        g_runHave[size/sizeof(WCHAR)]=0;runCommand(g_runWant);on=eqwi(g_runHave,g_runWant);
    }
    RegCloseKey(k);
    if(on&&RegOpenKeyExW(HKEY_CURRENT_USER,APPROVED_KEY,0,KEY_QUERY_VALUE,&k)==0){
        BYTE flag[16];DWORD fs=sizeof(flag);
        if(RegQueryValueExW(k,RUN_VALUE,0,0,flag,&fs)==0&&fs>=1&&(flag[0]&1))on=0; /* switched off in Task Manager */
        RegCloseKey(k);
    }
    return on;
}
static int setAutostart(int on){
    HKEY k=0;LONG r;
    if(on){
        runCommand(g_runWant);int n=0;while(g_runWant[n])n++;
        if(RegCreateKeyExW(HKEY_CURRENT_USER,RUN_KEY,0,0,0,KEY_SET_VALUE,0,&k,0)!=0)return 0;
        r=RegSetValueExW(k,RUN_VALUE,0,REG_SZ,(const BYTE*)g_runWant,(DWORD)((n+1)*sizeof(WCHAR)));RegCloseKey(k);
        if(r!=0)return 0;
    }else if(RegOpenKeyExW(HKEY_CURRENT_USER,RUN_KEY,0,KEY_SET_VALUE,&k)==0){
        r=RegDeleteValueW(k,RUN_VALUE);RegCloseKey(k);
        if(r!=0&&r!=2)return 0; /* 2: there was none */
    }
    /* A switch-off left in Task Manager would keep it from starting: the choice made here wins. */
    if(RegOpenKeyExW(HKEY_CURRENT_USER,APPROVED_KEY,0,KEY_SET_VALUE,&k)==0){RegDeleteValueW(k,RUN_VALUE);RegCloseKey(k);}
    return 1;
}
static int checkUpdatesOn(void){return GetPrivateProfileIntW(W("Settings"),W("CheckUpdates"),1,g_ini)!=0;}

/* ---- Updates: the latest GitHub release, read and downloaded on a worker thread ----
 * Nothing is downloaded before the user says yes, and nothing is swapped while projecting. */
#define UPD_LATEST 0   /* this is the newest version */
#define UPD_NONE 1     /* no release published yet (404) */
#define UPD_NEW 2      /* a newer version with the EXE attached */
#define UPD_NOASSET 3  /* a newer version, its EXE not attached (yet) */
#define UPD_FAILED 4   /* offline, rate-limited, an answer that does not parse */
#define DL_OK 0
#define DL_NET 1
#define DL_WRITE 2     /* the program folder does not take the new file */
#define DL_BAD 3       /* what came down is not an x64 EXE */
#define DL_MAX (32u<<20)
static int g_updBusy=0,g_updManual=0,g_updRetried=0,g_updWait=0; /* g_updWait: 1 ask, 2 install, once the projection stops */
static char g_updTag[40];        /* the release tag, only [0-9A-Za-z._-] */
static WCHAR g_updVersion[40];   /* the tag without its v, for the messages */
static WCHAR g_newPath[PATHCAP],g_oldPath[PATHCAP];
static BYTE g_http[65536];       /* the worker thread's read buffer */
static char g_json[262144];static DWORD g_jsonLen;
static char g_assetUrl[200];
static HANDLE g_dlFile;static DWORD g_dlSize;static int g_dlTooBig;static BYTE g_dlHead[512];
typedef int (*SINK)(const BYTE*,DWORD);
static void appendc(char* out,const char* s,int cap){int j=0,i=0;while(j<cap-1&&out[j])j++;while(s[i]&&j<cap-1)out[j++]=s[i++];out[j]=0;}
static int findc(const char* s,DWORD n,const char* sub){
    for(DWORD i=0;i<n;i++){DWORD j=0;while(sub[j]&&i+j<n&&s[i+j]==sub[j])j++;if(!sub[j])return (int)i;}
    return -1;
}
/* GET https://host/path; the body goes to sink. The HTTP status, -1 on a network error, -2 if sink refused. */
static int httpGet(const WCHAR* host,const WCHAR* path,const WCHAR* headers,SINK sink){
    int code=-1;HINTERNET c=0,r=0;
    HINTERNET s=WinHttpOpen((const WCHAR*)(L"ProjectorScaler/" APP_VERSION),WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,0,0,0);
    if(!s)return -1;
    WinHttpSetTimeouts(s,10000,10000,15000,20000);
    c=WinHttpConnect(s,host,UPD_PORT,0);
    if(c)r=WinHttpOpenRequest(c,W("GET"),path,0,0,0,UPD_FLAGS);
    if(r&&WinHttpSendRequest(r,headers,headers?(DWORD)-1:0,0,0,0,0)&&WinHttpReceiveResponse(r,0)){ /* redirects are followed */
        DWORD st=0,len=sizeof(st);
        if(WinHttpQueryHeaders(r,WINHTTP_QUERY_STATUS_CODE|WINHTTP_QUERY_FLAG_NUMBER,0,&st,&len,0)){
            code=(int)st;
            while(code==200){
                DWORD got=0;
                if(!WinHttpReadData(r,g_http,sizeof(g_http),&got)){code=-1;break;}
                if(!got)break;
                if(!sink(g_http,got)){code=-2;break;}
            }
        }
    }
    if(r)WinHttpCloseHandle(r);
    if(c)WinHttpCloseHandle(c);
    WinHttpCloseHandle(s);
    return code;
}
static int jsonSink(const BYTE* p,DWORD n){
    for(DWORD i=0;i<n&&g_jsonLen<sizeof(g_json)-1;i++)g_json[g_jsonLen++]=(char)p[i]; /* the tail (release notes) may be cut */
    return 1;
}
static int fileSink(const BYTE* p,DWORD n){
    if(g_dlSize+n>DL_MAX){g_dlTooBig=1;return 0;}
    for(DWORD i=0;i<n&&g_dlSize+i<sizeof(g_dlHead);i++)g_dlHead[g_dlSize+i]=p[i];
    DWORD put=0;
    if(!WriteFile(g_dlFile,p,n,&put,0)||put!=n)return 0;
    g_dlSize+=n;return 1;
}
/* "v2.10.1" -> {2,10,1,0}; 0 if it is not a version. */
static int parseVersion(const WCHAR* s,int* v){
    int i=0,k=0;
    for(k=0;k<4;k++)v[k]=0;
    if(s[0]=='v'||s[0]=='V')i++;
    for(k=0;k<4;){
        int n=0,any=0;
        while(s[i]>='0'&&s[i]<='9'&&n<100000){n=n*10+s[i]-'0';i++;any=1;}
        if(!any)return 0;
        v[k++]=n;
        if(s[i]=='.'&&k<4){i++;continue;}
        break;
    }
    return s[i]==0;
}
static int newerThanMine(const WCHAR* tag){
    int a[4],b[4];
    if(!parseVersion(tag,a)||!parseVersion((const WCHAR*)APP_VERSION,b))return 0;
    for(int k=0;k<4;k++)if(a[k]!=b[k])return a[k]>b[k];
    return 0;
}
static DWORD __stdcall checkThread(void* arg){
    (void)arg;
    WPARAM result=UPD_FAILED;
    g_jsonLen=0;g_updTag[0]=0;
    int code=httpGet((const WCHAR*)API_HOST,(const WCHAR*)REPO_PATH,W("Accept: application/vnd.github+json\r\n"),jsonSink);
    if(code==404)result=UPD_NONE;
    else if(code==200){
        g_json[g_jsonLen]=0;
        int at=findc(g_json,g_jsonLen,"\"tag_name\""),n=0,closed=0;
        if(at>=0){
            DWORD i=(DWORD)at+10;
            while(i<g_jsonLen&&(g_json[i]==' '||g_json[i]==':'))i++;
            if(i<g_jsonLen&&g_json[i]=='"')for(i++;i<g_jsonLen&&n<(int)sizeof(g_updTag)-1;i++){
                char ch=g_json[i];
                if(ch=='"'){closed=1;break;}
                if(!((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||ch=='.'||ch=='-'||ch=='_'))break;
                g_updTag[n++]=ch;
            }
        }
        g_updTag[n]=0;
        if(n&&closed){
            WCHAR tag[40];int k=0,parsed[4];
            for(k=0;k<=n;k++)tag[k]=(WCHAR)(BYTE)g_updTag[k];
            copyw(g_updVersion,tag[0]=='v'||tag[0]=='V'?tag+1:tag,40);
            if(!parseVersion(tag,parsed))result=UPD_FAILED;
            else if(!newerThanMine(tag))result=UPD_LATEST;
            else{
                /* Only this repository's own asset, under its exact name, is ever downloaded. */
                g_assetUrl[0]=0;
                appendc(g_assetUrl,"\"https://github.com/cmmendel/ProjectorScaler/releases/download/",200);
                appendc(g_assetUrl,g_updTag,200);appendc(g_assetUrl,"/" ASSET_NAME "\"",200);
                result=findc(g_json,g_jsonLen,g_assetUrl)>=0?UPD_NEW:UPD_NOASSET;
            }
        }
    }
    PostMessageW(g_main,WM_UPDATE_CHECKED,result,0);
    return 0;
}
static int downloadLooksRight(void){
    if(g_dlSize<32768||g_dlHead[0]!='M'||g_dlHead[1]!='Z')return 0;
    DWORD pe=(DWORD)g_dlHead[0x3C]|((DWORD)g_dlHead[0x3D]<<8)|((DWORD)g_dlHead[0x3E]<<16)|((DWORD)g_dlHead[0x3F]<<24);
    if(pe+6>sizeof(g_dlHead))return 0;
    return g_dlHead[pe]=='P'&&g_dlHead[pe+1]=='E'&&!g_dlHead[pe+2]&&!g_dlHead[pe+3]&&g_dlHead[pe+4]==0x64&&g_dlHead[pe+5]==0x86; /* x64 */
}
static DWORD __stdcall fetchThread(void* arg){
    (void)arg;
    WPARAM result=DL_NET;
    g_dlSize=0;g_dlTooBig=0;
    g_dlFile=CreateFileW(g_newPath,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    if(g_dlFile==INVALID_HANDLE){PostMessageW(g_main,WM_UPDATE_FETCHED,DL_WRITE,0);return 0;}
    static WCHAR path[160];path[0]=0;
    WCHAR tag[40];int k=0;while(g_updTag[k]&&k<39){tag[k]=(WCHAR)(BYTE)g_updTag[k];k++;}tag[k]=0;
    appendw(path,W("/cmmendel/ProjectorScaler/releases/download/"),160);appendw(path,tag,160);appendw(path,W("/" ASSET_NAME),160);
    int code=httpGet((const WCHAR*)DL_HOST,path,0,fileSink);
    CloseHandle(g_dlFile);g_dlFile=0;
    if(code==200)result=downloadLooksRight()?DL_OK:DL_BAD;
    else if(code==-2)result=g_dlTooBig?DL_BAD:DL_WRITE;
    if(result!=DL_OK)DeleteFileW(g_newPath);
    PostMessageW(g_main,WM_UPDATE_FETCHED,result,0);
    return 0;
}
static int busyProjecting(void){return g_isRunning||g_pending;}
static void waitForProjection(int what){g_updWait=what;SetTimer(g_main,ID_UPDATE_WAIT,5000,0);}
static void offerReleasePage(const WCHAR* why){
    static WCHAR msg[700];msg[0]=0;appendw(msg,why,700);
    appendw(msg,L("\n\n¿Abrir la página de descargas en el navegador?","\n\nOpen the download page in the browser?"),700);
    if(MessageBoxW(g_main,msg,L("Actualizar ProjectorScaler","Update ProjectorScaler"),MB_YESNO|MB_ICONWARNING)==IDYES)
        ShellExecuteW(g_main,W("open"),(const WCHAR*)RELEASES_PAGE,0,0,1);
}
static void startCheck(int manual){
    if(g_updBusy)return;
    g_updBusy=1;g_updManual=manual;
    if(manual)status(L("Buscando actualizaciones...","Checking for updates..."));
    HANDLE t=CreateThread(0,0,checkThread,0,0,0);
    if(t)CloseHandle(t);
    else{g_updBusy=0;g_updManual=0;if(manual)status(L("No se pudo buscar actualizaciones.","Could not check for updates."));}
}
static void startFetch(void){
    static WCHAR line[200];line[0]=0;
    appendw(line,L("Descargando la versión ","Downloading version "),200);appendw(line,g_updVersion,200);appendw(line,W("..."),200);
    status(line);g_updBusy=1;
    HANDLE t=CreateThread(0,0,fetchThread,0,0,0);
    if(t)CloseHandle(t);
    else{g_updBusy=0;offerReleasePage(L("No se pudo iniciar la descarga.","The download could not start."));}
}
static void askToUpdate(void){
    if(busyProjecting()){waitForProjection(1);return;}
    static WCHAR msg[700];msg[0]=0;
    appendw(msg,L("Hay una versión nueva de ProjectorScaler: la ","A new version of ProjectorScaler is out: "),700);appendw(msg,g_updVersion,700);
    appendw(msg,L(" (tienes la "," (you have "),700);appendw(msg,(const WCHAR*)APP_VERSION,700);appendw(msg,W(")."),700);
    appendw(msg,L("\n\n¿Descargarla e instalarla ahora? ProjectorScaler se cerrará y volverá a abrirse con la versión nueva. Tus ajustes se conservan.",
                  "\n\nDownload and install it now? ProjectorScaler will close and open again with the new version. Your settings are kept."),700);
    if(MessageBoxW(g_main,msg,L("Actualización disponible","Update available"),MB_YESNO|MB_ICONQUESTION)!=IDYES){
        status(L("Actualización aplazada: se volverá a ofrecer en el próximo inicio.","Update postponed: it will be offered again at the next start."));
        return;
    }
    startFetch();
}
/* A running EXE can be renamed but not overwritten: this copy steps aside as .old,
 * the download takes its name, the new copy starts and this one closes. */
static void installUpdate(void){
    if(busyProjecting()){
        status(L("La versión nueva está descargada: se instalará al detener la proyección.","The new version is downloaded: it will be installed when the projection stops."));
        waitForProjection(2);return;
    }
    DeleteFileW(g_oldPath);
    if(!MoveFileExW(g_exe,g_oldPath,MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH)){
        DeleteFileW(g_newPath);status(L("Actualización cancelada.","Update cancelled."));
        offerReleasePage(L("No se pudo sustituir el programa: la carpeta no admite cambios.","The program could not be replaced: its folder does not allow changes."));return;
    }
    if(!MoveFileExW(g_newPath,g_exe,MOVEFILE_WRITE_THROUGH)){
        MoveFileExW(g_oldPath,g_exe,MOVEFILE_WRITE_THROUGH);DeleteFileW(g_newPath);status(L("Actualización cancelada.","Update cancelled."));
        offerReleasePage(L("No se pudo colocar la versión nueva en la carpeta del programa.","The new version could not be put in the program folder."));return;
    }
    UnregisterHotKey(g_main,ID_EMERGENCY); /* the new copy registers the emergency key itself */
    /* CreateProcess, not ShellExecute: ShellExecute may hand the launch to a thread that dies with this process. */
    static WCHAR cmd[PATHCAP];cmd[0]=0;appendw(cmd,W("\""),PATHCAP);appendw(cmd,g_exe,PATHCAP);appendw(cmd,W("\""),PATHCAP);
    STARTUPINFOW_ si={0};si.cb=sizeof(si);PROCESS_INFORMATION_ pi={0};
    if(CreateProcessW(g_exe,cmd,0,0,0,0,0,0,&si,&pi)){CloseHandle(pi.hThread);CloseHandle(pi.hProcess);}
    else MessageBoxW(g_main,L("ProjectorScaler se ha actualizado. Ábrelo de nuevo.","ProjectorScaler has been updated. Open it again."),W("ProjectorScaler"),0x40);
    DestroyWindow(g_main);
}
static void onUpdateChecked(int result){
    int manual=g_updManual;
    g_updBusy=0;g_updManual=0;
    if(result==UPD_NEW){askToUpdate();return;}
    if(!manual){ /* the check at startup stays silent unless there is something to install */
        if(result==UPD_FAILED&&!g_updRetried){g_updRetried=1;SetTimer(g_main,ID_UPDATE_CHECK,120000,0);} /* the network may not be up yet */
        return;
    }
    static WCHAR msg[400];msg[0]=0;
    if(result==UPD_LATEST){
        appendw(msg,L("Ya tienes la última versión (","You have the latest version ("),400);appendw(msg,(const WCHAR*)APP_VERSION,400);appendw(msg,W(")."),400);
        status(msg);MessageBoxW(g_main,msg,W("ProjectorScaler"),0x40);
    }else if(result==UPD_NONE){
        status(L("Aún no hay versiones publicadas en GitHub.","No version has been published on GitHub yet."));
        MessageBoxW(g_main,L("Aún no hay versiones publicadas en GitHub.","No version has been published on GitHub yet."),W("ProjectorScaler"),0x40);
    }else if(result==UPD_NOASSET){
        appendw(msg,L("La versión ","Version "),400);appendw(msg,g_updVersion,400);
        appendw(msg,L(" está publicada, pero todavía sin el programa para descargar."," is published, but without the program to download yet."),400);
        status(msg);offerReleasePage(msg);
    }else{
        status(L("No se pudo consultar GitHub.","GitHub could not be reached."));
        MessageBoxW(g_main,L("No se pudo consultar GitHub. Comprueba la conexión a Internet e inténtalo más tarde.","GitHub could not be reached. Check the Internet connection and try again later."),W("ProjectorScaler"),MB_ICONWARNING);
    }
}
static void onUpdateFetched(int result){
    g_updBusy=0;
    if(result==DL_OK){installUpdate();return;}
    status(L("Actualización cancelada.","Update cancelled."));
    offerReleasePage(result==DL_WRITE?L("No se pudo guardar la versión nueva junto al programa: la carpeta no admite escritura.","The new version could not be saved next to the program: the folder is read-only."):
                     result==DL_BAD?L("Lo descargado no es un programa válido y no se ha instalado.","The download is not a valid program and was not installed."):
                     L("No se pudo descargar la versión nueva.","The new version could not be downloaded."));
}
static void showOptionsMenu(void){
    HMENU m=CreatePopupMenu();
    if(!m)return;
    AppendMenuW(m,MF_STRING|(autostartOn()?MF_CHECKED:0),ID_M_AUTOSTART,L("Iniciar con Windows","Start with Windows"));
    AppendMenuW(m,MF_STRING|(checkUpdatesOn()?MF_CHECKED:0),ID_M_CHECKUPD,L("Buscar actualizaciones al iniciar","Check for updates at startup"));
    AppendMenuW(m,MF_STRING|(g_updBusy?MF_GRAYED:0),ID_M_CHECKNOW,L("Buscar actualizaciones ahora","Check for updates now"));
    AppendMenuW(m,MF_SEPARATOR,0,0);
    AppendMenuW(m,MF_STRING|MF_GRAYED,0,(const WCHAR*)(L"ProjectorScaler " APP_VERSION));
    RECT r={0,0,0,0};GetWindowRect(g_menuBtn,&r);
    int cmd=(int)TrackPopupMenu(m,TPM_RIGHTALIGN|TPM_RETURNCMD,(int)r.right,(int)r.bottom,0,g_main,0);
    DestroyMenu(m);
    if(cmd==ID_M_AUTOSTART){
        int on=!autostartOn();
        if(!setAutostart(on))MessageBoxW(g_main,L("Windows no permitió cambiar el inicio automático.","Windows did not allow changing the automatic start."),W("ProjectorScaler"),MB_ICONWARNING);
        else status(on?L("ProjectorScaler se abrirá al iniciar sesión en Windows.","ProjectorScaler will open when you sign in to Windows."):
                       L("ProjectorScaler ya no se abrirá al iniciar sesión.","ProjectorScaler will no longer open when you sign in."));
    }else if(cmd==ID_M_CHECKUPD){
        int on=!checkUpdatesOn();
        g_iniError=0;writeOne(W("Settings"),W("CheckUpdates"),on);
        if(g_iniError)status(iniErrorText());
        else status(on?L("Se buscarán actualizaciones en GitHub al iniciar.","Updates will be checked on GitHub at startup."):
                       L("Ya no se buscarán actualizaciones al iniciar.","Updates will no longer be checked at startup."));
    }else if(cmd==ID_M_CHECKNOW)startCheck(1);
}
static void paintMain(HWND hwnd){
    PAINTSTRUCT ps;HDC dc=BeginPaint(hwnd,&ps);RECT r={0};GetClientRect(hwnd,&r);
    FillRect(dc,&r,g_brWindow);
    RECT banner={0,0,r.right,S(68)};HBRUSH navy=CreateSolidBrush(RGB3(25,48,77));FillRect(dc,&banner,navy);DeleteObject(navy);
    SetBkMode(dc,TRANSPARENT);SetTextColor(dc,RGB3(255,255,255));
    HGDIOBJ oldFont=SelectObject(dc,g_fontHeader);
    RECT hdr={S(40),S(5),S(396),S(45)};DrawTextW(dc,W("ProjectorScaler"),-1,&hdr,0);
    SelectObject(dc,g_fontTiny);RECT subtitle={S(42),S(44),S(396),S(65)};SetTextColor(dc,RGB3(200,222,240));
    DrawTextW(dc,L("Control de proyección · Windows 10/11 · Portátil","Projection control · Windows 10/11 · Portable"),-1,&subtitle,0);
    if(g_uiMode==0){
        paintCard(dc,20,80,737,330);paintCard(dc,20,420,737,116);
    }else{
        if(g_pickerOpen){
            paintCard(dc,20,75,737,558);paintCard(dc,20,639,737,40);paintCard(dc,20,685,737,40);paintCard(dc,20,731,737,40);paintCard(dc,20,777,737,122);
            SelectObject(dc,g_fontTiny);SetTextColor(dc,RGB3(96,110,128));
            for(int i=0;i<3;i++){RECT t={S(400),S(639+46*i),S(737),S(679+46*i)};
                DrawTextW(dc,L("Pulsa para mostrar","Click to show"),-1,&t,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);}
        }else{
            paintCard(dc,20,75,737,232);paintCard(dc,20,313,737,100);paintCard(dc,20,419,737,216);paintCard(dc,20,642,737,129);paintCard(dc,20,777,737,122);
        }
    }
    paintCredit(dc,S(20),S(BASE_CH-26),S(757),S(BASE_CH-8));
    SelectObject(dc,oldFont);
    EndPaint(hwnd,&ps);
}
static int isHeaderButton(int id){return id==ID_UI_BASIC||id==ID_UI_ADV||id==ID_LANG_ES||id==ID_LANG_EN||id==ID_MENU;}
static void drawButton(const void* data){
    typedef struct {UINT CtlType;UINT CtlID;UINT itemID;UINT itemAction;UINT itemState;HWND hwndItem;HDC hDC;RECT rcItem;ULONG_PTR itemData;} DRAWITEM;
    const DRAWITEM* d=(const DRAWITEM*)data;
    if(!d||!d->hDC)return;
    int id=(int)d->CtlID,disabled=(d->itemState&ODS_DISABLED)!=0,header=isHeaderButton(id);
    DWORD bg=RGB3(233,239,247),fg=RGB3(37,61,91);
    if(header){
        int on=(id==ID_UI_BASIC&&g_uiMode==0)||(id==ID_UI_ADV&&g_uiMode==1)||(id==ID_LANG_ES&&g_lang==0)||(id==ID_LANG_EN&&g_lang==1);
        bg=on?RGB3(255,255,255):RGB3(44,72,107);fg=on?RGB3(25,48,77):RGB3(200,222,240);
    }
    else if(id>=ID_TAB0&&id<ID_TAB0+3){int on=id-ID_TAB0==g_tileTab;bg=on?RGB3(25,48,77):RGB3(233,239,247);fg=on?RGB3(255,255,255):RGB3(37,61,91);}
    else if(id==ID_START){bg=RGB3(26,107,181);fg=RGB3(255,255,255);}
    else if(id==ID_IDENTIFY){bg=RGB3(24,128,139);fg=RGB3(255,255,255);}
    else if(id==ID_BLACK){bg=RGB3(52,63,80);fg=RGB3(255,255,255);}
    else if(id==ID_APPLY){bg=RGB3(209,226,245);}
    else if(id==ID_EDITFRAME&&g_editFrame){bg=RGB3(245,166,35);fg=RGB3(19,46,78);}
    if(disabled){bg=RGB3(214,221,228);fg=RGB3(131,140,150);}
    if(d->itemState&ODS_SELECTED && !disabled){bg=RGB3(61,86,112);fg=RGB3(255,255,255);}
    /* Paint behind the rounded corners in the colour of what is underneath. */
    if(header)boxOn(d->hDC,d->rcItem.left,d->rcItem.top,d->rcItem.right,d->rcItem.bottom,RGB3(25,48,77));
    else FillRect(d->hDC,&d->rcItem,g_brWhite);
    HBRUSH brush=CreateSolidBrush(bg),old=(HBRUSH)SelectObject(d->hDC,brush);
    HGDIOBJ oldPen=SelectObject(d->hDC,GetStockObject(8)); /* NULL_PEN */
    RoundRect(d->hDC,d->rcItem.left,d->rcItem.top,d->rcItem.right,d->rcItem.bottom,11,11);
    SelectObject(d->hDC,oldPen);SelectObject(d->hDC,old);DeleteObject(brush);
    RECT r=d->rcItem;WCHAR label[128]={0};GetWindowTextW(d->hwndItem,label,128);
    HFONT gear=0;
    if(id==ID_MENU){gear=CreateFontW(S(-17),0,0,0,400,0,0,0,1,0,0,0,0,W("Segoe MDL2 Assets"));label[0]=0xE713;label[1]=0;} /* Settings */
    HGDIOBJ oldFont=SelectObject(d->hDC,gear?gear:g_fontUi);SetBkMode(d->hDC,TRANSPARENT);SetTextColor(d->hDC,fg);
    DrawTextW(d->hDC,label,-1,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    SelectObject(d->hDC,oldFont);if(gear)DeleteObject(gear);
    if(d->itemState&ODS_FOCUS){RECT f={r.left+S(4),r.top+S(4),r.right-S(4),r.bottom-S(4)};DrawFocusRect(d->hDC,&f);}
}
/* ---- Basic-mode preview: the projector, with the frame where the picture lands ---- */
static void previewInner(HWND h,RECT* in){
    RECT r={0};GetClientRect(h,&r);
    double sa,tw,th;basicSizes(&sa,&tw,&th);
    int W0=(int)r.right-4,H0=(int)r.bottom-4;double ta=tw/th;
    int w=W0,hh=(int)(W0/ta+0.5);if(hh>H0){hh=H0;w=(int)(H0*ta+0.5);}
    in->left=(r.right-w)/2;in->top=(r.bottom-hh)/2;in->right=in->left+w;in->bottom=in->top+hh;
}
static void previewFrame(const RECT* in,RECT* f){
    int w=(int)(in->right-in->left),h=(int)(in->bottom-in->top);
    f->left=in->left+g_basicFree[0]*w/FREE_UNIT;f->right=in->left+g_basicFree[2]*w/FREE_UNIT;
    f->top=in->top+g_basicFree[1]*h/FREE_UNIT;f->bottom=in->top+g_basicFree[3]*h/FREE_UNIT;
}
static int previewHit(HWND h,int x,int y){
    RECT in,f;previewInner(h,&in);previewFrame(&in,&f);
    int g=S(10);
    int nl=IABS(x-(int)f.left)<=g,nr=IABS(x-(int)f.right)<=g,nt=IABS(y-(int)f.top)<=g,nb=IABS(y-(int)f.bottom)<=g;
    if(nt&&nl)return HIT_TL;
    if(nt&&nr)return HIT_TR;
    if(nb&&nl)return HIT_BL;
    if(nb&&nr)return HIT_BR;
    return (x>f.left&&x<f.right&&y>f.top&&y<f.bottom)?HIT_MOVE:HIT_NONE;
}
/* Move, or resize from a corner with the opposite corner fixed; the shape never changes. */
static void previewDrag(HWND h,int x,int y){
    RECT in;previewInner(h,&in);
    double iw=(double)(in.right-in.left),ih=(double)(in.bottom-in.top);if(iw<1||ih<1)return;
    double du=(x-(int)g_pFrom.x)*FREE_UNIT/iw,dv=(y-(int)g_pFrom.y)*FREE_UNIT/ih;
    double l=g_pStart[0],t=g_pStart[1],r=g_pStart[2],b=g_pStart[3];
    if(g_pDrag==HIT_MOVE){basicSet(l+du,t+dv,r-l,b-t);basicChanged();return;}
    int left=(g_pDrag==HIT_TL||g_pDrag==HIT_BL),up=(g_pDrag==HIT_TL||g_pDrag==HIT_TR);
    double ax=left?r:l,ay=up?b:t,px=(left?l:r)+du,py=(up?t:b)+dv;
    double a=basicRatio(),w=left?ax-px:px-ax,hh=up?ay-py:py-ay;
    w=MAX(w,600.0);hh=MAX(hh,600.0/a);
    if(w/a>hh)hh=w/a;else w=hh*a;
    double roomW=left?ax:FREE_UNIT-ax,roomH=up?ay:FREE_UNIT-ay,k=1.0;
    if(w>roomW)k=MIN(k,roomW/w);
    if(hh>roomH)k=MIN(k,roomH/hh);
    w*=k;hh*=k;
    basicSet(left?ax-w:ax,up?ay-hh:ay,w,hh);
    basicChanged();
}
static LRESULT __stdcall previewProc(HWND hwnd,UINT msg,WPARAM w,LPARAM l){
    int mx=(int)(short)(l&0xffff),my=(int)(short)((l>>16)&0xffff);
    switch(msg){
    case WM_ERASEBKGND:return 1;
    case WM_PAINT:{
        PAINTSTRUCT ps;HDC dc=BeginPaint(hwnd,&ps);RECT r={0};GetClientRect(hwnd,&r);
        HDC mem=CreateCompatibleDC(dc);HBITMAP bm=CreateCompatibleBitmap(dc,(int)r.right,(int)r.bottom);
        if(mem&&bm){
            HGDIOBJ old=SelectObject(mem,bm);
            boxOn(mem,0,0,(int)r.right,(int)r.bottom,RGB3(233,239,247));
            RECT in,f;previewInner(hwnd,&in);previewFrame(&in,&f);
            boxOn(mem,(int)in.left,(int)in.top,(int)in.right,(int)in.bottom,RGB3(14,18,24));
            int fw=(int)(f.right-f.left),fh=(int)(f.bottom-f.top);
            if(g_monitorCount>0&&fw>1&&fh>1){
                RECT s=g_monitors[basicSourceIndex()].rcMonitor;HDC scr=GetDC(0);
                if(scr){SetStretchBltMode(mem,HALFTONE);SetBrushOrgEx(mem,0,0,0);
                    StretchBlt(mem,(int)f.left,(int)f.top,fw,fh,scr,(int)s.left,(int)s.top,(int)(s.right-s.left),(int)(s.bottom-s.top),SRCCOPY);ReleaseDC(0,scr);}
            }
            DWORD amber=RGB3(245,166,35);int b=MAX(2,S(2));
            boxOn(mem,(int)f.left,(int)f.top,(int)f.right,(int)f.top+b,amber);boxOn(mem,(int)f.left,(int)f.bottom-b,(int)f.right,(int)f.bottom,amber);
            boxOn(mem,(int)f.left,(int)f.top,(int)f.left+b,(int)f.bottom,amber);boxOn(mem,(int)f.right-b,(int)f.top,(int)f.right,(int)f.bottom,amber);
            int hh=S(5),xs[2]={(int)f.left,(int)f.right},ys[2]={(int)f.top,(int)f.bottom};
            for(int i=0;i<2;i++)for(int j=0;j<2;j++){
                boxOn(mem,xs[i]-hh-1,ys[j]-hh-1,xs[i]+hh+1,ys[j]+hh+1,amber);
                boxOn(mem,xs[i]-hh+1,ys[j]-hh+1,xs[i]+hh-1,ys[j]+hh-1,RGB3(255,255,255));
            }
            BitBlt(dc,0,0,(int)r.right,(int)r.bottom,mem,0,0,SRCCOPY);
            SelectObject(mem,old);
        }
        if(bm)DeleteObject(bm);if(mem)DeleteDC(mem);
        EndPaint(hwnd,&ps);return 0;
    }
    case WM_SETCURSOR:
        if((l&0xffff)==HTCLIENT){
            POINT p;GetCursorPos(&p);POINT o={0,0};ClientToScreen(hwnd,&o);
            int hit=g_pDrag?g_pDrag:previewHit(hwnd,(int)(p.x-o.x),(int)(p.y-o.y));
            SetCursor(LoadCursorW(0,cursorFor(hit)));return 1;
        }
        break;
    case WM_LBUTTONDOWN:{
        int hit=previewHit(hwnd,mx,my);if(hit==HIT_NONE)return 0;
        g_pDrag=hit;g_pFrom.x=mx;g_pFrom.y=my;for(int i=0;i<4;i++)g_pStart[i]=g_basicFree[i];
        SetCapture(hwnd);return 0;
    }
    case WM_MOUSEMOVE:if(g_pDrag)previewDrag(hwnd,mx,my);return 0;
    case WM_LBUTTONUP:
        if(g_pDrag){
            previewDrag(hwnd,mx,my);g_pDrag=0;ReleaseCapture();
            g_iniError=0;writeBasic();if(g_iniError)status(iniErrorText());
        }
        return 0;
    case WM_CAPTURECHANGED:g_pDrag=0;return 0;
    }
    return DefWindowProcW(hwnd,msg,w,l);
}
static void setMode(int mode){
    if(mode==g_uiMode)return;
    if(g_isRunning||g_pending){stopOutput();restoreIfNeeded();status(L("Proyección detenida al cambiar de modo.","Projection stopped when changing mode."));}
    else g_statusText[0]=0; /* each mode starts with its own hint */
    readControls();destroyUI();
    g_uiMode=mode; /* not saved: every start opens in the basic mode */
    fitWindow(g_main,g_dpi,0);createUI();
    if(mode==0)SetTimer(g_main,ID_PREVIEW_TICK,1000,0);else KillTimer(g_main,ID_PREVIEW_TICK);
    InvalidateRect(g_main,0,1);
}
static void setLang(int lang){
    if(lang==g_lang)return;
    readControls();destroyUI();
    g_lang=lang;g_iniError=0;writeOne(W("Settings"),W("Language"),lang);
    g_statusText[0]=0;
    createUI();InvalidateRect(g_main,0,1);
}
static LRESULT __stdcall identifyProc(HWND hwnd,UINT msg,WPARAM w,LPARAM l){
    if(msg==WM_ERASEBKGND)return 1;
    if(msg==WM_PAINT){
        PAINTSTRUCT ps;HDC dc=BeginPaint(hwnd,&ps);RECT r;GetClientRect(hwnd,&r);
        HBRUSH bg=CreateSolidBrush(RGB3(19,46,78));FillRect(dc,&r,bg);DeleteObject(bg);
        int num=0;for(int i=0;i<g_monitorCount;i++)if(g_ids[i]==hwnd){num=i+1;break;}
        SetBkMode(dc,TRANSPARENT);SetTextColor(dc,RGB3(255,255,255));SelectObject(dc,g_fontOverlay);
        WCHAR n[24]={0};intw(n,num);RECT digit={0,(r.bottom-220)/2,r.right,(r.bottom-220)/2+195};DrawTextW(dc,n,-1,&digit,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
        WCHAR line[160]={0};appendw(line,W("PANTALLA "),160);appendi(line,num,160);
        int p=num>0&&g_monitors[num-1].dwFlags&MONITORINFOF_PRIMARY;
        appendw(line,p?L("  ·  PRINCIPAL","  · MAIN"):L("  ·  SECUNDARIA / PROYECTOR","  · SECONDARY / PROJECTOR"),160);
        SelectObject(dc,g_fontOverlaySmall);RECT head={0,digit.bottom+3,r.right,digit.bottom+58};DrawTextW(dc,line,-1,&head,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
        SelectObject(dc,g_fontUi);RECT sub={0,digit.bottom+70,r.right,digit.bottom+115};DrawTextW(dc,L("Identificación: desaparecerá en 5 segundos","Identification: disappears in 5 seconds"),-1,&sub,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
        EndPaint(hwnd,&ps);return 0;
    }
    return DefWindowProcW(hwnd,msg,w,l);
}
static void toggleEditFrame(void){
    if(!g_isRunning)return;
    g_editFrame=!g_editFrame;g_drag=HIT_NONE;
    SetWindowTextW(g_editBtn,g_editFrame?L("Terminar ajuste","Finish adjusting"):L("Ajustar con el ratón","Adjust with the mouse"));
    InvalidateRect(g_editBtn,0,1);
    compose();
    status(g_editFrame?L("Ajuste activo: lleva el puntero al proyector y arrastra el centro, los bordes o las esquinas (Mayús mantiene la proporción).","Adjusting: move the pointer to the projector and drag the middle, the edges or the corners (Shift keeps the proportions)."):
                       L("Ajuste terminado. El encuadre queda guardado.","Adjusting finished. The frame is saved."));
}
/* Manual EXTENDER <-> DUPLICAR. A manual choice replaces the automatic restore bookkeeping. */
static void toggleTopology(void){
    refreshMonitors();
    int mode=topologyMode();
    UINT flag=mode==2?SDC_TOPOLOGY_CLONE:SDC_TOPOLOGY_EXTEND;
    if(SetDisplayConfig(0,0,0,0,SDC_VALIDATE|flag)!=0){
        MessageBoxW(g_main,mode==2?L("Windows no admite DUPLICAR con esta conexión.","Windows does not support DUPLICATE with this connection."):L("Windows no admite EXTENDER con esta conexión. Comprueba que el proyector está conectado.","Windows does not support EXTEND with this connection. Check that the projector is connected."),L("Cambiar modo de pantalla","Change display mode"),0x30);
        return;
    }
    if(g_isRunning)stopOutput();
    dismissIds();
    KillTimer(g_main,ID_BEGIN_AFTER_EXTEND);g_pending=0;EnableWindow(g_start,1);
    if(g_wasClone){g_wasClone=0;iniWrite(W("Settings"),W("PendingRestoreClone"),W("0"));}
    g_switching=1;
    LONG result=SetDisplayConfig(0,0,0,0,SDC_APPLY|flag);
    g_switching=0;
    if(result!=0){MessageBoxW(g_main,L("Windows no pudo cambiar el modo. Prueba con Win + P.","Windows could not change the mode. Try Win + P."),L("Cambiar modo de pantalla","Change display mode"),0x30);return;}
    status(mode==2?L("Pasando a DUPLICAR...","Switching to DUPLICATE..."):L("Pasando a EXTENDER...","Switching to EXTEND..."));
    SetTimer(g_main,ID_DISPLAY_SETTLE,700,0); /* re-read the screens once Windows settles */
}
static void startProjection(void){
    if(g_uiMode==0){
        refreshMonitors();
        int mode=topologyMode();
        if(mode==1)switchToExtend();
        else if(mode==2)startOutput();
        else MessageBoxW(g_main,L("Solo se detecta una salida de vídeo. Conecta el proyector y configura Windows para DUPLICAR o EXTENDER.","Only one video output is detected. Connect the projector and set Windows to DUPLICATE or EXTEND."),L("No hay segundo monitor","No second screen"),0x30);
        return;
    }
    takeComboSelection();readControls();refreshMonitors();
    if(topologyMode()==1){switchToExtend();}
    else if(topologyMode()==2){startOutput();}
    else MessageBoxW(g_main,L("Solo se detecta una salida de vídeo. Conecta el proyector y configura Windows para DUPLICAR o EXTENDER.","Only one video output is detected. Connect the projector and set Windows to DUPLICATE or EXTEND."),L("No hay segundo monitor","No second screen"),0x30);
}
static LRESULT __stdcall mainProc(HWND hwnd,UINT msg,WPARAM w,LPARAM l){
    switch(msg){
    case WM_CREATE:
        g_main=hwnd;g_dpi=GetDpiForWindow(hwnd);if(!g_dpi)g_dpi=96;
        initResources();
        refreshMonitors();loadSavedMonitors();readConfig();readBasic();
        g_restoreClone=GetPrivateProfileIntW(W("Settings"),W("RestoreClone"),1,g_ini)?1:0;
        fitWindow(hwnd,g_dpi,0);createUI();
        if(g_uiMode==0)SetTimer(hwnd,ID_PREVIEW_TICK,1000,0);
        SetTimer(hwnd,ID_STARTUP_CHECK,400,0);
        /* Leftovers of the last update, then the check (later at sign-in, when the network may lag). */
        copyw(g_oldPath,g_exe,PATHCAP);appendw(g_oldPath,W(".old"),PATHCAP);
        copyw(g_newPath,g_exe,PATHCAP);appendw(g_newPath,W(".new"),PATHCAP);
        DeleteFileW(g_oldPath);DeleteFileW(g_newPath);
        SetTimer(hwnd,ID_UPDATE_CHECK,g_autostarted?30000:3000,0);
        return 0;
    case WM_DPICHANGED:
        fitWindow(hwnd,(UINT)(w&0xffff),(const RECT*)l);return 0;
    case WM_COMMAND:{
        int id=(int)(w&0xffff),code=(int)((w>>16)&0xffff);
        if(code==CBN_DROPDOWN && id==ID_SOURCE){fillSourceCombo();return 0;}
        if(code==CBN_SELCHANGE && (id==ID_SOURCE||id==ID_TARGET)){
            takeComboSelection();
            if(g_isRunning){
                /* Stay in EXTENDER and restart on the new pair; DUPLICAR comes back on Stop. */
                stopOutput();
                if(startOutput())status(L("Pantallas cambiadas: proyección reiniciada con la nueva selección.","Screens changed: projection restarted with the new selection."));
                else status(L("Proyección detenida: la nueva selección no es válida. Corrígela y pulsa Iniciar.","Projection stopped: the new selection is not valid. Fix it and press Start."));
            }
            return 0;
        }
        if(id==ID_RESTORE_CLONE && code==0){
            g_restoreClone=(SendMessageW(g_restoreBox,BM_GETCHECK,0,0)==BST_CHECKED);
            g_iniError=0;writeOne(W("Settings"),W("RestoreClone"),g_restoreClone);
            if(g_iniError)status(iniErrorText());
            return 0;
        }
        if(code!=0)break;
        switch(id){
        case ID_TAB0:case ID_TAB0+1:case ID_TAB0+2:setTileTab(id-ID_TAB0);break;
        case ID_UI_BASIC:setMode(0);break;
        case ID_UI_ADV:setMode(1);break;
        case ID_LANG_ES:setLang(0);break;
        case ID_LANG_EN:setLang(1);break;
        case ID_MENU:showOptionsMenu();break;
        case ID_CENTER:basicCenter();basicChanged();g_iniError=0;writeBasic();break;
        case ID_FILL:basicFill();basicChanged();g_iniError=0;writeBasic();break;
        case ID_APPLY:applySettings();break;
        case ID_EDITFRAME:toggleEditFrame();break;
        case ID_TOPOLOGY:toggleTopology();break;
        case ID_START:
            if(g_isRunning){stopOutput();restoreIfNeeded();status(L("Proyección detenida. Configuración restaurada si correspondía.","Projection stopped. Display settings restored where needed."));}
            else startProjection();
            break;
        case ID_BLACK:if(g_isRunning){g_isBlack=!g_isBlack;refreshRunState();render();status(g_isBlack?L("Imagen en negro; HDMI activo.","Picture black; HDMI still on."):L("Imagen reanudada.","Picture resumed."));}break;
        case ID_CINEMA:preset(100,0);break;
        case ID_CONF:preset(65,2);break;
        case ID_SMALL:preset(40,0);break;
        case ID_RELOAD:if(g_isRunning){stopOutput();restoreIfNeeded();}refreshMonitors();fillTiles();status(L("Pantallas actualizadas. Comprueba los números antes de iniciar.","Screens refreshed. Check the numbers before starting."));break;
        case ID_IDENTIFY:identifyScreens();break;
        case ID_SAVE_PROFILE:saveProfile();break;
        case ID_LOAD_PROFILE:loadProfile();break;
        }return 0;
    }
    case WM_DISPLAYCHANGE:
        /* Windows sends these in bursts (topology, then each mode). Hide the output at once
         * so it can never cover the panel, and decide once things have settled. */
        if(g_switching)return 0;
        dismissIds();
        if(g_output)ShowWindow(g_output,SW_HIDE);
        SetTimer(hwnd,ID_DISPLAY_SETTLE,700,0);
        return 0;
    case WM_TIMER:
        if(w==ID_HIDEIDS){dismissIds();return 0;}
        if(w==ID_THUMBS){thumbStep();return 0;}
        if(w==ID_TABGUARD){tabGuard();return 0;}
        if(w==ID_UPDATE_CHECK){
            KillTimer(hwnd,ID_UPDATE_CHECK);
            DeleteFileW(g_oldPath); /* right after an update the old copy may not have closed by WM_CREATE */
            if(checkUpdatesOn())startCheck(0);
            return 0;
        }
        if(w==ID_UPDATE_WAIT){
            if(busyProjecting())return 0;
            KillTimer(hwnd,ID_UPDATE_WAIT);
            int what=g_updWait;g_updWait=0;
            if(what==1)askToUpdate();else if(what==2)installUpdate();
            return 0;
        }
        if(w==ID_PREVIEW_TICK){
            /* Keeps the stills of "your screen" roughly current while the basic panel is open. */
            if(g_preview&&!g_pDrag)InvalidateRect(g_preview,0,0);
            return 0;
        }
        if(w==ID_DISPLAY_SETTLE){
            KillTimer(hwnd,ID_DISPLAY_SETTLE);
            if(g_switching)return 0;
            int same=refreshMonitors();
            if(g_isRunning){
                stopOutput();
                if(same && topologyMode()==2 && startOutput())
                    status(L("La configuración de pantallas cambió: proyección reajustada a la nueva resolución.","The display settings changed: projection adjusted to the new resolution."));
                else {
                    restoreIfNeeded();
                    status(L("La configuración de pantallas cambió y la salida ya no es válida: proyección detenida.","The display settings changed and the output is no longer valid: projection stopped."));
                }
            }
            if(g_uiMode==0){basicNormalize();basicChanged();InvalidateRect(hwnd,0,0);}
            return 0;
        }
        if(w==ID_STARTUP_CHECK){
            KillTimer(hwnd,ID_STARTUP_CHECK);
            refreshRunState(); /* the emergency key is registered after the panel is built */
            if(g_hotkey==2)status(L("Ctrl + Alt + P la usa otro programa: la parada de emergencia será Ctrl + Alt + Mayús + P.","Another program uses Ctrl + Alt + P: the emergency stop is Ctrl + Alt + Shift + P."));
            else if(g_hotkey==0)status(L("AVISO: no se pudo registrar ninguna tecla de parada de emergencia. Detén siempre con el botón.","WARNING: no emergency stop key could be registered. Always stop with the button."));
            if(GetPrivateProfileIntW(W("Settings"),W("PendingRestoreClone"),0,g_ini)){
                iniWrite(W("Settings"),W("PendingRestoreClone"),W("0"));
                if((g_restoreClone||g_uiMode==0) && topologyMode()==2 && MessageBoxW(hwnd,L("La última vez ProjectorScaler pasó las pantallas a EXTENDER y se cerró sin volver a DUPLICAR.\n\n¿Quieres volver a DUPLICAR ahora?","Last time ProjectorScaler switched the screens to EXTEND and closed without going back to DUPLICATE.\n\nGo back to DUPLICATE now?"),L("Restaurar pantallas","Restore screens"),MB_YESNO|MB_ICONQUESTION)==IDYES){
                    g_switching=1;
                    LONG result=SetDisplayConfig(0,0,0,0,SDC_APPLY|SDC_TOPOLOGY_CLONE);
                    g_switching=0;
                    if(result!=0)MessageBoxW(hwnd,L("No se pudo restaurar DUPLICAR automáticamente. Usa Win + P > Duplicar.","Could not restore DUPLICATE automatically. Use Win + P > Duplicate."),L("Restaurar pantallas","Restore screens"),0x30);
                    refreshMonitors();
                }
            }
            return 0;
        }
        if(w==ID_BEGIN_AFTER_EXTEND){
            refreshMonitors();
            if(topologyMode()==2){
                KillTimer(hwnd,ID_BEGIN_AFTER_EXTEND);
                g_pending=0;EnableWindow(g_start,1);
                if(!startOutput()){restoreIfNeeded();}else{g_switching=0;status(L("EXTENDER activado temporalmente. Imagen reducida en el proyector.","EXTEND switched on temporarily. Reduced picture on the projector."));}
            }else if(++g_pending>=12){
                KillTimer(hwnd,ID_BEGIN_AFTER_EXTEND);
                MessageBoxW(hwnd,L("No se pudo detectar el escritorio extendido. Revisa la conexión HDMI y usa Win + P si es necesario.","The extended desktop was not detected. Check the HDMI connection and use Win + P if needed."),L("Error de pantalla","Display error"),0x30);
                restoreIfNeeded();
            }
            return 0;
        }break;
    case WM_HOTKEY:
        if(w==ID_EMERGENCY){dismissIds();stopOutput();restoreIfNeeded();status(L("Parada de emergencia.","Emergency stop."));return 0;}
        break;
    case WM_MOUSEMOVE:{
        int x=(int)(short)(l&0xffff),y=(int)(short)((l>>16)&0xffff);
        g_overLink=x>=g_linkRect.left&&x<g_linkRect.right&&y>=g_linkRect.top&&y<g_linkRect.bottom;
        if(g_overLink)SetCursor(LoadCursorW(0,IDC_HAND));
        return 0;
    }
    case WM_SETCURSOR:
        if(g_overLink&&(HWND)w==hwnd&&(l&0xffff)==1){SetCursor(LoadCursorW(0,IDC_HAND));return 1;} /* HTCLIENT */
        break;
    case WM_LBUTTONUP:{
        int x=(int)(short)(l&0xffff),y=(int)(short)((l>>16)&0xffff);
        if(g_pickerOpen&&y>=S(639)&&y<S(771)&&x>=S(20)&&x<S(757)){setPicker(0);return 0;}
        if(x>=g_linkRect.left&&x<g_linkRect.right&&y>=g_linkRect.top&&y<g_linkRect.bottom)
            ShellExecuteW(hwnd,W("open"),W("https://cmmendel.com"),0,0,1);
        return 0;
    }
    case WM_UPDATE_CHECKED:onUpdateChecked((int)w);return 0;
    case WM_UPDATE_FETCHED:onUpdateFetched((int)w);return 0;
    case WM_PAINT:paintMain(hwnd);return 0;
    case WM_ERASEBKGND:return 1;
    case WM_DRAWITEM:drawButton((const void*)l);return 1;
    case WM_CTLCOLORSTATIC:
        SetBkMode((HDC)w,TRANSPARENT);SetTextColor((HDC)w,RGB3(43,65,91));return (LRESULT)g_brWhite;
    case WM_DESTROY:
        if(g_magInit==1){stopOutput();MagUninitialize();g_magInit=0;}
        KillTimer(hwnd,ID_PREVIEW_TICK);KillTimer(hwnd,ID_THUMBS);tilesClear();tabRelease();
        UnregisterHotKey(hwnd,ID_EMERGENCY);dismissIds();stopOutput();restoreIfNeeded();
        if(g_fontUi)DeleteObject(g_fontUi);if(g_fontTitle)DeleteObject(g_fontTitle);if(g_fontHeader)DeleteObject(g_fontHeader);
        if(g_fontTiny)DeleteObject(g_fontTiny);if(g_fontOverlay)DeleteObject(g_fontOverlay);if(g_fontOverlaySmall)DeleteObject(g_fontOverlaySmall);
        if(g_brWhite)DeleteObject(g_brWhite);if(g_brWindow)DeleteObject(g_brWindow);
        PostQuitMessage(0);return 0;
    }
    return DefWindowProcW(hwnd,msg,w,l);
}
int _fltused = 0;
void mainCRTStartup(void){
    g_inst=GetModuleHandleW(0);
    SetProcessDpiAwarenessContext((void*)(LONG_PTR)-4);
    /* The INI lives next to the EXE. A bare file name would make the Profile API use the
     * Windows directory, so a path too long to hold it is never truncated to one. */
    const DWORD cap=(DWORD)SIZEOF(g_ini);
    DWORD len=GetModuleFileNameW(0,g_ini,cap);
    int cut=(int)len-1;while(cut>=0&&g_ini[cut]!='\\'&&g_ini[cut]!='/')cut--;
    const WCHAR* iniName=W("ProjectorScaler.ini");
    if(!len||len>=cap||cut<0||cut+1+20>=(int)cap){
        MessageBoxW(0,L("La ruta de la carpeta del programa es demasiado larga. Mueve ProjectorScaler a una carpeta más corta.","The program folder path is too long. Move ProjectorScaler to a shorter folder."),W("ProjectorScaler"),0x10);
        ExitProcess(4);
    }
    copyw(g_exe,g_ini,(int)SIZEOF(g_exe)); /* still the EXE's path here */
    g_autostarted=findw(GetCommandLineW(),W("--autostart"))>=0;
    {int i=0;while(iniName[i]){g_ini[cut+1+i]=iniName[i];i++;}g_ini[cut+1+i]=0;}
    {   /* Language: the saved choice, else Spanish on a Spanish Windows and English elsewhere. */
        int lang=(int)GetPrivateProfileIntW(W("Settings"),W("Language"),-1,g_ini);
        if(lang<0)lang=((GetUserDefaultUILanguage()&0x3ff)==0x0a)?0:1;
        g_lang=lang?1:0;
        g_uiMode=0; /* always opens in the basic mode, whatever was used last */
    }
    HCURSOR arrow=LoadCursorW(0,IDC_ARROW);
    HICON iconBig=(HICON)LoadImageW(g_inst,(const WCHAR*)(ULONG_PTR)IDI_APP,IMAGE_ICON,GetSystemMetrics(SM_CXICON),GetSystemMetrics(SM_CYICON),0);
    HICON iconSmall=(HICON)LoadImageW(g_inst,(const WCHAR*)(ULONG_PTR)IDI_APP,IMAGE_ICON,GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),0);
    WNDCLASSEXW c={0};c.cbSize=sizeof(c);c.lpfnWndProc=mainProc;c.hInstance=g_inst;c.hCursor=arrow;c.hIcon=iconBig;c.hIconSm=iconSmall;c.lpszClassName=W("ProjectorScalerMain");c.hbrBackground=(HBRUSH)(ULONG_PTR)(5+1);
    if(!RegisterClassExW(&c)){ExitProcess(1);}
    WNDCLASSEXW o={0};o.cbSize=sizeof(o);o.lpfnWndProc=outputProc;o.hInstance=g_inst;o.hCursor=arrow;o.lpszClassName=W("ProjectorScalerOutput");o.hbrBackground=(HBRUSH)(ULONG_PTR)(4+1);
    if(!RegisterClassExW(&o)){ExitProcess(2);}
    WNDCLASSEXW idc={0};idc.cbSize=sizeof(idc);idc.lpfnWndProc=identifyProc;idc.hInstance=g_inst;idc.hCursor=arrow;idc.lpszClassName=W("ProjectorScalerIdentify");idc.hbrBackground=(HBRUSH)(ULONG_PTR)(4+1);
    if(!RegisterClassExW(&idc)){ExitProcess(3);}
    WNDCLASSEXW pv={0};pv.cbSize=sizeof(pv);pv.lpfnWndProc=previewProc;pv.hInstance=g_inst;pv.hCursor=arrow;pv.lpszClassName=W("ProjectorScalerPreview");
    if(!RegisterClassExW(&pv)){ExitProcess(3);}
    WNDCLASSEXW tc={0};tc.cbSize=sizeof(tc);tc.lpfnWndProc=tilesProc;tc.hInstance=g_inst;tc.hCursor=LoadCursorW(0,IDC_HAND);tc.lpszClassName=W("ProjectorScalerTiles");
    if(!RegisterClassExW(&tc)){ExitProcess(3);}
    HWND h=CreateWindowExW(0,W("ProjectorScalerMain"),(const WCHAR*)(L"ProjectorScaler " APP_VERSION),WS_OVERLAPPEDWINDOW|WS_VISIBLE,120,18,780,748,0,0,g_inst,0);
    if(!h){MessageBoxW(0,L("No se pudo iniciar ProjectorScaler.","ProjectorScaler could not start."),W("Error"),0x10);ExitProcess(3);}
    ShowWindow(h,SW_SHOW);UpdateWindow(h);
    /* The emergency stop is the only way back if the output ever covers the panel:
     * fall back to a second combination and tell the user which one is live. */
    if(RegisterHotKey(h,ID_EMERGENCY,MOD_CONTROL|MOD_ALT,'P'))g_hotkey=1;
    else if(RegisterHotKey(h,ID_EMERGENCY,MOD_CONTROL|MOD_ALT|MOD_SHIFT,'P'))g_hotkey=2;
    MSG m;
    while(GetMessageW(&m,0,0,0)>0){
        if(IsDialogMessageW(h,&m))continue; /* Tab / Shift+Tab between controls */
        TranslateMessage(&m);DispatchMessageW(&m);
    }
    ExitProcess(0);
}

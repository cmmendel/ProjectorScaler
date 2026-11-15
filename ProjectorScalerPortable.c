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
#define ID_HIDEIDS 230
#define ID_BEGIN_AFTER_EXTEND 231
#define ID_DISPLAY_SETTLE 232
#define ID_STARTUP_CHECK 233
#define RGB3(r,g,b) ((DWORD)((r)|((g)<<8)|((b)<<16)))

/* Layout is written at 96 DPI and scaled per monitor (per-monitor-v2 awareness). */
#define BASE_CW 777
#define BASE_CH 725
#define MAXCTL 64
#define FONT_UI 0
#define FONT_TITLE 1
#define FONT_TINY 2
#define FRAME_MIN_MS 50
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
static void status(const WCHAR* s){if(g_status)SetWindowTextW(g_status,s);}
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
    SetWindowTextW(g_modeLabel,mode==2?W("Modo actual: EXTENDER · salida independiente"):
        mode==1?W("Modo actual: DUPLICAR · se extenderá al proyectar"):
        W("Modo actual: una sola pantalla activa"));
    if(g_topoBtn)SetWindowTextW(g_topoBtn,mode==2?W("Pasar a DUPLICAR"):W("Pasar a EXTENDER"));
}
static void monitorName(int i,WCHAR* name){
    RECT r=g_monitors[i].rcMonitor;name[0]=0;
    appendi(name,i+1,150);appendw(name,W("  |  "),150);
    appendw(name,(g_monitors[i].dwFlags&MONITORINFOF_PRIMARY)?W("PRINCIPAL"):W("Secundaria"),150);
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
        appendw(line,W("Ventana  ·  "),150);appendw(line,title,150);
        if(IsIconic(g_winList[i]))appendw(line,W("  (minimizada)"),150);
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
    fillSourceCombo();comboselect(g_target,g_targetIndex);
    updateModeLabel();
    return matchedS&&matchedT;
}
static void takeComboSelection(void){
    if(g_monitorCount<1)return;
    int sel=comboindex(g_source);
    if(sel<g_monitorCount){g_sourceIndex=sel;g_srcWindow=0;}
    else if(sel-g_monitorCount<g_winCount)g_srcWindow=g_winList[sel-g_monitorCount];
    g_targetIndex=MIN(comboindex(g_target),g_monitorCount-1);
}
static void dismissIds(void){KillTimer(g_main,ID_HIDEIDS);for(int i=0;i<16;i++)if(g_ids[i]){DestroyWindow(g_ids[i]);g_ids[i]=0;}}
static void identifyScreens(void){
    dismissIds();refreshMonitors();
    if(!g_monitorCount)return;
    if(topologyMode()==1){
        MessageBoxW(g_main,W("Las pantallas están DUPLICADAS: Windows muestra exactamente la misma imagen en ambas.\n\nPulsa Iniciar proyección para pasar temporalmente a EXTENDER y entonces podrás identificar y elegir cada salida."),W("Identificación de pantallas"),0x40);
        return;
    }
    for(int i=0;i<g_monitorCount;i++){
        RECT r=g_monitors[i].rcMonitor;
        g_ids[i]=CreateWindowExW(WS_EX_TOPMOST|WS_EX_TOOLWINDOW|WS_EX_NOACTIVATE,W("ProjectorScalerIdentify"),W("Identificación"),WS_POPUP,(int)r.left,(int)r.top,(int)(r.right-r.left),(int)(r.bottom-r.top),0,0,g_inst,0);
        if(g_ids[i]){ShowWindow(g_ids[i],SW_SHOW);SetWindowPos(g_ids[i],HWND_TOPMOST,r.left,r.top,r.right-r.left,r.bottom-r.top,SWP_NOACTIVATE|SWP_SHOWWINDOW);}
    }
    SetTimer(g_main,ID_HIDEIDS,5000,0);
    status(W("Identificación activa 5 segundos. Localiza el número de cada pantalla."));
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
    setint(g_zoom,g_zoomValue);setint(g_x,g_xValue);setint(g_y,g_yValue);
    setint(g_customW,g_cw);setint(g_customH,g_ch);
    comboselect(g_aspect,g_aspectIndex);comboselect(g_fit,g_fitIndex);
    SendMessageW(g_cursor,BM_SETCHECK,g_showCursor?BST_CHECKED:0,0);
    /* With a free frame, size and position come from the mouse, not from these fields. */
    int fixed=g_aspectIndex!=ASPECT_FREE;
    EnableWindow(g_zoom,fixed);EnableWindow(g_x,fixed);EnableWindow(g_y,fixed);
}
static void readControls(void){
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
    if(g_monitorCount>g_sourceIndex)iniWrite(s,W("Source"),g_monitors[g_sourceIndex].szDevice);
    if(g_monitorCount>g_targetIndex)iniWrite(s,W("Target"),g_monitors[g_targetIndex].szDevice);
}
static const WCHAR* iniErrorText(void){
    return W("No se pudo escribir ProjectorScaler.ini: la carpeta del programa no admite escritura. Los ajustes no se guardarán.");
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
static void clearRender(void){
    if(g_capDC){if(g_capOld)SelectObject(g_capDC,g_capOld);if(g_capBmp)DeleteObject(g_capBmp);DeleteDC(g_capDC);}
    if(g_bufDC){if(g_bufOld)SelectObject(g_bufDC,g_bufOld);if(g_bufBmp)DeleteObject(g_bufBmp);DeleteDC(g_bufDC);}
    g_capDC=g_bufDC=0;g_capBmp=g_bufBmp=0;g_capOld=g_bufOld=0;
}
static void stopOutput(void){
    if(g_output){KillTimer(g_output,1);DestroyWindow(g_output);g_output=0;}
    clearRender();g_isRunning=0;g_isBlack=0;g_frameMs=FRAME_MIN_MS;
    if(g_start)SetWindowTextW(g_start,W("Iniciar proyección"));
    if(g_black){SetWindowTextW(g_black,W("Pantalla negra"));EnableWindow(g_black,0);}
    g_editFrame=0;g_drag=HIT_NONE;
    if(g_editBtn){SetWindowTextW(g_editBtn,W("Ajustar con el ratón"));EnableWindow(g_editBtn,0);}
}
static void computeFrame(int* ox,int* oy,int* ow,int* oh){
    if(g_aspectIndex==ASPECT_FREE){
        int l=(g_free[0]*g_tw+FREE_UNIT/2)/FREE_UNIT,t=(g_free[1]*g_th+FREE_UNIT/2)/FREE_UNIT;
        int r=(g_free[2]*g_tw+FREE_UNIT/2)/FREE_UNIT,b=(g_free[3]*g_th+FREE_UNIT/2)/FREE_UNIT;
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
static void captureWindow(void){
    if(!IsWindow(g_srcWindow)){
        if(!g_srcLost){g_srcLost=1;status(W("La ventana proyectada se ha cerrado: se mantiene la última imagen. Elige otro origen."));}
        return;
    }
    if(IsIconic(g_srcWindow))return;
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
    DrawTextW(g_bufDC,W("AJUSTE  ·  centro: mover  ·  bordes y esquinas: estirar  ·  Mayús: proporción"),-1,&tr,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    SelectObject(g_bufDC,old);
}
/* Puts the last capture into the frame. Cheap enough to call on every mouse move. */
static void compose(void){
    if(!g_isRunning||!g_bufDC)return;
    PatBlt(g_bufDC,0,0,g_tw,g_th,BLACKNESS);
    int fx,fy,fw,fh;computeFrame(&fx,&fy,&fw,&fh);
    if(!g_isBlack){
        int sx=0,sy=0,sw=g_sw,sh=g_sh,dx=fx,dy=fy,dw=fw,dh=fh;
        if(g_fitIndex==0){
            double ar=(double)g_sw/g_sh,fr=(double)fw/fh;
            if(ar>fr){dh=MAX(1,(int)(fw/ar+0.5));dy=fy+(fh-dh)/2;}
            else {dw=MAX(1,(int)(fh*ar+0.5));dx=fx+(fw-dw)/2;}
        }else if(g_fitIndex==1){
            double ar=(double)g_sw/g_sh,fr=(double)fw/fh;
            if(ar>fr){sw=MAX(1,(int)(g_sh*fr+0.5));sx=(g_sw-sw)/2;}
            else {sh=MAX(1,(int)(g_sw/fr+0.5));sy=(g_sh-sh)/2;}
        }
        SetStretchBltMode(g_bufDC,HALFTONE);
        SetBrushOrgEx(g_bufDC,0,0,0); /* required by GDI after selecting HALFTONE */
        StretchBlt(g_bufDC,dx,dy,dw,dh,g_capDC,sx,sy,sw,sh,SRCCOPY);
    }
    if(g_editFrame)drawEditOverlay(fx,fy,fw,fh);
    InvalidateRect(g_output,0,0);
}
static void render(void){
    if(!g_isRunning||!g_bufDC)return;
    if(!g_isBlack)captureSource();
    compose();
}
static int switchToExtend(void){
    if(MessageBoxW(g_main,W("Windows está en modo DUPLICAR.\n\nPara mostrar una imagen reducida SOLO en el proyector es necesario pasar TEMPORALMENTE a EXTENDER.\n\nLa aplicación podrá restaurar DUPLICAR al detener la proyección.\n\n¿Quieres cambiar ahora a EXTENDER?"),W("Cambiar modo de pantalla"),MB_YESNO|MB_ICONQUESTION)!=IDYES)return 0;
    if(SetDisplayConfig(0,0,0,0,SDC_VALIDATE|SDC_TOPOLOGY_EXTEND)!=0){
        MessageBoxW(g_main,W("Windows no admite el modo EXTENDER con esta conexión. Comprueba los adaptadores HDMI y la configuración de pantalla."),W("No se puede extender"),0x30);return 0;
    }
    g_switching=1;
    if(SetDisplayConfig(0,0,0,0,SDC_APPLY|SDC_TOPOLOGY_EXTEND)!=0){
        g_switching=0;MessageBoxW(g_main,W("Windows no pudo cambiar a EXTENDER. Puedes intentar Win + P > Extender."),W("Error de pantalla"),0x30);return 0;
    }
    g_wasClone=1;g_pending=0;EnableWindow(g_start,0);SetTimer(g_main,ID_BEGIN_AFTER_EXTEND,850,0);
    /* Survives a crash or a forced close: the next start offers to put DUPLICAR back. */
    iniWrite(W("Settings"),W("PendingRestoreClone"),W("1"));
    status(W("Cambiando de DUPLICAR a EXTENDER... Se abrirá la proyección en el monitor secundario."));
    return 1;
}
static void restoreIfNeeded(void){
    KillTimer(g_main,ID_BEGIN_AFTER_EXTEND);g_pending=0;g_switching=0;EnableWindow(g_start,1);
    if(!g_wasClone)return;
    g_wasClone=0;
    iniWrite(W("Settings"),W("PendingRestoreClone"),W("0"));
    if(g_restoreClone){
        LONG result=SetDisplayConfig(0,0,0,0,SDC_APPLY|SDC_TOPOLOGY_CLONE);
        if(result!=0)MessageBoxW(g_main,W("No se pudo restaurar DUPLICAR automáticamente. Usa Win + P > Duplicar."),W("Restaurar pantallas"),0x30);
    }
    refreshMonitors();
}
static int startOutput(void){
    takeComboSelection();
    int win=g_srcWindow!=0;
    if(g_monitorCount<2 || g_targetIndex>=g_monitorCount || (!win && (g_sourceIndex==g_targetIndex || g_sourceIndex>=g_monitorCount))){
        MessageBoxW(g_main,W("No hay dos escritorios independientes. Comprueba el modo EXTENDER y pulsa Actualizar."),W("ProjectorScaler"),0x30);return 0;
    }
    if(g_targetIndex==controllingIndex()){
        MessageBoxW(g_main,W("PROTECCIÓN ACTIVADA: el destino es la pantalla donde estás manejando ProjectorScaler.\n\nElige la otra pantalla como destino para no ocultar el panel de control."),W("Selección de destino incorrecta"),0x30);return 0;
    }
    if(win&&!IsWindow(g_srcWindow)){
        MessageBoxW(g_main,W("La ventana elegida ya no existe. Pulsa Actualizar y elígela de nuevo."),W("ProjectorScaler"),0x30);return 0;
    }
    RECT s=g_monitors[g_sourceIndex].rcMonitor,t=g_monitors[g_targetIndex].rcMonitor;
    g_sw=(int)(s.right-s.left);g_sh=(int)(s.bottom-s.top);
    if(win){
        /* Start at the window's client size; a minimised window starts at 16:9 until restored. */
        RECT cr={0};GetClientRect(g_srcWindow,&cr);
        g_sw=(int)cr.right;g_sh=(int)cr.bottom;
        if(IsIconic(g_srcWindow)||g_sw<2||g_sh<2){g_sw=1280;g_sh=720;}
    }
    g_srcLost=0;
    g_tw=(int)(t.right-t.left);g_th=(int)(t.bottom-t.top);g_tOrgX=(int)t.left;g_tOrgY=(int)t.top;
    if(g_sw<2||g_sh<2||g_tw<2||g_th<2){status(W("Error: resolución de monitor incorrecta."));return 0;}
    HDC screen=GetDC(0);
    if(!screen)return 0;
    g_capDC=CreateCompatibleDC(screen);g_bufDC=CreateCompatibleDC(screen);
    if(g_capDC)g_capBmp=CreateCompatibleBitmap(screen,g_sw,g_sh);
    if(g_bufDC)g_bufBmp=CreateCompatibleBitmap(screen,g_tw,g_th);
    ReleaseDC(0,screen);
    if(!g_capDC||!g_bufDC||!g_capBmp||!g_bufBmp){clearRender();status(W("Error: no se pudieron crear las superficies GDI."));return 0;}
    g_capOld=SelectObject(g_capDC,g_capBmp);g_bufOld=SelectObject(g_bufDC,g_bufBmp);
    g_output=CreateWindowExW(WS_EX_TOPMOST|WS_EX_TOOLWINDOW|WS_EX_NOACTIVATE,W("ProjectorScalerOutput"),W("ProjectorScaler salida"),WS_POPUP|WS_VISIBLE,(int)t.left,(int)t.top,g_tw,g_th,0,0,g_inst,0);
    if(!g_output){clearRender();status(W("Error al crear la ventana HDMI."));return 0;}
    SetWindowPos(g_output,HWND_TOPMOST,t.left,t.top,g_tw,g_th,SWP_NOACTIVATE|SWP_SHOWWINDOW);
    g_isRunning=1;g_isBlack=0;
    render();SetTimer(g_output,1,50,0);
    SetWindowTextW(g_start,W("Detener proyección"));EnableWindow(g_black,1);EnableWindow(g_editBtn,1);
    SetWindowTextW(g_black,W("Pantalla negra"));
    status(g_hotkey==1?W("Proyección activa. Parada de emergencia: Ctrl + Alt + P."):
           g_hotkey==2?W("Proyección activa. Parada de emergencia: Ctrl + Alt + Mayús + P (Ctrl + Alt + P la usa otro programa)."):
           W("Proyección activa. AVISO: no hay tecla de emergencia; detén con el botón Detener proyección."));
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
    case WM_TIMER:if(w==1){DWORD t0=GetTickCount();render();adaptFrameRate(GetTickCount()-t0);}return 0;
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
            status(g_iniError?iniErrorText():W("Encuadre libre guardado. Pulsa Terminar ajuste cuando acabes."));
        }
        return 0;
    case WM_CAPTURECHANGED:
        g_drag=HIT_NONE;return 0;
    }
    return DefWindowProcW(hwnd,msg,w,l);
}
static void applySettings(void){
    readControls();syncControls();g_iniError=0;writeConfig();if(g_isRunning)render();
    status(g_iniError?iniErrorText():W("Ajustes aplicados y guardados. Se actualiza la imagen en directo."));
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
    if(!name[0]){MessageBoxW(g_main,W("Escribe un nombre para guardar el perfil."),W("ProjectorScaler"),0x40);return;}
    readControls();
    profileSection(name,sect);g_iniError=0;
    writeOne(sect,W("Zoom"),g_zoomValue);writeOne(sect,W("X"),g_xValue);writeOne(sect,W("Y"),g_yValue);
    writeOne(sect,W("Aspect"),g_aspectIndex);writeOne(sect,W("Fit"),g_fitIndex);
    writeOne(sect,W("CustomWidth"),g_cw);writeOne(sect,W("CustomHeight"),g_ch);
    writeOne(sect,W("Cursor"),g_showCursor);
    writeFree(sect);
    listProfiles();SetWindowTextW(g_profile,name);
    status(g_iniError?iniErrorText():W("Perfil personalizado guardado en el archivo INI."));
}
static void loadProfile(void){
    WCHAR name[64],sect[96],sentinel[12];GetWindowTextW(g_profile,name,64);
    if(!name[0]){status(W("Selecciona un perfil antes de cargarlo."));return;}
    profileSection(name,sect);
    GetPrivateProfileStringW(sect,W("Zoom"),W("no-existe"),sentinel,12,g_ini);
    if(sentinel[0]=='n'){status(W("No se encuentra el perfil seleccionado."));return;}
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
    syncControls();applySettings();if(!g_iniError)status(W("Perfil cargado y aplicado."));
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
static void createUI(void){
    g_fontOverlay=CreateFontW(-168,0,0,0,800,0,0,0,1,0,0,0,0,W("Segoe UI"));
    g_fontOverlaySmall=CreateFontW(-30,0,0,0,650,0,0,0,1,0,0,0,0,W("Segoe UI"));
    g_brWhite=CreateSolidBrush(RGB3(255,255,255));g_brWindow=CreateSolidBrush(RGB3(239,243,248));

    section(W("01   PANTALLAS Y CONEXIÓN"),40,81,470);
    lbl(W("Origen: una pantalla o una ventana"),41,115,346);
    lbl(W("Pantalla de destino (proyector)"),399,115,342);
    g_source=combo(ID_SOURCE,40,139,341);SendMessageW(g_source,CB_SETDROPPEDWIDTH,(WPARAM)S(620),0);
    g_target=combo(ID_TARGET,399,139,338);
    button(W("IDENTIFICAR"),ID_IDENTIFY,40,176,160);
    button(W("Actualizar"),ID_RELOAD,208,176,120);
    g_topoBtn=button(W("Pasar a EXTENDER"),ID_TOPOLOGY,336,176,190);
    g_modeLabel=ctrl(W("STATIC"),W("Comprobando configuración..."),0,536,176,201,42,ID_MODE); /* two lines */
    setFontKind(g_modeLabel,FONT_TINY);

    section(W("02   IMAGEN Y GEOMETRÍA"),40,231,470);
    lbl(W("Tamaño (%)"),41,266,168);g_zoom=edit(ID_ZOOM,40,290,142);
    lbl(W("Horizontal (0-100)"),232,266,188);g_x=edit(ID_X,231,290,142);
    lbl(W("Vertical (0-100)"),423,266,174);g_y=edit(ID_Y,422,290,142);
    lbl(W("Relación de aspecto"),40,332,216);g_aspect=combo(ID_ASPECT,40,358,191);
    add(g_aspect,W("16:9 · Pantalla ancha"));add(g_aspect,W("16:10"));add(g_aspect,W("4:3 · Clásico"));add(g_aspect,W("21:9 · Cine"));add(g_aspect,W("1:1 · Cuadrada"));add(g_aspect,W("Personalizada"));add(g_aspect,W("Libre (con el ratón)"));
    lbl(W("Ancho : Alto"),249,332,178);g_customW=edit(ID_CW,248,358,67);lbl(W(":"),322,360,21);g_customH=edit(ID_CH,342,358,67);
    lbl(W("Adaptación"),427,332,225);g_fit=combo(ID_FIT,427,358,310);
    add(g_fit,W("Ajustar · Sin deformar"));add(g_fit,W("Rellenar · Con recorte"));add(g_fit,W("Estirar · Puede deformar"));
    g_cursor=ctrl(W("BUTTON"),W("Mostrar puntero"),BS_AUTOCHECKBOX|WS_TABSTOP,40,401,160,29,ID_CURSOR);
    g_editBtn=button(W("Ajustar con el ratón"),ID_EDITFRAME,208,399,262);EnableWindow(g_editBtn,0);
    g_apply=button(W("Aplicar y guardar"),ID_APPLY,478,399,259);

    section(W("03   PERFILES DE PROYECCIÓN"),40,449,466);
    button(W("Cine 16:9"),ID_CINEMA,40,484,211);
    button(W("Conferencia 4:3"),ID_CONF,262,484,233);
    button(W("Imagen pequeña"),ID_SMALL,507,484,230);
    lbl(W("Perfil personalizado:"),40,529,186);
    g_profile=ctrl(W("COMBOBOX"),W(""),WS_TABSTOP|WS_VSCROLL|0x0002u,212,529,205,150,ID_PROFILE);
    button(W("Guardar perfil"),ID_SAVE_PROFILE,428,526,149);
    button(W("Cargar perfil"),ID_LOAD_PROFILE,588,526,149);

    g_start=button(W("INICIAR PROYECCIÓN"),ID_START,40,590,343);
    g_black=button(W("PANTALLA NEGRA"),ID_BLACK,400,590,337);EnableWindow(g_black,0);
    g_restoreBox=ctrl(W("BUTTON"),W("Restaurar DUPLICAR al terminar (si se cambió automáticamente)"),BS_AUTOCHECKBOX|WS_TABSTOP,40,631,700,25,ID_RESTORE_CLONE);
    g_status=ctrl(W("STATIC"),W("Identifica las pantallas y selecciona la del proyector como destino."),0,40,663,695,38,ID_STATUS);
    setFontKind(g_status,FONT_TINY);
    refreshMonitors();loadSavedMonitors();readConfig();syncControls();listProfiles();
    g_restoreClone=GetPrivateProfileIntW(W("Settings"),W("RestoreClone"),1,g_ini)?1:0;
    SendMessageW(g_restoreBox,BM_SETCHECK,g_restoreClone?BST_CHECKED:0,0);
    updateModeLabel();
}
static void paintCard(HDC dc,int x,int y,int w,int h){RECT r={S(x),S(y),S(x+w),S(y+h)};FillRect(dc,&r,g_brWhite);}
static void paintMain(HWND hwnd){
    PAINTSTRUCT ps;HDC dc=BeginPaint(hwnd,&ps);RECT r={0};GetClientRect(hwnd,&r);
    FillRect(dc,&r,g_brWindow);
    RECT banner={0,0,r.right,S(68)};HBRUSH navy=CreateSolidBrush(RGB3(25,48,77));FillRect(dc,&banner,navy);DeleteObject(navy);
    SetBkMode(dc,TRANSPARENT);SetTextColor(dc,RGB3(255,255,255));
    HGDIOBJ oldFont=SelectObject(dc,g_fontHeader);
    RECT hdr={S(40),S(5),S(600),S(45)};DrawTextW(dc,W("ProjectorScaler"),-1,&hdr,0);
    SelectObject(dc,g_fontTiny);RECT subtitle={S(42),S(44),S(720),S(65)};SetTextColor(dc,RGB3(200,222,240));DrawTextW(dc,W("Control de proyección · Windows 10/11 · Portátil"),-1,&subtitle,0);
    SelectObject(dc,oldFont);
    paintCard(dc,20,75,737,144);paintCard(dc,20,225,737,216);paintCard(dc,20,448,737,129);paintCard(dc,20,583,737,122);
    EndPaint(hwnd,&ps);
}
static void drawButton(const void* data){
    typedef struct {UINT CtlType;UINT CtlID;UINT itemID;UINT itemAction;UINT itemState;HWND hwndItem;HDC hDC;RECT rcItem;ULONG_PTR itemData;} DRAWITEM;
    const DRAWITEM* d=(const DRAWITEM*)data;
    if(!d||!d->hDC)return;
    int id=(int)d->CtlID,disabled=(d->itemState&ODS_DISABLED)!=0;
    DWORD bg=RGB3(233,239,247),fg=RGB3(37,61,91);
    if(id==ID_START){bg=RGB3(26,107,181);fg=RGB3(255,255,255);}
    else if(id==ID_IDENTIFY){bg=RGB3(24,128,139);fg=RGB3(255,255,255);}
    else if(id==ID_BLACK){bg=RGB3(52,63,80);fg=RGB3(255,255,255);}
    else if(id==ID_APPLY){bg=RGB3(209,226,245);}
    else if(id==ID_EDITFRAME&&g_editFrame){bg=RGB3(245,166,35);fg=RGB3(19,46,78);}
    if(disabled){bg=RGB3(214,221,228);fg=RGB3(131,140,150);}
    if(d->itemState&ODS_SELECTED && !disabled){bg=RGB3(61,86,112);fg=RGB3(255,255,255);}
    HBRUSH brush=CreateSolidBrush(bg),old=(HBRUSH)SelectObject(d->hDC,brush);
    HGDIOBJ oldPen=SelectObject(d->hDC,GetStockObject(8)); /* NULL_PEN */
    RoundRect(d->hDC,d->rcItem.left,d->rcItem.top,d->rcItem.right,d->rcItem.bottom,11,11);
    SelectObject(d->hDC,oldPen);SelectObject(d->hDC,old);DeleteObject(brush);
    RECT r=d->rcItem;WCHAR label[128]={0};GetWindowTextW(d->hwndItem,label,128);
    HGDIOBJ oldFont=SelectObject(d->hDC,g_fontUi);SetBkMode(d->hDC,TRANSPARENT);SetTextColor(d->hDC,fg);
    DrawTextW(d->hDC,label,-1,&r,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    SelectObject(d->hDC,oldFont);
    if(d->itemState&ODS_FOCUS){RECT f={r.left+S(4),r.top+S(4),r.right-S(4),r.bottom-S(4)};DrawFocusRect(d->hDC,&f);}
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
        appendw(line,p?W("  ·  PRINCIPAL"):W("  ·  SECUNDARIA / PROYECTOR"),160);
        SelectObject(dc,g_fontOverlaySmall);RECT head={0,digit.bottom+3,r.right,digit.bottom+58};DrawTextW(dc,line,-1,&head,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
        SelectObject(dc,g_fontUi);RECT sub={0,digit.bottom+70,r.right,digit.bottom+115};DrawTextW(dc,W("Identificación: desaparecerá en 5 segundos"),-1,&sub,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
        EndPaint(hwnd,&ps);return 0;
    }
    return DefWindowProcW(hwnd,msg,w,l);
}
static void toggleEditFrame(void){
    if(!g_isRunning)return;
    g_editFrame=!g_editFrame;g_drag=HIT_NONE;
    SetWindowTextW(g_editBtn,g_editFrame?W("Terminar ajuste"):W("Ajustar con el ratón"));
    InvalidateRect(g_editBtn,0,1);
    compose();
    status(g_editFrame?W("Ajuste activo: lleva el puntero al proyector y arrastra el centro, los bordes o las esquinas (Mayús mantiene la proporción)."):
                       W("Ajuste terminado. El encuadre queda guardado."));
}
/* Manual EXTENDER <-> DUPLICAR. A manual choice replaces the automatic restore bookkeeping. */
static void toggleTopology(void){
    refreshMonitors();
    int mode=topologyMode();
    UINT flag=mode==2?SDC_TOPOLOGY_CLONE:SDC_TOPOLOGY_EXTEND;
    if(SetDisplayConfig(0,0,0,0,SDC_VALIDATE|flag)!=0){
        MessageBoxW(g_main,mode==2?W("Windows no admite DUPLICAR con esta conexión."):W("Windows no admite EXTENDER con esta conexión. Comprueba que el proyector está conectado."),W("Cambiar modo de pantalla"),0x30);
        return;
    }
    if(g_isRunning)stopOutput();
    dismissIds();
    KillTimer(g_main,ID_BEGIN_AFTER_EXTEND);g_pending=0;EnableWindow(g_start,1);
    if(g_wasClone){g_wasClone=0;iniWrite(W("Settings"),W("PendingRestoreClone"),W("0"));}
    g_switching=1;
    LONG result=SetDisplayConfig(0,0,0,0,SDC_APPLY|flag);
    g_switching=0;
    if(result!=0){MessageBoxW(g_main,W("Windows no pudo cambiar el modo. Prueba con Win + P."),W("Cambiar modo de pantalla"),0x30);return;}
    status(mode==2?W("Pasando a DUPLICAR..."):W("Pasando a EXTENDER..."));
    SetTimer(g_main,ID_DISPLAY_SETTLE,700,0); /* re-read the screens once Windows settles */
}
static LRESULT __stdcall mainProc(HWND hwnd,UINT msg,WPARAM w,LPARAM l){
    (void)l;
    switch(msg){
    case WM_CREATE:
        g_main=hwnd;g_dpi=GetDpiForWindow(hwnd);if(!g_dpi)g_dpi=96;
        fitWindow(hwnd,g_dpi,0);createUI();
        SetTimer(hwnd,ID_STARTUP_CHECK,400,0);
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
                if(startOutput())status(W("Pantallas cambiadas: proyección reiniciada con la nueva selección."));
                else status(W("Proyección detenida: la nueva selección no es válida. Corrígela y pulsa Iniciar."));
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
        case ID_APPLY:applySettings();break;
        case ID_EDITFRAME:toggleEditFrame();break;
        case ID_TOPOLOGY:toggleTopology();break;
        case ID_START:
            if(g_isRunning){stopOutput();restoreIfNeeded();status(W("Proyección detenida. Configuración restaurada si correspondía."));}
            else {
                takeComboSelection();readControls();refreshMonitors();
                if(topologyMode()==1){switchToExtend();}
                else if(topologyMode()==2){startOutput();}
                else MessageBoxW(g_main,W("Solo se detecta una salida de vídeo. Conecta el proyector y configura Windows para DUPLICAR o EXTENDER."),W("No hay segundo monitor"),0x30);
            }break;
        case ID_BLACK:if(g_isRunning){g_isBlack=!g_isBlack;SetWindowTextW(g_black,g_isBlack?W("Reanudar imagen"):W("Pantalla negra"));render();status(g_isBlack?W("Imagen en negro; HDMI activo."):W("Imagen reanudada."));}break;
        case ID_CINEMA:preset(100,0);break;
        case ID_CONF:preset(65,2);break;
        case ID_SMALL:preset(40,0);break;
        case ID_RELOAD:if(g_isRunning){stopOutput();restoreIfNeeded();}refreshMonitors();status(W("Pantallas actualizadas. Comprueba los números antes de iniciar."));break;
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
        if(w==ID_DISPLAY_SETTLE){
            KillTimer(hwnd,ID_DISPLAY_SETTLE);
            if(g_switching)return 0;
            int same=refreshMonitors();
            if(g_isRunning){
                stopOutput();
                if(same && topologyMode()==2 && startOutput())
                    status(W("La configuración de pantallas cambió: proyección reajustada a la nueva resolución."));
                else {
                    restoreIfNeeded();
                    status(W("La configuración de pantallas cambió y la salida ya no es válida: proyección detenida."));
                }
            }
            return 0;
        }
        if(w==ID_STARTUP_CHECK){
            KillTimer(hwnd,ID_STARTUP_CHECK);
            if(g_hotkey==2)status(W("Ctrl + Alt + P la usa otro programa: la parada de emergencia será Ctrl + Alt + Mayús + P."));
            else if(g_hotkey==0)status(W("AVISO: no se pudo registrar ninguna tecla de parada de emergencia. Detén siempre con el botón."));
            if(GetPrivateProfileIntW(W("Settings"),W("PendingRestoreClone"),0,g_ini)){
                iniWrite(W("Settings"),W("PendingRestoreClone"),W("0"));
                if(g_restoreClone && topologyMode()==2 && MessageBoxW(hwnd,W("La última vez ProjectorScaler pasó las pantallas a EXTENDER y se cerró sin volver a DUPLICAR.\n\n¿Quieres volver a DUPLICAR ahora?"),W("Restaurar pantallas"),MB_YESNO|MB_ICONQUESTION)==IDYES){
                    g_switching=1;
                    LONG result=SetDisplayConfig(0,0,0,0,SDC_APPLY|SDC_TOPOLOGY_CLONE);
                    g_switching=0;
                    if(result!=0)MessageBoxW(hwnd,W("No se pudo restaurar DUPLICAR automáticamente. Usa Win + P > Duplicar."),W("Restaurar pantallas"),0x30);
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
                if(!startOutput()){restoreIfNeeded();}else{g_switching=0;status(W("EXTENDER activado temporalmente. Imagen reducida en el proyector."));}
            }else if(++g_pending>=12){
                KillTimer(hwnd,ID_BEGIN_AFTER_EXTEND);
                MessageBoxW(hwnd,W("No se pudo detectar el escritorio extendido. Revisa la conexión HDMI y usa Win + P si es necesario."),W("Error de pantalla"),0x30);
                restoreIfNeeded();
            }
            return 0;
        }break;
    case WM_HOTKEY:
        if(w==ID_EMERGENCY){dismissIds();stopOutput();restoreIfNeeded();status(W("Parada de emergencia (Ctrl + Alt + P)."));return 0;}
        break;
    case WM_PAINT:paintMain(hwnd);return 0;
    case WM_ERASEBKGND:return 1;
    case WM_DRAWITEM:drawButton((const void*)l);return 1;
    case WM_CTLCOLORSTATIC:
        SetBkMode((HDC)w,TRANSPARENT);SetTextColor((HDC)w,RGB3(43,65,91));return (LRESULT)g_brWhite;
    case WM_DESTROY:
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
        MessageBoxW(0,W("La ruta de la carpeta del programa es demasiado larga. Mueve ProjectorScaler a una carpeta más corta."),W("ProjectorScaler"),0x10);
        ExitProcess(4);
    }
    {int i=0;while(iniName[i]){g_ini[cut+1+i]=iniName[i];i++;}g_ini[cut+1+i]=0;}
    HCURSOR arrow=LoadCursorW(0,IDC_ARROW);
    HICON iconBig=(HICON)LoadImageW(g_inst,(const WCHAR*)(ULONG_PTR)IDI_APP,IMAGE_ICON,GetSystemMetrics(SM_CXICON),GetSystemMetrics(SM_CYICON),0);
    HICON iconSmall=(HICON)LoadImageW(g_inst,(const WCHAR*)(ULONG_PTR)IDI_APP,IMAGE_ICON,GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),0);
    WNDCLASSEXW c={0};c.cbSize=sizeof(c);c.lpfnWndProc=mainProc;c.hInstance=g_inst;c.hCursor=arrow;c.hIcon=iconBig;c.hIconSm=iconSmall;c.lpszClassName=W("ProjectorScalerMain");c.hbrBackground=(HBRUSH)(ULONG_PTR)(5+1);
    if(!RegisterClassExW(&c)){ExitProcess(1);}
    WNDCLASSEXW o={0};o.cbSize=sizeof(o);o.lpfnWndProc=outputProc;o.hInstance=g_inst;o.hCursor=arrow;o.lpszClassName=W("ProjectorScalerOutput");o.hbrBackground=(HBRUSH)(ULONG_PTR)(4+1);
    if(!RegisterClassExW(&o)){ExitProcess(2);}
    WNDCLASSEXW idc={0};idc.cbSize=sizeof(idc);idc.lpfnWndProc=identifyProc;idc.hInstance=g_inst;idc.hCursor=arrow;idc.lpszClassName=W("ProjectorScalerIdentify");idc.hbrBackground=(HBRUSH)(ULONG_PTR)(4+1);
    if(!RegisterClassExW(&idc)){ExitProcess(3);}
    HWND h=CreateWindowExW(0,W("ProjectorScalerMain"),W("ProjectorScaler 2.1 · Proyección segura"),WS_OVERLAPPEDWINDOW|WS_VISIBLE,120,18,780,748,0,0,g_inst,0);
    if(!h){MessageBoxW(0,W("No se pudo iniciar ProjectorScaler."),W("Error"),0x10);ExitProcess(3);}
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

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
    SetWindowTextW(g_modeLabel,mode==2?W("MODO ACTUAL: EXTENDER · Salida independiente"):
        mode==1?W("MODO ACTUAL: DUPLICAR · Se convertirá temporalmente"):
        W("MODO ACTUAL: Una sola pantalla detectable"));
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
    SendMessageW(g_source,CB_RESETCONTENT,0,0);SendMessageW(g_target,CB_RESETCONTENT,0,0);
    int p=primaryIndex(),matchedS=0,matchedT=0;
    g_sourceIndex=p;g_targetIndex=(p==0&&g_monitorCount>1)?1:0;
    for(int i=0;i<g_monitorCount;i++){
        WCHAR name[150]={0};RECT r=g_monitors[i].rcMonitor;
        appendi(name,i+1,150);appendw(name,W("  |  "),150);
        appendw(name,(g_monitors[i].dwFlags&MONITORINFOF_PRIMARY)?W("PRINCIPAL"):W("Secundaria"),150);
        appendw(name,W("  "),150);appendi(name,(int)(r.right-r.left),150);appendw(name,W(" x "),150);appendi(name,(int)(r.bottom-r.top),150);
        appendw(name,W("  "),150);appendw(name,g_monitors[i].szDevice,150);
        add(g_source,name);add(g_target,name);
        if(srcName[0]&&eqw(g_monitors[i].szDevice,srcName)){g_sourceIndex=i;matchedS=1;}
        if(dstName[0]&&eqw(g_monitors[i].szDevice,dstName)){g_targetIndex=i;matchedT=1;}
    }
    /* In DUPLICAR there is one desktop, so source and target are saved as the same device;
     * after the switch to EXTENDER that must not count as a kept target. */
    if(matchedT&&g_targetIndex==g_sourceIndex)matchedT=0;
    if(!matchedT&&g_monitorCount>1){
        int ctl=controllingIndex(),pick=-1;
        for(int i=0;i<g_monitorCount&&pick<0;i++)if(i!=g_sourceIndex&&i!=ctl)pick=i;
        for(int i=0;i<g_monitorCount&&pick<0;i++)if(i!=g_sourceIndex)pick=i;
        g_targetIndex=pick<0?0:pick;
    }
    comboselect(g_source,g_sourceIndex);comboselect(g_target,g_targetIndex);
    updateModeLabel();
    return matchedS&&matchedT;
}
static void takeComboSelection(void){
    if(g_monitorCount<1)return;
    g_sourceIndex=MIN(comboindex(g_source),g_monitorCount-1);
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
    g_aspectIndex=MAX(0,MIN(g_aspectIndex,5));g_fitIndex=MAX(0,MIN(g_fitIndex,2));
    g_cw=MAX(1,MIN(g_cw,1000));g_ch=MAX(1,MIN(g_ch,1000));
}
static void syncControls(void){
    setint(g_zoom,g_zoomValue);setint(g_x,g_xValue);setint(g_y,g_yValue);
    setint(g_customW,g_cw);setint(g_customH,g_ch);
    comboselect(g_aspect,g_aspectIndex);comboselect(g_fit,g_fitIndex);
    SendMessageW(g_cursor,BM_SETCHECK,g_showCursor?BST_CHECKED:0,0);
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
static void writeConfig(void){
    const WCHAR* s=W("Settings");
    writeOne(s,W("Zoom"),g_zoomValue);writeOne(s,W("PositionX"),g_xValue);writeOne(s,W("PositionY"),g_yValue);
    writeOne(s,W("Aspect"),g_aspectIndex);writeOne(s,W("Fit"),g_fitIndex);writeOne(s,W("CustomWidth"),g_cw);writeOne(s,W("CustomHeight"),g_ch);
    writeOne(s,W("ShowCursor"),g_showCursor);
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
}
static void computeFrame(int* ox,int* oy,int* ow,int* oh){
    double r;
    switch(g_aspectIndex){case 1:r=16.0/10;break;case 2:r=4.0/3;break;case 3:r=21.0/9;break;case 4:r=1.0;break;case 5:r=(double)g_cw/(double)g_ch;break;default:r=16.0/9;}
    double w=(double)g_tw;double h=w/r;
    if(h>g_th){h=g_th;w=h*r;}
    w*=g_zoomValue/100.0;h*=g_zoomValue/100.0;
    *ow=(int)(w+0.5);*oh=(int)(h+0.5);
    *ow=MAX(1,MIN(*ow,g_tw));*oh=MAX(1,MIN(*oh,g_th));
    *ox=(g_tw-*ow)*g_xValue/100;*oy=(g_th-*oh)*g_yValue/100;
}
static void drawCursorOnCapture(void){
    if(!g_showCursor)return;
    CURSORINFO ci={0};ci.cbSize=sizeof(ci);
    if(!GetCursorInfo(&ci) || !(ci.flags&1))return;
    RECT r=g_monitors[g_sourceIndex].rcMonitor;
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
static void render(void){
    if(!g_isRunning||!g_bufDC)return;
    PatBlt(g_bufDC,0,0,g_tw,g_th,BLACKNESS);
    if(!g_isBlack){
        HDC desktop=GetDC(0);
        if(desktop){
            RECT r=g_monitors[g_sourceIndex].rcMonitor;
            BitBlt(g_capDC,0,0,g_sw,g_sh,desktop,r.left,r.top,SRCCOPY|CAPTUREBLT);
            ReleaseDC(0,desktop);
            drawCursorOnCapture();
            int fx,fy,fw,fh;computeFrame(&fx,&fy,&fw,&fh);
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
    }
    InvalidateRect(g_output,0,0);
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
    g_sourceIndex=comboindex(g_source);g_targetIndex=comboindex(g_target);
    if(g_monitorCount<2 || g_sourceIndex==g_targetIndex || g_sourceIndex>=g_monitorCount || g_targetIndex>=g_monitorCount){
        MessageBoxW(g_main,W("No hay dos escritorios independientes. Comprueba el modo EXTENDER y pulsa Actualizar pantallas."),W("ProjectorScaler"),0x30);return 0;
    }
    if(g_targetIndex==controllingIndex()){
        MessageBoxW(g_main,W("PROTECCIÓN ACTIVADA: el destino es la pantalla donde estás manejando ProjectorScaler.\n\nElige la otra pantalla como destino para no ocultar el panel de control."),W("Selección de destino incorrecta"),0x30);return 0;
    }
    RECT s=g_monitors[g_sourceIndex].rcMonitor,t=g_monitors[g_targetIndex].rcMonitor;
    g_sw=(int)(s.right-s.left);g_sh=(int)(s.bottom-s.top);
    g_tw=(int)(t.right-t.left);g_th=(int)(t.bottom-t.top);
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
    SetWindowTextW(g_start,W("Detener proyección"));EnableWindow(g_black,1);
    SetWindowTextW(g_black,W("Pantalla negra"));
    status(g_hotkey==1?W("Proyección activa. Parada de emergencia: Ctrl + Alt + P."):
           g_hotkey==2?W("Proyección activa. Parada de emergencia: Ctrl + Alt + Mayús + P (Ctrl + Alt + P la usa otro programa)."):
           W("Proyección activa. AVISO: no hay tecla de emergencia; detén con el botón Detener proyección."));
    writeConfig();return 1;
}
static LRESULT __stdcall outputProc(HWND hwnd,UINT msg,WPARAM w,LPARAM l){
    (void)l;
    switch(msg){
    case WM_TIMER:if(w==1){DWORD t0=GetTickCount();render();adaptFrameRate(GetTickCount()-t0);}return 0;
    case WM_ERASEBKGND:return 1;
    case WM_PAINT:{PAINTSTRUCT ps;HDC dc=BeginPaint(hwnd,&ps);if(g_bufDC&&dc)BitBlt(dc,0,0,g_tw,g_th,g_bufDC,0,0,SRCCOPY);EndPaint(hwnd,&ps);return 0;}
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
    g_zoomValue=MAX(20,MIN(g_zoomValue,100));g_xValue=MAX(0,MIN(g_xValue,100));g_yValue=MAX(0,MIN(g_yValue,100));
    g_aspectIndex=MAX(0,MIN(g_aspectIndex,5));g_fitIndex=MAX(0,MIN(g_fitIndex,2));
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
    lbl(W("Pantalla de origen (lo que vas a proyectar)"),41,115,346);
    lbl(W("Pantalla de destino (proyector)"),399,115,342);
    g_source=combo(ID_SOURCE,40,139,341);
    g_target=combo(ID_TARGET,399,139,338);
    button(W("IDENTIFICAR PANTALLAS"),ID_IDENTIFY,40,176,255);
    button(W("Actualizar lista"),ID_RELOAD,308,176,184);
    g_modeLabel=ctrl(W("STATIC"),W("Comprobando configuración..."),0,504,176,233,42,ID_MODE); /* two lines */
    setFontKind(g_modeLabel,FONT_TINY);

    section(W("02   IMAGEN Y GEOMETRÍA"),40,231,470);
    lbl(W("Tamaño (%)"),41,266,168);g_zoom=edit(ID_ZOOM,40,290,142);
    lbl(W("Horizontal (0-100)"),232,266,188);g_x=edit(ID_X,231,290,142);
    lbl(W("Vertical (0-100)"),423,266,174);g_y=edit(ID_Y,422,290,142);
    lbl(W("Relación de aspecto"),40,332,216);g_aspect=combo(ID_ASPECT,40,358,191);
    add(g_aspect,W("16:9 · Pantalla ancha"));add(g_aspect,W("16:10"));add(g_aspect,W("4:3 · Clásico"));add(g_aspect,W("21:9 · Cine"));add(g_aspect,W("1:1 · Cuadrada"));add(g_aspect,W("Personalizada"));
    lbl(W("Ancho : Alto"),249,332,178);g_customW=edit(ID_CW,248,358,67);lbl(W(":"),322,360,21);g_customH=edit(ID_CH,342,358,67);
    lbl(W("Adaptación"),427,332,225);g_fit=combo(ID_FIT,427,358,310);
    add(g_fit,W("Ajustar · Sin deformar"));add(g_fit,W("Rellenar · Con recorte"));add(g_fit,W("Estirar · Puede deformar"));
    g_cursor=ctrl(W("BUTTON"),W("Mostrar puntero del ratón"),BS_AUTOCHECKBOX|WS_TABSTOP,40,401,238,29,ID_CURSOR);
    g_apply=button(W("Aplicar y guardar"),ID_APPLY,344,399,393);

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
    WNDCLASSEXW c={0};c.cbSize=sizeof(c);c.lpfnWndProc=mainProc;c.hInstance=g_inst;c.hCursor=arrow;c.lpszClassName=W("ProjectorScalerMain");c.hbrBackground=(HBRUSH)(ULONG_PTR)(5+1);
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

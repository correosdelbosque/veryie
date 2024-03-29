// VeryIE.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "VeryIE.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "VeryIEView.h"

#include "afxpriv.h"
#include <..\src\occimpl.h>
#include "CustSite.h" 

//#include <afxsock.h>
#include <Winsock.h>
#include <afxmt.h>
#include <wininet.h>
//#include "rasspdm.h"
#include <initguid.h>
#include "VeryIE_i.c"
#include "VeryIENSHandle.h"
//add new
#include "SelectURL.h"
#include "SelectLang.h"
#include "InputDlg.h"

//##############################################################
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVeryIEApp

BEGIN_MESSAGE_MAP(CVeryIEApp, CWinApp)
	//{{AFX_MSG_MAP(CVeryIEApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVeryIEApp construction

CVeryIEApp::CVeryIEApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVeryIEApp object
CVeryIEApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVeryIEApp initialization
BOOL CVeryIEApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	//	SetUnhandledExceptionFilter(ExcepCallBack);
	//only one instance is allowed except -m
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		return TRUE;
	}

	HANDLE hSem = CreateSemaphore(NULL, 1, 1, m_pszAppName);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		m_bAutoStart = FALSE;
	else
		m_bAutoStart = TRUE;

    HINSTANCE hInstance = AfxGetResourceHandle();
    ASSERT(hInstance != NULL);
	LPTSTR lpszModule;
	try
	{
		 lpszModule = new TCHAR[_MAX_PATH];
    }
	catch(...)
	{
		return FALSE;
	}

	if (GetModuleFileName(hInstance, lpszModule, _MAX_PATH))
    {
		m_strProfile = lpszModule;
		int i = m_strProfile.ReverseFind('\\');
		m_strProfile= m_strProfile.Left(i+1);
		m_strRoot	= m_strProfile;
		m_strUser	= m_strProfile + "User\\";
		//
		m_strProfile		= m_strUser + "VeryIE.ini";
		m_strFormDataPath	= m_strUser + "FormData.ini";
		//
		m_strSkinPath		= m_strRoot + "skin\\";
		m_strGroupPath		= m_strRoot + "groups\\";
    }
    delete [] lpszModule;
	
	//First free the string allocated by MFC at CWinApp startup.
	//The string is allocated before InitInstance is called.
	free((void*)m_pszProfileName);
	//Change the name of the .INI file.
	//The CWinApp destructor will free the memory.
	m_pszProfileName=_tcsdup(m_strProfile);
	//delete[]  (char*)m_pszProfileName;
	//m_pszProfileName = m_strProfile;

	//must first create user path
	_CreateFullDir(m_strUser);

	HANDLE hfile ;
	CString filename;
	//
	filename = m_strProfile;
	hfile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hfile == INVALID_HANDLE_VALUE)
		CopyFile(m_strRoot+"Resource\\VeryIE.ini.default",filename, FALSE);
	else
		CloseHandle(hfile);
	//
	filename = m_strUser+"SearchEngine.ini";
	hfile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hfile == INVALID_HANDLE_VALUE)
		CopyFile(m_strRoot+"Resource\\SearchEngine.ini.default",filename, FALSE);
	else
		CloseHandle(hfile);
	//
	filename = m_strUser+"Filter.ini";
	hfile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hfile == INVALID_HANDLE_VALUE)
		CopyFile(m_strRoot+"Resource\\Filter.ini.default",filename, FALSE);
	else
		CloseHandle(hfile);
	//
	g_bForbidMult = GetProfileInt("Settings", "ForbidMult", FALSE);
	//group path
	CString strAbsDir;
	strAbsDir = GetProfileString("Settings", "GroupPath", NULL);
	if(!strAbsDir.IsEmpty())
	{
		CHECK_TAIL(strAbsDir);
		DO_RELATIVE_URL(strAbsDir)
		m_strGroupPath = strAbsDir;
	}

	//2 means first run,not select language
	m_bUseLngFile = GetProfileInt("Settings", "UseLngFile", 2);
	m_strLngFile = GetProfileString("Settings", "LngFile", "");
	if (m_bUseLngFile==2)
	{
		m_bUseLngFile = 0;
		WriteProfileInt("Settings", "UseLngFile", m_bUseLngFile );
		//
		CSelectLang dlg;
		dlg.DoModal();
	}
	else
	{
		m_strLngFile = theApp.m_strRoot+"Language\\" + m_strLngFile;
		if (m_strLngFile.GetLength()<1)
			m_bUseLngFile = FALSE;
		else
			_InitLanguageFile(m_strLngFile);
	}
	//
	if (cmdInfo.m_nShellCommand!=CCommandLineInfo::FileNew )
	{
		if (!m_bAutoStart)
		{
			CloseHandle(hSem);
			HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
			while (::IsWindow(hWndPrevious))
			{
				if (::GetProp(hWndPrevious, m_pszAppName))
				{
					if (cmdInfo.m_nShellCommand==CCommandLineInfo::FileOpen)
					{
						if (::GetLastActivePopup(hWndPrevious)==hWndPrevious)
						{
							LPSTR lpData;
							
							//mutex
							HANDLE hVeryIESem = CreateMutex(NULL, TRUE, "VeryIEMutex");
							WaitForSingleObject(hVeryIESem, INFINITE);
							HANDLE hMapping = CreateFileMapping
								((HANDLE)0xFFFFFFFF,NULL,
								PAGE_READWRITE,0,2560,"MY2IESHARE");
							if (hMapping==NULL)
							{
								MSGBOX("App:Fail to create share memory!");
							}
							else
							{
								lpData = (LPSTR) MapViewOfFile(hMapping,FILE_MAP_ALL_ACCESS,0,0,0);
								if (lpData==NULL)
								{
									MSGBOX("App:MapViewOfFile Fail");
								}
								else
								{
									sprintf(lpData,"%s",cmdInfo.m_strFileName);
									::SendMessage(hWndPrevious,WM_USER_SHELL_OPEN,NULL,NULL);
								}
								CloseHandle(hMapping);
							}
							ReleaseMutex(hVeryIESem);
						}
					}
					if (::IsIconic(hWndPrevious))
						::ShowWindow(hWndPrevious,SW_RESTORE);
					::SetForegroundWindow(::GetLastActivePopup(hWndPrevious));
					return FALSE;
				}
				hWndPrevious = ::GetWindow(hWndPrevious, GW_HWNDNEXT);
			}
			return FALSE;
		}
	}
	else if(g_bForbidMult && !m_bAutoStart)
	{
		//only one instance
		HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
		while (::IsWindow(hWndPrevious))
		{
			if (::GetProp(hWndPrevious, m_pszAppName))
			{
				if (::IsWindowVisible(hWndPrevious)==FALSE)
					::SendMessage(hWndPrevious,WM_HOTKEY,NULL,NULL);
				else
				{
					if (::IsIconic(hWndPrevious))
						::ShowWindow(hWndPrevious,SW_RESTORE);
					::SetForegroundWindow(::GetLastActivePopup(hWndPrevious));
				}
				return FALSE;
			}
			hWndPrevious = ::GetWindow(hWndPrevious, GW_HWNDNEXT);
		}	
	}
	// initialize Winsock library
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(1, 1);
	int nResult = WSAStartup(wVersionRequested, &wsaData);
	if (nResult == 0)
	{
		if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
		{
			WSACleanup();
		}
	}

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

#if _WIN32_WINNT >= 0x0400
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
	CoInitialize(NULL);
#endif

	if (!InitATL())
		return FALSE;

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.

	//get a random ID
    srand( (unsigned)time( NULL ) );
	g_nTrayIconID = rand()/16;

	strAbsDir = GetProfileString("Settings", "SkinPath", NULL);
	if(!strAbsDir.IsEmpty())
	{
		DO_RELATIVE_URL(strAbsDir)
		m_strSkinPath = strAbsDir;
	}
	
	//IShellUIHandle
	CCustomOccManager *pMgr = new CCustomOccManager;
	// Create an IDispatch class for extending the Dynamic HTML Object Model 
	m_pDispOM = new CImpIDispatch;
	//Drop target
	m_pDropTarget = new CImpIDropTarget;

	// Set our control containment up but using our control container 
	// management class instead of MFC's default
	AfxEnableControlContainer(pMgr);

	// create main MDI Frame window
	CMainFrame* mf = new CMainFrame;
	if (!mf->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = mf;
	//global main frame point
	::pmf = mf;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	//############################################################################
	LoadConfg();

	int nOpenType;
	CString strURL;

	BOOL bGoHome = GetProfileInt("Settings", "StartupMode", 2);
	//disable the old menu
	::SetMenu(pmf->m_hWnd, NULL);
	pmf->ShowWindow(m_nCmdShow);
	//max wins
	g_nMaxWins = GetProfileInt("Settings", "MaxWins", 100);
	BOOL run = 	GetProfileInt("Settings", "Running", 0);
	if(!m_bAutoStart)
		run = FALSE;
	g_bMax = GetProfileInt("Settings", "PageMax", 1);
	g_bMax = g_bMax>0 ? 1 : 0;
	//
	pmf->m_bKeepOnePage = GetProfileInt("Settings", "KeepOnePage", FALSE);
	if (pmf->m_bKeepOnePage)
	{
		if (bGoHome!=0 && bGoHome!=6)
			pmf->PostMessage(WM_COMMAND, ID_FILE_NEW_BLANK, 0);
	}
	//
	pmf->m_bAutoRunExternal = GetProfileInt("Settings", "AutoRunExternal", FALSE);
	pmf->m_bConfirmUnsafePage = GetProfileInt("Settings", "ConfirmUnsafePage", TRUE);
	pmf->m_dwDefaultProperty = GetProfileInt("Settings", "DefaultProperty", pmf->GetDefaultProperty());
	pmf->m_bUseTargetFrameName = GetProfileInt("Settings", "UseTargetFrameName", TRUE);

	//#####################################################################
	//!!anything before navigate add prev
	if (cmdInfo.m_nShellCommand==CCommandLineInfo::FileOpen)
	{
		nOpenType = 2;
		strURL = cmdInfo.m_strFileName;
		TCHAR           buf[2048];
		if(IS_FAVURL(strURL))
		{
			// an .URL file is formatted just like an .INI file, so we can
			// use GetPrivateProfileString() to get the information we want
			::GetPrivateProfileString(_T("InternetShortcut"), _T("URL"),
									  _T(""), buf, 2048,
									  strURL);
			strURL =  buf;
		}
		pmf->NewChildWindow(1, nOpenType, strURL);
	}
	else
	{
		//enable go home
		nOpenType = bGoHome;
		if(bGoHome == 2|| run)// must be first for run
		{
			char tmp[INTERNET_MAX_PATH_LENGTH];
			if (run)
			{
				remove(m_strUser+"LastVisit.ini");
				rename(m_strUser+"Visiting.ini", m_strUser+"LastVisit.ini");
			}
			CString filename = m_strUser+"LastVisit.ini";
			DWORD r = ::GetPrivateProfileString("LastVisit", "url0", NULL, tmp, INTERNET_MAX_PATH_LENGTH, filename);
			if(r)
			{
				CSelectURL dlg;
				dlg.DoModal();
			}
		}
		else if(bGoHome == 3)
		{
			CChildFrame *tcf;
			//load last visit
			char state[10]="state",url[8]="url"; // x+5
			CString filename = m_strUser+"LastVisit.ini";
			int i=0,nState;
			char tmp[INTERNET_MAX_PATH_LENGTH];
			BOOL r = TRUE;
			//
			BOOL bTemp = pmf->m_nNewSequence;
			pmf->m_nNewSequence = 0;
			while(r)
			{
				itoa(i, state+5, 10);
				itoa(i, url+3, 10);
				r = ::GetPrivateProfileString("LastVisit", url, NULL, tmp, INTERNET_MAX_PATH_LENGTH, filename);
				if (r)
				{
					tcf = pmf->NewChildWindow(1, 2, tmp);
					if (tcf)
					{
						nState = ::GetPrivateProfileInt("LastVisit", state, 0, filename);
						if (nState ==4)
							tcf->m_bLock = TRUE;
					}
				}
				i++;
			}
			pmf->m_nNewSequence  = bTemp;
		}
		else if(bGoHome == 0)
			pmf->PostMessage(WM_COMMAND, ID_FILE_NEW_BLANK, 0);
		else if(bGoHome == 1)//3.2
			pmf->PostMessage(WM_COMMAND, ID_FILE_NEW_S, 0);
		else if(bGoHome == 4)
		{
			pmf->OpenAllFavs(pmf->m_strStartFavFolder);
		}
		else if(bGoHome == 5)
		{
			//start group
			pmf->OpenGroup(pmf->m_strStartGroup+".cgp");
		}
		else if(bGoHome == 6)
			;//do nothing		
	}
	
	pmf->m_bAutoHideMode = GetProfileInt("Settings", "AutoHide", 0);
	if(pmf->m_bAutoHideMode)
	{
		pmf->AutoHideModeOn();
	}
	//full screen
	pmf->m_bFullScreenMode = GetProfileInt("Settings", "FullScreen", 0);
	if(pmf->m_bFullScreenMode)
	{
		pmf->FullScreenModeOn();
	}

	//############################################################################
	pmf->UpdateWindow();
	//delay load
	pmf->PostMessage(WM_DELAYLOAD_CONFIG);
	WriteProfileInt("Settings", "Running", 1);

	return TRUE;
}

// App command to run the dialog
void CVeryIEApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CVeryIEApp message handlers

//#pragma optimize( "", on )

int CVeryIEApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	try{
	WSACleanup();
	if(m_pDispOM)
		delete m_pDispOM;
	if(m_pDropTarget)
		delete m_pDropTarget;
	}catch(...){}

	if (m_bATLInited)
	{
		_Module.RevokeClassObjects();
		_Module.Term();
	}
	CoUninitialize();
	return CWinApp::ExitInstance();
}

void CVeryIEApp::LoadConfg()
{
	char *tmp = NULL;

	//enable popup
	g_bKillPop = GetProfileInt("Settings", "KillPop", 1);
	g_bKillAutoWin = GetProfileInt("Settings", "KillAutoWin", 1);
	g_bKillDupWin = GetProfileInt("Settings", "KillDupWin", 1);
	g_bKillListWin = GetProfileInt("Settings", "KillListWin", 1);
	//
	pmf->m_bNotConfirmPopupFilter = GetProfileInt("Settings", "NotConfirmPopupFilter", 1);
	pmf->m_bPlayPopupFilterSound = GetProfileInt("Settings", "PlayPopupFilterSound", 1);
	pmf->m_nPopDelay = GetProfileInt("Settings", "PopupBound", 120);
	pmf->m_nPopDelay /= 100;
	pmf->m_bFilterRefresh = GetProfileInt("Settings", "FilterRefresh", FALSE);
	pmf->m_bNotFilterClickDialog = GetProfileInt("Settings", "NotFilterClickDialog", TRUE);
	//
	pmf->m_bUseUrlFilter = GetProfileInt("Settings", "UseUrlFilter", TRUE);
	pmf->m_bUseDialogFilter = GetProfileInt("Settings", "UseDialogFilter", TRUE);
	pmf->m_bUseFlyingFilter = GetProfileInt("Settings", "UseFlyingFilter", TRUE);
	if (pmf->m_bUseFlyingFilter)
		pmf->RefreshKillFlyingCode();
	//
	pmf->m_bKillBlank = GetProfileInt("Filter", "KillBlank", TRUE);
	pmf->m_strBlankContent = GetProfileString("Filter", "BlankContent", "<AD>");
	if (pmf->m_bKillBlank)
		pmf->RefreshKillBlankCode();
	//
	pmf->m_bReloadUnShownImage = GetProfileInt("Settings", "ReloadUnShownImage", TRUE);
	//
	pmf->m_nEnableFilter = GetProfileInt("Settings", "EnableFilter", 0xF);
	//window pos
	int top = GetProfileInt("Settings", "top", 50);
	int left = GetProfileInt("Settings", "left", 50);
	int width = GetProfileInt("Settings", "width", 700);
	int height = GetProfileInt("Settings", "height", 500);
	if( width!=0 && top<2000 && top>=-20)
		m_pMainWnd->SetWindowPos(&CWnd::wndTop, left, top, width, height,SWP_HIDEWINDOW);   
	if( GetProfileInt("Settings", "Zoomed", 1))
		m_nCmdShow = SW_SHOWMAXIMIZED;

	pmf->m_nTitleLen = GetProfileInt("Settings", "TabSize", 20);

	//load defaul proxy
	pmf->GetIeProxy();
	pmf->m_bEnProxy = GetProfileInt("Settings", "EnableProxy", 0);
	pmf->m_strCurProxy = GetProfileString("Settings", "CurrentProxy", NULL);
	pmf->m_strCurProxyName = GetProfileString("Settings", "CurrentProxyName", NULL);//pmf->GetProxyName(pmf->m_strCurProxy);
	pmf->m_strProxyByPass = GetProfileString("Settings", "ProxyByPass", "<local>");
	pmf->UpdateProxy();
	
	//load defaul web proxy
	pmf->m_strDefaultWebProxy = GetProfileString("Settings", "DefaultWebProxy", NULL);
	//active new window
	pmf->m_bActiveNewWindow = GetProfileInt("Settings", "ActiveNew", 0);
	//
	pmf->m_bOpenFolderOut = GetProfileInt("Settings", "OpenFolderOut", TRUE);
	//the start favorite folder
	pmf->m_strStartFavFolder = GetProfileString("Settings", "StartFolder", NULL);
	//insert to next tab
	pmf->m_nNewSequence = GetProfileInt("Settings", "NewSequence", 1);
	
	//Exp Bar width
	pmf->m_nExpWidth = GetProfileInt("Settings", "ExpWidth", 200);
	//Exp Bar
	CString str = GetProfileString("Settings", "ExpBar");
	CString str1; 
	LOADSTR(str1 ,IDS_TITLE_HIS);
	if(str==str1)
		PostMessage(m_pMainWnd->m_hWnd, WM_COMMAND, ID_VIEW_HIS,0);
	LOADSTR(str1 ,IDS_TITLE_FAVORITE);
	if(str==str1)
		PostMessage(m_pMainWnd->m_hWnd, WM_COMMAND, ID_FAVORITES_DROPDOWN,0);
	LOADSTR(str1 ,IDS_TITLE_SHELL);
	if(str==str1)
		PostMessage(m_pMainWnd->m_hWnd, WM_COMMAND, ID_VIEW_FOLDER,0);
	LOADSTR(str1 ,IDS_TITLE_RESOURCE);
	if(str==str1)
		PostMessage(m_pMainWnd->m_hWnd, WM_COMMAND, ID_VIEW_EXPLOREBAR_RESOURCE,0);

	//autosizing tab
	pmf->m_bAutoTab = GetProfileInt("Settings", "AutoTab", 1);

	//max autosizing tab width
	pmf->m_nMaxTabWidth = GetProfileInt("Settings", "MaxTabWidth", 100);
	//min autosizing tab width
	pmf->m_nMinTabWidth = GetProfileInt("Settings", "MinTabWidth", 50);
	//
	g_bShowIndex = GetProfileInt("Settings","ShowIndex", TRUE);
	g_bShowIndex = GetProfileInt("Settings","ShowIndex", TRUE);
	g_bShowDot = GetProfileInt("Settings","ShowDot", TRUE);
	g_bShowRead = GetProfileInt("Settings","ShowRead", TRUE);
	g_bShowFavIcon = GetProfileInt("Settings","ShowFavIcon", TRUE);

	//silent
	g_bSilent = GetProfileInt("Settings", "Silent", TRUE);
	if (g_bSilent != (_RegGetString(HKEY_CURRENT_USER, 
		"Software\\Microsoft\\Internet Explorer\\Main",
		"Disable Script Debugger") == "yes" ? TRUE : FALSE))
	{
		if (g_bSilent)
			_RegSetString(HKEY_CURRENT_USER, 
				"Software\\Microsoft\\Internet Explorer\\Main",
				"Disable Script Debugger",
				"yes");
		else
			_RegSetString(HKEY_CURRENT_USER, 
				"Software\\Microsoft\\Internet Explorer\\Main",
				"Disable Script Debugger",
				"no");
	}
	//default font size
	g_nDefFontSize = GetProfileInt("Settings", "DefFontSize", 2);
	//disable scroll text on status bar
	g_bDisScrollText = GetProfileInt("Settings", "DisScrollText", FALSE);

	//filte blank popup window from same parent
	g_bFilteBlank = GetProfileInt("Settings", "FilteBlank", FALSE);

	//interval
	pmf->m_nInterval = GetProfileInt("Settings", "Interval", 0);

	//auto scroll
	pmf->m_bDefScrollAfterDL = GetProfileInt("Settings", "AutoScrollAfterDL", FALSE);
	pmf->m_bDefUseAutoScroll = GetProfileInt("Settings", "UseAutoScroll", FALSE);
	pmf->m_nDefSrSpeed = GetProfileInt("Settings", "SrSpeed", 1);
	pmf->m_nAutoScrollPage = GetProfileInt("Settings", "AutoScrollPage", 0);
	//scroll speed
	g_fSeed = (float)GetProfileInt("Settings", "SpeedSeed", 100);
	if(g_fSeed == 0)
		g_fSeed = 1;
	else
		g_fSeed = g_fSeed/100;

	//start group
	pmf->m_strStartGroup = GetProfileString("Settings", "StartGroup", "");

	//default bg color
	pmf->m_strBGColor = GetProfileString("Settings", "BGColor", "#FFFFFF");

	//default auto refresh
	pmf->m_nDefRefreshInterval = GetProfileInt("Settings", "AutoRefresh", 60);

	//animate icon
	pmf->m_bAnimatIcon = GetProfileInt("Settings", "AnimateIcon", TRUE);

	//lock homepage
	g_bLockHomepage = GetProfileInt("Settings", "LockHomepage", FALSE);

	pmf->m_bMouseCtrlScrSpeed = GetProfileInt("Settings", "MouseCtrlSpeed", FALSE);
	pmf->m_bDisDownActivex = GetProfileInt("Settings", "DisDownActivex", TRUE);

	//down
	pmf->m_nDownAll = GetProfileInt("Settings", "DownAll", 0);
	//
	pmf->m_nCollectorTrans = GetProfileInt("Settings", "CollectorTrans", 255);
	pmf->m_nMonitorTrans = GetProfileInt("Settings", "MonitorTrans", 180);
}

void CVeryIEApp::SaveConfg()
{
	try{
	//proxy
	if(g_bProxyDirty)
		pmf->m_aProxyCategories.SaveProxies();
	g_bProxyDirty = FALSE;

	//pop filter
	WriteProfileInt("Settings", "KillPop", g_bKillPop);
	WriteProfileInt("Settings", "KillAutoWin", g_bKillAutoWin);
	WriteProfileInt("Settings", "KillDupWin", g_bKillDupWin);
	WriteProfileInt("Settings", "KillListWin", g_bKillListWin);
	//content filter
	WriteProfileInt("Settings", "UseUrlFilter", pmf->m_bUseUrlFilter);
	WriteProfileInt("Settings", "UseFlyingFilter", pmf->m_bUseFlyingFilter);
	WriteProfileInt("Settings", "UseDialogFilter", pmf->m_bUseDialogFilter);
	WriteProfileInt("Settings", "EnableFilter", pmf->m_nEnableFilter);
	//
	WriteProfileInt("Settings", "DisDownActivex", pmf->m_bDisDownActivex);
	//else
	WriteProfileInt("Settings", "TabSize", pmf->m_nTitleLen);

	BYTE *tmp = NULL;
	int i = 1;

	//save defaul web proxy
	WriteProfileString("Settings","DefaultWebProxy", pmf->m_strDefaultWebProxy);
	
	//save defaul  proxy
	WriteProfileString("Settings","CurrentProxy", pmf->m_strCurProxy);
	WriteProfileString("Settings","CurrentProxyName", pmf->m_strCurProxyName);
	WriteProfileString("Settings","ProxyByPass", pmf->m_strProxyByPass);

	//active new
	WriteProfileInt("Settings", "ActiveNew", pmf->m_bActiveNewWindow);
	WriteProfileInt("Settings", "LinkInNewWindow", g_bLinkInNewWindow);
	//start favorite folder
	WriteProfileString("Settings","StartFolder", pmf->m_strStartFavFolder);

	//multiline tab
	WriteProfileInt("Settings", "MultiLineTab", pmf->m_bMultiLineTab);

	//insert to next tab
	WriteProfileInt("Settings", "NewSequence", pmf->m_nNewSequence);

	//Background PIC
	WriteProfileString("Settings", "SkinName", pmf->m_strSkinName);

	//Exp Bar
	CString str="";
	if(pmf->m_wndInstantBar.GetSafeHwnd()==NULL)
		str = "";
	else if(pmf->m_wndInstantBar.IsVisible())
		pmf->m_wndInstantBar.GetWindowText(str);
	WriteProfileString("Settings", "ExpBar", str);
	if(pmf->m_wndInstantBar.GetSafeHwnd()!=NULL)
	{
		CRect rect;
		pmf->m_wndInstantBar.GetWindowRect(&rect);
		WriteProfileInt("Settings", "ExpWidth", rect.Width());
	}

	//text label
	WriteProfileInt("Settings", "TextLabel", pmf->m_nTextLabel);
	//text label
	WriteProfileInt("Settings", "ColorIcon", pmf->m_bColorIcon);

	//autosizing tab
	WriteProfileInt("Settings","AutoTab", pmf->m_bAutoTab);

	//max autosizing tab width
	WriteProfileInt("Settings","MaxTabWidth", pmf->m_nMaxTabWidth);
	//min autosizing tab width
	WriteProfileInt("Settings","MinTabWidth", pmf->m_nMinTabWidth);

	//defaut font size
	WriteProfileInt("Settings", "DefFontSize", g_nDefFontSize);
	//!disable scroll text on statusbar
	WriteProfileInt("Settings", "DisScrollText", g_bDisScrollText);

	//auto scroll
	WriteProfileInt("Settings", "AutoScrollAfterDL", pmf->m_bDefScrollAfterDL); 
	WriteProfileInt("Settings", "UseAutoScroll", pmf->m_bDefUseAutoScroll);
	WriteProfileInt("Settings", "SrSpeed", pmf->m_nDefSrSpeed);
	WriteProfileInt("Settings", "AutoScrollPage", pmf->m_nAutoScrollPage);

	//start group
	WriteProfileString("Settings", "StartGroup", pmf->m_strStartGroup);

	//default bg color
	WriteProfileString("Settings", "BGColor", pmf->m_strBGColor);

	//default auto refresh
	WriteProfileInt("Settings", "AutoRefresh", pmf->m_nDefRefreshInterval);

	//toolbar icon
	WriteProfileInt("Settings", "SmallToolbar", pmf->m_bSmallToolBar);

	//auto set background
	WriteProfileInt("Settings", "AnimateIcon", pmf->m_bAnimatIcon);
	WriteProfileInt("Settings", "LockHomepage", g_bLockHomepage);
	WriteProfileInt("Settings", "MouseCtrlSpeed", pmf->m_bMouseCtrlScrSpeed);

	//lock toolbar
	WriteProfileInt("Settings", "LockToolbar", pmf->m_bLockToolbar);

	// search key
	pmf->SaveSearchKey();
	//
	WriteProfileInt("Settings", "DefaultCharSet", pmf->m_nDefaultCharSet);
	//
	WriteProfileInt("Settings", "GroupMenuShowMember", pmf->m_bGroupMenuShowMember);
	WriteProfileInt("Settings", "CloseAllBeforeNewGroup", pmf->m_bCloseAllBeforeNewGroup);
	//
	WriteProfileInt("Settings", "DirectOpenFile", pmf->m_bDirectOpenFile);
	WriteProfileInt("Settings", "OpenInNew", pmf->m_bOpenInNew);
	//
	WriteProfileInt("Settings", "DisableBackground", pmf->m_bDisableBackground);
	//
	
	WriteProfileInt("Settings", "AutoRefreshActive", pmf->m_bAutoRefreshActive);
	//
	WriteProfileInt("Search", "SearchMatchCase", pmf->m_bSearchMatchCase);
	WriteProfileInt("Search", "SearchMatchWhole", pmf->m_bSearchMatchWhole);
	WriteProfileInt("Search", "NotSaveKeyword", pmf->m_bNotSaveKeyword);
	//
	WriteProfileInt("Settings", "PageMax", g_bMax);
	WriteProfileInt("Settings", "AutoRunExternal", pmf->m_bAutoRunExternal);

	//must place here, for that this can be changed in status bar
	WriteProfileInt("Mouse", "RMouseDrag", pmf->m_bRMouseDrag );
	WriteProfileInt("Mouse", "RMouseGesture", pmf->m_bRMouseGesture );
	WriteProfileString("Settings", "SortSaveFolder", pmf->m_strSortSaveFolder);
	WriteProfileInt("Settings", "ShowSortSaveDlg", pmf->m_bShowSortSaveDlg );

	}catch(...){}
}

BOOL CVeryIEApp::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class
	try{
	if(pmf!=NULL)
	{
		if( pmf->m_bFavDirty && m_nDelay>30 )
		{
			pmf->PostMessage(WM_UPDATE_FAV,pmf->m_bFavDirty,0);
			pmf->m_bFavDirty = FALSE;
			m_nDelay=0;
		}
		else if(pmf->m_bFavDirty)
			m_nDelay++;

		if(pmf->m_bSaveConfig)
		{
			pmf->m_bSaveConfig = FALSE;
			AfxBeginThread(TSaveConfig, NULL);
		}
	}
	//
	if (lCount <= 0)
	{
		ThreadOnIdle(lCount);
	}
	else if (lCount == 1)
	{
		ThreadOnIdle(lCount);
	}
	return lCount < 1;  // more to do if lCount < 1

	}
	catch(...)
	{
		return lCount < 1;
	}
}

BOOL CVeryIEApp::ThreadOnIdle(LONG lCount)
{
	ASSERT_VALID(this);

	try{
	if (lCount <= 0)
	{
	}
	else if (lCount >= 0)
	{
		AFX_MODULE_THREAD_STATE* pState = _AFX_CMDTARGET_GETSTATE()->m_thread;
		if (pState->m_nTempMapLock == 0)
		{
			// free temp maps, OLE DLLs, etc.
			AfxLockTempMaps();
			AfxUnlockTempMaps();
		}
	}
	}catch(...){}

	return lCount < 0;  // nothing more to do if lCount >= 0
}

//#######################################################################################
CVeryIEModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_VeryIENSHandle, CVeryIENSHandle)
END_OBJECT_MAP()

LONG CVeryIEModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG CVeryIEModule::Lock()
{
	AfxOleLockApp();
	return 1;
}
LPCTSTR CVeryIEModule::FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
	while (*p1 != NULL)
	{
		LPCTSTR p = p2;
		while (*p != NULL)
		{
			if (*p1 == *p)
				return CharNext(p1);
			p = CharNext(p);
		}
		p1++;
	}
	return NULL;
}

BOOL CVeryIEApp::InitATL()
{
	m_bATLInited = TRUE;
	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	_Module.dwThreadID = GetCurrentThreadId();

	LPTSTR lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
	TCHAR szTokens[] = _T("-/");

	BOOL bRun = TRUE;
	LPCTSTR lpszToken = _Module.FindOneOf(lpCmdLine, szTokens);
	while (lpszToken != NULL)
	{
		if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_VeryIE, FALSE);
			_Module.UnregisterServer(TRUE); //TRUE means typelib is unreg'd
			bRun = FALSE;
			break;
		}
		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_VeryIE, TRUE);
			_Module.RegisterServer(TRUE);
			bRun = FALSE;
			break;
		}
		lpszToken = _Module.FindOneOf(lpszToken, szTokens);
	}

	if (!bRun)
	{
		m_bATLInited = FALSE;
		_Module.Term();
		return FALSE;
	}

	HRESULT hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
		REGCLS_MULTIPLEUSE);
	if (FAILED(hRes))
	{
		m_bATLInited = FALSE;
		return FALSE;
	}	

	return TRUE;
}


//#pragma optimize( "s", on )

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
#ifdef _WRITE_LNG_FILE_
	_WriteDlgString(this,"DialogAbout");
	this->OnCancel();
	return TRUE;
#endif
	LOADDLG("DialogAbout");
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CWnd *p;
	CString strAbout;

	if (theApp.m_bUseLngFile)
	{
		p= GetDlgItem(IDC_ABOUT);
		p->GetWindowText(strAbout);
		p->SetWindowText(strAbout);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

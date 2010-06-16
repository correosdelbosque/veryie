# Microsoft Developer Studio Project File - Name="VeryIE" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VeryIE - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VeryIE.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VeryIE.mak" CFG="VeryIE - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VeryIE - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VeryIE - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VeryIE - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Wsock32.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"../release/HackerBrowser.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "VeryIE - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "VeryIE___Win32_Debug"
# PROP BASE Intermediate_Dir "VeryIE___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /ZI /Od /D "WIN32" /D "_WINDOWS" /Fr /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /I "./proxy" /I "./" /D "WIN32" /D "_WINDOWS" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /win32
# SUBTRACT BASE MTL /mktyplib203
# ADD MTL /nologo /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Wsock32.lib pdh.lib Delayimp.lib /nologo /subsystem:windows /profile /map /debug /machine:I386 /DELAYLOAD:pdh.dll
# ADD LINK32 Wsock32.lib winmm.lib /nologo /subsystem:windows /profile /map /debug /machine:I386 /out:"../release/HackerBrowserD.exe"

!ENDIF 

# Begin Target

# Name "VeryIE - Win32 Release"
# Name "VeryIE - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddPopupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AddressBarEx.cpp
# End Source File
# Begin Source File

SOURCE=.\AddToThisFavDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AdvTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimateIcon.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseExpObj.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ChevBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CleanAll.cpp
# End Source File
# Begin Source File

SOURCE=.\CollectorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Crypt.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomizeToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\Custsite.cpp
# End Source File
# Begin Source File

SOURCE=.\EnTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ExpMenu.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\FavTree.cpp
# End Source File
# Begin Source File

SOURCE=.\FavTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FavWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\FixedHtmlView.cpp
# End Source File
# Begin Source File

SOURCE=.\Function.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupSelectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupUrlDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HistoryTree.cpp
# End Source File
# Begin Source File

SOURCE=.\HisTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Idispimp.cpp
# End Source File
# Begin Source File

SOURCE=.\InputPassword.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuData.cpp
# End Source File
# Begin Source File

SOURCE=.\Menuorder.cpp
# End Source File
# Begin Source File

SOURCE=.\Monitor.cpp
# End Source File
# Begin Source File

SOURCE=.\OrgGroupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PopupConfirm.cpp
# End Source File
# Begin Source File

SOURCE=.\PopupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\QuickSearchDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SAPrefsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SAPrefsSubDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Scbarcf.cpp
# End Source File
# Begin Source File

SOURCE=.\Scbarg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectLang.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectURL.cpp
# End Source File
# Begin Source File

SOURCE=.\SetFormDataDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellPidl.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellTree.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ShellWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleSAH.cpp
# End Source File
# Begin Source File

SOURCE=.\SizecBar.cpp
# End Source File
# Begin Source File

SOURCE=.\SortSaveDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatusBarWithProgress.Cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\TextProgressCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\UrlFilterProp.cpp
# End Source File
# Begin Source File

SOURCE=.\VeryIE.cpp
# End Source File
# Begin Source File

SOURCE=.\VeryIE.idl
# ADD MTL /h "VeryIE_i.h" /iid "VeryIE_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\VeryIE.rc
# End Source File
# Begin Source File

SOURCE=.\VeryIEHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\VeryIENSHandle.cpp
# End Source File
# Begin Source File

SOURCE=.\VeryIEOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\VeryIEView.cpp
# End Source File
# Begin Source File

SOURCE=.\WebFileOpenDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddPopupDlg.h
# End Source File
# Begin Source File

SOURCE=.\AddressBarEx.h
# End Source File
# Begin Source File

SOURCE=.\AddToThisFavDlg.h
# End Source File
# Begin Source File

SOURCE=.\AdvTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\AnimateIcon.h
# End Source File
# Begin Source File

SOURCE=.\BaseExpObj.h
# End Source File
# Begin Source File

SOURCE=.\ChevBar.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\CleanAll.h
# End Source File
# Begin Source File

SOURCE=.\CollectorDlg.h
# End Source File
# Begin Source File

SOURCE=.\ComboBar.h
# End Source File
# Begin Source File

SOURCE=.\Crypt.h
# End Source File
# Begin Source File

SOURCE=.\CustomizeToolbar.h
# End Source File
# Begin Source File

SOURCE=.\Custsite.h
# End Source File
# Begin Source File

SOURCE=.\FavTree.h
# End Source File
# Begin Source File

SOURCE=.\FavTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\FavWnd.h
# End Source File
# Begin Source File

SOURCE=.\FixedHtmlView.h
# End Source File
# Begin Source File

SOURCE=.\Function.h
# End Source File
# Begin Source File

SOURCE=.\GroupSelectDlg.h
# End Source File
# Begin Source File

SOURCE=.\GroupUrlDlg.h
# End Source File
# Begin Source File

SOURCE=.\HistoryTree.h
# End Source File
# Begin Source File

SOURCE=.\HisTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\HtmlWnd.h
# End Source File
# Begin Source File

SOURCE=.\idispimp.h
# End Source File
# Begin Source File

SOURCE=.\InputPassword.h
# End Source File
# Begin Source File

SOURCE=.\macro.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MenuBar.h
# End Source File
# Begin Source File

SOURCE=.\MenuData.h
# End Source File
# Begin Source File

SOURCE=.\Menuorder.h
# End Source File
# Begin Source File

SOURCE=.\Monitor.h
# End Source File
# Begin Source File

SOURCE=.\OrgGroupDlg.h
# End Source File
# Begin Source File

SOURCE=.\PopupConfirm.h
# End Source File
# Begin Source File

SOURCE=.\PopupDlg.h
# End Source File
# Begin Source File

SOURCE=.\QuickSearchDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Scbarcf.h
# End Source File
# Begin Source File

SOURCE=.\Scbarg.h
# End Source File
# Begin Source File

SOURCE=.\SelectLang.h
# End Source File
# Begin Source File

SOURCE=.\SelectURL.h
# End Source File
# Begin Source File

SOURCE=.\SetFormDataDlg.h
# End Source File
# Begin Source File

SOURCE=.\ShellPidl.h
# End Source File
# Begin Source File

SOURCE=.\ShellTree.h
# End Source File
# Begin Source File

SOURCE=.\ShellTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ShellWnd.h
# End Source File
# Begin Source File

SOURCE=.\SimpleSAH.h
# End Source File
# Begin Source File

SOURCE=.\Sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\SortSaveDlg.h
# End Source File
# Begin Source File

SOURCE=.\StatusBarWithProgress.H
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TabDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\TextProgressCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ToolMenu.h
# End Source File
# Begin Source File

SOURCE=.\TxtDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\UrlFilterProp.h
# End Source File
# Begin Source File

SOURCE=.\VeryIE.h
# End Source File
# Begin Source File

SOURCE=.\VeryIEHelper.h
# End Source File
# Begin Source File

SOURCE=.\VeryIENSHandle.h
# End Source File
# Begin Source File

SOURCE=.\VeryIEOptions.h
# End Source File
# Begin Source File

SOURCE=.\VeryIEView.h
# End Source File
# Begin Source File

SOURCE=.\WebFileOpenDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\CollectorTool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\drag.cur
# End Source File
# Begin Source File

SOURCE=.\RES\FavExp.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\LinkList.Bmp
# End Source File
# Begin Source File

SOURCE=.\RES\LinkList.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\mainfrm.ico
# End Source File
# Begin Source File

SOURCE=.\RES\normal.ico
# End Source File
# Begin Source File

SOURCE=.\res\page.ico
# End Source File
# Begin Source File

SOURCE=.\res\proxy.bmp
# End Source File
# Begin Source File

SOURCE=.\res\refresh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\save.ico
# End Source File
# Begin Source File

SOURCE=.\res\secure.ico
# End Source File
# Begin Source File

SOURCE=.\RES\TaskBar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\treelist.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VeryIE.rc2
# End Source File
# Begin Source File

SOURCE=.\VeryIE.rgs
# End Source File
# Begin Source File

SOURCE=.\res\VeryIENSHandle.rgs
# End Source File
# End Group
# Begin Group "proxy"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\proxy\InputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\proxy\InputDlg.h
# End Source File
# Begin Source File

SOURCE=.\proxy\LinkListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\proxy\LinkListDlg.h
# End Source File
# Begin Source File

SOURCE=.\proxy\ProxyInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\proxy\ProxyInfo.h
# End Source File
# Begin Source File

SOURCE=.\proxy\ProxyList.cpp
# End Source File
# Begin Source File

SOURCE=.\proxy\ProxyList.h
# End Source File
# Begin Source File

SOURCE=.\proxy\SelProxyCatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\proxy\SelProxyCatDlg.h
# End Source File
# Begin Source File

SOURCE=.\proxy\SetProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\proxy\SetProxy.h
# End Source File
# Begin Source File

SOURCE=.\proxy\SortListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\proxy\SortListCtrl.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\VeryIE.reg
# End Source File
# End Target
# End Project
# Section VeryIE : {01710002-7E02-0173-02BA-580102187D01}
# 	1:8:IDR_VeryIE:102
# End Section

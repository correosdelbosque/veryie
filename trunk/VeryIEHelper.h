// VeryIEHelper.h: interface for the CVeryIEHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VeryIEHELPER_H__74460E23_1598_11D4_9BCE_0000E85300AE__INCLUDED_)
#define AFX_VeryIEHELPER_H__74460E23_1598_11D4_9BCE_0000E85300AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VeryIEView.h"

CVeryIEView* GetCurrentView(int nFlag = 0, BOOL bInNewWindow = FALSE);
CVeryIEView * CreateNewView();

#endif // !defined(AFX_VeryIEHELPER_H__74460E23_1598_11D4_9BCE_0000E85300AE__INCLUDED_)

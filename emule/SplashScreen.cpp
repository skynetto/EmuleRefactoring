//this file is part of eMule
//Copyright (C)2002-2010 Merkur ( strEmail.Format("%s@%s", "devteam", "emule-project.net") / http://www.emule-project.net )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#include "stdafx.h"
#include <SplashScreen.h>
#include <EnBitmap.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CSplashScreen, CDialog)

BEGIN_MESSAGE_MAP(CSplashScreen, CDialog)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

CSplashScreen::CSplashScreen(CWnd* pParent /*=NULL*/)
	: CDialog(CSplashScreen::IDD, pParent)
	, m_timeToLive{ _UI32_MAX }
	, m_timeEvent{0}
	, m_emuleVersion{}
{
}

CSplashScreen::CSplashScreen(CWnd* pParent, uint32 timeToLive, const CString& version)
	: CDialog(CSplashScreen::IDD, pParent)
	, m_emuleVersion{ version }
	, m_timeToLive{ timeToLive }
	, m_timeEvent{timeToLive}
{
}

CSplashScreen::~CSplashScreen()
{
	m_imgSplash.DeleteObject();
}

void CSplashScreen::SetVersion(const CString& version)
{
	m_emuleVersion = version;
}

void CSplashScreen::SetTimeout(uint32 timeToLive)
{
	m_timeToLive = timeToLive;
}

BOOL CSplashScreen::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetTimer(m_timeEvent, m_timeToLive, NULL);

	CEnBitmap bmp;
	if (bmp.LoadImage(_T("ABOUT"), _T("JPG")))
	{
		VERIFY(m_imgSplash.Attach((HBITMAP)bmp.Detach()));

		if (m_imgSplash.GetSafeHandle()) {
			BITMAP bmp;
			if (m_imgSplash.GetBitmap(&bmp)) {
				WINDOWPLACEMENT wp;
				GetWindowPlacement(&wp);
				wp.rcNormalPosition.right = wp.rcNormalPosition.left + bmp.bmWidth;
				wp.rcNormalPosition.bottom = wp.rcNormalPosition.top + bmp.bmHeight;
				SetWindowPlacement(&wp);
			}
		}
	}

	return TRUE;
}

BOOL CSplashScreen::PreTranslateMessage(MSG *pMsg)
{
	switch (pMsg->message) {
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_NCLBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
	case WM_NCMBUTTONDOWN:
		OnClose();
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CSplashScreen::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if (m_imgSplash.GetSafeHandle()) {
		CDC dcMem;
		if (dcMem.CreateCompatibleDC(&dc)) {
			CBitmap *pOldBM = dcMem.SelectObject(&m_imgSplash);
			BITMAP BM;
			m_imgSplash.GetBitmap(&BM);
			dc.BitBlt(0, 0, BM.bmWidth, BM.bmHeight, &dcMem, 0, 0, SRCCOPY);
			if (pOldBM)
				dcMem.SelectObject(pOldBM);

			CRect rc(0, BM.bmHeight * 65 / 100, BM.bmWidth, BM.bmHeight);
			dc.FillSolidRect(rc.left + 1, rc.top + 1, rc.Width() - 2, rc.Height() - 2, RGB(255, 255, 255));

			LOGFONT lf = {};
#ifdef _BOOTSTRAPNODESDAT
			lf.lfHeight = 24;
#else
#if defined(_DEBUG) && (defined(_BETA) || defined(_DEVBUILD))
			lf.lfHeight = 28;
#else
			lf.lfHeight = 30;
#endif
#endif
			lf.lfWeight = FW_BOLD;
			lf.lfQuality = ANTIALIASED_QUALITY;
			_tcscpy(lf.lfFaceName, _T("Arial"));
			CFont font;
			font.CreateFontIndirect(&lf);
			CFont *pOldFont = dc.SelectObject(&font);
			rc.top += dc.DrawText(m_emuleVersion, &rc, DT_CENTER | DT_NOPREFIX);
			if (pOldFont)
				dc.SelectObject(pOldFont);
			font.DeleteObject();

			rc.top += 8;

			lf.lfHeight = 14;
			lf.lfWeight = FW_NORMAL;
			lf.lfQuality = ANTIALIASED_QUALITY;
			_tcscpy(lf.lfFaceName, _T("Arial"));
			font.CreateFontIndirect(&lf);
			pOldFont = dc.SelectObject(&font);
			dc.DrawText(_T("Copyright (C) 2002-2020 Merkur"), &rc, DT_CENTER | DT_NOPREFIX);
			if (pOldFont)
				dc.SelectObject(pOldFont);
			font.DeleteObject();
		}
	}
}

void CSplashScreen::OnTimer(UINT_PTR nIDEvent)
{
	PostMessage(WM_CLOSE);
	CDialog::OnTimer(nIDEvent);
}


void CSplashScreen::OnClose()
{	
	KillTimer(m_timeEvent);
	EndDialog(IDOK);
	CDialog::OnClose();
}

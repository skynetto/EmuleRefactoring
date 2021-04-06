#pragma once
#include <Resource.h>

class CSplashScreen : public CDialog
{
	DECLARE_DYNAMIC(CSplashScreen)

	enum
	{
		IDD = IDD_SPLASH
	};

public:
	explicit CSplashScreen(CWnd* pParent = NULL); // standard constructor
	explicit CSplashScreen(CWnd *pParent , uint32 timetoLive, const CString & version);   
	virtual	~CSplashScreen();

	void SetVersion(const CString& version);
	void SetTimeout(uint32 timeToLive);

protected:
	CBitmap m_imgSplash;

	BOOL OnInitDialog();
	void OnPaint();
	BOOL PreTranslateMessage(MSG *pMsg);
private:
	CString m_emuleVersion;
	uint32 m_timeToLive;
	UINT_PTR m_timeEvent;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
};
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
	explicit CSplashScreen(CWnd *pParent = NULL);   // standard constructor
	virtual	~CSplashScreen();

	void SetVersion(const CString& version);

protected:
	CBitmap m_imgSplash;

	BOOL OnInitDialog();
	void OnPaint();
	BOOL PreTranslateMessage(MSG *pMsg);
private:
	CString m_emuleVersion;

	DECLARE_MESSAGE_MAP()
};
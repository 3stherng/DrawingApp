#pragma once

class CApp : public CWinApp
{
public:
	CApp() noexcept;
	virtual BOOL InitInstance() override;
	virtual int ExitInstance() override;

public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
};

extern CApp drawing_app;

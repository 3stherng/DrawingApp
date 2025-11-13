#pragma once

class CAboutDlg : public CDialogEx
{
protected:
  virtual void DoDataExchange(CDataExchange* pDX);

public:
  CAboutDlg() noexcept;

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_ABOUTBOX };
#endif
};

#include "pch.h"
#include "CDialogBoxGeneric.h"

IMPLEMENT_DYNAMIC(CDialogBoxGeneric, CDialogEx)

CMFCPropertyGridProperty* CDialogBoxGeneric::_AddTopic(CMFCPropertyGridCtrl& i_property_grid, 
                                                       std::wstring i_topic_name)
{
  auto property = std::make_unique<CMFCPropertyGridProperty>(i_topic_name.c_str());
  i_property_grid.AddProperty(property.get());
  return property.release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CDialogBoxGeneric::_GetDialogWidth()
{
  CRect dialogRect;
  GetClientRect(&dialogRect);
  return dialogRect.Width();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CDialogBoxGeneric::_GetDialogHeight()
{
  CRect dialogRect;
  GetClientRect(&dialogRect);
  return dialogRect.Height();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CDialogBoxGeneric::OnInitDialog()
{
  CDialog::OnInitDialog();

  _SetWindowTitle();

  int button_width = _GetDialogWidth() / 5;
  int button_height = _GetDialogHeight() / 10;

  // TODO: Use smart pointers
  CButton* apply_button = new CButton;
  apply_button->Create(L"Apply",
                       WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                       CRect(10, 10, 10 + button_width, 10 + button_height),
                       this,
                       IDOK);

  CButton* cancel_button = new CButton;
  cancel_button->Create(L"Cancel",
                        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                        CRect(20 + button_width, 10, 20 + 2 * button_width, 10 + button_height),
                        this,
                        IDCANCEL);

  _CreatePropertyGrid();

  return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxGeneric::OnCancel()
{
  DestroyWindow();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxGeneric::PostNcDestroy()
{
  AfxGetMainWnd()->SendMessage(WM_OPERATION_DIALOG_DESTROYED, 0, 0);
  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0, 0);
}

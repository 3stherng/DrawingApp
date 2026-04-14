#pragma once

#include "resource.h"

class CDialogBoxGeneric : public CDialogEx
{
  DECLARE_DYNAMIC(CDialogBoxGeneric)

private:
  int _GetDialogWidth();
  int _GetDialogHeight();

protected:
  virtual void _CreateTempObject() = 0;
  virtual void _CreatePropertyGrid() = 0;
  virtual void _SetWindowTitle() = 0;

  virtual BOOL OnInitDialog() override;
  virtual void DoDataExchange(CDataExchange* pDX) override = 0;
  virtual void OnOK() override = 0;
  virtual void OnCancel() override;
  virtual void PostNcDestroy() override;

  CMFCPropertyGridProperty* _AddTopic(CMFCPropertyGridCtrl& i_property_grid, std::wstring i_topic_name);
  
  template <typename TType>
  CMFCPropertyGridProperty* _AddStaticProperty(CMFCPropertyGridProperty* i_topic,
                                               std::wstring i_parameter_name,
                                               TType i_value)
  {
    auto property = std::make_unique<CMFCPropertyGridProperty>(i_parameter_name.c_str(), i_value, L"");
    property->Enable(FALSE);
    property->AllowEdit(FALSE);
    i_topic->AddSubItem(property.get());
    return property.release();
  }

  template <typename TType>
  CMFCPropertyGridProperty* _AddDynamicProperty(CMFCPropertyGridProperty* i_topic,
                                                std::wstring i_parameter_name,
                                                TType i_value)
  {
    auto property = std::make_unique<CMFCPropertyGridProperty>(i_parameter_name.c_str(), i_value, L"");
    property->AllowEdit(TRUE);
    i_topic->AddSubItem(property.get());
    return property.release();
  }

public:
  explicit CDialogBoxGeneric(CWnd* pParent) {};
  virtual ~CDialogBoxGeneric() {};

  virtual void GeneratePreviewObject() = 0;

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG_GENERIC };
#endif

protected:
  virtual afx_msg LRESULT OnGridItemChanged(WPARAM wParam, LPARAM lParam) = 0;
};

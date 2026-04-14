#pragma once

#include "CDialogBoxPropertiesGeneric.h"
#include "DrawShapesHelper.h"

class CChildView : public CWnd
{
private:
  std::unique_ptr<CDialogEx> mp_properties_dialog_box;
  DrawShapesHelper m_draw_shape_helper;

  void _DrawObjects(CDC& device_context);
  void _CreateDialog(std::unique_ptr<CDialogBoxPropertiesGeneric> ip_dialog_box);

protected:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;

public:
  CChildView() : mp_properties_dialog_box(nullptr) {};
  virtual ~CChildView() {};

protected:
  afx_msg void OnPaint();
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg LRESULT OnCommandPropertiesDialogDestroyed(WPARAM wParam, LPARAM IParam);
  DECLARE_MESSAGE_MAP()
};

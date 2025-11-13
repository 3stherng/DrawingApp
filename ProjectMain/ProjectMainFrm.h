#pragma once

#include "CDialogBoxGeneric.h"
#include "ProjectChildView.h"
#include "GUIDrawObjects.h"

class CMainFrame : public CFrameWnd
{
private:
  bool is_drawing_feature_active;
  CChildView m_child_view;
  std::shared_ptr<CDialogEx> mp_dialog;
  std::shared_ptr<GUIDrawObjects> mp_active_gui_draw_feature;

  void _CreateMenu();
  void _CreateDialog(std::unique_ptr<CDialogBoxGeneric> ip_dialog_box);
  void _DeactivateDrawingFeature();

public:
  CMainFrame() noexcept : mp_dialog(nullptr), mp_active_gui_draw_feature(nullptr), is_drawing_feature_active(false) {};
  virtual ~CMainFrame() {};

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs) override;
  virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) override;
  
  std::shared_ptr<CDialogEx> GetActiveDialog() { return mp_dialog; }
  std::shared_ptr<GUIDrawObjects> GetActiveGuiDrawFeature() { return mp_active_gui_draw_feature; }

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  DECLARE_DYNAMIC(CMainFrame)

  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  
  afx_msg LRESULT OnCommandOperationDialogDestroyed(WPARAM wParam, LPARAM IParam);
  afx_msg LRESULT OnCommandPropertiesDialogDestroyed(WPARAM wParam, LPARAM IParam);
  afx_msg LRESULT OnCommandRedrawEverything(WPARAM wParam, LPARAM IPraram);

  afx_msg void OnCreateCircleMenuClicked();
  afx_msg void OnCreateLineMenuClicked();
  afx_msg void OnCreateRectangleMenuClicked();
  afx_msg void OnDrawCircleToggled();
  afx_msg void OnDrawLineToggled();
  afx_msg void OnDrawRectangleToggled();
  afx_msg void OnRedoMenuClicked();
  afx_msg void OnUndoMenuClicked();
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg BOOL PreTranslateMessage(MSG* pMsg);

  DECLARE_MESSAGE_MAP()
};

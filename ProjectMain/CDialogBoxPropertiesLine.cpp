#include "pch.h"

#include "CDialogBoxPropertiesLine.h"
#include "ProjectChildView.h"
#include "ProjectMain.h"
#include "MFCUtilities.h"

#include <ProjectBase/UIOperationChangeColor.h>


CDialogBoxPropertiesLine::CDialogBoxPropertiesLine(std::shared_ptr<IObject> ip_line)
  : CDialogBoxPropertiesGeneric(nullptr)
  , mp_line(std::dynamic_pointer_cast<Object::CLine>(ip_line))
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CDialogBoxPropertiesLine::~CDialogBoxPropertiesLine()
{
  mp_line->SetObjectSelectionFalse();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxPropertiesLine::_SetWindowTitle()
{
  std::wstring name = mp_line->GetName() + L"-" + mp_line->GetObjectID();
  SetWindowText(name.c_str());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxPropertiesLine::_CreatePropertyGrid()
{
  HDITEM item;
  item.cxy = 120;
  item.mask = HDI_WIDTH;

  CRect rectPropertyGrid;
  rectPropertyGrid.SetRect(10, 10, 300, 200);
  m_property_grid.GetHeaderCtrl().SetItem(0, new HDITEM(item));

  auto p_topic_parameters = _AddTopic(m_property_grid, MFCUtilities::LoadStringW(IDS_PARAMETERS).c_str());

  _AddColorProperty(p_topic_parameters,
                    MFCUtilities::LoadStringW(IDS_COLOR),
                    MFCUtilities::ConvertVectorColorToRGB(mp_line->GetColor()));
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_POINT_FROM_X),
                             mp_line->GetPointFrom()[0]);
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_POINT_FROM_Y),
                             mp_line->GetPointFrom()[1]);
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_POINT_TO_X),
                             mp_line->GetPointTo()[0]);
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_POINT_TO_Y),
                             mp_line->GetPointTo()[1]);
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_LENGTH),
                             mp_line->GetLength());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDialogBoxPropertiesLine, CDialogEx)
  ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnGridItemChanged)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CDialogBoxPropertiesLine::OnGridItemChanged(WPARAM wParam, LPARAM lParam)
{
  UNREFERENCED_PARAMETER(lParam);

  if (wParam != IDC_MFCPROPERTYGRID) // Ensure it's the correct grid control
    return -1;

  if (const auto p_changed_prop = m_property_grid.GetCurSel(); p_changed_prop)
    if (auto pColorProp = dynamic_cast<CMFCPropertyGridColorProperty*>(p_changed_prop); pColorProp)
    {
      auto p_operation_change_color = std::make_shared<UIOperationChangeColor>();
      p_operation_change_color->SetParameters(std::dynamic_pointer_cast<IObject>(mp_line),
                                              MFCUtilities::ConvertRGBToVectorColor(pColorProp->GetColor()));
      p_operation_change_color->DoOperation();
    }

  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxPropertiesLine::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_MFCPROPERTYGRID, m_property_grid);
}

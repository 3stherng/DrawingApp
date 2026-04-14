#include "pch.h"

#include "CDialogBoxPropertiesCircle.h"
#include "MFCUtilities.h"

#include <ProjectBase/UIOperationChangeColor.h>

CDialogBoxPropertiesCircle::CDialogBoxPropertiesCircle(std::shared_ptr<IObject> ip_circle)
  : CDialogBoxPropertiesGeneric(nullptr)
  , mp_circle(std::dynamic_pointer_cast<Object::CCircle>(ip_circle))
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CDialogBoxPropertiesCircle::~CDialogBoxPropertiesCircle()
{
  mp_circle->SetObjectSelectionFalse();
  mp_circle->SetBorderColor({ 0,0,0 });
  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxPropertiesCircle::_SetWindowTitle()
{
  std::wstring name = mp_circle->GetName() + L"-" + mp_circle->GetObjectID();
  SetWindowText(name.c_str());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxPropertiesCircle::_CreatePropertyGrid()
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
                    MFCUtilities::ConvertVectorColorToRGB(mp_circle->GetColor()));
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_CENTER_POINT_X),
                             mp_circle->GetCenterPoint()[0]);
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_CENTER_POINT_Y),
                             mp_circle->GetCenterPoint()[1]);
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_DIAMETER),
                             mp_circle->GetDiameter());
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_SURFACE_AREA),
                             mp_circle->GetSurfaceArea());
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_PERIMETER),
                             mp_circle->GetPerimeter());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDialogBoxPropertiesCircle, CDialogEx)
  ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnGridItemChanged)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CDialogBoxPropertiesCircle::OnGridItemChanged(WPARAM wParam, LPARAM lParam)
{
  UNREFERENCED_PARAMETER(lParam);

  if (wParam != IDC_MFCPROPERTYGRID) // Ensure it's the correct grid control
    return -1;
  
  if (const auto p_changed_prop = m_property_grid.GetCurSel(); p_changed_prop)
    if (const auto pColorProp = dynamic_cast<CMFCPropertyGridColorProperty*>(p_changed_prop); pColorProp)
    {
      auto p_operation_change_color = std::make_shared<UIOperationChangeColor>();
      p_operation_change_color->SetParameters(std::dynamic_pointer_cast<IObject>(mp_circle),
                                              MFCUtilities::ConvertRGBToVectorColor(pColorProp->GetColor()));
      p_operation_change_color->DoOperation();
    }

  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxPropertiesCircle::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_MFCPROPERTYGRID, m_property_grid);
}

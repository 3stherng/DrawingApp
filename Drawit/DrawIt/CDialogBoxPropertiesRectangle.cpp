#include "pch.h"

#include "CDialogBoxPropertiesRectangle.h"
#include "ProjectChildView.h"
#include "ProjectMain.h"
#include "MFCUtilities.h"

#include <ProjectBase/UIOperationChangeColor.h>


CDialogBoxPropertiesRectangle::CDialogBoxPropertiesRectangle(std::shared_ptr<IObject> ip_rectangle)
  : CDialogBoxPropertiesGeneric(nullptr)
  , mp_rectangle(std::dynamic_pointer_cast<Object::CRectangle>(ip_rectangle))
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CDialogBoxPropertiesRectangle::~CDialogBoxPropertiesRectangle()
{
  mp_rectangle->SetObjectSelectionFalse();
  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxPropertiesRectangle::_SetWindowTitle()
{
  std::wstring name = mp_rectangle->GetName() + L"-" + mp_rectangle->GetObjectID();
  SetWindowText(name.c_str());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDialogBoxPropertiesRectangle, CDialogEx)
  ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnGridItemChanged)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxPropertiesRectangle::_CreatePropertyGrid()
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
                    MFCUtilities::ConvertVectorColorToRGB(mp_rectangle.get()->GetColor()));
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_CENTER_POINT_X),
                             mp_rectangle->GetCenterPoint()[0]);
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_CENTER_POINT_Y),
                             mp_rectangle->GetCenterPoint()[1]);
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_DIMENSION_X),
                             mp_rectangle->GetDimensionX());
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_DIMENSION_Y),
                             mp_rectangle->GetDimensionY());
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_SURFACE_AREA),
                             mp_rectangle->GetSurfaceArea());
  _AddStaticProperty<double>(p_topic_parameters,
                             MFCUtilities::LoadStringW(IDS_PERIMETER),
                             mp_rectangle->GetSurfaceArea());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CDialogBoxPropertiesRectangle::OnGridItemChanged(WPARAM wParam, LPARAM lParam)
{
  UNREFERENCED_PARAMETER(lParam);

  if (wParam != IDC_MFCPROPERTYGRID) // Ensure it's the correct grid control
    return -1;

  if (const auto p_changed_prop = m_property_grid.GetCurSel(); p_changed_prop)
    if (const auto pColorProp = dynamic_cast<CMFCPropertyGridColorProperty*>(p_changed_prop); pColorProp)
    {
      auto p_operation_change_color = std::make_shared<UIOperationChangeColor>();
      p_operation_change_color->SetParameters(std::dynamic_pointer_cast<IObject>(mp_rectangle),
                                              MFCUtilities::ConvertRGBToVectorColor(pColorProp->GetColor()));
      p_operation_change_color->DoOperation();
    }

  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxPropertiesRectangle::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_MFCPROPERTYGRID, m_property_grid);
}

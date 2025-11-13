#include "pch.h"
#include "CDialogBoxCreateCircle.h"

#include "DrawShapesHelper.h"
#include "resource.h"
#include "MFCUtilities.h"

#include <ProjectBase/UIOperationCreateCircle.h>

CDialogBoxCreateCircle::CDialogBoxCreateCircle()
  : CDialogBoxGeneric(nullptr)
{
  _CreateTempObject();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateCircle::_SetWindowTitle()
{
  SetWindowText(L"Create Circle");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateCircle::_CreateTempObject()
{
  mp_temp_circle = std::make_unique<Object::CCircle>(m_input_parameters.m_center_point,
                                                     m_input_parameters.m_diameter);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateCircle::GeneratePreviewObject()
{
  DrawShapesHelper draw_shape_helper;

  mp_temp_circle->SetColor(MFCUtilities::ConvertRGBToVectorColor(RGB(211, 211, 211)));
  draw_shape_helper.Draw(*mp_temp_circle);
  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateCircle::_CreatePropertyGrid()
{
  HDITEM item;
  item.cxy = 120;
  item.mask = HDI_WIDTH;

  CRect rectPropertyGrid;
  rectPropertyGrid.SetRect(10, 10, 300, 200);
  m_property_grid.GetHeaderCtrl().SetItem(0, new HDITEM(item));

  auto p_topic_parameters = _AddTopic(m_property_grid, MFCUtilities::LoadStringW(IDS_PARAMETERS));

  _AddDynamicProperty<double>(p_topic_parameters,
                              MFCUtilities::LoadStringW(IDS_CENTER_POINT_X),
                              m_input_parameters.m_center_point[0]);
  _AddDynamicProperty<double>(p_topic_parameters,
                              MFCUtilities::LoadStringW(IDS_CENTER_POINT_Y),
                              m_input_parameters.m_center_point[1]);
  mp_diameter = _AddDynamicProperty<double>(p_topic_parameters,
                                            MFCUtilities::LoadStringW(IDS_DIAMETER),
                                            m_input_parameters.m_diameter);

  auto p_topic_properties = _AddTopic(m_property_grid, MFCUtilities::LoadStringW(IDS_PROPERTIES));

  mp_surface_area = _AddStaticProperty<double>(p_topic_properties,
                                               MFCUtilities::LoadStringW(IDS_SURFACE_AREA),
                                               mp_temp_circle->GetSurfaceArea());
  mp_perimeter = _AddStaticProperty<double>(p_topic_properties,
                                            MFCUtilities::LoadStringW(IDS_PERIMETER),
                                            mp_temp_circle->GetPerimeter());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateCircle::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_MFCPROPERTYGRID, m_property_grid);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDialogBoxCreateCircle, CDialogEx)
  ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnGridItemChanged)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDialogBoxCreateCircle message handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CDialogBoxCreateCircle::OnGridItemChanged(WPARAM wParam, LPARAM lParam)
{
  UNREFERENCED_PARAMETER(lParam);

  if (wParam != IDC_MFCPROPERTYGRID) // Ensure it's the correct grid control
    return -1;

  // Question: Help, Can't think of any suitable way to avoid nesting
  
  if (const auto p_changed_prop = m_property_grid.GetCurSel(); p_changed_prop)
  {
    const CString changed_prop_name = p_changed_prop->GetName();
    const COleVariant changed_prop_value = p_changed_prop->GetValue();

    if (changed_prop_name == MFCUtilities::LoadStringW(IDS_CENTER_POINT_X).c_str())
    {
      m_input_parameters.m_center_point[0] = changed_prop_value.dblVal;
    }
    else if (changed_prop_name == MFCUtilities::LoadStringW(IDS_CENTER_POINT_Y).c_str())
    {
      m_input_parameters.m_center_point[1] = changed_prop_value.dblVal;
    }
    else if (changed_prop_name == MFCUtilities::LoadStringW(IDS_DIAMETER).c_str())
    {
      if (changed_prop_value.dblVal <= 0)
        mp_diameter->SetValue(mp_temp_circle->GetDiameter());
      else
        m_input_parameters.m_diameter = changed_prop_value.dblVal;
    }
  }

  mp_temp_circle->SetCenterPoint(m_input_parameters.m_center_point);
  mp_temp_circle->SetDiameter(m_input_parameters.m_diameter);

  m_output_parameters.m_surface_area = mp_temp_circle->GetSurfaceArea();
  m_output_parameters.m_perimeter = mp_temp_circle->GetPerimeter();

  mp_surface_area->SetValue(m_output_parameters.m_surface_area);
  mp_perimeter->SetValue(m_output_parameters.m_perimeter);

  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateCircle::OnOK()
{
  const auto p_operation = std::make_shared<UIOperationCreateCircle>();
  p_operation->SetParameters(m_input_parameters.m_center_point, m_input_parameters.m_diameter);
  try
  { 
    p_operation->DoOperation();
  }
  catch (std::exception& ex) // Posted my question in UIOperationCircle
  {
    AfxMessageBox(L"Failed Create Circle");
  }
  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
}

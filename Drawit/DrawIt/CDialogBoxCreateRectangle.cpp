#include "pch.h"
#include "CDialogBoxCreateRectangle.h"

#include "DrawShapesHelper.h"
#include "resource.h"
#include "MFCUtilities.h"

#include <ProjectBase/UIOperatiOnCreateRectangle.h>

CDialogBoxCreateRectangle::CDialogBoxCreateRectangle()
  : CDialogBoxGeneric(nullptr)
  , mp_temp_rectangle(nullptr)
{
  _CreateTempObject();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateRectangle::_CreateTempObject()
{
  mp_temp_rectangle = std::make_unique<Object::CRectangle>(m_input_parameters.m_center_point,
                                                           m_input_parameters.m_dimension_x,
                                                           m_input_parameters.m_dimension_y);

  m_output_parameters.m_surface_area = mp_temp_rectangle->GetSurfaceArea();
  m_output_parameters.m_perimeter = mp_temp_rectangle->GetPerimeter();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateRectangle::_SetWindowTitle()
{
  SetWindowText(L"Create Rectangle");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CDialogBoxCreateRectangle::_CreatePropertyGrid()
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
  mp_dimension_x = _AddDynamicProperty<double>(p_topic_parameters,
                                               MFCUtilities::LoadStringW(IDS_DIMENSION_X),
                                               m_input_parameters.m_dimension_x);
  mp_dimension_y = _AddDynamicProperty<double>(p_topic_parameters,
                                               MFCUtilities::LoadStringW(IDS_DIMENSION_Y),
                                               m_input_parameters.m_dimension_y);

  auto p_topic_properties = _AddTopic(m_property_grid, MFCUtilities::LoadStringW(IDS_PROPERTIES));

  mp_surface_area = _AddStaticProperty<double>(p_topic_properties,
                                               MFCUtilities::LoadStringW(IDS_SURFACE_AREA),
                                               m_output_parameters.m_surface_area);
  mp_perimeter = _AddStaticProperty<double>(p_topic_properties,
                                            MFCUtilities::LoadStringW(IDS_PERIMETER),
                                            m_output_parameters.m_perimeter);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateRectangle::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_MFCPROPERTYGRID, m_property_grid);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDialogBoxCreateRectangle, CDialogEx)
  ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnGridItemChanged)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDialogBoxCreateRectangle message handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CDialogBoxCreateRectangle::OnGridItemChanged(WPARAM wParam, LPARAM lParam)
{
  UNREFERENCED_PARAMETER(lParam);

  if (wParam != IDC_MFCPROPERTYGRID) // Ensure it's the correct grid control
    return -1;
  if (const auto p_changed_prop = m_property_grid.GetCurSel(); p_changed_prop)
  {
    const CString changed_prop_name = p_changed_prop->GetName();
    const COleVariant changed_value = p_changed_prop->GetValue();

    if (changed_prop_name == MFCUtilities::LoadStringW(IDS_CENTER_POINT_X).c_str())
    {
      m_input_parameters.m_center_point[0] = changed_value.dblVal;
    }
    else if (changed_prop_name == MFCUtilities::LoadStringW(IDS_CENTER_POINT_Y).c_str())
    {
      m_input_parameters.m_center_point[1] = changed_value.dblVal;
    }
    else if (changed_prop_name == MFCUtilities::LoadStringW(IDS_DIMENSION_X).c_str())
    {
      if (changed_value.dblVal <= 0)
      {
        m_input_parameters.m_dimension_x = mp_temp_rectangle->GetDimensionX();
        mp_dimension_x->SetValue(m_input_parameters.m_dimension_x);
      }
      else
        m_input_parameters.m_dimension_x = changed_value.dblVal;
    }
    else if (changed_prop_name == MFCUtilities::LoadStringW(IDS_DIMENSION_Y).c_str())
    {
      if (changed_value.dblVal <= 0)
      {
        m_input_parameters.m_dimension_y = mp_temp_rectangle->GetDimensionY();
        mp_dimension_y->SetValue(m_input_parameters.m_dimension_y);
      }
      else
        m_input_parameters.m_dimension_y = changed_value.dblVal;
    }

  }

  mp_temp_rectangle->SetCenterPoint(m_input_parameters.m_center_point);
  mp_temp_rectangle->SetDimensionX(m_input_parameters.m_dimension_x);
  mp_temp_rectangle->SetDimensionY(m_input_parameters.m_dimension_y);

  m_output_parameters.m_surface_area = mp_temp_rectangle->GetSurfaceArea();
  m_output_parameters.m_perimeter = mp_temp_rectangle->GetPerimeter();

  mp_surface_area->SetValue(m_output_parameters.m_surface_area);
  mp_perimeter->SetValue(m_output_parameters.m_perimeter);

  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateRectangle::OnOK()
{
  const auto p_operation = std::make_shared<UIOperationCreateRectangle>();

  p_operation->SetParameters(m_input_parameters.m_center_point,
                             m_input_parameters.m_dimension_x,
                             m_input_parameters.m_dimension_y);
  try
  {
    p_operation->DoOperation();
    AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
  }
  catch (std::exception& ex) // Posted my question in UIOperationCircle
  {
    AfxMessageBox(L"Failed Create Circle");
  }
}

void CDialogBoxCreateRectangle::GeneratePreviewObject()
{
  DrawShapesHelper draw_shape_helper;

  mp_temp_rectangle->SetColor(MFCUtilities::ConvertRGBToVectorColor(RGB(211, 211, 211)));
  draw_shape_helper.Draw(*mp_temp_rectangle);

  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
}

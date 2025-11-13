#include "pch.h"
#include "CDialogBoxCreateLine.h"

#include "DrawShapesHelper.h"
#include "resource.h"
#include "MFCUtilities.h"

#include <ProjectBase/UIOperatiOnCreateLine.h>


CDialogBoxCreateLine::CDialogBoxCreateLine()
  : CDialogBoxGeneric(nullptr)
{
  _CreateTempObject();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateLine::_SetWindowTitle()
{
  SetWindowText(L"Create Line");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateLine::_CreateTempObject()
{
  mp_temp_line = std::make_unique<Object::CLine>(m_input_parameters.m_point_from,
                                                 m_input_parameters.m_point_to);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateLine::GeneratePreviewObject()
{
  DrawShapesHelper draw_shape_helper;

  mp_temp_line->SetColor(MFCUtilities::ConvertRGBToVectorColor(RGB(144, 144, 144)));
  draw_shape_helper.Draw(*mp_temp_line);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateLine::_CreatePropertyGrid()
{
  HDITEM item;
  item.cxy = 120;
  item.mask = HDI_WIDTH;

  CRect rectPropertyGrid;
  rectPropertyGrid.SetRect(10, 10, 300, 200);
  m_property_grid.GetHeaderCtrl().SetItem(0, new HDITEM(item));

  auto p_topic_parameters = _AddTopic(m_property_grid, MFCUtilities::LoadStringW(IDS_PARAMETERS));

  _AddDynamicProperty<double>(p_topic_parameters,
                              MFCUtilities::LoadStringW(IDS_POINT_FROM_X),
                              m_input_parameters.m_point_from[0]);
  _AddDynamicProperty<double>(p_topic_parameters,
                              MFCUtilities::LoadStringW(IDS_POINT_FROM_Y),
                              m_input_parameters.m_point_from[1]);
  _AddDynamicProperty<double>(p_topic_parameters,
                              MFCUtilities::LoadStringW(IDS_POINT_TO_X),
                              m_input_parameters.m_point_to[0]);
  _AddDynamicProperty<double>(p_topic_parameters,
                              MFCUtilities::LoadStringW(IDS_POINT_TO_Y),
                              m_input_parameters.m_point_to[1]);

  auto p_topic_properties = _AddTopic(m_property_grid, MFCUtilities::LoadStringW(IDS_PROPERTIES));

  mp_length = _AddStaticProperty<double>(p_topic_properties,
                                         MFCUtilities::LoadStringW(IDS_LENGTH),
                                         m_output_parameters.m_length);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateLine::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_MFCPROPERTYGRID, m_property_grid);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDialogBoxCreateLine, CDialogEx)
  ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnGridItemChanged)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDialogBoxCreateLine message handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CDialogBoxCreateLine::OnGridItemChanged(WPARAM wParam, LPARAM lParam)
{
  UNREFERENCED_PARAMETER(lParam);

  if (wParam != IDC_MFCPROPERTYGRID) // Ensure it's the correct grid control
    return -1;

  if (const auto p_changed_prop = m_property_grid.GetCurSel(); p_changed_prop)
  {
    const CString changed_prop_name = p_changed_prop->GetName();
    const COleVariant changed_prop_value = p_changed_prop->GetValue();

    if (changed_prop_name == MFCUtilities::LoadStringW(IDS_POINT_FROM_X).c_str())
      m_input_parameters.m_point_from[0] = changed_prop_value.dblVal;
    else if (changed_prop_name == MFCUtilities::LoadStringW(IDS_POINT_FROM_Y).c_str())
      m_input_parameters.m_point_from[1] = changed_prop_value.dblVal;
    else if (changed_prop_name == MFCUtilities::LoadStringW(IDS_POINT_TO_X).c_str())
      m_input_parameters.m_point_to[0] = changed_prop_value.dblVal;
    else if (changed_prop_name == MFCUtilities::LoadStringW(IDS_POINT_TO_Y).c_str())
      m_input_parameters.m_point_to[1] = changed_prop_value.dblVal;
  }

  mp_temp_line->SetPointFrom(m_input_parameters.m_point_from);
  mp_temp_line->SetPointTo(m_input_parameters.m_point_to);
  m_output_parameters.m_length = mp_temp_line->GetLength();
  mp_length->SetValue(m_output_parameters.m_length);

  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxCreateLine::OnOK()
{
  const auto p_operation = std::make_shared<UIOperationCreateLine>();
  p_operation->SetParameters(m_input_parameters.m_point_from, m_input_parameters.m_point_to);
  try
  {
    p_operation->DoOperation();
    AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
  }
  catch (std::exception& ex)
  {
    AfxMessageBox(L"Failed Create Line");
  }
}

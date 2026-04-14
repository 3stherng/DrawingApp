#include "pch.h"
#include "CDialogBoxPropertiesGeneric.h"

#include "MFCUtilities.h"

#include <ProjectFramework/IObject.h>
#include <ProjectFramework/IUIOperation.h>

#include "resource.h"


IMPLEMENT_DYNAMIC(CDialogBoxPropertiesGeneric, CDialogEx)

void CDialogBoxPropertiesGeneric::_AddColorProperty(CMFCPropertyGridProperty* i_topic, std::wstring i_parameter_name, COLORREF i_color)
{
	auto property = std::make_unique<CMFCPropertyGridColorProperty>(i_parameter_name.c_str(), i_color);
	property->SetColumnsNumber(5);
	i_topic->AddSubItem(property.release());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CMFCPropertyGridProperty* CDialogBoxPropertiesGeneric::_AddTopic(CMFCPropertyGridCtrl& i_property_grid, std::wstring i_topic_name)
{
	auto property = std::make_unique<CMFCPropertyGridProperty>(i_topic_name.c_str());
	i_property_grid.AddProperty(property.get());
	return property.release();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CDialogBoxPropertiesGeneric::OnInitDialog()
{
  CDialog::OnInitDialog();

  _SetWindowTitle();
  _CreatePropertyGrid();

  return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxPropertiesGeneric::OnCancel()
{
  DestroyWindow();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDialogBoxPropertiesGeneric::PostNcDestroy()
{
  AfxGetMainWnd()->SendMessage(WM_PROPERTIES_DIALOG_DESTROYED, 0, 0);
}
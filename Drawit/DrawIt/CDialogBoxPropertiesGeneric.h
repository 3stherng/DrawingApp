#pragma once

#include "resource.h"

class CDialogBoxPropertiesGeneric : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogBoxPropertiesGeneric)

protected:
	virtual void _SetWindowTitle() = 0;
	virtual void _CreatePropertyGrid() = 0;

	virtual BOOL OnInitDialog() override;
	virtual void DoDataExchange(CDataExchange* pDX) override = 0;
	virtual LRESULT OnGridItemChanged(WPARAM wParam, LPARAM lParam) = 0;
	virtual void OnCancel() override;
	virtual void PostNcDestroy() override;

	CMFCPropertyGridProperty* _AddTopic(CMFCPropertyGridCtrl& i_property_grid, std::wstring i_topic_name);
	void _AddColorProperty(CMFCPropertyGridProperty* i_topic, std::wstring i_parameter_name, COLORREF i_color);

	template <typename TType>
	void _AddStaticProperty(CMFCPropertyGridProperty* i_topic, std::wstring i_parameter_name, TType i_value)
	{
		auto property = std::make_unique<CMFCPropertyGridProperty>(i_parameter_name.c_str(), i_value, L"");
		property->AllowEdit(FALSE);
		i_topic->AddSubItem(property.release());
	}

public:
	CDialogBoxPropertiesGeneric(CWnd* pParent) : CDialogEx(IDD_DIALOG_GENERIC, pParent) {};
	virtual ~CDialogBoxPropertiesGeneric() {};

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GENERIC };
#endif
};

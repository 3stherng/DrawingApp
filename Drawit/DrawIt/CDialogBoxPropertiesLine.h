#pragma once

#include "CDialogBoxPropertiesGeneric.h"

#include <ProjectBase/CLine.h>
#include <ProjectFramework/IObject.h>


class CDialogBoxPropertiesLine final : public CDialogBoxPropertiesGeneric
{
private:
	std::shared_ptr<Object::CLine> mp_line;
	CMFCPropertyGridCtrl m_property_grid;

	void _SetWindowTitle() override;
	void _CreatePropertyGrid() override;

protected:
	void DoDataExchange(CDataExchange* pDX) override;

public:
	CDialogBoxPropertiesLine(std::shared_ptr<IObject> ip_line);
	~CDialogBoxPropertiesLine();

protected:
	virtual afx_msg LRESULT OnGridItemChanged(WPARAM wParam, LPARAM lParam) override;
	DECLARE_MESSAGE_MAP()
};

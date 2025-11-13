#pragma once

#include "CDialogBoxPropertiesGeneric.h"

#include <ProjectBase/CCircle.h>
#include <ProjectFramework/IObject.h>

class CDialogBoxPropertiesCircle final : public CDialogBoxPropertiesGeneric
{
private:
	std::shared_ptr<Object::CCircle> mp_circle;
	CMFCPropertyGridCtrl m_property_grid;

protected:
	void _SetWindowTitle() override;
	void _CreatePropertyGrid() override;
	void DoDataExchange(CDataExchange* pDX) override;

public:
	CDialogBoxPropertiesCircle(std::shared_ptr<IObject> ip_circle);
	~CDialogBoxPropertiesCircle();

protected:
	virtual afx_msg LRESULT OnGridItemChanged(WPARAM wParam, LPARAM lParam) override;
	DECLARE_MESSAGE_MAP()
};

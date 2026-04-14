#pragma once

#include "CDialogBoxPropertiesGeneric.h"

#include <ProjectBase/CRectangle.h>
#include <ProjectFramework/IObject.h>


class CDialogBoxPropertiesRectangle : public CDialogBoxPropertiesGeneric
{
private:
	std::shared_ptr<Object::CRectangle> mp_rectangle;
	CMFCPropertyGridCtrl m_property_grid;

protected:
	virtual void _SetWindowTitle() override;
	virtual void _CreatePropertyGrid() override;
	virtual void DoDataExchange(CDataExchange* pDX) override;

public:
	CDialogBoxPropertiesRectangle(std::shared_ptr<IObject> ip_object);
	~CDialogBoxPropertiesRectangle();

protected:
	virtual afx_msg LRESULT OnGridItemChanged(WPARAM wParam, LPARAM lParam) override;
	DECLARE_MESSAGE_MAP()
};

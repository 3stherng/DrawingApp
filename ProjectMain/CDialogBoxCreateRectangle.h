#pragma once

#include "CDialogBoxGeneric.h"

#include <ProjectBase/CRectangle.h>

class CDialogBoxCreateRectangle final : public CDialogBoxGeneric
{
private:
	struct InputParameters
	{
		_Vector::double2 m_center_point = { 0., 0. };
		double m_dimension_x = 300.;
		double m_dimension_y = 300.;
	};

	struct OutputParameters
	{
		double m_surface_area = 0.;
		double m_perimeter = 0.;
	};

	InputParameters m_input_parameters;
	OutputParameters m_output_parameters;
	CMFCPropertyGridCtrl m_property_grid;
	// TODO: Use smart pointers
	CMFCPropertyGridProperty* mp_dimension_x;
	CMFCPropertyGridProperty* mp_dimension_y;
	CMFCPropertyGridProperty* mp_surface_area;
	CMFCPropertyGridProperty* mp_perimeter;

	std::unique_ptr<Object::CRectangle> mp_temp_rectangle;

	void _CreateTempObject() override;
	void _SetWindowTitle() override;
	void _CreatePropertyGrid() override;

protected:
	void DoDataExchange(CDataExchange* pDX) override;
	void OnOK() override;
	void GeneratePreviewObject() override;

public:
	CDialogBoxCreateRectangle();

protected:
	virtual afx_msg LRESULT OnGridItemChanged(WPARAM wParam, LPARAM lParam) override;
	DECLARE_MESSAGE_MAP()
};

#pragma once

#include "CDialogBoxGeneric.h"

#include <ProjectBase/CCircle.h>


class CDialogBoxCreateCircle final : public CDialogBoxGeneric
{
private:
	struct InputParameters
	{
		_Vector::double2 m_center_point = { 0., 0. };
		double m_diameter = 300.;
	};

	struct OutputParameters
	{
		double m_surface_area = 0;
		double m_perimeter = 0;
	};

	InputParameters m_input_parameters;
	OutputParameters m_output_parameters;
	CMFCPropertyGridCtrl m_property_grid;
	// TODO: Use smart pointers
	CMFCPropertyGridProperty* mp_diameter;
	CMFCPropertyGridProperty* mp_surface_area;
	CMFCPropertyGridProperty* mp_perimeter;

	std::unique_ptr<Object::CCircle> mp_temp_circle = nullptr;

	void _CreateTempObject() override;
	void _SetWindowTitle() override;
	void _CreatePropertyGrid() override;

protected:
	void DoDataExchange(CDataExchange* pDX) override;
	void OnOK() override;
	void GeneratePreviewObject() override;

public:
	CDialogBoxCreateCircle();

protected:
	virtual afx_msg LRESULT OnGridItemChanged(WPARAM wParam, LPARAM lParam) override;
	DECLARE_MESSAGE_MAP()
};

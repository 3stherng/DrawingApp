#pragma once

#include "CDialogBoxGeneric.h"

#include <ProjectBase/CLine.h>

class CDialogBoxCreateLine final: public CDialogBoxGeneric
{
private:
	struct InputParameters
	{
		_Vector::double2 m_point_from = {-100., -100.};
		_Vector::double2 m_point_to = { 100., 100. };
	};

	struct OutputParameters
	{
		double m_length = 0;
	};

	InputParameters m_input_parameters;
	OutputParameters m_output_parameters;
	CMFCPropertyGridCtrl m_property_grid;
	// TODO: Use smart pointer
	CMFCPropertyGridProperty* mp_length;

	std::unique_ptr<Object::CLine> mp_temp_line = nullptr;

	void _CreateTempObject() override;
	void _SetWindowTitle() override;
	void _CreatePropertyGrid() override;

protected:
	void DoDataExchange(CDataExchange* pDX) override;
	void OnOK() override;
	void GeneratePreviewObject() override;

public:
	CDialogBoxCreateLine();
	~CDialogBoxCreateLine() = default;

protected:
	virtual afx_msg LRESULT OnGridItemChanged(WPARAM wParam, LPARAM lParam) override;
	DECLARE_MESSAGE_MAP()
};

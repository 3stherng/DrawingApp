#pragma once

class MFCUtilities
{
public:
  template <typename T = void> // force 'inline' via template
  static AFX_MODULE_STATE* GetModuleState()
  {
    const auto p_static_state = AfxGetStaticModuleState();
    if (p_static_state->m_hCurrentInstanceHandle == nullptr) // happens when called from main .exe module
      return AfxGetAppModuleState();
    else
      return p_static_state;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template <typename T = void> // force 'inline' via template
  static std::wstring LoadString(const UINT& i_id)
  {
    AFX_MANAGE_STATE(GetModuleState());

    CString str;
    str.LoadString(i_id);
    return str.GetString();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  static COLORREF ConvertVectorColorToRGB(const std::vector<size_t>& i_vector_color)
  {
    return RGB(i_vector_color[0], i_vector_color[1], i_vector_color[2]);
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  static std::vector<size_t> ConvertRGBToVectorColor(const COLORREF& i_rgb_color)
  {
    return { static_cast<size_t>(GetRValue(i_rgb_color)),
             static_cast<size_t>(GetGValue(i_rgb_color)),
             static_cast<size_t>(GetBValue(i_rgb_color)) };
  }
};

// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define WM_ADD_NEW_DRAWING WM_USER+0x100
#define WM_REDRAW_EVERYTHING WM_USER+0x102
#define WM_OPERATION_DIALOG_DESTROYED WM_USER+0x103
#define WM_PROPERTIES_DIALOG_DESTROYED WM_USER+0x104

// add headers that you want to pre-compile here
#include "afxdialogex.h"
#include "afxwinappex.h"
#include "framework.h"

#include <iostream>
#include <optional>
#include <string>

#include <MathHelpers/_Vector.h>

#endif //PCH_H

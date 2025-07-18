#pragma once

// .dll explicit garbage that pollutes this project because (C) Microsoft exists
#ifdef _WIN32

#ifdef GFX_EXPORTS
#define GFX_API __declspec(dllexport)
#else
#define GFX_API __declspec(dllimport)
#endif // ifdef GFX_EXPORTS

#else

// Use an empty macro since POSIX does not require any of this nonesense
#define GFX_API

#endif // ifdef _WIN32

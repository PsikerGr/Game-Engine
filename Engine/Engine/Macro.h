#pragma once

#ifndef __HE_MACRO_H_INCLUDED__
#define __HE_MACRO_H_INCLUDED__


#ifdef  ENGINE_DLL_EXPORTS
#define ENGINE_DLL __declspec(dllexport)
#else
#define ENGINE_DLL __declspec(dllimport)
#endif


#endif // __HE_MACROS_H_INCLUDED__
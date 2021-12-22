#pragma once

#ifdef DK_PLATFORM_WINDOWS
	#ifdef DK_BUILD_DLL
		#define DK_API __declspec(dllexport)

	#else
		#define DK_API __declspec(dllimport)
	#endif
#else
	#error Hazel only supports Windows!
#endif

#define BIT(x) (1 << x)
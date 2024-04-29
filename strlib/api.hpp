#pragma once

#if !defined(STRLIB_STATIC) && ! defined(STRLIB_HEADER_ONLY)
	#ifdef STRLIB_EXPORT
		#ifndef __GNUC__
			#define STRLIB_API __declspec(dllexport)
		#else
			#define STRLIB_API __attribute__((visibility("default")))
		#endif
	#else
		#ifndef __GNUC__
			#define STRLIB_API __declspec(dllimport)
		#else
			#define STRLIB_API
		#endif
	#endif
#else
	#define STRLIB_API
#endif
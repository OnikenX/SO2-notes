#pragma once

#include <windows.h>
#include <memory>
#include <tchar.h>
#include <sstream>
#include <iostream>

#ifdef UNICODE
#define tcout std::wcout
#define tcin std::wcin
#define tstring std::wstring
#define tstringstream std::wstringstream
#else
#define tcout std::cout
#define tcin std::cin
#define tstring std::string
#define tstringstream std::stringstream
#endif

namespace Win32Wrappers {
	//only usable with HKEY and HANDLE
	template <typename H>
	class handle;

	template <>
	class handle<HKEY> {
		HKEY h{};
	public:

		handle() {}

		~handle() {
			RegCloseKey(h);
			//_tprintf(TEXT("Closed Key"));
		}
		HKEY& operator()() {
			return h;
		}
		
		HKEY copy() {
			return h;
		}
	};

	template <>
	class handle<HANDLE> {
		HANDLE h{};
	public:
		handle() {}
		
		~handle() {
			CloseHandle(h);
			//_tprintf(TEXT("Closed handle"));
		}
		HANDLE copy() {
			return h;
		}
		HANDLE& operator()() {
			return h;
		}
	};
	template <>
	class handle<HMODULE> {
		HMODULE h{};
	public:
		handle() {}
		/*this overload = (HMODULE s){
			h = s;
		}*/
		~handle() {
			FreeLibrary(h);
			//_tprintf(TEXT("Closed handle"));
		}
		HMODULE copy() {
			return h;
		}
		HMODULE& operator()() {
			return h;
		}
	};
}


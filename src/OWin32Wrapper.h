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

// shortener for the TEXT macro
#define t(quote) TEXT(quote)

namespace Win32Wrappers
{
	//only usable with HKEY and HANDLE
	template <typename H>
	class Handle;

	template <>
	class Handle<HKEY>
	{
		HKEY h{};

	public:
		Handle() {}

		~Handle()
		{
			RegCloseKey(h);
			//_tprintf(TEXT("Closed Key"));
		}
		HKEY &operator()()
		{
			return h;
		}

		HKEY copy()
		{
			return h;
		}
	};

	template <>
	class Handle<HANDLE>
	{
		HANDLE h;

	public:
		Handle(HANDLE h) : h(h) {}
		Handle() {}

		~Handle()
		{
			CloseHandle(h);
			//_tprintf(TEXT("Closed handle"));
		}
		HANDLE copy()
		{
			return h;
		}
		HANDLE &operator()()
		{
			return h;
		}
	};
	template <>
	class Handle<HMODULE>
	{
		HMODULE h{};

	public:
		Handle() {}
		/*this overload = (HMODULE s){
			h = s;
		}*/
		~Handle()
		{
			FreeLibrary(h);
			//_tprintf(TEXT("Closed handle"));
		}
		HMODULE copy()
		{
			return h;
		}
		HMODULE &operator()()
		{
			return h;
		}
	};

	class test
	{
		int a;

	public:
		test() {}

		~test() {}

		int copy()
		{
			return a;
		}

		int &operator()()
		{
			return a;
		}
	};
};

// this is an helper class for printing utf-8 in the windows terminal
//
// put these lines in the main and there you go,
// ```cpp
//  #ifdef _WIN32
//      SetConsoleOutputCP(CP_UTF8);
//      setvbuf(stdout, nullptr, _IONBF, 0);
//      MBuf buf;
//      std::cout.rdbuf(&buf);
//  #endif
// ```
class MBuf : public std::stringbuf
{
public:
	int sync()
	{
		fputs(str().c_str(), stdout);
		str("");
		return 0;
	}
};

// corre isto no inicio do programa
void coisas_do_inicio()
{
//inputs e outputs em unicode se preciso
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
}
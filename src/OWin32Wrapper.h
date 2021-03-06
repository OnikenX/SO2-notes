#pragma once

#include <windows.h>
#include <memory>
#include <tchar.h>
#include <sstream>
#include <iostream>
#include <sstream>
using namespace std::literals;

#ifdef UNICODE
#define tcout std::wcout
#define tcerr std::wcerr
#define tcin std::wcin
#define tstring std::wstring
#define tstringstream std::wstringstream
#else
#define tcout std::cout
#define tcerr std::cerr
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

	template <typename T>
	class ValueGuard
	{
		T &value;
		HANDLE mutex;
		friend ValueGuard;

	public:
		ValueGuard(HANDLE mutex, T &value) : value(value), mutex(mutex)
		{
			tcout << t("geting lock\n");
			auto switcher = WaitForSingleObject(mutex, INFINITE);
			tcout << t("waited\n");
			switch (switcher)
			{
			case WAIT_ABANDONED:
				throw std::exception("Problem in creating guard: WAIT_ABANDONED!");
				break;
			case WAIT_OBJECT_0:
				// SUCCESS
				break;
			case WAIT_TIMEOUT:
				throw std::exception("Problem in creating guard: WAIT_TIMEOUT!");
				break;
			case WAIT_FAILED:
				throw std::exception("Problem in creating guard: WAIT_FAILED!");
				break;
			default:
				std::ostringstream stream;
				stream << "Problem in creating guard: UNSPECIFIED" << switcher;
				throw std::exception(stream.str().c_str());
				break;
			}
		}

		~ValueGuard()
		{
			ReleaseMutex(mutex);
		}

		T &get()
		{
			return value;
		}
	};

	template <typename T>
	class ValueLocked
	{
		T value{};
		Win32Wrappers::Handle<HANDLE> mutex;

	public:
		Win32Wrappers::Handle<HANDLE> create_internal_mutex()
		{
			static auto name = t("000000");

			auto tmp_mutex = CreateMutex(NULL, TRUE, NULL);

			if (tmp_mutex == NULL)
				throw std::exception("Error creating mutex.");
			return Win32Wrappers::Handle<HANDLE>{tmp_mutex};
		}
		ValueLocked(T value) : value(value)
		{
			mutex = create_internal_mutex();
		}

		//locks the mutex
		// template <typename X>
		ValueGuard<T> lock()
		{
			return ValueGuard<T>(mutex(), value);
		}
	};
};

class DifferentNameGenerator
{
	static DifferentNameGenerator *instance;
	Win32Wrappers::Handle<HANDLE> mutex;
	LPCTSTR nomebase;
	// Private constructor so that no objects can be created.
	DifferentNameGenerator()
	{
		mutex = CreateMutex(NULL, TRUE, t("___DifferentNameGenerator___"));
		if (mutex() == NULL)
		{
			auto errorcode = GetLastError();
			_tprintf(t("Mutex for DifferentNameGenerator died. ERROR:%d"), errorcode);
			ExitProcess(errorcode);
		}
		nomebase = t("aaaaaaaaaaaaaaaa");
		// nomebase[0] = nomebase[0] - 1;
		_tprintf(t("Created an DifferentNameGenerator with %d different possible names.\n"), _tcslen(nomebase) * (t("z") - t("a")));
	}

public:
	static DifferentNameGenerator &getInstance()
	{
		if (!instance)
			instance = new DifferentNameGenerator;
		return *instance;
	}

	// void getNewName(TCHAR[16] strtovalue)
	// {
	// 	for (int i = 0; i < _tcslen(nomebase); i++)
	// 	{
	// 		if (_tcscmp(nomebase[i], t("z"))){
	// 			++nomebase[i];
	// 			break;
	// 		}
	// 	}
	// 	_tcscpy(strtovalue, nomebase);
	// 	return strtovalue;
	// }
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
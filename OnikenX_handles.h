#pragma once

#include <Windows.h>
#include <memory>

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

}


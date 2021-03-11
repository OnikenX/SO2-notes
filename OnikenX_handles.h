#pragma once

#include <windows.h>

namespace OnikenX {
	namespace Win32Wrappers{
		template<typename H>
		class Handle {
		public:
			HANDLE h;
			Handle(HANDLE handle) : h(handle) {};
			
			~Handle() {
				CloseHandle(h);
			}
		};
	}
}


#pragma once

#include <windows.h>
#include <memory>

namespace OnikenX {
	namespace Win32Wrappers {
		//to automaticaly close handles and hkeys
		template <typename HKEY>
		class Handle {
			H h{};
		public:

			Handle() {}

			~Handle() {
				auto typeH = typeid(H).name;
				if (typeid(HKEY).name == typeH) {
					RegCloseKey(h);
					_tprintf(TEXT("Closed Key"));
				}
				else if (typeid(HANDLE).name == typeH) {
					CloseHandle(h);
					_tprintf(TEXT("Closed handle"));
				}
				else {
					_tprintf(TEXT("Don't know type."));
				}
			}
			H& operator()() {
				return H;
			}

		};
	}
}


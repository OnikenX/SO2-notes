#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <conio.h>


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


int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
	_tprintf(TEXT("boas!!\n"));
   return 0;

   CreateThread(
feck, pelo menos já melhorei o meu script de init para inciar com default do vsdev x64 em powershell)
}
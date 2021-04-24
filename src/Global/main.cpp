#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>

#include "OWin32Wrapper.h"

#include "ficha1.h"
#include "ficha2.h"
#include "ficha3.h"

//using namespace std;
//Permitir que o mesmo código possa funcionar para ASCII ou UNICODE


int _tmain(int argc, LPTSTR argv[]) {
	//UNICODE: Por defeito, a consola Windows não processe caracteres wide.
	//A maneira mais fácil para ter esta funcionalidade é chamar _setmode:


#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
	test_dll_explicit();

	return 0;
}
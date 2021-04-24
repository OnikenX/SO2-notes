#include "ficha3.h"
//#include <SO2_F3_DLL.h>
/*
Notas das aulas

Exerc�cio 1, 3 (seguindo as al�neas do 2), 2
Uso Impl�cito da DLL:

1�-> Ficheiros necess�rios: .h, .lib e .dll
(Cuidado com a arquitectura em que est�o a compilar o vosso projeto: x86 ou x64)

2� -> incluir .h e .lib no projeto (basta fazer adicionar item existente)
3� -> usar neste projeto, a vari�vel global factor e a fun��o
4� -> Build -> usaDLLImplicito.exe
5� -> No momento de executar o .exe, � que � necess�rio a .dll na mesma pasta


Uso expl�cito da DLL:

1�-> Ficheiros necess�rios: .dll

2� -> LoadLibraryEx : carregar dll

HMODULE dll = LoadLibraryEx(_T(�SO2_F3_DLL.dll�), NULL, 0);

GetProcAddress -> retorna o endere�o da fun��o/vari�vel
If (hDLL != NULL){
FARPROC ptrGenerico = GetProcAddress(hDLL, �factor�);
_tprintf(_T(�Valor da vari�vel %lf�), (double *) ptrGenerico);
double *varGlobal = (double *) ptrGenerico;
_tprintf(_T(�%lf�), *varGlobal);
//tipo_retorno (* nome_ptr) (tipo_par1, tipo_par2,�);

por exemplo para obter o ponteiro do applyFactor seria:
double(*doubleFactor)(double);

//para obter o ponteiro de uma fun��o:
ptrGenerico = GetProcAddress(hDLL, "applyFactor");
applyFactor = (double (*)(double))ptrGenerico;
applyFactor(4.3);
//para libertar
FreeLibrary(hDll);


3� -> Build: usoExplicito.dll
usoExplicito.exe
4� -> Quando for executar, garantir que a DLL � encontrada pelo execut�vel
Ou na mesma pasta, ou na PATH
*/


//� preciso adicionar no projecto a dll para ser de forma explicita
//void test_dll_implicit() {
//	double a = applyFactor(4.5);
//	std::wcout << a << std::endl;
//}

//aqui � preciso ter o dll na mesma pasta
void test_dll_explicit() {
	HMODULE hdll = LoadLibraryEx(TEXT("dll_test.dll"), NULL, 0);
	if (hdll != NULL) {
		FARPROC ptrGenerico = GetProcAddress(hdll, "foo");
		auto foo = (double (*)(double))ptrGenerico;
		_tprintf(TEXT("Valor da vari�vel %lf"), foo(2.0));
		FreeLibrary(hdll);
	}
}

//
/// Severity	Code	Description	Project	File	Line	Suppression State
//Error	LNK2019	unresolved external symbol __imp_applyFactor referenced in function "void __cdecl test_dll_implicit(void)" (? test_dll_implicit@@YAXXZ)	SO2 - notes	C : \Users\OnikenX\source\repos\SO2 - notes\ficha3.obj	1
//Error	LNK1120	1 unresolved externals	SO2 - notes	C : \Users\OnikenX\source\repos\SO2 - notes\x64\Debug\SO2 - notes.exe	1

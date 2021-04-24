#include "ficha3.h"
//#include <SO2_F3_DLL.h>
/*
Notas das aulas

Exercício 1, 3 (seguindo as alíneas do 2), 2
Uso Implícito da DLL:

1º-> Ficheiros necessários: .h, .lib e .dll
(Cuidado com a arquitectura em que estão a compilar o vosso projeto: x86 ou x64)

2º -> incluir .h e .lib no projeto (basta fazer adicionar item existente)
3º -> usar neste projeto, a variável global factor e a função
4º -> Build -> usaDLLImplicito.exe
5º -> No momento de executar o .exe, é que é necessário a .dll na mesma pasta


Uso explícito da DLL:

1º-> Ficheiros necessários: .dll

2º -> LoadLibraryEx : carregar dll

HMODULE dll = LoadLibraryEx(_T(“SO2_F3_DLL.dll”), NULL, 0);

GetProcAddress -> retorna o endereço da função/variável
If (hDLL != NULL){
FARPROC ptrGenerico = GetProcAddress(hDLL, “factor”);
_tprintf(_T(“Valor da variável %lf”), (double *) ptrGenerico);
double *varGlobal = (double *) ptrGenerico;
_tprintf(_T(“%lf”), *varGlobal);
//tipo_retorno (* nome_ptr) (tipo_par1, tipo_par2,…);

por exemplo para obter o ponteiro do applyFactor seria:
double(*doubleFactor)(double);

//para obter o ponteiro de uma função:
ptrGenerico = GetProcAddress(hDLL, "applyFactor");
applyFactor = (double (*)(double))ptrGenerico;
applyFactor(4.3);
//para libertar
FreeLibrary(hDll);


3º -> Build: usoExplicito.dll
usoExplicito.exe
4º -> Quando for executar, garantir que a DLL é encontrada pelo executável
Ou na mesma pasta, ou na PATH
*/


//é preciso adicionar no projecto a dll para ser de forma explicita
//void test_dll_implicit() {
//	double a = applyFactor(4.5);
//	std::wcout << a << std::endl;
//}

//aqui é preciso ter o dll na mesma pasta
void test_dll_explicit() {
	HMODULE hdll = LoadLibraryEx(TEXT("dll_test.dll"), NULL, 0);
	if (hdll != NULL) {
		FARPROC ptrGenerico = GetProcAddress(hdll, "foo");
		auto foo = (double (*)(double))ptrGenerico;
		_tprintf(TEXT("Valor da variável %lf"), foo(2.0));
		FreeLibrary(hdll);
	}
}

//
/// Severity	Code	Description	Project	File	Line	Suppression State
//Error	LNK2019	unresolved external symbol __imp_applyFactor referenced in function "void __cdecl test_dll_implicit(void)" (? test_dll_implicit@@YAXXZ)	SO2 - notes	C : \Users\OnikenX\source\repos\SO2 - notes\ficha3.obj	1
//Error	LNK1120	1 unresolved externals	SO2 - notes	C : \Users\OnikenX\source\repos\SO2 - notes\x64\Debug\SO2 - notes.exe	1

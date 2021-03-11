#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>
#include "OnikenX_handles.h"
//using namespace std;
//Permitir que o mesmo código possa funcionar para ASCII ou UNICODE

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



using std::endl;



void ex1() {
	std::cout << "Olá cães." << std::endl;
	//ele printa no ecrã: 
	//Olß cÒes.

	//isso porque windows não supporta nativamente os characters Unicode como outros sistemas operativos.
	//char -> 1 bytes (caracteres que estão na tabela ASCII (8BIT))
	//wchar -> 2 bytes (caracteres que estão na tabela UNICODE-16BIT)
	//solução -> TCHAR ou para char ou wchar depende da propriedade do projeto Character Set
}

void ex2copypaste() {
	const int MAX = 256;
	TCHAR str[MAX], result[MAX] = TEXT("Olá! Este programa é para aceitar UNICODE. Insira \'fim\' para sair\n");
	unsigned int i;
	do {
		_tprintf(result);
		fflush(stdin);
		_fgetts(str, MAX, stdin);
		//Retirar \n
		str[_tcslen(str) - 1] = '\0';
		//Maiúsculas
		for (i = 0; i < _tcslen(str); i++)
			str[i] = _totupper(str[i]);
		_stprintf_s(result, MAX, TEXT("Frase:%s, Tamanho:%d\n"), str, _tcslen(str));
	} while (_tcsicmp(TEXT("FIM"), str));
}

void ex3a() {
	const int MAX = 256;
	TCHAR result[MAX] = TEXT("Olá! não às dorgas.");
	_tprintf(TEXT("Frase: %s Tamanho:%d (character) %d (bytes)\n"), result, _tcslen(result), _tcslen(result) * sizeof(TCHAR));
	srand(time(NULL));
	int aleatorio = rand();
	_gettchar();

}


void ex4loopFIM() {
	tstring str = TEXT("Olá! Este programa é para aceitar UNICODE. Insira \'fim\' para sair\n");

	tcout << str;
	do {
		std::getline(tcin, str);
		//Maiúsculas
		for (unsigned int i = 0; i < str.length(); ++i)
			str[i] = _totupper(str[i]);
		/*str = TEXT("NOVO");*/
		tcout << TEXT("Frase: ") << str << TEXT("Tamanho:") << str.length() << std::endl;
	} while (str != TEXT("FIM"));

}


void ex4createProcess(LPTSTR argv[]) {
	const int MAX = 256;
	TCHAR text[MAX] = TEXT("echo hello");

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	//limpar a memoria para nao ser mal interpretado
	ZeroMemory(&si, sizeof(si)); //zeromemory é o mesmo que o memset com tudo a 0
	ZeroMemory(&pi, sizeof(pi)); //resultado da função: pid do processo, tid da thread principal, handle
	
	si.cb = sizeof(STARTUPINFO);



	// Start the child process. 
	if (!CreateProcess(NULL,   // No module name (use command line)
		text,        // Command line
		nullptr,           // Process handle not inheritable
		nullptr,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		nullptr,           // Use parent's environment block
		nullptr,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}
	else {
		tcout << TEXT("processo foi lançado , PID:") << pi.dwProcessId << ' ' << pi.dwProcessId << endl; //ver o gestor de tarefas

		//Esperar pelo processo terminar
		WaitForSingleObject(&pi.hProcess, INFINITE); // > positivo tempo de espera, 0 só para consulta, INFITE até acontecer
	}

	

	
}
void test_std() {
	using namespace std::string_literals;
	tcout << _T("helléÅÈÑÉËÅÅËÈφe") << std::endl;
}


//ex2
void registryPlayground() {
	const int TAM = 100;
	HKEY chave; // handle para a chave depois aberta/criada
	TCHAR chave_nome[TAM] = TEXT("SOFTWARE\\SO2\\registryPlayground"), 
		par_nome[TAM]=TEXT("primeira aula"),
		par_valor[TAM]=TEXT("true");
	DWORD resultado;
	
	if (RegCreateKeyEx(
		HKEY_CURRENT_USER,
		chave_nome,
		0,
		NULL,								//LPSTR                       lpClass,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,								//REGSAM                      samDesired,
		NULL,								//const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		&chave,								//PHKEY                       phkResult,
		&resultado							//LPDWORD                     lpdwDisposition
	) != ERROR_SUCCESS) {
		_tprintf(TEXT("Chave não foi criada nem aberta! ERRO=%l", f));
		return;
	}
	if (resultado = REG_CREATED_NEW_KEY) 
		_tprintf(TEXT("chave criada"));
	else
		_tprintf(TEXT("chave não criada."));
	//par_valor[0] = '\0';
	DWORD tamanho = sizeof(par_valor);
	if (RegSetKeyValue(
		chave,//HKEY_CURRENT_USER
		par_nome,
		0,
		NULL,
		par_valor,//LPCVOID lpData,
		sizeof(TCHAR) * (_tcslen(par_valor) + 1)
	) != ERROR_SUCCESS)
	{
		_tprintf(TEXT("Atributo não foi encontrado. ERRO"));
		return;
	}
	CloseHandle(chave);
}

int _tmain(int argc, LPTSTR argv[]) {
	//UNICODE: Por defeito, a consola Windows não processe caracteres wide.
	//A maneira mais fácil para ter esta funcionalidade é chamar _setmode:
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
	registryPlayground();
	return 0;
}

#include "OWin32Wrapper.h"
#include "ficha1.h"

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
		_tprintf(TEXT("CreateProcess failed (%d).\n"), GetLastError());
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
	tcout << _T("hello") << std::endl;
}



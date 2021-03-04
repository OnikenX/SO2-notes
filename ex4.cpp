#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>
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


void loopFIM() {
	tstring str = TEXT("Olá! Este programa é para aceitar UNICODE. Insira \'fim\' para sair\n");

	tcout << str;
	do {
		std::getline(tcin, str);
		//Maiúsculas
		for (unsigned int i = 0; i < str.length(); i++)
			str[i] = _totupper(str[i]);
		/*str = TEXT("NOVO");*/
		tcout << TEXT("Frase: ") << str << TEXT("Tamanho:") << str.length() << std::endl;
	} while (str != TEXT("FIM"));

}


void createProcess(LPTSTR argv[]) {
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

int _tmain(int argc, LPTSTR argv[]) {
	//UNICODE: Por defeito, a consola Windows não processe caracteres wide.
	//A maneira mais fácil para ter esta funcionalidade é chamar _setmode:
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
	createProcess(argv);
	return 0;
}
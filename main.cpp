#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>
//using namespace std;
//Permitir que o mesmo c�digo possa funcionar para ASCII ou UNICODE
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
	std::cout << "Ol� c�es." << std::endl;
	//ele printa no ecr�: 
	//Ol� c�es.

	//isso porque windows n�o supporta nativamente os characters Unicode como outros sistemas operativos.
	//char -> 1 bytes (caracteres que est�o na tabela ASCII (8BIT))
	//wchar -> 2 bytes (caracteres que est�o na tabela UNICODE-16BIT)
	//solu��o -> TCHAR ou para char ou wchar depende da propriedade do projeto Character Set
}

void ex2copypaste() {
	const int MAX = 256;
	TCHAR str[MAX], result[MAX] = TEXT("Ol�! Este programa � para aceitar UNICODE. Insira \'fim\' para sair\n");
	unsigned int i;
	do {
		_tprintf(result);
		fflush(stdin);
		_fgetts(str, MAX, stdin);
		//Retirar \n
		str[_tcslen(str) - 1] = '\0';
		//Mai�sculas
		for (i = 0; i < _tcslen(str); i++)
			str[i] = _totupper(str[i]);
		_stprintf_s(result, MAX, TEXT("Frase:%s, Tamanho:%d\n"), str, _tcslen(str));
	} while (_tcsicmp(TEXT("FIM"), str));
}

void ex3a() {
	const int MAX = 256;
	TCHAR result[MAX] = TEXT("Ol�! n�o �s dorgas.");
	_tprintf(TEXT("Frase: %s Tamanho:%d (character) %d (bytes)\n"), result, _tcslen(result), _tcslen(result) * sizeof(TCHAR));
	srand(time(NULL));
	int aleatorio = rand();
	_gettchar();

}


void ex4loopFIM() {
	tstring str = TEXT("Ol�! Este programa � para aceitar UNICODE. Insira \'fim\' para sair\n");

	tcout << str;
	do {
		std::getline(tcin, str);
		//Mai�sculas
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
	ZeroMemory(&si, sizeof(si)); //zeromemory � o mesmo que o memset com tudo a 0
	ZeroMemory(&pi, sizeof(pi)); //resultado da fun��o: pid do processo, tid da thread principal, handle
	
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
		tcout << TEXT("processo foi lan�ado , PID:") << pi.dwProcessId << ' ' << pi.dwProcessId << endl; //ver o gestor de tarefas

		//Esperar pelo processo terminar
		WaitForSingleObject(&pi.hProcess, INFINITE); // > positivo tempo de espera, 0 s� para consulta, INFITE at� acontecer
	}

	

	
}

int _tmain(int argc, LPTSTR argv[]) {
	//UNICODE: Por defeito, a consola Windows n�o processe caracteres wide.
	//A maneira mais f�cil para ter esta funcionalidade � chamar _setmode:
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	ex4createProcess(argv);
	return 0;
}
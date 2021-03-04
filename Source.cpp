#include <string>
#include <iostream>

#include <windows.h>
#include <tchar.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#define MAX 256


void ex1() {
	std::cout << "Olá cães." << std::endl;
	//ele printa no ecrã: 
	//Olß cÒes.

	//isso porque windows não supporta nativamente os characters Unicode.
	//char -> 1 bytes (caracteres que estão na tabela ASCII (8BIT))
	//wchar -> 2 bytes (caracteres que estão na tabela UNICODE-16BIT)
	//solução -> TCHAR ou para char ou wchar depende da propriedade do projeto Character Set
}

void ex2copypaste() {
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
	TCHAR result[MAX] = TEXT("Olá! não às dorgas.");
	_tprintf(TEXT("Frase: %s Tamanho:%d (character) %d (bytes)\n"), result, _tcslen(result), _tcslen(result) * sizeof(TCHAR));
	srand(time(NULL));
	int aleatorio = rand();
	_gettchar();
	
}

void ex4() {


}


//
//int _tmain(int argc, LPTSTR argv[]) {
//	//UNICODE: Por defeito, a consola Windows não processacaracteres wide. 
//	//A maneira mais fácil para ter esta funcionalidade é chamar _setmode:
//#ifdef UNICODE 
//	_setmode(_fileno(stdin), _O_WTEXT);
//	_setmode(_fileno(stdout), _O_WTEXT);
//#endif	
//
//	ex3a();
//}
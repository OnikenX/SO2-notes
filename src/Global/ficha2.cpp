#include "ficha2.h"
#include "OWin32Wrapper.h""

//ex2
void registryPlayground() {
	const int TAM = 100;
	//HKEY chave; // handle para a chave depois aberta/criada
	Win32Wrappers::handle<HKEY> chave;
	TCHAR chave_nome[TAM] = TEXT("SOFTWARE\\SO2\\registryPlayground"),
		par_nome[TAM] = TEXT("primeira aula"),
		par_valor[TAM] = TEXT("true");
	DWORD resultado;

	if (RegCreateKeyEx(
		HKEY_CURRENT_USER,
		chave_nome,
		0,
		NULL,								//LPSTR                       lpClass,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,								//REGSAM                      samDesired,
		NULL,								//const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		&chave(),								//PHKEY                       phkResult,
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
		chave(),
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
}

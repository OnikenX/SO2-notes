#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

#include "../OWin32Wrapper.h"

DWORD WINAPI thread_exec(LPVOID unused)
{

    for (int i = 0; i < 10; i++)
    {
        tcout << t("this is a text") << i << std::endl;
    }

    return 0;
}

bool is_prime(int possible_prime)
{
    for (int i = 2; i < possible_prime; ++i)
        if (possible_prime % i == 0)
            return false;
    // tcout << possible_prime << t(" is prime!!!") << std::endl;
    return true;
}

DWORD WINAPI soma_primos(LPVOID __void__)
{
    int possible_prime = 0;
    //known prime numbers
    int sum = 0;
    int sums_count = 0;
    while (true)
    {
        possible_prime++;
        if (is_prime(possible_prime))
        {
            sum += possible_prime;
        }

        if (++sums_count == 15)
        {
            tcout << t("Somatorio até ") << sum << t("(soma_primos)") << std::endl;
            Sleep(1000);
        }
    }
}

DWORD WINAPI soma_pares(LPVOID __void__)
{
    int pares = 0;
    int sum = 0;
    int sum_count = 0;
    while (true)
    {
        pares += 2;
        sum += pares;
        if (++sum_count == 200)
        {
            tcout << t("Fiz somatorio até ") << sum << t("(soma_pares)")<< std::endl;
            Sleep(1000);
            sum_count = 0;
        }
    }
    return 0;
}

int _tmain()
{
    coisas_do_inicio();

    //inicializes thread dos pares
    auto pairsHandle = Win32Wrappers::Handle<HANDLE>{
        CreateThread(
            NULL,
            0,
            soma_pares,
            NULL,
            0,
            NULL)};
    //inicializes thread dos primos
    auto primesHandle = Win32Wrappers::Handle<HANDLE>{
        CreateThread(
            NULL,
            0,
            soma_primos,
            NULL,
            0,
            NULL)};

    { //WAITER
        const int handle_array_size = 2;
        HANDLE handle_array[handle_array_size];
        handle_array[0] = pairsHandle();
        handle_array[1] = primesHandle();

        WaitForMultipleObjects(handle_array_size, handle_array, true, INFINITE);
    }
    return 0;
}

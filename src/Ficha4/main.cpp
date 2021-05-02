#include <iostream>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <memory>

#include "../OWin32Wrapper.h"

#define MUTEX_MAIN t("mutex_main")

using namespace Win32Wrappers;

struct Numbers
{
    Win32Wrappers::ValueLocked<long long int> soma_dos_dois{0};
    Win32Wrappers::ValueLocked<long long int> soma_dos_primos{0};
    Win32Wrappers::ValueLocked<long long int> soma_dos_pares{0};
};

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
    return true;
}

DWORD WINAPI soma_primos(LPVOID _values)
{
    auto values = (Numbers *)_values;
    long long int possible_prime = 0;
    //known prime numbers
    // long long int sum = 0;
    int sums_count = 0;
    while (true)
    {
        possible_prime++;
        if (is_prime(possible_prime))
        {
            tcout << t("lock\n");
            {
                auto guard = values->soma_dos_primos.lock();
                tcout << t("locked\n");
                guard.get() += possible_prime;
            }
            tcout << t("unlock\n");
            if (++sums_count == 15)
            {
                long long int sum{0};
                tcout << t("lock\n");
                {
                    auto guard = values->soma_dos_primos.lock();
                    sum = guard.get();
                }
                tcout << t("unlock\n");

                tcout << t("Somatorio até ") << sum << t("(soma_primos)") << std::endl;
                Sleep(1000);
                sums_count = 0;
            }
        }
    }
}

DWORD WINAPI soma_pares(LPVOID _values)
{
    auto values = (Numbers *)_values;

    long long int pares = 0;
    long long int sum = 0;
    int sum_count = 0;
    while (true)
    {
        pares += 2;
        sum += pares;
        if (++sum_count == 200)
        {
            tcout << t("Fiz somatorio até ") << sum << t("(soma_pares)") << std::endl;
            Sleep(1000);
            sum_count = 0;
        }
    }
    return 0;
}

int _tmain()
{
    auto numbers = std::make_unique<Numbers>();
    coisas_do_inicio();
    //inicializes thread dos pares
    auto pairsHandle = Win32Wrappers::Handle<HANDLE>{CreateThread(NULL, 0, soma_pares, numbers.get(), 0, NULL)};
    //inicializes thread dos primos
    auto primesHandle = Win32Wrappers::Handle<HANDLE>{CreateThread(NULL, 0, soma_primos, numbers.get(), 0, NULL)};
    { //WAITER
        const int handle_array_size = 2;
        HANDLE handle_array[handle_array_size];
        handle_array[0] = pairsHandle();
        handle_array[1] = primesHandle();
        {
        }
        WaitForMultipleObjects(handle_array_size, handle_array, true, INFINITE);
    }
    return 0;
}

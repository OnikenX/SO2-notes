#include "shared.h"

HANDLE cant_read_try_to_create_file_mapping()
{
    HANDLE hMapFile = NULL;
    LPCTSTR pBuf;
    _tprintf(TEXT("Could not open file mapping object (%d), trying to create it.\n"),
             GetLastError());

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE, // suse paging file
        NULL,                 // default security
        PAGE_READWRITE,       // read/write access
        0,                    // maximum object size (high-order DWORD)
        BUF_SIZE,             // maximum object size (low-order DWORD)
        szName);              // name of mapping object
    if (hMapFile == NULL)
    {
        _tprintf(TEXT("Could not create file mapping object neither open (%d).\n"),
                 GetLastError());

        pBuf = (LPTSTR)MapViewOfFile(hMapFile,            // handle to map object
                                     FILE_MAP_ALL_ACCESS, // read/write permission
                                     0,
                                     0,
                                     BUF_SIZE);
    }
}

HANDLE try_open_file_mapping()
{
    HANDLE hMapFile = NULL;
    LPCTSTR pBuf;

    hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS, // read/write access
        FALSE,               // do not inherit the name
        szName);             // name of mapping object

    //cant open
    if (hMapFile == NULL)
    {
        hMapFile = cant_read_try_to_create_file_mapping();
        //did oepn
    }
    else
    {

        pBuf = (LPTSTR)MapViewOfFile(hMapFile,            // handle to map object
                                     FILE_MAP_ALL_ACCESS, // read/write permission
                                     0,
                                     0,
                                     BUF_SIZE);

        if (pBuf == NULL)
        {
            _tprintf(TEXT("Could not map view of file (%d).\n"),
                     GetLastError());
            CloseHandle(hMapFile);
            return NULL;
        }
        MessageBox(NULL, pBuf, TEXT("Process2"), MB_OK);
        UnmapViewOfFile(pBuf);
        CloseHandle(hMapFile);
    }
}

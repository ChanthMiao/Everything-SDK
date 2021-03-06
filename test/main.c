
// Everything IPC test
// this tests the lib and the dll.

#include <locale.h>
#include <stdio.h>

#include "Everything.h"
#pragma warning(disable : 4710)

int main(void)
{
    printf("SDK test\n");

    Everything_SetSearchW(L"hello");

    Everything_SetRequestFlags(EVERYTHING_REQUEST_FILE_NAME | EVERYTHING_REQUEST_PATH | EVERYTHING_REQUEST_SIZE);
    Everything_SetSort(EVERYTHING_SORT_SIZE_DESCENDING);

    printf("Execute Query\n");

    Everything_QueryW(TRUE);

    printf("Result List Request Flags %08x\n", (UINT)Everything_GetResultListRequestFlags());

    {
        DWORD i;

        for (i = 0; i < Everything_GetNumResults(); i++)
        {
            LARGE_INTEGER size;
            const wchar_t *filename;
            const wchar_t *path;

            Everything_GetResultSize(i, &size);

            filename = Everything_GetResultFileNameW(i);
            path = Everything_GetResultPathW(i);

            printf("Name: %S\n", filename);
            printf("Path: %S\n", path);
            printf("Size: %I64u\n", size.QuadPart);
        }
    }
    /*
        // ANSI test
        Everything_SetSearchA("hello");
        Everything_QueryA(TRUE);

        {
            DWORD i;

            for(i=0;i<Everything_GetNumResults();i++)
            {
                printf("%s\n",Everything_GetResultFileNameA(i));
            }
        }
    */
    return 0;
}

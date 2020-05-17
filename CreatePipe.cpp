#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    BOOL bPipe;
    HANDLE hRead;
    HANDLE hWrite;

    char szBuffer[512] = "Hello Pipe";
    DWORD dwBufferSize = sizeof(szBuffer);
    BOOL bReadFile;
    BOOL bWriteFile;
    DWORD dwNoBytesRead;
    DWORD dwNoBytesWrite;

    bPipe = CreatePipe(&hRead,
                       &hWrite,
                       NULL,
                       dwBufferSize);

    if(bPipe == FALSE)
    {
        cout << "CreatePipe - failed: " << GetLastError() << endl;
    }else
    {
        cout << "CreatePipe - sucess..." << endl;

        bWriteFile = WriteFile(hWrite,
                               szBuffer,
                               dwBufferSize,
                               &dwNoBytesWrite,
                               NULL);
        CloseHandle(hWrite);

        bReadFile = ReadFile(hRead,
                             szBuffer,
                             dwBufferSize,
                             &dwNoBytesRead,
                             NULL);
        cout << "ReadPipe: " << szBuffer << endl;
        CloseHandle(hRead);
    }



    system("pause");
    return 0;
}

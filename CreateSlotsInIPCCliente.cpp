//CLIENT
#include <windows.h>
#include <iostream>
#include <string.h>

using namespace std;

int main()
{
    cout << "...MAILSLOTS CLIENT..." << endl;
    //create local variable
    HANDLE hCreateFile;

    //Write Local variable
    BOOL bWriteFile;
    DWORD dwNoBytesWrite;
    char szWriteFileBuffer[1023] = "hello world!";
    DWORD dwWriteFileBufferSize = sizeof(szWriteFileBuffer);

    //ReadFile Local variable
//    BOOL bReadFile;
//    DWORD dwNoBytesRead;
//    char szReadFileBuffer[1023];
//    DWORD dwReadFileBufferSize = sizeof(szReadFileBuffer);

    //CreateFile for pipe
    hCreateFile = CreateFile(TEXT("\\\\.\\mailslot\\MYMAILSLOTS"),
                             GENERIC_READ | GENERIC_WRITE,
                             0,
                             NULL,
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL,
                             NULL);
    if(hCreateFile == INVALID_HANDLE_VALUE)
    {
        cout << "CreateFile - failed" << GetLastError() << endl;
    }
    cout << "CreateFile - sucess..." << endl;

    cout << "write your message: " << endl;

    cin >> szWriteFileBuffer;

    bWriteFile = WriteFile(hCreateFile,
                           szWriteFileBuffer,
                           dwWriteFileBufferSize,
                           &dwNoBytesWrite,
                           NULL);
    if(bWriteFile == FALSE)
    {
        cout << "WriteFile - failed: " << GetLastError() << endl;
    }
    cout << "WriteFile - sucess..." << endl;

    cout << "message: " << szWriteFileBuffer << endl;

    system("pause");
    return 0;
}

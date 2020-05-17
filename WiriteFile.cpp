#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    HANDLE hFile;
    BOOL bFile;
    char chBuffer[1024] = "testando escrita...";
    DWORD dwNoByteToWrite = strlen(chBuffer);
    DWORD dwNoByteWiritten = 0;

    hFile = CreateFile(TEXT("C:\\newdirector\\KAYQUEOBOLAADAUMDO.txt"),
                       GENERIC_READ | GENERIC_WRITE,
                       FILE_SHARE_READ,
                       NULL,
                       CREATE_NEW,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL);
     if(hFile == INVALID_HANDLE_VALUE)
    {
        cout << "CreateFile - error: " << GetLastError() << endl;
    }else
    {
        cout << "CreatFile - sucess..." << endl;
    }


    bFile = WriteFile(hFile,
                      chBuffer,
                      dwNoByteToWrite,
                      &dwNoByteWiritten,
                      NULL);
    if(bFile == FALSE)
    {
        cout << "WriteFile - error: " << GetLastError() << endl;
    }else
    {
        cout << "WriteFile - sucess..." << endl;
    }

    CloseHandle(hFile);


    system("pause");
    return 0;
}

//SERVER
#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "...MAILSLOTS..SERVER..." << endl;

    //CreateMailSlots local variable
    HANDLE hSlots;

    //ReadFile local variable
    BOOL bReadFile;
    DWORD dwNoBytesRead;
    char szReadFileBuffer[1023];
    DWORD dwReadFileBufferSize = sizeof(szReadFileBuffer);

    //step 1 - CreateMailSlots def.
    hSlots = CreateMailslot(TEXT("\\\\.\\mailslot\\MYMAILSLOTS"),
                            0,
                            MAILSLOT_WAIT_FOREVER,
                            NULL);
    if(hSlots == INVALID_HANDLE_VALUE)
    {
        cout << "CreateMailslot - failed: " << GetLastError() << endl;
    }
    cout << "CreateMailslot - sucess..." << endl;

    //step 2 - ReadFile def.
    bReadFile = ReadFile(hSlots,
                         szReadFileBuffer,
                         &dwReadFileBufferSize,
                         &dwNoBytesRead,
                         NULL);
    if(bReadFile)
    {
        cout << "ReadFile - failed: " << GetLastError() << endl;
    }
    cout << "ReadFile - sucess..." << endl;
    cout << "DATA READING FROM MAILSLOTS CLIENT..." << szReadFileBuffer << endl;

    //step 3 - CloseHandle
    CloseHandle(hSlots);

    system("pause");
    return 0;
}

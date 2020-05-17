#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "FILE MAPPING - SERVER OR PARENT" << endl;
    cout << endl;

    HANDLE hFileMap;
    BOOL bResult;
    PCHAR lpBuffer = NULL;
    char buffer[1024] = "hello from file map server";
    size_t szBuffer = sizeof(Buffer);

    hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,
                                 NULL,
                                 PAGE_READWRITE,
                                 0,
                                 256,
                                 TEXT("local\\mapping"));
    if(hFileMap == FALSE)
    {
        cout << "FileMap - failed: " << GetLastError() << endl;
    }
    cout << "FileMap - sucess..." << endl;

    lpBuffer = (TCHAR)MapViewOfFile(hFileMap,
                                    FILE_MAP_ALL_ACCESS,
                                    0,
                                    0,
                                    256);
    if(lpBuffer == NULL)
    {
        cout << "MapViewOfFile - failed: " << GetLastError() << endl;
    }
    cout << "MapViewOfFile - sucess..." << endl;

    CopyMemory(lpBuffer, Buffer, szBuffer);

    bResult = UnmapViewOfFile(lpBuffer);
    if(bResult == FALSE)
    {
        cout << "UnmapViewOfFile - failed:" << GetLastError() << endl;
    }
    cout << "UnmapViewOfFile - sucess..." << endl;

    system("pause");
    return 0;
}

#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    HANDLE hFile;

    hFile = CreateFile(
                TEXT("C:\\newdirector\\KAYQUEBOLAADAUMDO.txt"),
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

    CloseHandle(hFile);

    system("pause");
    return 0;
}

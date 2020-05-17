#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    BOOL bFile;
    bFile = CopyFile(
            L"C:\\newdirector\\hello.txt",
            L"C:\\newdirector\\mello.txt",
            FALSE);

    if(bFile == FALSE)
    {
        cout << "CopyFile - error: " << GetLastError() << endl;
    }else
    {
        cout << "CopyFile - sucess: " << endl;
    }
    system("pause");
    return 0;
}

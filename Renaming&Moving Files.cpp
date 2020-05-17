#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    BOOL bFile;

    bFile = MoveFile(
            L"C:\\newdirector\\hello.txt",
            L"C:\\newdirector\\mello.txt");

    if(bFile == FALSE)
    {
        cout << "MoveFile - error: " << GetLastError() << endl;
    }else
    {
        cout << "MoveFile - sucess: " << endl;
    }

    system("pause");
    return 0;
}

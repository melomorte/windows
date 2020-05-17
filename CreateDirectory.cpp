#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    BOOL bDir;
    bDir = CreateDirectory(TEXT("c:\\filemanipulation"), NULL);

    if(bDir == FALSE)
    {
        cout << "CreateDirectory - failed & error:  " << GetLastError() <<  endl;
    }else
    {
        cout << "CreateDirectory - sucess..." << endl;
    }

    system("pause");
    return 0;
}

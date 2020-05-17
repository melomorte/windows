#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    BOOL bDir;
    bDir = RemoveDirectory("C:\\newdirector");

    if(bDir == FALSE)
    {
        cout << "RemoveDirectory - failed: " << GetLastError() << endl;
    }else
    {
        cout << "RemoveDirectory - sucess..." << endl;
    }


    system("pause");
    return 0;
}

#include <windows.h>
#include <iostream>

using namespace std;

int main()
{

    HANDLE hMutex;

    cout << "OPEN MUTEX FUNCTION" << endl;

    hMutex = OpenMutex(MUTEX_ALL_ACCESS,
                                  FALSE,
                       TEXT("myMutex")); //unamed

    if(hMutex == NULL)
    {
        cout << "CreateMutex - failed: " << GetLastError() << endl;
    }else
    {
        cout << "CreateMutex - sucess..." << endl;

        CloseHandle(hMutex);
    }

    system("pause");
    return 0;
}

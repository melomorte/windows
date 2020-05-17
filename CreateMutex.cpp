#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    HANDLE hMutex;

    cout << "MUTEX 1" << endl;

    hMutex = CreateMutex(NULL,
                        FALSE,
             TEXT("myMutex"));

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

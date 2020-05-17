#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    HANDLE hSem;

    hSem = CreateSemaphore(NULL,
                           1,
                           1,
                           NULL);

    if(hSem == NULL)
    {
        cout << "CreateSemaphore - failed: " << GetLastError() << endl;
    }else
    {
        cout << "CreateSemaphore - sucess..." << endl;
        CloseHandle(hSem);
    }


    system("pause");
    return 0;
}

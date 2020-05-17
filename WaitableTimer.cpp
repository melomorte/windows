#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    //local variable
    HANDLE hTimer = NULL;
    BOOL bSetWaitableTimer = FALSE;
    DWORD dWaitWorSingleObject;

    LARGE_INTEGER lIdueTime;
    lIdueTime.QuadPart = -5000000LL;

    //step - 1: Create Waitable Timer
    hTimer = CreateWaitableTimer(NULL,
                                 TRUE,
                                 NULL);

    if(NULL == hTimer)
    {
        cout << "Create waitable - failed: " << endl;
    }
    cout << "Create waitable - sucess" << endl;

    //step - 2: Set Waitable Timer
    bSetWaitableTimer = SetWaitableTimer(hTimer,
                                         &lIdueTime,
                                         0,
                                         NULL,
                                         NULL,
                                         0);

    if(FALSE == bSetWaitableTimer)
    {
        cout << "SetWaitableTimer - failed: " << endl;
    }
    cout << "SetWaitableTimer - sucess..." << endl;

    //step - 3: printing output
    cout << "waiting for 5 sec....." << endl;

    //wait for single object
    dWaitWorSingleObject = WaitForSingleObject(hTimer, INFINITE);

    //close handle
    CloseHandle(hTimer);


    system("pause");
    return 0;
}

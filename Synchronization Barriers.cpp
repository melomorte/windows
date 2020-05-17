#include <windows.h>
#include <iostream>

using namespace std;

//global variable
SYNCHRONIZATION_BARRIER sb;
int x = 5;

//thread fun - 1
DWORD WINAPI ThreadFun1(LPVOID lpvoid)
{
    EnterSynchronizationBarrier(&sb, SYNCHRONIZATON_BARRIERR_FLAGS_SPIN_ONLY);
    cout << "in thread fun - 1: " << endl;
    cout << ++x << endl;
    DeleteSynchrnizationBarrier(&sb);

    return 0;
}

//thread fun - 2
DWORD WINAPI ThreadFun2(LPVOID lpvoid)
{
    EnterSynchronizationBarrier(&sb, SYNCHRONIZATON_BARRIERR_FLAGS_SPIN_ONLY);
    cout << "in thread fun - 2: " << endl;
    cout << ++x << endl;
    DeleteSynchrnizationBarrier(&sb);

    return 0;
}

int main()
{
    //local variable
    HANDLE hThread1, hThread2;

    //step - 1: initialize the synchronization barrier
    InitializeSynchronizationBarrier(&sb, 2, SYNCHRONIZATON_BARRIERR_FLAGS_SPIN_ONLY);

    //step - 2: Create thread's
    hThread1 = CreateThread(NULL,
                            0,
                            &ThreadFun1,
                            NULL,
                            0,
                            0);

    hThread2 = CreateThread(NULL,
                            0,
                            &ThreadFun2,
                            NULL,
                            0,
                            0);

    //step - 3: wait for single object
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    //step - 4: Close Handle
    CloseHandle(hThread1);
    CloseHandle(hThread2);


    system("pause");
    return 0;
}

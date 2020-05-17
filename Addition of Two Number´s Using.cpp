#include <windows.h>
#include <iostream>

using namespace std;

int a[2];

DWORD WINAPI ThreadFun(LPVOID lpParam)
{
    int x, y, result;

    x = a[2];
    y = a[3];

    result = x + y;
    cout << "addition = " << result << endl;
}

int main()
{
    HANDLE hThread;
    DWORD ThreadID;

    cout << "Enter your first No: " << endl;
    cin >> a[0];
    cout << "Enter your second No: " << endl;
    cin >> a[1];

    hThread = CreateThread(NULL,
                           0,
                           &ThreadFun,
                           (void*)&a,
                           0,
                           &ThreadID);

    if(hThread == NULL)
    {
        cout << "ThreadCreate - error: " << GetLastError() << endl;
    }else
    {
        cout << "ThreadCreate - sucess..." << endl;
        CloseHandle(hThread);
    }


    system("pause");
    return 0;
}

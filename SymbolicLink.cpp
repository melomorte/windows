#include <windows.h>
#include <iostream>

int main()
{
    BOOL bSynlink;

    bSynlink = CreateSymbolicLink(L"C:\\newdirector\\HARDFile.txt",
                                  L"C:\\newdirector\\sampleHARDFile.txt",
                                  0);
    if(bSynlink == FALSE)
    {
        cout << "CreateSymbolicLink - error: " << GetLastError() << endl;
    }else
    {
        cout << "CreateSymbolicLink - error: " << endl;
    }

    system("PAUSE");
    return 0;
}

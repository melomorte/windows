#include <windows.h>
#include <winbase.h>
#include <iostream>

using namespace std;

int main()
{
    BOOL bhFile;

	bhFile = CreateHardLink(TEXT("C:\\newdirector\\textFile.txt"),
							TEXT("C:\\newdirector\\HARDFile.txt"),
                            NULL);
    if(bhFile == FALSE)
    {
        cout << "CreateHardLink - error: " << GetLastError() << endl;
    }else
    {
        cout << "CreateHardLink - sucess... " << endl;
    }


    system("pause");
    return 0;
}

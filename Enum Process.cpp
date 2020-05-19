#include <windows.h>
#include <psapi.h>      //process enumeration.
#include <iostream>
#include <wchar.h>

using namespace std;

void listAllProcess(DWORD dwProcessID)
{
    HANDLE hProcess;
    BOOL bEnumProcessModule = FALSE;
    HANDLE hMod;
    DWORD bytesneeded = 0;
    wchar_t chProcessName[MAX_PATH] = L"UNKNOU";
    wchar_t chProcessPath[MAX_PATH] = L"UNKNOU PATH";

    //open each process based on their PID.
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                           FALSE,
                           dwProcessID);

    if(NULL != hProcess)
    {
        //get the process module.
        bEnumProcessModule = EnumProcessModulesEx(hProcess,
                                                  &hMod,
                                                  sizeof(hMod),
                                                  &bytesneeded,
                                                  LIST_MODULES_ALL);

        if(bEnumProcessModule == TRUE)
        {
            //get the process handle name.
            GetModuleBaseName(hProcess,
                              hMod,
                              chProcessName,
                              sizeof(chProcessName) / sizeof(wchar_t));
            //get the each process path.
            GetModuleFileName(hProcess,
                              hMod,
                              chProcessPath,
                              sizeof(chProcessName) / sizeof(wchar_t));
        }
    }
    cout << ".............................................................." << endl;
    wcout << "Module Base Name: " << chProcessName << endl;
    wcout << "Process Path Name: " << chProcessPath << endl;
    wcout << "Process ID: " << dwProcessID << endl;
    cout << ".............................................................." << endl;

    //close handle for each open process.
    CloseHandle(hProcess);
}

int main()
{
    //local variable.
    DWORD aProcess[2048] = {0};
    BOOL bEnumProcess = FALSE;
    DWORD bytesneeded = 0;
    DWORD TotalProcess = 0;

    //enumerating the process.
    bEnumProcess = EnumProcesses(aProcess,
                                 sizeof(aProcess),
                                 &bytesneeded);

    if(FALSE == bEnumProcess)
    {
        cout << "Enum Process - Failed: " << GetLastError() << endl;
    }
    cout << "Enum Process - sucess..." << endl;

    //caculate no's of PID.
    TotalProcess = bytesneeded / sizeof(DWORD);

    cout << "total no of process: " << TotalProcess << endl;

    //call each process id's and get this module and path name.
    for(size_t i = 0; i < TotalProcess; i++)
    {
        listAllProcess(aProcess[i]);
    }


    system("pause");
    return 0;
}

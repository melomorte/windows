#include <windows.h> //windows service
#include <iostream>

using namespace std;

//........................GLOBAL VARIABLES DECLARATION...................................................
#define SERVICE_NAME      TEXT("KAYQUE Service")         //Service name
SERVICE_STATUS            ServiceStatus = {0};           //service status structure
SERVICE_STATUS_HANDLE     hServiceStatusHandle = NULL;   //SERVICE STATUS HANDLE FOR REGISTER THE SERVICE
HANDLE                    hServiceEvent = NULL;          //event handle for service

//.......................WINDOWS SERVICE FUNCTIONS DECLARATIONS..........................................
void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpArgv);   //service main function
void WINAPI serviceControlHandle(DWORD dwControl);       //service control handle
void ServiceReportStatus(DWORD dwCurrentState,
                         DWORD dwWin32ExitCode,
                         DWORD dwWaitHint);              //service report status
void ServiceInit(DWORD dwArgc, LPTSTR *lpArgv);          //service init function
void ServiceInstall(void);                               //service install function
void ServiceDelete(void);                                //service delete function
void ServiceStart(void);                                 //service start function
void ServiceStop(void);                                  //service stop function

//.......................MAIN FUNCTION...................................................................
int main(int argc, CHAR *argv[])
{
    cout << "In Main Function - Start..." << endl;

    //........LOCAL VARIABLE DEFINITION........
    BOOL bStServiceCtrlDispatcher = FALSE;

    //........FUNCTION LOGIC STARTS HERE.......
    if(lstrcmpiA(argv[1], "install")== 0)
    {
        system("cls");
        //...call service install function...
        ServiceInstall();

        Sleep(200);
        cout << "installation sucess..." << endl;
        Beep(523,500);
    }//if
    else if(lstrcmpiA(argv[1], "start")== 0)
    {
        system("cls");
        //...call service start function...
        ServiceStart();

        Sleep(200);
        cout << "service start sucess..." << endl;
        Beep(523,500);
    }//else if
    else if(lstrcmpiA(argv[1], "stop")== 0)
    {
        system("cls");
        //...call service stop function...
        ServiceStop();

        Sleep(200);
        cout << "service stop sucess..." << endl;
        Beep(523,500);
    }//else if
    else if(lstrcmpiA(argv[1], "delete")== 0)
    {
        system("cls");
        //...call service delete function...
        ServiceDelete();

        Sleep(200);
        cout << "service delete sucess..." << endl;
        Beep(523,500);
    }
    else
    {
        //step - 1: fill the service table entry (2d array).
        SERVICE_TABLE_ENTRY DispatchTable[] =
        {
            {SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION)ServiceMain},
            {NULL, NULL}
        };

        //step - 2: start service control dispatcher.
        bStServiceCtrlDispatcher = StartServiceCtrlDispatcher(DispatchTable);

        if(FALSE == bStServiceCtrlDispatcher)
        {
            cout << "bStServiceCtrlDispatcher - failed: " << GetLastError() << endl;
        }
        else
        {
            cout << "bStServiceCtrlDispatcher - sucess..." << endl;
        }//if
    }//else

    cout << "Main Function End..." << endl;
    system("pause");
    return 0;
}//......................END OF MAIN FUNCTION............................................................

//.......................SERVICE MAIN FUNCTION DEFINITION................................................
void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpArgv)
{
    cout << "Service Main - Start..." << endl;

    //........LOCAL VARIABLE DEFINITION........
    BOOL bServiceStatus = FALSE;

    //step - 1: registering service control handle function to SCM.
    hServiceStatusHandle = RegisterServiceCtrlHandler(SERVICE_NAME,
                                                      serviceControlHandle);

    if(hServiceStatusHandle == NULL)
    {
        cout << "registering service control handle - failed: " << GetLastError() << endl;
    }
    else
    {
        cout << "registering service control handle - sucess..." << endl;
    }

    //step - 2: SERVICE_STATUS initial setup here.
    ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ServiceStatus.dwServiceSpecificExitCode = 0;

    //step - 3: call service report status for notifying initial setup.
    ServiceReportStatus(SERVICE_START_PENDING, NO_ERROR, 3000);

    //step - 4: check the service status.
    bServiceStatus = SetServiceStatus(hServiceStatusHandle, &ServiceStatus);

    if(FALSE == bServiceStatus)
    {
        cout << "Service Status Initial Setup - Failed: " << GetLastError() << endl;
    }
    else
    {
        cout << "Service Status Initial Setup - sucess..." << endl;
    }

    //step - 5: call service init function
    ServiceInit(dwArgc, lpArgv);

    cout << "Service Main End..." << endl;
}//......................END OF SERVICE MAIN FUNCTION....................................................

//.......................SERVICE CONTROL HANDLE DEFINITION...............................................
void WINAPI serviceControlHandle(DWORD dwControl)
{
    cout << "service Control Handle - Start..." << endl;

    switch(dwControl)
    {
        case SERVICE_CONTROL_STOP:
            {
                //call service report status.
                ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);

                cout << "Service stopped" << endl;
                break;
            }
        default:
                break;
    }

    cout << "Service Control Handle End..." << endl;
}//......................END OF SERVICE CONTROL HANDLE FUNCTION..........................................

//.......................SERVICE INIT DEFINITION.........................................................
void ServiceInit(DWORD dwArgc, LPSTR *lpArgv)
{
    cout << "Service Init - Start..." << endl;

    //step - 1: Create event.
    hServiceEvent = CreateEvent(NULL,  //security attributes
                                TRUE,  //manual reset event
                                FALSE, //non signaled
                                NULL); //name of event

    if(NULL == hServiceEvent)
    {
        //Call Service Report Status.
        ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);
    }
    else
    {
        //Call Service Report Status fun to notify SCM for current states of service.
        ServiceReportStatus(SERVICE_RUNNING, NO_ERROR, 0);
    }

    //step - 2: Check whether to stop the service.
    while(1)
    {
        //wait for single object which wait event to be signaled.
        WaitForSingleObject(hServiceEvent, INFINITE);

        //send report status to SCM.
        ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);

    }
    cout << "Service Init End..." << endl;
}//......................END OF SERVICE INIT FUNCTION....................................................

//.......................SERVICE REPORT STATUS FUNCTION..................................................
void ServiceReportStatus(DWORD dwCurrentState,
                         DWORD dwWin32ExitCode,
                         DWORD dwWaitHint)
{
    cout << "Service Report Status - Start..." << endl;
    //Local variable definitions
    static DWORD dwCheckPoint = 1;
    BOOL bSetServicStatus = FALSE;

    //step - 1: Filling the service status structure.
    ServiceStatus.dwCurrentState = dwCurrentState;
    ServiceStatus.dwWin32ExitCode = dwWin32ExitCode;
    ServiceStatus.dwWaitHint = dwWaitHint;

    //step - 2: check the current state of service.
    if(dwCurrentState == SERVICE_START_PENDING)//service is about to start.
    {
        ServiceStatus.dwControlsAccepted = 0;
    }
    else
    {
        ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    }

    //step - 3: progress for service operation.
    if((dwCurrentState == SERVICE_RUNNING) || (dwCurrentState == SERVICE_STOPPED))
    {
        ServiceStatus.dwCheckPoint = 0;
    }
    else
    {
        ServiceStatus.dwCheckPoint = dwCheckPoint++;
    }

    //step - 4: notify he current status of SCM.
    bSetServicStatus = SetServiceStatus(hServiceStatusHandle, &ServiceStatus);

    if(FALSE == bSetServicStatus)
    {
        cout << "Service Status Failed: " << GetLastError() << endl;
    }
    else
    {
        cout << "Service Status Sucess..." << endl;
    }//if
    cout << "Service Report Status End..." << endl;

}//......................END OF SERVICE REPORT STATUS FUNCTION...........................................

//.......................SERVICE INSALL FUNCTION.........................................................
void ServiceInstall(void)
{
    cout << "Service Install - Start..." << endl;
    //Local variable definitions.
    SC_HANDLE hScOpenScManager = NULL;
    SC_HANDLE hScCreateService = NULL;
    DWORD dwGetModuleFileName = 0;
    TCHAR szPath[MAX_PATH];

    //step - 1: get module file name get the executable file from SCM.
    dwGetModuleFileName = GetModuleFileName(NULL, szPath, MAX_PATH);

    if(0 == dwGetModuleFileName)
    {
        cout << "Service Installed - Failed: " << GetLastError() << endl;
    }
    else
    {
        cout << "Service Installed - sucess..." << endl;
    }//if

    //step - 2: open the service control manager.
    hScOpenScManager = OpenSCManager(NULL,                      //local machine.
                                     NULL,                      //by default database.
                                     SC_MANAGER_ALL_ACCESS);    //Access right.

    if(NULL == hScOpenScManager)
    {
        cout << "Open Manager - failed: " << GetLastError() << endl;
    }
    else
    {
        cout << "Open Manager - sucess..." << endl;
    }

    //step - 3: Create the Service.
    hScCreateService = CreateService(hScOpenScManager,
                                     SERVICE_NAME,
                                     SERVICE_NAME,
                                     SERVICE_ALL_ACCESS,
                                     SERVICE_WIN32_OWN_PROCESS,
                                     SERVICE_DEMAND_START,
                                     SERVICE_ERROR_NORMAL,
                                     szPath,
                                     NULL,
                                     NULL,
                                     NULL,
                                     NULL,
                                     NULL);

    if(NULL == hScCreateService)
    {
        cout << "Create Service - Failed: " << GetLastError() << endl;
        CloseServiceHandle(hScOpenScManager);
    }
    else
    {
        cout << "Create Service - sucess..." << endl;
    }

    //step - 4: close the handle for Open SC manager and Create Service.
    CloseServiceHandle(hScCreateService);
    CloseServiceHandle(hScOpenScManager);

    cout << "Service Install End..." << endl;

}//......................END OF SERVICE INSTALL FUNCTION.................................................

//.......................SERVICE DELETE FUNCTION.........................................................
void ServiceDelete(void)
{
    cout << "Service Delete - Start..." << endl;
    //local variable definition.
    SC_HANDLE hScOpenSCManager = NULL;
    SC_HANDLE hScOpenService = NULL;
    BOOL bDeleteService = FALSE;

    //step - 1: Open the service control manager.
    hScOpenSCManager = OpenSCManager(NULL,
                                     NULL,
                                     SC_MANAGER_ALL_ACCESS);

    if(NULL == hScOpenSCManager)
    {
        cout << "Open Manager - Failed: " << GetLastError() << endl;
    }
    else
    {
        cout << "Open Manager Sucess..." << endl;
    }

    //step - 2: Open the service.
    hScOpenService = OpenService(hScOpenSCManager,
                                 SERVICE_NAME,
                                 SERVICE_ALL_ACCESS);

    if(NULL == hScOpenService)
    {
        cout << "Open Service Failed: " << GetLastError() << endl;
    }
    else
    {
        cout << "Open Service - Sucess..." << endl;
    }

    //step - 3: Delete Service.
    bDeleteService = DeleteService(hScOpenService);

    if(NULL == bDeleteService)
    {
        cout << "Delete Service Failed: " << GetLastError() << endl;
    }
    else
    {
        cout << "Delete Service - Sucess..." << endl;
    }

    //step - 4: Close he handle for SCM and Open service
    CloseServiceHandle(hScOpenService);
    CloseServiceHandle(hScOpenSCManager);

    cout << "Delete Service End..." << endl;

}//......................END OF SERVICE DELETE FUNCTION..................................................

//.......................SERVICE START FUNCTION..........................................................
void ServiceStart(void)
{
    cout << "Service Start - Start..." << endl;
    //local variable.
    BOOL bStartService = FALSE;
    SERVICE_STATUS_PROCESS SvcStatusProcess;
    SC_HANDLE hOpenSCManager = NULL;
    SC_HANDLE hOpenService = NULL;
    BOOL bQueryServiceStatus = FALSE;
    DWORD dwBytesNeeded;

    //step - 1: Open Service Control Manager.
    hOpenSCManager = OpenSCManager(NULL,
                                   NULL,
                                   SC_MANAGER_ALL_ACCESS);

    if(NULL == hOpenSCManager)
    {
        cout << "OpenSCManager - failed: " << GetLastError() << endl;
    }
    else
    {
        cout << "OpenSCManager - sucess..." << endl;
    }

    //step - 2: Open Service.
    hOpenService = OpenService(hOpenSCManager,
                               SERVICE_NAME,
                               SC_MANAGER_ALL_ACCESS);

    if(NULL == hOpenService)
    {
        cout << "Open Service - failed: " << GetLastError() << endl;
        CloseServiceHandle(hOpenSCManager);
    }
    else
    {
        cout << "Open Service - sucess..." << endl;
    }

    //step - 3: query about current service status.
    bQueryServiceStatus = QueryServiceStatusEx(hOpenService,
                                               SC_STATUS_PROCESS_INFO,
                                               (LPBYTE)&SvcStatusProcess,
                                               sizeof(SERVICE_STATUS_PROCESS),
                                               &dwBytesNeeded);

    if(FALSE == bQueryServiceStatus)
    {
        cout << "Query Service - Failed: " << GetLastError() << endl;
    }
    else
    {
        cout << "Query Service - sucess..." << endl;
    }

    //step - 4: checked Service is running or stopped.
    if((SvcStatusProcess.dwCurrentState != SERVICE_STOPPED)&&
       (SvcStatusProcess.dwCurrentState != SERVICE_STOP_PENDING))
    {
        cout << "Service Running..." << endl;
    }
    else
    {
        cout << "Service Stopped..." << endl;
    }

    //step - 5: if service is stopped then query the service.
    while(SvcStatusProcess.dwCurrentState == SERVICE_STOP_PENDING)
    {
        bQueryServiceStatus = QueryServiceStatusEx(hOpenService,
                                                   SC_STATUS_PROCESS_INFO,
                                                   (LPBYTE)&SvcStatusProcess,
                                                   sizeof(SERVICE_STATUS_PROCESS),
                                                   &dwBytesNeeded);

        if(FALSE == bQueryServiceStatus)
        {
            cout << "Query Service - Failed: " << GetLastError() << endl;
            CloseServiceHandle(hOpenService);
            CloseServiceHandle(hOpenSCManager);
        }
        else
        {
            cout << "Query Service - sucess..." << endl;
        }
    }//while

    //step - 6: start the service.
    bStartService = StartService(hOpenService,
                                 NULL,
                                 NULL);

    if(FALSE == bStartService)
    {
        cout << "Start Service - Failed: " << GetLastError() << endl;
        CloseServiceHandle(hOpenService);
        CloseServiceHandle(hOpenSCManager);
    }
    else
    {
        cout << "Open Service - sucess..." << endl;
    }

    //step - 7: query the service again.
     bQueryServiceStatus = QueryServiceStatusEx(hOpenService,
                                                   SC_STATUS_PROCESS_INFO,
                                                   (LPBYTE)&SvcStatusProcess,
                                                   sizeof(SERVICE_STATUS_PROCESS),
                                                   &dwBytesNeeded);

    if(FALSE == bQueryServiceStatus)
    {
        cout << "Query Service - Failed: " << GetLastError() << endl;
        CloseServiceHandle(hOpenService);
        CloseServiceHandle(hOpenSCManager);
    }
    else
    {
        cout << "Query Service - sucess..." << endl;
    }

    //step - 8: check service is running or not.
    if(SvcStatusProcess.dwCurrentState == SERVICE_RUNNING)
    {
        cout << "Service Running - sucess..." << endl;
    }
    else
    {
        cout << "Service Running - Failed: " << GetLastError() << endl;
        CloseServiceHandle(hOpenService);
        CloseServiceHandle(hOpenSCManager);
    }

    //step - 9: Close the service Handle for Open SC Manager && Open Service.
    CloseServiceHandle(hOpenService);
    CloseServiceHandle(hOpenSCManager);

    cout << "Service Start End..." << endl;
}//.......................END OF SERVICE START FUNCTION..................................................

//........................SERVICE STOP FUNCTION..........................................................
void ServiceStop(void)
{
    cout << "Service Stop - Start..." << endl;
    //local variable.
    SERVICE_STATUS_PROCESS SvcStatusProcess;
    SC_HANDLE hScOpenSCManager = NULL;
    SC_HANDLE hScOpenService = NULL;
    BOOL bQueryServiceStatus = TRUE;
    BOOL bControlService = TRUE;
    DWORD dwBytesNeeded;

    //step - 1: Open Service Control Manager.
    hScOpenSCManager = OpenSCManager(NULL,
                                     NULL,
                                     SC_MANAGER_ALL_ACCESS);

    if(NULL == hScOpenSCManager)
    {
        cout << "OpenSCManager - Failed: " << GetLastError() << endl;
    }
    else
    {
        cout << "OpenSCManager - sucess..." << endl;
    }//if

    //step - 2: Open Your Service.
    hScOpenService = OpenService(hScOpenSCManager,
                                 SERVICE_NAME,
                                 SC_MANAGER_ALL_ACCESS);

    if(NULL == hScOpenService)
    {
        cout << "Open Service - Failed: " << GetLastError() << endl;
        CloseServiceHandle(hScOpenSCManager);
    }
    else
    {
        cout << "Open Service - sucess..." << endl;
    }

    //step - 3:Query Service Status.

    bQueryServiceStatus = QueryServiceStatusEx(hScOpenService,
                                               SC_STATUS_PROCESS_INFO,
                                               (LPBYTE)&SvcStatusProcess,
                                               sizeof(SERVICE_STATUS_PROCESS),
                                               &dwBytesNeeded);

    if(FALSE == bQueryServiceStatus)
    {
        cout << "Query Service - Failed: " << GetLastError() << endl;
        CloseServiceHandle(hScOpenService);
        CloseServiceHandle(hScOpenSCManager);
    }
    else
    {
        cout << "Query Service - Sucess..." << endl;
    }

    //step - 4: Send a stop code to the service control manager.
    bControlService = ControlService(hScOpenService,
                                     SERVICE_CONTROL_STOP,
                                     (LPSERVICE_STATUS)&SvcStatusProcess);

    if(TRUE == bControlService)
    {
        cout << "Control Service - Sucess..." << endl;
    }
    else
    {
        cout << "Control Service - Failed: " << GetLastError() << endl;
        CloseServiceHandle(hScOpenService);
        CloseServiceHandle(hScOpenSCManager);
    }//if

    //step - 5: wait for service to stop.
    while(SvcStatusProcess.dwCurrentState != SERVICE_STOPPED)
    {
        //step - 6: inside while loop query the service.
        bQueryServiceStatus = QueryServiceStatusEx(hScOpenService,
                                                   SC_STATUS_PROCESS_INFO,
                                                   (LPBYTE)&SvcStatusProcess,
                                                   sizeof(SERVICE_STATUS_PROCESS),
                                                   &dwBytesNeeded);

        if(TRUE == bQueryServiceStatus)
        {
            cout << "Query Service - Failed: " << GetLastError() << endl;
            CloseServiceHandle(hScOpenService);
            CloseServiceHandle(hScOpenSCManager);
        }
        else
        {
            cout << "Query Service - sucess..." << endl;
        }

        //step - 7: inside while loop check the current state of service.
        if(SvcStatusProcess.dwCurrentState == SERVICE_STOPPED)
        {
            cout << "Service Stopped - sucess..." << endl;
            break;
        }
        else
        {
            cout << "Service Stopped - Failed: " << GetLastError() << endl;
             CloseServiceHandle(hScOpenService);
             CloseServiceHandle(hScOpenSCManager);
        }
    }//while

    //step - 8: Close the Handle for open SCM &open service
    CloseServiceHandle(hScOpenService);
    CloseServiceHandle(hScOpenSCManager);

}//........................END OF SERVICE STOP FUNCTION..................................................

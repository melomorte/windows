#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "______ NAMED PIPE CLIENT______" << endl;

    //named pipe local variable

    HANDLE hCreateNamedPipe;
    char szInputBuffer[1023];
    char szOutputBuffer[1023];
    DWORD dwszInputBuffer = sizeof(szInputBuffer);
    DWORD dwszOutputBuffer = sizeof(szOutputBuffer);

    //connectNaamedPipe variable local
    BOOL bConnectPipe;


    //WriteFile local variable

    BOOL bWriteFile;
    char szWriteFileBuffer[1023] = "Hello From Named Pipe Client!";
    DWORD dwWriteBufferSize = sizeof(szWriteFileBuffer);
    DWORD dwNoBytesWrite;

    //Flush Buffer
    BOOL bFlushFileBuffer;

    //ReadFile
    BOOL bReadFile;
    char szReadFileBuffer[1023];
    DWORD dwReadBufferSize[1023];
    DWORD dwNoBytesRead;

    //CreateNamedPipe
    hCreateNamedPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\MYNAMEDPIPE"),
                                       PIPE_ACCESS_DUPLEX,
                                       PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                                       PIPE_UNLIMITED_INSTANCES,
                                       dwszOutputBuffer,
                                       dwszInputBuffer,
                                       0,
                                       NULL);

    if(hCreateNamedPipe == INVALID_HANDLE_VALUE)
    {
        cout << "CreateNamedPipe - failed:" << GetLastError();
    }
    cout << "CreateNamedPipe - sucess..." << endl;


    //connect NamedPipe step 2
    bConnectPipe = ConnectNamedPipe(hCreateNamedPipe, NULL);
    if(bConnectPipe == FALSE)
    {
        cout << "ConnectNamedPipe - failed: " << GetLastError() << endl;
    }
    cout << "ConnectNamedPipe - sucess..." << endl;

    //WriteFile operation - atep
    bWriteFile = WriteFile(hCreateNamedPipe,
                           szWriteFileBuffer,
                           dwWriteBufferSize,
                           &dwNoBytesWrite,
                           NULL);

    if(bWriteFile == FALSE)
    {
        cout << "WriteFile - failed: " << GetLastError() << endl;
    }
    cout << "WriteFile - sucess..." << endl;

    //Flush the File Buffer - step 4
    bFlushFileBuffer = FlushFileBuffers(hCreateNamedPipe);
    if(bFlushFileBuffer == FALSE)
    {
        cout << "FlushFileBuffer - failed: " << GetLastError() << endl;
    }
    cout << "FlushFileBuffer - sucess..." << endl;

    //ReadFile - step 5

    bReadFile = ReadFile(hCreateNamedFile,
                         szReadFileBuffer,
                         dwReadBufferSize,
                         &dwNoBytesRead,
                         NULL);
    if(bReadFile == FALSE)
    {
        cout << "ReadFile - failed: " << GetLastError() << endl;
    }
    cout << "ReadFile - sucess..." << endl;

    //DisconnectNamedPipe
    DisconnectNamedPipe(hCreateNamedPipe);
    //CloseHandle
    CloseHandle(hCreateNamedPipe);

    system("pause");
    return 0;
}

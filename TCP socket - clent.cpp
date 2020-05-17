#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "......TCP CLIENT......" << endl;
    cout << endl;

    //local variable
    WSADATA Winsockdata;
    int iWsaStartup;
    int iWsaCleanup;

    SOCKET TCPClientSocket;
    int iCloseSocket;

    struct sockadddr_in TCPServerAdd;

    int iConnect;

    int iRecv;
    char RecvBuffer[512];
    int iRecvBuffer = strlen(RecvBuffer)+1;

    int iSend;
    char SenderBuffer[512] = "client - hey, how, how, how, how, how";
    int iSenderBuffer = strlen(SenderBuffer)+1;

    //step - 1: Wsastartup fun
    iWsaStartup = WSAStartup(MAKEWORD(2,2),&Winsockdata);

    if(iWsaStartup != 0)
    {
        cout << "WsaStartup - failed: " << endl;
    }
    cout << "WsaStartup - sucess..." << endl;

    //step - 2: socket creation
    TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(TCPClientSocket == INVALID_SOCKET)
    {
        cout << "TCPClientSocket - failed: " << endl;
    }
    cout << "TCPClientSocket - sucess" << endl;

    //step - 3: fill structure
    TCPServerAdd.sin_family = AF_NET;
    TCPServerAdd.sin_adddr.s = inet_addr("127.0.0.1");
    TCPServerAdd.sin_port = htons(8000);

    //step - 4: connect fun
    iConnect = connect(TCPClientSocket,(SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));

    if(iConnect == SOCKET_ERROR)
    {
        cout << "Connect - failed: " << endl;
    }
    cout << "Connect - sucess..." << endl;

    //step - 5: recv data from server
    iRecv = recv(TCPClientSocket, RecvBuffer, iRecvBuffer, 0);

    if(iRecv == SOCKET_ERROR)
    {
        cout << "recv - failed: " << endl;
    }
    cout << "recv - sucess..." << endl;

    //step - 6: send datato server
    iSend = send(TCPClientSocket, SenderBuffer, iSenderBuffer, 0);

    if(iSend == SOCKET_ERROR)
    {
        cout << "send - failed: " << endl;
    }
    cout << "send - sucess..." << endl;

    //step - 7: close socket fun
    iCloseSocket = closesocket(TCPClientSocket);

    if(iCloseSocket == SOCKET_ERROR)
    {
        cout << "CloseSocket - failed: " << endl;
    }
    cout << "CloseSocket - sucess..." << endl;

    //step - WSA cleanup fun
    iWsaCleanup = WSACleanup();

    if(iWsaCleanup == SOCKET_ERROR)
    {
        cout << "WsaCleanup - failed: " << endl;
    }
    cout << "WsaCleanup - sucess..." << endl;


    system("pause");
    return 0;
}

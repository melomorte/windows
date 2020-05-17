#include <winSock2.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "......TCP SERVER......" << endl;
    cout << endl;

    //local variable
    WSADATA Winsockdata;
    int iWsaStartup;
    int iWsaCleanup;

    SOCKET TCPServerSocket;
    int iCloseSocket;

    struct sockaddr_in TCPServerAdd;
    struct sockaddr_in TCPClientAdd;
    int iTCPClient = sizeof(TCPClientAdd);

    int iBind;
    int iListen;

    SOCKET  sAcceptSocket;

    int iSend;
    char SenderBuffer[512] = "server - hey, how, hey, how, hey, how";
    int iSendrBuffer = strlen(SenderBuffer)+1;

    int iRecv;
    char RecvBuffer[512];
    int iRecvBuffer = strlen(RecvBuffer)+1;

    //step - 1: WSAStartup
    iWsaStartup = WSAStartup(MAKEWORD(2,2)&Winsockdata);

    if(iWsaStartup != 0)
    {
        cout << "WSAStartup - failed: " << endl;
    }
    cout << "WSAStartup - sucess..." << endl;

    //step - 2: fill the structure
    TCPServerAdd.sin_family = AF_NET;
    TCPServerAdd.sin_adddr.s = inet_addr("127.0.0.1");
    TCPServerAdd.sin_port = htons(8000);

    //step - 3: socket creation
    TCPServerSocket = socket(AF_INET,
                             SOCK_STREAM,
                             IPPROTO_TCP);

    if(TCPServerSocket == INVALID_SOCKET)
    {
        cout << "TCPServerSocket - failed: " << endl;
    }
    cout << "TCPServerSocket - sucess..." << endl;

    //step - 4: bind fun
    iBind = bind(TCPServerSocket(SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));

    if(iBind == SOCKET_ERROR)
    {
        cout << "bind - failed: " << endl;
    }
    cout << "bind - sucess..." << endl;

    //step - 5: listen fun
    iListen = listen(TCPServerSocket,2);

    if(iListen == SOCKET_ERROR)
    {
        cout << "listen - failed: " << endl;
    }
    cout << "listen - sucess..." << endl;

    //step - 6: accept
    sAcceptSocket = accept(TCPServerSocket, (SOCKADDR*)&TCPClientAdd, &iTCPClient);

    if(sAcceptSocket == INVALID_SOCKET)
    {
        cout << "AcceptSocket - failed: " << endl;
    }
    cout << "AcceptSocket - sucess..." << endl;

    //step - 7: send data to client
    iSend = send(sAcceptSocket, SenderBuffer, iSenderBuffer, 0)

    if(iSend == SOCKET_ERROR)
    {
        cout << "Send - failed: " << endl;
    }
    cout << "Send - sucess..." << endl;

    //step - 8: Recv data from client
    iRecv = recv(sAcceptSocket,RecvBuffer, iRecvBuffer, 0);

    if(iRecv == SOCKET_ERROR)
    {
        cout << "Recv - failed: " << endl;
    }
    cout << "Recv - sucess..." << endl;

    //step - 9: Close Socket
    iCloseSocket = closesocket(TCPServerSocket);

    if(iCloseSocket == SOCKET_ERROR)
    {
        cout << "Close Socket - failed: " << endl;
    }
    cout << "Close Socket - sucess..." << endl;

    //step - 10: Cleanup
    iWsaCleanup = WSACleanup();

    if(iWsaCleanup == SOCKET_ERROR)
    {
        cout << "WsaCleanup - failed: " << endl;
    }
    cout << "WsaCleanup - sucess..." << endl;


    system("pause");
    return 0;
}

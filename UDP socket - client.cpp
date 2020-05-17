#include <windows.h>
#include <winsock.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "\t\t......UDP CLIENT......" << endl;
    cout << endl;

    WSADATA WinSockData;
    int iWsaStartup;
    int iWsaCleanup;

    SOCKET UDPSocketClient;
    struct sockaddr_in UDPServer;

    char Buffer[512] = "hey hey hey hey hey hey hey";
    int iSendto;

    int iBufferlen = strlen(Buffer)+1;
    int iUDOServerlen = sizeof(UDPServer);
    int iCloseSocket;

    //step - 1: initialize of winsock

    iWsaStartup = WSAStartup(MAKEWORD(2,2), &WinSockData);

    if(iWsaStartup != 0)
    {
        cout << "iWsaStartup - error: " << endl;
    }
    cout << "iWsaStartup - sucess..." << endl;

    //step - 2: fill the UDPServer structure
    UDPServer.sin_family = AF_INET;
    UDPServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    UDPServer.sin_port = htons(8001);

    //step - 3: SocketCreation
    UDPSocketClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(UDPSocketClient == INVALID_SOCKET)
    {
        cout << "UDPSocketClient - failed" << endl;
    }
    cout << "UDPSocketClient - sucess..." << endl;

    //step - 4: send to fun
    iSendto = sendto(UDPSocketClient,
                     Buffer,
                     iBufferlen,
                     MSG_DONTROUTE,
                     (SOCKADDR*)&UDPServer,
                     sizeof(UDPServer));

    if(iSendto == SOCKET_ERROR)
    {
        cout << "sending data - failed" << endl;
    }
    cout << "sending data - sucess..." << endl;

    //step - 5: CloseSocket Function

    iCloseSocket = closesocket(UDPSocketClient);

    if(iCloseSocket == SOCKET_ERROR)
    {
        cout << "CloseSocket - failed: " << endl;
    }
    cout << "CloseSocket - sucess..." << endl;

    //step - 6: te4rminate dll

    iWsaCleanup = WSACleanup();

    if(iWsaCleanup == SOCKET_ERROR)
    {
        cout << "iWsaCleanup - failed: " << endl;
    }
    cout << "iWsaCleanup - sucess..." << endl;

    system("pause");
    return 0;
}

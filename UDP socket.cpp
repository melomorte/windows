#include <windows.h>
#include <winsock.h>
#include <iostream>

using namespace std;

int main()
{
    cout << "\t\t......UDP SERVER......" << endl;
    cout << endl;

    WSADATA WinSockData;
    int iWsaStartup;
    int iWsaCleanup;

    SOCKET UDPSocketServer;
    struct sockaddr_in UDPClient;

    char Buffer[512];
    int iBufferlen = strlen(Buffer)+1;

    int iBind;
    int iReciveFrom;

    int iUDPClientlen = sizeof(UDPClient);
    int iCloseSocket;

    //step - 1: initialization of winsock
    iWsaStartup = WSAStartup(MAKEWORD(2,2), &WinSockData);

    if(iWsaStartup != 0)
    {
        cout << "iWsaStartup - failed: " << endl;
    }
    cout << "iWsaStartup - sucess..." << endl;

    //step - 2: fill the UDP client (SOCKET ADDRESS) structure
    UDPClient.sin_family = AF_INET;
    UDPClient.sin_addr.s_addr = inet_addr("127.0.0.1");
    UDPClient.sin_port = htons(8001);

    //step - 3: socket creation
    UDPSocketServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(UDPSocketServer == INVALID_SOCKET)
    {
        cout << "UDP Socket Server - failed: " << endl;
    }
    cout << "UDP Socket Server - sucess..." << endl;

    //step - 4: bind the server
    iBind = bind(UDPSocketServer,
                 (SOCKADDR*)&UDPClient,
                 sizeof(UDPClient));

    if(iBind == SOCKET_ERROR)
    {
        cout << "Bind - failed: " << endl;
    }
    cout << "Bind - sucess..." << endl;

    //step - 5: receive from data for client
    iReciveFrom = recvfrom(UDPSocketServer,
                           Buffer,
                           iBufferlen,
                           MSG_PEEK,
                           (SOCKADDR*)&UDPClient,
                           &iUDPClientlen);

    if(iReciveFrom == SOCKET_ERROR)
    {
        cout << "ReciveFrom - failed: " << endl;
    }
    cout << "ReciveFrom - sucess..." << endl;
    cout << "Receive data: " << Buffer << endl;

    //step - 6: CloseSocket function
    iCloseSocket = closesocket(UDPSocketServer);

    if(iCloseSocket == SOCKET_ERROR)
    {
        cout << "CloseSocket - failed: " << endl;
    }
    cout << "CloseSocket - sucess..." << endl;

    //step - 7: WSALeanup fun for terminate from dll
    iWsaCleanup = WSACleanup();

    if(iWsaCleanup == SOCKET_ERROR)
    {
        cout << "iWsaCleanup - failed: " << endl;
    }
    cout << "iWsaCleanup - sucess..." << endl;

    system("pause");
    return 0;
}

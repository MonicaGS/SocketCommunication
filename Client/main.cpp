//Client

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)
#include <WinSock2.h>
#include <iostream>

int main()
{
    //Winsock Startup
    WSAData wsaData;
    WORD DllVersion = MAKEWORD(2, 1);
    if (WSAStartup(DllVersion, &wsaData) != 0)
    {
        MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
        exit(1);
    }

    SOCKADDR_IN addr;
    int addrlen = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //localhost
    addr.sin_port = htons(1111);                    //Port
    addr.sin_family = AF_INET;		                //IPV4 Socket

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
    {
        MessageBoxA(NULL, "Failed to connect", "Error", MB_OK | MB_ICONERROR);
        return 0;                                   //failed to connect
    }
    std::cout << "Connected!" << std::endl;

    char MOTD[256] = "Welcome! This is the Message of the Day.";    //Create buffer with message of the day
    send(Connection, (char*)&MOTD, sizeof(MOTD), NULL);

    system("pause");
    closesocket(Connection);
    return 0;
}
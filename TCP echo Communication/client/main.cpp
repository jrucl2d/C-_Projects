#include <iostream>
#include <string>
#include <winsock2.h>

using namespace std;

// 에러 핸들링
void ShowErrorMessage(string message){
    cout << "[ERROR]: " << message << '\n';
    system("pause");
    exit(1);
}
int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    SOCKADDR_IN serverAddress;

    int serverPort = 8000; // 동일한 포트번호
    char received[256];
    string sent;

    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0) // Winsock을 초기화(2.2버전), Startup된 결과를 wsaData에서 확인
        ShowErrorMessage("WSAStartup()");

    clientSocket = socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓을 생성

    if(clientSocket == INVALID_SOCKET)
        ShowErrorMessage("socket()");

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET; // IPv4
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // 문자열 IP를 네트워크 바이트 형식으로
    serverAddress.sin_port = htons(serverPort); // 2바이트 정수 네트워크 바이트 형식으로, 포트 설정
    if(connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
        ShowErrorMessage("connect()");
    cout << "[NOW] connect()\n";

    while(1){
        cout << "[MESSAGE SEND]: ";
        getline(cin, sent);
        if(sent == "") continue;
        send(clientSocket, sent.c_str(), sent.length(), 0);
        int length = recv(clientSocket, received, sizeof(received), 0);
        received[length] = '\0';
        if(strcmp(received, "[exit]") == 0){
            cout << "[SERVER EXIT]\n";
            break;
        }
        cout << "[SERVER MESSAGE]: " << received << '\n';
    }
    closesocket(clientSocket);
    WSACleanup();
    system("pause");
    return 0;
}

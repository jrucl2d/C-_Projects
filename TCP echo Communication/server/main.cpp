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
    SOCKET serverSocket, clientSocket; // 서버에서는 클라이언트 소켓 또한 필요하다.
    SOCKADDR_IN  serverAddress, clientAddress;

    int serverPort = 8000;
    char received[256];

    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0) // Winsock을 초기화(2.2버전), Startup된 결과를 wsaData에서 확인
        ShowErrorMessage("WSAStartup()");

    serverSocket = socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓을 생성(IPv4, TCP)

    if(serverSocket == INVALID_SOCKET)
        ShowErrorMessage("socket()");

    memset(&serverAddress, 0, sizeof(serverAddress)); // 서버주소 0으로 초기화
    serverAddress.sin_family = AF_INET; // IPv4
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // 4바이트 정수를 네트워크 바이트 형식으로, 본인의 주소로 서버를 열겠다.
    serverAddress.sin_port = htons(serverPort); // 2바이트 정수 네트워크 바이트 형식으로, 포트 설정
    if(bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
        ShowErrorMessage("bind()");
    cout << "[NOW] bind()\n";

    if(listen(serverSocket, 5) == SOCKET_ERROR) // 동시에 5개 클라이언트 접속 가능
        ShowErrorMessage("listen()");
    cout << "[NOW] listen()\n";

    int sizeClientAddress = sizeof(clientAddress);
    clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddress, &sizeClientAddress);
    cout << "[NOW] accept()\n";

    if(clientSocket == INVALID_SOCKET)
        ShowErrorMessage("accept()");
    while(1){
        int length = recv(clientSocket, received, sizeof(received), 0);
        received[length] = '\0'; // 마지막 문자를 잘라냄
        cout << "[CLIENT MESSAGE]: " << received << '\n';
        cout << "[MESSAGE SEND]: " << received << '\n';
        if(strcmp(received, "[exit]") == 0){
            send(clientSocket, received, sizeof(received) - 1, 0); // 마지막 엔터를 제거하기 위해서 -1을 해줌
            cout << "[SERVER EXIT]\n";
            break;
        }
        send(clientSocket, received, sizeof(received) - 1, 0);
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    system("pause");
    return 0;
}

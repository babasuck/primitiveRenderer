#include "networkContext.h"
#include <windows.h>


typedef struct NetworkContext {
    SOCKET sock;
    WSADATA wsaData;
} NetworkContext;

typedef struct ClientInfo {
    SOCKET sock;
    char** tokens;
} ClientInfo;


ClientInfo* ClientInfo_ctr(SOCKET sock) {
    ClientInfo* client = (ClientInfo*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(ClientInfo));
    client->sock = sock;
    return client;
}

void ClientInfo_dtor(ClientInfo* client) {
    for (int i = 0; i < 5; i++) {
        free(client->tokens[i]);
    }
    free(client->tokens);
    free(client);
}


NetworkContext* Network_ctr(const char* ip, unsigned short port) {
    WSADATA wsdata;
    WSAStartup(MAKEWORD(2, 2), &wsdata);
    NetworkContext* net = (NetworkContext*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*net));
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);
    SOCKADDR_IN addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.S_un.S_addr = inet_addr(ip);
    bind(sock, (SOCKADDR*)&addr, sizeof(addr));
    net->sock = sock;
    net->wsaData = wsdata;
    return net;
}

void Network_startListening(NetworkContext* net) {
    listen(net->sock, 5);
}

char** ClientInfo_getClientInfo(ClientInfo* net) { 
    u_long mode = 0;
    ioctlsocket(net->sock, FIONBIO, &mode);
    char buffer[255];
    char* tok;
    char** tokens = calloc(5, sizeof(char*));
    recv(net->sock, buffer, 255, 0);
    tok = strtok(buffer, ":");
    tokens[0] = calloc(strlen(tok), sizeof(*tok));
    strcpy(tokens[0], tok);
    for(int i = 1; i < 5; i++) {
        tok = strtok(NULL, ":");
        tokens[i] = calloc(strlen(tok), sizeof(*tok));
        strcpy(tokens[i], tok);
    }
    closesocket(net->sock);
    net->tokens = tokens;
    return tokens;
}

ClientInfo* Network_acceptConnection(NetworkContext* net) {
    SOCKADDR_IN addr = {0};
    SOCKET client;
    if((client = accept(net->sock, 0, 0)) != INVALID_SOCKET) 
        return ClientInfo_ctr(client);
    return 0;
}
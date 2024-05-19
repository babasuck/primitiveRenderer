#pragma once
#include <winsock2.h>


typedef struct NetworkContext NetworkContext;
typedef struct ClientInfo ClientInfo;


NetworkContext* Network_ctr(const char* ip, unsigned short port);

ClientInfo* ClientInfo_ctr(SOCKET socket);
void ClientInfo_dtor(ClientInfo* client);

void Network_startListening(NetworkContext* net);

ClientInfo* Network_acceptConnection(NetworkContext* net);

char** ClientInfo_getClientInfo(ClientInfo* net);
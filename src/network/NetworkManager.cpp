//
// Created by zakrent on 9/28/17.
//
#include <SDL_net.h>
#include "NetworkManager.h"

namespace network {
    NetworkManager::NetworkManager() {
        consoleLog::logMessage(consoleLog::logLevel::info, "Initializing network manager...");
        IPaddress localAddress;
        if(SDLNet_ResolveHost(&localAddress, NULL, 1234) < 0){
            consoleLog::logMessage(consoleLog::logLevel::error, "Error resolving host!");
            std::abort();
        }
        serverTcpsock = SDLNet_TCP_Open(&localAddress);
        if(!serverTcpsock){
            consoleLog::logMessage(consoleLog::logLevel::error, "Couldn't open TCP socket!");
            std::abort();
        }
        socketSet=SDLNet_AllocSocketSet(16);

    }

    void NetworkManager::checkForIncomingConnections(){
        if(0 < SDLNet_CheckSockets(socketSet, 10)){
            if(SDLNet_SocketReady(serverTcpsock)){
                TCPsocket client;
                client = SDLNet_TCP_Accept(serverTcpsock);
                if(client){
                    Client clientStruct(client, SDL_GetTicks());

                    IPaddress* clientAddr = SDLNet_TCP_GetPeerAddress(client);
                    char logMessage[20];
                    snprintf(logMessage, 20, "Connection from %u", SDLNet_Read32(clientAddr->host));
                    consoleLog::logMessage(consoleLog::logLevel::info ,logMessage);

                    addClient(clientStruct);
                }
            }
        }
    }

    void NetworkManager::addClient(Client client) {
        SDLNet_TCP_AddSocket(socketSet, client.socket);
        clients.push_back(client);
    }

    void NetworkManager::updateClientState() {
        char buffer[1000];
        for(Client& client : clients){
            strncpy(buffer, "", 1000);
            currentGameState.serialize(buffer, client.clientGameState);
            SDLNet_TCP_Send(client.socket, buffer, (int)strlen(buffer));
        }
    }
}

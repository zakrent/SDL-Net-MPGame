//
// Created by zakrent on 9/28/17.
//
#include <SDL_net.h>
#include "NetworkManager.h"
#include "states/events/HeartBeatEvent.h"
#include "states/events/ControlEvent.h"

namespace network {
    NetworkManager::NetworkManager(Uint16 port) {
        consoleLog::logMessage(consoleLog::logLevel::info, "Initializing network manager...");
        IPaddress localAddress{};
        if(SDLNet_ResolveHost(&localAddress, nullptr, port) < 0){
            consoleLog::logMessage(consoleLog::logLevel::error, "Error resolving host!");
            std::abort();
        }
        serverTcpsock = SDLNet_TCP_Open(&localAddress);
        if(!serverTcpsock){
            consoleLog::logMessage(consoleLog::logLevel::error, "Couldn't open TCP socket!");
            std::abort();
        }
        socketSet=SDLNet_AllocSocketSet(16);
        SDLNet_TCP_AddSocket(socketSet,serverTcpsock);
    }

    void NetworkManager::checkForIncomingTraffic(){
        if(0 < SDLNet_CheckSockets(socketSet, 10)){
            if(SDLNet_SocketReady(serverTcpsock)){
                TCPsocket client;
                client = SDLNet_TCP_Accept(serverTcpsock);
                if(client){
                    NetworkClient clientStruct(client, SDL_GetTicks());

                    IPaddress* clientAddr = SDLNet_TCP_GetPeerAddress(client);
                    char logMessage[50];
                    Uint32 ipAddress = SDLNet_Read32(&clientAddr->host);
                    snprintf(logMessage, 50, "Connection from %u.%u.%u.%u", ((ipAddress & 0xff000000) >> 24), ((ipAddress & 0x00ff0000) >> 16), ((ipAddress & 0x0000ff00) >> 8), (ipAddress & 0x000000ff));
                    consoleLog::logMessage(consoleLog::logLevel::info ,logMessage);

                    addClient(clientStruct);
                }
            }
            for(NetworkClient& client : clients){
                client.events.clear();
                int counter = 0;
                while(SDLNet_SocketReady(client.socket) && counter < 10) {
                    EventState eventState(client.socket);
                    client.events.push_back(eventState);
                    int result = SDLNet_CheckSockets(socketSet, 0);
                    if(result < 1){
                        break;
                    }
                    counter++;
                }
            }
        }
    }

    void NetworkManager::addClient(NetworkClient client) {
        SDLNet_TCP_AddSocket(socketSet, client.socket);
        clients.push_back(client);
    }

    void NetworkManager::updateClientState() {
        char buffer[1000];
        for(int i = 0; i < clients.size(); i++){
            NetworkClient client = clients[i];
            strncpy(buffer, "", 1000);
            int length = currentGameState.serialize(buffer, client.clientGameState);
            int result = SDLNet_TCP_Send(client.socket, buffer, length);
            int test = (SDL_GetTicks() - client.timeout);
            if(result < length || (test > 2000) ){
                char logMessage[50];
                IPaddress* clientAddr = SDLNet_TCP_GetPeerAddress(client.socket);
                Uint32 ipAddress = SDLNet_Read32(clientAddr);
                snprintf(logMessage, 50, "%u.%u.%u.%u timed out", ((ipAddress & 0xff000000) >> 24), ((ipAddress & 0x00ff0000) >> 16), ((ipAddress & 0x0000ff00) >> 8), (ipAddress & 0x000000ff));
                consoleLog::logMessage(consoleLog::logLevel::info ,logMessage);

                SDLNet_TCP_DelSocket(socketSet, client.socket);
                clients.erase(clients.begin()+i);
            }
            else {
                clients[i].clientGameState = currentGameState;
            }
        }
    }

    void NetworkManager::generateCurrentGameState(std::vector<entity::BaseEntity*> entities) {
        GameState newGameState;
        for(entity::BaseEntity* entity : entities){
            newGameState.addEntityState(entity->generateEntityState());
        }
        currentGameState = newGameState;
    }
}

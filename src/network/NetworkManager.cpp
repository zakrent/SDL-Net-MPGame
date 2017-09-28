//
// Created by zakrent on 9/28/17.
//
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
}

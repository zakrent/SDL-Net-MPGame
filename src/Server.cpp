//
// Created by zakrent on 11/10/17.
//

#include "Server.h"
#include "math/physics.h"

Server::Server(Uint16 port) : networkManager(port) {
    consoleLog::logMessage(consoleLog::logLevel::info, "Server started");
    entities.push_back(new entity::BaseEntity(math::Vector2(0,500), math::Vector2(5,0), SDL_Rect{0,0,24,24}));
    entities.push_back(new entity::BaseEntity(math::Vector2(10,10), math::Vector2(1,0), SDL_Rect{0,0,24,24}));
}

Server::~Server() {
    consoleLog::logMessage(consoleLog::logLevel::info, "Server shutting down...");

    for (auto &entity : entities) {
        delete entity;
    }
}


void Server::update() {
    networkManager.checkForIncomingTraffic();

    for(int i = 0; i < entities.size(); i++){
        if(entities[i]->shouldBeDestroyed){
            delete entities[i];
            entities.erase(entities.begin()+i);
        }
        entities[i]->update();
        for(int j = i+1; j < entities.size(); j++){
            /*if(math::checkCollision(*entities[i], *entities[j])){
                entities[i]->handleCollision();
                entities[j]->handleCollision();
            }*/
        }
    }

    networkManager.generateCurrentGameState(entities);
    networkManager.updateClientState();
}

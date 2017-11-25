//
// Created by zakrent on 11/10/17.
//

#include "Server.h"
#include "math/physics.h"
#include "entity/PlayerEntity.h"
#include "network/states/events/ControlEvent.h"

Server::Server(Uint16 port) : networkManager(port) {
    consoleLog::logMessage(consoleLog::logLevel::info, "Server started");
}

Server::~Server() {
    consoleLog::logMessage(consoleLog::logLevel::info, "Server shutting down...");

    for (auto &entity : entities) {
        delete entity;
    }
}

entity::BaseEntity *Server::getEntityWithId(uint32 id) {
    for(auto entity : entities){
        if(entity->getID() == id)
            return entity;
    }
    return nullptr;
}

void Server::update() {
    networkManager.checkForIncomingTraffic();

    for(network::NetworkClient& client : networkManager.clients){
        entity::BaseEntity* entity = getEntityWithId(client.playerEntityID);
        if(!entity){
            entities.push_back(new entity::PlayerEntity(math::Vector2(50,50), math::Vector2(0,0), SDL_Rect{0,0,24,24}));
            entity = entities.back();
        }
        entity->active = true;
        for(network::EventState& eventState : client.events){
            switch(eventState.eventType){
                case 1: {
                    client.timeout = SDL_GetTicks();
                    break;
                }
                case 2: {
                    network::ControlEvent event(eventState.eventData);

                    bool wKey = (event.controls & 0x1) != 0;
                    bool sKey = (event.controls & 0x2) != 0;
                    bool dKey = (event.controls & 0x4) != 0;
                    bool aKey = (event.controls & 0x8) != 0;

                    float targetXVel = dKey - aKey;
                    float targetYVel = sKey - wKey;

                    math::Vector2 targetVelocity(targetXVel, targetYVel);
                    entity->setVelocity(targetVelocity);
                    break;
                }
                default:
                    break;
            }
        }

    }

    for(int i = 0; i < entities.size(); i++){
        if(entities[i]->shouldBeDestroyed){
            delete entities[i];
            entities.erase(entities.begin()+i);
            continue;
        }
        entities[i]->update();
        for(int j = i+1; j < entities.size(); j++){
            if(math::checkCollision(*entities[i], *entities[j])){
                entities[i]->handleCollision();
                entities[j]->handleCollision();
            }
        }
        if(!entities[i]->active)
            entities[i]->shouldBeDestroyed = true;
        entities[i]->active = false;
    }

    networkManager.generateCurrentGameState(entities);
    networkManager.updateClientState();
}
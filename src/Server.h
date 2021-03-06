//
// Created by zakrent on 11/10/17.
//

#ifndef GAME_MP_SERVER_SERVER_H
#define GAME_MP_SERVER_SERVER_H


#include <vector>
#include "entity/BaseEntity.h"
#include "network/NetworkManager.h"

class Server {
private:
    network::NetworkManager networkManager;
    std::vector<entity::BaseEntity*> entities;
    entity::BaseEntity* getEntityWithId(uint32 id);
public:
    void update();

    explicit Server(Uint16 port);
    ~Server();
};


#endif //GAME_MP_SERVER_SERVER_H

//
// Created by zakrent on 10/1/17.
//

#ifndef GAME_MP_SERVER_BASE_H
#define GAME_MP_SERVER_BASE_H
namespace network {
    class BaseMessage {
        virtual void serialize(char* buffer){};

    public:
        BaseMessage(){};
    };
}

#endif //GAME_MP_SERVER_BASE_H

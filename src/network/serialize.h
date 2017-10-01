//
// Created by zakrent on 10/1/17.
//

#ifndef GAME_MP_SERVER_SERIALIZE_H
#define GAME_MP_SERVER_SERIALIZE_H

#include "../misc/types.h"

namespace network {
    void serializeUInt64(char *buffer, uint64 value);
    void serializeInt(char *buffer, int value);
    void serializeDouble(char *buffer, double value);

    uint64 unserializeUInt64(char *data);
    int unserializeInt(char *data);
    double unserializeDouble(char *data);
}

#endif //GAME_MP_SERVER_SERIALIZE_H

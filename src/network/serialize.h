//
// Created by zakrent on 10/1/17.
//

#ifndef GAME_MP_SERVER_SERIALIZE_H
#define GAME_MP_SERVER_SERIALIZE_H

#include "../misc/types.h"
#include "../math/Vector2.h"

namespace network {
    void serializeUInt64(char *buffer, uint64 value);
    void serializeUInt32(char *buffer, uint32 value);
    void serializeUInt8(char *buffer, uint8 value);
    void serializeInt(char *buffer, int value);
    void serializeDouble(char *buffer, double value);
    void serializeVector(char *buffer, math::Vector2 value);

    uint64 unserializeUInt64(char *data);
    uint32 unserializeUInt32(char *data);
    uint8 unserializeUInt8(char *data);
    int unserializeInt(char *data);
    double unserializeDouble(char *data);
    math::Vector2 unserializeVector(char *data);
}

#endif //GAME_MP_SERVER_SERIALIZE_H

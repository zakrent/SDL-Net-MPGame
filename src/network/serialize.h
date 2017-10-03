//
// Created by zakrent on 10/1/17.
//

#ifndef GAME_MP_SERVER_SERIALIZE_H
#define GAME_MP_SERVER_SERIALIZE_H

#include "../misc/types.h"
#include "../math/Vector2.h"

namespace network {
    void serializeUInt32(char *buffer, uint32 value);
    void serializeUInt16(char *buffer, uint16 value);
    void serializeDouble(char *buffer, double value);
    void serializeVector(char *buffer, math::Vector2 value);

    uint32 unserializeUInt32(char *data);
    uint16 unserializeUInt16(char *data);
    double unserializeDouble(char *data);
    math::Vector2 unserializeVector(char *data);

    uint32 htonf(float f);
    float ntohf(uint32_t p);
}

#endif //GAME_MP_SERVER_SERIALIZE_H

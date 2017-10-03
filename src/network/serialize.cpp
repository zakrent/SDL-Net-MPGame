//
// Created by zakrent on 10/1/17.
//

//serialization

#include <SDL_net.h>
#include "serialize.h"
#include "../misc/types.h"
namespace network {
    void serializeUInt32(char *buffer, uint32 value) {
        SDLNet_Write32(value, buffer);
    }
    void serializeUInt16(char *buffer, uint16 value) {
        SDLNet_Write16(value, buffer);
    }

    uint32 unserializeUInt32(char *data) {
        return SDLNet_Read32(data);
    }
    uint16 unserializeUInt16(char *data) {
        return SDLNet_Read16(data);
    }


    void serializeDouble(char *buffer, double value) {
        serializeUInt32(buffer, htonf((float)value));
    }

    void serializeVector(char *buffer, math::Vector2 value) {
        serializeDouble(buffer, (double)value.x);
        serializeDouble(buffer+4, (double)value.y);
    }

    double unserializeDouble(char *data) {
        return ntohf(unserializeUInt32(data));
    }

    math::Vector2 unserializeVector(char *data) {
        math::Vector2 result(0,0);
        result.x = unserializeDouble(data);
        result.y = unserializeDouble(data+4);
        return result;
    }

    //Copied from https://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#serialization
    uint32 htonf(float f)
    {
        uint32_t p;
        uint32_t sign;

        if (f < 0) { sign = 1; f = -f; }
        else { sign = 0; }

        p = ((((uint32_t)f)&0x7fff)<<16) | (sign<<31); // whole part and sign
        p |= (uint32_t)(((f - (int)f) * 65536.0f))&0xffff; // fraction

        return p;
    }

    //Copied from https://beej.us/guide/bgnet/output/html/singlepage/bgnet.html#serialization
    float ntohf(uint32_t p)
    {
        float f = ((p>>16)&0x7fff); // whole part
        f += (p&0xffff) / 65536.0f; // fraction

        if (((p>>31)&0x1) == 0x1) { f = -f; } // sign bit set

        return f;
    }
}

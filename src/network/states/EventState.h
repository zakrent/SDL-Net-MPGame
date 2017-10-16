//
// Created by zakrent on 10/8/17.
//

#ifndef GAME_MP_SERVER_EVENTSTATE_H
#define GAME_MP_SERVER_EVENTSTATE_H

#include "../../misc/types.h"
#include "../serialize.h"

namespace network {
    struct EventState{
        uint32 eventType;

        int serialize(char* buffer){
            int offset = 0;
            serializeUInt32(buffer, eventType);
            offset += 4;
            return offset;
        }
        EventState(uint32 eventType) : eventType(eventType){}
        EventState(char* buffer){
            eventType = unserializeUInt32(buffer);
        }
    };
}

#endif //GAME_MP_SERVER_EVENTSTATE_H

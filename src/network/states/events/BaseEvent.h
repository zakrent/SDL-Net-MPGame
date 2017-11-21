//
// Created by zakrent on 11/17/17.
//

#ifndef GAME_MP_SERVER_BASEEVENT_H
#define GAME_MP_SERVER_BASEEVENT_H

#include "../../../misc/types.h"
#include "../../serialize.h"

namespace network{
    struct BaseEvent{
        const uint32 eventType;

        virtual int serialize(char* buffer) = 0;

        BaseEvent(uint32 _eventType) : eventType(_eventType){};
        BaseEvent(char* data) : eventType(unserializeUInt32(data)){};
    };
}
#endif //GAME_MP_SERVER_BASEEVENT_H

//
// Created by zakrent on 11/17/17.
//

#ifndef GAME_MP_SERVER_HEARTBEATEVENT_H
#define GAME_MP_SERVER_HEARTBEATEVENT_H

#include "BaseEvent.h"

namespace network{
    struct HeartBeatEvent : public BaseEvent{

        uint32 timeStamp;

        int serialize(char* buffer) override {
            int offset = 0;
            serializeUInt32(buffer+offset, eventType);
            offset += 4;
            serializeUInt32(buffer+offset, timeStamp);
            offset += 4;
            return offset;
        }

        HeartBeatEvent() : BaseEvent(1), timeStamp(SDL_GetTicks()){}
        HeartBeatEvent(char* data) : BaseEvent(unserializeUInt32(data)), timeStamp(unserializeUInt32(data+5)) {};
    };
}

#endif //GAME_MP_SERVER_HEARTBEATEVENT_H

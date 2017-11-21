//
// Created by zakrent on 10/8/17.
//

#ifndef GAME_MP_SERVER_EVENTSTATE_H
#define GAME_MP_SERVER_EVENTSTATE_H

#include "../../misc/types.h"
#include "../serialize.h"
#include "events/BaseEvent.h"

namespace network {
    struct EventState{
        uint32 eventType;

        char eventData[20];

        template<typename T>
        T getEvent(){
            T event(eventData);
            return event;
        }

        int getDataSize(){
            switch(eventType){
                case 0:
                    return 4;
                case 1:
                case 2:
                    return 8;
                default:
                    return 0;
            }
        }

        int serialize(char* buffer){
            memcpy(buffer, eventData, static_cast<size_t>(getDataSize()));
            return getDataSize();
        }

        EventState(BaseEvent& baseEvent){
            eventType = baseEvent.eventType;
            baseEvent.serialize(eventData);
        }

        EventState(TCPsocket tcpsock){
            int offset = 0;
            char buffer[20];
            strncpy(buffer, "", 20);
            SDLNet_TCP_Recv(tcpsock, buffer+offset, 4);
            offset += 4;
            eventType = unserializeUInt32(buffer);
            int size = getDataSize();
            if(size-offset > 0)
                SDLNet_TCP_Recv(tcpsock, buffer+offset, size-offset);
            memcpy(eventData, buffer, 20);
        }
    };
}

#endif //GAME_MP_SERVER_EVENTSTATE_H

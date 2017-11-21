//
// Created by zakrent on 11/21/17.
//

#ifndef GAME_MP_SERVER_CONTROLEVENT_H
#define GAME_MP_SERVER_CONTROLEVENT_H

#include <SDL_types.h>
#include <SDL_system.h>
#include "BaseEvent.h"

namespace network{
    struct ControlEvent : public BaseEvent{
        Uint32 controls;

        int serialize(char* buffer) override {
            int offset = 0;
            serializeUInt32(buffer+offset, eventType);
            offset += 4;
            serializeUInt32(buffer+offset, controls);
            offset += 4;
            return offset;
        }

        ControlEvent() : BaseEvent(2){
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            controls = 0;
            controls |= state[SDL_SCANCODE_W] ? 0x1 : 0x0;
            controls |= state[SDL_SCANCODE_S] ? 0x2 : 0x0;
            controls |= state[SDL_SCANCODE_D] ? 0x4 : 0x0;
            controls |= state[SDL_SCANCODE_A] ? 0x8 : 0x0;
        }
        explicit ControlEvent(char* data) : BaseEvent(unserializeUInt32(data)), controls(unserializeUInt32(data+4)) {};
    };
}

#endif //GAME_MP_SERVER_CONTROLEVENT_H

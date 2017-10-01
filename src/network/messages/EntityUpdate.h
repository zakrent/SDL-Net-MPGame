//
// Created by zakrent on 10/1/17.
//

#ifndef GAME_MP_SERVER_ENTITYUPDATE_H
#define GAME_MP_SERVER_ENTITYUPDATE_H

#include <SDL_video.h>
#include "Base.h"
#include "../../misc/types.h"
#include "../../math/Vector2.h"
#include "../../entity/entityTypeEnum.h"
#include "messageTypeEnum.h"
#include "../serialize.h"

namespace network{
    class EntityUpdateMessage : public BaseMessage{
        entity::entityType type;
        uint64 id;
        math::Vector2 position;
        math::Vector2 velocity;
        SDL_Rect srcrect;
        bool shouldBeDestroyed;

        void serialize(char* buffer) {
            char serializedData[100];
            serializedData[0] = messageType::EntityUpdateMessageType;
            serializeUInt64(serializedData+1, type);
            serializeUInt64(serializedData+10, id);
            serializeDouble(serializedData+19, position.x);
            serializeDouble(serializedData+28, position.y);
            serializeDouble(serializedData+37, velocity.x);
            serializeDouble(serializedData+46, velocity.y);
            serializeInt(serializedData+55, srcrect.x);
            serializeInt(serializedData+60, srcrect.y);
            serializeInt(serializedData+65, srcrect.w);
            serializeInt(serializedData+70, srcrect.h);
            serializeInt(serializedData+75, (int)shouldBeDestroyed);
            strcpy(buffer, serializedData);
        }

    public:
        EntityUpdateMessage() : position(0,0), velocity(0,0){};
    };
}

#endif //GAME_MP_SERVER_ENTITYUPDATE_H

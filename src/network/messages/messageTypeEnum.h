//
// Created by zakrent on 10/1/17.
//

#ifndef GAME_MP_SERVER_MESSAGETYPEENUM_H
#define GAME_MP_SERVER_MESSAGETYPEENUM_H

#include "Base.h"
#include "EntityUpdate.h"

namespace network{
    enum messageType{
        BaseMessageType,
        EntityUpdateMessageType,
    };
}

#endif //GAME_MP_SERVER_MESSAGETYPEENUM_H

//
// Created by zakrent on 10/1/17.
//

#ifndef GAME_MP_SERVER_GAMESTATE_H
#define GAME_MP_SERVER_GAMESTATE_H

#include <map>
#include "EntityState.h"
#include "../../entity/BaseEntity.h"

namespace network{
    class GameState{
        std::map<uint64 ,EntityState> states;
    public:
        void addEntityState(EntityState state){
            states.insert(std::pair<uint64 ,EntityState>(state.getId(), state));
        }

        void serialize(char* buffer){
            char tempBuffer[100];
            for (auto state : states) {
                strncpy(tempBuffer, "", 100);
                state.second.serialize(tempBuffer, 0xff);
                strncat(buffer, tempBuffer, strlen(tempBuffer)+1);
            }
        }

        int serialize(char* buffer, GameState prevGameState){
            int offset = 0;
            for (auto state : states) {
                auto iter = prevGameState.states.find(state.second.getId());
                if(iter == prevGameState.states.end()){
                    offset += state.second.serialize(buffer+offset, 0xff);
                }else{
                    auto element = *iter;
                    EntityState prevState = element.second;
                    if(state.second.getDelta(prevState))
                        offset += state.second.serialize(buffer+offset, state.second.getDelta(prevState));
                }
            }
            return offset;
        }

    };
}

#endif //GAME_MP_SERVER_GAMESTATE_H

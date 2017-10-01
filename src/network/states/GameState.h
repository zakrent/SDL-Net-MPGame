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

        void serialize(char* buffer, GameState prevGameState){
            char tempBuffer[100];
            for (auto state : states) {
                strncpy(tempBuffer, "", 100);
                auto iter = prevGameState.states.find(state.second.getId());
                if(iter == prevGameState.states.end()){
                    state.second.serialize(tempBuffer, 0xff);
                }else{
                    auto element = *iter;
                    EntityState prevState = element.second;
                    if(state.second.getDelta(prevState))
                        state.second.serialize(tempBuffer, state.second.getDelta(prevState));
                }
                strncat(buffer, tempBuffer, strlen(tempBuffer)+1);
            }
        }

    };
}

#endif //GAME_MP_SERVER_GAMESTATE_H

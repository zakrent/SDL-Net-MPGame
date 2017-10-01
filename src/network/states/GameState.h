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
            for (auto state : states) {
                state.second.serialize(buffer, 0xff);
            }
        }

        void serialize(char* buffer, GameState prevGameState){
            for (auto state : states) {
                auto iter = prevGameState.states.find(state.second.getId());
                if(iter == prevGameState.states.end()){
                    state.second.serialize(buffer, 0xff);
                }else{
                    auto element = *iter;
                    EntityState prevState = element.second;
                    state.second.serialize(buffer, state.second.getDelta(prevState));
                }
            }
        }

    };
}

#endif //GAME_MP_SERVER_GAMESTATE_H

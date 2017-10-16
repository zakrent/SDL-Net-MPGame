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
        std::vector<EntityState> states;
    public:
        void addEntityState(EntityState state){
            states.push_back(state);
        }

        std::vector<EntityState>::iterator getStateWithId(uint64 id){
            for (std::vector<EntityState>::iterator iter = states.begin(); iter != states.end() ; iter++) {
                if(iter->getId() == id)
                    return iter;
            }
            return states.end();
        }

        int serialize(char* buffer, GameState prevGameState){
            int offset = 0;
            for (auto state : states) {
                auto iter = prevGameState.getStateWithId(state.getId());
                if(iter == prevGameState.states.end()){
                    offset += state.serialize(buffer+offset, 0xff);
                }
                else{
                    auto element = *iter;
                    EntityState prevState = element;
                    if(state.getDelta(prevState))
                        offset += state.serialize(buffer+offset, state.getDelta(prevState));
                }
            }
            return offset;
        }
        GameState() : states() {};

    };
}

#endif //GAME_MP_SERVER_GAMESTATE_H

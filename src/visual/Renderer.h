//
// Created by zakrent on 11/11/17.
//

#ifndef GAME_MP_SERVER_RENDERER_H
#define GAME_MP_SERVER_RENDERER_H


#include <SDL_rect.h>
#include <SDL_render.h>
#include <vector>
#include "../math/Vector2.h"
#include "TextureWrapper.h"
#include "../network/states/EntityState.h"

namespace visual {
    class Renderer {
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        TextureWrapper mainTextureSheet;

        void beginRendering();
        void swapBuffers();
        void renderTexture(SDL_Rect srcrect, SDL_Rect dstrect);
        void renderState(network::EntityState);
    public:
        void renderStates(std::vector<network::EntityState>* states);
    public:
        Renderer();
    };
}


#endif //GAME_MP_SERVER_RENDERER_H

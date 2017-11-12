//
// Created by zakrent on 11/11/17.
//

#ifndef GAME_MP_SERVER_TEXTUREWRAPPER_H
#define GAME_MP_SERVER_TEXTUREWRAPPER_H


#include <SDL_render.h>

namespace visual {
    class TextureWrapper {
    private:
        SDL_Texture *texturePointer;
    public:
        SDL_Texture *getTexturePointer();
        void loadFromFile(SDL_Renderer *renderer, char *filePath);
    public:
        TextureWrapper();
        TextureWrapper(SDL_Renderer *renderer, char *filePath);
        ~TextureWrapper();
    };
}


#endif //GAME_MP_SERVER_TEXTUREWRAPPER_H

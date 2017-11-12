//
// Created by zakrent on 11/11/17.
//

#include "Renderer.h"
namespace visual {
    Renderer::Renderer() {
        SDL_CreateWindowAndRenderer(400,400, 0, &window, &renderer);
        beginRendering();
        swapBuffers();
        mainTextureSheet.loadFromFile(renderer, (char*)"textures/EntitySheet.bmp");
    }

    void Renderer::beginRendering() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void Renderer::swapBuffers() {
        SDL_RenderPresent(renderer);
    }

    void Renderer::renderTexture(SDL_Rect srcrect, SDL_Rect dstrect) {
        SDL_RenderCopyEx(renderer,mainTextureSheet.getTexturePointer(),  &srcrect, &dstrect, 0, nullptr, SDL_FLIP_NONE);
    }


    void Renderer::renderState(network::EntityState state) {
        renderTexture(state.getSrcrect(), SDL_Rect{(int)state.getPosition().x, (int)state.getPosition().y, state.getSrcrect().w, state.getSrcrect().h});
    }

    void Renderer::renderStates(std::vector<network::EntityState>* states) {
        beginRendering();
        for (const auto &state : *states) {
            renderState(state);
        }
        swapBuffers();
    }
}
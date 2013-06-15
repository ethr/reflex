#include "SDL.h"
#include "SDL_ttf.h"
#include "Renderer.hpp"

#include <iostream>


static Uint32 time_left(Uint32& next_time) {
    Uint32 now = SDL_GetTicks();
    Uint32 ret = 0;
    if (next_time > now) {
      ret = next_time - now;
    }
    next_time = SDL_GetTicks() + (1000/60);
    return ret;
}

int main(int argc, char *argv[]) {
    int width = 640;
    int height = 480;
 
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    	return 1;
    }
    if (TTF_Init() == -1) {
      printf("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
      return 2;
    }
    atexit(SDL_Quit);

    const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
    if (videoInfo) {
      width = videoInfo->current_w;
      height = videoInfo->current_h;
    }

    SDL_Surface* screen = SDL_SetVideoMode(width, height, 0,
        SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF);
    reflexgame::Renderer renderer(screen);
    reflexgame::GameState gameState(width, height);
 
    if (screen == NULL)
        return 2;

    SDL_ShowCursor(0);
    SDL_WM_GrabInput(SDL_GRAB_ON);

    Uint32 nextTime = 0;
    time_left(nextTime);
    gameState.start();
    while(true) {
        gameState.handleTick();
        if (gameState.gameEnded()) {
          SDL_Event event; 
          while(SDL_PollEvent(&event)) {
            switch(event.type){
              case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                  case SDLK_ESCAPE:
                    return 0;
                    break;
                  default:
                    break;
                }
              case SDL_QUIT:
                return 0;
              default:
                break;
            }
          }
          renderer.drawEndGame(gameState);
        } else {
          SDL_Event event; 
          while(SDL_PollEvent(&event)) {
            switch(event.type){
              case SDL_MOUSEBUTTONDOWN:
                {
                  if (event.button.button == SDL_BUTTON_LEFT) {
                    int x = event.button.x;
                    int y = event.button.y;
                    printf("Click at (%d, %d)\n", x, y);
                    gameState.attackAt(x, y);
                  }
                  break;
                }
              case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                  case SDLK_ESCAPE:
                    return 0;
                    break;
                  default:
                    break;
                }
              case SDL_QUIT:
                return 0;
              default:
                break;
            }
          }
          renderer.draw(gameState);
        }
        SDL_Flip(screen);
        SDL_Delay(time_left(nextTime));
    }
 
    return 0;
}

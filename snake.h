#ifndef SNAKE_H
#define SNAKE_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>

using namespace std;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
             const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const string &WINDOW_TITLE);

void logSDLError(std::ostream& os,
                const std::string &msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

#endif // SNAKE_H

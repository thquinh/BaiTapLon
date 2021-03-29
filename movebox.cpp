#include <iostream>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Box move";

struct Box {
    int x; int y;
    int StepX = 1; int StepY = 0;
    int w; int h;
    Box(int _x = 200, int _y = 200, int _w = 10, int _h = 10){
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }
    void display(SDL_Renderer* renderer) {
        SDL_Rect fill_rec = {x, y, w, h};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &fill_rec);
        SDL_RenderPresent(renderer);
    }
    void move(SDL_Event e) {
        x += StepX;y += StepY;
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym)
            {
            case SDLK_UP :
                {
                    StepY = -1;
                    StepX = 0;
                    break;
                }
            case SDLK_DOWN :
                {
                    StepY = 1;
                    StepX = 0;
                    break;
                }
            case SDLK_LEFT :
                {
                    StepX = -1;
                    StepY = 0;
                    break;
                }
            case SDLK_RIGHT :
                {
                    StepX = 1;
                    StepY = 0;
                    break;
                }
            }
        }
    }
    bool insideFrame(int frameX, int frameY, int frameW, int frameH) {
        return (frameX <= x && frameY <= y && x + w <= frameX + frameW && y + h <= frameY + frameH);
    }
};

void drawframe(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_Rect fill_rect = {128, 100, SCREEN_WIDTH*2 / 3, SCREEN_HEIGHT*2 / 3};
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &fill_rect);
    SDL_RenderPresent(renderer);
}
int SDL_main(int argc, char* argv[])
{
    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    Box box;
    box.display(renderer);
    SDL_Event e;
	bool quit = true;
	while(box.insideFrame(128, 100, SCREEN_WIDTH*2 / 3, SCREEN_HEIGHT*2 / 3)) {
        drawframe(renderer);
        box.move(e);
		box.display(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		SDL_Delay(15);
        if (SDL_PollEvent(&e) == 0) continue;
		if (e.type == SDL_QUIT) break;
	}
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

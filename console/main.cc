#include "../functions/include/broken_line.h"
//
//using namespace std;
using namespace broken_line;
//
//int main() {
//	draw_trapezoid();
//}

#include "../SDL2/include/SDL.h"
#include "../SDL2/include/SDL_timer.h"
#include <cstdio> 

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("Graphics",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1000, 1000, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

    double a[8];
    fstream file;
    file.open("C:\\Users\\79379\\Desktop\\Right_BL\\data_for_BL.txt");
    for (int i = 0;i < 8;++i) {
        file >> a[i];
    }

	int close = 0;

    while (!close) {
        SDL_Event event;
        SDL_RenderDrawLine(renderer, 500, 0, 500, 1000);
        SDL_RenderDrawLine(renderer, 0, 500, 1000, 500);
        SDL_RenderDrawLine(renderer, 980, 490, 1000, 500);
        SDL_RenderDrawLine(renderer, 980, 510, 1000, 500);
        SDL_RenderDrawLine(renderer, 490, 20, 500, 0);
        SDL_RenderDrawLine(renderer, 510, 20, 500, 0);
        for (int i = 0; i <= 1000;i+= 25) {
            SDL_RenderDrawLine(renderer, 0+i, 495, 0+i, 505);
            SDL_RenderDrawLine(renderer, 495, 25+i, 505, 25+i);
        }
        SDL_RenderDrawLine(renderer, 500+a[0]*25, 500 -a[1]*25, 500 +a[2]*25, 500 -a[3]*25);
        SDL_RenderDrawLine(renderer, 500 + a[2] * 25, 500 - a[3] * 25, 500 + a[4] * 25, 500 - a[5] * 25);
        SDL_RenderDrawLine(renderer, 500 + a[4] * 25, 500 - a[5] * 25, 500 + a[6] * 25, 500 - a[7] * 25);
        SDL_RenderDrawLine(renderer, 500 + a[6] * 25, 500 - a[7] * 25, 500 + a[0] * 25, 500 - a[1] * 25);
        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
 
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;
            }
        }
 
        // calculates to 60 fps
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
    }
 
    return 0;
}
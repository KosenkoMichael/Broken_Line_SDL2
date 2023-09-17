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
                                       500, 500, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    double a[8];
    fstream file;
    file.open("C:\\Users\\79379\\Desktop\\Right_BL\\data_for_BL.txt");
    for (int i = 0;i < 8;++i) {
        file >> a[i];
    }

	int close = 0;

    while (!close) {
        SDL_Event event;
        SDL_RenderDrawLine(renderer, 250, 0, 250, 500);
        SDL_RenderDrawLine(renderer, 0, 250, 500, 250);
        for (int i = 0; i <= 500;i+= 25) {
            SDL_RenderDrawLine(renderer, 0+i, 247, 0+i, 253);
            SDL_RenderDrawLine(renderer, 247, 0+i, 253, 0+i);
        }
        SDL_RenderDrawLine(renderer, 250+a[0]*25, 250-a[1]*25, 250+a[2]*25, 250-a[3]*25);
        SDL_RenderDrawLine(renderer, 250 + a[2] * 25, 250 - a[3] * 25, 250 + a[4] * 25, 250 - a[5] * 25);
        SDL_RenderDrawLine(renderer, 250 + a[4] * 25, 250 - a[5] * 25, 250 + a[6] * 25, 250 - a[7] * 25);
        SDL_RenderDrawLine(renderer, 250 + a[6] * 25, 250 - a[7] * 25, 250 + a[0] * 25, 250 - a[1] * 25);
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
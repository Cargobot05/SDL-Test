#include<iostream>
#include<SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;
const int PLAYER_SPEED = 3;

int main(int argc, char *argv[])
{
    SDL_Init( SDL_INIT_EVERYTHING );

    bool running = true;

    SDL_Window *window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Rect r{WIDTH/2, HEIGHT/2, 50, 50};

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

    if (window == NULL)
    {
        std::cout<<"Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    int playerVel_x = 0;
    int playerVel_y = 0;

    SDL_Event userEvent;

    while (running)
    {
        int tickA, tickB, tickDelta;
        tickA = SDL_GetTicks64();
        tickDelta = tickA - tickB;

        if (tickDelta > 1000/71.0)
        {
            //std::cout << "fps: " << 1000/tickDelta << std::endl;

            tickB = tickA;

            const Uint8 *keystates = SDL_GetKeyboardState(NULL);

            if (keystates[SDL_SCANCODE_UP] && !keystates[SDL_SCANCODE_DOWN])
                playerVel_y = -PLAYER_SPEED;
            if (keystates[SDL_SCANCODE_DOWN] && !keystates[SDL_SCANCODE_UP])
                playerVel_y = PLAYER_SPEED;
            if (keystates[SDL_SCANCODE_LEFT] && !keystates[SDL_SCANCODE_RIGHT])
                playerVel_x = -PLAYER_SPEED;
            else if (keystates[SDL_SCANCODE_RIGHT] && !keystates[SDL_SCANCODE_LEFT])
                playerVel_x = PLAYER_SPEED;

            if (SDL_PollEvent(&userEvent))
            {
                if (userEvent.type == SDL_QUIT)
                    running = false;
            }

            r.x += playerVel_x;
            r.y += playerVel_y;

            if (playerVel_x < 0)
                playerVel_x++;
            if (playerVel_x > 0)
                playerVel_x--;

            if (playerVel_y < 0)
                playerVel_y++;
            if (playerVel_y > 0)
                playerVel_y--;
            
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &r);
            //std::cout << r.x << " " << r.y << std::endl;

            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
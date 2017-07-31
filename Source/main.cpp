#include "ttt.h"
#include "additionalfunctions.h"

int main(int argc, char* argv[])
{
    SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");     //Used to allow for debugging in Windows (On CodeBlocks)

    if (init() == false)
    {
        close();
        return 0;
    }

    if (adjust_resolution() < 0)
    {
        close();
        return 0;
    }

    SDL_Event x;

    bool exit = false;

    TTT Game;

    if (Game.menu() == -1)
    {
        close();
        return 0;
    }

    while(!exit)
    {
        if (SDL_PollEvent(&x) != 0)
        {
            if (x.type == SDL_QUIT)
            {
                exit = true;
            }
        }

        if (Game.game_loop() < 0) // In game loop add update wins function
        {
            exit = true;
        }

        else
        {
            if (Game.play_again() < 0)
            {
                exit = true;
            }
        }
    }

    close();

    return 0;
}

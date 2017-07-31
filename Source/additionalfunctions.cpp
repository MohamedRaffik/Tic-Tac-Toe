#include "additionalfunctions.h"

SDL_Window* mWindow = NULL;
SDL_Surface* wSurface = NULL;
SDL_Renderer* wRenderer = NULL;
TTF_Font* font = NULL;

int screenW = 1024;     //Default Resolution ( 1024 * 600 )
int screenH = 600;

Uint32 white;
Uint32 black;

/***************************************************************************
 *  Function is responsible for initializing all SDL Subsystems as well    *
 *  as creating the global renderer and the checking for the font that  |  *
 *  will be used in the program                                         V  *
 ***************************************************************************/

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    if (TTF_Init() < 0)
    {
        return false;
    }

    mWindow = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW, screenH, SDL_WINDOW_SHOWN);

    if (mWindow == NULL)
    {
        return false;
    }

    wSurface = SDL_GetWindowSurface(mWindow);

    SDL_FillRect(wSurface, NULL, SDL_MapRGB(wSurface->format, 0x00, 0x00, 0x00));

    wRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_SOFTWARE);

    if (wRenderer == NULL)
    {
        return false;
    }

    font = TTF_OpenFont("Roboto-Black.ttf", 120);

    if (font == NULL)
    {
        return false;
    }

    white = SDL_MapRGB(wSurface->format, 0xFF, 0xFF, 0xFF);
    black = SDL_MapRGB(wSurface->format, 0x00, 0x00, 0x00);

    SDL_SetRenderDrawColor(wRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_UpdateWindowSurface(mWindow);

    return true;
}


int adjust_resolution()
{
    string resolution[5] = {"800 x 600", "1024 x 600", "1280 x 720", "1366 x 768", "1920 x 1080"};
    string title = "Select the appropriate resolution";
    string apply = "Apply";
    string confirm_text = "Confirm";

    int picked = 1;

    SDL_Event e;

    bool apply_bool;

    int mouseX, mouseY;

    bool confirm = false;

    while (!confirm)
    {
        if (SDL_PollEvent(&e) == 1)
        {
            if (e.type == SDL_QUIT)
            {
                return -1;
            }
        }

        SDL_Rect t = {screenW * 2/10, screenH * 1/10, screenW * 6/10, screenH * 1/10};
        SDL_Rect a = {screenW * 1/10, screenH * 8/10, screenW * 2/10, screenH * 1/10};
        SDL_Rect c = {screenW * 7/10, screenH * 8/10, screenW * 2/10, screenH * 1/10};

        SDL_Rect r1 = {screenW * 4/10, screenH * 3/10, screenW * 2/10, screenH * 1/10};
        SDL_Rect r2 = {screenW * 4/10, screenH * 4/10, screenW * 2/10, screenH * 1/10};
        SDL_Rect r3 = {screenW * 4/10, screenH * 5/10, screenW * 2/10, screenH * 1/10};
        SDL_Rect r4 = {screenW * 4/10, screenH * 6/10, screenW * 2/10, screenH * 1/10};
        SDL_Rect r5 = {screenW * 4/10, screenH * 7/10, screenW * 2/10, screenH * 1/10};


        if (e.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
        }

        Uint32 start = SDL_GetTicks();

        highlight(title.c_str(), false, t);
        highlight(apply.c_str(), false, a);
        highlight(confirm_text.c_str(), false, c);

        if (rect_detection(r1, e, mouseX, mouseY))
        {
            picked = 0;
        }

        if (rect_detection(r2, e, mouseX, mouseY))
        {
            picked = 1;
        }

        if (rect_detection(r3, e, mouseX, mouseY))
        {
            picked = 2;
        }

        if (rect_detection(r4, e, mouseX, mouseY))
        {
            picked = 3;
        }

        if (rect_detection(r5, e, mouseX, mouseY))
        {
            picked = 4;
        }

        if (rect_detection(a, e, mouseX, mouseY))
        {
            apply_bool = true;
        }

        if (rect_detection(c, e, mouseX, mouseY))
        {
            confirm = true;
        }

        if (picked == 0)
        {
            highlight(resolution[0].c_str(), true, r1);
        }

        else
        {
            highlight(resolution[0].c_str(), false, r1);
        }

        if (picked == 1)
        {
            highlight(resolution[1].c_str(), true, r2);
        }

        else
        {
            highlight(resolution[1].c_str(), false, r2);
        }

        if (picked == 2)
        {
            highlight(resolution[2].c_str(), true, r3);
        }

        else
        {
            highlight(resolution[2].c_str(), false, r3);
        }

        if (picked == 3)
        {
            highlight(resolution[3].c_str(), true, r4);
        }

        else
        {
            highlight(resolution[3].c_str(), false, r4);
        }

        if (picked == 4)
        {
            highlight(resolution[4].c_str(), true, r5);
        }

        else
        {
            highlight(resolution[4].c_str(), false, r5);
        }

        if (apply_bool == true)
        {
            if (picked == 0)
            {
                screenW = 800;
                screenH = 600;
            }

            else if (picked == 1)
            {
                screenW = 1024;
                screenH = 600;
            }

            else if (picked == 2)
            {
                screenW = 1280;
                screenH = 720;
            }

            else if (picked == 3)
            {
                screenW = 1366;
                screenH = 768;
            }

            else if (picked == 4)
            {
                screenW = 1920;
                screenH = 1080;
            }

            SDL_DestroyWindow(mWindow);
            init();
            apply_bool = false;
        }

        Uint32 total = SDL_GetTicks();
        fps_cap(start, total);

        SDL_RenderPresent(wRenderer);
    }

    SDL_FillRect(wSurface, NULL, black);

    return 0;
}


/****************************************************************************
 *   Function responsible for delaying loops in order to reduce CPU usage | *
 *   and to produce a render speed of 60 frames per second                V *
 ****************************************************************************/


void fps_cap(Uint32 start, Uint32 total)
{
    int delay = (1000/60) - (total - start);

    if (delay > 0)
    {
        SDL_Delay(delay);
    }
}

void highlight(string text, bool c, SDL_Rect pos)
{
    SDL_Color col_white = {0xFF, 0xFF, 0xFF, 0xFF};
    SDL_Color col_black = {0x00, 0x00, 0x00, 0x00};

    SDL_Surface* text_surface;
    if (c)
    {
        text_surface = TTF_RenderText_Shaded(font, text.c_str(), col_black, col_white);
    }
    else
    {
        text_surface = TTF_RenderText_Shaded(font, text.c_str(), col_white, col_black);
    }

    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(wRenderer, text_surface);
    SDL_RenderCopy(wRenderer, text_texture, NULL, &pos);
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);

    text_surface = NULL;
    text_texture = NULL;
}

void change_fsize(int fsize)
{
    TTF_CloseFont(font);
    font = NULL;
    font = TTF_OpenFont("Roboto-Black.ttf", fsize);
}

string input_text(SDL_Rect rect, int max_length, string old_text)
{
    change_fsize(50);

    string text = old_text;

    int w, h;

    bool allow = true;
    bool quit = false;

    SDL_Event t;

    SDL_StartTextInput();

    while (!quit)
    {
        if (SDL_PollEvent(&t) != 0)
        {
            if (t.type == SDL_QUIT)
            {
                return "Quit";
            }
        }

        const Uint8* key = SDL_GetKeyboardState(NULL);

        Uint32 start = SDL_GetTicks();

        SDL_FillRect(wSurface, &rect, white);

        if (t.type == SDL_TEXTINPUT)
        {
            if (allow)
            {
                text += t.text.text;
                allow = false;
            }
        }

        if (t.key.state == SDL_RELEASED)
        {
            allow = true;
        }

        if ((key[SDL_SCANCODE_BACKSPACE]) && (allow) && (text.length() > 0))
        {
            text.resize(text.length() - 1);
            SDL_FillRect(wSurface, &rect, white);
            allow = false;
        }

        if ((key[SDL_SCANCODE_RETURN]) && (allow))
        {
            SDL_StopTextInput();
            quit = true;
            allow = false;
        }

        if ((signed)text.length() > max_length)
        {
            text.resize(max_length);
        }

        TTF_SizeText(font, text.c_str(), &w, &h);
        SDL_Rect r_text = {rect.x, rect.y, w, rect.h};

        highlight(text, true, r_text);

        Uint32 total = SDL_GetTicks();
        fps_cap(start, total);

        SDL_RenderDrawRect(wRenderer, &rect);
        SDL_RenderPresent(wRenderer);
    }

    SDL_StopTextInput();

    SDL_SetRenderDrawColor(wRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderDrawRect(wRenderer, &rect);
    SDL_SetRenderDrawColor(wRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return text;
}

bool rect_detection(SDL_Rect rect, SDL_Event a, int mouseX, int mouseY)
{
    if ((mouseX >= rect.x) && (mouseX <= rect.x + rect.w) && (mouseY >= rect.y) && (mouseY <= rect.y + rect.h))
    {
        if (a.type == SDL_MOUSEBUTTONDOWN)
        {
            return true;
        }
    }

    return false;
}


/**************************************************************************************
 *   Function is responsible for closing all SDL related functions and destroying  |  *
 *   the window and renderer                                                       V  *
 **************************************************************************************/


void close()
{
    SDL_DestroyRenderer(wRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

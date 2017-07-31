#ifndef additionalfunctions
#define additionalfunctions

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

/***** Global Variables ***********/
extern SDL_Window* mWindow;
extern SDL_Surface* wSurface;
extern SDL_Renderer* wRenderer;
extern TTF_Font* font;

extern int screenW;
extern int screenH;

extern Uint32 white;
extern Uint32 black;

/********** Function Declarations **********/

bool init();

int adjust_resolution();

void highlight(string text, bool c, SDL_Rect pos);

void change_fsize(int fsize);

string input_text(SDL_Rect rect, int max_length, string old_text);

bool rect_detection(SDL_Rect rect, SDL_Event a, int mouseX, int mouseY);

void fps_cap(Uint32 start, Uint32 total); //FPS CAP

void close();

#endif // additionalfunctions


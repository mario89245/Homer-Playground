#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 480; // Temporary setup
const int SCREEN_HEIGHT = 640; // Have program default to fullscreen

bool init(SDL_Window* window, SDL_Surface* windowSurface)
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) //Initialize SDL
    {
        std::cout<<"SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        success = false;
    }
    else
    {
        std::cout<<"SDL initialized! Creating window...\n";
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ); //Create window
        if(window == NULL) 
        {
            std::cout<<"Window could not be created! SDL Error: " << SDL_GetError() << "\n"; 
            success = false;
        }
        else
        {
            windowSurface = SDL_GetWindowSurface(window);
        } 
    }

    return success;
}

bool loadMedia(SDL_Window* window, SDL_Surface* windowSurface, SDL_Surface* homerSpriteSheet) 
{
    bool success = true;

    homerSpriteSheet = SDL_LoadBMP("homerSpriteSheet.bmp");
    if(homerSpriteSheet == NULL)
    {
        std::cout<<"Unable to load image! SDL Error: " << SDL_GetError() << "\n";
        success = false;
    }

    return success;
}

void close(SDL_Window* window) 
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    SDL_Window* window = NULL; // Note: Stop using global variables
    SDL_Surface* windowSurface = NULL;

    SDL_Surface* homerSpriteSheet = NULL; // Currently CPU renders this

    if(!init(window, windowSurface))
    {
        std::cout<<"Failed to Initialize!\n";
    }
    else
    {
        if(!loadMedia(window, windowSurface, homerSpriteSheet))
        {
            std::cout<<"Failed to load media!\n";
        }
        else
        {
            SDL_BlitSurface(homerSpriteSheet, NULL, windowSurface, NULL);
            SDL_UpdateWindowSurface(window);
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; }} // Keep window up unless user quits
                                                                                                                                   // This is not professional (See Events Tutorial)
        }
    }

    SDL_FreeSurface(homerSpriteSheet);
    homerSpriteSheet = NULL;
    close(window);

    return 0;
}
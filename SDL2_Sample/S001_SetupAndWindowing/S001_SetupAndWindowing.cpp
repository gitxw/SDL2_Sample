#include <SDL.h>

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{

    // Pointers to our window and surface
    SDL_Surface* winSurface = NULL;
    SDL_Window* window = NULL;

    // Initialize SDL. SDL_Init will return -1 if it fails.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        system("pause");
        // End the program
        return 1;
    }

    // Create our window
    window = SDL_CreateWindow("Example",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480, SDL_WINDOW_SHOWN);

    // Make sure creating the window succeeded
    if (!window) {
        cout << "Error creating window: " << SDL_GetError() << endl;
        system("pause");
        // End the program
        return 1;
    }

    // Get the surface from the window
    winSurface = SDL_GetWindowSurface(window);

    // Make sure getting the surface succeeded
    if (!winSurface) {
        cout << "Error getting surface: " << SDL_GetError() << endl;
        system("pause");
        // End the program
        return 1;
    }

    // Fill the window with a color rectangle
    SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 90, 120));

    // Update the window display
    SDL_UpdateWindowSurface(window);

    // Wait
    system("pause");

    // Destroy the window. This will also destroy the surface
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    // End the program
    return 0;
}

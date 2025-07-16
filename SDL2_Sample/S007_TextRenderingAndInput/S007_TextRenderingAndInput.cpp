// 为了支持中文，本代码要使用utf-8编码

#include <Windows.h>
#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

bool init();
void kill();
bool loop();
std::wstring UTF8_To_UTF16(const std::string& source);
std::string UTF16_To_UTF8(const std::wstring& source);

// Pointers to our window, renderer, texture, and font
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture *texture, *text;
TTF_Font* font;
string input;

int main(int argc, char** args)
{
    if (!init()) {
        system("pause");
        return 1;
    }

    while (loop()) {
        // wait before processing the next frame
        SDL_Delay(10);
    }

    kill();
    return 0;
}

bool loop()
{
    static const unsigned char* keys = SDL_GetKeyboardState(NULL);

    SDL_Event e;
    SDL_Rect dest;

    // Clear the window to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Event loop
    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
        case SDL_QUIT:
            return false;
        case SDL_TEXTINPUT:
            input += e.text.text;
            break;
        case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_BACKSPACE && input.size()) {
                // 删除中文字符时，可以整个字删除
                wstring input_u16 = UTF8_To_UTF16(input);
                input_u16.pop_back();
                input = UTF16_To_UTF8(input_u16);
            }
            break;
        }
    }

    // Render texture
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_Color foreground = { 0, 0, 0 };

    if (input.size()) {
        SDL_Surface* text_surf = TTF_RenderUTF8_Blended(font, input.c_str(), foreground); // 此函数支持中文
        text = SDL_CreateTextureFromSurface(renderer, text_surf);

        dest.x = static_cast<int>(320 - (text_surf->w / 2.0f));
        dest.y = 240;
        dest.w = text_surf->w;
        dest.h = text_surf->h;
        SDL_RenderCopy(renderer, text, NULL, &dest);

        SDL_DestroyTexture(text);
        SDL_FreeSurface(text_surf);
    }

    // Update window
    SDL_RenderPresent(renderer);

    return true;
}

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        cout << "Error initializing SDL_image: " << IMG_GetError() << endl;
        return false;
    }

    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        cout << "Error intializing SDL_ttf: " << TTF_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow("Example",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Error creating window: " << SDL_GetError() << endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "Error creating renderer: " << SDL_GetError() << endl;
        return false;
    }

    SDL_Surface* buffer = IMG_Load("test.png");
    if (!buffer) {
        cout << "Error loading image test.png: " << SDL_GetError() << endl;
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, buffer);
    SDL_FreeSurface(buffer);
    buffer = NULL;
    if (!texture) {
        cout << "Error creating texture: " << SDL_GetError() << endl;
        return false;
    }

    // Load font
    font = TTF_OpenFont("msyh.ttc", 72); // 微软雅黑字体，支持中文
    if (!font) {
        cout << "Error loading font: " << TTF_GetError() << endl;
        return false;
    }

    // Start sending SDL_TextInput events
    SDL_StartTextInput();

    return true;
}

void kill()
{
    SDL_StopTextInput();

    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
    texture = NULL;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

std::wstring UTF8_To_UTF16(const std::string& source)
{
    unsigned long len = ::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, NULL, NULL);
    if (len == 0)
        return std::wstring();
    wchar_t* buffer = new wchar_t[len];
    ::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, buffer, len);

    std::wstring dest(buffer);
    delete[] buffer;
    return dest;
}

std::string UTF16_To_UTF8(const std::wstring& source)
{
    unsigned long len = ::WideCharToMultiByte(CP_UTF8, NULL, source.c_str(), -1, NULL, NULL, NULL, NULL);
    if (len == 0)
        return std::string();
    char* buffer = new char[len];
    ::WideCharToMultiByte(CP_UTF8, NULL, source.c_str(), -1, buffer, len, NULL, NULL);

    std::string dest(buffer);
    delete[] buffer;
    return dest;
}

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;

bool init();
void kill();
bool loop();

// Pointers to our window, renderer, texture, music, sound and ttf
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* bg_img_texture;
Mix_Music* music;
Mix_Chunk* sound;

TTF_Font* font; // 字体
SDL_Texture* ttf_texture; // 字体纹理
SDL_Rect ttf_rect; // 字体位置

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

    // Clear the window to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Event loop
    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
        case SDL_QUIT:
            return false;
        case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_SPACE) {
                if (Mix_PausedMusic() == 1) {
                    Mix_ResumeMusic();
                } else {
                    Mix_PauseMusic();
                }
            } else if (e.key.keysym.sym == SDLK_ESCAPE) {
                Mix_HaltMusic();
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            // Play sound once on the first available channel
            Mix_PlayChannel(-1, sound, 0);
            break;
        }
    }

    // Render bg_img_texture
    SDL_RenderCopy(renderer, bg_img_texture, NULL, NULL);

    // 绘制ttf纹理
    SDL_RenderCopy(renderer, ttf_texture, NULL, &ttf_rect);

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

    // Initialize SDL_image with PNG loading subsystem
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        cout << "Error initializing SDL_image: " << IMG_GetError() << endl;
        system("pause");
        return false;
    }

    // Initialize SDL_mixer with our audio format
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        cout << "Error initializing SDL_mixer: " << Mix_GetError() << endl;
        return false;
    }

    // 初始化 SDL_ttf
    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not initialize: " << TTF_GetError() << endl;
        system("pause");
        return false;
    }

    // 创建窗口
    window = SDL_CreateWindow("Example",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Error creating window: " << SDL_GetError() << endl;
        return false;
    }

    // 创建渲染器
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "Error creating renderer: " << SDL_GetError() << endl;
        return false;
    }

    // Load image (PNG) into surface
    SDL_Surface* buffer = IMG_Load("test.png");
    if (!buffer) {
        cout << "Error loading image test.png: " << SDL_GetError() << endl;
        return false;
    }

    // Create bg_img_texture
    bg_img_texture = SDL_CreateTextureFromSurface(renderer, buffer);
    // Free surface as it's no longer needed
    SDL_FreeSurface(buffer);
    buffer = NULL;
    if (!bg_img_texture) {
        cout << "Error creating bg_img_texture: " << SDL_GetError() << endl;
        return false;
    }

    // Load music
    music = Mix_LoadMUS("music.wav");
    if (!music) {
        cout << "Error loading music: " << Mix_GetError() << endl;
        return false;
    }

    // Load sound
    sound = Mix_LoadWAV("scratch.wav");
    if (!sound) {
        cout << "Error loading sound: " << Mix_GetError() << endl;
        return false;
    }

    // Play music forever
    Mix_PlayMusic(music, -1);

    // 加载字体 - 替换为你的中文字体文件路径
    const char* FONT_PATH = "STCAIYUN.TTF"; // 华文彩云，支持中文
    const int FONT_SIZE = 72;
    font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (!font) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
        return false;
    }
    // 设置字体样式
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    TTF_SetFontOutline(font, 1); // 设置1像素轮廓
    // 创建文字表面
    SDL_Color font_color = { 255, 0, 255, 255 }; // RGBA紫色
    SDL_Surface* blendedSurface = TTF_RenderUTF8_Blended(font, "~ ABC主菜单 ~", font_color);
    if (!blendedSurface) {
        cout << "Failed to create blended text surface: " << TTF_GetError() << endl;
        return false;
    }
    // 创建字体纹理
    ttf_texture = SDL_CreateTextureFromSurface(renderer, blendedSurface);
    if (!ttf_texture) {
        cout << "Failed to create blended texture: " << TTF_GetError() << endl;
        return false;
    }
    // 设置文本位置
    ttf_rect = { 50, 50, blendedSurface->w, blendedSurface->h };
    // 释放表面（不再需要）
    SDL_FreeSurface(blendedSurface);

    return true;
}

void kill()
{
    // 销毁字体相关资源
    SDL_DestroyTexture(ttf_texture);
    TTF_CloseFont(font);

    // 销毁背景图像相关资源
    SDL_DestroyTexture(bg_img_texture);
    bg_img_texture = NULL;

    // 销毁声音相关资源
    Mix_FreeMusic(music);
    Mix_FreeChunk(sound);
    music = NULL;
    sound = NULL;

    // 销毁窗体相关资源
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

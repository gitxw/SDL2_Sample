#include <iostream>
#include <string>
#include <time.h>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

// Gravity in pixels per second squared
const float GRAVITY = 750.0f;

bool init();
void kill();
void loop();
void renderText(string text, SDL_Rect dest);

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* box;
TTF_Font* font;

struct square {
    float x, y, w, h, xvelocity, yvelocity;
    Uint32 born, lastUpdate;
};

int main(int argc, char** args)
{
    if (!init()) {
        system("pause");
        return 1;
    }

    loop();

    kill();
    return 0;
}

void loop()
{
    srand(static_cast<unsigned int>(time(NULL)));

    // Physics squares
    vector<square> squares;

    bool running = true;
    Uint32 totalFrameTicks = 0;
    Uint32 totalFrames = 0;
    while (running) {
        // Start frame timing
        totalFrames++;
        Uint32 startTicks = SDL_GetTicks();
        Uint64 startPerf = SDL_GetPerformanceCounter();

        SDL_Event e;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Event loop
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                for (int i = 0; i < 3; i++) {
                    square s;
                    s.x = static_cast<float>(e.button.x);
                    s.y = static_cast<float>(e.button.y);
                    s.w = static_cast<float>(rand() % 50 + 25);
                    s.h = static_cast<float>(rand() % 50 + 25);
                    s.yvelocity = -500.0f;
                    s.xvelocity = static_cast<float>(rand() % 500 - 250);
                    s.lastUpdate = SDL_GetTicks();
                    s.born = SDL_GetTicks();
                    squares.push_back(s);
                }

                break;
            }
        }

        // Physics loop 物理计算，依据时间差，不受帧率影响
        for (int index = 0; index < squares.size(); index++) {
            square& s = squares[index];

            Uint32 time = SDL_GetTicks();
            float dT = (time - s.lastUpdate) / 1000.0f;

            s.yvelocity += dT * GRAVITY;
            s.y += s.yvelocity * dT;
            s.x += s.xvelocity * dT;

            if (s.y > 480 - s.h) {
                s.y = 480 - s.h;
                s.xvelocity = 0;
                s.yvelocity = 0;
            }

            s.lastUpdate = time;
            if (s.lastUpdate > s.born + 5000) { // 生成5秒后消失
                squares.erase(squares.begin() + index);
                index--;
            }
        }

        // Render loop
        for (const square& s : squares) {
            SDL_Rect dest = {
                static_cast<int>(round(s.x)),
                static_cast<int>(round(s.y)),
                static_cast<int>(round(s.w)),
                static_cast<int>(round(s.h))
            };
            SDL_RenderCopy(renderer, box, NULL, &dest);
        }

        int delay_method = 0;

        if (delay_method == 0) { // 故意浮动等待，使帧率波动，测试物理引擎的正确性
            // Delay for a random number of ticks - this makes the frame rate variable,
            // demonstrating that the physics is independent of the frame rate.
            SDL_Delay(rand() % 25);
        } else if (delay_method == 1) { // 等待delta ms
            static Uint64 last_tick = 0;

            double delta_ms = (double)SDL_GetPerformanceCounter() - (double)last_tick;
            delta_ms *= 1000.0;
            delta_ms /= SDL_GetPerformanceFrequency();

            int delay_ms = static_cast<int>(floor(16.666f - delta_ms));
            if (delay_ms > 0) {
                SDL_Delay(delay_ms);
                SDL_Log("%.1f    %d", delta_ms, delay_ms);
            } else {
                SDL_Log("No time!!!!!!!!!!!!");
            }
            last_tick = SDL_GetPerformanceCounter();
        } else if (delay_method == 2) { // 等待固定ms
            SDL_Delay(17);
        } else { // 不等待，适用于开启垂直同步
            ;
        }

        // End frame timing
        Uint32 endTicks = SDL_GetTicks();
        Uint64 endPerf = SDL_GetPerformanceCounter();
        Uint64 framePerf = endPerf - startPerf;
        float frameTime = (endTicks - startTicks) / 1000.0f;
        totalFrameTicks += endTicks - startTicks;

        // Strings to display
        string fps = "Current FPS: " + to_string(1.0f / frameTime);
        string avg = "Average FPS: " + to_string(1000.0f / ((float)totalFrameTicks / totalFrames));
        string perf = "Current Perf: " + to_string(framePerf);

        // Display strings
        SDL_Rect dest = { 10, 10, 0, 0 };
        renderText(fps, dest);
        dest.y += 24;
        renderText(avg, dest);
        dest.y += 24;
        renderText(perf, dest);

        // Display window
        SDL_RenderPresent(renderer);
    }
}

void renderText(string text, SDL_Rect dest)
{
    SDL_Color fg = { 0, 0, 0 };
    SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), fg);

    dest.w = surf->w;
    dest.h = surf->h;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_RenderCopy(renderer, tex, NULL, &dest);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "Error initializing SDL: " << SDL_GetError() << endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_JPG) < 0) {
        cout << "Error initializing SDL_image: " << IMG_GetError() << endl;
        return false;
    }

    if (TTF_Init() < 0) {
        cout << "Error initializing SDL_ttf: " << TTF_GetError() << endl;
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

    SDL_Surface* buffer = IMG_Load("box.jpg");
    if (!buffer) {
        cout << "Error loading image box.jpg: " << SDL_GetError() << endl;
        return false;
    }

    box = SDL_CreateTextureFromSurface(renderer, buffer);
    SDL_FreeSurface(buffer);
    buffer = NULL;
    if (!box) {
        cout << "Error creating texture: " << SDL_GetError() << endl;
        return false;
    }

    font = TTF_OpenFont("font.ttf", 24);
    if (!font) {
        cout << "Error loading font: " << TTF_GetError() << endl;
        return false;
    }

    return true;
}

void kill()
{
    TTF_CloseFont(font);
    SDL_DestroyTexture(box);
    font = NULL;
    box = NULL;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

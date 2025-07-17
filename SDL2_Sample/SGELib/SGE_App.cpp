#include "SGE_App.h"

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <iostream>

// 构造函数
SGE_App::SGE_App()
    : m_window(nullptr)
    , m_renderer(nullptr)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SGE_App constructor.");
}

// 析构函数
SGE_App::~SGE_App()
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SGE_App destructor.");

    Destroy();

    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SGE_App destoryed.");
}

// 初始化
bool SGE_App::Init(
    const std::string windowTitle,
    const SDL_Rect& windowRect,
    Uint32 windowFlags,
    Uint32 rendererFlags)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    // 初始化成功后可以输出SDL日志了
    SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "SGE_App::Init() start.");
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init successfully.");

    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error intializing SDL_ttf: %s", TTF_GetError());
        return false;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init successfully.");

    // Initialize SDL_image 尽可能加载所有格式
    /*
    IMG_INIT_JPG    = 0x00000001,
    IMG_INIT_PNG    = 0x00000002,
    IMG_INIT_TIF    = 0x00000004,
    IMG_INIT_WEBP   = 0x00000008,
    IMG_INIT_JXL    = 0x00000010, // 官方编译的默认版本不支持此格式
    IMG_INIT_AVIF   = 0x00000020
    */
    int img_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | /*IMG_INIT_JXL |*/ IMG_INIT_AVIF;
    int img_initted = IMG_Init(img_flags);
    if ((img_initted & img_flags) != img_flags) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL_image: %s", IMG_GetError());
        return false;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init successfully.");

    // Initialize SDL_mixer 尽可能加载所有格式
    /*
    MIX_INIT_FLAC   = 0x00000001,
    MIX_INIT_MOD    = 0x00000002, // 官方编译的默认版本不支持此格式
    MIX_INIT_MP3    = 0x00000008,
    MIX_INIT_OGG    = 0x00000010,
    MIX_INIT_MID    = 0x00000020,
    MIX_INIT_OPUS   = 0x00000040, // 官方编译的默认版本不支持此格式
    MIX_INIT_WAVPACK= 0x00000080  // 官方编译的默认版本不支持此格式
    */
    int mix_flags = MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID /*| MIX_INIT_MOD |MIX_INIT_OPUS | MIX_INIT_WAVPACK */;
    int mix_initted = Mix_Init(mix_flags);
    if ((mix_initted & mix_flags) != mix_flags) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error intializing SDL_mixer: %s", TTF_GetError());
        return false;
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Mix_Init successfully.");

    // 打开音频设备
    int frequency = 44100;
    int channels = 2;
    int chunksize = 2048;

    // 尝试打开音频设备
    if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize) < 0) {
        // 第一次失败：降低采样率
        frequency = 22050;
        if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize) < 0) {
            // 第二次失败：增加缓冲区
            chunksize = 4096;
            if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize) < 0) {
                // 第三次失败：使用单声道
                channels = 1;
                if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize) < 0) {
                    // 最终失败：使用最小配置
                    frequency = 11025;
                    chunksize = 1024;
                    if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize) < 0) {
                        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error Mix_OpenAudio: %s", Mix_GetError());
                        return false;
                    }
                }
            }
        }
    }

    // 创建窗口
    m_window = SDL_CreateWindow(
        windowTitle.c_str(),
        windowRect.x, windowRect.y, windowRect.w, windowRect.h,
        windowFlags);
    if (nullptr == m_window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating window: %s", SDL_GetError());
        return false;
    }

    // 创建渲染器
    // 第2个参数设置-1，由SDL决定渲染后端
    // ----------------------------------------------------------
    // 平台       默认尝试顺序 (高→低优先级)
    // Windows    Direct3D 11 → Direct3D 9 → OpenGL → Software
    // macOS      Metal → OpenGL → Software
    // Linux      Vulkan → OpenGL → OpenGL ES → Software
    // Android    Vulkan → OpenGL ES 3 → OpenGL ES 2
    // ----------------------------------------------------------
    m_renderer = SDL_CreateRenderer(m_window, -1, rendererFlags);
    if (nullptr == m_renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating renderer: %s", SDL_GetError());
        return false;
    }

    // 使用黑色清空窗口内容
    if (SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error SDL_SetRenderDrawColor: %s", SDL_GetError());
        return false;
    }
    if (SDL_RenderClear(m_renderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error SDL_RenderClear: %s", SDL_GetError());
        return false;
    }

    SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "SGE_App::Init() end.");
    return true;
}

// 销毁
void SGE_App::Destroy()
{
    SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "SGE_App::Destroy() start.");

    // 销毁渲染器
    if (nullptr != m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    // 销毁窗口
    if (nullptr != m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    Mix_CloseAudio(); // 关闭音频设备

    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();

    SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "SGE_App::Destroy() end.");
}

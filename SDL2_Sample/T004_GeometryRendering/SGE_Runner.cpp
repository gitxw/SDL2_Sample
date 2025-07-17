#include "SGE_Runner.h"

// 运行
void SGE_Runner::Run()
{
    m_isRunning = true;
    while (m_isRunning) {
        // event
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (m_frameEventFunc) {
                m_frameEventFunc(this, e);
            }
        }

        // update
        if (m_frameUpdateFunc) {
            m_frameUpdateFunc(this, 10);
        }

        // renderer
        if (m_frameRenderFunc) {
            m_frameRenderFunc(this);
        }

        // wait before processing the next frame
        SDL_Delay(10);
    }
}

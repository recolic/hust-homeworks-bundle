#ifndef R_OGL_FPS
#define R_OGL_FPS 1

#include <rlib/stdio.hpp>
#include <atomic>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

inline std::atomic<size_t> fps_counter(0);

inline void fps_thread() {
    while(true) {
        std::this_thread::sleep_for(1s);
        auto fps = fps_counter.exchange(0);
        rlib::println("FPS =", fps);
    }
}

void QueryGLVersion()
{
    std::string version  = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    std::string glslver  = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
    std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

    rlib::printfln("OpenGL [{}] with GLSL [{}] on renderer [{}].", version, glslver, renderer);
}

inline void init_fps() {
    QueryGLVersion();
    std::thread(fps_thread).detach();
}


#endif

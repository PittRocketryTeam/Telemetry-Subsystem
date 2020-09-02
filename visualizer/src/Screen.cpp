#include "Screen.hpp"
#include "Shader.hpp"
#include "gl.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Util.hpp"
#define WMAX 1.f

static SDL_Window* window;
static SDL_GLContext ctx;
static int width;
static int height;

static unsigned int fbo;
static unsigned int rbo;
static unsigned int fb_tex;
static unsigned int vao;
static mode7::Shader screenShader;
static unsigned int texture_loc;
static int RESX;
static int RESY;

static float screen_quad_data[] = {
    -1.0f, -1.0f,  0.f,  0.f,
     WMAX, -1.0f,  1.f,  0.f,
     WMAX,  WMAX,  1.f,  1.f,

     WMAX,  WMAX,  1.f,  1.f,
    -1.0f,  WMAX,  0.f,  1.f,
    -1.0f, -1.0f,  0.f,  0.f
};

void mode7::Screen::create(int w, int h)
{
    //auto pair = Util::getMonitorRes();
    //width = pair.first;
    //height = pair.second;
    width = w;
    height = h;
    RESX = w;
    RESY = h;

    //SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetSwapInterval(0);

    window = SDL_CreateWindow(
        "title",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_WINDOW_OPENGL// | SDL_WINDOW_FULLSCREEN//_DESKTOP
    );
    ctx = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    const GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        printf("glew init error: %s\n", glewGetErrorString(err));
    }

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.7f, 0.7f, 0.8f, 1.0f);

    // load screen shader
    screenShader.open(
        "assets/shaders/screen_v.glsl",
        "assets/shaders/screen_f.glsl"
    );

    texture_loc = glGetUniformLocation(screenShader.pid(), "tex");

    // generate frame buffer and render buffer
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glGenTextures(1, &fb_tex);
    glBindTexture(GL_TEXTURE_2D, fb_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, RESX, RESY, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb_tex, 0);
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, RESX, RESY);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "framebuffer not complete" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // generate quad
    unsigned int vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * 3 * 4 * sizeof(float), screen_quad_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 2,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 2,
        GL_FLOAT, GL_FALSE,
        4 * sizeof(float),
        (void*)(2 * sizeof(float))
    );
}

void mode7::Screen::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void mode7::Screen::beginRender()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, RESX, RESY);
}

void mode7::Screen::flip()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
    /*glBlitFramebuffer(
        0, 0, width, height,
        0, 0, width, height,
        GL_COLOR_BUFFER_BIT, GL_NEAREST
    );*/
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    screenShader.onlyUse();
    glActiveTexture(GL_TEXTURE0);
    glUniform1ui(texture_loc, fb_tex);
    glBindTexture(GL_TEXTURE_2D, fb_tex);
    
    glBindVertexArray(vao);
    glDisable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glActiveTexture(0);
    glBindVertexArray(0);
    
    SDL_GL_SwapWindow(window);
}

void mode7::Screen::destroy()
{
    glDeleteFramebuffers(1, &fbo);
    SDL_DestroyWindow(window);
}

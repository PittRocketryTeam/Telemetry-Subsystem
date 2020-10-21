#include <iostream>
#include <SDL.h>
#include "App.hpp"
#include "Clock.hpp"
#include "Screen.hpp"
#include "Camera.hpp"
#include "Keyboard.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

#define WIDTH 1280
#define HEIGHT 720

using namespace mode7;

static int running = 0;
static SDL_Event e;

void events()
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            running = 0;
        }
    }

    Keyboard::poll();

    if (Keyboard::isDown("escape"))
    {
        running = 0;
    }
}

void update()
{
    App::update();
}

void draw()
{
    Screen::beginRender();
    App::draw();
    Screen::flip();
}

#ifdef main
#undef main
#endif
int main()
{
    std::cout << "hello world" << std::endl;
    
    Screen::create(WIDTH, HEIGHT);
    Camera::create(WIDTH, HEIGHT, 70, 1.f, 1000.f);

    Keyboard::attach();

    App::init();    

    running = 1;
    Clock::start();
    while (running)
    {
        Clock::tick();
        while (Clock::lagging())
        {
            events();
            update();
            Clock::lagTick();
        }
        draw();
    }

    Screen::destroy();
    
    return 0;
}

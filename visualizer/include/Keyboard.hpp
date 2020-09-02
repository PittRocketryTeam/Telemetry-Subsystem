#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <SDL.h>
#include <string>

namespace mode7
{

class Keyboard
{
public:
    static void attach();
    static void poll();
    static bool isDown(SDL_Scancode);
    static bool isDown(const std::string&);
    static bool isPressed(SDL_Scancode);
    static bool isPressed(const std::string&);

    static int lock();
    static void unlock();
    static bool available(int);
};

}

#endif /* KEYBOARD_HPP */
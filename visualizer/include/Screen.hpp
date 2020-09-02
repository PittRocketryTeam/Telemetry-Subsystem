#ifndef SCREEN_HPP
#define SCREEN_HPP

namespace mode7
{

class Screen
{
public:

    static void create(int, int);
    static void clear();
    static void beginRender();
    static void flip();
    static void destroy();

private:

};

#endif /* SCREEN_HPP */

}
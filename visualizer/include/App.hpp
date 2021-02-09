#ifndef APP_HPP
#define APP_HPP
#define PI 3.14159265
class App
{
public:

    static void init();
    static void update();
    static void draw();
    static void checkKeyboardMovement(); 
    static void addCheckPoint();
    static void motorBurnout(); 
};

#endif /* APP_HPP */

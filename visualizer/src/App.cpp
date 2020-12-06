#include "App.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "ModelLoader.hpp"
#include "Camera.hpp"
#include "Keyboard.hpp"

using namespace mode7;

static Shader test_shader;
static Shader flat_shader;
static Scene test_mesh;
static Scene test_cube;
static Scene skybox;
static Scene rocket;
static Scene ground;
static Object dummy;
static float x, y, z;
static float radius, angle; 
static bool crackHead, keyChange; 
static glm::vec3 help; 


void App::init()
{
    test_shader.open("assets/shaders/test_v.glsl", "assets/shaders/test_f.glsl");
    flat_shader.open("assets/shaders/flat_v.glsl", "assets/shaders/flat_f.glsl");
    test_mesh = ModelLoader::open("assets/models/vehicle.dae");
    test_mesh.scale = glm::vec3(0.75f);
    //test_mesh.rotate(M_PI / 8.f, 0.f, 0.f);
    test_cube = ModelLoader::open("assets/models/test_cube.dae");
    skybox = ModelLoader::open("assets/models/skybox.dae");
    skybox.scale = glm::vec3(500.f);
    test_cube.position.z = -3.f;

    ground = ModelLoader::open("assets/models/ground2.dae");
    ground.scale = glm::vec3(250.f);
    ground.position.y = -4;
    crackHead = false; 

    radius = 30; //obj to move at a radius of 2 

    //test_mesh.addChild(&test_cube);
    dummy.addChild(&test_cube);
    test_mesh.addChild(&dummy);
}

//Basically just focusing on the x,y plane as of now. 
void App::update()
{
    angle += 0.1f; 
    //test_mesh.position.x = radius * cosf(angle); 
    //test_mesh.position.y = radius * sinf(angle);

    Keyboard::poll();
    
    if(Keyboard::isDown(SDL_SCANCODE_R) || !crackHead)
    {
        //Whenever the key R is pressed or the program started up, the camera will look at the default view 
        Camera::lookAt(glm::vec3(test_mesh.position.x, test_mesh.position.y, 20), test_mesh.position + glm::vec3(0, 10, 0));
        crackHead = true; 
    }
    else if (Keyboard::isDown(SDL_SCANCODE_LEFT))
    {
        x += 0.1f; 
        z += 0.1f; 
        //Note the camera should move on the x-z plane, the angle here for x and z are incrementing to move left 
        Camera::lookAt(test_mesh.position + glm::vec3(radius*sin(x), 0, radius*cos(z)), test_mesh.position + glm::vec3(0, 10, 0));
    }
    else if (Keyboard::isDown(SDL_SCANCODE_RIGHT))
    {
        x -= 0.1f; 
        z -= 0.1f; 
        //Note the camera should move on the x-z plane, the angle here for x and z are incrementing to move right 
        Camera::lookAt(test_mesh.position + glm::vec3(radius*sinf(x), 0, radius*cosf(z)), test_mesh.position + glm::vec3(0, 10, 0));
    }
    else if(Keyboard::isDown(SDL_SCANCODE_UP))
    {
        y -= 0.1f; 
        z -= 0.1f; 
        //Note the camera should move on the y-z plane, the angle here for x and z are incrementing to move up
        Camera::lookAt(test_mesh.position + glm::vec3(0, radius*sinf(y), radius*cosf(z)), test_mesh.position + glm::vec3(0, 10, 0));
    }
    else if(Keyboard::isDown(SDL_SCANCODE_DOWN))
    {
        y += 0.1f; 
        z += 0.1f; 
        //Note the camera should move on the y-z plane, the angle here for x and z are incrementing to move down
        Camera::lookAt(test_mesh.position + glm::vec3(0, radius*sinf(y), radius*cosf(z)), test_mesh.position + glm::vec3(0, 10, 0));
    }

    
    dummy.update();
    skybox.update();
    ground.update();
    test_mesh.update();
    Camera::updateView();  
}

//This method will draw the object (.dae) onto the canvas. 
void App::draw()
{
    skybox.draw(flat_shader);
    ground.draw(flat_shader);
    test_mesh.draw(flat_shader);
    //test_cube.draw(test_shader);
}

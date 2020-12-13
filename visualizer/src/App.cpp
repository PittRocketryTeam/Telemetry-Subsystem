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
static float radius, angle, prev_view; 
static bool start; 


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
    start = false; 
    angle = (1.0 * PI)/180.0f; 
    radius = 40; //obj to move at a radius of 2 

    //test_mesh.addChild(&test_cube);
    dummy.addChild(&test_cube);
    test_mesh.addChild(&dummy);
}

//Basically just focusing on the x,y plane as of now. 
void App::update()
{
    //test_mesh.position.x = radius * cosf(angle); 
    //test_mesh.position.y = radius * sinf(angle);
    Keyboard::poll();
    
    if(Keyboard::isDown(SDL_SCANCODE_R) || !start)
    {
        //Whenever the key R is pressed or the program started up, the camera will look at the default view 
        Camera::lookAt(glm::vec3(test_mesh.position.x, test_mesh.position.y, radius), test_mesh.position + glm::vec3(0, 10, 0));
        start = true; 

        x = y = z = 0.0f; 
    }
    else if (Keyboard::isDown(SDL_SCANCODE_LEFT))
    {
            prev_view = radius - (radius * cosf(z)); 

        x += angle; 
        z += angle;
        //Note the camera should move on the x-z plane, the angle here for x and z are incrementing to move left 
        Camera::lookAt(test_mesh.position + glm::vec3(radius*sinf(x), 0, radius*cosf(z)), test_mesh.position + glm::vec3(0, 10, 0));
        //Camera::lookAt(test_mesh.position + glm::vec3(prev_view*sin(x), radius * sinf(y), prev_view*cosf(z)) , test_mesh.position + glm::vec3(0, 10, 0));
    }
    else if (Keyboard::isDown(SDL_SCANCODE_RIGHT))
    {
        //prev_view = radius - (radius * cosf(z)); Ignore; will be helpful tho for the quaternion camera stuff 
        x -= angle; 
        z -= angle; 
        //Note the camera should move on the x-z plane, the angle here for x and z are incrementing to move right 
        Camera::lookAt(test_mesh.position + glm::vec3(radius*sinf(x), 0, radius*cosf(z)), test_mesh.position + glm::vec3(0, 10, 0));
        //Camera::lookAt(test_mesh.position + glm::vec3(prev_view*sinf(x), radius * sinf(y), prev_view*cosf(z)), test_mesh.position + glm::vec3(0, 10, 0));
    }
    else if(Keyboard::isDown(SDL_SCANCODE_UP))
    { //Not all cases are handled with up and down, the x val has to be modified and not 0 as it currently is 
        y += angle; 
        z += angle; 

        //Note the camera should move on the y-z plane, the angle here for x and z are incrementing to move up
        Camera::lookAt(test_mesh.position + glm::vec3(0, radius*sinf(y), radius*cosf(z)), test_mesh.position + glm::vec3(0, 10, 0));
    }
    else if(Keyboard::isDown(SDL_SCANCODE_DOWN))
    {//same note as above
        y -= angle; 
        z -= angle; 
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

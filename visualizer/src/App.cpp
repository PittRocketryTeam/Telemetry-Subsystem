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
static float x;

void App::init()
{
    test_shader.open("assets/shaders/test_v.glsl", "assets/shaders/test_f.glsl");
    flat_shader.open("assets/shaders/flat_v.glsl", "assets/shaders/flat_f.glsl");
    test_mesh = ModelLoader::open("assets/models/vehicle.dae");
    test_mesh.scale = glm::vec3(0.75f);
    test_mesh.rotate(M_PI / 8.f, 0.f, 0.f);
    test_cube = ModelLoader::open("assets/models/test_cube.dae");
    skybox = ModelLoader::open("assets/models/skybox.dae");
    skybox.scale = glm::vec3(500.f);
    test_cube.position.z = -3.f;

    ground = ModelLoader::open("assets/models/ground2.dae");
    ground.scale = glm::vec3(250.f);
    ground.position.y = -4;

    //test_mesh.addChild(&test_cube);
    dummy.addChild(&test_cube);
    test_mesh.addChild(&dummy);
}

//Basically just focusing on the x,y plane as of now. 
void App::update()
{
    Keyboard::poll();
    if (Keyboard::isDown(SDL_SCANCODE_LEFT))
    {
        test_mesh.rotate(0.f, 0.1f, 0.f);
    }
    if (Keyboard::isDown(SDL_SCANCODE_RIGHT))
    {
        test_mesh.rotate(0.f, -0.1f, 0.f);
    }

    test_mesh.position.y = -3.f;
 
    //For object moving in a circle. If the radius is larger, the object will go out of view at times so adjust the z-axis in the camera.
    dummy.update();
    skybox.update();
    ground.update();

    Camera::lookAt(glm::vec3(-15, 20, -15), test_mesh.position + glm::vec3(0, 10, 0));
    //std::cout << angle << std::endl; 

    angle += 0.05f;  //Note since the screen's height is 480 --> an angle val larger than 4.8 takes the object out of view (a note for the commented code in beginning of this method)
    test_monk.update(); 
  
    
    //One view (circle movement with camera follow)
    //Camera::lookAt(glm::vec3(test_monk.position.x, test_monk.position.y, 5), glm::vec3(0,0,0));

    //Second view (circle movement without camera follow)
    //Camera::lookAt(glm::vec3(0.0f, 0.0f, 5), glm::vec3(0,0,0));
   
    //Try to change x, y, and z as the object is moving up (still figuring this out) to make the movement look seamless
    //Camera::lookAt(glm::vec3(test_monk.position.x, test_monk.position.y, 5), glm::vec3(x, y, z));

    //This will focus on the object, but it won't show any movement although the object is moving. 
    Camera::lookAt(glm::vec3(test_monk.position.x, test_monk.position.y, 5), test_monk.position);
    Camera::updateView();  
}

//This method will draw the object (.dae) onto the canvas. Without this, it is a blank canvas. 
void App::draw()
{
    skybox.draw(flat_shader);
    ground.draw(flat_shader);
    test_mesh.draw(flat_shader);
    //test_cube.draw(test_shader);
}

#include "App.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "ModelLoader.hpp"
#include "Data.hpp"
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
static Data zeeData;  

//static float x, y, z;


static Object vehicle_tracker;
static Object camera_arm;
static float x;


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

    zeeData.readData("../../test-data/data.csv");
    //test_mesh.addChild(&test_cube);
    dummy.addChild(&test_cube);
    test_mesh.addChild(&dummy);


    // the camera arm holds the camera a distance of 50 away from the vehicle
    camera_arm.addChild(&Camera::getObject());
    camera_arm.position.z = 50.f;
    // the vehicle tracker is just a point in space that follows the vehicle
    vehicle_tracker.addChild(&camera_arm);
}


}
 
void App::update()
{
    //test_mesh.position.x = radius * cosf(angle); 
    //test_mesh.position.y = radius * sinf(angle);
    //Keyboard::poll();
    Camera::lookAt(glm::vec3(test_mesh.position.x, test_mesh.position.y, 5), test_mesh.position);        
    dummy.update();
    skybox.update();
    ground.update();
    test_mesh.update();
    Camera::updateView();  

    Keyboard::poll();
    if (Keyboard::isDown(SDL_SCANCODE_LEFT))
    {
        vehicle_tracker.rotate(0.f, 0.1f, 0.f);
    }
    if (Keyboard::isDown(SDL_SCANCODE_RIGHT))
    {
        vehicle_tracker.rotate(0.f, -0.1f, 0.f);
    }
    if (Keyboard::isDown(SDL_SCANCODE_UP))
    {
        vehicle_tracker.rotate(0.1f, 0.f, 0.f);
    }
    if (Keyboard::isDown(SDL_SCANCODE_DOWN))
    {
        vehicle_tracker.rotate(-0.1f, 0.f, 0.f);
    }

    // this block just clamps the x rotation
    float thx = glm::eulerAngles(vehicle_tracker.rx).x;
    if (thx > 0.f && thx <= M_PI_2)
    {
        vehicle_tracker.setRotationX(M_PI_2);
    }
    else if (thx < 0.f && thx > -M_PI_2)
    {
        vehicle_tracker.setRotationX(-M_PI_2);
    }

    test_mesh.position.y = -3.f;

    // make the vehicle tracker follow the vehicle
    vehicle_tracker.position = test_mesh.position;

    test_mesh.update();
    vehicle_tracker.update();
    skybox.update();
    ground.update();
    
    //Camera::lookAt(glm::vec3(-15, 20, -15), test_mesh.position + glm::vec3(0, 10, 0));
    Camera::updateView();

}

void App::draw()
{
    skybox.draw(flat_shader);
    ground.draw(flat_shader);
    test_mesh.draw(flat_shader);
    //test_cube.draw(test_shader);
}

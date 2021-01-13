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

static Object vehicle_tracker;
static Object camera_arm;
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

    // the camera arm holds the camera a distance of 50 away from the vehicle
    camera_arm.addChild(&Camera::getObject());
    camera_arm.position.z = 50.f;
    // the vehicle tracker is just a point in space that follows the vehicle
    vehicle_tracker.addChild(&camera_arm);
}

void App::update()
{
    Keyboard::poll();
    if (Keyboard::isDown(SDL_SCANCODE_LEFT))
    {
        vehicle_tracker.rotate(0.f, 0.1f, 0.f);
    }
    else if (Keyboard::isDown(SDL_SCANCODE_RIGHT))
    {
        vehicle_tracker.rotate(0.f, -0.1f, 0.f);
    }
    else if (Keyboard::isDown(SDL_SCANCODE_UP))
    {
        camera_arm.position.z -= 1.f;
    }
    else if (Keyboard::isDown(SDL_SCANCODE_DOWN))
    {
        camera_arm.position.z += 1.f;
    }
    else if (Keyboard::isDown(SDL_SCANCODE_A))
    {
        camera_arm.position.x -= 1.f;
    }
    else if (Keyboard::isDown(SDL_SCANCODE_D))
    {
        camera_arm.position.x += 1.f;
    }
    else if (Keyboard::isDown(SDL_SCANCODE_W))
    {
        camera_arm.position.y += 1.f;
    }
    else if (Keyboard::isDown(SDL_SCANCODE_S))
    {
        camera_arm.position.y -= 1.f;
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

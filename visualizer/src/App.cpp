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
    test_mesh = ModelLoader::open("assets/models/suzanne.dae");
    test_cube = ModelLoader::open("assets/models/test_cube.dae");
    skybox = ModelLoader::open("assets/models/skybox.dae");
    skybox.scale = glm::vec3(500.f);
    test_cube.position.z = -3.f;

    ground = ModelLoader::open("assets/models/ground.dae");
    ground.scale = glm::vec3(250.f);
    ground.position.y = -4;

    //test_mesh.addChild(&test_cube);
    dummy.addChild(&test_cube);
    test_mesh.addChild(&dummy);
}

void App::update()
{
    Keyboard::poll();
    if (Keyboard::isDown(SDL_SCANCODE_LEFT))
    {
        dummy.rotate(0.f, 0.1f, 0.f);
    }
    if (Keyboard::isDown(SDL_SCANCODE_RIGHT))
    {
        dummy.rotate(0.f, -0.1f, 0.f);
    }

    test_mesh.position.y = -3.f;

    test_mesh.update();
    dummy.update();
    skybox.update();
    ground.update();
    
    Camera::lookAt(glm::vec3(-5, -2, -5), test_mesh.position);
    Camera::updateView();
}

void App::draw()
{
    skybox.draw(flat_shader);
    ground.draw(flat_shader);
    test_mesh.draw(test_shader);
    test_cube.draw(test_shader);
}

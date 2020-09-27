#include "App.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "ModelLoader.hpp"
#include "Camera.hpp"

using namespace mode7;

static Shader test_shader;
static Scene test_mesh;
static Scene test_cube;
static float x;

void App::init()
{
    test_shader.open("assets/shaders/test_v.glsl", "assets/shaders/test_f.glsl");
    test_mesh = ModelLoader::open("assets/models/suzanne.dae");
    test_cube = ModelLoader::open("assets/models/test_cube.dae");

    test_cube.position.z = -3.f;

    test_mesh.addChild(&test_cube);
}

void App::update()
{
    test_cube.rotate(0.f, 0.01f, 0.f);
    test_mesh.rotate(0.f, 0.01f, 0.f);
    test_mesh.position.y = 3.f * sinf(x);
    x += 0.05f;

    test_mesh.update();
    
    Camera::lookAt(glm::vec3(-5, 2, -5), test_mesh.position);
    Camera::updateView();
}

void App::draw()
{
    test_mesh.draw(test_shader);
    test_cube.draw(test_shader);
}

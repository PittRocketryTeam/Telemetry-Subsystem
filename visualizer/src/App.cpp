#include "App.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "ModelLoader.hpp"
#include "Camera.hpp"

using namespace mode7;

static Shader test_shader;
static Scene test_mesh;

void App::init()
{
    test_shader.open("assets/shaders/test_v.glsl", "assets/shaders/test_f.glsl");
    test_mesh = ModelLoader::open("assets/models/test_cube.dae");
    
    Camera::lookAt(glm::vec3(3.f, 2.f, 3.f), glm::vec3(0.f, 0.f, 0.f));
}

void App::update()
{
    test_mesh.rotate(0.f, 0.01f, 0.f);
    test_mesh.update();
    
    Camera::updateView();
}

void App::draw()
{
    test_mesh.draw(test_shader);
}

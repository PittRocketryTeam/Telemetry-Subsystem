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
static Shader line_shader; 
static Scene test_mesh;
static Scene test_cube;
static Scene skybox;
static Scene rocket;
static Scene ground;
static Scene flame; 
static Data zeeData;  

static Object vehicle_tracker;
static Object camera_arm;
static std::vector<glm::vec3> path; 
static Mesh what_mesh; 
static int counter; 
static bool burnout; 

void App::init()
{ 
    test_shader.open("assets/shaders/test_v.glsl", "assets/shaders/test_f.glsl");
    flat_shader.open("assets/shaders/flat_v.glsl", "assets/shaders/flat_f.glsl");
    line_shader.open("assets/shaders/path_v.glsl", "assets/shaders/path_f.glsl"); 
    
    test_mesh = ModelLoader::open("assets/models/vehicle.dae");
    test_mesh.scale = glm::vec3(0.75f);

    flame = ModelLoader::open("assets/models/flame.dae");
    flame.scale = glm::vec3(1.0f); 
    test_mesh.addChild(&flame); 

    skybox = ModelLoader::open("assets/models/skybox.dae");
    skybox.scale = glm::vec3(500.f);

    ground = ModelLoader::open("assets/models/ground2.dae");
    ground.scale = glm::vec3(250.f);
    ground.position.y = -4;

    zeeData.readData("../../test-data/data.csv");

    // the camera arm holds the camera a distance of 50 away from the vehicle
    camera_arm.addChild(&Camera::getObject());
    camera_arm.position.z = 50.f;
    // the vehicle tracker is just a point in space that follows the vehicle
    vehicle_tracker.addChild(&camera_arm);

    test_cube = ModelLoader::open("assets/models/test_cube.dae");
}

void App::checkKeyboardMovement()
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

    //test_mesh.position.y = -3.f;

    // make the vehicle tracker follow the vehicle
    vehicle_tracker.position = test_mesh.position;
}

void App::motorBurnout()
{
    burnout = true; //a flag to stop further draw calls
    flame.position = glm::vec3(0, -100, 0); //set flame object out of view 
}

void App::addCheckPoint()
{
    glm::vec3 new_point = test_mesh.position; //Get new point
    //path.push_back(*path.end()); 
    path.push_back(new_point); //add new coordinate
    //std::cout << "amt: " << amt << std::endl;
    what_mesh.drawLines(path, path.size());  
}

void App::update()
{
    zeeData.pollData(); //health packet 
    std::vector<float> orientation_pkt = zeeData.pollData(); //orientation packet 
    test_mesh.quat = glm::quat(orientation_pkt[12], orientation_pkt[15], orientation_pkt[13], orientation_pkt[14]); 
    //std::cout << "W: " << orientation_pkt[12] << " X: " << orientation_pkt[13] << " Y: " << orientation_pkt[14] << " Z: " << orientation_pkt[15] << std::endl; 
    test_mesh.position.y += 0.01f;
    flame.position = test_mesh.position; 
    flame.quat = test_mesh.quat;  
    //std::cout << test_mesh.position.x << std::endl;

    test_mesh.update(1); //use test_mesh.update(1) to do a quaternion rotation 
    test_cube.update();
    flame.update(1); //rotate the same way as test_mesh
    vehicle_tracker.position = test_mesh.position;
    vehicle_tracker.update();
    skybox.update();
    ground.update();
    checkKeyboardMovement();
    if(counter == 5)
    {
        addCheckPoint(); 
        counter = 0; 
    }
    counter += 1; 
    Camera::updateView();
}

void App::draw()
{
    skybox.draw(flat_shader);
    ground.draw(flat_shader);
    test_mesh.draw(flat_shader);
    if(!burnout)
    {
        flame.draw(test_shader); 
    }
    what_mesh.drawLine(line_shader, path.size()); 
   
}

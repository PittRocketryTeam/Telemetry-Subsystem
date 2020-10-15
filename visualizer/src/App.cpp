#include "App.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "ModelLoader.hpp"
#include "Camera.hpp"

using namespace mode7;

static Shader test_shader;
static Scene test_monk;
static Scene test_cube;
static float angle;
static float radius; 
static float moved; 
static float x, y, z; 
void App::init()
{
    test_shader.open("assets/shaders/test_v.glsl", "assets/shaders/test_f.glsl");
    test_monk = ModelLoader::open("assets/models/suzanne.dae"); //Monkey object
    //test_cube = ModelLoader::open("assets/models/test_cube.dae"); //Cube object

    test_monk.position = glm::vec3(0.0f, 0.0f, 0.0f); 

    radius = 2; //To move the object in a circle with radius 2 look at update method
    angle = 0.0f; //Start at the beginning of the unit circle :D
    x = y = z = 0.0f; 
    //test_mesh.addChild(&test_cube); 
}

//Basically just focusing on the x,y plane as of now. 
void App::update()
{
    //For object moving only up 
    //test_cube.position.x = 0.0f; 
    //test_cube.position.y = angle;
 
    //For object moving in a circle. If the radius is larger, the object will go out of view at times so adjust the z-axis in the camera.
    test_monk.position.x = radius * cosf(angle); 
    test_monk.position.y = radius * sinf(angle);


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
    test_monk.draw(test_shader);
}

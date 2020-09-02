#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Object.hpp"
#include <glm/glm.hpp>

namespace mode7
{

class Camera
{
public:

    static void create(float, float, float, float, float);
    static void updateView();
    static void lookAt(glm::vec3, glm::vec3);
    static glm::mat4 getProjection();
    static glm::mat4 getView();
    static Object& getObject();

private:

    static Object object;
    static glm::mat4 view;
    static glm::mat4 projection;
};

}

#endif /* CAMERA_HPP */

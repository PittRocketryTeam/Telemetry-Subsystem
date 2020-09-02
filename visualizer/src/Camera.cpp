#include "Camera.hpp"

namespace mode7
{

glm::mat4 Camera::view(1.0f);
glm::mat4 Camera::projection(1.0f);
Object Camera::object;

void Camera::create(float w, float h, float fov, float n, float f)
{
    projection = glm::perspective(glm::radians(fov), w / h, n, f);
}

void Camera::updateView()
{
    view = glm::inverse(object.getWorldMatrix());
}

void Camera::lookAt(glm::vec3 eye, glm::vec3 target)
{
    object.matrix = glm::inverse(glm::lookAt(eye, target, glm::vec3(0, 1, 0)));
    object.accumulate();
    object.decompose();
}

glm::mat4 Camera::getProjection()
{
    return projection;
}

glm::mat4 Camera::getView()
{
    return view;
}

Object& Camera::getObject()
{
    return object;
}

}

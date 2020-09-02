#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include "gl.h"
#include "BBox.hpp"

namespace mode7
{

class Object
{
public:

    Object();
    virtual ~Object();

    void addChild(Object*);

    void move();
    virtual void update();
    virtual void update(glm::mat4);

    glm::mat4 getWorldMatrix();
    glm::vec3 getWorldPosition();
    glm::vec3 getWorldRotation();
    glm::vec3 getWorldScale();
    glm::vec3 getFront();
    glm::quat getWorldQuat();

    void accumulate();
    void decompose();

    void setRotation(float, float, float);
    void rotate(float, float, float);
    void setRotationX(float);
    void setRotationY(float);
    void setRotationZ(float);

    glm::quat getWorldRx();
    glm::quat getWorldRy();

    BBox* getBoundingBox();
    std::vector<Object*> getChildren();

    Object* getParent();

    glm::vec3 position;
    glm::quat rx;
    glm::quat ry;
    glm::quat rz;
    glm::vec3 scale;
    glm::vec3 velocity;

    glm::quat quat;
    glm::mat4 matrix;
    glm::mat4 inherent;

protected:

    glm::vec3 worldPosition;
    glm::vec3 worldRotation;
    glm::vec3 worldScale;
    glm::quat worldQuat;
    glm::mat4 worldMatrix;

    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    Object* parent;

private:

    BBox bbox;

    std::vector<Object*> children;
};

}

#endif /* OBJECT_HPP */

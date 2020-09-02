#include "Group.hpp"
#include <iostream>

namespace mode7
{

Group::Group()
{

}

Group::~Group()
{
    for (auto& mesh : meshes)
    {
        //delete mesh;
    }
}

void Group::addMesh(Mesh* m)
{
    meshes.push_back(m);
    Object::addChild(m);
}

void Group::update()
{
    Object::update();
}

void Group::draw(Shader& s)
{
    for (auto& mesh : meshes)
    {
        mesh->draw(s);
    }
}

}
#include "Scene.hpp"

namespace mode7
{

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::addMesh(std::shared_ptr<Mesh> mesh)
{
    meshes.push_back(mesh);
    addChild(mesh.get());
    //mesh->parent = this;
}

Mesh* Scene::getMesh(unsigned int index)
{
    return meshes[index].get();
}

void Scene::draw(Shader& s)
{
    for (auto& e : meshes)
    {
        e->draw(s);
    }
}

}
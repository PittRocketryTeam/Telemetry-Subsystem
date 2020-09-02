#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include "Mesh.hpp"
#include "Shader.hpp"

namespace mode7
{

class Scene : public Object
{
public:

    Scene();
    ~Scene();

    void addMesh(std::shared_ptr<Mesh>);
    Mesh* getMesh(unsigned int);
    
    void draw(Shader&);

private:

    std::vector<std::shared_ptr<Mesh>> meshes;
};

}

#endif /* SCENE_HPP */
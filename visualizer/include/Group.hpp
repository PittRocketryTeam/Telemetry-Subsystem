#ifndef GROUP_HPP
#define GROUP_HPP

#include <vector>
#include "Object.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

namespace mode7
{

class Group : public Object
{
public:

    Group();
    ~Group();

    void addMesh(Mesh*);
    void update();
    void draw(Shader&);

private:

    std::vector<Mesh*> meshes;
};

}

#endif /* GROUP_HPP */
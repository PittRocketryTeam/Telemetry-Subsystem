#ifndef BBOX_HPP
#define BBOX_HPP

#include <glm/glm.hpp>

namespace mode7
{

class BBox
{
public:

    BBox();
    ~BBox();

    bool intersects(BBox&);
    bool intersects(glm::vec3);

    glm::vec3 pos;
    glm::vec3 dim;
};

}

#endif /* BBOX_HPP */

#include "BBox.hpp"

namespace mode7
{

BBox::BBox() :
    pos(0.0f),
    dim(0.0f)
{

}

BBox::~BBox()
{

}

bool BBox::intersects(BBox& b)
{
    glm::vec3 ao(0.0f);
    glm::vec3 bo(0.0f);

    ao[0] = pos[0] - (dim[0] / 2.0f);
    ao[1] = pos[1] - (dim[1] / 2.0f);
    ao[2] = pos[2] - (dim[2] / 2.0f);
    bo[0] = b.pos[0] - (b.dim[0] / 2.0f);
    bo[1] = b.pos[1] - (b.dim[1] / 2.0f);
    bo[2] = b.pos[2] - (b.dim[2] / 2.0f);

    bool out =
        ao[0] <= bo[0] + b.dim[0] && ao[0] + dim[0] > bo[0] &&
        ao[1] <= bo[1] + b.dim[1] && ao[1] + dim[1] > bo[1] &&
        ao[2] <= bo[2] + b.dim[2] && ao[2] + dim[2] > bo[2];

    return out;
}

bool BBox::intersects(glm::vec3 pt)
{
    BBox b;
    b.pos = pt;
    b.dim = glm::vec3(1.0f);
    return intersects(b);
}

}
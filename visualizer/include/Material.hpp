#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "gl.h"
#include "Texture.hpp"
#include <vector>
#include <cstdint>

namespace mode7
{

class Material
{
public:

    Material();
    virtual ~Material();

    void addMap(Texture);

    virtual Texture getMap(uint32_t);
    virtual uint32_t numMaps();

    int tile;

protected:

    std::vector<Texture> maps;
};

}

#endif /* MATERIAL_HPP */
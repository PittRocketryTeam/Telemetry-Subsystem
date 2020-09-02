#include "Material.hpp"

namespace mode7
{

Material::Material() :
    tile(1)
{

}

Material::~Material()
{

}

void Material::addMap(Texture map)
{
    maps.push_back(map);
}

Texture Material::getMap(uint32_t index)
{
    return maps[index];
}

uint32_t Material::numMaps()
{
    return maps.size();
}

}
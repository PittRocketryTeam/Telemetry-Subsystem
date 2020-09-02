#include "TexCache.hpp"
#include <map>
#include <iostream>

namespace mode7
{

static std::map<std::string, Texture> cache;

Texture TexCache::open(const std::string& fn, TexType type)
{
    if (cache.find(fn) == cache.end())
    {
        //std::cout << "miss: " << fn << std::endl;
        Texture tex;
        tex.open(fn, type);
        cache[fn] = tex;
        return tex;
    }

    //std::cout << "hit: " << fn << std::endl;

    return cache[fn];
}

}
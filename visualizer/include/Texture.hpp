#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "gl.h"
#include <string>
#include <cstdint>

namespace mode7
{

enum class TexType {DIFFUSE, SPECULAR, NORMAL, BUMP};

class Texture
{
public:

    Texture();
    ~Texture();

    void open(const std::string&, TexType);
    void fill(void*, int, int);
    uint32_t getId();
    TexType getType();

    inline void destroy()
    {
        if (id != -1)
        {
            glDeleteTextures(1, &id);
        }
        id = -1;
    }

    // static methods
    static unsigned int open(const std::string&);

private:

    TexType type;
    GLuint id;
};

}

#endif /* TEXTURE_HPP */

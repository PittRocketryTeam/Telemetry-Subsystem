#include "Mesh.hpp"
#include <iostream>

namespace mode7
{

Vertex::Vertex()
{

}

Vertex::~Vertex()
{
    
}

static const GLfloat plane_vertex_data[] = {
   -1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
   1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
   1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, -1.0f,
   -1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, -1.0f,
};

static const GLuint plane_index_data[] = {
    0, 1, 2,
    2, 3, 0,
};

Mesh::Mesh() :
    Object(),
    vao(0),
    vbo(0),
    ebo(0),
    elements(false),
    triangles(0),
    alt(nullptr)
{
}

Mesh::~Mesh()
{
    destroy();
}

void Mesh::setMaterial(Material& mat)
{
    material = mat;
}

void Mesh::createFromBuffer(const float* buffer, GLuint vertices)
{
    elements = false;
    triangles = vertices;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(float), buffer, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 3,
        GL_FLOAT, GL_FALSE,
        8 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2, 2,
        GL_FLOAT, GL_FALSE,
        8 * sizeof(float),
        (void*)(6 * sizeof(float))
    );
}

void Mesh::createFromShape(int shape)
{
    elements = true;
    const float* vertices = nullptr;
    const GLuint* indices = nullptr;
    int num_vertices;
    if (shape == PLANE)
    {
        vertices = plane_vertex_data;
        indices = plane_index_data;
        triangles = sizeof(plane_index_data);
        num_vertices = sizeof(plane_vertex_data);
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, num_vertices, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles * 3, indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3,
        GL_FLOAT, GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 3,
        GL_FLOAT, GL_FALSE,
        8 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2, 2,
        GL_FLOAT, GL_FALSE,
        8 * sizeof(float),
        (void*)(6 * sizeof(float))
    );
}

void Mesh::createFromArrays(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    elements = true;
    triangles = indices.size();

    destroy();

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3,
        GL_FLOAT, GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 3,
        GL_FLOAT, GL_FALSE,
        8 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2, 2,
        GL_FLOAT, GL_FALSE,
        8 * sizeof(float),
        (void*)(6 * sizeof(float))
    );
}

void Mesh::setAltShader(Shader& s)
{
    alt = &s;
}

void Mesh::drawTriangles()
{
    glBindVertexArray(vao);
    
    if (elements)
    {
        glDrawElements(GL_TRIANGLES, triangles, GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, triangles);
    }
    glBindVertexArray(0);
}

void Mesh::draw(Shader& s)
{
    s.use();

    s.setMaterial(material);
    s.setModel(*this);

    drawTriangles();
}

}

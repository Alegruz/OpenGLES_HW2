#ifndef HW2_OBJECT_H
#define HW2_OBJECT_H

#include "global.h"
#include "program.h"
#include "material.h"
#include "vertex.h"

class Object {
public:
    Object(Program* program, Material* material,
            const vector<Vertex>& vertices, const vector<Index>& indices);
    virtual ~Object();

    virtual void draw() const;

    mat4 worldMat;
    Material* material;
    vector<Vertex> vertices;
    vector<Index> indices;

private:
    Program* program;
    GLuint vbo, ibo;
    virtual void create(Program* program, Material* material);
    virtual void load(const vector<Vertex>& vertices, const vector<Index>& indices);
    virtual void destroy();
    virtual void tangent();
};

#endif //HW2_OBJECT_H

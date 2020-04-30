#include "object.h"

Object::Object(Program* program, Material* material,
        const vector<Vertex> &vertices, const vector<Index> &indices) {

    create(program, material);
    load(vertices, indices);
}

Object::~Object() {
    destroy();
}

void Object::create(Program* program, Material* material) {
    this->program = program;
    this->material = material;

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    if(vbo == 0 || ibo == 0)
        LOG_PRINT_ERROR("Fail to generate buffers");

    if (glGetUniformLocation(program->get(), "worldMat") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "worldMat");
}

void Object::load(const vector<Vertex> &vertices, const vector<Index> &indices) {
    LOG_PRINT_DEBUG("Load object data");

    this->vertices = vertices;
    this->indices = indices;

    tangent();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(),
            this->vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index) * this->indices.size(),
                 this->indices.data(), GL_STATIC_DRAW);
}


void Object::draw() const {
    if (material)
        material->update();

    GLint loc = glGetUniformLocation(program->get(), "worldMat");
    if (loc >= 0) glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(worldMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (const void *) offsetof(Vertex, pos));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (const void *) offsetof(Vertex, nor));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (const void *) offsetof(Vertex, tex));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (const void *) offsetof(Vertex, tan));

    // draw elements
    glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_SHORT, (const void *) 0);
}

void Object::destroy() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}


void Object::tangent() {
    LOG_PRINT_DEBUG("Calculate tangent");

    // initialize tangent to zero vector
    for (unsigned int i = 0; i < vertices.size(); i++) {
        vertices[i].tan = vec3(0.0f);
    }

    // calculate tangent
    for (unsigned int i = 0; i < indices.size(); i += 3) {

        // points in triangle
        Vertex& p0 = vertices[indices[i + 0]];
        Vertex& p1 = vertices[indices[i + 1]];
        Vertex& p2 = vertices[indices[i + 2]];

        // edge vector
        const vec3 q1 = p1.pos - p0.pos;
        const vec3 q2 = p2.pos - p0.pos;

        // texture coordinates difference
        const float u10 = p1.tex.s - p0.tex.s;
        const float v10 = p1.tex.t - p0.tex.t;
        const float u20 = p2.tex.s - p0.tex.s;
        const float v20 = p2.tex.t - p0.tex.t;

        // inverse of determinant
        const float invDet = 1.0f / (u10 * v20 - u20 * v10);

        // calculate tangent
        const vec3 tan = invDet * (v20 * q1 - v10 * q2);

        // sum tangent
        p0.tan += tan;
        p1.tan += tan;
        p2.tan += tan;
    }

    // normalize (average) tangent
    for (unsigned int i = 0; i < vertices.size(); i++) {
        vertices[i].tan = normalize(vertices[i].tan);
    }
}
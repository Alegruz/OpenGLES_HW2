#include "material.h"

Material::Material(Program* program,
        Texture* textureDiff, Texture* textureDissolve,
        vec3 specular, vec3 ambient, vec3 emissive, float shininess)
        : specular(specular), ambient(ambient), emissive(emissive), shininess(shininess), threshold(0.0f), displacement(0.0f) {
    create(program, textureDiff, textureDissolve);
}

Material::~Material() {

}

void Material::create(Program* program, Texture* textureDiff, Texture* textureDissolve) {
    LOG_PRINT_DEBUG("Create material");

    this->program = program;
    this->textureDiff = textureDiff;
    this->textureDissolve = textureDissolve;

    if (glGetUniformLocation(program->get(), "matSpec") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "matSpec");
    if (glGetUniformLocation(program->get(), "matAmbi") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "matAmbi");
    if (glGetUniformLocation(program->get(), "matEmit") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "matEmit");
    if (glGetUniformLocation(program->get(), "matSh") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "matSh");
    if (glGetUniformLocation(program->get(), "threshold") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "threshold");
    if (glGetUniformLocation(program->get(), "displacement") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "displacement");
}

void Material::update() const {
    if (textureDiff) textureDiff->update();
    if (textureDissolve) textureDissolve->update();

    GLint matSpecLoc = glGetUniformLocation(program->get(), "matSpec");
    GLint matAmbiLoc = glGetUniformLocation(program->get(), "matAmbi");
    GLint matEmitLoc = glGetUniformLocation(program->get(), "matEmit");
    GLint matShLoc = glGetUniformLocation(program->get(), "matSh");
    GLint thresholdLoc = glGetUniformLocation(program->get(), "threshold");
    GLint displacementLoc = glGetUniformLocation(program->get(), "displacement");

    if (matSpecLoc >= 0) glUniform3fv(matSpecLoc, 1, value_ptr(specular));
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "matSpec");
    if (matAmbiLoc >= 0) glUniform3fv(matAmbiLoc, 1, value_ptr(ambient));
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "matAmbi");
    if (matEmitLoc >= 0) glUniform3fv(matEmitLoc, 1, value_ptr(emissive));
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "matEmit");
    if (matShLoc >= 0) glUniform1f(matShLoc, shininess);
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "matSh");
    if (thresholdLoc >= 0) glUniform1f(thresholdLoc, threshold);
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "threshold");
    if (displacementLoc >= 0) glUniform1f(displacementLoc, displacement);
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "displacement");
}
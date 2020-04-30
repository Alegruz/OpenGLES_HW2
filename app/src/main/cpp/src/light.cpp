#include "light.h"

Light::Light(Program* program)
        : position(0.0f),
          attenuation{0.005f, 0.01f, 0.015f},
          diffuse(0.8f),
          specular(1.0f),
          ambient(0.05f) {

    create(program);
}

void Light::create(Program* program) {
    LOG_PRINT_DEBUG("Create light");

    this->program = program;
}

void Light::update() const {
}

LeftLight::LeftLight(Program *program)
        : Light(program) {

}

void LeftLight::create(Program *program) {
    Light::create(program);

    if (glGetUniformLocation(program->get(), "srcDiffL") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "srcDiffL");
    if (glGetUniformLocation(program->get(), "srcSpecL") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "srcSpecL");
    if (glGetUniformLocation(program->get(), "srcAmbiL") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "srcAmbiL");
    if (glGetUniformLocation(program->get(), "lightPosL") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "lightPosL");
    if (glGetUniformLocation(program->get(), "lightAttL") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "lightAttL");
}

void LeftLight::update() const {
    Light::update();

    // get uniform locations
    GLint srcDiffLoc = glGetUniformLocation(program->get(), "srcDiffL");
    GLint srcSpecLoc = glGetUniformLocation(program->get(), "srcSpecL");
    GLint srcAmbiLoc = glGetUniformLocation(program->get(), "srcAmbiL");
    GLint lightPosLoc = glGetUniformLocation(program->get(), "lightPosL");
    GLint lightAttLoc = glGetUniformLocation(program->get(), "lightAttL");

    // set uniform data
    if (srcDiffLoc >= 0) glUniform3fv(srcDiffLoc, 1, value_ptr(diffuse));
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "srcDiffL");
    if (srcSpecLoc >= 0) glUniform3fv(srcSpecLoc, 1, value_ptr(specular));
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "srcSpecL");
    if (srcAmbiLoc >= 0) glUniform3fv(srcAmbiLoc, 1, value_ptr(ambient));
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "srcAmbiL");
    if (lightPosLoc >= 0) glUniform3fv(lightPosLoc, 1, value_ptr(position));
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "lightPosL");
    if (lightAttLoc >= 0) glUniform1fv(lightAttLoc, 3, attenuation);
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "lightAttL");
}

RightLight::RightLight(Program *program)
        : Light(program) {
}

void RightLight::create(Program *program) {
    Light::create(program);

    if (glGetUniformLocation(program->get(), "srcDiffR") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "srcDiffR");
    if (glGetUniformLocation(program->get(), "srcSpecR") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "srcSpecR");
    if (glGetUniformLocation(program->get(), "srcAmbiR") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "srcAmbiR");
    if (glGetUniformLocation(program->get(), "lightPosR") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "lightPosR");
    if (glGetUniformLocation(program->get(), "lightAttR") < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s", "lightAttR");
}

void RightLight::update() const {
    Light::update();

    GLint srcDiffLoc = glGetUniformLocation(program->get(), "srcDiffR");
    GLint srcSpecLoc = glGetUniformLocation(program->get(), "srcSpecR");
    GLint srcAmbiLoc = glGetUniformLocation(program->get(), "srcAmbiR");
    GLint lightPosLoc = glGetUniformLocation(program->get(), "lightPosR");
    GLint lightAttLoc = glGetUniformLocation(program->get(), "lightAttR");

    if (srcDiffLoc >= 0) glUniform3fv(srcDiffLoc, 1, value_ptr(diffuse));
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "srcDiffR");
    if (srcSpecLoc >= 0) glUniform3fv(srcSpecLoc, 1, value_ptr(specular));
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "srcSpecR");
    if (srcAmbiLoc >= 0) glUniform3fv(srcAmbiLoc, 1, value_ptr(ambient));
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "srcAmbiR");
    if (lightPosLoc >= 0) glUniform3fv(lightPosLoc, 1, value_ptr(position));
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "lightPosR");
    if (lightAttLoc >= 0) glUniform1fv(lightAttLoc, 3, attenuation);
    else LOG_PRINT_ERROR("Fail to find uniform location: %s", "lightAttR");
}

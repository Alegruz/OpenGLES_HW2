#include "texture.h"

#include <fstream>

Texture::Texture(Program *program, const int number, const string name,
                 const vector<Texel> &data, const GLsizei size)
                 : id(0)
{
    create(program, number, name);
    load(data, size);
}
Texture::Texture(Program *program, const int number, const string name,
                 const std::string& fileName, const GLsizei size) {
    create(program, number, name);
    loadPNG(fileName, size);
}

Texture::~Texture() {
    destroy();
}

void Texture::create(Program* program, const int number, const string name) {
    LOG_PRINT_DEBUG("Create texture: %s", name.c_str());

    this->program = program;
    this->number = number;
    this->name = name;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &id);
    if (id == 0)
        LOG_PRINT_ERROR("Fail to generate texture: %s", this->name.c_str());


    if (glGetUniformLocation(program->get(), this->name.c_str()) < 0)
        LOG_PRINT_WARN("Fail to get uniform location: %s, %d", this->name.c_str(), glGetUniformLocation(program->get(), this->name.c_str()));
}

void Texture::load(const vector<Texel> &data, const GLsizei size) {
    LOG_PRINT_DEBUG("Load texture data");

    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    glGenerateMipmap(GL_TEXTURE_2D);
}
void Texture::loadPNG(const string& fileName, const GLsizei size) {
    LOG_PRINT_DEBUG("Load PNG texture data");

    std::vector<unsigned char> image;
    unsigned int width = 0;
    unsigned int height = 0;
//    unsigned int error = lodepng::decode(image, width, height, fileName);
//
//    if (error != 0)
//    {
//        return;
//    }
//
    size_t u2 = 1; while(u2 < width) u2 *= 2;
    size_t v2 = 1; while(v2 < height) v2 *= 2;

    // Make power of two version of the image.
    std::vector<unsigned char> image2(u2 * v2 * 4);
    for(size_t y = 0; y < height; y++) {
        for(size_t x = 0; x < width; x++) {
            for(size_t c = 0; c < 4; c++) {
                image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
            }
        }
    }

    std::ifstream file(fileName, std::ios::binary);
    if (file.fail())
    {
        LOG_PRINT_DEBUG("File input failure");
        return;
    }
    file.close();

    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(image2[0]));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::update() const {
    GLint textureLoc = glGetUniformLocation(program->get(), this->name.c_str());

    glActiveTexture((GLenum)(GL_TEXTURE0 + number));
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    if (textureLoc >= 0) glUniform1i(textureLoc, number);
    else LOG_PRINT_ERROR("Fail to get uniform location: %s, %d", this->name.c_str(), glGetUniformLocation(program->get(), this->name.c_str()));
}

void Texture::destroy() {
    LOG_PRINT_DEBUG("Destroy texture");
    glDeleteTextures(1, &id);
}


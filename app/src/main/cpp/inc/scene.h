#ifndef HW2_SCENE_H
#define HW2_SCENE_H

#include "global.h"
#include "program.h"
#include "camera.h"
#include "object.h"
#include "texture.h"
#include "material.h"
#include "light.h"

class Scene {
public:
    static void setup(AAssetManager* aAssetManager);
    static void screen(int width, int height);
    static void update(float deltaTime);

private:
    static Shader* vertexShader;
    static Shader* fragmentShader;
    static Program* program;
    static Camera* camera;
    static Object* teapot;
    static Texture* diffuse;
    static Texture* dissolve;
    static Material* material;
    static LeftLight* lightL;
    static RightLight* lightR;

    static void lightMovement(float deltaTime);

};

#endif //HW2_SCENE_H

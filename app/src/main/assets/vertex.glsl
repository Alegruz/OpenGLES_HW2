#version 300 es

uniform mat4 worldMat, viewMat, projMat;
uniform vec3 eyePos, lightPosL, lightPosR;
uniform float lightAttL[3], lightAttR[3];
uniform float displacement;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 tangent;

out vec3 v_normal;
out vec2 v_texCoord;
out vec3 v_view, v_lightL, v_lightR;
out float v_attL, v_attR;

void main() {

    // vertex displacement
    vec3 displacedPos = position;

    // world-space position
    vec3 worldPos = (worldMat * vec4(displacedPos, 1.0)).xyz;

    // world-space vertex normal
    v_normal = normalize(transpose(inverse(mat3(worldMat))) * normal);

    // view vector
    v_view = normalize(eyePos - worldPos);

    // light vectors
    // v_lightL = ;
    // v_lightR = ;

    // attenuations
    // float distL = ;
    // float distR = ;
    // v_attL = ;
    // v_attR = ;

    // texture coordinates
    v_texCoord = texCoord;

    // clip-space position
    gl_Position = projMat * viewMat * vec4(worldPos, 1.0);
}
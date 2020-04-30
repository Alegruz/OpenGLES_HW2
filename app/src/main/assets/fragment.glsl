#version 300 es

precision mediump float;

uniform sampler2D textureDiff;
uniform sampler2D textureDissolve;

uniform vec3 matSpec, matAmbi, matEmit;
uniform float matSh;
uniform vec3 srcDiffL, srcSpecL, srcAmbiL;
uniform vec3 srcDiffR, srcSpecR, srcAmbiR;
uniform float threshold;

in vec3 v_normal;
in vec2 v_texCoord;
in vec3 v_view, v_lightL, v_lightR;
in float v_attL, v_attR;

layout(location = 0) out vec4 fragColor;

void main() {

    vec3 color = texture(textureDiff, v_texCoord).rgb;

    // re-normalize unit vectors (normal, view, and light vectors)
    // vec3 normal = ;
    // vec3 view = ;
    // vec3 lightL = ;
    // vec3 lightR = ;

    // diffuse term
    // vec3 matDiff = ;
    // vec3 diffL = ;
    // vec3 diffR = ;
    // vec3 diff = ;

    // specular term
    // vec3 reflL = ;
    // vec3 reflR = ;
    // vec3 specL = ;
    // vec3 specR = ;
    // vec3 spec = ;

    // ambient term
    // vec3 ambiL = ;
    // vec3 ambiR = ;
    // vec3 ambi = ;

    // color = ;

    float alpha = 1.0f;

    // dissolving
    // float dissolve = ;
    // if (dissolve < threshold)
    //    alpha = 0.0;

    // final output color with alpha
    fragColor = vec4(color, alpha);
}
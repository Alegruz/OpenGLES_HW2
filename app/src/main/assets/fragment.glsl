#version 300 es

precision mediump float;

uniform sampler2D textureDiff;
uniform sampler2D textureDissolve;

uniform vec3 matSpec, matAmbi, matEmit;
uniform float matSh;
uniform vec3 srcDiffL, srcSpecL, srcAmbiL;
uniform vec3 srcDiffR, srcSpecR, srcAmbiR;
uniform float threshold;

//in vec3 v_normal;
in vec2 v_texCoord;
in vec3 v_view, v_lightL, v_lightR;
in float v_attL, v_attR;
in vec3 v_diffL, v_diffR;
in vec3 v_reflL, v_reflR;

layout(location = 0) out vec4 fragColor;

void main()
{
    // re-normalize unit vectors (normal, view, and light vectors)
//    vec3 normal = normalize( v_normal );
    vec3 view = normalize( v_view );
    vec3 lightL = normalize( v_lightL );
    vec3 lightR = normalize( v_lightR );
    vec3 reflL = normalize( v_reflL );
    vec3 reflR = normalize( v_reflR );

    // diffuse term
    vec4 albedo = texture( textureDiff, v_texCoord );
//    vec3 diffL = max( v_diffL, 0.0 ) * srcDiffL * matDiff;
//    vec3 diffR = max( v_diffR, 0.0 ) * srcDiffR * matDiff;
    vec3 diffL = max( v_diffL, 0.0 ) * srcDiffL;
    vec3 diffR = max( v_diffR, 0.0 ) * srcDiffR;
    vec3 diff = clamp( (diffL + diffR) * albedo.xyz, 0.0, 1.0 );

    // specular term
//    vec3 reflL = 2.0 * normal * dot( normal, lightL ) - lightL;
//    vec3 reflR = 2.0 * normal * dot( normal, lightR ) - lightR;

    vec3 specL = pow( clamp( max( dot( reflL, -view ), 0.0), 0.0, 1.0 ), matSh ) * srcSpecL;
    vec3 specR = pow( clamp( max( dot( reflR, -view ), 0.0), 0.0, 1.0 ), matSh ) * srcSpecR;
//    float specularValueL = clamp( dot( reflL, -view ), 0.0, 1.0 );
//    float specularValueR = clamp( dot( reflR, -view ), 0.0, 1.0 );
//    vec3 spec = vec3( specularValueL + specularValueR );
    vec3 spec = ( specL + specR ) * matSpec;

    // ambient term
    vec3 ambiL = srcAmbiL;
    vec3 ambiR = srcAmbiR;
    vec3 ambi = ( ambiL + ambiR ) * matAmbi;

    float alpha = 1.0f;

    // dissolving
    // float dissolve = ;
    // if (dissolve < threshold)
    //    alpha = 0.0;

    // final output color with alpha
    fragColor = vec4(diff + spec + ambi + matEmit, alpha);
}
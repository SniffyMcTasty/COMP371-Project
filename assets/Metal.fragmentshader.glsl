#version 330 core

// Interpolated values from the vertex shaders
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform vec3 LightPosition_worldspace;
uniform vec3 LightColor;
uniform float LightIntensity;
uniform vec3 diffuse_color;
uniform vec3 ambient_color;
uniform vec3 specular_color;
uniform float shininess;
uniform float custom_property;

const float PI = 3.14159265359;

// Perlin noise function
float noise(vec3 p) {
    vec3 i = floor(p);
    vec3 f = fract(p);
    vec3 u = f*f*(3.0-2.0*f);
    return mix(mix(mix(dot(vec3(0,0,0), f - vec3(0,0,0)),
    dot(vec3(1,0,0), f - vec3(1,0,0)), u.x),
    mix(dot(vec3(0,1,0), f - vec3(0,1,0)),
    dot(vec3(1,1,0), f - vec3(1,1,0)), u.x), u.y),
    mix(mix(dot(vec3(0,0,1), f - vec3(0,0,1)),
    dot(vec3(1,0,1), f - vec3(1,0,1)), u.x),
    mix(dot(vec3(0,1,1), f - vec3(0,1,1)),
    dot(vec3(1,1,1), f - vec3(1,1,1)), u.x), u.y), u.z);
}

void main() {
    // Declare inner uniform modifiers
    float inner_shininess = shininess;
    if (inner_shininess > 1.0) inner_shininess = 1.0;
    else if (inner_shininess <= 0.0) inner_shininess = 0.001;
    float roughness = custom_property;

    // Compute surface normal
    vec3 n = normalize(Normal_cameraspace);

    // Compute surface roughness using Perlin noise
    roughness = noise(Position_worldspace * (50 - 40 * roughness)) * inner_shininess*0.1;

    // Compute specular lighting using the Cook-Torrance model
    vec3 l = normalize(LightDirection_cameraspace);
    vec3 v = normalize(EyeDirection_cameraspace);
    vec3 h = normalize(l + v);
    float NdotH = clamp(abs(dot(n, h)), 0, 1);
    float NdotL = clamp(abs(dot(n, l)), 0, 1);
    float NdotV = clamp(abs(dot(n, v)), 0, 1);
    float VdotH = clamp(abs(dot(v, h)), 0, 1);
    float D = (1.0 / (4.0 * roughness * roughness * pow(NdotH, 4.0))) * exp((NdotH * NdotH - 1.0) / (roughness * roughness * NdotH * NdotH));
    float G = min(1.0, min(2.0 * NdotH * NdotV / VdotH, 2.0 * NdotH * NdotL / VdotH));
    float F = pow(1.0 - VdotH, 5.0);
    F *= 0.2;
    F += 0.8;
    float specular = D * G * F / (4.0 * NdotL * NdotV);

    // Compute diffuse lighting
    float diffuse = NdotL;

    // Add some ambient lighting
    color = ambient_color;

    // Compute final color
    color += diffuse_color * diffuse * LightColor * LightIntensity + LightColor * LightIntensity * specular_color * (0.2 + specular * 0.8);
}
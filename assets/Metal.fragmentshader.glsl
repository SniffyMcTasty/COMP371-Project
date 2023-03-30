#version 330 core

// Interpolated values from the vertex shaders
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform vec3 LightPosition_worldspace;
uniform vec3 diffuse_color;

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

    float shininess = 0.5;
    if (shininess > 1.0) shininess = 1.0;
    else if (shininess <= 0.0) shininess = 0.001;
    float roughness = 0.5;
    if (roughness > 1.0) roughness = 1.0;
    else if (roughness < 0.0) roughness = 0.0;

    // Light emission properties
    // You probably want to put them as uniforms
    vec3 LightColor = vec3(1,1,1);
    float LightPower = 1.0f;

    // Compute surface normal
    vec3 n = normalize(Normal_cameraspace);

    // Compute surface roughness using Perlin noise
    roughness = noise(Position_worldspace * (50 - 40 * roughness)) * shininess*0.1;

    // Compute specular lighting using the Cook-Torrance model
    vec3 l = normalize(LightDirection_cameraspace);
    vec3 v = normalize(EyeDirection_cameraspace);
    vec3 h = normalize(l + v);
    float NdotH = max(0.0, abs(dot(n, h)));
    float NdotL = max(0.0, abs(dot(n, l)));
    float NdotV = max(0.0, abs(dot(n, v)));
    float VdotH = max(0.0, abs(dot(v, h)));
    // Microfacet distribution function by Beckman
    float D = (1.0 / (4.0 * roughness * roughness * pow(NdotH, 4.0))) * exp((NdotH * NdotH - 1.0) / (roughness * roughness * NdotH * NdotH));
    float G = min(1.0, min(2.0 * NdotH * NdotV / VdotH, 2.0 * NdotH * NdotL / VdotH));
    float F = pow(1.0 - VdotH, 5.0);
    F *= 0.2;
    F += 0.8;
    float specular = D * G * F / (4.0 * NdotL * NdotV);

    // Compute diffuse lighting
    float diffuse = NdotL;

    // Add some ambient lighting
    color = vec3(0.1, 0.1, 0.1) * diffuse_color;

    // Compute final color
    color += diffuse_color * diffuse * LightColor + LightColor * vec3(0.3,0.3,0.3) * (0.2 + specular * 0.8);
}
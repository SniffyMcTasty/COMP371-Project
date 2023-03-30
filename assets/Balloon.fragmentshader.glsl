#version 330 core

// Interpolated values from the vertex shaders
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform mat4 MV;
uniform vec3 LightPosition_worldspace;
uniform vec3 LightColor;
uniform float LightIntensity;
uniform vec3 diffuse_color;
uniform vec3 ambient_color;
uniform vec3 specular_color;
uniform float shininess;

void main() {
    // Compute the cosTheta angle
    float cosTheta = dot(Normal_cameraspace, normalize(LightDirection_cameraspace));

    // Clamp cosTheta from 0 to 1
    cosTheta = clamp(abs(cosTheta), 0, 1);

    // Intensity is the same for all colors
    vec3 result = diffuse_color * cosTheta * LightIntensity * LightColor;

    // Add some ambient
    result += ambient_color;

    // Send the color to the GPU
    color = result;

    // Add some specular
    float specular = dot(Normal_cameraspace, normalize(LightDirection_cameraspace + EyeDirection_cameraspace));
    specular = clamp(abs(specular), 0, 1);
    int minShininess = 3;
    specular = pow(specular, minShininess - shininess * minShininess + 0.001);
    color += specular_color * specular * LightIntensity * LightColor;
}
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
uniform vec3 diffuse_color;

void main() {

    // Compute the intensity
    vec3 lightDirection = normalize(LightPosition_worldspace - Position_worldspace);
    float intensity = dot(Normal_cameraspace, lightDirection);

    // Clamp intensity from 0 to 1
    intensity = clamp(abs(intensity), 0, 1);

    // Intensity is the same for all colors
    vec3 result = diffuse_color * intensity;

    // Add some ambient
    result += vec3(0.1, 0.1, 0.1);

    // Send the color to the GPU
    color = result;

    // Add some specular
    float specular = dot(Normal_cameraspace, normalize(LightDirection_cameraspace + EyeDirection_cameraspace));
    specular = clamp(abs(specular), 0, 1);
    specular = pow(specular, 4);
    color += vec3(0.3, 0.3, 0.3) * specular;
}
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
uniform vec3 diffuse_color;
//uniform float shininess;
//uniform float reflection;
//uniform float roughness;
uniform samplerCube skybox;

// Schlick approximation for the fresnel effect
vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

void main() {
    float shininess = 0.0;
    float reflection = 0.0;
    float roughness = 0.0;

    // Normalize cameraspace normal
    vec3 Normal_cameraspace_normalized = normalize(Normal_cameraspace);

    // Compute the intensity
    float intensity = dot(Normal_cameraspace_normalized, normalize(LightDirection_cameraspace));

    // If the normal and the light direction are not opposite to each other
    // then we must clamp the intensity to 0.0
    intensity = clamp(intensity, 0.0, 1.0);

    // Compute the color
    vec3 diffuse = diffuse_color * intensity;

    // Compute the reflection vector
    vec3 reflectDir = reflect(-normalize(EyeDirection_cameraspace), Normal_cameraspace_normalized);

    // Compute the fresnel factor using Schlick's approximation
    vec3 F0 = vec3(0.04);
    vec3 fresnel = fresnelSchlick(clamp(dot(reflectDir, EyeDirection_cameraspace), 0.0, 1.0), F0);

    // Compute the reflection color
    vec3 reflectionColor = vec3(0.0);
    if (reflection > 0.0) {
        reflectionColor = texture(skybox, reflectDir).rgb;
        reflectionColor = mix(vec3(1.0), reflectionColor, reflection);
    }

    // Mix the reflection and diffuse color based on roughness
    color = mix(diffuse, reflectionColor, pow(1.0 - roughness, 2.0));

    // Add some specular
    float specular = pow(clamp(dot(Normal_cameraspace_normalized, normalize(LightDirection_cameraspace + EyeDirection_cameraspace)), 0.0, 1.0), shininess);
    color += vec3(1.0) * specular * fresnel;
}

#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;

// Output data ; will be interpolated for each fragment.
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform vec3 LightPosition_worldspace;
uniform float custom_property;

// Balloon vertex shader main function
void main(){

    float inflation = custom_property;

    // Apply balloon-like transformation to the vertex position
    vec3 vertexPosition = vertexPosition_modelspace;
    vertexPosition += vertexNormal_modelspace * 0.1 * inflation;

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  MVP * vec4(vertexPosition,1);

    // Position of the vertex, in worldspace : M * position
    Position_worldspace = (vec4(vertexPosition,1)).xyz;

    // Vector that goes from the vertex to the camera, in worldspace.
    // In camera space, the camera is at the origin (0,0,0).
    vec3 Position_cameraspace = (V * vec4(Position_worldspace,1)).xyz;
    EyeDirection_cameraspace = vec3(0,0,0) - Position_cameraspace;

    // Vector that goes from the vertex to the light, in worldspace : MV * position - lightposition
    vec3 LightPosition_cameraspace = (V * vec4(LightPosition_worldspace,1)).xyz;
    LightDirection_cameraspace = EyeDirection_cameraspace;

    // Normal of the vertex, in camera space.
    Normal_cameraspace = mat3(transpose(inverse(V))) * vertexNormal_modelspace;
}
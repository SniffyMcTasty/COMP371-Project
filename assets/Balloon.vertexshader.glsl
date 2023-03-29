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

// Balloon vertex shader main function
void main(){

    // Apply balloon-like transformation to the vertex position
    vec3 vertexPosition = vertexPosition_modelspace;
    vertexPosition.x = vertexPosition.x + vertexNormal_modelspace.x * 0.1;
    vertexPosition.y = vertexPosition.y + vertexNormal_modelspace.y * 0.1;
    vertexPosition.z = vertexPosition.z + vertexNormal_modelspace.z * 0.1;

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  MVP * vec4(vertexPosition,1);

    // Position of the vertex, in worldspace : M * position
    vec4 vertexPosition_worldspace = V * vec4(vertexPosition,1);
    Position_worldspace = vertexPosition_worldspace.xyz;

    // Vector that goes from the vertex to the light, in worldspace : MV * position - lightposition
    vec3 LightPosition_cameraspace = (V * vec4(LightPosition_worldspace,1)).xyz;
    LightDirection_cameraspace = LightPosition_cameraspace - Position_worldspace;

    // Vector that goes from the vertex to the camera, in worldspace.
    // In camera space, the camera is at the origin (0,0,0).
    EyeDirection_cameraspace = vec3(0,0,0) - Position_worldspace;

    // Normal of the vertex, in camera space.
    Normal_cameraspace = mat3(transpose(inverse(V))) * vertexNormal_modelspace;
}
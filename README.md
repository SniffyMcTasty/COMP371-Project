# COMP371 Project

## Mockup

![alt text](https://github.com/SniffyMcTasty/COMP371-Project/blob/master/images/Mockup.png)

## Objectives

1. Create UI for user selection
2. Create a metallic shader
3. Create a toon shader shader
4. Create a balloon shader
5. Allow user to load custom shader

### Objective 1

This objective will be accomplished using the ImGui library to create a user interface: https://github.com/ocornut/imgui

The UI will allow the user to choose any kind of model that is compatible with the ASSIMP library that will be used to load the models: https://github.com/assimp/assimp.
The base code used for the intergration of models using ASSIMP is from OGLDEV's Youtube tutorial:
- https://www.youtube.com/watch?v=sP_kiODC25Q
- https://github.com/emeiri/ogldev/tree/master/tutorial18_youtube

The UI will also allow the user to load their own shader from the `shaders` folder in the JSON format.
The option to select the shader will be done during their respective objective, but since objectives are also considered milestones, being able to load shaders from JSON format
and changing its properties will be done during objective 5 as the last milestone.

### Objectives 2, 3 and 4

Since this project is mostly shader-oriented, 3 base shaders will be hardcoded into the program first and the selector will be 3 radio buttons while implementing them.
The selector will be changed later into objective 5 into a dropdown menu linked to a folder inside the code's directory.

### Objective 5

This objective refers to how every JSON-formatted shader will allow the user to modify the properties.
This means that properties subject to change will need to be coded as having an initial value and a range.

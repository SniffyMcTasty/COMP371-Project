#ifndef TOGLAPP_H
#define TOGLAPP_H


// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "TOGLWindow.h"
#include "Virtual3DLayer.h"
#include "RenderModel.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_glfw.h"
#include "NFDextended/src/include/nfd.h"

namespace TAPP {

    
    
class TOGLApp {
public:

    
    bool initialize_libraries();

    // this calls also initialize_libraries
    bool initialize(int& w, int& h,  std::string name);


    void run();
    
    bool release();
    
    
    // for now a single window
    TOGLWindow m_window;
    
    
    static void mouse_button_event(GLFWwindow * window, int button, int action, int mods);
    static void keyboard_button_event(GLFWwindow *, int inputKey, int b, int action, int d);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void resize_callback(GLFWwindow* window, int wx, int wyy);
    
    static bool gbutton, ctrlbutton; /* true if some button pressed */
    static int gmods;
    static double gx;
    static double gy;

    string vertexShaderInit = "../assets/Phong.vertexshader.glsl", fragmentShaderInit = "../assets/Phong.fragmentshader.glsl";
    string filenameInit = "teapot1", vsNameInit = "Phong.vertexshader", fsNameInit = "Phong.fragmentshader";
    glm::float32 shininessInit = 0.5, customPropertyInit = 0.5;
    glm::vec3 lightPosInit = glm::vec3(0,0,0), lightColorInit = glm::vec3(1,1,1);
    glm::float32 lightIntensityInit = 1.0;
    glm::vec3 diffuseColorInit = glm::vec3(1, 0, 0), ambientColorInit = glm::vec3(0.1, 0.1, 0.1) * diffuseColorInit, specularColorInit = glm::vec3(0.3, 0.3, 0.3);
    glm::float32 diffuseIntensityInit = 1.0, ambientIntensityInit = 0.1, specularIntensityInit = 0.3;
    
};


extern TOGLApp gapp;


}// namespace

#endif // TOGLAPP_H

#include <iostream>
#include "TOGLApp.h"

using namespace std;

namespace TAPP {

    TOGLApp gapp;
    
    bool TOGLApp::initialize(int& w, int& h,  std::string name){
        
        
        if (!glfwInit())
        {
            fprintf(stderr, "Failed to initialize GLFW\n");
            getchar();
            return false;
        }

        
        m_window.create(w, h, name);
        
        
        glfwSetMouseButtonCallback(m_window.m_window, TOGLApp::mouse_button_event);
        glfwSetKeyCallback(m_window.m_window, TOGLApp::keyboard_button_event);
        glfwSetCursorPosCallback(m_window.m_window, TOGLApp::cursor_position_callback);
        glfwSetScrollCallback(m_window.m_window, TOGLApp::scroll_callback);
        glfwSetWindowSizeCallback(m_window.m_window, TOGLApp::resize_callback);

        // Setup ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui_ImplGlfw_InitForOpenGL(m_window.m_window, true);
        ImGui_ImplOpenGL3_Init();
        ImGui::StyleColorsDark();
        io.FontAllowUserScaling = true;
        
        glewExperimental = true; // Needed for core profile
        if (glewInit() != GLEW_OK) {
            cout<<"Step B1.2"<<endl;
            fprintf(stderr, "Failed to initialize GLEW\n");
            getchar();
            glfwTerminate();
            return false;
        }


        
        return true;
        
    }
   
    void TOGLApp::run(){

        string vertexShader = vertexShaderInit, fragmentShader = fragmentShaderInit;
        m_window.init(vertexShader, fragmentShader);
        string filename = filenameInit, vsName = vsNameInit, fsName = fsNameInit;
        glm::float32 shininess = shininessInit, customProperty = customPropertyInit;
        glm::vec3 lightPos = lightPosInit, lightColor = lightColorInit;
        glm::float32 lightIntensity = lightIntensityInit;
        glm::vec3 diffuseColor = diffuseColorInit, ambientColor = ambientColorInit, specularColor = specularColorInit;
        glm::float32 diffuseIntensity = diffuseIntensityInit, ambientIntensity = ambientIntensityInit, specularIntensity = specularIntensityInit;

        do {
            glfwPollEvents();
            if(m_window.isSleeping) continue;
            glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Start new ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            for(int i=0;i<m_window.m_layers.size();++i){
                m_window.m_layers[i]->render(shininess, customProperty,
                                             lightPos, lightColor, lightIntensity,
                                             diffuseColor,ambientColor, specularColor,
                                             ambientIntensity, diffuseIntensity, specularIntensity);
            }

            // Model selection window
            ImGui::Begin("Model selection");
            ImGui::Text(filename.c_str());
            if (ImGui::Button("Browse")) {
                NFD_Init();
                nfdchar_t *outPath;
                nfdfilteritem_t filter[1] = {{"Object file", "obj"}};
                nfdresult_t result = NFD_OpenDialog(&outPath, filter, 1, NULL);
                if(result == NFD_OKAY) {
                    // Load file
                    puts("Success");
                    puts(outPath);
                    string temp = outPath;

                    // Render model
                    Virtual3DLayer* view = (Virtual3DLayer*) m_window.m_layers.at(0);
                    RenderModel* sp = new RenderModel(temp);
                    view->m_objects.clear();
                    view->m_objects.push_back(sp);
                    m_window.init(vertexShader, fragmentShader);

                    // Change name of shown file
                    char *p = strtok(outPath, "\\");
                    while(p != NULL) {
                        temp = p;
                        p = strtok(NULL, "\\");
                    }
                    filename = temp.substr(0, temp.length() - 4);
                    free(outPath);
                } else if(result == NFD_CANCEL) {
                    puts("User cancelled");
                } else {
                    printf("Error: %s\n", NFD_GetError());
                }
                NFD_Quit();
            }
            ImGui::SameLine();
            if (ImGui::Button("Reset")) filename = filenameInit;
            ImGui::End();

            // Shaders selection window
            ImGui::Begin("Shader selection");
            ImGui::Text(vsName.c_str());
            ImGui::Text(fsName.c_str());
            if (ImGui::Button("Browse")) {
                NFD_Init();
                nfdchar_t *outPath;
                nfdfilteritem_t filter[1] = {{"GLSL vertex shader", "vertexshader.glsl"}};
                nfdresult_t result = NFD_OpenDialog(&outPath, filter, 1, NULL);
                if(result == NFD_OKAY) {
                    // Load file
                    puts("Success");
                    puts(outPath);
                    string temp = outPath;

                    vertexShader = temp;

                    // Change name of shown file
                    char *p = strtok(outPath, "\\");
                    while(p != NULL) {
                        temp = p;
                        p = strtok(NULL, "\\");
                    }
                    vsName = temp.substr(0, temp.length() - 5);
                    free(outPath);
                } else if(result == NFD_CANCEL) {
                    puts("User cancelled");
                } else {
                    printf("Error: %s\n", NFD_GetError());
                }
                NFD_Quit();
                if (result != NFD_CANCEL && result != NFD_ERROR) {
                    NFD_Init();
                    filter[0] = {"GLSL file", "fragmentshader.glsl"};
                    result = NFD_OpenDialog(&outPath, filter, 1, NULL);
                    if (result == NFD_OKAY) {
                        // Load file
                        puts("Success");
                        puts(outPath);
                        string temp = outPath;

                        fragmentShader = temp;

                        // Change name of shown file
                        char *p = strtok(outPath, "\\");
                        while (p != NULL) {
                            temp = p;
                            p = strtok(NULL, "\\");
                        }
                        fsName = temp.substr(0, temp.length() - 5);
                        free(outPath);
                    } else if (result == NFD_CANCEL) {
                        puts("User cancelled");
                    } else {
                        printf("Error: %s\n", NFD_GetError());
                    }
                    NFD_Quit();
                    if (result != NFD_CANCEL && result != NFD_ERROR) {
                        m_window.init(vertexShader, fragmentShader);
                    }
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Reset")) {
                vertexShader = vsNameInit;
                fragmentShader = fsNameInit;
                m_window.init(vertexShader, fragmentShader);
            }
            ImGui::End();

            // Property sliders window
            ImGui::Begin("Properties");
            ImGui::SliderFloat("Shininess", &shininess, 0.001f, 1.0f);
            ImGui::SliderFloat("Custom property", &customProperty, 0.0f, 1.0f);
            if (ImGui::Button("Reset")) {
                shininess = shininessInit;
                customProperty = customPropertyInit;
            }
            ImGui::End();

            // Light properties window
            ImGui::Begin("Light properties");
            ImGui::SliderFloat3("Light position", &lightPos[0], -10.0f, 10.0f);
            ImGui::ColorEdit3("Light color", &lightColor[0]);
            ImGui::SliderFloat("Light intensity", &lightIntensity, 0.0f, 1.0f);
            if (ImGui::Button("Reset")) {
                lightPos = lightPosInit;
                lightColor = lightColorInit;
                lightIntensity = lightIntensityInit;
            }
            ImGui::End();

            // Object colors window
            ImGui::Begin("Object colors");
            ImGui::ColorEdit3("Ambient color", &ambientColor[0]);
            ImGui::ColorEdit3("Diffuse color", &diffuseColor[0]);
            ImGui::ColorEdit3("Specular color", &specularColor[0]);
            if (ImGui::Button("Reset")) {
                ambientColor = ambientColorInit;
                diffuseColor = diffuseColorInit;
                specularColor = specularColorInit;
            }
            ImGui::End();

            // Color intensity window
            ImGui::Begin("Color intensity");
            ImGui::SliderFloat("Ambient intensity", &ambientIntensity, 0.0f, 1.0f);
            ImGui::SliderFloat("Diffuse intensity", &diffuseIntensity, 0.0f, 1.0f);
            ImGui::SliderFloat("Specular intensity", &specularIntensity, 0.0f, 1.0f);
            if (ImGui::Button("Reset")) {
                ambientIntensity = ambientIntensityInit;
                diffuseIntensity = diffuseIntensityInit;
                specularIntensity = specularIntensityInit;
            }
            ImGui::End();

            // Render ImGui
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwGetFramebufferSize(m_window.m_window, &m_window.m_width, &m_window.m_height);
            glViewport(0, 0, m_window.m_width, m_window.m_height);
            glfwSwapBuffers(m_window.m_window);
            
        } // Check if the ESC key was pressed or the window was closed
        while (glfwGetKey(m_window.m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
               glfwWindowShouldClose(m_window.m_window) == 0);
        
        
    }
    
    
    bool TOGLApp::release(){

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwTerminate();

        return true;
    }
    
    
    // callbacks
    bool TOGLApp::gbutton=false;
    bool TOGLApp::ctrlbutton=false;
    int TOGLApp::gmods=0; /* same as glfw */
    double TOGLApp::gx = 0;
    double TOGLApp::gy = 0;
    
    
     void TOGLApp::mouse_button_event(GLFWwindow * window, int button, int action, int mods){
        
        gmods = mods;
        
        if(action==GLFW_PRESS){
            
//            gbutton = true;
//
//            if(button==GLFW_MOUSE_BUTTON_LEFT){
//                gapp.m_window.grab(gx, gy, 0, mods);
//            } else if(button==GLFW_MOUSE_BUTTON_RIGHT){
//                gapp.m_window.grab(gx, gy, 1, mods);
//            } else if(button==GLFW_MOUSE_BUTTON_MIDDLE){
//                gapp.m_window.grab(gx, gy, 2, mods);
//            } else {
//                cout<<"What button? "<<button<<endl;
//            }
            if(button==GLFW_MOUSE_BUTTON_RIGHT){
                gbutton = true;
                gapp.m_window.grab(gx, gy, 1, mods);
            } else {
                cout<<"What button? "<<button<<endl;
            }
        } else if(action==GLFW_RELEASE){
            
            
            gbutton = false;
            
            gapp.m_window.release(mods);
            
            if(button==GLFW_MOUSE_BUTTON_LEFT){
                
            } else if(button==GLFW_MOUSE_BUTTON_RIGHT){
                
            } else if(button==GLFW_MOUSE_BUTTON_MIDDLE){
                
            } else {
                cout<<"What button? "<<button<<endl;
            }

        } else {
            cout<<"What action? "<<action<<endl;
        }
        
     }
    
    
     void TOGLApp::keyboard_button_event(GLFWwindow *, int inputKey, int b, int action, int d){

         if(action == GLFW_PRESS) {
             if (inputKey == GLFW_KEY_LEFT_CONTROL) {
                 ctrlbutton = true;
                 gapp.m_window.keypress(inputKey, action, d);
             }
         } else if (action == GLFW_RELEASE) {
             if (inputKey == GLFW_KEY_LEFT_CONTROL) {
                 ctrlbutton = false;
             }
         }
        
    }
    
    
     void TOGLApp::cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
        gx = xpos;
        gy = ypos;
        
        // cout<<"Debug MP: "<<gx<<" "<<gy<<endl;
         
        // any button depressed
        if(gbutton){
            gapp.m_window.drag(gx, gy, gmods);
        } else {
            gapp.m_window.hover(gx, gy, gmods);
        }
        
     }
    
    
    void TOGLApp::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
        if(!ctrlbutton) {
            gapp.m_window.scroll(yoffset);
        }
    }
    
    
    void TOGLApp::resize_callback(GLFWwindow* window, int wx, int wy){
        gapp.m_window.resize(wx, wy);
        gapp.m_window.isSleeping = wx == 0 || wy == 0;
    }
    
};  // namespace


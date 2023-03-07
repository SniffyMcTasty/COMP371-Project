#include <iostream>
#include "TOGLApp.h"

#include "Virtual3DLayer.h"

#include "RenderModel.h"

#include "Text.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_glfw.h"

using namespace TAPP;
using namespace std;

std::string global_path;

int main(int argc, char* argv[]){

    if(argc!=2){
        cout<<"Usage: "<<argv[0]<<" objname.obj"<<endl;
        return -1;
    }
    
    int w = 1024;
    int h = 768;
    
    std::string name = "Shader Viewer";
    
    if(!gapp.initialize(w, h, name)){
        cout<<"Unable to initialize!"<<endl;
        return -1;
    }
    
    Virtual3DLayer* view = new Virtual3DLayer(512, 384);
    gapp.m_window.m_layers.push_back(view);
    
    RenderModel* sp = new RenderModel(argv[1]);
   
    
    
    
    view->m_objects.push_back(sp);
    
   
/*
    Text* text = new Text();
    text->m_text = "Hello World!";
    text->m_x = 300;
    text->m_y = 300;
    text->m_size = 60;
    view->m_objects.push_back(text);
 */   

    // Setup ImGui
    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO();
    // ImGui_ImplGlfw_InitForOpenGL(gapp.m_window.m_window, true);
    // ImGui_ImplOpenGL3_Init();
    // ImGui::StyleColorsDark();
 
    gapp.run();
    
    //ImGui::DestroyContext();
    gapp.release();


	return 0;
}


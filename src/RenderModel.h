#ifndef VSPHERE_H
#define VSPHERE_H

#include <GL/glew.h>

#include "RUIObject.h"
#include <vector>


#include "ObjModel.h"



namespace TAPP {
    
    class RenderModel :public RUIObject {
    public:
        
        RenderModel()
        :RUIObject(){
        
    }
        
        RenderModel(std::string filename)
        :RUIObject(){
        
            Load(m_obj, filename.c_str());
        }
        
    
        
        // Uniform variables
        GLuint shaderMVP;
        GLuint shaderV;
        GLuint shaderLightPos;
        GLuint shaderLightColor;
        GLuint shaderLightIntensity;
        GLuint shaderDiffuse;//diffuse color
        GLuint shaderAmbient;//ambient color
        GLuint shaderSpecular;//specular color
        GLuint shaderDiffuseIntensity;//diffuse intensity
        GLuint shaderAmbientIntensity;//ambient intensity
        GLuint shaderSpecularIntensity;//specular intensity
        GLuint shaderShininess;//shininess
        GLuint shaderCustomProperty;//custom property

        
        // shader program
        GLuint program;
        void load_shader();
        
        
       // Geometric data buffers
        
        // vertex array
        unsigned int m_VAO;
        
        // vertex buffer
        unsigned int m_VBO;
        
        // normal buffer
        unsigned int m_NBO;
        
        // element buffer object - holds the triangle indices
        unsigned int m_EBO;
        
        void load_geometry();
        
        
        
        ObjModel m_obj;
        
        virtual void init(std::string vertexShader, std::string fragmentShader);
        virtual void release();
        virtual void hover(double  x, double y, int mods);
        virtual void grab(double x, double y, int b, int mods /* 0 left, 1 right, 2 middle*/);
        virtual void drag(double x, double y, int mods) ;
        virtual void resize(double x, double y);
        
        virtual void render(glm::float32 shininess, glm::float32 customProperty,
                            glm::vec3 lightPos, glm::vec3 lightColor, glm::float32 lightIntensity,
                            glm::vec3 diffuse, glm::vec3 ambient, glm::vec3 specular,
                            glm::float32 ambient_intensity, glm::float32 diffuse_intensity, glm::float32 specular_intensity) ;
        
        
        virtual void render_pick_select(PickDataback& ) ; // to see if we selected this object
        virtual void render_pick_detail(PickDataback& ); // to see if we selected a certain primitive
    
};


}
#endif // TOGLAPP_H

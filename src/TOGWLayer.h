#ifndef TOGLWLAYER_H
#define TOGLWLAYER_H

#include <string>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/intersect.hpp>

namespace TAPP {

class TOGWLayer {
public:
    
    
    TOGWLayer(int w, int h)
        :m_width(w), m_height(h){
        
    }
    
    int m_width, m_height;
    
    virtual void init(int w, int h, std::string vertexShader, std::string fragmentShader) = 0;
    virtual void hover(double  x, double y, int mods)=0;
    virtual void grab(double x, double y, int b, int mods /* 0 left, 1 right, 2 middle*/)=0;
    virtual void drag(double x, double y, int mods)=0;
    virtual void scroll(double y)=0;
    virtual void release(int mods)=0;
    
    virtual void keypress(int key, int state, int mods)=0;
    
    
    virtual void resize(int w, int h)=0;
    virtual void render(glm::float32 shininess, glm::float32 customProperty) = 0;

    
};

}// namespace

#endif // TOGLAPP_H

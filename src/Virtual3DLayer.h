#ifndef VIRTUAL_VIEW_G_H
#define VIRTUAL_VIEW_G_H

#include <vector>

#include "TOGWLayer.h"
#include "RUIObject.h"
#include "TCamera.h"


namespace TAPP {

    class Virtual3DLayer : public TOGWLayer {
    public:
        
        Virtual3DLayer(int w, int h)
            :TOGWLayer(w, h){
                action_state = 0;
                m_camera.Resize(w, h);
            }
    
        TCamera m_camera;
    
        int action_state;// 0 = browsing, 1 - measuring

        
        std::vector<RUIObject*> m_objects;
    
        virtual void init(int w, int h, std::string vertexShader, std::string fragmentShader);
        virtual void hover(double  x, double y, int mods);
        virtual void grab(double x, double y, int b, int mods /* 0 left, 1 right, 2 middle*/);
        virtual void drag(double x, double y, int mods);
        virtual void scroll(double y);

        virtual void keypress(int key, int state, int mods);

        virtual void render(glm::float32 shininess, glm::float32 customProperty, glm::vec3 lightPos, glm::vec3 lightColor, glm::float32 lightIntensity);
        virtual void release(int mods);
        virtual void resize(int w, int h);
        
        
        double cx, cy;
        
        // utils
        void compute_ray(double x, double y, glm::vec3& origin, glm::vec3& direction);

        
        PickDataback tmp;
        
};


}
#endif // TOGLAPP_H

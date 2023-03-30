#include <iostream>

#include "RenderModel.h"

#include "GLUtils.h"

#include "ObjModel.h"

#include "GLUtils.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace std;
using namespace T3D;

namespace TAPP {

   
    void RenderModel::hover(double  x, double y, int mods){
        
        
    }
    void RenderModel::grab(double x, double y, int b, int mods /* 0 left, 1 right, 2 middle*/){
        
        
    }
    
    
    void RenderModel::drag(double x, double y, int mods) {
        
        
    }
    
    
    void RenderModel::resize(double x, double y){
        
        
    }
    
    void RenderModel::load_geometry(){
        
        std::vector<float> vertices, normals;
        //
        
        if(m_obj.vertex.size()!=m_obj.normal.size()){
            cout<<"Error normal vs vertices! "<<m_obj.vertex.size()<<" "<<m_obj.normal.size()<<endl;
            return;
        }
        
        for(int i=0;i<m_obj.vertex.size();++i){
            for(int j=0;j<3;++j){
                vertices.push_back(m_obj.vertex[i][j]);
                normals.push_back(m_obj.normal[i][j]);
               // vertices[3*i+j] = m_obj.vertex[i][j];
               // normals[3*i+j] = m_obj.normal[i][j];
            }
        }
        
    //    cout<<"Mesh has: "<<vertices.size()/3<<": vertices!"<<endl;
        
        std::vector<unsigned int> indices;
      //  unsigned int* indices = new unsigned int[m_obj.faces.size()*3];
        
        for(int i=0;i<m_obj.faces.size();++i){
            if(m_obj.faces[i].size()!=3){
                cout<<"Error: not a triangular mesh!"<<endl;
                return;
            }
            for(int j=0;j<3;++j){
                indices.push_back(m_obj.faces[i][j]);
           //     indices[3*i+j] = m_obj.faces[i][j];
            }
        }
        
    //    cout<<"Mesh has: "<<indices.size()/3<<": faces!"<<endl;

        
        // 0 - create the vertex array object
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
        
        
        cout<<"Szies: "<<sizeof(vertices)<<" "<<sizeof(normals)<<" "<<sizeof(indices)<<" "<<sizeof(unsigned int)<<" "<<sizeof(float)<<endl;
        
        // create the vertex buffer object -- first entry in the renderer
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);
        
        glGenBuffers(1, &m_NBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_NBO);
        glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(float), &normals[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        
        
        // element array buffer
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    // Load a single texture from a file and return its texture ID
    GLuint loadTexture(const char* filename)
    {
        int width, height, channels;
        unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(image);

        return textureID;
    }

    // Load a skybox texture from 6 files and return its texture ID
    GLuint loadSkyboxTexture(const char* colorFilename, const char* displacementFilename,
                             const char* metalnessFilename, const char* normalDXFilename,
                             const char* normalGLFilename, const char* roughnessFilename)
    {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        // Load each face of the cube map
        GLuint faces[] = {
                GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
        };

        for (int i = 0; i < 6; i++)
        {
            GLuint textureFaceID;
            switch (i)
            {
                case 0: textureFaceID = loadTexture(colorFilename); break;
                case 1: textureFaceID = loadTexture(displacementFilename); break;
                case 2: textureFaceID = loadTexture(metalnessFilename); break;
                case 3: textureFaceID = loadTexture(normalDXFilename); break;
                case 4: textureFaceID = loadTexture(normalGLFilename); break;
                case 5: textureFaceID = loadTexture(roughnessFilename); break;
            }

            GLint w, h, format;
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);
            unsigned char* pixels = new unsigned char[w * h * 4];
            glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
            glTexImage2D(faces[i], 0, format, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            delete[] pixels;
            glDeleteTextures(1, &textureFaceID);
        }

        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

        return textureID;
    }



    void RenderModel::init(std::string vertexShader, std::string fragmentShader){
        is_error();
        
        
        cout<<"Load geomertry!"<<endl;
        
        // need to generate new normals because sometimes I might have different normals and this is a problem when rendering
        m_obj.Triangulate();
        m_obj.GenerateNormals(1);
        load_geometry();
    
        cout<<"Load shaders!"<<endl;

        program = LoadShaders( vertexShader.c_str(), fragmentShader.c_str());
       
        if(is_error(true)){
            cout<<"Err 00"<<endl;
        }
        
       // load uniforms
       
        // Get a handle for our "MVP" uniform
        shaderMVP = glGetUniformLocation(program, "MVP");
        shaderV = glGetUniformLocation(program, "V");
        shaderLight = glGetUniformLocation(program, "LightPosition_worldspace");
        shaderDiffuse = glGetUniformLocation(program, "diffuse_color");

        // Load the cube map texture
        GLuint textureID = loadSkyboxTexture("../assets/metal/Metal009_2K_Color.png",
                                             "../assets/metal/Metal009_2K_Displacement.png",
                                             "../assets/metal/Metal009_2K_Metalness.png",
                                             "../assets/metal/Metal009_2K_NormalDX.png",
                                             "../assets/metal/Metal009_2K_NormalGL.png",
                                             "../assets/metal/Metal009_2K_Roughness.png");

        // Load the cube map texture into OpenGL
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        // Set the texture wrapping/filtering options
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        if(is_error()){
            cout<<"Err B"<<endl;
        }
        
    }
    
    
    void RenderModel::release(){
        
    //    cout<<"Do I ger hre! 34"<<endl;
        
        /*
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteBuffers(1, &uvbuffer);
        glDeleteBuffers(1, &normalbuffer);
        glDeleteProgram(programID);
        glDeleteTextures(1, &Texture);
        glDeleteVertexArrays(1, &VertexArrayID);
         */
    }
    

void RenderModel::render(){
    
  //  render_general(0);

   render_general(0);

}



    void RenderModel::render_general(int mode){
        
        glDisable(GL_CULL_FACE); 
        
        
        if(is_error()){
            cout<<"Err B1"<<endl;
        }
        
         //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
         glEnable(GL_DEPTH_TEST);
      
        if(is_error()){
            cout<<"Err B1_2"<<endl;
        }
        
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

        glUseProgram(program);
    //    cout<<"render"<<endl;
        
        if(is_error()){
            cout<<"Err B2"<<endl;
        }
        
        
        glm::mat4 MVP = m_ProjMatrix * m_ViewMatrix;

        
#if 0
        std::cout<<"X "<<endl;
        for (int i = 0; i<4; ++i){
            for (int j = 0; j<4; ++j){
                std::cout << m_ProjMatrix[i][j] << " ";
          //      std::cout <<   m_ViewMatrix[i][j]<<" ";
            }
        }
        std::cout << std::endl;
#endif
        
        if(is_error()){
            cout<<"Err B3"<<endl;
        }
        
        glm::vec3 lightPos = glm::vec3(0,0,0);
        glm::vec3 dc = glm::vec3(1, 0, 0);
        if(mode==0){
            glUniformMatrix4fv(shaderMVP, 1, GL_FALSE, &MVP[0][0]);
            glUniformMatrix4fv(shaderV, 1, GL_FALSE, &m_ViewMatrix[0][0]);
            glUniform3f(shaderDiffuse, dc.x, dc.y, dc.z);
            glUniform3f(shaderLight, lightPos.x, lightPos.y, lightPos.z);
            // Bind the texture to a uniform variable in the shader
            glUniform1i(glGetUniformLocation(program, "skybox"), 0); // 0 = texture unit 0
        }
       
        if(is_error()){
            cout<<"Err 3"<<endl;
        }
        
        if(mode==1){
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        } else {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        }
    
        glDrawElements(GL_TRIANGLES, m_obj.faces.size()*3, GL_UNSIGNED_INT, 0);
        
        if(is_error()){
            cout<<"Err 343"<<endl;
        }
        
    }
    void RenderModel::render_pick_select(PickDataback& ) { // to see if we selected this object
        
        
        
        
    }
    
    
    
    void RenderModel::render_pick_detail(PickDataback& pd){ // to see if we selected a certain primitive
        
        // this is wrong
        glm::vec3 origin = pd.origin;
        
      //  cout<<"O: "<<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<" "<<endl;
        
        
        glm::vec3 dir = pd.dir;
        
        float b_u, b_v, b_w, b_z; //bary coordiante
        
        for (int i = 0; i < m_obj.faces.size(); i++)
        {
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec2> textures;
            for (int j = 0; j < m_obj.faces[i].size(); j++)
            {
                TPoint P = m_obj.vertex[m_obj.faces[i][j]];
                TVector txt = m_obj.texture[m_obj.txfaces[i][j]];
                glm::vec2 uv(txt[0], txt[1]);
                glm::vec3 vertex(P[0], P[1], P[2]);
                vertices.push_back(vertex);
                textures.push_back(uv);
            }
            
            //		for(int k = 0;k<3;k++){
            //		vertices[k] = convert(vertices[k]);
            //		}
            glm::vec2 barytemp;
            glm::vec3 bary;
            float distance;
            //   std::cout<<"Do I get here?"<<std::endl;
            
            // Hack
            bool hit = glm::intersectRayTriangle(origin, dir, vertices[0], vertices[1], vertices[2], barytemp, distance);
            
            bary[0] = barytemp[0];
            bary[1] = barytemp[1];
            bary[2] = 0;
            
            
            pd.bHit = 0;
            
            if (hit)
            {
                
                pd.bHit = 1;
                
                std::vector<glm::vec2>  uvs;
                uvs = textures;
                
                glm::vec2 p_uv = uvs[0]*(1 - bary.x - bary.y)  + uvs[1]*bary.x + uvs[2]*bary.y;
                glm::vec2 tmp;
                tmp[0] = (1 - bary.x - bary.y) * uvs[0][0] + bary.x*uvs[1][0]+bary.y*uvs[2][0];
                tmp[1] = (1 - bary.x - bary.y) * uvs[0][1] + bary.x*uvs[1][1]+bary.y*uvs[2][1];
                
                
                // HACK
                int ww = 0;//txt_width;
                int hh = 0;//txt_height;
                
                pd.P2d[0] = p_uv[0]* ww;
                pd.P2d[1] = (1-p_uv[1])*hh;
                
          //      printf("P_UV tmp: %f,%f\n", p_uv[0]* ww, (1-p_uv[1])*hh);
           //     printf("P_UV: %f,%f\n", p_uv[0],p_uv[1]);
                
                glm::vec3 cartesian = vertices[0] * (1 - bary.x - bary.y)
                + vertices[1] * bary.x + vertices[2] * bary.y;
                
                pd.P3d = cartesian;
            }
        }

    }// end of picking function
    
}

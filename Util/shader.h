/*
    Instituto de Ciencias Matemáticas e de Computação - ICMC
    Disciplina: Computação Gráfica
    Estudante: Érica Ribeiro - nUSP: 11836351
*/


#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>  
#include <GLFW/glfw3.h> 
#include <iostream>
#include <unordered_map> 

using namespace std; 
  
struct shaderProgramSource{   
    string vertexSource;  
    string fragmentSource;
};

class shader{ 
    private:
        string m_filepath; 
        unsigned int m_RendererID;
        unordered_map<string, unsigned int> m_UniformLocationCache;
    public:
        shader (const string &filepath);
        ~shader ();

        void bind() const;
        void unbind() const;
 

        //definir uniforms
        void setUniform4f(const string &name, float v0, float v1, float v2, float v3);
        void setUniformMatrix4fv(const string &name, float matriz[16]);

    private:
        shaderProgramSource parseShader(const string &filepath);
        unsigned int compileShader(int type, const string &source);
        unsigned int createShader(const string &vertexShader, const string &fragShader);

        unsigned int getUniformLocation(const string &name);        
};

#endif
/*
    Instituto de Ciencias Matemáticas e de Computação - ICMC
    Disciplina: Computação Gráfica
    Estudante: Érica Ribeiro - nUSP: 11836351
*/

#ifndef VERTEXARRAYLAYOUT_H_
#define VERTEXARRAYLAYOUT_H_

#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
 
using namespace std; 


struct vertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type){
        switch(type){
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
    }
};

class vertexBufferLayout{
    private:
        vector<vertexBufferElement> m_Elements;
        unsigned int m_Stride;
    public:
        vertexBufferLayout()
            : m_Stride(0){}

        template<typename T>
        void Push ( unsigned int count){
            m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
            m_Stride += count * vertexBufferElement::getSizeOfType(GL_FLOAT);
        }

        inline const vector<vertexBufferElement> getElements() const {return m_Elements;}
        inline unsigned int getStride() const {return m_Stride;}

};

#endif

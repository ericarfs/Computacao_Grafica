/*
    Instituto de Ciencias Matemáticas e de Computação - ICMC
    Disciplina: Computação Gráfica
    Estudante: Érica Ribeiro - nUSP: 11836351
*/

#ifndef BUFFERS_H_
#define BUFFERS_H_

#include <GL/glew.h>  
#include <GLFW/glfw3.h>

class vertexBuffer{
    private:
        unsigned int m_RendererID;

    public:
        vertexBuffer(const void *data, unsigned int size);
        ~vertexBuffer();

        void bind() const;
        void unbind() const;

};

class indexBuffer{
    private:
        unsigned int m_RendererID;
        unsigned int m_Count; 

    public:
        indexBuffer(const unsigned int *data, unsigned int count);
        ~indexBuffer(); 

        void bind() const;
        void unbind() const;
        inline unsigned int getCount() const { return m_Count; }
};

#endif


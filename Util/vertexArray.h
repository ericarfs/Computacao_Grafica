/*
    Instituto de Ciencias Matemáticas e de Computação - ICMC
    Disciplina: Computação Gráfica
    Estudante: Érica Ribeiro - nUSP: 11836351
*/

#ifndef VERTEXARRAY_H_
#define VERTEXARRAY_H_

#include "vertexBufferLayout.h" 
#include "buffers.h" 

class vertexArray{
    private:
        unsigned int m_RendererID;

    public:
        vertexArray();
        ~vertexArray();

        void addBuffer(const vertexBuffer &vb, const vertexBufferLayout &layout);

        void bind() const;
        void unbind() const;
};

#endif
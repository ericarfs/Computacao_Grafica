/*
    Instituto de Ciencias Matemáticas e de Computação - ICMC
    Disciplina: Computação Gráfica
    Estudante: Érica Ribeiro - nUSP: 11836351
*/

#include "vertexArray.h"

 
vertexArray::vertexArray(){
    glGenVertexArrays(1, &m_RendererID);
}

vertexArray::~vertexArray(){
    glDeleteVertexArrays(1, &m_RendererID);
}

void vertexArray::bind() const {
    glBindVertexArray(m_RendererID);
}

void vertexArray::unbind() const {
    glBindVertexArray(0);
}


void vertexArray::addBuffer(const vertexBuffer &vb, const vertexBufferLayout &layout){
    bind();
    vb.bind();
    const auto &elements = layout.getElements();
    unsigned long offset = 0;
    for(unsigned int i=0; i < elements.size(); i++){
        const auto &element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*) offset);
        offset+=element.count * vertexBufferElement::getSizeOfType(element.type);
    }
}
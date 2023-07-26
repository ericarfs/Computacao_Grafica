/*
    Instituto de Ciencias Matemáticas e de Computação - ICMC
    Disciplina: Computação Gráfica
    Estudante: Érica Ribeiro - nUSP: 11836351
*/


#include "buffers.h"

vertexBuffer::vertexBuffer(const void *data, unsigned int size){
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

    // Abaixo, nós enviamos todo o conteúdo da variável vertices.
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}
 
vertexBuffer::~vertexBuffer(){
    glDeleteBuffers(1, &m_RendererID);
    
}

void vertexBuffer::bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    
}

void vertexBuffer::unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
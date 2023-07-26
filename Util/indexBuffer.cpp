/*
    Instituto de Ciencias Matemáticas e de Computação - ICMC
    Disciplina: Computação Gráfica
    Estudante: Érica Ribeiro - nUSP: 11836351
*/

#include "buffers.h"
#include <assert.h>

indexBuffer::indexBuffer(const unsigned int *data, unsigned int count)
    :m_Count(count)
{
    assert(sizeof(unsigned int) == sizeof(GLint));

    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    // Abaixo, nós enviamos todo o conteúdo da variável vertices.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_DYNAMIC_DRAW);
}

indexBuffer::~indexBuffer(){
    glDeleteBuffers(1, &m_RendererID);
    
}

void indexBuffer::bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    
}

void indexBuffer::unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
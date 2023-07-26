/*
    Instituto de Ciencias Matemáticas e de Computação - ICMC
    Disciplina: Computação Gráfica
    Estudante: Érica Ribeiro - nUSP: 11836351
*/

#ifndef GERARMATRIZ_H_
#define GERARMATRIZ_H_

#include <stdio.h>

void getMatrizTransformacao(float t_x, float t_ty, float angulo, float s_x, float s_y, float m_resultado[16]);
void multiplica(float m1[16], float m2[16], float m3[16], float m_resultado[16]);

#endif //GERARMATRIZ_H_


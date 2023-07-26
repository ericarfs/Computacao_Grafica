/*
    Instituto de Ciencias Matemáticas e de Computação - ICMC
    Disciplina: Computação Gráfica
    Estudante: Érica Ribeiro - nUSP: 11836351
*/

#include "gerarMatriz.h"
#include <cmath>


void getMatrizTransformacao(float t_x, float t_y,float angulo, float s_x, float s_y, float m_resultado[16]){

    float mat_translation[16] = {
        1.0f, 0.0f, 0.0f, t_x,
        0.0f, 1.0f, 0.0f, t_y,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };  

    float c = 1.0f; // armazenar cosseno (da matriz de rotacao)
    float s = 0.0f; 
 
    // definindo a matriz de rotacao (na realidade eh um vetor, mas o OpenGl processa como matriz 4x4)
    c = cos( ((angulo) * M_PI / 180.0) ); // cos considerando conversao para radianos
    s = sin( ((angulo) * M_PI / 180.0) );

    float mat_rotation[16] = {
        c   , -s  , 0.0f, 0.0f,
        s   ,  c  , 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    float mat_scaling[16] = {
         s_x, 0.0f, 0.0f, 0.0f,
        0.0f,  s_y, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };  

    multiplica(mat_translation,mat_rotation,mat_scaling, m_resultado);

}



// funcao para multiplicar duas "matrizes 4x4" (na realidade sao vetores de 16 elementos) 
void multiplica(float m1[16], float m2[16], float m3[16], float m_resultado[16]){

    // OpenGL lida recebe vetores de 16 elementos e interpreta como matrizes 4x4.
    // Nessa funcao, transformamos as matrizes de volta para float[4][4] para facilitar a multiplicacao

    float m_a[4][4];
    float m_b[4][4];
    float m_c[4][4]; 
    float m_d[4][4]; // m_d = m_a * m_b
    float m_e[4][4]; // m_e = m_d * m_c

    int n = 0;
    for(int i=0; i < 4; i++){
        for(int j=0; j < 4; j++){
            m_a[i][j] = m1[n];
            m_b[i][j] = m2[n];
            m_c[i][j] = m3[n];
            n += 1;
        }
    }


    for(int i=0;i<4;i++){    
        for(int j=0;j<4;j++){
            m_d[i][j]=0.0;
            for(int k=0; k < 4; k++){
                m_d[i][j] += m_a[i][k]*m_b[k][j];    
            }
        }
    }

    for(int i=0;i<4;i++){    
        for(int j=0;j<4;j++){
            m_e[i][j]=0.0;
            for(int k=0; k < 4; k++){
                m_e[i][j] += m_c[i][k]*m_d[k][j];    
            }
        }
    }

    // voltando a resposta para o formato do OpenGL
    n = 0;
    for(int i=0; i < 4; i++){
        for(int j=0; j < 4; j++){
            m_resultado[n] = m_e[i][j];
            n += 1;
        }
    }

}
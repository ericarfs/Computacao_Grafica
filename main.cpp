/*
    Instituto de Ciencias Matemáticas e de Computação - ICMC
    Disciplina: Computação Gráfica
    Estudante: Érica Ribeiro - nUSP: 11836351
*/


#include <GL/glew.h>  

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
 
#include "Util/vertexArray.h"  
#include "Util/shader.h" 
#include "Util/gerarMatriz.h"

using namespace std;
 
//movimento de translação do jogador
float t_x_jogador = 0.0f; 
float t_y_jogador = 0.0f;

//angulo do catavento
float angulo_catavento = 0.0f;

//Fatores de transformação do objeto 1
float t_x_obj1 = -0.7f; 
float t_y_obj1 = 0.6f;
float s_x_obj1 = 1.2f; 
float s_y_obj1 = 1.2f;
float angulo_obj1 = 15.0f;

//Fatores de transformação do objeto 2
float t_x_obj2 = 0.4f; 
float t_y_obj2 = 0.4f;
float s_x_obj2 = 0.8f; 
float s_y_obj2 = 0.8f;
float angulo_obj2 = -125.0f;

//Fatores de transformação do objeto 3
float t_x_obj3 = 0.2f; 
float t_y_obj3 = -0.4f;
float s_x_obj3 = 1.22f; 
float s_y_obj3 = 1.22f;
float angulo_obj3 = 135.0f;

//Fatores de transformação do objeto 4
float t_x_obj4 = -0.9f; 
float t_y_obj4 = -1.2f;
float s_x_obj4 = 0.62f; 
float s_y_obj4 = 0.62f; 
float angulo_obj4 = -25.0f;

//variaveis que controlam se o objeto ta na posição correta
int objPosicionado1 = 0;
int objPosicionado2 = 0;
int objPosicionado3 = 0;
int objPosicionado4 = 0;

//variaveis que controlam se o objeto ta no angulo correto
int anguloCorreto1 = 0;
int anguloCorreto2 = 0;
int anguloCorreto3 = 0;
int anguloCorreto4 = 0;


//Função que verifica se o objeto está na posição correta
int verificarPosicaoObjeto(float t_x, float t_y,float s_x,float s_y, int anguloCorreto){    
    if(abs(t_x) >= 0.58f && abs(t_x) <= 0.61f && abs(t_y) >= 0.58f && abs(t_y) <= 0.61f && s_x >= 0.98f && s_x <= 1.04f && s_y >= 0.98f && s_y <= 1.04f && anguloCorreto==1){
        angulo_catavento -= 5.0;  
        return 1;
    }
        
    return 0;
}


//Função para movimentar os objetos na tela
void movimentarObjetos(float &t_x, float &t_y,float &s_x,float &s_y, float &angulo, int &objPosicionado, int key){
    if(objPosicionado == 0){
        if(key==68) t_x += 0.02; // tecla para direita  (d)
        if(key==65) t_x -= 0.02; // tecla para esquerda (a)
        
        if(key==87) t_y += 0.02; // tecla para cima  (w)
        if(key==83) t_y -= 0.02; // tecla para baixo (s)

        if(key==72) {
            s_y += 0.02;
            s_x += 0.02;  
        } //aumentar escala (h) 

        if(key==71) {
            s_y -= 0.02;
            s_x -= 0.02;  
            
        } //diminuir escala (g) 


        if(key==82) angulo+= 5.0; //girar para a esquerda (r)
        if(key==84) angulo-= 5.0; //girar para a direita  (t)

        if(angulo > 360.0) angulo -= 360.0;
        if(angulo < -360.0) angulo += 360.0;


    }   
    /* --------------------- */
}
 

//Função que desenha os objetos na tela
void drawObject(const shader &shader, const vertexArray &va, const indexBuffer &ib, int quantVertices){
    shader.bind();
    va.bind();
    ib.bind(); 

    glDrawElements(GL_TRIANGLES, quantVertices, GL_UNSIGNED_INT, NULL);
}


// Funcao para processar eventos de teclado
static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){
    printf("Pressionando tecla %d\n", key);

    //Se o botão de fechar for clicado
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){

        //Acionamos o comando que a Janela deve fechar
        glfwSetWindowShouldClose(window, true);
    }
    
    /* Movimentação do jogador */
    if(t_x_jogador<=0.92)
        if(key==262) t_x_jogador += 0.02; // tecla para direita
    if(t_x_jogador>=-0.92)
        if(key==263) t_x_jogador -= 0.02; // tecla para esquerda
    
   
    if(t_y_jogador<=1.88)
        if(key==265) t_y_jogador += 0.02; // tecla para cima
    if(t_y_jogador>=0.01)
        if(key==264) t_y_jogador -= 0.02; // tecla para baixo

    /* --- Movimentar objetos --- */
    //objeto 01
    if(t_x_jogador < -0.90 && t_y_jogador >= 1.88) {
        movimentarObjetos(t_x_obj1, t_y_obj1, s_x_obj1, s_y_obj1, angulo_obj1, objPosicionado1, key);
    }

    //objeto 02
    else if(t_x_jogador > 0.90 && t_y_jogador >= 1.88) {
        movimentarObjetos(t_x_obj2, t_y_obj2, s_x_obj2, s_y_obj2, angulo_obj2, objPosicionado2, key);
    }

    //objeto 03
    else if(t_x_jogador > 0.90 && t_y_jogador <= 0.06) {
        movimentarObjetos(t_x_obj3, t_y_obj3, s_x_obj3, s_y_obj3, angulo_obj3, objPosicionado3, key);
    }
    
    //objeto 04
    else if(t_x_jogador < -0.90 && t_y_jogador <= 0.06) {
        movimentarObjetos(t_x_obj4, t_y_obj4, s_x_obj4, s_y_obj4, angulo_obj4, objPosicionado4, key);
    }
    
    /* ---------------------- */

}



int main(void){
 
    // inicicializando o sistema de\ janelas
    glfwInit();

    
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    // deixando a janela invisivel, por enquanto
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // Informar qual versao do OpenGl vai ser usada, nesse caso a 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Informar que será utilizado o CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    // criando uma janela
    GLFWwindow* window = glfwCreateWindow(600, 600, "Minha Janela", NULL, NULL);

    
    // tornando a janela como principal 
    glfwMakeContextCurrent(window);

    // inicializando Glew (para lidar com funcoes OpenGL)
    GLint GlewInitResult = glewInit();
    cout << "GlewStatus: " << glewGetErrorString(GlewInitResult) << endl;

    //ler os shaders
    shader shader("basic.shaders");
    shader.bind();   


    //Definindo os vertices do catavento
    float catavento[] = { // criando vertices e preenchendo
        0.0f, 0.0f,

        //triangulo esquerdo
        -0.20f, 0.07f, 
        -0.20f, -0.07f,

        //triangulo inferior
        -0.07f,-0.20f,
        0.07f, -0.20f,

        //triangulo direito
        0.20f, -0.07f, 
        0.20f, 0.07f,

        //triangulo superior
        0.07f,0.20f,
        -0.07f, 0.20f,

    };

    unsigned int cataventoIndices[] = { // criando indices para a sequencia de vertices
        0, 1, 2, 
        3, 4, 0, 
        5, 6, 0, 
        7, 8, 0
    };


    //Definindo os vertices do jogador
    float jogador[] = { // criando vertices e preenchendo
        //tringulo do meio
         0.0f, -0.92f,
        -0.04f,-1.0f,
        0.04f, -1.0f,

        //triangulo esquerdo
        -0.04f,-0.96f,
        -0.02f,-0.97f,

        //triangulo direito
        0.04f,-0.96f,
        0.02f,-0.97f,

    };

    unsigned int jogadorIndices[] = { // criando indices para a sequencia de vertices
        0, 1, 2,
        1, 3, 4,
        2, 5, 6
    };

    
    //Definindo os vertices dos indicadores de posição
    float posicoes[] = { // criando vertices e preenchendo
        //triangulo superior esquerdo
        -1.0f, 1.0f,
        -1.0f, 0.93f,
        -0.93f, 1.0f,

        //triangulo superior direito
        1.0f, 1.0f,
        1.0f, 0.93f,
        0.93f, 1.0f,

        //triangulo inferior esquerdo
        -1.0f, -1.0f,
        -1.0f, -0.93f,
        -0.93f, -1.0f,

        //triangulo inferior direito
        1.0f, -1.0f,
        1.0f, -0.93f,
        0.93f, -1.0f,

        //quadrado de superior esquerdo
        -0.72f, 0.46f,
        -0.72f, 0.72f,
        -0.46f, 0.72f,
        -0.46f, 0.46f,

        //quadrado de superior direito
        0.72f, 0.46f,
        0.72f, 0.72f,
        0.46f, 0.72f,
        0.46f, 0.46f,

        //quadrado de inferior esquerdo
        -0.72f, -0.46f,
        -0.72f, -0.72f,
        -0.46f, -0.72f,
        -0.46f, -0.46f,

        //quadrado de inferior direito
        0.72f, -0.46f,
        0.72f, -0.72f,
        0.46f, -0.72f,
        0.46f, -0.46f,


    };

    unsigned int posicoesIndices[] = { // criando indices para a sequencia de vertices
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10,11,
        12, 13, 14,
        14, 15, 12,
        16, 17, 18,
        18, 19, 16,
        20, 21, 22,
        22, 23, 20,
        24, 25, 26,
        26, 27, 24,
    };


    //Definindo os vertices do objeto
    float objeto[] = { // criando vertices e preenchendo
        //triangulo do meio
        0.0f, 0.1f,
        -0.1f, -0.05f,
        0.1f, -0.05f,

        //retangulo debaixo
        -0.05f, -0.05f,
        -0.04f, -0.08f,
         0.04f, -0.08f,
         0.05f, -0.05f,

        //triangulo esquerdo
        -0.12f, 0.05f,
        -0.05f, 0.0f,

        //triangulo direito
        0.05f, 0.0f,
        0.12f, 0.05f,
    };

    unsigned int objetoIndices[] = { // criando indices para a sequencia de vertices
        0, 1, 2, 
        3, 4, 5, 
        3, 5, 6, 
        1, 7, 8, 
        2, 10, 9, 
    };

  
    vertexBuffer vbCatavento(catavento, 12*2*sizeof(float));
    vertexBuffer vbJogador(jogador, 9*2*sizeof(float));
    vertexBuffer vbPosicoes(posicoes, 36*2*sizeof(float));
    vertexBuffer vbObjeto(objeto, 15*2*sizeof(float));

    vertexBufferLayout layoutCatavento, layoutJogador, layoutPosicoes, layoutObjeto;
    layoutCatavento.Push<float>(2);
    layoutJogador.Push<float>(2);
    layoutPosicoes.Push<float>(2);
    layoutObjeto.Push<float>(2);

    vertexArray vaCatavento, vaJogador, vaPosicoes, vaObjeto;
    vaCatavento.addBuffer(vbCatavento, layoutCatavento);
    vaJogador.addBuffer(vbJogador, layoutJogador);
    vaPosicoes.addBuffer(vbPosicoes, layoutPosicoes);
    vaObjeto.addBuffer(vbObjeto, layoutObjeto);

    indexBuffer ibCatavento(cataventoIndices, 24);
    indexBuffer ibJogador(jogadorIndices, 18);
    indexBuffer ibPosicoes(posicoesIndices, 36);
    indexBuffer ibObjeto(objetoIndices, 15);
    
    vaCatavento.unbind();
    vbCatavento.unbind();
    ibCatavento.unbind();
    shader.unbind();

    vaJogador.unbind();
    vbJogador.unbind();
    ibJogador.unbind();
    shader.unbind();

    vaPosicoes.unbind();
    vbPosicoes.unbind();
    ibPosicoes.unbind();
    shader.unbind();

    vaObjeto.unbind();
    vbObjeto.unbind();
    ibObjeto.unbind();
    shader.unbind();


    // Associando nossa janela com eventos de teclado
    glfwSetKeyCallback(window, key_event); // teclado

    // Exibindo nossa janela
    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.8, 0.8, 0.8, 1.0);

        
        //verificar se os objetos tao no angulo correto
        if(angulo_obj1 == -135.0 || angulo_obj1 == 225.0) {
            anguloCorreto1 = 1;
        }
        else{
            anguloCorreto1 = 0;
        }
        if(angulo_obj2 == -225.0 || angulo_obj2 == 135.0) {
            anguloCorreto2 = 1;
        }
        else{
            anguloCorreto2 = 0;
        }
        if(angulo_obj3 ==   45.0 || angulo_obj3 == -315.0) {
            anguloCorreto3 = 1;
        }
        else{
            anguloCorreto3 = 0;
        }
        if(angulo_obj4 == -45.0 || angulo_obj4 == 315.0) {
            anguloCorreto4 = 1;
        }
        else{
            anguloCorreto4 = 0;
        }

        //verificar se os objetos estão na posição correta
        objPosicionado1 = verificarPosicaoObjeto(t_x_obj1, t_y_obj1, s_x_obj1, s_y_obj1, anguloCorreto1);
        objPosicionado2 = verificarPosicaoObjeto(t_x_obj2, t_y_obj2, s_x_obj2, s_y_obj2, anguloCorreto2);
        objPosicionado3 = verificarPosicaoObjeto(t_x_obj3, t_y_obj3, s_x_obj3, s_y_obj3, anguloCorreto3);
        objPosicionado4 = verificarPosicaoObjeto(t_x_obj4, t_y_obj4, s_x_obj4, s_y_obj4, anguloCorreto4);


        //Matriz de transformações dos indicadores de posição
        float matTransformationPosicoes[16] = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        };


       // multiplica(mat_translation,mat_rotation,mat_transformation);
        getMatrizTransformacao(0.0, 0.0, 0.0, 1.0, 1.0, matTransformationPosicoes);
        shader.setUniformMatrix4fv("mat_transformation", matTransformationPosicoes);
        shader.setUniform4f("u_Color", 0.9f,0.9f,0.9f,1.0f);  

        drawObject(shader, vaPosicoes, ibPosicoes, 36);

        
        //Matriz de transformação do catavento
        float matTransformationCatavento[16] = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        };
 
       // multiplica(mat_translation,mat_rotation,mat_transformation);
        getMatrizTransformacao(0.0, 0.0, angulo_catavento, 1.0, 1.0, matTransformationCatavento);
        shader.setUniformMatrix4fv("mat_transformation", matTransformationCatavento);
        shader.setUniform4f("u_Color", 1.0f,0.0f,0.0f,1.0f);  
        if(objPosicionado1 && objPosicionado2 && objPosicionado3 && objPosicionado4){
            angulo_catavento = 0;
            shader.setUniform4f("u_Color", 0.0f,1.0f,0.0f,1.0f);
        }
        else{
            angulo_catavento+=20;
        }

        drawObject(shader, vaCatavento, ibCatavento, 12);


        //Matriz de transformação do player
        float matTransformationJogador[16] = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        };

        
       // multiplica(mat_translation,mat_rotation,mat_transformation);
        getMatrizTransformacao(t_x_jogador, t_y_jogador, 0.0, 1.0, 1.0, matTransformationJogador);
        shader.setUniformMatrix4fv("mat_transformation", matTransformationJogador);
        shader.setUniform4f("u_Color", 0.5f,0.0f,1.0f,1.0f);          
            
        drawObject(shader, vaJogador, ibJogador, 9);


        //Matriz de transformação do objeto 01
        float matTransformationObjeto1[16] = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        };

        //Aplicar as transformações
        getMatrizTransformacao(t_x_obj1,t_y_obj1,angulo_obj1, s_x_obj1, s_y_obj1, matTransformationObjeto1);
        shader.setUniformMatrix4fv("mat_transformation", matTransformationObjeto1);
        shader.setUniform4f("u_Color", 1.0f,0.5f,0.5f,1.0f);  
        //se o objeto estiver no angulo correto
        if(anguloCorreto1)  shader.setUniform4f("u_Color", 0.9f,0.7f,0.3f,1.0f); 
        //se o objeto estiver na posicao correta, fica azul
        if(objPosicionado1) shader.setUniform4f("u_Color", 0.0f,0.0f,1.0f,1.0f);
        
        //desenhar o objeto 1
        drawObject(shader, vaObjeto, ibObjeto, 15);

        //Matriz de transformação do objeto 02
        float matTransformationObjeto2[16] = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        };

        //Aplicar as transformações
        getMatrizTransformacao(t_x_obj2,t_y_obj2,angulo_obj2, s_x_obj2, s_y_obj2, matTransformationObjeto2);
        shader.setUniformMatrix4fv("mat_transformation", matTransformationObjeto2);
        shader.setUniform4f("u_Color", 1.0f,0.5f,0.5f,1.0f); 
        //se o objeto estiver no angulo correto
        if(anguloCorreto2)  shader.setUniform4f("u_Color", 0.9f,0.7f,0.3f,1.0f);  
        //se o objeto estiver na posicao correta, fica azul
        if(objPosicionado2) shader.setUniform4f("u_Color", 0.0f,0.0f,1.0f,1.0f);

        //desenhar o objeto 2
        drawObject(shader, vaObjeto, ibObjeto, 15);

        //Matriz de transformação do objeto 03
        float matTransformationObjeto3[16] = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        };

        //Aplicar as transformações
        getMatrizTransformacao(t_x_obj3,t_y_obj3,angulo_obj3, s_x_obj3, s_y_obj3, matTransformationObjeto3);
        shader.setUniformMatrix4fv("mat_transformation", matTransformationObjeto3);
        shader.setUniform4f("u_Color", 1.0f,0.5f,0.5f,1.0f);
        //se o objeto estiver no angulo correto
        if(anguloCorreto3)  shader.setUniform4f("u_Color", 0.9f,0.7f,0.3f,1.0f); 
        //se o objeto estiver na posicao correta, fica azul 
        if(objPosicionado3) shader.setUniform4f("u_Color", 0.0f,0.0f,1.0f,1.0f);

        //desenhar o objeto 3
        drawObject(shader, vaObjeto, ibObjeto, 15);

        //Matriz de transformação do objeto 04
        float matTransformationObjeto4[16] = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        };

        //Aplicar as transformações
        getMatrizTransformacao(t_x_obj4,t_y_obj4,angulo_obj4, s_x_obj4, s_y_obj4, matTransformationObjeto4);
        shader.setUniformMatrix4fv("mat_transformation", matTransformationObjeto4);
        shader.setUniform4f("u_Color", 1.0f,0.5f,0.5f,1.0f);
        //se o objeto estiver no angulo correto
        if(anguloCorreto4)  shader.setUniform4f("u_Color", 0.9f,0.7f,0.3f,1.0f);  
        //se o objeto estiver na posicao correta, fica azul
        if(objPosicionado4) shader.setUniform4f("u_Color", 0.0f,0.0f,1.0f,1.0f);

        //desenhar o objeto 4
        drawObject(shader, vaObjeto, ibObjeto, 15);
 
        glfwSwapBuffers(window);
        
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);

    

    return 0;
}

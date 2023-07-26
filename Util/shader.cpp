/*
    Instituto de Ciencias Matemáticas e de Computação - ICMC
    Disciplina: Computação Gráfica
    Estudante: Érica Ribeiro - nUSP: 11836351
*/

#include "shader.h"
#include <GL/glew.h>  
#include <GLFW/glfw3.h> 
#include <fstream>  
#include <sstream>
#include <string>

shader::shader(const string &filepath)
    : m_filepath(filepath), m_RendererID(0)
{
     shaderProgramSource source = parseShader(filepath);
    // Requisitando slot para a GPU para nossos programas Vertex e Fragment Shaders
    m_RendererID = createShader(source.vertexSource, source.fragmentSource);
}

shader::~shader(){
   glDeleteProgram(m_RendererID);
}


 
shaderProgramSource shader::parseShader(const string &filepath){

    ifstream stream(filepath);

    enum class shaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    string line;
    stringstream ss[2];

    shaderType type = shaderType::NONE;

    while(getline(stream, line)){
        if(line.find("#shader") != string::npos){
            if(line.find("vertex") != string::npos){
                type = shaderType::VERTEX;
            }
            else if(line.find("fragment") != string::npos){
                type = shaderType::FRAGMENT;
            }
        }
        else{
            ss[(int)type] << line << '\n';
        }
    }

    return {ss[0].str(), ss[1].str()};

} 


// Função que compila os shaders necessários
unsigned int shader::compileShader(int type, const string &source){
    unsigned int id = -1;

    //verificar qual o tipo de shader a ser compilado
    if(type == 0){
        id = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (type == 1){
        id = glCreateShader(GL_FRAGMENT_SHADER);
    }
    
    // Associando nosso código-fonte GLSL aos slots solicitados
    const char* src = source.c_str(); 
    glShaderSource(id, 1, &src, NULL);

    // Compilando o  Shader e verificando erros
    glCompileShader(id);

    int isCompiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(id, infoLength, NULL, info);

        printf("Erro de compilacao no Shader.\n");
        printf("--> %s\n",info);

    }

    return id;
}

// Função que cria os shaders para o programa
unsigned int shader::createShader(const string &vertexShader, const string &fragShader){
 
    // Requisitando slot para a GPU para nossos programas Vertex e Fragment Shaders
    unsigned int program = glCreateProgram();
    unsigned int vertex = compileShader(0, vertexShader);
    unsigned int fragment = compileShader(1, fragShader);
    
    // Associando os programas compilado ao programa principal
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Linkagem do programa e definindo como default
    glLinkProgram(program); 
    glValidateProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    

    return program;

}

void shader::bind() const{
   glUseProgram(m_RendererID);    
}

void shader::unbind() const{
   glUseProgram(0);    
}

void shader::setUniform4f(const string &name, float v0, float v1, float v2, float v3){
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void shader::setUniformMatrix4fv(const string &name, float matriz[16]){
    // enviando a matriz de transformacao para a GPU
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_TRUE, matriz);
}

unsigned int shader::getUniformLocation(const string &name){

    if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end()){
        return m_UniformLocationCache[name];
    }

    unsigned int location = glGetUniformLocation(m_RendererID, name.c_str());
    if(location == -1.0){
        cout << "Uniform '" << name << "doesn't exists!" <<endl;
    }

    m_UniformLocationCache[name] = location;
    return location;
}
#pragma once

#include "glad.h"

#include "fstream"
#include "iostream"
#include "sstream"
#include "string"

using std::string;
class Shader {

public:
  unsigned int ID;

  Shader(string vertexPath, string fragmentPath) {
    string vertextCode, fragmentCode;
    std::ifstream vertexStream, fragmentStream;

    vertexStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::stringstream vertexStrStream, fragmentStrStream;
    vertexStream.open(vertexPath);
    fragmentStream.open(fragmentPath);
    vertexStrStream << vertexStream.rdbuf();
    fragmentStrStream << fragmentStream.rdbuf();

    vertextCode = vertexStrStream.str();
    fragmentCode = fragmentStrStream.str();
    const char *vertexCodeCSTR = vertextCode.c_str();
    const char *fragmentCodeCSTR = fragmentCode.c_str();

    ID = glCreateProgram();
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCodeCSTR, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader,"VERTEX");

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCodeCSTR, NULL);
    glCompileShader(fragmentShader);

    checkCompileErrors(fragmentShader,"FRAGMENT");

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    checkCompileErrors(ID,"PROGRAM");
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
  };

  void use(){
    glUseProgram(ID);
  }

  void setUniformBool(const string &name, bool value){
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
  }


  void setUniformInt(const string &name, int value){
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
  }

  void setUniformfloat(const string &name, float value){
    glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
  }

  private: 

    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

};

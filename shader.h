#pragma once

#include "glad.h"

#include "fstream"
#include "string"
#include "sstream"
#include "iostream"
using std::string;
class Shader
{

public:
    // program id
    unsigned int ID;
    // constructor for creation
    Shader(const char *vertexPath, const char *fragmentPath)
    {
        string vertexCode;
        string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (const std::ifstream::failure e)
        {
            std::cerr << e.what() << '\n';
        }
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;
        int success;
        char infoLog[512];
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "PROBLEM COMPILING" << infoLog << std::endl;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "PROBLEM SECOND F SHADER" << infoLog << std::endl;
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "PROBLEM LINKING" << infoLog << std::endl;
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    

    void use(){
        glUseProgram(ID);
    }
    void setBool(const string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
    }
    void setInt(const string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
    }
    void setFloat(const string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
    }
};

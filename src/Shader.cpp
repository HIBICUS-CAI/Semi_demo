//
// Created by 蔡元涵 on 2020/6/3.
//

#include "Shader.h"
#include "Texture.h"
#include <SDL.h>
#include <fstream>
#include <sstream>
#include <gtc/type_ptr.inl>

Shader::Shader() : mFragShader(0), mVertexShader(0), mShaderProgram(0)
{

}

Shader::~Shader()
{

}

bool Shader::CompileShader(const std::string &fileName, GLenum shaderType, GLuint &outShader)
{
    //读取文件
    std::ifstream shaderFile(fileName);
    if (shaderFile.is_open())
    {
        //读取所有流
        std::stringstream sstream;
        sstream << shaderFile.rdbuf();
        std::string contents = sstream.str();
        const char *contentsChar = contents.c_str();

        outShader = glCreateShader(shaderType);
        glShaderSource(outShader, 1, &(contentsChar), nullptr);
        glCompileShader(outShader);

        if (!IsCompiled(outShader))
        {
            SDL_Log("Failed to compile shader %s", fileName.c_str());

            return false;
        }
    } else
    {
        SDL_Log("Shader file not found: %s", fileName.c_str());

        return false;
    }

    return true;
}

bool Shader::IsCompiled(GLuint shader)
{
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        SDL_Log("Shader compile failed: %s", buffer);

        return false;
    }

    return true;
}

bool Shader::IsVaildProgram()
{
    GLint status;
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
        SDL_Log("Shader link failed:\n%s", buffer);

        return false;
    }

    return true;
}

bool Shader::Load(const std::string &vertName, const std::string &fragName)
{
    //编译顶点着色器和片段着色器
    if (!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader) ||
        !CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader))
    {
        return false;
    }

    //创建shader链接顶点片段着色器
    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, mVertexShader);
    glAttachShader(mShaderProgram, mFragShader);
    glLinkProgram(mShaderProgram);

    if (!IsVaildProgram())
    {
        return false;
    }

    return true;
}

void Shader::Unload()
{
    glDeleteProgram(mShaderProgram);
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragShader);
}

void Shader::SetActive()
{
    //设置激活
    glUseProgram(mShaderProgram);
}

void Shader::SetMatrixUniform(const char *name, const glm::mat4 &matrix)
{
    //根据name索引uniform
    GLuint loc = glGetUniformLocation(mShaderProgram, name);
    glUniformMatrix4fv(loc, 1, GL_TRUE,glm::value_ptr(matrix));
}
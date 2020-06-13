//
// Created by 蔡元涵 on 2020/6/3.
//

#ifndef SEMI_DEMO_SHADER_H
#define SEMI_DEMO_SHADER_H

#include <glew.h>
#include <string>
#include <glm.hpp>

class Shader
{
public:
    Shader();

    ~Shader();

    bool Load(const std::string &vertName, const std::string &fragName);

    void Unload();

    //将shader置为激活状态
    void SetActive();

    //传递设置矩阵uniform
    void SetMatrixUniform(const char *name, const glm::mat4 &matrix);

private:
    bool CompileShader(const std::string &fileName, GLenum shaderType, GLuint &outShader);

    //验证是否编译or链接成功
    bool IsCompiled(GLuint shader);

    bool IsVaildProgram();

    //储存shader相关ID
    GLuint mVertexShader;
    GLuint mFragShader;
    GLuint mShaderProgram;
};


#endif //SEMI_DEMO_SHADER_H

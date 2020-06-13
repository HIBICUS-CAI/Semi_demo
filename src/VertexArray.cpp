//
// Created by 蔡元涵 on 2020/6/3.
//

#include <glew.h>
#include "VertexArray.h"

VertexArray::VertexArray(const float *verts, unsigned int numVerts,
                         const unsigned int *indices, unsigned int numIndices) : mNumVerts(
        numVerts), mNumIndices(numIndices)
{
    //创建VAO
    glGenVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);

    //创建VBO
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, numVerts * 5 * sizeof(float), verts, GL_STATIC_DRAW);

    //创建索引缓冲
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices,
                 GL_STATIC_DRAW);

    //顶点属性配置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
                          reinterpret_cast<void *>(sizeof(float) * 3));
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &mVertexBuffer);
    glDeleteBuffers(1, &mIndexBuffer);
    glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
    glBindVertexArray(mVertexArray);
}
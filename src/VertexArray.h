//
// Created by 蔡元涵 on 2020/6/3.
//

#ifndef SEMI_DEMO_VERTEXARRAY_H
#define SEMI_DEMO_VERTEXARRAY_H


class VertexArray
{
public:
    VertexArray(const float *verts, unsigned int numVerts, const unsigned int *indices,
                unsigned int numIndices);

    ~VertexArray();

    void SetActive();

    unsigned int getNumVerts() const
    {
        return mNumVerts;
    }

    unsigned int getNumIndices() const
    {
        return mNumIndices;
    }

private:
    // VBO中的顶点数
    unsigned int mNumVerts;
    // 索引缓冲的顶点数量
    unsigned int mNumIndices;
    // VBO的ID
    unsigned int mVertexBuffer;
    // 索引缓冲的ID
    unsigned int mIndexBuffer;
    // VAO的ID
    unsigned int mVertexArray;
};


#endif //SEMI_DEMO_VERTEXARRAY_H

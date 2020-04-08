#pragma once

class CRenderableVertex
{
    protected:
        unsigned int m_IndicesVBO;
        unsigned int m_VerticesVBO;

        size_t m_IndexCount;
        size_t m_VertexCount;

    public:
        CRenderableVertex(void) : m_IndexCount(0), m_VertexCount(0), m_IndicesVBO(0), m_VerticesVBO(0)
        {
        }

        ~CRenderableVertex(void)
        {
            glDeleteBuffers(1, &m_IndicesVBO);
            glDeleteBuffers(1, &m_VerticesVBO);
        }

        inline size_t GetFacesCount(void)  { return m_IndexCount / 3; }
        inline size_t GetVertexsCount(void) { return m_VertexCount; }

        virtual void Render(void) = 0;
};

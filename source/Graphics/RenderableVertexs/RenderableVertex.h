#pragma once

class CRenderableVertexs
{
    protected:
        unsigned int m_IndicesVBO;
        unsigned int m_VerticesVBO;

        unsigned int m_IndexCount;
		unsigned int m_VertexCount;

    public:
        CRenderableVertexs(void) : m_IndexCount(0), m_VertexCount(0), m_IndicesVBO(0), m_VerticesVBO(0)
        {
        }

        ~CRenderableVertexs(void)
        {
            glDeleteBuffers(1, &m_IndicesVBO);
            glDeleteBuffers(1, &m_VerticesVBO);
        }

        unsigned int GetFacesCount(void)  { return m_IndexCount / 3; }
        unsigned int GetVertexsCount(void) { return m_VertexCount; }

        virtual void Render(void) = 0;
};

#pragma once
#include <Windows.h>

#include <gl\glew.h>
#include <gl\wglew.h>

#include "RenderableVertex.h"

template<class V, class I> class CIndexedVertex : public CRenderableVertex
{
    private:
        template<class T> unsigned int GetDataType                (void) { return GL_UNSIGNED_INT; }

        template<>        unsigned int GetDataType<unsigned short>(void) { return GL_UNSIGNED_SHORT; }
        template<>        unsigned int GetDataType<unsigned char> (void) { return GL_UNSIGNED_BYTE; }
        template<>        unsigned int GetDataType<unsigned int>  (void) { return GL_UNSIGNED_INT; }

        template<>        unsigned int GetDataType<short>         (void) { return GL_SHORT; }
        template<>        unsigned int GetDataType<char>          (void) { return GL_BYTE; }
        template<>        unsigned int GetDataType<int>           (void) { return GL_INT; }

    public:
        CIndexedVertex(void *VertexAddress, void *IndexAddres, size_t VertexCount, size_t IndexCount)
        {
            glGenBuffers(1, &m_VerticesVBO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
            glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(V), VertexAddress, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glGenBuffers(1, &m_IndicesVBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesVBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexCount * sizeof(I), IndexAddres, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            m_IndexCount = IndexCount;
            m_VertexCount = VertexCount;
        }

        ~CIndexedVertex(void)
        {
        }

        void Render(void) override
        {
            V::Bind(m_VerticesVBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesVBO);

            glDrawElements(GL_TRIANGLES, (unsigned int)m_IndexCount, GetDataType<I>(), (void *) 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            V::UnBind();
        }
};

#include "./DebugRender.h"
#include "Common/Files/stb_image_write.h"

void CDebugRender::DrawLine(const CVector3f &start, const CVector3f &end, const CVector3f &color)
{
    float v[6] = { start.x, start.y, start.z, end.x, end.y, end.z };
    float c[6] = { color.x, color.y, color.z, color.x, color.y, color.z };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, v);
    glColorPointer(3, GL_FLOAT, 0, c);

    glDrawArrays(GL_LINES, 0, 2);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void CDebugRender::DrawAxis(const CVector3f &origin, float sz)
{
    DrawLine(origin, CVector3f(sz, 0.0f, 0.0f) + origin, CVector3f(1.0f, 0.0f, 0.0f));
    DrawLine(origin, CVector3f(0.0f, sz, 0.0f) + origin, CVector3f(0.0f, 1.0f, 0.0f));
    DrawLine(origin, CVector3f(0.0f, 0.0f, sz) + origin, CVector3f(0.0f, 0.0f, 1.0f));
}

void CDebugRender::DrawGrid(int nLines, float sz, const CVector3f &color)
{
    float hSz = sz / 2.0f;

    for (int i = 0; i <= nLines; i++)
    {
        DrawLine(CVector3f(-hSz + (i * sz) / nLines, 0.0f, -hSz), CVector3f(-hSz + (i * sz) / nLines, 0.0f, hSz), color);
    }

    for (int i = 0; i <= nLines; i++)
    {
        DrawLine(CVector3f(-hSz, 0.0f, -hSz + (i * sz) / nLines), CVector3f(hSz, 0.0f, -hSz + (i * sz) / nLines), color);
    }
}

void CDebugRender::DrawCube(const CVector3f &pos, const CVector3f &color)
{
    static const float g_vertex_buffer_data[] =
    {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f
    };

    const float g_color_buffer_data[] =
    {
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b,
        color.r, color.g, color.b
    };

    glPushMatrix();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, g_vertex_buffer_data);
        glColorPointer(3, GL_FLOAT, 0, g_color_buffer_data);

        glTranslatef(pos.x, pos.y, pos.z);
        glScalef(0.1f, 0.1f, 0.1f);
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}

static unsigned int quadVAO = 0;
static unsigned int quadVBO = 0;

void CDebugRender::RenderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] =
        {
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);

        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    }

    glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

int CDebugRender::TakeScreenShot(const char *filename)
{
    GLint viewport[4] = {};
    glGetIntegerv(GL_VIEWPORT, viewport);

    int x = viewport[0];
    int y = viewport[1];

    int width = viewport[2];
    int height = viewport[3];

    char *data = (char *)malloc((size_t)width * (size_t)height * (size_t)3);
    if (!data) return 0;

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_flip_vertically_on_write(1);
    int saved = stbi_write_png(filename, width, height, 3, data, 0);

    free(data);
    return saved;
}

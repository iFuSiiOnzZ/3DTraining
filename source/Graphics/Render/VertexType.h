#pragma once
#include <gl\glew.h>
#include <gl\wglew.h>

#define VERTEX_TYPE_GEOMETRY    1 << 0
#define VERTEX_TYPE_NORMALS1    1 << 1
#define VERTEX_TYPE_TEXTURE1    1 << 2
#define VERTEX_TYPE_COLORS01    1 << 3
#define VERTEX_TYPE_TANGENT     1 << 4
#define VERTEX_TYPE_BITANGENT   1 << 5

struct VERTEX_GEOMETRY
{
    float px, py, pz;

    static unsigned short GetVertexType()
    {
        return VERTEX_TYPE_GEOMETRY;
    }

    static void Bind(unsigned int vbo)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY), (void *) offsetof(VERTEX_GEOMETRY, px));
    }

    static void UnBind(void)
    {
        glDisableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};

struct VERTEX_GEOMETRY_NORMALS
{
    float px, py, pz;
    float nx, ny, nz;

    static unsigned short GetVertexType()
    {
        return VERTEX_TYPE_GEOMETRY | VERTEX_TYPE_NORMALS1;
    }

    static void Bind(unsigned int vbo)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY_NORMALS), (void *) offsetof(VERTEX_GEOMETRY_NORMALS, px));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY_NORMALS), (void *) offsetof(VERTEX_GEOMETRY_NORMALS, nx));
    }

    static void UnBind(void)
    {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};

struct VERTEX_GEOMETRY_NORMALS_COLOR
{
    float px, py, pz;
    float nx, ny, nz;
    float cr, cg, cb;

    static unsigned short GetVertexType()
    {
        return VERTEX_TYPE_GEOMETRY | VERTEX_TYPE_NORMALS1 | VERTEX_TYPE_COLORS01;
    }

    static void Bind(unsigned int vbo)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY_NORMALS_COLOR), (void *) offsetof(VERTEX_GEOMETRY_NORMALS_COLOR, px));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY_NORMALS_COLOR), (void *) offsetof(VERTEX_GEOMETRY_NORMALS_COLOR, nx));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY_NORMALS_COLOR), (void *) offsetof(VERTEX_GEOMETRY_NORMALS_COLOR, cr));
    }

    static void UnBind(void)
    {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};

struct VERTEX_GEOMETRY_NORMALS_TEXTURE
{
    float px, py, pz;
    float nx, ny, nz;
    float tu, tv;

    static unsigned short GetVertexType()
    {
        return VERTEX_TYPE_GEOMETRY | VERTEX_TYPE_NORMALS1 | VERTEX_TYPE_TEXTURE1;
    }

    static void Bind(unsigned int vbo)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY_NORMALS_TEXTURE), (void *)offsetof(VERTEX_GEOMETRY_NORMALS_TEXTURE, px));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY_NORMALS_TEXTURE), (void *)offsetof(VERTEX_GEOMETRY_NORMALS_TEXTURE, nx));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY_NORMALS_TEXTURE), (void *)offsetof(VERTEX_GEOMETRY_NORMALS_TEXTURE, tu));
    }

    static void UnBind(void)
    {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};

struct VERTEX_GEOMETRY_NORMALS_TEXTURE_TANGENT_BITANGENT
{
    float px, py, pz;
    float nx, ny, nz;
    float tu, tv;
    float tx, ty, tz;
    float bx, by, bz;

    static unsigned short GetVertexType()
    {
        return VERTEX_TYPE_GEOMETRY | VERTEX_TYPE_NORMALS1 | VERTEX_TYPE_TEXTURE1 | VERTEX_TYPE_TANGENT | VERTEX_TYPE_BITANGENT;
    }

    static void Bind(unsigned int vbo)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY_NORMALS_TEXTURE_TANGENT_BITANGENT), (void *)offsetof(VERTEX_GEOMETRY_NORMALS_TEXTURE_TANGENT_BITANGENT, px));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY_NORMALS_TEXTURE_TANGENT_BITANGENT), (void *)offsetof(VERTEX_GEOMETRY_NORMALS_TEXTURE_TANGENT_BITANGENT, nx));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY_NORMALS_TEXTURE_TANGENT_BITANGENT), (void *)offsetof(VERTEX_GEOMETRY_NORMALS_TEXTURE_TANGENT_BITANGENT, tu));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY_NORMALS_TEXTURE_TANGENT_BITANGENT), (void *)offsetof(VERTEX_GEOMETRY_NORMALS_TEXTURE_TANGENT_BITANGENT, tx));

        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_GEOMETRY_NORMALS_TEXTURE_TANGENT_BITANGENT), (void *)offsetof(VERTEX_GEOMETRY_NORMALS_TEXTURE_TANGENT_BITANGENT, bx));
    }

    static void UnBind(void)
    {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(4);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
};

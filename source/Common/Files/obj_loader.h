#pragma once

#include <vector>
#include <string>

struct obj_p2_t
{
    float x, y;
};

struct obj_p3_t
{
    float x, y, z;
};

struct obj_vertex_t
{
    obj_p3_t vertex;
    obj_p3_t normal;
    obj_p2_t uv;
    obj_p3_t tangent;
    obj_p3_t bitangent;
};

struct obj_material_t
{
    obj_material_t()
    {
        Ns = Ni = d = 0.0f;
        Ka = Kd = Ks = {};
        illum = 0;
    }

    // Name
    std::string name;

    // Ambient Color
    obj_p3_t Ka;

    // Diffuse Color
    obj_p3_t Kd;

    // Specular Color
    obj_p3_t Ks;

    // Specular Exponent
    float Ns;

    // Optical Density
    float Ni;

    // Dissolve
    float d;

    // Illumination
    int illum;

    // Ambient Texture Map
    std::string map_Ka;

    // Diffuse Texture Map
    std::string map_Kd;

    // Specular Texture Map
    std::string map_Ks;

    // Bump Texture Map
    std::string map_Bump;

    // Specular Hightlight Map
    std::string map_Ns;

    // Alpha Texture Map
    std::string map_d;
};

struct obj_object_t
{
    std::vector<obj_vertex_t> geometry;
    std::vector<int> indices;

    obj_material_t material;
    std::string name;
};

struct obj_meshes_t
{
    std::vector<obj_object_t> objects;
    obj_object_t full;
};

///////////////////////////////////////////////////////////////////////////////

void obj_parse(const char *filename, obj_meshes_t &outData);

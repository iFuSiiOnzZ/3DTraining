#include "obj_loader.h"
#include <sstream>

static bool obj_load_file(const std::string &filePath, std::string &outFileContent)
{
    FILE *fileHandler = NULL;
    char fileContent[256] = { 0 };

    if (fopen_s(&fileHandler, filePath.c_str(), "rt") != 0)
    {
        return false;
    }

    while (fgets(fileContent, 256, fileHandler))
    {
        outFileContent.append(fileContent);
    }

    fclose(fileHandler);
    return true;
}

static char *obj_get_path(const char *filename, char *outBuffer)
{
    const char *lastSlash = nullptr;
    char *auxBuffer = outBuffer;

    for (const char *c = filename; *c != '\0'; ++c)
    {
        if (*c == '\\' || *c == '/')
        {
            lastSlash = c;
        }
    }

    while (lastSlash && filename != lastSlash)
    {
        *auxBuffer++ = *filename++;
    }

    return outBuffer;
}

static inline bool obj_is_ofl(char c)
{
    return c == '\n' || c == '\r' || c == '\0';
}

static inline bool obj_is_white_space(char c)
{
    return c == ' ' || c == '\t' || c == '\v' || obj_is_ofl(c);
}

static char *obj_str_trim(char *str)
{
    while (obj_is_white_space(*str)) ++str;
    int strLen = (int)std::strlen(str) - 1;

    while (strlen > 0 && obj_is_white_space(*(str + strLen))) str[strLen--] = '\0';
    return str;
}

static char *obj_get_line(char **dstr)
{
    char *str = *dstr;
    if (*str == '\0') return nullptr;

    while (obj_is_white_space(*str)) ++str;
    char *lineStart = str;

    while (!obj_is_ofl(*str)) ++str;
    *str = '\0'; *dstr = str + 1;

    return lineStart;
}

static bool obj_check_token(const char *str, const char *token)
{
    const char *s1 = str;
    const char *s2 = token;

    while (obj_is_white_space(*s1)) ++s1;
    while (obj_is_white_space(*s2)) ++s2;

    while (*s1 && (*s1 == *s2)) ++s1, ++s2;
    return obj_is_white_space(*s1) && obj_is_white_space(*s2);
}

static std::vector<char *> obj_split_by_token(char *str, const char *tokens)
{
    std::vector<char *> output;
    char *posn = nullptr, *pch = strtok_s((char *)str, tokens, &posn);

    while (pch != nullptr)
    {
        output.emplace_back(pch);
        pch = strtok_s(nullptr, tokens, &posn);
    }

    return output;
}

static void obj_parse_p3(std::vector<obj_p3_t> &vector, char *line)
{
    std::vector<char *> v = obj_split_by_token(line, " \t");
    if (v.size() < 3) return;

    obj_p3_t p = { std::stof(v[0]), std::stof(v[1]), std::stof(v[2]) };
    vector.emplace_back(p);
}

static void obj_parse_p2(std::vector<obj_p2_t> &vector, char *line)
{
    std::vector<char *> v = obj_split_by_token(line, " \t");
    if (v.size() < 2) return;

    obj_p2_t p = { std::stof(v[0]), std::stof(v[1]) };
    vector.emplace_back(p);
}

static void obj_add_face(char *line, const std::vector<obj_p3_t> &vertices, const std::vector<obj_p3_t> &normals, const std::vector<obj_p2_t> &textures, obj_object_t &outGeometry, obj_object_t *outGeometry2 = nullptr)
{
    std::vector<char *> faces = obj_split_by_token(line, " \t");

    if (faces.size() != 3)
    {
        *(int *)0 = 0;
    }

    for (size_t i = 0; i < faces.size(); ++i)
    {
        std::vector<char *> f = obj_split_by_token(faces[i], "/");
        obj_vertex_t geometry = {};

        size_t type = f.size();
        int vNumber = 0;

        if (type == 3)
        {
            type = f[1] == '\0' ? type : 4;
        }

        switch (type)
        {
            case 1: // vertex
            {
                vNumber = std::stoi(f[0]) - 1;
                geometry.vertex = vertices[vNumber];
            } break;

            case 2: // vertex / texture
            {
                vNumber = std::stoi(f[0]) - 1;
                int iTex = std::stoi(f[1]) - 1;

                geometry.vertex = vertices[vNumber];
                geometry.uv = textures[iTex];
            } break;

            case 3: // vertex / / normal
            {
                vNumber = std::stoi(f[0]) - 1;
                int iNorm = std::stoi(f[2]) - 1;

                geometry.vertex = vertices[vNumber];
                geometry.normal = normals[iNorm];
            } break;

            case 4: // vertex / texture / normal
            {
                vNumber = std::stoi(f[0]) - 1;
                int iTex = std::stoi(f[1]) - 1;
                int iNorm = std::stoi(f[2]) - 1;

                geometry.vertex = vertices[vNumber];
                geometry.normal = normals[iNorm];
                geometry.uv = textures[iTex];
            } break;
        }

        outGeometry.geometry.emplace_back(geometry);
        outGeometry.indices.emplace_back((int)outGeometry.geometry.size() - 1);

        if (outGeometry2)
        {
            outGeometry2->geometry.emplace_back(geometry);
            outGeometry2->indices.emplace_back((int)outGeometry2->geometry.size() - 1);
        }
    }
}

static void obj_parse_material(const char *filename, std::vector<obj_material_t> &outMaterials)
{
    std::string objContent;
    obj_load_file(filename, objContent);

    obj_material_t dummyMat;
    obj_material_t *material = &dummyMat;

    char *line = nullptr;
    char *str = (char *)objContent.c_str();

    while ((line = obj_get_line(&str)) != nullptr)
    {
        if (obj_check_token(line, "newmtl"))
        {
            outMaterials.emplace_back(obj_material_t());
            material = &outMaterials.back();

            char *value = line + 6;
            material->name = obj_str_trim(value);
        }
        else if (obj_check_token(line, "illum"))
        {
            char *value = line + 6;
            material->illum = std::stoi(obj_str_trim(value));
        }
        else if (obj_check_token(line, "Ns"))
        {
            char *value = line + 2;
            material->Ns = std::stof(obj_str_trim(value));
        }
        else if (obj_check_token(line, "Ni"))
        {
            char *value = line + 2;
            material->Ni = std::stof(obj_str_trim(value));
        }
        else if (obj_check_token(line, "Ka"))
        {
            std::vector<char *> Ka = obj_split_by_token((char*)line + 2, " \t");
            if (Ka.size() < 3) continue;

            material->Ka.x = std::stof(Ka[0]);
            material->Ka.y = std::stof(Ka[1]);
            material->Ka.z = std::stof(Ka[2]);
        }
        else if (obj_check_token(line, "Kd"))
        {
            std::vector<char *> Kd = obj_split_by_token(line + 2, " \t");
            if (Kd.size() < 3) continue;

            material->Kd.x = std::stof(Kd[0]);
            material->Kd.y = std::stof(Kd[1]);
            material->Kd.z = std::stof(Kd[2]);
        }
        else if (obj_check_token(line, "Ks"))
        {
            std::vector<char *> Ks = obj_split_by_token(line + 2, " \t");
            if (Ks.size() < 3) continue;

            material->Ks.x = std::stof(Ks[0]);
            material->Ks.y = std::stof(Ks[1]);
            material->Ks.z = std::stof(Ks[2]);
        }
        else if (obj_check_token(line, "map_Ka"))
        {
            char *value = line + 7;
            material->map_Ka = obj_str_trim(value);
        }
        else if (obj_check_token(line, "map_Kd"))
        {
            char *value = line + 7;
            material->map_Kd = obj_str_trim(value);
        }
        else if (obj_check_token(line, "map_Ks"))
        {
            char *value = line + 7;
            material->map_Ks = obj_str_trim(value);
        }
        else if (obj_check_token(line, "map_Bump"))
        {
            char *value = line + 9;
            material->map_Bump = obj_str_trim(value);
        }
        else if (obj_check_token(line, "map_d"))
        {
            char *value = line + 9;
            material->map_d = obj_str_trim(value);
        }
    }
}

static obj_material_t *obj_get_material(std::vector<obj_material_t> &materials, const char *materialName)
{
    for (size_t i = 0; i < materials.size(); ++i)
    {
        if (materials[i].name.compare(materialName) == 0)
        {
            return &materials[i];
        }
    }

    return nullptr;
}

static inline const char *obj_get_mtl_name(const char *mtllib)
{
    while (obj_is_white_space(*mtllib)) ++mtllib;
    return mtllib;
}

///////////////////////////////////////////////////////////////////////////////

static inline obj_p3_t operator-(const obj_p3_t &p1, const obj_p3_t &p2)
{
    obj_p3_t r = { p1.x - p2.x, p1.y - p2.y, p1.z - p2.z };
    return r;
}

static inline obj_p3_t operator*(const obj_p3_t &p1, float f)
{
    obj_p3_t r = { p1.x * f, p1.y * f, p1.z * f };
    return r;
}

static inline obj_p2_t operator-(const obj_p2_t &p1, const obj_p2_t &p2)
{
    obj_p2_t r = { p1.x - p2.x, p1.y - p2.y };
    return r;
}

static inline float obj_dot_product(const obj_p3_t &p1, const obj_p3_t &p2)
{
    return p1.x - p2.x + p1.y * p2.y + p1.z * p2.z;
}

static inline obj_p3_t obj_cross_product(const obj_p3_t & p1, const obj_p3_t & p2)
{
    obj_p3_t out = {};

    out.x = p1.y * p2.z - p1.z * p2.y;
    out.y = p1.z * p2.x - p1.x * p2.z;
    out.z = p1.x * p2.y - p1.y * p2.x;

    return out;
}

static void obj_calculate_tangent_bitangent(obj_meshes_t &outData)
{
    for (auto &obj : outData.objects)
    {
        if (obj.geometry.size() % 3 != 0)
        {
            *(int *)0 = 0;
        }

        for(size_t i = 0; i < obj.geometry.size(); i += 3)
        {
            obj_p3_t v1 = obj.geometry[i + 1].vertex - obj.geometry[i + 0].vertex;
            obj_p3_t v2 = obj.geometry[i + 2].vertex - obj.geometry[i + 0].vertex;

            obj_p2_t uv1 = obj.geometry[i + 1].uv - obj.geometry[i + 0].uv;
            obj_p2_t uv2 = obj.geometry[i + 2].uv - obj.geometry[i + 0].uv;

            float coef = 1.0f / (uv1.x * uv2.y - uv2.x * uv1.y);
            obj_p3_t normal = obj.geometry[i + 0].normal;

            obj_p3_t tangent = (v1 * uv2.y - v2 * uv1.y) * coef;
            obj_p3_t bitangent = (v2 * uv1.x - v1 * uv2.x) * coef;

            if (obj_dot_product(obj_cross_product(normal, tangent), bitangent) < 0.0f)
            {
                tangent.x *= -1; tangent.y *= -1; tangent.z *= -1;
            }

            obj.geometry[i + 0].bitangent = bitangent;
            obj.geometry[i + 0].tangent = tangent;

            obj.geometry[i + 1].bitangent = bitangent;
            obj.geometry[i + 1].tangent = tangent;

            obj.geometry[i + 2].bitangent = bitangent;
            obj.geometry[i + 2].tangent = tangent;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

void obj_parse(const char *filename, obj_meshes_t &outData)
{
    std::string objContent, copyOfContent;
    obj_load_file(filename, objContent);

    copyOfContent = objContent;
    char *line = nullptr, *str = (char *)objContent.c_str();

    std::vector<obj_p3_t> vertices, normals;
    std::vector<obj_p2_t> textures;

    vertices.reserve(256);
    textures.reserve(256);
    normals.reserve(256);

    std::vector<obj_material_t> materials;
    materials.reserve(32);

    while ((line = obj_get_line(&str)) != nullptr)
    {
        if (obj_check_token(line, "v"))
        {
            obj_parse_p3(vertices, line + 2);
        }
        else if (obj_check_token(line, "vn"))
        {
            obj_parse_p3(normals, line + 3);
        }
        else if (obj_check_token(line, "vt"))
        {
            obj_parse_p2(textures, line + 3);
        }
        else if (obj_check_token(line, "mtllib"))
        {
            char path[256] = {};
            obj_get_path(filename, path);

            size_t slen = strlen(path);
            path[slen++] = '/';

            strcat_s(path, sizeof(path) - slen, obj_get_mtl_name(line + 6));
            obj_parse_material(path, materials);
        }
    }

    objContent = copyOfContent;
    str = (char *)objContent.c_str();

    obj_object_t dummyObj;
    obj_object_t *currentObject = &dummyObj;

    while ((line = obj_get_line(&str)) != nullptr)
    {
        if (obj_check_token(line, "o") || obj_check_token(line, "g"))
        {
            outData.objects.emplace_back(obj_object_t());
            currentObject = &outData.objects.back();

            currentObject->name = obj_str_trim((char*)line + 2);
            if (currentObject->name.empty()) currentObject->name = "unnamed";
        }
        else if (obj_check_token(line, "usemtl"))
        {
            if (currentObject->indices.empty())
            {
                char *matName = obj_str_trim(line + 7);
                currentObject->material.name = matName;

                obj_material_t *mat = obj_get_material(materials, matName);
                if (mat) currentObject->material = *mat;
            }
            else
            {
                outData.objects.emplace_back(obj_object_t());
                currentObject = &outData.objects.back();

                currentObject->name = outData.objects[outData.objects.size() - 2].name;

                char *matName = obj_str_trim(line + 7);
                currentObject->material.name = matName;

                obj_material_t *mat = obj_get_material(materials, matName);
                if (mat) currentObject->material = *mat;
            }
        }
        else if (obj_check_token(line, "f"))
        {
            obj_add_face(line + 2, vertices, normals, textures, outData.full, currentObject);
        }
    }

    obj_calculate_tangent_bitangent(outData);
}

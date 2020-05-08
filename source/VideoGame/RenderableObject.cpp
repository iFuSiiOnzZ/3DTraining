#include "RenderableObject.h"

#include "Common/Files/stb_image.h"
#include "Common/Files/obj_loader.h"

#include "Common/Utils/FileUtils.h"
#include "Common/Utils/ResourceManager.h"
#include "Common/Memory/AllocatorManager.h"

#include "Graphics/Shaders/ShaderProgram.h"

#include "Graphics/Render/Texture.h"
#include "Graphics/Render/VertexType.h"
#include "Graphics/Render/IndexedVertexs.h"

CRenderableObject::CRenderableObject()
{
    mesh = nullptr;
    illumModel = 0;

    Ns = Ni = d = 0.0f;
    TKa = TKd = TKs = Bump = nullptr;
}

CRenderableObject::~CRenderableObject()
{
}

void CRenderableObject::bind(CShaderProgram &shaderProgram)
{
    if (TKa)
    {
        shaderProgram.setUniformVector3f("material.ambientColor", Ka.u);
        shaderProgram.setUniformValue("material.ambientTexture", 0);

        TKa->SetUnit(0);
        TKa->Use();
    }

    if (TKd)
    {
        shaderProgram.setUniformVector3f("material.diffuseColor", Kd.u);
        shaderProgram.setUniformValue("material.diffuseTexture", 1);

        TKd->SetUnit(1);
        TKd->Use();
    }

    if (TKs)
    {
        shaderProgram.setUniformVector3f("material.specularColor", Ks.u);
        shaderProgram.setUniformValue("material.specularTexture", 2);

        TKs->SetUnit(2);
        TKs->Use();
    }

    if (Bump)
    {
        shaderProgram.setUniformValue("material.hasBump", 1);
        shaderProgram.setUniformValue("material.bump", 3);

        Bump->SetUnit(3);
        Bump->Use();
    }
}

void CRenderableObject::render()
{
    mesh->Render();
}

void CRenderableObject::unbind(CShaderProgram &shaderProgram)
{
    if (TKa) TKa->UnUse();
    if (TKd) TKd->UnUse();
    if (TKs) TKs->UnUse();

    if (Bump) Bump->UnUse();
    shaderProgram.setUniformValue("material.hasBump", 0);
}

std::vector<CRenderableObject> *CRenderableObject::loadObject(const char *filename)
{
    obj_meshes_t meshes;
    obj_parse(filename, meshes);

    std::string objPath = FileGetPath(filename);
    CResourceManager *resourceManger = CResourceManager::GetSingletonPtr();

    typedef std::vector<CRenderableObject> CRenderObjsVec;
    CRenderObjsVec *renderObjects = ALLOCATOR_FREE_LIST->MakeNew<CRenderObjsVec>();

    for (auto &mesh : meshes.objects)
    {
        if (mesh.indices.empty())
        {
            continue;
        }

        using IndexedVertex = CIndexedVertex<VERTEX_GEOMETRY_NORMALS_TEXTURE_TANGENT_BITANGENT, unsigned int>;
        renderObjects->emplace_back(CRenderableObject());

        renderObjects->back().transform = CScalef(0.01f, 0.01f, 0.01f);

        renderObjects->back().Ka.x = mesh.material.Ka.x;
        renderObjects->back().Ka.y = mesh.material.Ka.y;
        renderObjects->back().Ka.z = mesh.material.Ka.z;

        renderObjects->back().Kd.x = mesh.material.Kd.x;
        renderObjects->back().Kd.y = mesh.material.Kd.y;
        renderObjects->back().Kd.z = mesh.material.Kd.z;

        renderObjects->back().Ks.x = mesh.material.Ks.x;
        renderObjects->back().Ks.y = mesh.material.Ks.y;
        renderObjects->back().Ks.z = mesh.material.Ks.z;

        renderObjects->back().mesh = ALLOCATOR_FREE_LIST->MakeNew<IndexedVertex>
        (
            mesh.geometry.data(),
            mesh.indices.data(),
            mesh.geometry.size(),
            mesh.indices.size()
        );

        if (mesh.material.map_Ka.size())
        {
            std::string baseName = FileGetBaseName(mesh.material.map_Ka);
            CTexture *tex = resourceManger->Get<CTexture>(baseName);
            renderObjects->back().TKa = tex;

            if (tex == nullptr)
            {
                tex = ALLOCATOR_FREE_LIST->MakeNew<CTexture>();
                renderObjects->back().TKa = tex;

                tex->SetName(baseName);
                tex->SetRepeate(true).SetSmooth(true);

                std::string path = objPath + mesh.material.map_Ka;
                int w = 0, h = 0, n = 0;

                unsigned char *img = stbi_load(path.c_str(), &w, &h, &n, 0);
                tex->SetTexture(img, w, h, n);

                stbi_image_free(img);
                resourceManger->Add<CTexture>(baseName, tex);
            }
        }

        if (mesh.material.map_Kd.size())
        {
            std::string baseName = FileGetBaseName(mesh.material.map_Kd);
            CTexture *tex = resourceManger->Get<CTexture>(baseName);
            renderObjects->back().TKd = tex;

            if (tex == nullptr)
            {
                tex = ALLOCATOR_FREE_LIST->MakeNew<CTexture>();
                renderObjects->back().TKd = tex;

                tex->SetName(baseName);
                tex->SetRepeate(true).SetSmooth(true);

                std::string path = objPath + mesh.material.map_Kd;
                int w = 0, h = 0, n = 0;

                unsigned char *img = stbi_load(path.c_str(), &w, &h, &n, 0);
                tex->SetTexture(img, w, h, n);

                stbi_image_free(img);
                resourceManger->Add<CTexture>(baseName, tex);
            }
        }

        if (mesh.material.map_Ks.size())
        {
            std::string baseName = FileGetBaseName(mesh.material.map_Ks);
            CTexture *tex = resourceManger->Get<CTexture>(baseName);
            renderObjects->back().TKs = tex;

            if (tex == nullptr)
            {
                tex = ALLOCATOR_FREE_LIST->MakeNew<CTexture>();
                renderObjects->back().TKs = tex;

                tex->SetName(baseName);
                tex->SetRepeate(true).SetSmooth(true);

                std::string path = objPath + mesh.material.map_Ks;
                int w = 0, h = 0, n = 0;

                unsigned char *img = stbi_load(path.c_str(), &w, &h, &n, 0);
                tex->SetTexture(img, w, h, n);

                stbi_image_free(img);
                resourceManger->Add<CTexture>(baseName, tex);
            }
        }

        if (mesh.material.map_Bump.size())
        {
            std::string baseName = FileGetBaseName(mesh.material.map_Bump);
            CTexture *tex = resourceManger->Get<CTexture>(baseName);
            renderObjects->back().Bump = tex;

            if (tex == nullptr)
            {
                tex = ALLOCATOR_FREE_LIST->MakeNew<CTexture>();
                renderObjects->back().Bump = tex;

                tex->SetName(baseName);
                tex->SetRepeate(true).SetSmooth(false);

                std::string path = objPath + mesh.material.map_Bump;
                int w = 0, h = 0, n = 0;

                unsigned char *img = stbi_load(path.c_str(), &w, &h, &n, 0);
                tex->SetTexture(img, w, h, n);

                stbi_image_free(img);
                resourceManger->Add<CTexture>(baseName, tex);
            }
        }
    }

    return renderObjects;
}

void CRenderableObject::free(std::vector<CRenderableObject> *obj)
{
    if (obj)
    {
        obj->clear();
        ALLOCATOR_FREE_LIST->MakeDelete(obj);
    }
}

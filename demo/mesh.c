#include "mesh.h"

GSKE_Mesh* GSKE_CreateMesh()
{
    GSKE_Mesh* mesh = (GSKE_Mesh*)MEM_alloc(sizeof(GSKE_Mesh));
    memset(mesh, 0, sizeof(GSKE_Mesh));
    mesh->translation.x = FIX16(0);
    mesh->translation.y = FIX16(0);
    mesh->translation.z = FIX16(0);
    mesh->rotation.x = FIX16(0);
    mesh->rotation.y = FIX16(0);
    mesh->rotation.z = FIX16(0);
    mesh->material = MATERIAL_Flat;
    return mesh;
}

void GSKE_DestroyMesh(GSKE_Mesh* mesh)
{
    MEM_free(mesh->vertices);
    MEM_free(mesh->faces);
    MEM_free(mesh);
}

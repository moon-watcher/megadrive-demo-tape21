#ifndef _GSKE_MESH_H_
#define _GSKE_MESH_H_

#include "genesis.h"

typedef enum
{
    MATERIAL_Dot,
    MATERIAL_Wireframe,
    MATERIAL_Flat    
} MATERIAL;

typedef struct
{
    u16 vertex_count;
    Vect3D_f16* vertices;
    u16 face_count;
    u16* faces;
    Vect3D_f16 translation;
    Vect3D_f16 rotation;
    MATERIAL material;
} GSKE_Mesh;

GSKE_Mesh* GSKE_CreateMesh();
void GSKE_DestroyMesh(GSKE_Mesh* mesh);

#endif

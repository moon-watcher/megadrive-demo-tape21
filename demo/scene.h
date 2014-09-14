#ifndef _GSKE_SCENE_H_
#define _GSKE_SCENE_H_

#include "mesh.h"

#define GSKE_MAX_MESH       4
#define GSKE_MAX_VERTEX     600
#define GSKE_MAX_FACE       300

typedef struct
{
    GSKE_Mesh* meshes[GSKE_MAX_MESH];
    int mesh_count;
    Vect3D_f16 ws_vertices[GSKE_MAX_VERTEX];
    Vect2D_s16 vp_vertices[GSKE_MAX_VERTEX];
    u16 faces[GSKE_MAX_FACE*3];
    u8 faceMesh[GSKE_MAX_FACE];
    u16 face_sort[GSKE_MAX_FACE];
    u16 face_norms[GSKE_MAX_FACE];
} GSKE_SceneS;

extern GSKE_SceneS GSKE_Scene;

void GSKE_CreateScene();
void GSKE_DestroyScene();
void GSKE_UpdateScene();

u16 GSKE_AddMesh(GSKE_Mesh* mesh);
void GSKE_RemoveMesh(u16 mesh);

#endif

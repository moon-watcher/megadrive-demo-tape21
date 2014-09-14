#include "scene.h"
#include "raster.h"

GSKE_SceneS GSKE_Scene;

void GSKE_CreateScene()
{
    memset(GSKE_Scene.meshes, 0, sizeof(GSKE_Mesh*)*GSKE_MAX_MESH);
    GSKE_Scene.mesh_count = 0;
}

void GSKE_DestroyScene()
{
    u16 i;
    for (i=0 ; i<GSKE_Scene.mesh_count ; ++i)
        GSKE_RemoveMesh(i);
    GSKE_CreateScene();   
}

void quick_sort(int deb, int fin)
{
    int i=deb;
    int j=fin;
    int milieu=GSKE_Scene.face_norms[GSKE_Scene.face_sort[(deb+fin)/2]];
    int temp;

    while (i<=j)
    {
        while (GSKE_Scene.face_norms[GSKE_Scene.face_sort[i]]>milieu && i<j) i++;
        while (GSKE_Scene.face_norms[GSKE_Scene.face_sort[j]]<milieu && j>0) j--;

        if (i<=j)
        {
            temp = GSKE_Scene.face_sort[i];
            GSKE_Scene.face_sort[i]=GSKE_Scene.face_sort[j];
            GSKE_Scene.face_sort[j]=temp;
            ++i;
            --j;
        }
    }

    if (i<fin) quick_sort(i,fin);
    if (deb<j) quick_sort(deb,j);
}

void GSKE_UpdateScene()
{
    u16 vertex_count = 0;
    u16 face_count = 0;
    u16 i,j;
    int minZ = 99999;
    int maxZ = 0;
    for (i=0 ; i<GSKE_Scene.mesh_count ; ++i)
    {
        if (vertex_count+GSKE_Scene.meshes[i]->vertex_count<GSKE_MAX_VERTEX)
        {
            M3D_setTransMat3D(&GSKE_Scene.meshes[i]->translation);
            M3D_setRotMat3D(&GSKE_Scene.meshes[i]->rotation);
            M3D_transform3D(GSKE_Scene.meshes[i]->vertices, GSKE_Scene.ws_vertices+vertex_count, GSKE_Scene.meshes[i]->vertex_count);
             
            for (j=0 ; j<GSKE_Scene.meshes[i]->face_count ; ++j)
            {
                GSKE_Scene.faceMesh[face_count] = i;
                GSKE_Scene.faces[face_count*3+0] = GSKE_Scene.meshes[i]->faces[j*3+0]+vertex_count;
                GSKE_Scene.faces[face_count*3+1] = GSKE_Scene.meshes[i]->faces[j*3+1]+vertex_count;
                GSKE_Scene.faces[face_count*3+2] = GSKE_Scene.meshes[i]->faces[j*3+2]+vertex_count;
                
                GSKE_Scene.face_norms[face_count] = GSKE_Scene.ws_vertices[GSKE_Scene.faces[face_count*3+0]].z/3
                    + GSKE_Scene.ws_vertices[GSKE_Scene.faces[face_count*3+1]].z/3
                    + GSKE_Scene.ws_vertices[GSKE_Scene.faces[face_count*3+2]].z/3;
                if (GSKE_Scene.face_norms[face_count]<minZ) minZ = GSKE_Scene.face_norms[face_count];
                if (GSKE_Scene.face_norms[face_count]>maxZ) maxZ = GSKE_Scene.face_norms[face_count];
                GSKE_Scene.face_sort[face_count] = face_count;                
                ++face_count;
            }
            vertex_count += GSKE_Scene.meshes[i]->vertex_count;
        }
    }
        
    quick_sort(0, face_count-1);
            
    M3D_project3D_s16(GSKE_Scene.ws_vertices, GSKE_Scene.vp_vertices, vertex_count);
    
    for (i=0 ; i<face_count ; ++i)
    {
        u16 iv[3];
        u16 sf = GSKE_Scene.face_sort[i];
        iv[0] = GSKE_Scene.faces[sf*3+0];
        iv[1] = GSKE_Scene.faces[sf*3+1];
        iv[2] = GSKE_Scene.faces[sf*3+2];
                  
        if (GSKE_Scene.ws_vertices[iv[0]].z<=0 || GSKE_Scene.ws_vertices[iv[1]].z<=0 || GSKE_Scene.ws_vertices[iv[2]].z<=0)
            continue;
         
        switch (GSKE_Scene.meshes[GSKE_Scene.faceMesh[sf]]->material)
        {
            case MATERIAL_Dot:
            {
                GSKE_DrawPolygonDot(
                    GSKE_Scene.vp_vertices+iv[0],
                    GSKE_Scene.vp_vertices+iv[1],
                    GSKE_Scene.vp_vertices+iv[2], 15|(15<<4));
            } break;
            
            case MATERIAL_Wireframe:
            {
                GSKE_DrawPolygonWireframe(
                    GSKE_Scene.vp_vertices+iv[0],
                    GSKE_Scene.vp_vertices+iv[1],
                    GSKE_Scene.vp_vertices+iv[2], 15);
            } break;
            
            case MATERIAL_Flat:
            {
                u8 color;
                if (maxZ-minZ==0) color = 15;
                else { int depth = (GSKE_Scene.face_norms[sf]-minZ)*15/(maxZ-minZ); color = 15-(depth&15); }
              
                GSKE_DrawPolygonFlat(
                    GSKE_Scene.vp_vertices+iv[0],
                    GSKE_Scene.vp_vertices+iv[1],
                    GSKE_Scene.vp_vertices+iv[2], color);
            } break;
        }
    }
}

u16 GSKE_AddMesh(GSKE_Mesh* mesh)
{
    if (GSKE_Scene.mesh_count<GSKE_MAX_MESH)
    {
        GSKE_Scene.meshes[GSKE_Scene.mesh_count++] = mesh;
        return GSKE_Scene.mesh_count-1;
    }
    return -1;
}

void GSKE_RemoveMesh(u16 mesh)
{
    if (mesh<GSKE_Scene.mesh_count)
    {
        GSKE_DestroyMesh(GSKE_Scene.meshes[mesh]);
        GSKE_Scene.meshes[mesh] = 0;
        int i;
        for (i=mesh ; i<GSKE_Scene.mesh_count-1 ; ++i)
            GSKE_Scene.meshes[i] = GSKE_Scene.meshes[i+1];
        --GSKE_Scene.mesh_count;        
    }
}



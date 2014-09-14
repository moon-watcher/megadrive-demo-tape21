#include "effect_sega.h"
#include "tile_test.h"

void EFFECT_sega()
{
    int i;
    for (i=0 ; i<8 ; ++i)
    {
        VDP_setPaletteColor(PAL0, i, (i*2));
        VDP_setPaletteColor(PAL0, i+8, (i+8));
    }
    
    GSKE_Mesh* mesh_0 = GSKE_CreateMesh();
    mesh_0->vertex_count = 33;
    mesh_0->vertices = (Vect3D_f16*)MEM_alloc(33*sizeof(Vect3D_f16));
    mesh_0->vertices[0].x = intToFix16(-14); mesh_0->vertices[0].y = intToFix16(-14); mesh_0->vertices[0].z = intToFix16(-14);
    mesh_0->vertices[1].x = intToFix16(-14); mesh_0->vertices[1].y = intToFix16(14); mesh_0->vertices[1].z = intToFix16(-14);
    mesh_0->vertices[2].x = intToFix16(14); mesh_0->vertices[2].y = intToFix16(14); mesh_0->vertices[2].z = intToFix16(-14);
    mesh_0->vertices[3].x = intToFix16(14); mesh_0->vertices[3].y = intToFix16(14); mesh_0->vertices[3].z = intToFix16(-14);
    mesh_0->vertices[4].x = intToFix16(14); mesh_0->vertices[4].y = intToFix16(-14); mesh_0->vertices[4].z = intToFix16(-14);
    mesh_0->vertices[5].x = intToFix16(-14); mesh_0->vertices[5].y = intToFix16(-14); mesh_0->vertices[5].z = intToFix16(14);
    mesh_0->vertices[6].x = intToFix16(14); mesh_0->vertices[6].y = intToFix16(-14); mesh_0->vertices[6].z = intToFix16(14);
    mesh_0->vertices[7].x = intToFix16(14); mesh_0->vertices[7].y = intToFix16(14); mesh_0->vertices[7].z = intToFix16(14);
    mesh_0->vertices[8].x = intToFix16(-14); mesh_0->vertices[8].y = intToFix16(14); mesh_0->vertices[8].z = intToFix16(14);
    mesh_0->vertices[9].x = intToFix16(-14); mesh_0->vertices[9].y = intToFix16(-14); mesh_0->vertices[9].z = intToFix16(14);
    mesh_0->vertices[10].x = intToFix16(-14); mesh_0->vertices[10].y = intToFix16(-14); mesh_0->vertices[10].z = intToFix16(-14);
    mesh_0->vertices[11].x = intToFix16(14); mesh_0->vertices[11].y = intToFix16(-14); mesh_0->vertices[11].z = intToFix16(-14);
    mesh_0->vertices[12].x = intToFix16(14); mesh_0->vertices[12].y = intToFix16(-14); mesh_0->vertices[12].z = intToFix16(14);
    mesh_0->vertices[13].x = intToFix16(14); mesh_0->vertices[13].y = intToFix16(-14); mesh_0->vertices[13].z = intToFix16(14);
    mesh_0->vertices[14].x = intToFix16(-14); mesh_0->vertices[14].y = intToFix16(-14); mesh_0->vertices[14].z = intToFix16(14);
    mesh_0->vertices[15].x = intToFix16(-14); mesh_0->vertices[15].y = intToFix16(-14); mesh_0->vertices[15].z = intToFix16(-14);
    mesh_0->vertices[16].x = intToFix16(14); mesh_0->vertices[16].y = intToFix16(-14); mesh_0->vertices[16].z = intToFix16(-14);
    mesh_0->vertices[17].x = intToFix16(14); mesh_0->vertices[17].y = intToFix16(14); mesh_0->vertices[17].z = intToFix16(-14);
    mesh_0->vertices[18].x = intToFix16(14); mesh_0->vertices[18].y = intToFix16(14); mesh_0->vertices[18].z = intToFix16(14);
    mesh_0->vertices[19].x = intToFix16(14); mesh_0->vertices[19].y = intToFix16(14); mesh_0->vertices[19].z = intToFix16(14);
    mesh_0->vertices[20].x = intToFix16(14); mesh_0->vertices[20].y = intToFix16(-14); mesh_0->vertices[20].z = intToFix16(14);
    mesh_0->vertices[21].x = intToFix16(14); mesh_0->vertices[21].y = intToFix16(14); mesh_0->vertices[21].z = intToFix16(-14);
    mesh_0->vertices[22].x = intToFix16(-14); mesh_0->vertices[22].y = intToFix16(14); mesh_0->vertices[22].z = intToFix16(-14);
    mesh_0->vertices[23].x = intToFix16(-14); mesh_0->vertices[23].y = intToFix16(14); mesh_0->vertices[23].z = intToFix16(14);
    mesh_0->vertices[24].x = intToFix16(-14); mesh_0->vertices[24].y = intToFix16(14); mesh_0->vertices[24].z = intToFix16(14);
    mesh_0->vertices[25].x = intToFix16(14); mesh_0->vertices[25].y = intToFix16(14); mesh_0->vertices[25].z = intToFix16(14);
    mesh_0->vertices[26].x = intToFix16(14); mesh_0->vertices[26].y = intToFix16(14); mesh_0->vertices[26].z = intToFix16(-14);
    mesh_0->vertices[27].x = intToFix16(-14); mesh_0->vertices[27].y = intToFix16(14); mesh_0->vertices[27].z = intToFix16(-14);
    mesh_0->vertices[28].x = intToFix16(-14); mesh_0->vertices[28].y = intToFix16(-14); mesh_0->vertices[28].z = intToFix16(-14);
    mesh_0->vertices[29].x = intToFix16(-14); mesh_0->vertices[29].y = intToFix16(-14); mesh_0->vertices[29].z = intToFix16(14);
    mesh_0->vertices[30].x = intToFix16(-14); mesh_0->vertices[30].y = intToFix16(-14); mesh_0->vertices[30].z = intToFix16(14);
    mesh_0->vertices[31].x = intToFix16(-14); mesh_0->vertices[31].y = intToFix16(14); mesh_0->vertices[31].z = intToFix16(14);
    mesh_0->vertices[32].x = intToFix16(-14); mesh_0->vertices[32].y = intToFix16(14); mesh_0->vertices[32].z = intToFix16(-14);
    mesh_0->face_count = 12;
    mesh_0->faces = (u16*)MEM_alloc(12*3*sizeof(u16));
    mesh_0->faces[0*3+0] = 0; mesh_0->faces[0*3+1] = 1; mesh_0->faces[0*3+2] = 2;
    mesh_0->faces[1*3+0] = 3; mesh_0->faces[1*3+1] = 4; mesh_0->faces[1*3+2] = 0;
    mesh_0->faces[2*3+0] = 5; mesh_0->faces[2*3+1] = 6; mesh_0->faces[2*3+2] = 7;
    mesh_0->faces[3*3+0] = 7; mesh_0->faces[3*3+1] = 8; mesh_0->faces[3*3+2] = 9;
    mesh_0->faces[4*3+0] = 10; mesh_0->faces[4*3+1] = 11; mesh_0->faces[4*3+2] = 12;
    mesh_0->faces[5*3+0] = 13; mesh_0->faces[5*3+1] = 14; mesh_0->faces[5*3+2] = 15;
    mesh_0->faces[6*3+0] = 16; mesh_0->faces[6*3+1] = 17; mesh_0->faces[6*3+2] = 18;
    mesh_0->faces[7*3+0] = 19; mesh_0->faces[7*3+1] = 20; mesh_0->faces[7*3+2] = 16;
    mesh_0->faces[8*3+0] = 21; mesh_0->faces[8*3+1] = 22; mesh_0->faces[8*3+2] = 23;
    mesh_0->faces[9*3+0] = 24; mesh_0->faces[9*3+1] = 25; mesh_0->faces[9*3+2] = 26;
    mesh_0->faces[10*3+0] = 27; mesh_0->faces[10*3+1] = 28; mesh_0->faces[10*3+2] = 29;
    mesh_0->faces[11*3+0] = 30; mesh_0->faces[11*3+1] = 31; mesh_0->faces[11*3+2] = 32;

    GSKE_Mesh* mesh_1 = GSKE_CreateMesh();
    mesh_1->vertex_count = 33;
    mesh_1->vertices = (Vect3D_f16*)MEM_alloc(33*sizeof(Vect3D_f16));
    mesh_1->vertices[0].x = intToFix16(-20); mesh_1->vertices[0].y = intToFix16(-20); mesh_1->vertices[0].z = intToFix16(-20);
    mesh_1->vertices[1].x = intToFix16(-20); mesh_1->vertices[1].y = intToFix16(20); mesh_1->vertices[1].z = intToFix16(-20);
    mesh_1->vertices[2].x = intToFix16(20); mesh_1->vertices[2].y = intToFix16(20); mesh_1->vertices[2].z = intToFix16(-20);
    mesh_1->vertices[3].x = intToFix16(20); mesh_1->vertices[3].y = intToFix16(20); mesh_1->vertices[3].z = intToFix16(-20);
    mesh_1->vertices[4].x = intToFix16(20); mesh_1->vertices[4].y = intToFix16(-20); mesh_1->vertices[4].z = intToFix16(-20);
    mesh_1->vertices[5].x = intToFix16(-20); mesh_1->vertices[5].y = intToFix16(-20); mesh_1->vertices[5].z = intToFix16(20);
    mesh_1->vertices[6].x = intToFix16(20); mesh_1->vertices[6].y = intToFix16(-20); mesh_1->vertices[6].z = intToFix16(20);
    mesh_1->vertices[7].x = intToFix16(20); mesh_1->vertices[7].y = intToFix16(20); mesh_1->vertices[7].z = intToFix16(20);
    mesh_1->vertices[8].x = intToFix16(-20); mesh_1->vertices[8].y = intToFix16(20); mesh_1->vertices[8].z = intToFix16(20);
    mesh_1->vertices[9].x = intToFix16(-20); mesh_1->vertices[9].y = intToFix16(-20); mesh_1->vertices[9].z = intToFix16(20);
    mesh_1->vertices[10].x = intToFix16(-20); mesh_1->vertices[10].y = intToFix16(-20); mesh_1->vertices[10].z = intToFix16(-20);
    mesh_1->vertices[11].x = intToFix16(20); mesh_1->vertices[11].y = intToFix16(-20); mesh_1->vertices[11].z = intToFix16(-20);
    mesh_1->vertices[12].x = intToFix16(20); mesh_1->vertices[12].y = intToFix16(-20); mesh_1->vertices[12].z = intToFix16(20);
    mesh_1->vertices[13].x = intToFix16(20); mesh_1->vertices[13].y = intToFix16(-20); mesh_1->vertices[13].z = intToFix16(20);
    mesh_1->vertices[14].x = intToFix16(-20); mesh_1->vertices[14].y = intToFix16(-20); mesh_1->vertices[14].z = intToFix16(20);
    mesh_1->vertices[15].x = intToFix16(-20); mesh_1->vertices[15].y = intToFix16(-20); mesh_1->vertices[15].z = intToFix16(-20);
    mesh_1->vertices[16].x = intToFix16(20); mesh_1->vertices[16].y = intToFix16(-20); mesh_1->vertices[16].z = intToFix16(-20);
    mesh_1->vertices[17].x = intToFix16(20); mesh_1->vertices[17].y = intToFix16(20); mesh_1->vertices[17].z = intToFix16(-20);
    mesh_1->vertices[18].x = intToFix16(20); mesh_1->vertices[18].y = intToFix16(20); mesh_1->vertices[18].z = intToFix16(20);
    mesh_1->vertices[19].x = intToFix16(20); mesh_1->vertices[19].y = intToFix16(20); mesh_1->vertices[19].z = intToFix16(20);
    mesh_1->vertices[20].x = intToFix16(20); mesh_1->vertices[20].y = intToFix16(-20); mesh_1->vertices[20].z = intToFix16(20);
    mesh_1->vertices[21].x = intToFix16(20); mesh_1->vertices[21].y = intToFix16(20); mesh_1->vertices[21].z = intToFix16(-20);
    mesh_1->vertices[22].x = intToFix16(-20); mesh_1->vertices[22].y = intToFix16(20); mesh_1->vertices[22].z = intToFix16(-20);
    mesh_1->vertices[23].x = intToFix16(-20); mesh_1->vertices[23].y = intToFix16(20); mesh_1->vertices[23].z = intToFix16(20);
    mesh_1->vertices[24].x = intToFix16(-20); mesh_1->vertices[24].y = intToFix16(20); mesh_1->vertices[24].z = intToFix16(20);
    mesh_1->vertices[25].x = intToFix16(20); mesh_1->vertices[25].y = intToFix16(20); mesh_1->vertices[25].z = intToFix16(20);
    mesh_1->vertices[26].x = intToFix16(20); mesh_1->vertices[26].y = intToFix16(20); mesh_1->vertices[26].z = intToFix16(-20);
    mesh_1->vertices[27].x = intToFix16(-20); mesh_1->vertices[27].y = intToFix16(20); mesh_1->vertices[27].z = intToFix16(-20);
    mesh_1->vertices[28].x = intToFix16(-20); mesh_1->vertices[28].y = intToFix16(-20); mesh_1->vertices[28].z = intToFix16(-20);
    mesh_1->vertices[29].x = intToFix16(-20); mesh_1->vertices[29].y = intToFix16(-20); mesh_1->vertices[29].z = intToFix16(20);
    mesh_1->vertices[30].x = intToFix16(-20); mesh_1->vertices[30].y = intToFix16(-20); mesh_1->vertices[30].z = intToFix16(20);
    mesh_1->vertices[31].x = intToFix16(-20); mesh_1->vertices[31].y = intToFix16(20); mesh_1->vertices[31].z = intToFix16(20);
    mesh_1->vertices[32].x = intToFix16(-20); mesh_1->vertices[32].y = intToFix16(20); mesh_1->vertices[32].z = intToFix16(-20);
    mesh_1->face_count = 12;
    mesh_1->faces = (u16*)MEM_alloc(12*3*sizeof(u16));
    mesh_1->faces[0*3+0] = 0; mesh_1->faces[0*3+1] = 1; mesh_1->faces[0*3+2] = 2;
    mesh_1->faces[1*3+0] = 3; mesh_1->faces[1*3+1] = 4; mesh_1->faces[1*3+2] = 0;
    mesh_1->faces[2*3+0] = 5; mesh_1->faces[2*3+1] = 6; mesh_1->faces[2*3+2] = 7;
    mesh_1->faces[3*3+0] = 7; mesh_1->faces[3*3+1] = 8; mesh_1->faces[3*3+2] = 9;
    mesh_1->faces[4*3+0] = 10; mesh_1->faces[4*3+1] = 11; mesh_1->faces[4*3+2] = 12;
    mesh_1->faces[5*3+0] = 13; mesh_1->faces[5*3+1] = 14; mesh_1->faces[5*3+2] = 15;
    mesh_1->faces[6*3+0] = 16; mesh_1->faces[6*3+1] = 17; mesh_1->faces[6*3+2] = 18;
    mesh_1->faces[7*3+0] = 19; mesh_1->faces[7*3+1] = 20; mesh_1->faces[7*3+2] = 16;
    mesh_1->faces[8*3+0] = 21; mesh_1->faces[8*3+1] = 22; mesh_1->faces[8*3+2] = 23;
    mesh_1->faces[9*3+0] = 24; mesh_1->faces[9*3+1] = 25; mesh_1->faces[9*3+2] = 26;
    mesh_1->faces[10*3+0] = 27; mesh_1->faces[10*3+1] = 28; mesh_1->faces[10*3+2] = 29;
    mesh_1->faces[11*3+0] = 30; mesh_1->faces[11*3+1] = 31; mesh_1->faces[11*3+2] = 32;
    
    mesh_0->material = MATERIAL_Flat;
    mesh_1->material = MATERIAL_Wireframe;
    
    GSKE_setScrollMode(GSKE_HSCROLL_Plane, GSKE_VSCROLL_Plane);
    
     int xs=0, ys=0;
    
    u16 w = BMP_CELLWIDTH;
    u16 h = BMP_CELLHEIGHT;
    VDP_setPalette(PAL2, &tile_test[2]);
    
    for (ys=0 ; ys<VDP_getPlanHeight(); ++ys)
    for (xs=0 ; xs<VDP_getPlanWidth(); ++xs)
        VDP_fillTileMapRectInc(BPLAN, TILE_ATTR_FULL(PAL2, 0, 0, 0, BMP_CELLWIDTH/2+((ys+4)%h)*w+(xs%w)), xs, ys, 1, 1);
    
    u16 mesh0Id = GSKE_AddMesh(mesh_0);
    u16 mesh1Id = GSKE_AddMesh(mesh_1);
    u16 j = 0;
    do
    {
        j+=10;
        mesh_0->translation.z = FIX16(120);
        mesh_0->rotation.x = j*100;
        mesh_0->rotation.y = j*300;
        mesh_0->rotation.z = j*200;
        mesh_1->translation.z = FIX16(120);
        mesh_1->rotation.x = j*100;
        mesh_1->rotation.y = j*300;
        mesh_1->rotation.z = j*200;
        GSKE_update3d();
        
        VDP_setHorizontalScroll(BPLAN, 0, j);
        VDP_setHorizontalScroll(APLAN, 0, j*2);
    }
    while(j<800);
    GSKE_RemoveMesh(mesh0Id);
    GSKE_RemoveMesh(mesh1Id);
    //GSKE_exit3d();
}

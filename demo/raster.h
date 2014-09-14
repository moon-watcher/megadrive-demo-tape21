#ifndef _GSKE_RASTER_H_
#define _GSKE_RASTER_H_

#include "genesis.h"

inline void GSKE_DrawDot(Vect2D_s16* p, u8 color);
inline void GSKE_DrawPolygonDot(Vect2D_s16* v1, Vect2D_s16* v2, Vect2D_s16* v3, u8 color);
inline void GSKE_DrawLine(Vect2D_s16* p1, Vect2D_s16* p2, u8 color);
inline void GSKE_DrawPolygonWireframe(Vect2D_s16* v1, Vect2D_s16* v2, Vect2D_s16* v3, u8 color);
inline void GSKE_DrawHorizontalLine(int x1, int x2, int y, u8 color);
inline void GSKE_DrawPolygonFlat(Vect2D_s16* v1, Vect2D_s16* v2, Vect2D_s16* v3, u8 color);
inline void GSKE_DrawHorizontalLineGouraud(long x1, long c1, long x2, long c2, long y);
inline void GSKE_DrawPolygonGouraud(Vect2D_s16* v1, u8 c1, Vect2D_s16* v2, u8 c2, Vect2D_s16* v3, u8 c3);
inline void GSKE_DrawHorizontalLineTexMap(long x1, long tx1, long ty1, long x2, long tx2, long ty2, long y, const u8* texmap);
inline void GSKE_DrawPolygonTexMap(Vect2D_s16* v1, Vect2D_s16* uv1, Vect2D_s16* v2, Vect2D_s16* uv2, Vect2D_s16* v3, Vect2D_s16* uv3, const u8* texmap);

#endif

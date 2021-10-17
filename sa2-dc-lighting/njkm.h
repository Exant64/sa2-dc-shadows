#pragma once
#include "SA2ModLoader.h"
#include <d3d9.h>
typedef struct MODTRI {
    NJS_VECTOR v1;
    NJS_VECTOR v2;
    NJS_VECTOR v3;
}MODTRI, * PMODTRI;

extern MODTRI ModifierVertexBuf[];
extern PMODTRI pSQ;

void njInitModifier();
void DrawPolygons();
void EndDraw();
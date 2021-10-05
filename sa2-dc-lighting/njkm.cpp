#include "pch.h"
#include "SA2ModLoader.h"
#include "njkm.h"
#include <d3dx9.h>

MODTRI ModifierVertexBuf[4096];
PMODTRI pModSQ = &ModifierVertexBuf[0];

PMODTRI njStartModifier()
{
    return pModSQ;
}

void njEndVertex(PMODTRI pDST)
{
    pModSQ = pDST;
}
void* njEndModifier(void*){}

const int gjStartVertex3DPtr = 0x0041FDE0;
void gjStartVertex3D(float* a1, unsigned int a2)
{
	__asm
	{
		mov ecx, a1
		push a2
		call gjStartVertex3DPtr
		add esp, 4
	}
}

static IDirect3DVertexDeclaration9* njDrawPolygonDeclaration;
static const D3DVERTEXELEMENT9 drawPolygonDeclaration[] =
{
	{0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,   0},
	D3DDECL_END()
};
IDirect3DDevice9* modifierDrawDevice;
void DrawPolygons()
{
	int vertCount = ((Uint32)pModSQ - (Uint32)ModifierVertexBuf) / sizeof(MODTRI);

	modifierDrawDevice->SetVertexDeclaration(njDrawPolygonDeclaration);
	modifierDrawDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, vertCount , &ModifierVertexBuf[0], 12);

	modifierDrawDevice->SetStreamSource(0, nullptr, 0, 0);
	
}

void EndDraw()
{
	pModSQ = ModifierVertexBuf;
}
void njInitModifier(IDirect3DDevice9* device)
{
	modifierDrawDevice = device;
	modifierDrawDevice->CreateVertexDeclaration(drawPolygonDeclaration, &njDrawPolygonDeclaration);
}
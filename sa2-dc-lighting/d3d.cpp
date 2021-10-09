#include "pch.h"

#include "SA2ModLoader.h"
#include "d3d.h"
#include <d3dx9.h>
#include <string>
#include "njkm.h"

IDirect3DVertexDeclaration9* pShadowQuadDeclaration;
static const D3DVERTEXELEMENT9 shadowQuadDeclaration[] =
{
	{0,  0,  D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,   0},
	{0,  12, D3DDECLTYPE_D3DCOLOR,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0},
	D3DDECL_END()
};
IDirect3DDevice9* device;
IDirect3DVertexShader9* ninjaVertexShader;
IDirect3DPixelShader9* ninjaPixelShader;

IDirect3DVertexShader9* ninjaLVertexShader;
IDirect3DPixelShader9* ninjaLPixelShader;

//uhhhh this mod was originally restoring dc lighting (but i couldnt figure out specular) 

DataArray(Light, Lights, 0x01DE4280, 12);
ThiscallFunctionPointer(void, Renderer__SetShaderConstantsF, (void* a1, int a2, int a3, const float* a4, signed int a5), 0x00866E80);
ThiscallFunctionPointer(void, Renderer__SetShaderConstantsF2, (void* a1, int a2, int a3, float* a4), 0x00866E30);
void __cdecl DoLighting_Simple(int a1)
{
	NJS_VECTOR loc;
	loc = Lights[a1].direction;
	njCalcPoint(&loc, &loc, _nj_current_matrix_ptr_);
	
	Renderer__SetShaderConstantsF2(dword_1A557C0, 0, 200, (float*)&loc);
	Renderer__SetShaderConstantsF(dword_1A557C0, 0, 204, &Lights[a1].intensity, 1);
	Renderer__SetShaderConstantsF(dword_1A557C0, 0, 208, &Lights[a1].ambient, 1);
}
static void __declspec(naked)  DoLightingHook()
{
	__asm
	{
		push eax
		call DoLighting_Simple
		add esp, 4
		retn
	}
}


void LoadModVolShaders(const char* path)
{
	

	LPD3DXBUFFER pNinjaVertexShaderBuf, pNinjaPixelShaderBuf;
	std::string pSimpleShaderString = std::string(path);
	pSimpleShaderString.append("\\ShadowGenVolumeV.hlsl");
	D3DXCompileShaderFromFileA(pSimpleShaderString.c_str(), 0, 0, "main", "vs_3_0", 0, &pNinjaVertexShaderBuf, 0, 0);

	pSimpleShaderString = std::string(path);
	pSimpleShaderString.append("\\ShadowGenVolumeP.hlsl");
	D3DXCompileShaderFromFileA(pSimpleShaderString.c_str(), 0, 0, "main", "ps_3_0", 0, &pNinjaPixelShaderBuf, 0, 0);

	device->CreateVertexShader((const DWORD*)pNinjaVertexShaderBuf->GetBufferPointer(), &ninjaVertexShader);
	device->CreatePixelShader((const DWORD*)pNinjaPixelShaderBuf->GetBufferPointer(), &ninjaPixelShader);

	device->CreateVertexDeclaration(shadowQuadDeclaration, &pShadowQuadDeclaration);

#ifdef DCLIGHTING
	WriteJump((void*)0x00487060, DoLightingHook);

	pSimpleShaderString = std::string(path);
	pSimpleShaderString.append("\\NinjaVertex.hlsl");
	D3DXCompileShaderFromFileA(pSimpleShaderString.c_str(), 0, 0, "main", "vs_3_0", 0, &pNinjaVertexShaderBuf, 0, 0);

	pSimpleShaderString = std::string(path);
	pSimpleShaderString.append("\\NinjaPixel.hlsl");
	D3DXCompileShaderFromFileA(pSimpleShaderString.c_str(), 0, 0, "main", "ps_3_0", 0, &pNinjaPixelShaderBuf, 0, 0);

	device->CreateVertexShader((const DWORD*)pNinjaVertexShaderBuf->GetBufferPointer(), &ninjaLVertexShader);
	device->CreatePixelShader((const DWORD*)pNinjaPixelShaderBuf->GetBufferPointer(), &ninjaLPixelShader);
#endif
}
#pragma once
#include "SA2ModLoader.h"
#include <d3d9.h>
struct  Renderer
{
	void* vtable;
	char field_4[52];
	IDirect3DDevice9* pointerToDevice;
	char field_3C[70];
};
struct Light
{
	NJS_VECTOR direction;
	float intensity;
	float ambient;
	NJS_VECTOR color;
};

#pragma pack(push, 8)
struct __declspec(align(4)) ShaderD3DPointerThing
{
	char gap0[12];
	void* shaderData;
	int field_10;
	int field_14;
	int field_18;
	int field_1C;
	int field_20;
	int field_24;
	int field_28;
	int field_2C;
	int field_30;
	int field_34;
	int field_38;
	int field_3C;
	int field_40;
	int field_44;
	int field_48;
	int field_4C;
	int field_50;
};
#pragma pack(pop)

#pragma pack(push, 8)
struct ShaderData
{
	int field_0;
	int field_4;
	int field_8;
	int field_C;
	int field_10;
	int field_14;
	int field_18;
	int field_1C;
	int field_20;
	int field_24[20];
	int field_74;
	int field_78;
	int field_7C;
	int field_80;
	int field_84;
	int field_88;
	int field_8C;
	int field_90;
	int field_94;
	int field_98;
	int field_9C;
	int field_A0;
	int field_A4;
	int field_A8;
	int field_AC;
	int field_B0;
	int field_B4;
	int field_B8;
	int field_BC;
	int field_C0;
	int field_C4;
	int field_C8;
	int field_CC;
	int field_D0;
	int field_D4;
	int field_D8;
	int field_DC;
	int field_E0;
	int field_E4;
	int field_E8;
	ShaderD3DPointerThing* VertexShader;
	int field_F0;
	ShaderD3DPointerThing* PixelShader;
};
#pragma pack(pop)
DataPointer(int, struc_36Instance, 0x01A557BC);
VoidFunc(sub_4785A0, 0x4785A0);
extern IDirect3DDevice9* device;
DataPointer(Renderer*, dword_1A557C0, 0x1A557C0);
extern IDirect3DVertexShader9* ninjaVertexShader;
extern IDirect3DPixelShader9* ninjaPixelShader;

void LoadModVolShaders(const char* path);
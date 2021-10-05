#pragma once
#include <SA2ModLoader.h>
enum {
	RenderFlag_None = 0,
	RenderFlag_Opaque = 1 << 1,
	RenderFlag_Trans = 1 << 2
};
//not implemented yet but we'll probably need it sooner or later
enum {
	DrawEntry_Field1C,
	DrawEntry_Field20,
};
struct TransparentModelEntry
{
	NJS_CNK_MODEL* model;

	NJS_ARGB ConstantMaterial;
	unsigned int ctrl3dFlg;
	unsigned int atrAnd;
	unsigned int atrOr;
	unsigned int blendmode;
	unsigned int cnk_blend_mode;
	int lightID;

	int drawEntry;

	NJS_TEXLIST* texlist;
	int EasyFlag;
	float matrix[12];
};
extern int ModelTransFlag;
extern bool NinjaFlag;
void DoLighting(int a1);
void TransList_Render();
void TransList_Init();

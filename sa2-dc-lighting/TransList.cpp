#include "pch.h"
#include <SA2ModLoader.h>
#include <vector>
#include <d3d9.h>
#include "njCnkModifier.h"
#include "TransList.h"
#include "d3d.h"


const int njCnkEasyDrawModelPtr = 0x42E6C0;
void njCnkEasyDrawModel(NJS_CNK_MODEL* a1)
{
	__asm
	{
		mov eax, a1
		call njCnkEasyDrawModelPtr
	}
}


std::vector<TransparentModelEntry> transparentModelList;
int ModelTransFlag = 0;
bool NinjaFlag = 0; //dont queue ninja flag shit, breaks player
NJS_CNK_MODEL* pCurrentDrawingModel = nullptr;
int LastLightID = 0;

void TransList_Add(NJS_CNK_MODEL* model)
{
	TransparentModelEntry entry;
	entry.lightID = LastLightID;
	entry.ctrl3dFlg = _nj_control_3d_flag_;
	if (_nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_CONSTANT_ATTR)
	{
		entry.atrAnd = *(Uint32*)0x025F02D4;
		entry.atrOr = *(Uint32*)0x025F0268;
	}
	if ((_nj_control_3d_flag_ & NJD_CONTROL_3D_CONSTANT_MATERIAL) || (_nj_control_3d_flag_ & NJD_CONTROL_3D_OFFSET_MATERIAL))
	{
		entry.ConstantMaterial = *(NJS_ARGB*)0x025EFFD0;
	}
	entry.cnk_blend_mode = *(int*)0x025F0264;
	entry.blendmode = RenferInfo_->Thing;
	entry.texlist = RenferInfo_->CurrentTexlist;
	entry.model = model;
	entry.EasyFlag = *(int*)0x01A55844;
	memcpy(entry.matrix, _nj_current_matrix_ptr_, 0x30);
	transparentModelList.push_back(entry);
}
void TransList_Clear()
{
	transparentModelList.clear();
}

const int DoLightingPtr = 0x00487060;
void DoLighting(int a1)
{
	__asm
	{
		mov eax, a1
		call DoLightingPtr
	}
}

void TransList_Render()
{
	//Opaque();

	//device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	ModelTransFlag = RenderFlag_Trans;
	int shaderBackup = *(int*)0x01A5579C;
	SetShaders(1);
	for (TransparentModelEntry& entry : transparentModelList)
	{
		device->SetRenderState(D3DRS_ZENABLE, true);
		device->SetRenderState(D3DRS_ZFUNC, D3DCMP_GREATEREQUAL);
		int c3d = _nj_control_3d_flag_;
		int atrAndBp = *(Uint32*)0x025F02D4;
		int atrOrBp = *(Uint32*)0x025F0268;
		njPushMatrixEx();
		memcpy(_nj_current_matrix_ptr_, entry.matrix, 0x30);
		njSetTexture(entry.texlist);
		DoLighting(entry.lightID);
		_nj_control_3d_flag_ = entry.ctrl3dFlg;
		if (_nj_control_3d_flag_ & NJD_CONTROL_3D_CNK_CONSTANT_ATTR)
		{
			*(Uint32*)0x025F02D4 = entry.atrAnd;
			*(Uint32*)0x025F0268 = entry.atrOr;
		}
		if ((_nj_control_3d_flag_ & NJD_CONTROL_3D_CONSTANT_MATERIAL) || (_nj_control_3d_flag_ & NJD_CONTROL_3D_OFFSET_MATERIAL))
		{
			*(NJS_ARGB*)0x025EFFD0 = entry.ConstantMaterial;
		}
		*(int*)0x025F0264 = entry.cnk_blend_mode;

		RenferInfo_->Thing = entry.blendmode;
		if (entry.EasyFlag)
			njCnkEasyDrawModel(entry.model);
		else
		{
			VoidFunc(sub_42D340, 0x42D340);
			sub_42D340();
			ProcessChunkModel(entry.model);
		}
		*(NJS_ARGB*)0x025EFFD0 = { 0,0,0,0 };

		*(Uint32*)0x025F02D4 = atrAndBp;
		*(Uint32*)0x025F0268 = atrOrBp;
		_nj_control_3d_flag_ = c3d;
		njPopMatrixEx();
	}
	SetShaders(shaderBackup);
	TransList_Clear();
	ModelTransFlag = RenderFlag_Trans | RenderFlag_Opaque;
}
FunctionPointer(signed int, sub_41C790, (int a1), 0x41C790);
int __cdecl ChunkModelTransCheck(int a1)
{
	bool canRender = false;

	DWORD zwrite;
	device->GetRenderState(D3DRS_ZWRITEENABLE, &zwrite);

	if (zwrite == 0)
	{
		if (ModelTransFlag & RenderFlag_Trans)
		{
			canRender = true;
		}
		else
			TransList_Add(pCurrentDrawingModel);
	}
	else if (ModelTransFlag & RenderFlag_Opaque) {

		canRender = true;
	}

	if (NinjaFlag || canRender) return sub_41C790(a1);
	else return 1;

}

const int sub_42D190Ptr = 0x42D190;
void sub_42D190(int* vertexChun, int buffer, int isSimple)
{
	__asm
	{
		push isSimple
		push buffer
		mov eax, vertexChun
		call sub_42D190Ptr
		add esp, 8
	}
}

void __cdecl sub_42D190_(NJS_CNK_MODEL* a1, int* vertexChunk, int buffer, int isSimple)
{
	pCurrentDrawingModel = a1;
	sub_42D190(vertexChunk, buffer, isSimple);
}

static void __declspec(naked) sub_42D190Hook()
{
	__asm
	{

		push[esp + 08h] // isSimple
		push[esp + 08h] // buffer
		push eax // vertexChun
		push[ebp + 8]

		// Call your __cdecl function here:
		call sub_42D190_
		add esp, 4
		pop eax // vertexChun
		add esp, 4 // buffer
		add esp, 4 // isSimple

		retn
	}
}
FunctionPointer(void, gjSetLightColor, (int id, float b, float g, float r), 0x0042A950);
void __cdecl gjSetLightColorHack(int LightID, int id, float b, float g, float r)
{
	LastLightID = LightID;
	gjSetLightColor(id, b, g, r);
}
__declspec(naked) void gjSetLightColorHook()
{
	__asm
	{
		mov LastLightID, eax
		jmp gjSetLightColor
	}
}

const int sub_42ED60Ptr = 0x42ED60;
void sub_42ED60(int result, int a2, int a3)
{
	__asm
	{
		mov eax, result
		mov ebx, a2
		push a3
		call sub_42ED60Ptr
		add esp, 4
	}
}
void __cdecl sub_42ED60Hack(int result, int a2, int a3)
{
	NinjaFlag = 1;
	sub_42ED60(result, a2, a3);
}
static void __declspec(naked) sub_42ED60Hook()
{
	__asm
	{
		push[esp + 04h] // a3
		push ebx // a2
		push eax // result

		// Call your __cdecl function here:
		call sub_42ED60Hack

		pop eax // result
		pop ebx // a2
		add esp, 4 // a3
		retn
	}
}

void TransListRenderHook()
{
	TransList_Render();
	sub_4785A0();
}

void TransList_Init()
{
	//render queued shit after all field_1C but before fade
	WriteCall((void*)0x004702BB, TransListRenderHook);

	//do not trans-queue ninjaflag models
	WriteCall((void*)0x0042D211, sub_42ED60Hook);

	WriteCall((void*)0x0048714D, gjSetLightColorHook);
	WriteCall((void*)0x0042D599, sub_42D190Hook);
	WriteCall((void*)0x0042E211, ChunkModelTransCheck);
	WriteCall((void*)0x0042E78E, ChunkModelTransCheck);
	WriteCall((void*)0x0042F0DF, ChunkModelTransCheck);
	WriteCall((void*)0x0042F2DF, ChunkModelTransCheck);
	WriteCall((void*)0x0042F3F1, ChunkModelTransCheck);
}
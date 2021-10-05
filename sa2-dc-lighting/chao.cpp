#include "pch.h"
#include "njCnkModifier.h"
#include "data/ChaoGenericShadow.nja"
#include "TransList.h"


struct FRUIT_INFO
{
	float growth;
	float AimGrowth;
	int SwingCounter;
	NJS_POINT3 pos;
	int angx;
	int angy;
};

#pragma pack(push, 8)
struct __declspec(align(4)) ALO_GrowTreeExecutor_Data
{
	EntityData1 entityData;
	char kind;
	char state;
	__int16 field_32;
	float growth;
	int life;
	int water;
	int pos_num;
	FRUIT_INFO fruit[3];
	float scale;
	float ScaleSpd;
	int ThirstyFlag;
	int WaterFlag;
	int LeafRotAng;
	float LeafWidth;
	int LeafDispNum;
	int FruitRotAng;
	float FruitWidth;
	int FruitDispNum;
	int SwingFlag;
	int SwingCountFlag;
	float SwingDist;
	int RollAngle;
	int TouchAngle;
	int ChaoSwingPhase;
	int RollPhase;
	int garden;
	void* pMySaveInfo;
	NJS_TEXLIST* texlist;
	NJS_OBJECT* pLocalObject;
	NJS_OBJECT* pShadowObject;
	NJS_OBJECT* pCopyObject;
};
#pragma pack(pop)

DataArray(int, dword_12E8AEC, 0x12E8AEC, 11);
void __cdecl sub_5479C0(ALO_GrowTreeExecutor_Data* a1)
{
	float* v1; // ebx
	float* v2; // esi
	float* v3; // eax
	float* v4; // esi
	int v5; // edx
	float* v6; // esi
	unsigned int v7; // ebp
	float* v8; // eax
	float* v9; // eax
	float* v10; // esi
	float* v11; // eax
	float* v12; // esi
	float* v13; // eax
	float* v14; // esi
	float* v15; // eax
	float* v16; // ebx
	float v17; // [esp+1Ch] [ebp-3Ch]
	float v18; // [esp+1Ch] [ebp-3Ch]
	double v19; // [esp+1Ch] [ebp-3Ch]
	float v20; // [esp+20h] [ebp-38h]
	float v21; // [esp+24h] [ebp-34h]
	float v22; // [esp+28h] [ebp-30h]
	float v23; // [esp+2Ch] [ebp-2Ch]
	float v24; // [esp+30h] [ebp-28h]
	float v25; // [esp+34h] [ebp-24h]
	float v26; // [esp+38h] [ebp-20h]
	float v27; // [esp+3Ch] [ebp-1Ch]
	float v28; // [esp+40h] [ebp-18h]
	float v29; // [esp+44h] [ebp-14h]
	float v30; // [esp+48h] [ebp-10h]
	float v31; // [esp+4Ch] [ebp-Ch]
	float v32; // [esp+50h] [ebp-8h]
	float v33; // [esp+54h] [ebp-4h]
	int a1a; // [esp+5Ch] [ebp+4h]
	//njSetTexture(^)
	njPushMatrixEx();
	{
		njTranslate(_nj_current_matrix_ptr_, a1->entityData.Position.x, a1->entityData.Position.y, a1->entityData.Position.z);
		if (a1->TouchAngle)
		{
			njRotateY(_nj_current_matrix_ptr_, a1->TouchAngle);
		}
		if (a1->RollAngle)
		{
			njRotateX(_nj_current_matrix_ptr_, a1->RollAngle);
		}
		if (a1->TouchAngle)
		{
			njRotateY(_nj_current_matrix_ptr_, -a1->TouchAngle);
		}
		if (a1->entityData.Rotation.y)
		{
			njRotateY(_nj_current_matrix_ptr_, a1->entityData.Rotation.y);
		}
		njTranslate(_nj_current_matrix_ptr_, 0.0, 20.0, 0.0);
		njCnkModDrawModel(object_8D9813C7ECAA3378948.chunkmodel);
	}
	njPopMatrixEx();

	njPushMatrixEx();
	{
		njTranslate(_nj_current_matrix_ptr_, a1->entityData.Position.x, a1->entityData.Position.y, a1->entityData.Position.z);
		if (a1->TouchAngle)
		{
			njRotateY(_nj_current_matrix_ptr_, a1->TouchAngle);
		}
		if (a1->RollAngle)
		{
			njRotateX(_nj_current_matrix_ptr_, a1->RollAngle);
		}
		if (a1->TouchAngle)
		{
			njRotateY(_nj_current_matrix_ptr_, -a1->TouchAngle);
		}
		if (a1->entityData.Rotation.y != 0xFFFFE000)
		{
			njRotateY(_nj_current_matrix_ptr_, a1->entityData.Rotation.y + 0x2000);
		}
		njTranslate(_nj_current_matrix_ptr_, 0.0, 20.0, 0.0);

		v5 = a1->LeafRotAng;
		v18 = a1->LeafWidth;
		a1a = a1->LeafRotAng;
		njPushMatrixEx();
		{
			v19 = v18 * 0.1500000059604645;
			v32 = njSin(dword_12E8AEC[0] + v5) * v19 + 7.699999809265137;
			njScale(0, 3.0f, 2.0f, v32);
			njTranslate(_nj_current_matrix_ptr_, 0.0, 0.0, 0.85000002);
			njCnkModDrawModel(object_8D9813C7ECAA3378948.chunkmodel);
		}
		njPopMatrixEx();

		njRotateY(_nj_current_matrix_ptr_, 14336);

		njPushMatrixEx();
		{
			v32 = njSin(a1a + dword_12E8AEC[1]) * v19 + 7.300000190734863;
			njScale(0, 3.0f, 2.0f, v32);
			njTranslate(_nj_current_matrix_ptr_, 0.0, 0.0, 0.85000002);
			njCnkModDrawModel(object_8D9813C7ECAA3378948.chunkmodel);
		}
		njPopMatrixEx();

		njRotateY(_nj_current_matrix_ptr_, 0x5000);

		njPushMatrixEx();
		{
			v32 = njSin(dword_12E8AEC[2] + a1a) * v19 + 7.800000190734863;
			njScale(0, 4.0f, 2.0f, v32);
			njTranslate(_nj_current_matrix_ptr_, 0.0, 0.0, 0.85000002);
			njCnkModDrawModel(object_8D9813C7ECAA3378948.chunkmodel);
		}
		njPopMatrixEx();

		njRotateY(_nj_current_matrix_ptr_, 19200);

		njPushMatrixEx();
		{
			v32 = njSin(dword_12E8AEC[3] + a1a) * v19 + 7.099999904632568;
			njScale(0, 4.0f, 2.0f, v32);
			njTranslate(_nj_current_matrix_ptr_, 0.0, 0.0, 0.85000002);
			njCnkModDrawModel(object_8D9813C7ECAA3378948.chunkmodel);
		}
		njPopMatrixEx();
	}
	njPopMatrixEx();
}
void __cdecl sub_547840(ALO_GrowTreeExecutor_Data* a1)
{
	ALO_GrowTreeExecutor_Data* v3; // esi
	signed int v4; // esi

	v3 = a1;
	njPushMatrixEx();
	{
		njTranslate(_nj_current_matrix_ptr_, v3->entityData.Position.x, v3->entityData.Position.y, v3->entityData.Position.z);
		if (v3->TouchAngle)
		{
			njRotateY(_nj_current_matrix_ptr_, v3->TouchAngle);
		}
		if (v3->RollAngle)
		{
			njRotateX(_nj_current_matrix_ptr_, v3->RollAngle);
		}
		if (v3->TouchAngle)
		{
			njRotateY(_nj_current_matrix_ptr_, -v3->TouchAngle);
		}
		v4 = v3->entityData.Rotation.y;
		if (v4)
		{
			njRotateY(_nj_current_matrix_ptr_, v4);
		}
		njTranslate(_nj_current_matrix_ptr_, 0.0, 20.0, 0.0);
		njCnkModDrawModel(object_8D9813C7ECAA3378948.chunkmodel);
		//sub_42D340();
		//ProcessChunkModelsWithCallback((NJS_OBJECT*)&Sphere, ProcessChunkModel);
	}
	njPopMatrixEx();

	njPushMatrixEx();
	{
		njScale(0, 3, 2, 3);
		njTranslate(_nj_current_matrix_ptr_, 0.0, 0.0, 0.85000002);
		njCnkModDrawModel(object_8D9813C7ECAA3378948.chunkmodel);
	}
	njPopMatrixEx();
}
static void __declspec(naked) sub_547840_Hook()
{
	__asm
	{
		push eax // a1

		// Call your __cdecl function here:
		call sub_547840

		pop eax // a1
		retn
	}
}
void __cdecl DrawChaoWorldShadow()
{
	njCnkModDrawModel(object_8D9813C7ECAA3378948.chunkmodel);
}

void __cdecl ChaoTranslate_(float* a1, float x, float y, float z)
{
	njTranslate(0, x, y, z);
	DrawChaoWorldShadow();
}

static void __declspec(naked) ChaoTranslateHook()
{
	__asm
	{
		push[esp + 0Ch] // a4
		push[esp + 0Ch] // a3
		push[esp + 0Ch] // a2
		push eax // a1

		// Call your __cdecl function here:
		call ChaoTranslate_

		pop eax // a1
		add esp, 4 // a2
		add esp, 4 // a3
		add esp, 4 // a4
		retn
	}
}

void __cdecl ChaoScaleHook_(float* a1, float x, float y, float z)
{
	njScale(0, x, y, z);
	DrawChaoWorldShadow();
}

static void __declspec(naked) ChaoScaleHook()
{
	__asm
	{
		push[esp + 0Ch] // a4
		push[esp + 0Ch] // a3
		push[esp + 0Ch] // a2
		push eax // a1

		// Call your __cdecl function here:
		call ChaoScaleHook_

		pop eax // a1
		add esp, 4 // a2
		add esp, 4 // a3
		add esp, 4 // a4
		retn
	}
}

const int C_MTXConcatptr = 0x00426E40;
void ChaoMTXConcatHook()
{
	__asm
	{
		call C_MTXConcatptr
	}
	DrawChaoWorldShadow();
}

const int njScaleVptr = 0x007802B0;
void ChaoPopHook()
{
	DrawChaoWorldShadow();
	njPopMatrixEx();

}


const int sub_793F90Ptr = 0x793F90;
void sub_793F90(NJS_OBJECT* a1, MotionTableData* eax0)
{
	__asm
	{
		mov ecx, a1
		mov eax, eax0
		call sub_793F90Ptr
	}
}

void __cdecl HorseFix(NJS_OBJECT* a1, MotionTableData* eax0)
{
	ModelTransFlag = RenderFlag_Opaque;
	sub_793F90(a1, eax0);
	ModelTransFlag = RenderFlag_Opaque | RenderFlag_Trans;
}
static void __declspec(naked) HorseFixHook()
{
	__asm
	{
		push eax // eax0
		push ecx // a1

		// Call your __cdecl function here:
		call HorseFix

		pop ecx // a1
		pop eax // eax0
		retn
	}
}


FunctionPointer(char*, CCL_IsHitKind, (ObjectMaster* a1, int a2), 0x00486760);
int AL_IsHitKindWithNum(ObjectMaster* a1, int a2, int a3)
{
	char* res = CCL_IsHitKind(a1, a3);
	if (res)
	{
		return *((int*)res + 1);
	}
	return 0;
}
static void __declspec(naked) AL_IsHitKindWithNumDisplay()
{
	__asm
	{
		push[esp + 04h] // a3
		push ecx // a2
		push edx // a1

		// Call your __cdecl function here:
		call AL_IsHitKindWithNum

		pop edx // a1
		pop ecx // a2
		add esp, 4 // a3
		retn
	}
}
void __cdecl ALO_ChaosDriveExecutor_Display_(ObjectMaster* a1)
{
	ALO_ChaosDriveExecutor_Display(a1);

	EntityData1* v1; // ebp
	double v2; // st7
	float* v3; // ebx
	float* v4; // eax
	float* v5; // esi
	double v6; // st7
	int v7; // edx
	float* v8; // eax
	float* v9; // esi
	int v10; // eax
	float* v13; // ebx
	float v14; // [esp+1Ch] [ebp-30h] BYREF
	float v15; // [esp+20h] [ebp-2Ch]
	float v16; // [esp+24h] [ebp-28h]
	float v17; // [esp+28h] [ebp-24h]
	float v18; // [esp+2Ch] [ebp-20h]
	float v19; // [esp+30h] [ebp-1Ch]
	float v20; // [esp+34h] [ebp-18h]
	float v21; // [esp+38h] [ebp-14h]
	float v22; // [esp+3Ch] [ebp-10h]
	float v23; // [esp+40h] [ebp-Ch]
	float v24; // [esp+44h] [ebp-8h]
	float v25; // [esp+48h] [ebp-4h]
	float a1b; // [esp+50h] [ebp+4h]
	float a1c; // [esp+50h] [ebp+4h]
	float a1a; // [esp+50h] [ebp+4h]

	v1 = a1->Data1.Entity;
	if ((v1->Status & 0x8000u) == 0)
	{
		v2 = 0.0;
	}
	else
	{
		v2 = 0.69999999;
	}

	njSetTexture((NJS_TEXLIST*)0x01717DAC);
	njPushMatrixEx();
	a1b = v2;
	a1c = v1->Position.y + a1b;
	njTranslate(0, v1->Position.x, a1c, v1->Position.z);
	v6 = 0.0;

	
	if ((v1->Status & 0x8000u) != 0)
	{
		if (v1->Rotation.y)
		{
			njRotateY(0, v1->Rotation.y);
			v6 = 0.0;
		}
		njScale(0, 1.1f, 1.1f, 1.1f);
		
		njScale(0, 0.7f, 0.7f, 0.7f);
		njCnkModDrawModel(&attach_000D810C);

	}
	else
	{
		a1a = v1->Scale.x;
		if (a1a > 0.05f)
		{
			if (v1->Rotation.y)
			{
				njRotateY(0, v1->Rotation.y);
			}

			
			njScale(0, a1a * 0.65f, a1a * 0.65f , a1a * 1.1f);
			njCnkModDrawModel(&attach_000D810C);
		}
	}
	njPopMatrixEx();
}
void ChaoWorld_Init()
{
	//chaos drive
	WriteData((int*)0x00545636, (int)ALO_ChaosDriveExecutor_Display_);

	//kills existing chao shadows
	WriteJump((void*)0x541370, nullsub_1);

	//queue horse, fixes shadow problem with it + fixes a vanilla problem (fruits get rendered after the horse => fruit gets drawn above horse tail even if behind it)
	WriteCall((void*)0x0580DA4, HorseFixHook);

	//attempt to fix something
	WriteCall((void*)0x0054607D, AL_IsHitKindWithNumDisplay);

	//tree, TODO make these use the ChaoXYZhooks
	WriteJump((void*)0x5479C0, sub_5479C0);
	WriteJump((void*)0x547840, sub_547840_Hook);

	WriteCall((void*)0x00537E3F, ChaoMTXConcatHook); //race tree

	//chao shadows
	WriteCall((void*)0x005406AF, ChaoMTXConcatHook);
	WriteCall((void*)0x00540769, ChaoMTXConcatHook);
	WriteCall((void*)0x00540847, ChaoMTXConcatHook);
	WriteCall((void*)0x005408FE, ChaoMTXConcatHook);
	WriteCall((void*)0x00540997, ChaoMTXConcatHook);
	WriteCall((void*)0x00540A09, ChaoPopHook);
	WriteCall((void*)0x00540A6F, ChaoPopHook);
	WriteCall((void*)0x00540ABE, ChaoPopHook);
	WriteJump((void*)0x00540B53, ChaoPopHook);

	WriteCall((void*)0x0057B956, ChaoMTXConcatHook);//egg
	WriteCall((void*)0x0054A4CB, ChaoMTXConcatHook);//obakehead
	WriteCall((void*)0x00549AC6, ChaoTranslateHook);//seed, njTranslate
	WriteCall((void*)0x00546146, ChaoScaleHook);//fruit, njScaleV
	WriteCall((void*)0x0055A537, ChaoMTXConcatHook);//racefruit, njScaleV
	WriteCall((void*)0x00548C00, ChaoTranslateHook);//minimal, njTranslate

	//toys
	WriteCall((void*)0x00580E55, ChaoMTXConcatHook);//horse
	WriteCall((void*)0x0055CB3D, ChaoMTXConcatHook);//tv
	WriteCall((void*)0x0055D612, ChaoMTXConcatHook);//ball
	WriteCall((void*)0x0057CC4B, ChaoMTXConcatHook);//radicase
	WriteCall((void*)0x00580836, ChaoMTXConcatHook);//box
}
#include "pch.h"
#include "d3d.h"
#include "njCnkModifier.h"
#include "data/Shouko.nja"
#include <math.h>
#include "TransList.h"
#include "data/Bunchin.nja"
#include "njkm.h"
#include "data/MeteorHerd.nja"
#include "data/Block.nja"

float FracInt;
float njFraction(float a1)
{
	return modff(a1, &FracInt);
}

void EnemyModifier(EntityData1* data1, EnemyField38* data2)
{
	float fr14 = data2->fEC;
	float fr15 = fr14 * data2->field_F0;
	njControl3D_Add(0x2400);
	njPushMatrixEx();
	njTranslate(0, data1->Position.x, data1->Position.y, data1->Position.z);
	njRotateY(0, data1->Rotation.y);
	njScale(0, fr14, 1, fr15);
	njCnkModDrawObject(&object_000D8124);
	njPopMatrixEx();
	njControl3D_Remove(0x2400);
}

void DrawEnemyShadow()
{
	njCnkModDrawObject(&object_000D8124);
}

const int C_MTXConcatptr = 0x00426E40;
void EnemyMTXConcatHook()
{
	__asm
	{
		call C_MTXConcatptr
	}
	DrawEnemyShadow();
}

void __cdecl BeetleModifier(ObjectMaster* a1)
{
	njPopMatrixEx();
	EnemyField38* enemyData = (EnemyField38*)a1->EntityData2;
	if (njFraction(a1->Data1.Entity->Scale.x) == 0 && enemyData->fEC > 0)
		EnemyModifier(a1->Data1.Entity, enemyData);
	//DoLighting(*(char*)0x01DE4400);
}

const int ModHookJump = 0x005013C5;
__declspec(naked) void BeetleModifierHook()
{
	__asm
	{
		push[ebp + 8]
		call BeetleModifier
		add esp, 4
		jmp ModHookJump
	}
}

void __cdecl sub_4F9DA0(ObjectMaster* a1)
{
	EntityData1* v1; // ebp
	float* v2; // ebx
	float* v3; // eax
	float* v4; // esi
	float* v5; // eax
	signed int v6; // ebp

	v1 = a1->Data1.Entity;
	DoLighting(8);
	if (v1->Action != 1)
	{
		njPushMatrixEx();
		njTranslate(0, v1->Position.x, v1->Position.y, v1->Position.z);
		if (v1->Rotation.z)
		{
			njRotateZ(0, v1->Rotation.z);
		}
		if (v1->Rotation.x)
		{
			njRotateX(0, v1->Rotation.x);
		}
		if (v1->Rotation.y != -16384)
		{
			njRotateY(0, v1->Rotation.y + 0x4000);
		}
		njSetTexture((NJS_TEXLIST*)0x014CD9F0);
		VoidFunc(sub_42D340, 0x42D340);
		sub_42D340();
		ProcessChunkModelsWithCallback((NJS_OBJECT*)0x014D05AC, ProcessChunkModel);
		njPopMatrixEx();

		_nj_control_3d_flag_ |= 0x2400u;
		njPushMatrixEx();
		njTranslate(0, v1->Position.x, v1->Position.y, v1->Position.z);
		v6 = v1->Rotation.y + 0x4000;
		if (v6)
		{
			njRotateY(0, v6);
		}
		njCnkModDrawObject(&object_001350E0);
		njPopMatrixEx();
		_nj_control_3d_flag_ &= 0xFFFFDBFF;

	}
	DoLighting(*(char*)0x01DE4400);
}

ObjectFunc(sub_6DC900, 0x6DC900);
void BunchinDraw(ObjectMaster *a1)
{
	sub_6DC900(a1);
	EnemyField38* enemy = (EnemyField38*)a1->EntityData2;
	
	//decompiled from dc
	float fr14 = enemy->f0 * 0.5f;

	if (fr14 > 100.0f)
		fr14 = 100.0f;

	njPushMatrix(0);

	float fr12 = 0.06666667f;
	float fr13 = 1.3333334f;

	float fr3, fr6;

	if (a1->Data1.Entity->Rotation.z & 0x1000)
	{
		njTranslate(0, a1->Data1.Entity->Position.x, a1->Data1.Entity->Position.y + fr14 + -102.5, a1->Data1.Entity->Position.z);
		njRotateY(0, a1->Data1.Entity->Rotation.y);
		fr3 = a1->Data1.Entity->Scale.z + 1;
		fr6 = fr3*fr13;
		fr3 = 103.0f;
	}
	else
	{
		njTranslate(0, a1->Data1.Entity->Position.x, a1->Data1.Entity->Position.y + fr14 + -2.5, a1->Data1.Entity->Position.z);
		njRotateY(0, a1->Data1.Entity->Rotation.y);
		fr3 = a1->Data1.Entity->Scale.z + 1;
		fr6 = fr3 * fr13;
		fr3 = 3.0f;
	}
	fr14 += fr3;
	float fr2 = a1->Data1.Entity->Scale.x + 1;

	njScale(0, fr2 * fr13, fr14 * fr12, fr6);
	njCnkModDrawModel(&attach_000B286C);
	njPopMatrix(1);
}

const int sub_48A2D0Ptr = 0x48A2D0;
void sub_48A2D0(int a1)
{
	__asm
	{
		mov eax, a1
		call sub_48A2D0Ptr
	}
}

void __cdecl MinimalMod(int a1)
{
	sub_48A2D0(a1);
	njPushMatrixEx();
	njTranslate(0, 0, 2, 0);
	njScale(0, 1.2,0.5,1.8);
	njCnkModDrawModel(object_000D8124.chunkmodel);
	njPopMatrixEx();
}
static void __declspec(naked) MinimalModHook()
{
	__asm
	{
		push eax // a1

		// Call your __cdecl function here:
		call MinimalMod

		pop eax // a1
		retn
	}
}

void GoalRingShadow()
{
	njPushMatrixEx();
	njScale(0, 30, 5, 10);
	float backup = object_000D8124.chunkmodel->r;
	object_000D8124.chunkmodel->r *= 35.0f;
	njCnkModDrawObject(&object_000D8124);
	object_000D8124.chunkmodel->r = backup;
	njPopMatrixEx();
	njCnkEasyDrawModel((NJS_CNK_MODEL*)0xB4EACC);
}

//replace function that draws a shadow sprite
void __cdecl sub_6D3B40(NJS_VECTOR* a1, float a2)
{
	njPushMatrixEx();
	njTranslate(0, a1->x, a1->y + 0.1f, a1->z);
	njScale(0,a2, 1, a2);
	DrawEnemyShadow();
	njPopMatrixEx();
}
static void __declspec(naked) sub_6D3B40Hook()
{
	__asm
	{
		push[esp + 04h] // a2
		push edx // a1

		// Call your __cdecl function here:
		call sub_6D3B40

		pop edx // a1
		add esp, 4 // a2
		retn
	}
}


void __cdecl IronBallDisp(ObjectMaster* a1)
{
	float* v1; // eax
	EntityData1* v2; // esi
	float* v3; // edi
	Float* v4; // eax
	float* v5; // eax
	float* v6; // edi
	float* v7; // eax
	float* v8; // edi
	float* v9; // eax
	float* v10; // eax
	float* v11; // edi
	float* v12; // ebx
	int v13; // ecx
	float* result; // eax
	float a3; // [esp+1Ch] [ebp-34h]
	float a2; // [esp+1Ch] [ebp-34h]
	float v17; // [esp+1Ch] [ebp-34h]
	float v18[12]; // [esp+20h] [ebp-30h] BYREF
	
	v2 = a1->Data1.Entity;
	njPushMatrixEx();
	a3 = v2->Position.y + 10.0;
	njTranslate(0, v2->Position.x, a3, v2->Position.z);
	if (v2->Rotation.y)
	{
		njRotateY(0, v2->Rotation.y);
	}
	
	njSetTexture((NJS_TEXLIST*)0xB3D120);
	njCnkEasyDrawModel((NJS_CNK_MODEL*)0xB3EA4C);

	njPushMatrixEx();
	sub_6D3B40((NJS_VECTOR*)0xB3E4EC, 5.0);
	njScale(0, v2->Scale.x + 1.0, 1, 1);
	njCnkEasyDrawModel((NJS_CNK_MODEL*)0xB3E49C);
	njPopMatrixEx();

	njPushMatrixEx();
	a2 = (v2->Scale.x + 1.0) * 20.0;
	njTranslate(0, a2, 0.0, 0.0);
	sub_6D3B40((NJS_VECTOR*)0xB3E4EC, 10);
	v13 = (int)a1->EntityData2;
	if (*(int*)v13)
	{
		njRotateX(0, -*(int*)v13);
	}
	njSetTexture((NJS_TEXLIST*)0xB3D100);
	njCnkEasyDrawModel((NJS_CNK_MODEL*)0xB3E374);
	njPopMatrixEx();

	njPushMatrixEx();
	njScale(0, -(v2->Scale.x + 1.0), 1, 1);
	njCnkEasyDrawModel((NJS_CNK_MODEL*)0xB3E49C);
	njPopMatrixEx();

	v17 = -((v2->Scale.x + 1.0) * 20.0);
	njTranslate(0, v17, 0.0, 0.0);
	sub_6D3B40((NJS_VECTOR*)0xB3E4EC, 10);
	v13 = (int)a1->EntityData2;
	if (*(int*)v13)
	{
		njRotateX(0, -*(int*)v13);
	}
	njRotateY(0, 0x8000);
	njSetTexture((NJS_TEXLIST*)0xB3D100);
	njCnkEasyDrawModel((NJS_CNK_MODEL*)0xB3E374);
	njPopMatrixEx();
}

void __cdecl UDREELDisp(ObjectMaster *a1)
{
	ObjectFunc(sub_6E6170, 0x6E6170);
	ObjectFunc(sub_6E6320, 0x6E6320);
	sub_6E6170(a1);
	sub_6E6320(a1);
}

DataPointer(NJS_CNK_MODEL*, off_C42148, 0xC42148);
const int sub_693AC0Ptr = 0x693AC0;
void sub_693AC0(int result, int a2, int a3)
{
	__asm
	{
		mov eax, result
		mov ecx, a2
		push a3
		call sub_693AC0Ptr
		add esp, 4
	}
}
void C_MTXConcat(float* a1, float* a2, float* a3)
{
	__asm
	{
		mov eax, a1
		mov edx, a2
		mov ecx, a3
		call C_MTXConcatptr
	}
}
void __cdecl EggBeetleDisp(ObjectMaster* a1)
{
	ObjectFunc(sub_691280, 0x691280);
	sub_691280(a1);
	njPushMatrixEx();

	float* v14 = *(float**)(*(int*)((int)a1 + 64) + 80);
	if (!v14)
	{
		v14 = _nj_current_matrix_ptr_;
	}
	C_MTXConcat(_nj_current_matrix_ptr_, _nj_current_matrix_ptr_, v14);
	if (a1->Data1.Entity->Rotation.z)
	{
		njRotateZ(0, -a1->Data1.Entity->Rotation.z);
	}
	if (a1->Data1.Entity->Rotation.x)
	{
		njRotateX(0, -a1->Data1.Entity->Rotation.x);
	}
	njRotateY(0, 0x8000);
	
	float v26 = off_C42148->r;
	off_C42148->r = v26 * 1.2f;
	njTranslate(0, 0, *(float*)0xC430AC, 0);
	njScale(0, 1, 1.2, 1);
	if ((unsigned __int16)*off_C42148->vlist == 34)
	{
		sub_693AC0(a1->Data1.Entity->Rotation.z, a1->Data1.Entity->Rotation.x, (int)off_C42148->vlist);
		//off_C42148->vlist = v17;
	}
	njCnkModDrawModel(off_C42148);
	off_C42148->r = v26;
	njPopMatrixEx();
}

float DAT_8c500ff4 = 3.5f;
NJS_VECTOR modVec = { 0,-200,0 };
Sint32 vertex_0019FB78[] = { 0x190022, 0x80000, 0xC1700000u, 0xC1700000u, 0xC1700000u, 0xC1700000u, 0xC1700000u, 0x41700000, 0xC1700000u, 0x41700000, 0xC1700000u, 0xC1700000u, 0x41700000, 0x41700000, 0x41700000, 0xC1700000u, 0xC1700000u, 0x41700000, 0xC1700000u, 0x41700000, 0x41700000, 0x41700000, 0xC1700000u, 0x41700000, 0x41700000, 0x41700000, 0xFF, 0x0 };

Sint16 poly_0019FB24[] = { 0x38, 0x25, 0xC, 0x0, 0x1, 0x2, 0x1, 0x3, 0x2, 0x1, 0x5, 0x3, 0x5, 0x7, 0x3, 0x5, 0x4, 0x7, 0x4, 0x6, 0x7, 0x4, 0x0, 0x6, 0x0, 0x2, 0x6, 0x4, 0x5, 0x0, 0x5, 0x1, 0x0, 0x2, 0x3, 0x6, 0x3, 0x7, 0x6, 0xFF };

NJS_CNK_MODEL attach_0019FBE4 = { vertex_0019FB78, poly_0019FB24, { 0 }, 21.2132f };

NJS_OBJECT object_0019FBFC = { NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_0019FBE4, 0, 0, 0, 0, 0, 0, 1, 1, 1, NULL, NULL };

FunctionPointer(int , sub_5B44E0,(float a1, float arg4, int arg8),0x5B44E0);
void __cdecl FUN_8c500e06(float param_2, float param_3, Rotation* param_1)
{
	sub_5B44E0(param_2, param_3, (int)param_1);
	NJS_CNK_MODEL local_94;
	param_2 = sqrtf(param_2 * param_2 + param_3 * param_3);
	local_94.plist = attach_0019FBE4.plist;
	local_94.center.x = attach_0019FBE4.center.x;
	local_94.center.y = attach_0019FBE4.center.y;
	local_94.r = param_2 * 2.0 + attach_0019FBE4.r;
	local_94.center.z = attach_0019FBE4.center.z;
	local_94.vlist = (Sint32*)&SomeBuffer;
	njCnkModDrawModel((NJS_CNK_MODEL*)&local_94);
	return;
}

DataArray(char, dword_1DEFE24, 0x1DEFE24, 1);
NJS_VECTOR stru_1195CD4 = {};
void __cdecl TruckMod(float a1, float arg4, int arg8)
{
	float* v4; // ebx
	double v5; // st6
	float* v6; // eax
	unsigned int i; // edi
	float* v8; // edx
	int result; // eax
	int v10; // esi
	float* v11; // ecx
	int v12; // ebx
	int v13; // edi
	double v14; // st7
	double v15; // st6
	double v16; // st5
	double v17; // st4
	double v18; // st2
	double v19; // rt1
	double v20; // rt2
	double v21; // st2
	double v22; // st4
	int v23; // eax
	double v24; // st1
	int v25; // eax
	double v26; // st1
	float* v27; // ecx
	int v28; // edx
	NJS_VECTOR a3[4]; // [esp+0h] [ebp-60h] BYREF
	NJS_VECTOR a2[4]; // [esp+30h] [ebp-30h] BYREF
	float v31; // [esp+64h] [ebp+4h]
	float v32; // [esp+68h] [ebp+8h]
	Float v33; // [esp+6Ch] [ebp+Ch]
	Float v34; // [esp+6Ch] [ebp+Ch]
	float v35; // [esp+6Ch] [ebp+Ch]

	a3[2].x = a1;
	a3[0].x = -a3[2].x;
	a3[0].y = 30.0f;
	a3[0].z = -arg4;
	a3[1].y = 130.0f;
	a3[1].z = arg4 + -900.0f;
	a3[2].y = 30.0f;
	a3[3].y = 130.0f;
	a3[1].x = a3[0].x;
	a3[2].z = a3[0].z;
	a3[3].x = a3[2].x;
	a3[3].z = a3[1].z;

	njPushUnitMatrix();
	njRotateEx((Rotation*)arg8, 1);
	for (i = 0; i < 4; ++i)
	{
		njCalcVector(_nj_current_matrix_ptr_, &a2[i], &a3[i], 0);
	}
	njPopMatrixEx();

	njPushUnitMatrix();
	njRotateY(0, ((Rotation*)arg8)->y);
	stru_1195CD4 = { 0, -200, -100 };
	njCalcVector(_nj_current_matrix_ptr_, &stru_1195CD4, &stru_1195CD4, 0);
	njPopMatrixEx();

	SomeBuffer = *attach_0019FBE4.vlist;
	*(int*)dword_1DEFE24 = attach_0019FBE4.vlist[1];
	v8 = (float*)(attach_0019FBE4.vlist + 2);
	result = *(unsigned __int16*)&dword_1DEFE24[2];
	v10 = 0;
	v11 = (float*)0x1DEFE28;
	v12 = *(unsigned __int16*)&dword_1DEFE24[2];
	v13 = 0;
	if (*(unsigned __int16*)&dword_1DEFE24[2])
	{
		v14 = stru_1195CD4.z;
		v15 = stru_1195CD4.y;
		v16 = stru_1195CD4.x;
		v17 = 0.0;
		v18 = 100.0f;
		while (1)
		{
			v20 = v18;
			v21 = v17;
			v22 = v20;
			--v12;
			if (v21 >= v8[1])
			{
				v25 = v13;
				v26 = a2[v13].x;
				v13 = v13 + 1;
				v35 = (v26 - v16) * 0.12f + v16 + v22;
				v32 = (a2[v25].z - v14) * 0.12f + v14 + v22;
				v31 = v15;
			}
			else
			{
				v23 = v10;
				v24 = a2[v10].x;
				v10 = v10 + 1;
				v35 = v24;
				v32 = a2[v23].z;
				v31 = a2[v23].y;
			}
			*v11 = v35;
			v27 = v11 + 1;
			*v27 = v31;
			result = v32;
			*++v27 = v32;
			v8 += 3;
			v11 = v27 + 1;
			v10 &= 3u;
			v13 &= 3u;
			if (!v12)
			{
				break;
			}
			v19 = v21;
			v18 = v22;
			v17 = v19;
		}
	}
	v28 = *(int*)v8;
	*(int*)v11 = v28;
	while (v28 != 255)
	{
		;
	}
	NJS_CNK_MODEL local_94;
	float r = sqrtf(a1 * a1 + arg4 * arg4);
	local_94.plist = attach_0019FBE4.plist;
	local_94.center.x = attach_0019FBE4.center.x;
	local_94.center.y = attach_0019FBE4.center.y;
	local_94.r = r * 2.0 + 300.0f;
	local_94.center.z = attach_0019FBE4.center.z;
	local_94.vlist = (Sint32*)&SomeBuffer;
	njCnkModDrawModel((NJS_CNK_MODEL*)&local_94);
}
void __cdecl TruckDisp(ObjectMaster* a1)
{
	ObjectFunc(sub_5E7070, 0x5E7070);
	sub_5E7070(a1);

	float* v4 = (float*)a1->EntityData2;
	float v82 = v4[54] + 10.0;
	float v83 = a1->Data1.Entity->Position.y + v82 - 5.0 + v4[81];
	njPushMatrixEx();
	njTranslate(0, a1->Data1.Entity->Position.x, v83, a1->Data1.Entity->Position.z);
	TruckMod(70, 60, (int)&a1->Data1.Entity->Rotation);
	njPopMatrixEx();
}

#pragma pack(push, 8)
struct __declspec(align(4)) CarData
{
	const char* field_0;
	float field_4;
	NJS_TEXLIST* field_8;
	NJS_OBJECT* field_C;
	NJS_TEXLIST* field_10;
	NJS_OBJECT* a4;
	int a1;
	CollisionData* collisionData;
	int colliCount;
	float a5[8];
	int flags;
	NJS_OBJECT* obj2;
	int a7;
};
#pragma pack(pop)
DataArray(CarData, stru_10D9810, 0x10D9810, 1);

bool sub_6BC520(NJS_VECTOR* p, float a1, float* a2)
{
	float v4; // [esp+0h] [ebp-10h]
	NJS_VECTOR a2a; // [esp+4h] [ebp-Ch] BYREF

	njCalcVector(_nj_current_matrix_ptr_, &a2a, p, 0);
	v4 = -a2a.z;
	*a2 = v4;
	return -a1 <= v4;
}
ObjectFunc(sub_5E0430, 0x005E0430);
void __cdecl CarDispMod(ObjectMaster* a1)
{
	a1->field_2C = 0;

	sub_5E0430(a1);

	int v27[3] = { 0,0,0 };
	//FUN_8c500e06(&a3, 15, 30);
	int v3;
	EntityData1* v1 = a1->Data1.Entity;
	int index = (int)(a1->Data1.Entity->Scale.x + 0.1f);
	CarData* v2 = &stru_10D9810[index % 30];
	if (!*(int*)0x1AEDCEC
		|| (v3 = v1->Index, (unsigned __int8)v3 >= 0xAu) && ((unsigned __int8)v3 >= 0x14u || (FrameCountIngame & 1) == 0))
	{
		if (v1->NextAction >= 0 && v2)
		{
			float v22;
			float v23 = v2->field_C->chunkmodel->center.z;
			float a3 = v23 + 30.0;
			if (sub_6BC520(&v1->Position, a3, &v22))
			{
				float v4 = v22;
				if (v22 <= (double)*(float*)0x12D3864)
				{
					njPushMatrixEx();
					a3 = *(float*)((int)a1->EntityData2 + 0x54);
					if (v2->field_4 <= v4 || !v2->a4 || (v1->NextAction & 4) != 0)
					{
						
						int v12 = (int)a1->EntityData2;
						v27[0] = v1->Rotation.x + *(int*)((int)(a1->EntityData2) + 0x44);
						v27[1] = v1->Rotation.y + *(int*)((int)(a1->EntityData2) + 0x48);
						v27[2] = v1->Rotation.z + *(int*)((int)(a1->EntityData2) + 0x4c);
						float v14 = v1->Position.y;
						a3 = v14 + a3 + 1.0 + *(float*)(v12 + 104);
						njTranslate(0, v1->Position.x, a3, v1->Position.z);
						FUN_8c500e06(v2->a5[0], v2->a5[2], (Rotation*)v27);
					}
					else
					{
						if (v2->field_C)
						{
							v27[0] = v1->Rotation.x + *(int*)((int)(a1->EntityData2) + 0x44);
							v27[1] = v1->Rotation.y + *(int*)((int)(a1->EntityData2) + 0x48);
							v27[2] = v1->Rotation.z + *(int*)((int)(a1->EntityData2) + 0x4c);

							UnknownData2* v6 = a1->EntityData2;
							a3 = v1->Position.y + a3 + 1.0 + v6->some_vector.z;
							njTranslate(0, v1->Position.x, a3, v1->Position.z);
							FUN_8c500e06(v2->a5[0], v2->a5[2], (Rotation*)v27);
						}

					}
					njPopMatrixEx();
					return;
				}
			}
		}
	}
}
ObjectFunc(sub_5E25D0, 0x5E25D0);
void __cdecl CarCrashDispMod(ObjectMaster* a1)
{
	sub_5E25D0(a1);

	CarData* car = (CarData*)a1->Data2.Undefined;

	njPushMatrixEx();
	njTranslateEx(&a1->Data1.Entity->Position);
	FUN_8c500e06(car->a5[0], car->a5[2], &a1->Data1.Entity->Rotation);
	njPopMatrixEx();

}

void __cdecl GolemUDReel(NJS_CNK_MODEL *a1)
{
	njCnkEasyDrawModel(a1);
	njScale(0, 3.6f, 1.5f, 3.6f);
	DrawEnemyShadow();
}

static void __declspec(naked) GolemUDReelHook()
{
	__asm
	{
		push eax // a1

		// Call your __cdecl function here:
		call GolemUDReel

		pop eax // a1
		retn
	}
}

void __cdecl MeteorHerd_Tank(ObjectMaster* a1)
{
	if (!a1->Data1.Entity->NextAction) 
	{
		njPushMatrixEx();
		njTranslate(0, a1->Data1.Entity->Position.x, a1->Data1.Entity->Position.y, a1->Data1.Entity->Position.z);
		if (a1->Data1.Entity->Rotation.y) njRotateY(0, a1->Data1.Entity->Rotation.y);
		njCnkModDrawModel(&attach_000967C0);
		njPopMatrixEx();
	}
	ObjectFunc(sub_5C3A60, 0x5C3A60);
	sub_5C3A60(a1);
	
}

void __cdecl MeteorHerd_MDCONTBOX(ObjectMaster* a1)
{
	njPushMatrixEx();
	njTranslate(0, a1->Data1.Entity->Position.x, a1->Data1.Entity->Position.y, a1->Data1.Entity->Position.z);
	if (a1->Data1.Entity->Rotation.y) njRotateY(0, a1->Data1.Entity->Rotation.y);
	njCnkModDrawObject(&object_0008A8F4);
	njPopMatrixEx();
	ObjectFunc(sub_5C3E00, 0x5C3E00);
	sub_5C3E00(a1);

}

void __cdecl MeteorHerd_METEOBIG(ObjectMaster* a1)
{
	njPushMatrixEx();
	njTranslate(0, a1->Data1.Entity->Position.x, a1->Data1.Entity->Position.y, a1->Data1.Entity->Position.z);
	njCnkModDrawObject(&object_00089614);
	njPopMatrixEx();
	ObjectFunc(sub_5C4F20, 0x5C4F20);
	sub_5C4F20(a1);
}

void __cdecl MeteorHerd_FireBall(ObjectMaster* a1)
{
	njPushMatrixEx();
	njTranslate(0, a1->Data1.Entity->Position.x, a1->Data1.Entity->Position.y, a1->Data1.Entity->Position.z);
	njCnkModDrawObject(&object_00089614);
	njPopMatrixEx();
	ObjectFunc(sub_5C1370, 0x5C1370);
	sub_5C1370(a1);
}

void BlockDispMod()
{
	njCnkModDrawObject(&object_000BEC94);
}

void BlockDispModHook()
{
	__asm
	{
		call C_MTXConcatptr
	}
	BlockDispMod();
}

void Enemy_Init()
{
	//truck
	WriteData((int*)(0x005E4CCB - 4), (int)TruckDisp);
	WriteJump((void*)0x05E85B0, nullsub_1);

	//cannons core vertical block
	WriteCall((void*)0x004CFDFA, BlockDispModHook);

	//generic pickupable displaysub
	WriteCall((void*)0x006BC8CD, EnemyMTXConcatHook);

	WriteData((int*)(0x005C37D2), (int)MeteorHerd_Tank);
	WriteData((int*)(0x005C3BBF - 4), (int)MeteorHerd_MDCONTBOX);
	WriteData((int*)(0x005C4DF6 - 4), (int)MeteorHerd_METEOBIG);
	WriteData((int*)(0x005C12E2 - 4), (int)MeteorHerd_FireBall);
	WriteJump((void*)0x5C5120, nullsub_1); //meteo big kill sa2b shadow

	//car
	//mission street cars
	WriteCall((void*)0x005B588A, FUN_8c500e06);
	WriteCall((void*)0x005B5944, FUN_8c500e06);
	WriteCall((void*)0x005B7422, FUN_8c500e06);
	WriteCall((void*)0x005B74DA, FUN_8c500e06);
	WriteJump((void*)0x5E2930, nullsub_1); //city escape car crash 
	WriteData((int*)(0x005DE62D -4), (int)CarDispMod); //city escape car render
	WriteData((int*)(0x005E1501 -4), (int)CarCrashDispMod); //city escape car crash render

	//eggbeetle
	WriteData((int*)(0x00690DE3-4), (int)EggBeetleDisp);

	//omochao
	WriteCall((void*)0x006BF73B, EnemyMTXConcatHook); 
	WriteJump((void*)0x6C0CE0, nullsub_1); //kill 2C

	//udreel/pulley
	WriteCall((void*)0x006E63CB, DrawEnemyShadow);
	WriteData((int*)(0x006E569E), (int)UDREELDisp);
	WriteData((int*)(0x006E56A5), (int)nullsub_1);
	//golem's udreel
	WriteCall((void*)0x004BC47C, nullsub_1); //kill sprite shadow call that doesnt actually seem to work
	WriteCall((void*)0x004BC3A6, GolemUDReelHook);
	WriteCall((void*)0x04BC3B0, GolemUDReelHook);

	//ironball2
	WriteData((int*)0x006D3C78, (int)IronBallDisp); //merges sprite shadow sub with displaysub so that the modifier hook can run before the shadows get drawn
	WriteData((int*)0x006D3C85, (int)nullsub_1); //kills field_20 sprite shadow call

	//goalring
	WriteCall((void*)0x006C6E9E, GoalRingShadow);
	WriteJump(GoalRing_2C, nullsub_1);
	WriteCall((void*)0x006C725F, nullsub_1); //kill sprite shadows (theres a sprite shadow version and a shadowmap version?)
	WriteCall((void*)0x006C7001, nullsub_1);

	//hintbox
	WriteCall((void*)0x006E7F34, DrawEnemyShadow); //they replaced the njCnkModDrawModel call with a sprite shadow

	//chaos drive
	WriteCall((void*)0x0048F378, EnemyMTXConcatHook);

	//minimal
	WriteCall((void*)0x0048A425, MinimalModHook);

	//disable existing BUNCHIN shadow
	WriteJump((void*)0x6DCBE0, nullsub_1);
	WriteData((int*)0x006DBC0A, (int)BunchinDraw);

	//beetle shadow
	WriteJump((void*)0x005013B0, BeetleModifierHook);
	//a lot of enemies didnt remove the EnemyModifier call so lets just restore that function to fix like 10 enemies at once
	WriteCall((void*)0x00479AB7, EnemyMTXConcatHook);
	//kyoko
	WriteCall((void*)0x004FC557, EnemyMTXConcatHook);
	WriteCall((void*)0x04FC5F1, EnemyMTXConcatHook);
	WriteCall((void*)0x004FC685, EnemyMTXConcatHook);

	//shouko/fighter jet
	WriteJump((void*)0x4F9DA0, sub_4F9DA0);
}
#include "pch.h"
#include "d3d.h"
#include "njCnkModifier.h"
#include "data/Shouko.nja"
#include <math.h>
#include "TransList.h"
#include "data/Bunchin.nja"

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

void Enemy_Init()
{
	//omochao
	WriteCall((void*)0x006BF73B, EnemyMTXConcatHook); 
	WriteJump((void*)0x6C0CE0, nullsub_1); //kill 2C

	//udreel/pulley
	WriteCall((void*)0x006E63CB, DrawEnemyShadow);
	WriteData((int*)(0x006E569E), (int)UDREELDisp);
	WriteData((int*)(0x006E56A5), (int)nullsub_1);

	//ironball2
	WriteData((int*)0x006D3C78, (int)IronBallDisp); //merges sprite shadow sub with displaysub so that the modifier hook can run before the shadows get drawn
	WriteData((int*)0x006D3C85, (int)nullsub_1); //kills field_20 sprite shadow call

	//goalring
	WriteCall((void*)0x006C6E9E, GoalRingShadow);
	WriteJump(GoalRing_2C, nullsub_1);

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
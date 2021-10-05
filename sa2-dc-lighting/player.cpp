#include "pch.h"
#include "SA2ModLoader.h"
#include "njCnkModifier.h"
#include "IniFile.hpp"

#include "data/PlayerShadow.h"
#include "data/TailsModifier.h"
#include "data/Knuckles.nja"
#include "data/Rouge.nja"
#include "data/SonicModifier.nja"
#include "data/ShadowModifier.nja"
#include "data/EggWalker.nja"
#include "data/TailsWalker.nja"

#pragma region Tails
void sub_750C40(int animation, EntityData1* a2, TailsCharObj2* a3)
{
	_nj_control_3d_flag_ |= 0x2400u;

	int v4 = a3->base.AnimInfo.Animations[animation].ModelNum;
	njPushMatrixEx();
	if (v4 == 208)
	{
		njTranslate(0, *(float*)&a3->field_1BC[92 - 4], *(float*)&a3->field_1BC[96 - 4], *(float*)&a3->field_1BC[100 - 4]);
		if (a2->Rotation.y != 0x8000)
		{
			njRotateY(0, 0x8000 - a2->Rotation.y);
		}
		njCnkModDrawModel(object_0000BDFC.chunkmodel);
		njPopMatrixEx();

		njPushMatrixEx();
		njTranslate(0, *(float*)&a3->field_1BC[44 - 4], *(float*)&a3->field_1BC[48 - 4], *(float*)&a3->field_1BC[52 - 4]);
		if (a2->Rotation.y != 0x8000)
		{
			njRotateY(0, 0x8000 - a2->Rotation.y);
		}
		njScale(0, 1, 1, 0.7f);
		njCnkModDrawModel(object_000D8124.chunkmodel);

		njPopMatrixEx();

		njPushMatrixEx();
		njTranslate(0, *(float*)&a3->field_1BC[56 - 4], *(float*)&a3->field_1BC[60 - 4], *(float*)&a3->field_1BC[64 - 4]);
		if (a2->Rotation.y != 0x8000)
		{
			njRotateY(0, 0x8000 - a2->Rotation.y);
		}
		njScale(0, 1, 1, 0.7f);
		njCnkModDrawModel(object_000D8124.chunkmodel);

		njPopMatrixEx();

		njPushMatrixEx();
		njTranslate(0, *(float*)&a3->field_1BC[68 - 4], *(float*)&a3->field_1BC[72 - 4], *(float*)&a3->field_1BC[76 - 4]);
		if (a2->Rotation.y != 0x8000)
		{
			njRotateY(0, 0x8000 - a2->Rotation.y);
		}
		njScale(0, 2.6, 1, 1);
		njCnkModDrawModel(object_000D8124.chunkmodel);
		njPopMatrixEx();

		njPushMatrixEx();
		njTranslate(0, *(float*)&a3->field_1BC[80 - 4], *(float*)&a3->field_1BC[84 - 4], *(float*)&a3->field_1BC[88 - 4]);
		if (a2->Rotation.y != 0x8000)
		{
			njRotateY(0, 0x8000 - a2->Rotation.y);
		}
		njScale(0, 2.6f, 1, 1);
		njCnkModDrawModel(object_000D8124.chunkmodel);
	}
	else
	{
		if (v4 == 6)
		{
			njTranslate(0, a2->Position.x, a2->Position.y + 0.3f, a2->Position.z);
			if (a2->Rotation.y != 0x8000)
			{
				njRotateY(0, 0x8000 - a2->Rotation.y);
			}
			njScale(0, 5, 1, 5);
			njCnkModDrawModel(object_000D8124.chunkmodel);
		}

	}
	njPopMatrixEx();
	_nj_control_3d_flag_ &= ~0x2400u;

}

static void __declspec(naked) TailsModHook()
{
	__asm
	{
		push[esp + 08h] // a3
		push[esp + 08h] // a2
		push eax // animation

		// Call your __cdecl function here:
		call sub_750C40

		pop eax // animation
		add esp, 4 // a2
		add esp, 4 // a3
		retn
	}
}
#pragma endregion

#pragma region Knuckles
void __cdecl sub_730100(int a1, int a2, int a3)
{
    int v3; // edx
    float* v4; // esi
    float* v5; // eax
    float* v6; // eax
    float* v7; // eax
    float* v8; // eax
    float* v9; // eax
    float* v10; // eax
    float* v11; // eax
    float* v12; // eax
    float* v13; // eax
    float* v14; // esi
    float v15; // [esp+1Ch] [ebp-30h] BYREF
    float v16; // [esp+20h] [ebp-2Ch]
    float v17; // [esp+24h] [ebp-28h]
    float v18; // [esp+28h] [ebp-24h]
    float v19; // [esp+2Ch] [ebp-20h]
    float v20; // [esp+30h] [ebp-1Ch]
    float v21; // [esp+34h] [ebp-18h]
    float v22; // [esp+38h] [ebp-14h]
    float v23; // [esp+3Ch] [ebp-10h]
    float v24; // [esp+40h] [ebp-Ch]
    float v25; // [esp+44h] [ebp-8h]
    float v26; // [esp+48h] [ebp-4h]

    _nj_control_3d_flag_ |= 0x2400u;
    v3 = *(__int16*)(*(int*)(a3 + 408) + 16 * a1 + 2);
    njPushMatrixEx();
    if (v3 == 142)
    {
        njTranslate(0, *(float*)(a3 + 536), *(float*)(a3 + 540), *(float*)(a3 + 544));
        if (*(int*)(a2 + 12) != 0x8000)
        {
            njRotateY(0, 0x8000 - *(int*)(a2 + 12));
        }
		njCnkModDrawObject(&object_0000A3C0);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 488), *(float*)(a3 + 492), *(float*)(a3 + 496));
        if (*(int*)(a2 + 12) != 0x8000)
        {
            njRotateY(0, 0x8000 - *(int*)(a2 + 12));
        }
        njScale(0, *(float*)0xB18F54, 1, 1.1f);
		njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 500), *(float*)(a3 + 504), *(float*)(a3 + 508));
        if (*(int*)(a2 + 12) != 0x8000)
        {
            njRotateY(0, 0x8000 - *(int*)(a2 + 12));
        }
        njScale(0, *(float*)0xB18F54, 1, 1.1f);
		njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 512), *(float*)(a3 + 516), *(float*)(a3 + 520));
        if (*(int*)(a2 + 12) != 0x8000)
        {
            njRotateY(0, 0x8000 - *(int*)(a2 + 12));
        }
        njScale(0, 2.6f, 1, 1.2f);
		njCnkModDrawModel(object_000D8124.chunkmodel);
		njPopMatrixEx();

		njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 524), *(float*)(a3 + 528), *(float*)(a3 + 532));
        if (*(int*)(a2 + 12) != 0x8000)
        {
            njRotateY(0, 0x8000 - *(int*)(a2 + 12));
        }
		njScale(0,2.6f, 1, 1.2f);
		njCnkModDrawModel(object_000D8124.chunkmodel);
    }
    _nj_control_3d_flag_ &= ~0x2400u;
	njPopMatrixEx();
}
static void __declspec(naked) KnucklesMod()
{
	__asm
	{
		push[esp + 08h] // a3
		push[esp + 08h] // a2
		push eax // a1

		// Call your __cdecl function here:
		call sub_730100

		pop eax // a1
		add esp, 4 // a2
		add esp, 4 // a3
		retn
	}
}
#pragma endregion

#pragma region Rouge
void __cdecl sub_7311E0(int a1, EntityData1* a2, int a3)
{
    float* v3; // eax
    int v4; // edx
    float* v5; // esi
    float* v6; // eax
    float* v7; // eax
    float* v8; // eax
    float* v9; // eax
    float* v10; // eax
    float* v11; // eax
    float* v12; // eax
    float* v13; // eax
    float* v14; // eax
    float* v15; // eax
    float* v16; // esi
    float v17; // [esp+1Ch] [ebp-30h] BYREF
    float v18; // [esp+20h] [ebp-2Ch]
    float v19; // [esp+24h] [ebp-28h]
    float v20; // [esp+28h] [ebp-24h]
    float v21; // [esp+2Ch] [ebp-20h]
    float v22; // [esp+30h] [ebp-1Ch]
    float v23; // [esp+34h] [ebp-18h]
    float v24; // [esp+38h] [ebp-14h]
    float v25; // [esp+3Ch] [ebp-10h]
    float v26; // [esp+40h] [ebp-Ch]
    float v27; // [esp+44h] [ebp-8h]
    float v28; // [esp+48h] [ebp-4h]

    _nj_control_3d_flag_ |= 0x2400u;
    v4 = *(__int16*)(*(int*)(a3 + 408) + 16 * a1 + 2);
    njPushMatrixEx();
    if (v4 == 171)
    {
        njTranslate(0, *(float*)(a3 + 536), *(float*)(a3 + 540), *(float*)(a3 + 544));
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njCnkModDrawObject(&object_0000B038);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 488), *(float*)(a3 + 492), *(float*)(a3 + 496));
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njTranslate(0, 0.0, -2.0, 0.0);
        
        njScale(0, 1.2, 1, 0.7f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 500), *(float*)(a3 + 504), *(float*)(a3 + 508));
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njTranslate(0, 0.0, -2.0, 0.0);
        
        njScale(0, 1.2, 1, 0.7f);
        njCnkModDrawModel(object_000D8124.chunkmodel); njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 512), *(float*)(a3 + 516), *(float*)(a3 + 520));
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        
        njScale(0, 2,1,1);
        njCnkModDrawModel(object_000D8124.chunkmodel); njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 524), *(float*)(a3 + 528), *(float*)(a3 + 532));
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njScale(0, 2, 1, 1);
        njCnkModDrawModel(object_000D8124.chunkmodel);
    }
    _nj_control_3d_flag_ &= 0xFFFFDBFF;
    njPopMatrixEx();
}
static void __declspec(naked) RougeMod()
{
    __asm
    {
        push[esp + 08h] // a3
        push[esp + 08h] // a2
        push eax // a1

        // Call your __cdecl function here:
        call sub_7311E0

        pop eax // a1
        add esp, 4 // a2
        add esp, 4 // a3
        retn
    }
}

#pragma endregion

#pragma region Eggman
#include "data/Eggman.nja"
void sub_73F1A0(int a1, EntityData1* a2, int a3)
{
    int v3; // edx
    float* v4; // esi
    float* v5; // eax
    float* v6; // eax
    float* v7; // eax
    float* v8; // eax
    float* v9; // eax
    float* v10; // eax
    float* v11; // eax
    float* v12; // eax
    float* v13; // eax
    float* v14; // eax
    float* v15; // eax
    float* v16; // esi
    float v17; // [esp+1Ch] [ebp-30h] BYREF
    float v18; // [esp+20h] [ebp-2Ch]
    float v19; // [esp+24h] [ebp-28h]
    float v20; // [esp+28h] [ebp-24h]
    float v21; // [esp+2Ch] [ebp-20h]
    float v22; // [esp+30h] [ebp-1Ch]
    float v23; // [esp+34h] [ebp-18h]
    float v24; // [esp+38h] [ebp-14h]
    float v25; // [esp+3Ch] [ebp-10h]
    float v26; // [esp+40h] [ebp-Ch]
    float v27; // [esp+44h] [ebp-8h]
    float v28; // [esp+48h] [ebp-4h]

    _nj_control_3d_flag_ |= 0x2400u;
    v3 = *(__int16*)(*(int*)(a3 + 408) + 16 * a1 + 2);
    njPushMatrixEx();
    if (v3 == 230)
    {
        njTranslate(0, *(float*)(a3 + 536), *(float*)(a3 + 540), *(float*)(a3 + 544));
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njCnkModDrawObject(&object_0000A2C0);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 488), *(float*)(a3 + 492), *(float*)(a3 + 496));
        njTranslate(0, 0.0, -2.0, 0.0);
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njScale(0, *(float*)0x1708AA4, 1, 1.1f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 500), *(float*)(a3 + 504), *(float*)(a3 + 508));
        njTranslate(0, 0.0, -2.0, 0.0);
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njScale(0, *(float*)0x1708AA4, 1, 1.1f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 512), *(float*)(a3 + 516), *(float*)(a3 + 520));
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njScale(0, 2.2, 1.0, 0.7f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 524), *(float*)(a3 + 528), *(float*)(a3 + 532));
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njScale(0, 2.2, 1, 0.7f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
    }
    _nj_control_3d_flag_ &= 0xFFFFDBFF;
    njPopMatrixEx();
}
static void __declspec(naked) EggmanMod()
{
    __asm
    {
        push[esp + 08h] // a3
        push[esp + 08h] // a2
        push eax // a1

        // Call your __cdecl function here:
        call sub_73F1A0

        pop eax // a1
        add esp, 4 // a2
        add esp, 4 // a3
        retn
    }
}
#pragma endregion

void SonicMod(EntityData1* a1, SonicCharObj2* a3, int animation)
{
    int v4 = a3->base.AnimInfo.Animations[animation].ModelNum;
    int charObjHack = (int)a3;
    njControl3D_Add(0x2400);
    njPushMatrixEx();
    if (v4 && v4 == 6)
    {
        njTranslate(0, a1->Position.x, a1->Position.y + 0.3f, a1->Position.z);
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 5, 1, 5);
        njCnkModDrawModel(object_000D8124.chunkmodel);
    }
    else
    {
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x218));
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njCnkModDrawObject(&object_000145FC);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x1E8));
        njTranslate(0, 0, -1, 0);
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 1, 1, 0.7f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x1F4));
        njTranslate(0, 0, -1, 0);
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 1, 1, 0.7f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x200));
        njTranslate(0, 0, -1, 0);
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 2.6f, 1, 1);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x20C));
        njTranslate(0, 0, -1, 0);
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 2.6f, 1, 1);
        njCnkModDrawModel(object_000D8124.chunkmodel);
    }

    njPopMatrixEx();
    njControl3D_Remove(0x2400);
}
void ShadowMod(EntityData1* a1, SonicCharObj2* a3, int animation)
{
    int v4 = a3->base.AnimInfo.Animations[animation].ModelNum;
    int charObjHack = (int)a3;
    njControl3D_Add(0x2400);
    njPushMatrixEx();
    if (v4 != 0x41 && v4 == 0x47)
    {
        njTranslate(0, a1->Position.x, a1->Position.y + 0.3f, a1->Position.z);
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 5, 1, 5);
        njCnkModDrawModel(object_000D8124.chunkmodel);
    }
    else
    {
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x218));
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njCnkModDrawObject(&object_00015690);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x1E8));
        njTranslate(0, 0, -1, 0);
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 1, 1, 0.7f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x1F4));
        njTranslate(0, 0, -1, 0);
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 1, 1, 0.7f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x200));
        njTranslate(0, 0, -1, 0);
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 2.6f, 1, 1);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x20C));
        njTranslate(0, 0, -1, 0);
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 2.6f, 1, 1);
        njCnkModDrawModel(object_000D8124.chunkmodel);
    }

    njPopMatrixEx();
    njControl3D_Remove(0x2400);
}

void __cdecl SonicShadowMod(ObjectMaster* a1)
{
    Sonic_Display(a1);

    if (!a1->Data2.Character->CharID)
    {
        SonicMod(a1->Data1.Entity, (SonicCharObj2*)a1->Data2.Character, a1->Data2.Character->AnimInfo.Current);
    }
    else
    {
        ShadowMod(a1->Data1.Entity, (SonicCharObj2*)a1->Data2.Character, a1->Data2.Character->AnimInfo.Current);
    }
}

void __cdecl sub_745310(int a1, EntityData1* a2, MechEggmanCharObj2* a3)
{
    int v3; // edx
    float* v4; // esi
    float* v5; // eax
    float* v6; // eax
    float* v7; // eax
    float* v8; // eax
    float* v9; // eax
    float* v10; // esi

    _nj_control_3d_flag_ |= 0x2400u;
    v3 = a3->base.AnimInfo.Animations[a1].ModelNum;
    njPushMatrixEx();
    if (v3 == 248)
    {
        njTranslate(0, *(float*)&a3->field_1BC[92-4], *(float*)&a3->field_1BC[96 - 4], *(float*)&a3->field_1BC[100 - 4]);
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njCnkModDrawObject(&object_0000E47C);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)&a3->field_1BC[68 - 4], *(float*)&a3->field_1BC[72 - 4], *(float*)&a3->field_1BC[76 - 4]);
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njCnkModDrawObject(&object_0000E558);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)&a3->field_1BC[80 - 4], *(float*)&a3->field_1BC[84 - 4], *(float*)&a3->field_1BC[88 - 4]);
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njCnkModDrawObject(&object_0000E558);
    }
    _nj_control_3d_flag_ &= ~0x2400u;
    njPopMatrixEx();
}
static void __declspec(naked) EggWalkerMod()
{
    __asm
    {
        push[esp + 08h] // a3
        push[esp + 08h] // a2
        push eax // a1

        // Call your __cdecl function here:
        call sub_745310

        pop eax // a1
        add esp, 4 // a2
        add esp, 4 // a3
        retn
    }
}

void __cdecl sub_748AF0(int a1, EntityData1* a2, int a3)
{
    int v3; // edx
    float* v4; // esi
    float* v5; // eax
    float* v6; // eax
    float* v7; // eax
    float* v8; // eax
    float* v9; // eax
    float* v10; // esi

    _nj_control_3d_flag_ |= 0x2400u;
    v3 = *(__int16*)(*(int*)(a3 + 408) + 16 * a1 + 2);
    njPushMatrixEx();
    if (v3 == 293)
    {
        njTranslate(0, *(float*)(a3 + 536), *(float*)(a3 + 540), *(float*)(a3 + 544));
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njCnkModDrawObject(&object_0000CFEC);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 512), *(float*)(a3 + 516), *(float*)(a3 + 520));
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njCnkModDrawObject(&object_0000D0B0);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 524), *(float*)(a3 + 528), *(float*)(a3 + 532));
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njCnkModDrawObject(&object_0000D0B0);
    }
    _nj_control_3d_flag_ &= ~0x2400u;
    njPopMatrixEx();
}
static void __declspec(naked) TailsWalker()
{
    __asm
    {
        push[esp + 08h] // a3
        push[esp + 08h] // a2
        push eax // a1

        // Call your __cdecl function here:
        call sub_748AF0

        pop eax // a1
        add esp, 4 // a2
        add esp, 4 // a3
        retn
    }
}

void Player_Init(const IniFile* config)
{
    if (config->getBool("Characters", "MechTails", true))
    {
        WriteJump((void*)0x748AF0, TailsWalker);
        WriteData((int*)0x00741088, (int)nullsub_1);
    }

    if (config->getBool("Characters", "MechEggman", true))
    {
        WriteJump((void*)0x745310, EggWalkerMod);
        WriteData((int*)0x00740E28, (int)nullsub_1);
    }

    if (config->getBool("Characters", "SonicShadow", true))
    {
        WriteData((int*)0x0071706F, (int)SonicShadowMod);
        WriteData((int*)0x007175CF, (int)SonicShadowMod);
        WriteJump((void*)0x0071E520, nullsub_1);
    }

	if (config->getBool("Characters", "Knuckles", true))
	{
		WriteJump((void*)0x730100, KnucklesMod);
		WriteJump((void*)0x0072DCE0, nullsub_1);
	}

    if (config->getBool("Characters", "Rouge", true))
    {
        WriteJump((void*)0x7311E0, RougeMod);
        WriteJump((void*)0x0072E390, nullsub_1);
    }

    if (config->getBool("Characters", "Tails", true))
    {
        WriteJump((void*)0x750C40, TailsModHook);
        WriteJump((void*)0x0074FF20, nullsub_1);
    }

    if (config->getBool("Characters", "Eggman", true))
    {
        WriteJump((void*)0x73F1A0, EggmanMod);
        WriteJump((void*)0x0073E8B0, nullsub_1);
    }

    
	
}
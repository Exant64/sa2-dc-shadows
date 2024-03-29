#include "pch.h"
#include "SA2ModLoader.h"
#include "njCnkModifier.h"
#include "IniFile.hpp"

#include "data/playermodel.h"

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
		njScale(0, 2.6f, 1, 1);
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
    int v4; // edx

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
        
        njScale(0, 1.2f, 1, 0.7f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 500), *(float*)(a3 + 504), *(float*)(a3 + 508));
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njTranslate(0, 0.0, -2.0, 0.0);
        
        njScale(0, 1.2f, 1, 0.7f);
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

void sub_73F1A0(int a1, EntityData1* a2, int a3)
{
    int v3; // edx

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
        njTranslate(0, 0.0, -2.0f, 0.0);
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
        njScale(0, 2.2f, 1.0, 0.7f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 524), *(float*)(a3 + 528), *(float*)(a3 + 532));
        if (a2->Rotation.y != 0x8000)
        {
            njRotateY(0, 0x8000 - a2->Rotation.y);
        }
        njScale(0, 2.2f, 1, 0.7f);
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
    OnControl3D(0x2400);
    njPushMatrixEx();
    //spindash or rolling
    if (v4 == 6)
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
        if (a3->base.CharID2 == Characters_Amy)
            njCnkModDrawObject(&object_0000BC64);
        else
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
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 2.6f, 1, 1);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x20C));
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 2.6f, 1, 1);
        njCnkModDrawModel(object_000D8124.chunkmodel);
    }

    njPopMatrixEx();
    OffControl3D(0x2400);
}
void ShadowMod(EntityData1* a1, SonicCharObj2* a3, int animation)
{
    int v4 = a3->base.AnimInfo.Animations[animation].ModelNum;
    int charObjHack = (int)a3;
    OnControl3D(0x2400);
    njPushMatrixEx();
    if (v4 == 6)
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
        if (a3->base.CharID2 == Characters_MetalSonic)
            njCnkModDrawObject(&object_00008C3C);
        else
            njCnkModDrawObject(&object_00015690);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x1E8));        
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 1, 1, 0.7f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x1F4));
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 1, 1, 0.7f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x200));
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 2.6f, 1, 1);
        njCnkModDrawModel(object_000D8124.chunkmodel);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslateEx((NJS_VECTOR*)(charObjHack + 0x20C));
        njRotateY(0, 0x8000 - a1->Rotation.y);
        njScale(0, 2.6f, 1, 1);
        njCnkModDrawModel(object_000D8124.chunkmodel);
    }

    njPopMatrixEx();
    OffControl3D(0x2400);
}

void __cdecl SonicShadowMod(ObjectMaster* a1)
{
    Sonic_Display(a1);

    int currentAnim = a1->Data2.Character->AnimInfo.Current;
    if (a1->Data2.Character->AnimInfo.mtnmode != 2)
    {
        if ((a1->Data1.Entity->Status & Status_Ball) != 0
            && a1->Data2.Character->CharID2 != Characters_MetalSonic
            && ( *(uint8_t*)((int)a1->Data2.Character + 0x360) & 0x11) != 0)
            currentAnim = 30;
    }

    if (!a1->Data2.Character->CharID)
    {
        SonicMod(a1->Data1.Entity, (SonicCharObj2*)a1->Data2.Character, currentAnim);
    }
    else
    {
        ShadowMod(a1->Data1.Entity, (SonicCharObj2*)a1->Data2.Character, currentAnim);
    }
}

void __cdecl sub_745310(int a1, EntityData1* a2, MechEggmanCharObj2* a3)
{
    int v3; // edx

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

    CharObj2Base* obj2 = (CharObj2Base*)a3;
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
        if(obj2->CharID2 == Characters_ChaoWalker)
            njCnkModDrawObject(&object_0000C380);
        else
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

void __cdecl TikalChaos(int a1, int a2, int a3)
{
    int v3; // edx
    
    _nj_control_3d_flag_ |= 0x2400u;
    v3 = *(__int16*)(*(int*)(a3 + 408) + 16 * a1 + 2);
    njPushMatrixEx();
    //if (v3 == 142)
    {
        njTranslate(0, *(float*)(a3 + 536), *(float*)(a3 + 540), *(float*)(a3 + 544));
        if (*(int*)(a2 + 12) != 0x8000)
        {
            njRotateY(0, 0x8000 - *(int*)(a2 + 12));
        }
        CharObj2Base* base = (CharObj2Base*)a3;
        if (base->CharID2 == Characters_Tikal)
            njCnkModDrawObject(&object_00008218);
        else
            njCnkModDrawObject(&object_0000B2A4);
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
        njScale(0, 2.6f, 1, 1.2f);
        njCnkModDrawModel(object_000D8124.chunkmodel);
    }
    _nj_control_3d_flag_ &= ~0x2400u;
    njPopMatrixEx();
}
void __cdecl TikalDisp(ObjectMaster* a1)
{
    Tikal_Display(a1);
    TikalChaos(a1->Data2.Character->AnimInfo.Current, (int)a1->Data1.Entity, (Uint32)a1->Data2.Character);
    //TikalMod(a1->Data1.Entity, (Uint32)a1->Data2.Character, a1->Data2.Character->AnimInfo.Current);
}

void __cdecl ChaosDisp(ObjectMaster* a1)
{
    Chaos_Display(a1);
    TikalChaos(a1->Data2.Character->AnimInfo.Current, (int)a1->Data1.Entity, (Uint32)a1->Data2.Character);
    //TikalMod(a1->Data1.Entity, (Uint32)a1->Data2.Character, a1->Data2.Character->AnimInfo.Current);
}

void __cdecl ChaoWalkers(int a1, int a2, int a3)
{
    int v3; // edx

    CharObj2Base* obj2 = (CharObj2Base*)a3;
    _nj_control_3d_flag_ |= 0x2400u;
    v3 = *(__int16*)(*(int*)(a3 + 408) + 16 * a1 + 2);
    njPushMatrixEx();
    //if (v3 == 248)
    {
        njTranslate(0, *(float*)(a3 + 536), *(float*)(a3 + 540), *(float*)(a3 + 544));
        if (*(int*)(a2 + 12) != 0x8000)
        {
            njRotateY(0, 0x8000 - *(int*)(a2 + 12));
        }
        if (obj2->CharID2 == Characters_ChaoWalker)
            njCnkModDrawObject(&object_0000C380);
        else
            njCnkModDrawObject(&object_0000C380);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 512), *(float*)(a3 + 516), *(float*)(a3 + 520));
        if (*(int*)(a2 + 12) != 0x8000)
        {
            njRotateY(0, 0x8000 - *(int*)(a2 + 12));
        }
        njCnkModDrawObject(&object_0000C4BC);
        njPopMatrixEx();

        njPushMatrixEx();
        njTranslate(0, *(float*)(a3 + 524), *(float*)(a3 + 528), *(float*)(a3 + 532));
        if (*(int*)(a2 + 12) != 0x8000)
        {
            njRotateY(0, 0x8000 - *(int*)(a2 + 12));
        }
        njCnkModDrawObject(&object_0000C4BC);
    }
    _nj_control_3d_flag_ &= ~0x2400u;
    njPopMatrixEx();
}

void __cdecl ChaoWalkerDisp(ObjectMaster* a1)
{
    ChaoWalker_Display(a1);
    ChaoWalkers(a1->Data2.Character->AnimInfo.Current, (int)a1->Data1.Entity, (Uint32)a1->Data2.Character);
    //TikalMod(a1->Data1.Entity, (Uint32)a1->Data2.Character, a1->Data2.Character->AnimInfo.Current);
}

void __cdecl DarkChaoWalkerDisp(ObjectMaster* a1)
{
    DarkChaoWalker_Display(a1);
    ChaoWalkers(a1->Data2.Character->AnimInfo.Current, (int)a1->Data1.Entity, (Uint32)a1->Data2.Character);
    //TikalMod(a1->Data1.Entity, (Uint32)a1->Data2.Character, a1->Data2.Character->AnimInfo.Current);
}

DataArray(NJS_VECTOR*, off_1DD92B0, 0x1DD92B0, 1);
void __cdecl sub_61C6C0Mod(ObjectMaster* obj)
{
    ObjectFunc(sub_61C6C0, 0x61C6C0);
    sub_61C6C0(obj);

    NJS_VECTOR* v5 = off_1DD92B0[*(int*)0x1DD92A0];
    float* v1 = (float*)obj->EntityData2;
    float a1[12];
    a1[9] = v1[5] - v5->x;
    a1[10] = v1[6] - v5->y;
    a1[11] = v1[7] - v5->z;
    a1[8] = a1[9] * a1[9];
    float v6 = a1[8];
    a1[8] = a1[10] * a1[10];
    float v7 = v6 + a1[8];
    a1[8] = a1[11] * a1[11];
    a1[8] = v7 + a1[8];
    if (a1[8] <= 25000000.0)
    {
        _nj_control_3d_flag_ |= 0x2400u;
        
        int* v29 = (int*)obj->EntityData2;
        
        njPushMatrixEx();
        float a3 = *((float*)v29 + 6) + 0.01f - 2.0f;
        njTranslate(0, *((float*)v29 + 5), a3, *((float*)v29 + 7));
        if (v29[4])
        {
            njRotateZ(0, v29[4]);
        }
        if (v29[2])
        {
            njRotateX(0, v29[2]);
        }
        int v31 = *((int*)v29 + 26);
        int v32 = *((int*)v29 + 3);
        if (v31 + v32 != 0x8000)
        {
            njRotateY(0, v31 + v32 - 0x8000);
        }
        int v33 = v29[62] + v29[65];
        if (v33)
        {
            njRotateZ(0, v33);
        }
        int v34 = v29[60] + v29[63];
        if (v34)
        {
            njRotateX(0, v34);
        }
        int v35 = v29[61] + v29[64];
        if (v35)
        {
            njRotateY(0, v35);
        }
        int v36 = *((int*)v29 + 18);
        switch (v36)
        {
        case 0:
            njRotateY(0, 0x4000);
            njCnkModDrawObject(&object_00190A8C);
            break;
        case 1:
            njCnkModDrawObject(&object_00190548);
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            njCnkModDrawObject(&object_001902EC);
            break;
        case 8:
            njScale(0, 5, 1, 5);
            njCnkModDrawObject(&object_000D8124);
            break;
        }

        _nj_control_3d_flag_ &= 0xFFFFDBFF;
        njPopMatrixEx();
    }
}
FunctionPointer(void, sub_42B530,(int a1),0x42B530);
void __cdecl KartShadowHook(int a1)
{
    _nj_control_3d_flag_ |= 0x2400;
    sub_42B530(a1);
    _nj_control_3d_flag_ &= ~0x2400;
}

void __cdecl BoardDisp(ObjectMaster* a1)
{
    ObjectFunc(sub_6F7BE0, 0x6F7BE0);
    sub_6F7BE0(a1);
    if (MainCharObj1[a1->Data1.Entity->NextAction])
    {
        njPushMatrixEx();
        memcpy(_nj_current_matrix_ptr_, (void*)0x1A513B0, 0x30);
        njCnkModDrawObject(&object_00189CBC);
        njPopMatrixEx();
    }
}

void __cdecl BoardCityDisp(ObjectMaster* a1)
{
    ObjectFunc(sub_5EBCE0, 0x5EBCE0);
    sub_5EBCE0(a1);
    if (MainCharObj1[a1->Data1.Entity->NextAction])
    {
        njPushMatrixEx();
        memcpy(_nj_current_matrix_ptr_, (void*)0x1A282F8, 0x30);
        njCnkModDrawObject(&object_00189CBC);
        njPopMatrixEx();
    }
}

void Player_Init(const IniFile* config)
{
    //city escape board shadow
    WriteData((int*)0x005EBCB1, (int)BoardCityDisp);
    WriteJump((void*)0x5EBFC0, nullsub_1);
    //metal harbor board shadow
    WriteData((int*)0x006F7AE1, (int)BoardDisp);

    //karts
    WriteData((int*)(0x0061C592-4), (int)sub_61C6C0Mod);
    WriteJump((void*)0x61CB80, nullsub_1);
    WriteCall((void*)0x0623FBC, KartShadowHook); //enable shadow on course

    if (config->getBool("Characters", "Amy", true))
    {
        WriteData((int*)0x007172E8, (int)SonicShadowMod);
        WriteData((int*)(0x007172FA - 4), (int)nullsub_1);
    }

    if (config->getBool("Characters", "Metal", true))
    {
        WriteData((int*)0x007177CA, (int)SonicShadowMod);
        WriteData((int*)(0x007177DC-4), (int)nullsub_1);
    }

    if (config->getBool("Characters", "Chaos", true))
    {
        WriteData((int*)0x00728CCA, (int)ChaosDisp);
        WriteData((int*)(0x00728CDC - 4), (int)nullsub_1);
    }

    if (config->getBool("Characters", "Tikal", true))
    {
        WriteData((int*)0x00728AD3, (int)TikalDisp);
        WriteData((int*)(0x00728ADE - 4), (int)nullsub_1);
    }

    if (config->getBool("Characters", "ChaoWalker", true))
    {
        WriteData((int*)0x00741268, (int)ChaoWalkerDisp);
        WriteData((int*)(0x0074127A - 4), (int)nullsub_1);
    }

    if (config->getBool("Characters", "DarkChaoWalker", true))
    {
        WriteData((int*)0x00741448, (int)DarkChaoWalkerDisp);
        WriteData((int*)(0x0074145A - 4), (int)nullsub_1);
    }

    if (config->getBool("Characters", "MechTails", true))
    {
        WriteJump((void*)0x748AF0, TailsWalker);
        WriteData((int*)(0x0074108C - 4), (int)nullsub_1);
        WriteData((int*)(0x0074127A - 4), (int)nullsub_1);
    }

    if (config->getBool("Characters", "MechEggman", true))
    {
        WriteJump((void*)0x745310, EggWalkerMod);
        WriteData((int*)(0x00740E2C - 4), (int)nullsub_1);
        WriteData((int*)(0x0074145A - 4), (int)nullsub_1);
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
        WriteData((int*)(0x007283E8 - 4), (int)nullsub_1);
	}

    if (config->getBool("Characters", "Rouge", true))
    {
        WriteJump((void*)0x7311E0, RougeMod);
        WriteData((int*)(0x00728805 - 4), (int)nullsub_1);
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
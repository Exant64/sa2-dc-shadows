#include "pch.h"
#include "njCnkModifier.h"
#include "data/BigFoot.nja"
#include "data/BoomBoo.nja"
#include "enemy.h"
#include "TransList.h"
#include "chao.h"
#include "event.h"
void sub_5D0620_Mod(ObjectMaster* a1)
{
	ObjectFunc(sub_5D0620, 0x5D0620);
	sub_5D0620(a1);

	njControl3D_Add(0x2400);

	njPushMatrixEx();
	njTranslateEx((NJS_VECTOR*)0x1A27E84);
	njRotateY(0, a1->Data1.Entity->Rotation.y + 0x4000);
	njCnkModDrawObject(&object_000F5C7C);
	njPopMatrixEx();

	njPushMatrixEx();
	njTranslateEx((NJS_VECTOR*)(0x1A27E84 + 12));
	njRotateY(0, a1->Data1.Entity->Rotation.y + 0x4000);
	njCnkModDrawObject(&object_000F5EC0);
	njPopMatrixEx();

	njPushMatrixEx();
	njTranslateEx((NJS_VECTOR*)(0x1A27E84 + 12 + 12));
	njRotateY(0, a1->Data1.Entity->Rotation.y + 0x4000);
	njRotateY(0, 0x8000);
	njCnkModDrawObject(&object_000F5EC0);
	njPopMatrixEx();

	njControl3D_Remove(0x2400);
}

VoidFunc(sub_612C80, 0x612C80);
FunctionPointer(void, sub_613F20,(int a1),0x613F20);

FunctionPointer(void, sub_782420, (NJS_OBJECT*), 0x782420);
void __cdecl BossBigBogyDisp(ObjectMaster *a1)
{
    signed int v1; // eax
    signed int v2; // eax
    float v3; // [esp+10h] [ebp-20h]
    int v4; // [esp+18h] [ebp-18h]
    EntityData1* v5; // [esp+1Ch] [ebp-14h]
    int v6; // [esp+20h] [ebp-10h]
    int* v7; // [esp+24h] [ebp-Ch]
    int* v8; // [esp+28h] [ebp-8h]
    MotionTableData* eax0; // [esp+2Ch] [ebp-4h]

    v5 = a1->Data1.Entity;
    v8 = (int*)a1->Data2.Undefined;
    v4 = v8[4];
    eax0 = (MotionTableData*)v8[3];
    v7 = (int*)a1->EntityData2;
    v6 = 0;
    if (*(char*)(v4 + 1) != 2)
    {
        njPushMatrixEx();
        sub_612C80();
        njTranslateV(0, &v5->Position);
        njScaleV_(&v5->Scale);
        v3 = njSin(v7[34]) * 0.8999999761581421 + 55.0;
        njTranslate(0, 0.0, v3, 0.0);
        njRotateZ(0, v5->Rotation.z);
        njRotateX(0, v5->Rotation.x);
        njRotateY(0, v5->Rotation.y);
        if (v7[19])
        {
            njRotateX(0,v7[19]);
        }
        v1 = (int)(njSin(v7[33]) * 3.0 * 182.0444488525391);
        njRotateX(0,v1);
        njTranslate(0, 0.0, -55.0, 0.0);
        v2 = (int)(njSin(v7[35]) * 5.5 * 182.0444488525391);
        njRotateZ(0,v2);
        njRotateY(0, 0x4000);
        njSetTexture(&modeltex_bossbogy_TEXLIST);
        if ((v5->Status & 0x400) != 0)
        {
            SaveConstantAttr();
            njControl3D_Backup();
            njControl3D_Add(0x820);
            OnConstantAttr(0, 0x800);
            SetMaterial(*((float*)v7 + 46), 0.0, 0.0, 0.0);
            v6 = 1;
        }
        if (v5->Action == 11 && v5->NextAction == 5 && FrameCountIngame % 0x14u < 0xA)
        {
            DoLighting(4);
        }
        else
        {
            DoLighting(3);
        }
        sub_793F90((NJS_OBJECT*)0x101DAEC, eax0);
        DoLighting(*(char*)0x01DE4400);
        if (v6 == 1)
        {
            SetMaterial(0.0, 0.0, 0.0, 0.0);
            LoadConstantAttr();
            njControl3D_Restore();
        }
        njPopMatrixEx();
        *(int*)0x01A55834 = 0;
    }
    else
    {
        njPushMatrixEx();
        njTranslateV(0, &v5->Position);
        njRotateY(0, v5->Rotation.z);
        njRotateX(0, v5->Rotation.x);
        NJS_VECTOR scl;
        scl.x = v5->Scale.x;
        scl.y = v5->Scale.x;
        scl.z = v5->Scale.x;
        njScaleV_(&scl);

        float a2 = eax0->frame;
        /*
        *(int*)0x25EFE54 = 0x25EFE60;          // njCnkMotion inlined
        sub_7819A0(&animation_0007C328, *(float*)&v7[52]);
        *(int*)0x1D19C0C = (int)njCnkModDrawModel;
        sub_782420(&object_0006F328);
        */
        ModDrawMotion(&object_0006F328, *(float*)&v7[52], &animation_0007C328);
        njPopMatrixEx();
    }
    sub_613F20(*(int*)(v4 + 12));
}

void Boss_Init()
{
	//big foot
	WriteData((int*)(0x005CC502 - 4), (int)sub_5D0620_Mod);
	WriteJump((void*)0x5D0B30, nullsub_1);

	//big boom boo
    WriteJump((void*)0x612CD0, BossBigBogyDisp);
	WriteCall((void*)0x00613FD0, DrawEnemyShadow);
	WriteJump((void*)0x6133C0, nullsub_1);
}
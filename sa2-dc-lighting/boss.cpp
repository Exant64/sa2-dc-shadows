#include "pch.h"
#include "njCnkModifier.h"
#include "data/BigFoot.nja"
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

void Boss_Init()
{
	WriteData((int*)(0x005CC502 - 4), (int)sub_5D0620_Mod);
	WriteJump((void*)0x5D0B30, nullsub_1);
}
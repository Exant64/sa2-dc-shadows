#include "pch.h"
#include "njCnkModifier.h"

DataArray(NJS_CNK_MODEL*, MODMODmodels, 0x00B4D830, 3);
void __cdecl MODMOD_Disp(ObjectMaster* a1)
{
	njPushMatrixEx();
	njTranslate(0, a1->Data1.Entity->Position.x,
		a1->Data1.Entity->Position.y,
		a1->Data1.Entity->Position.z);
	if (a1->Data1.Entity->Rotation.x)
	{
		njRotateX(0, a1->Data1.Entity->Rotation.x);
	}
	if (a1->Data1.Entity->Rotation.y)
	{
		njRotateY(0, a1->Data1.Entity->Rotation.y);
	}

	njScale(0, a1->Data1.Entity->Scale.x + 1.0f,
		a1->Data1.Entity->Scale.y + 1.0f,
		a1->Data1.Entity->Scale.z + 1.0f);

	njCnkModDrawModel(MODMODmodels[a1->Data1.Entity->Timer]);

	njPopMatrixEx();
}
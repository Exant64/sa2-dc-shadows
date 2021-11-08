#pragma once
#include "SA2ModLoader.h"
DataPointer(int, _nj_control_3d_flag_, 0x025F02D8);
extern "C" {
	__declspec(dllexport)void njCnkModDrawObject(NJS_OBJECT* object);
	__declspec(dllexport)void njCnkModDrawModel(NJS_CNK_MODEL* model);
}
extern NJS_OBJECT object_000D8124;
extern NJS_CNK_MODEL attach_000D810C;
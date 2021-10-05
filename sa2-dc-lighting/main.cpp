#include "pch.h"
#include "SA2ModLoader.h"
#include <d3d9.h>
#include <string>
#include <d3dx9.h>
#include "njCnkModifier.h"
#include "njkm.h"
#include <vector>
#include "TransList.h"
#include <cmath>
#include "d3d.h"
#include "enemy.h"
#include "chao.h"

#include <string>
#include "IniFile.hpp"
#include "player.h"

VoidFunc(Opaque, 0x0042C030);
VoidFunc(AlphaTestDisable, 0x0042C170);
VoidFunc(AlphaTestEnable, 0x0042C0A0);

extern "C"
{
	bool ShadowDebug = false;

	int CheapShadow = 0x80;

	void DefaultCheapShadow()
	{
		CheapShadow = 0x80;
	}
	void ChaoWorldShadowInit()
	{
		VoidFunc(sub_531FC0, 0x531FC0);
		sub_531FC0();
		CheapShadow = 0x73;
	}
	void ChaoWorldShadowExit()
	{
		VoidFunc(sub_5321B0, 0x5321B0);
		sub_5321B0();
		CheapShadow = 0x50;
	}
	void DrawQuad()
	{
		int backup = ScreenFadeARGB.color;
		ScreenFadeARGB.color = 0;
		ScreenFadeARGB.argb.a = 0xFF - CheapShadow; //0x40 = sa2b opacity
		sub_4785A0(); //abuse screenfade to draw fullscreen quad
		ScreenFadeARGB.color = backup;
	}

	void DrawVolumeHook()
	{
		VoidFunc(UpdateObjects, 0x00470010);
		int blendmode = RenferInfo_->Thing;
		device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		device->SetRenderState(D3DRS_STENCILREF, 0);
		device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
		device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
		device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
		UpdateObjects();
		//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


		SetShaders(4);
		//device->SetVertexShader(ninjaVertexShader);
		//device->SetPixelShader(ninjaPixelShader);
		DWORD cullmode;
		DWORD zfunc;
		device->GetRenderState(D3DRS_CULLMODE, &cullmode);
		device->GetRenderState(D3DRS_ZFUNC, &zfunc);

		//turn off color write
		device->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);
		//make sure it doesnt ignore z buffer
		device->SetRenderState(D3DRS_ZENABLE, true);
		device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		//do not write depth data
		device->SetRenderState(D3DRS_ZWRITEENABLE, false);
		//obviously enable stencil stuff
		device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		device->SetRenderState(D3DRS_STENCILREF, 0x1);
		device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
		device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

		//CCW strips
		device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		DrawPolygons();

		//CW strips
		device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_DECR);
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		DrawPolygons();

		EndDraw();
		//restore depth write
		device->SetRenderState(D3DRS_ZWRITEENABLE, true);

		//
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		device->SetRenderState(D3DRS_ZENABLE, false);
		device->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);
		device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

		device->SetRenderState(D3DRS_ZENABLE, FALSE);
		device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// Only write where stencil val >= 0x81
		device->SetRenderState(D3DRS_STENCILREF, 0x81);
		device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);
		device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		DrawQuad();

		device->SetRenderState(D3DRS_ZENABLE, true);

		device->SetRenderState(D3DRS_ZFUNC, zfunc);
		device->SetRenderState(D3DRS_CULLMODE, cullmode);
		device->SetRenderState(D3DRS_STENCILENABLE, false);
		//state->Apply();
		RenferInfo_->Thing = blendmode;
	}

	const int sub_470D20Ptr = 0x470D20;
	void sub_470D20(ObjectMaster* a1)
	{
		__asm
		{
			mov eax, a1
			call sub_470D20Ptr
		}
	}


	void DrawVolumeInit()
	{
		VoidFunc(UpdateObjects, 0x00470010);
		ModelTransFlag = RenderFlag_Opaque|RenderFlag_Trans;
		device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		device->SetRenderState(D3DRS_STENCILREF, 0);
		device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
		device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
		device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
		//VoidFunc(CollisionLoop, 0x00486190);
		//CollisionLoop();
		UpdateObjects();
	}

	void DrawVolumeDisplaySub()
	{
		VoidFunc(UpdateObjects, 0x00470010);
		IDirect3DVertexShader9* backupV;
		IDirect3DPixelShader9* backupP;
		device->GetVertexShader(&backupV);
		device->GetPixelShader(&backupP);
		device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		device->SetRenderState(D3DRS_STENCILREF, 0);
		device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
		device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
		device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

		device->SetVertexShader(ninjaVertexShader);
		device->SetPixelShader(ninjaPixelShader);

		DWORD cullmode;
		DWORD zfunc;
		DWORD zwrite;
		DWORD alphablend;
		DWORD zenable;
		DWORD srcblend, dstblend;
		DWORD alphatest,alphafunc;
		DWORD colorwriteenable;
		device->GetRenderState(D3DRS_ALPHATESTENABLE, &alphatest);
		device->GetRenderState(D3DRS_ZENABLE, &zenable);
		device->GetRenderState(D3DRS_CULLMODE, &cullmode);
		device->GetRenderState(D3DRS_ZFUNC, &zfunc);
		device->GetRenderState(D3DRS_ZWRITEENABLE, &zwrite);
		device->GetRenderState(D3DRS_ALPHABLENDENABLE, &alphablend);
		device->GetRenderState(D3DRS_SRCBLEND, &srcblend);
		device->GetRenderState(D3DRS_DESTBLEND, &dstblend);
		device->GetRenderState(D3DRS_ALPHAFUNC, &alphafunc);
		device->GetRenderState(D3DRS_COLORWRITEENABLE, &colorwriteenable);

		//turn off color write
		if (!ShadowDebug)
		{
			device->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);
			device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		}
		else
		{
			device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		}
		//make sure it doesnt ignore z buffer
		device->SetRenderState(D3DRS_ZENABLE, true);
		device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		//do not write depth data
		device->SetRenderState(D3DRS_ZWRITEENABLE, false);
		//obviously enable stencil stuff
		device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
		device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
		device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
		device->SetRenderState(D3DRS_STENCILREF, 0x1);
		device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
		device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

		//CCW strips
		device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		DrawPolygons();

		//CW strips
		device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_DECR);
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		DrawPolygons();

		EndDraw();
		//restore depth write
		device->SetRenderState(D3DRS_ZWRITEENABLE, true);

		//
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		device->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);
		device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

		device->SetRenderState(D3DRS_ZENABLE, FALSE);
		device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		// Only write where stencil val >= 0x81
		device->SetRenderState(D3DRS_STENCILREF, 0x81);
		device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);
		device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
		int shaderBackup = *(int*)0x01A5579C;
		DrawQuad();
		SetShaders(shaderBackup);
		device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		//device->SetRenderState(D3DRS_SRCBLEND, srcblend);
		//device->SetRenderState(D3DRS_DESTBLEND, dstblend);
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		device->SetRenderState(D3DRS_ALPHAFUNC, alphafunc);
		device->SetRenderState(D3DRS_COLORWRITEENABLE, colorwriteenable);
		device->SetRenderState(D3DRS_ZWRITEENABLE, false);
		device->SetRenderState(D3DRS_ZENABLE, zenable);
		device->SetRenderState(D3DRS_ZFUNC, zfunc);
		device->SetRenderState(D3DRS_CULLMODE, cullmode);
		device->SetRenderState(D3DRS_STENCILENABLE, false);
		//state->Apply();
		device->SetVertexShader(backupV);
		device->SetPixelShader(backupP);
		sub_470D20(ObjectLists[0]);
	}




	

	void Control3DShadowBegin()
	{
		if (_nj_control_3d_flag_ & NJD_CONTROL_3D_SHADOW)
		{
			device->SetRenderState(D3DRS_STENCILREF, 0x80);
		}
		else
			device->SetRenderState(D3DRS_STENCILREF, 0);
	}

	void Control3DShadowEnd()
	{
		NinjaFlag = 0;
		device->SetRenderState(D3DRS_STENCILREF, 0);
	}
	FunctionPointer(void, DrawModelFlags, (signed __int16* a1, unsigned __int16 a2), 0x0056D9F0);
	FunctionPointer(void, sub_56D7C0, (signed __int16* a1, unsigned __int16 a2), 0x56D7C0);
	void __cdecl DrawModelFlagsHook(signed __int16* a1, unsigned __int16 a2)
	{
		Control3DShadowBegin();
		DrawModelFlags(a1,a2);
		Control3DShadowEnd();	
	}
	void __cdecl sub_56D7C0Hook(signed __int16* a1, unsigned __int16 a2)
	{
		Control3DShadowBegin();
		sub_56D7C0(a1, a2);
		Control3DShadowEnd();
	}
	FunctionPointer(int, _DrawSA2BModel, (void* a1), 0x0042BED0);
	int DrawSA2BModelControlHook(void*a1)
	{
		Control3DShadowBegin();
		int retval = _DrawSA2BModel(a1);
		Control3DShadowEnd();
		return retval;
	}
	FunctionPointer(void,sub_42CF30,(signed __int16* a1, int a2),0x42CF30);
	void __cdecl sub_42CF30Hook(signed __int16* a1, int a2)
	{
		Control3DShadowBegin();
		sub_42CF30(a1, a2);
		Control3DShadowEnd();
	}
	FunctionPointer(void, sub_42CAD0, (signed __int16* a1, int a2), 0x42CAD0);
	void __cdecl sub_42CAD0Hook(signed __int16* a1, int a2)
	{
		Control3DShadowBegin();
		sub_42CAD0(a1, a2);
		Control3DShadowEnd();
	}



	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		device = dword_1A557C0->pointerToDevice;
		njInitModifier(device);
	
		//njSetCheapShadowMode, sets opacity for shadows on dc, restored those
		if (!config->getBool("DCShadows", "UseBattleOpacity", false))
		{
			WriteCall((void*)0x00434E9A, DefaultCheapShadow);
			WriteCall((void*)0x0052ACED, ChaoWorldShadowInit);
			WriteCall((void*)0x0052AF1B, ChaoWorldShadowExit);
		}
		else
			CheapShadow = 0x40;

		Enemy_Init();
		ChaoWorld_Init();
		TransList_Init();

		ShadowDebug = config->getBool("DCShadows", "Debug", false);

		//kill existing shadows (field_2C)
		if (config->getBool("DCShadows", "KillBattle", false)) 
		{
			WriteCall((void*)0x004708A3, nullsub_1);
			WriteCall((void*)0x0047050E, nullsub_1);
		}

		Player_Init(config);

		//the actual volume drawing stuff
		WriteCall((void*)0x00470513, DrawVolumeInit);
		WriteCall((void*)0x004708B0, DrawVolumeInit);
			
		WriteCall((void*)0x004700D9, DrawVolumeDisplaySub);
	
		//appropriately set stencil mode for each draw function by checking control3d
		WriteCall((void*)0x0056DF13, DrawModelFlagsHook);
		WriteCall((void*)0x0056DF29, sub_56D7C0Hook);
		WriteCall((void*)0x0042B6E3, DrawSA2BModelControlHook);
		WriteCall((void*)0x0042D610, sub_42CF30Hook);
		WriteCall((void*)0x0042D61F, sub_42CAD0Hook);

		//modmod, i dont know what its used for yet
		//WriteJump((void*)0x6C7B20, MODMOD_Disp);

		//animal shadow check disable to always render shadow
		//WriteData<2>((char*)0x0548B66, (char)0x90);
		//WriteData<2>((char*)0x00548B6B, (char)0x90);
		//WriteData<2>((char*)0x00548B68, (char)0x90);
		
		LoadModVolShaders(path);

		delete config;
	}
	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}

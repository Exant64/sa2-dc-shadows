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
#include "boss.h"

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

		//if the last MagicSDK vertex declaration was PosColor, it will not set the PosColor again
		//and it will use our last set modifier declaration which doesnt have color, and that prevents the quad
		//from getting rendered, so we force our own PosColor declaration

		device->SetVertexDeclaration(pShadowQuadDeclaration);

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
	FunctionPointer(void, GXCallDisplayList, (int arg0, unsigned int a2), 0x0041C9B0);
	void __cdecl DrawSA2BModelControlHook(int arg0, unsigned int a2)
	{
		Control3DShadowBegin();
		GXCallDisplayList(arg0,a2);
		Control3DShadowEnd();
	}


	FunctionPointer(void,sub_42CF30,(signed __int16* a1, int a2),0x42CF30);
	void __cdecl sub_42CF30Hook(signed __int16* a1, int a2)
	{
		Control3DShadowBegin();
		sub_42CF30(a1, a2);
		Control3DShadowEnd();
	}
	FunctionPointer(void, sub_42CAD0, (signed __int16* a1, int a2), 0x42CAD0);

	enum
	{
		GXRender,
		EasyRender,
		SimpleRender,
		EasyMultiRender,
		SimpleMultiRender
	};
	int NinjaRenderMode = 0;
	void __cdecl sub_42CAD0Hook(signed __int16* a1, int a2)
	{
		Control3DShadowBegin();

#ifdef DCLIGHTING
		

		IDirect3DVertexShader9* vertexBackup;
		IDirect3DPixelShader9* pixelBackup;

		device->GetVertexShader(&vertexBackup);
		device->GetPixelShader(&pixelBackup);

		if (NinjaRenderMode > 0)
		{
			device->SetVertexShader(ninjaLVertexShader);
			device->SetPixelShader(ninjaLPixelShader);
			float flag = 0;
			if (NinjaRenderMode == EasyRender)
				flag = 1;
			device->SetVertexShaderConstantF(216, &flag, 1);
			//DoLighting_Simple(LastLightID);
		}
#endif

		sub_42CAD0(a1, a2);

#ifdef DCLIGHTING
		device->SetVertexShader(vertexBackup);
		device->SetPixelShader(pixelBackup);
#endif

		Control3DShadowEnd();
	}

	void __cdecl _njCnkEasyDrawModel(NJS_CNK_MODEL* model)
	{
		NinjaRenderMode = EasyRender;
		njCnkEasyDrawModel(model);
		NinjaRenderMode = GXRender;
	}

	static void __declspec(naked) njCnkEasyDrawModelHook()
	{
		__asm
		{
			push eax // a1

			// Call your __cdecl function here:
			call _njCnkEasyDrawModel

			pop eax // a1
			retn
		}
	}

	void __cdecl _njCnkSimpleDrawModel(NJS_CNK_MODEL* model)
	{
		FunctionPointer(void, sub_42E660, (NJS_CNK_MODEL*), 0x42E660);
		NinjaRenderMode = SimpleRender;
		sub_42E660(model);
		NinjaRenderMode = GXRender;
	}
	FunctionPointer(void, sub_782420, (NJS_OBJECT* a1), 0x782420);
	//ThiscallFunctionPointer(void, sub_7819A0, (NJS_MOTION* a1, float a2), 0x7819A0);
	const int sub_7819A0Ptr = 0x7819A0;
	void sub_7819A0(NJS_MOTION* a1, float a2)
	{
		__asm
		{
			mov ecx, a1
			push a2
			call sub_7819A0Ptr
			add esp, 4
		}
	}
	void __cdecl sub_780870(NJS_OBJECT* a2, float a3, NJS_MOTION* a4)
	{
		*(int*)0x25EFE54 = 0x25EFE60;
		sub_7819A0(a4, a3);
		*(int*)0x1D19C0C = (int)_njCnkSimpleDrawModel;
		sub_782420(a2);
	}
	static void __declspec(naked) sub_780870Hook()
	{
		__asm
		{
			push ecx // a4
			push[esp + 0Ch] // a3
			push[esp + 0Ch] // a2

			// Call your __cdecl function here:
			call sub_780870

			add esp, 4 // a2
			add esp, 4 // a3
			pop ecx // a4
			retn
		}
	}
	void __cdecl sub_690670(NJS_OBJECT* result)
	{
		NJS_OBJECT* v1; // ebp
		float* v2; // ebx
		signed int v3; // esi
		signed int v4; // edi

		v1 = (NJS_OBJECT*)result->child;
		if (v1)
		{
			v2 = _nj_current_matrix_ptr_;
			do
			{
				njPushMatrixEx();
				njTranslate(0, v1->pos[0], v1->pos[1], v1->pos[2]);
				v3 = v1->ang[1];
				v4 = v1->ang[0];
				if (v1->ang[2])
				{
					njRotateZ(0, v1->ang[2]);
				}
				if (v3)
				{
					njRotateY(0, v3);
				}
				if (v4)
				{
					njRotateX(0, v4);
				}
				njCnkModDrawModel(v1->chunkmodel);
				njPopMatrixEx();
				v1 = (NJS_OBJECT*)v1->sibling;
			} while (v1);
			_nj_current_matrix_ptr_ = v2;
		}
	}
	static void __declspec(naked) sub_690670H()
	{
		__asm
		{
			push eax // result

			// Call your __cdecl function here:
			call sub_690670

			pop eax // result
			retn
		}
	}
	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		device = dword_1A557C0->pointerToDevice;
		njInitModifier(device);

#ifdef DCLIGHTING
		//checkpoint lighting test
		WriteCall((void*)0x006D9F51, njCnkEasyDrawModelHook);
		WriteCall((void*)0x006D9FFE, njCnkEasyDrawModelHook);
		WriteCall((void*)0x006DA08A, njCnkEasyDrawModelHook);

		//e_ai
		WriteCall((void*)0x004FF92A, sub_780870Hook);

		WriteCall((void*)0x0050137E, sub_780870Hook); //beetle

		//WriteData((int*)0x00501395, (int)_njCnkSimpleDrawModel);
		//WriteData((int*)0x004FF935, (int)_njCnkSimpleDrawModel);
		
#endif
		//special objects that have a SetCOLShadow (battle shadow) call, make sure to enable the original ninja modifier shadow flag
		WriteData((int*)0x00495F60, (int)(0x80000 | 0x2400));
		WriteData((int*)0x00496322, (int)(~(0x80000 | 0x2400)));

		//egg quarters pillar modifiers
		WriteJump((void*)0x690670, sub_690670H);

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
		Boss_Init();

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
		//WriteCall((void*)0x0042B6E3, DrawSA2BModelControlHook);
		WriteCall((void*)0x0042BFBF, DrawSA2BModelControlHook);
		WriteCall((void*)0x0042BF49, DrawSA2BModelControlHook);
		WriteCall((void*)0x0042D610, sub_42CF30Hook);
		WriteCall((void*)0x0042D61F, sub_42CAD0Hook);

		//modmod, i dont know what its used for yet
		WriteJump((void*)0x6C7B20, MODMOD_Disp);

		//animal shadow check disable to always render shadow
		//WriteData<2>((char*)0x0548B66, (char)0x90);
		//WriteData<2>((char*)0x00548B6B, (char)0x90);
		//WriteData<2>((char*)0x00548B68, (char)0x90);
		
		LoadModVolShaders(path);

		delete config;
	}
	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}

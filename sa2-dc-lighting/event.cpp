#include "SA2ModLoader.h"
#include "njCnkModifier.h"
#include <vector>

#define EVENT_DC_KEY 0xC600000	//dc can load files into any address, so they used this imagebase to gen the events and just loaded it into there
//that obviously doesnt work for us so we have to adjust the pointers

struct EventEntityDC {
	NJS_OBJECT* obj;
	NJS_MOTION* mot;
	NJS_MOTION* shape;
	int a1;
	NJS_VECTOR pos;
	Uint32 flags;
};

struct EventSceneDC {
	EventEntityDC* entities;
	int entityCount;
	char pad[0x20 - 8];
};

struct EventHeaderDC {
	EventSceneDC* pScenes;
	int a2;
	int sceneCount;
};

char EventLoadingBuffer[0x300000];
EventHeaderDC* DCEvent = (EventHeaderDC*)EventLoadingBuffer;

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
void __cdecl ModDrawMotion(NJS_OBJECT* a2, float a3, NJS_MOTION* a4)
{
	*(int*)0x25EFE54 = 0x25EFE60;
	sub_7819A0(a4, a3);
	*(int*)0x1D19C0C = (int)njCnkModDrawModel;
	sub_782420(a2);
}

void RenderEventModScene(int scene)
{
	if (!DCEvent->pScenes || DCEvent->sceneCount != *(int*)(0x0204FE20 + 8)) //if the scenecount isnt equal to the gc scenecount, it would break so stop rendering
		return;

	EventSceneDC* pScene = &DCEvent->pScenes[scene];
	for (int i = 0; i < pScene->entityCount; i++)
	{
		EventEntityDC* entity = &pScene->entities[i];

		if (entity->flags & 0x40) 
		{
			if (entity->mot && entity->obj)
				ModDrawMotion(entity->obj, *(float*)0x1DB0FC4, entity->mot);
			else if (entity->obj)
				njCnkModDrawObject(entity->obj);
		}
	}

}


FunctionPointer(void, sub_5FC170,(NJS_OBJECT* a1, void* baseAddress),0x5FC170);

template<typename T>
void ResolvePointer(T* & p)
{
	int pointer = (int)p;
	if (pointer >= EVENT_DC_KEY && pointer < 0x0C900000)
		p = (T*)((pointer - EVENT_DC_KEY) + (int)EventLoadingBuffer);
	
}

void FixEventMdl(NJS_CNK_MODEL* pMdl)
{
	ResolvePointer<Sint32>(pMdl->vlist);
	ResolvePointer<Sint16>(pMdl->plist);
}

void FixEventObj(NJS_OBJECT* a1, int& count)
{
	do
	{
		count++;
		if (a1->chunkmodel)
		{
			ResolvePointer<void>(a1->model);
			FixEventMdl(a1->chunkmodel);
		}

		if (a1->child) 
		{
			ResolvePointer<NJS_OBJECT>(a1->child);
			FixEventObj(a1->child, count);
		}

		if (a1->sibling)
			ResolvePointer<NJS_OBJECT>(a1->sibling);
		
		a1 = a1->sibling;
	} while (a1);
}

void FixMDATA(void* data, int count, int mdata)
{
	char* pData = (char*)data;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < mdata; j++)
		{
			int mdataPtr = *(int*)(pData + j * 4);
			if (mdataPtr >= EVENT_DC_KEY && mdataPtr < 0x0C900000)
				mdataPtr = (mdataPtr - EVENT_DC_KEY) + (int)EventLoadingBuffer;
			*(int*)(pData + j * 4) = mdataPtr;	
		}
		pData += (4 * 2 * mdata);
	}
}

void FixEventMot(NJS_MOTION* pMot, NJS_OBJECT* obj, int count)
{
	ResolvePointer<void>(pMot->mdata);
	int mcount = 0;
	if (pMot->type & NJD_MTYPE_POS_0)
		mcount++;
	if (pMot->type & NJD_MTYPE_ANG_1)
		mcount++;
	if (pMot->type & NJD_MTYPE_SCL_2)
		mcount++;
	if (pMot->type & NJD_MTYPE_VEC_3)
		mcount++;
	if (pMot->type & NJD_MTYPE_VERT_4)
		mcount++;
	if (pMot->type & NJD_MTYPE_QUAT_1)
		mcount++;

	if(mcount < 1 || mcount > 4) while (1) { PrintDebug("bad mdata"); }

	FixMDATA(pMot->mdata, count, mcount);
}

void FixEventEntity(EventEntityDC* entity)
{
	//dont bother to process if not modifier
	if (entity->flags & 0x40) 
	{	
		int count = 0;
		if (entity->obj)
		{
			ResolvePointer<NJS_OBJECT>(entity->obj);

			FixEventObj(entity->obj, count);
		}
		if (entity->mot && !entity->obj)
			while (1) { PrintDebug("motion and no object"); } //spin, debugging thing
		if (entity->mot)
		{
			ResolvePointer<NJS_MOTION>(entity->mot);

			FixEventMot(entity->mot, entity->obj, count);
		}
	}
}

const int sub_4532C0Ptr = 0x4532C0;
int sub_4532C0(void* a3, int a4, const char* a5)
{
	int retval;
	__asm {
		mov esi, a5
		mov edi, a4

		push a3
		call sub_4532C0Ptr
		mov retval, eax
		add esp, 4
	}
	return retval;
}

FunctionPointer(void, FixEventFile, (void* a1),0x005FEAD0);

const int sub_426670Ptr = 0x426670;
void sub_426670(const char* a1)
{
	__asm
	{
		mov eax, a1
		call sub_426670Ptr
	}
}
VoidFunc(sub_600210, 0x600210);
void __cdecl LoadEventMods(void * a1)
{
	//FixEventFile(a1);
	sub_600210();

	sub_426670("..");

	char v38[32];
	sprintf(v38, "e%04d.prs", *(int*)0x1A28AF4);
	int v24;
	v24 = sub_4532C0((void*)0x01DEFE20, 0, v38);

	sub_426670("EVENT");

	if (v24 < 0) 
	{
		DCEvent->pScenes = 0;
		DCEvent->sceneCount = 0;
		PrintDebug("failed to load DC event");
		return;
	}
	
	PRSDec((unsigned __int8*)0x01DEFE20, (uint8_t*)EventLoadingBuffer);
	EventHeaderDC* header = (EventHeaderDC*)EventLoadingBuffer;

	ResolvePointer<EventSceneDC>(header->pScenes);

	for (int i = 0; i <= header->sceneCount; i++)
	{
		if (header->pScenes[i].entities) 
		{
			ResolvePointer<EventEntityDC>(header->pScenes[i].entities);

			for (int j = 0; j < header->pScenes[i].entityCount; j++)
				FixEventEntity(&header->pScenes[i].entities[j]);
		}
	}
}

void RenderEventMods()
{
	VoidFunc(sub_5FA520, 0x5FA520);
	sub_5FA520(); 
	RenderEventModScene(0); //always draw first scene
	RenderEventModScene(*(int*)0x01DB0FC8); //currentscene
}

void Event_Init()
{
	//kill sa2b shadows in events
	WriteJump((void*)0x5FAC80, nullsub_1);

	WriteCall((void*)0x005FAC39, RenderEventMods);
	WriteCall((void*)0x005FFFE1, LoadEventMods);
}
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

EventHeaderDC* DCEvent;

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
	if (DCEvent->sceneCount != *(int*)(0x0204FE20 + 8)) //if the scenecount isnt equal to the gc scenecount, it would break so stop rendering
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

char EventLoadingBuffer[0x300000];
FunctionPointer(void, sub_5FC170,(NJS_OBJECT* a1, void* baseAddress),0x5FC170);
int ResolvePointer(int p)
{
	if (p >= EVENT_DC_KEY && p < 0x0C900000)
		return (p - EVENT_DC_KEY) + (int)EventLoadingBuffer;
	return p;
}

void FixEventMdl(NJS_CNK_MODEL* pMdl)
{
	pMdl->vlist = (Sint32*)ResolvePointer((int)pMdl->vlist);
	pMdl->plist = (Sint16*)ResolvePointer((int)pMdl->plist);
}

void FixEventObj(NJS_OBJECT* a1, int& count)
{
	do
	{
		count++;
		if (a1->chunkmodel)
		{
			a1->chunkmodel = (NJS_CNK_MODEL*)ResolvePointer((int)a1->chunkmodel);
			FixEventMdl(a1->chunkmodel);
		}

		if (a1->child) 
		{
			a1->child = (NJS_OBJECT*)ResolvePointer((int)a1->child);
			FixEventObj(a1->child, count);
		}

		if (a1->sibling)
			a1->sibling = (NJS_OBJECT*)ResolvePointer((int)a1->sibling);
		
		a1 = a1->sibling;
	} while (a1);
}

void FixMDATA1(NJS_MDATA1* data, int count)
{
	for (int i = 0; i < count; i++) 
	{
		data->p[0] = (void*)ResolvePointer((int)data->p[0]);
		data++;
	}
}

void FixMDATA2(NJS_MDATA2* data, int count)
{
	for (int i = 0; i < count; i++) 
	{
		data->p[0] = (void*)ResolvePointer((int)data->p[0]);
		data->p[1] = (void*)ResolvePointer((int)data->p[1]);
		data++;
	}
}

void FixMDATA3(NJS_MDATA3* data, int count)
{
	for (int i = 0; i < count; i++) 
	{
		data->p[0] = (void*)ResolvePointer((int)data->p[0]);
		data->p[1] = (void*)ResolvePointer((int)data->p[1]);
		data->p[2] = (void*)ResolvePointer((int)data->p[2]);
		data++;
	}
}

void FixMDATA4(NJS_MDATA4* data, int count)
{
	for (int i = 0; i < count; i++) {
		data->p[0] = (void*)ResolvePointer((int)data->p[0]);
		data->p[1] = (void*)ResolvePointer((int)data->p[1]);
		data->p[2] = (void*)ResolvePointer((int)data->p[2]);
		data->p[3] = (void*)ResolvePointer((int)data->p[3]);
		data++;
	}
}

void FixEventMot(NJS_MOTION* pMot, NJS_OBJECT* obj, int count)
{
	pMot->mdata = (void*)ResolvePointer((int)pMot->mdata);
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

		switch (mcount)
		{
		case 1:
			FixMDATA1((NJS_MDATA1*)pMot->mdata, count);
			break;
		case 2:
			FixMDATA2((NJS_MDATA2*)pMot->mdata, count);
			break;
		case 3:
			FixMDATA3((NJS_MDATA3*)pMot->mdata, count);
			break;
		case 4:
			FixMDATA4((NJS_MDATA4*)pMot->mdata, count);
			break;
		default:
			while (1) { PrintDebug("bad mdata"); }
			break;
		}
	
}

void FixEventEntity(EventEntityDC* entity)
{
	//dont bother to process if not modifier
	if (entity->flags & 0x40) 
	{	
		int count = 0;
		if (entity->obj)
		{
			entity->obj = (NJS_OBJECT*)ResolvePointer((int)entity->obj);
			FixEventObj(entity->obj, count);
		}
		if (entity->mot && !entity->obj)
			while (1) { PrintDebug("motion and no object"); } //spin, debugging thing
		if (entity->mot)
		{
			entity->mot = (NJS_MOTION*)ResolvePointer((int)entity->mot);
			FixEventMot(entity->mot, entity->obj, count);
		}
	}
}

const int sub_428B90Ptr = 0x428B90;
int sub_428B90(void* a3, int a4, const char* a5)
{
	int retval;
	__asm {
		push a4
		push a3
		mov ecx, a5
		call sub_428B90Ptr
		mov retval, eax
		add esp,8
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
void __cdecl LoadEventMods(void * a1)
{
	FixEventFile(a1);

	sub_426670("..");

	char v38[255];
	sprintf((char*)&v38, "e%04d.prs", *(int*)0x1A28AF4);
	int v24;
	v24 = sub_428B90(&SomeBuffer, 0, v38);
	sub_426670("EVENT");
	if (v24 < 0)
		return;
	
	PRSDec((unsigned __int8*)&SomeBuffer, (uint8_t*)EventLoadingBuffer);

	EventHeaderDC* header = (EventHeaderDC*)EventLoadingBuffer;
	DCEvent = header;
	header->pScenes = (EventSceneDC*)ResolvePointer((int)header->pScenes);
	
	for (int i = 0; i <= header->sceneCount; i++)
	{
		if (header->pScenes[i].entities) 
		{
			header->pScenes[i].entities = (EventEntityDC*)ResolvePointer((int)header->pScenes[i].entities);
			
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
	WriteCall((void*)0x005FFF7F, LoadEventMods);
}
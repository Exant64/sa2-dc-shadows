#include "pch.h"
#include <sa2modloader.h>
#include "njkm.h"
#include "njCnkModifier.h"

typedef NJS_VECTOR NJS_CNK_MOD_BUF;

typedef struct NJS_MODIFIER_WORK {
    int vNum; //0
    Uint16* pVlist; //4
    NJS_CNK_MOD_BUF* pVertexBuf; //8
    void* pSQ; //12
} NJS_MODIFIER_WORK;

NJS_MODIFIER_WORK _nj_modifier_work;

extern void* njEndModifier(void*);
PMODTRI njCnkModPolygon(Uint16* plist, NJS_CNK_MOD_BUF* buf, Uint16 val, PMODTRI sq)
{
    PMODTRI pSQ = sq;
    Uint16 count;
    int calc;

    count = val & 0x3FFF;


    calc = ((val >> -0xE) & 3) << 1;

    do
    {
        NJS_CNK_MOD_BUF* tri1 = &buf[*plist++];
        NJS_CNK_MOD_BUF* tri2 = &buf[*plist++];
        NJS_CNK_MOD_BUF* tri3 = &buf[*plist++];
        pSQ->v1.x = tri1->x;
        pSQ->v1.y = tri1->y;
        pSQ->v1.z = tri1->z;

        pSQ->v2.x = tri2->x;
        pSQ->v2.y = tri2->y;
        pSQ->v2.z = tri2->z;

        pSQ->v3.x = tri3->x;
        pSQ->v3.y = tri3->y;
        pSQ->v3.z = tri3->z;

        pSQ++;

        //(*(Uint8**)&plist) += calc;

    } while (--count);

    return pSQ;
}

int njCnkModVertex(NJS_MODIFIER_WORK* work)
{
    NJS_CNK_MOD_BUF* buf = work->pVertexBuf;
    float* vertex = (float*)work->pVlist;
    int num = 0;
    for (int i = 0; i < work->vNum; i++)
    {
        buf[i].x = vertex[0];
        buf[i].y = vertex[1];
        buf[i].z = vertex[2];
        njCalcVector(_nj_current_matrix_ptr_, &buf[i], &buf[i], 0);
        vertex += 3;
        num++;
    }
    return num;
}

extern PMODTRI njStartModifier();
extern void njEndVertex(PMODTRI);

DataPointer(void*, _nj_vertex_buf_, 0x025EFE48);
const int sub_42F640Ptr = 0x42F640;
int njCnkModelClip(NJS_CNK_MODEL* a1)
{
    int retval;
    __asm
    {
        mov esi, a1
        call sub_42F640Ptr
        mov retval, eax
    }
    return retval;
}
int _njCnkModDrawModel(NJS_CNK_MODEL* model)
{
    Uint16* vlist, * plist;
    Uint16 type, offset, num;
    NJS_CNK_MOD_BUF* buf = (NJS_CNK_MOD_BUF*)_nj_vertex_buf_;
    NJS_CNK_MOD_BUF* oBuf;
    if (_nj_control_3d_flag_ & NJD_CONTROL_3D_MODEL_CLIP)
        if (model->r > 0 && njCnkModelClip(model))
        {
            return 1;
        }
    vlist = (Uint16*)model->vlist;

    type = *vlist++;
    vlist++;
    offset = *vlist++;
    num = *vlist++;

    oBuf = &buf[offset];

    _nj_modifier_work.vNum = num;
    _nj_modifier_work.pVlist = vlist;
    _nj_modifier_work.pVertexBuf = oBuf;

    if (type != NJD_CV)
    {
        return 0;
    }
    njCnkModVertex(&_nj_modifier_work);

    plist = (Uint16*)model->plist;
    while ((type = *plist++) != 0xFF)
    { 
        type = (Uint8)type;
        if (type >= NJD_MATOFF)
        {
            if (type >= NJD_VOLOFF)
            {
                Uint16 size = *plist++;
                Uint16 val_ = *plist++;
                if (type == NJD_CO_P3)
                {
                    PMODTRI sq = njStartModifier();
                    PMODTRI end = njCnkModPolygon(plist, buf, val_, sq);
                    njEndVertex(end);
                }
                plist += (size - 1);
            }
            else
            {
                Uint16 val = *plist++;
                plist += val;
            }
        }
    }

    return 0;
}

void _njCnkModDrawObject(NJS_OBJECT* obj)
{
    Uint32 clip;
    do
    {
        Uint32 eval = obj->evalflags;
        if ((eval & 7) == 7)
        {
            if (!(eval & 8))
                _njCnkModDrawModel(obj->chunkmodel);
            if (!(eval & NJD_EVAL_BREAK))
                _njCnkModDrawObject(obj->child);

        }
        else
        {
            njPushMatrixEx();
            if (!(eval & 1))
                njTranslateEx((NJS_VECTOR*)obj->pos);
            if (!(eval & 2))
                njRotateEx((Rotation*)obj->ang, eval & 0x20);
            if (!(eval & 4))
                njScale(0,obj->scl[0], obj->scl[1], obj->scl[2]);
            if (!(eval & 8))
                clip = _njCnkModDrawModel(obj->chunkmodel);
            if (!(eval & NJD_EVAL_BREAK))
                if (eval & NJD_EVAL_CLIP && clip)
                    _njCnkModDrawObject(obj->child);
            njPopMatrixEx();
        }
        obj = obj->child;
    } while (obj);
}
void njCnkModDrawModel(NJS_CNK_MODEL* model)
{
    _njCnkModDrawModel(model);
}
void njCnkModDrawObject(NJS_OBJECT* object)
{
    _njCnkModDrawObject(object);
}
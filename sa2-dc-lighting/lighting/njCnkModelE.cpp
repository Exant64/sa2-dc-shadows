#include "SA2ModLoader.h"


typedef	struct {
    Float	lx, ly, lz;			/* light vector		*/
    Float	diff, ambi;			/* light intensity	*/
    Sint32	n;					/* vertex num		*/
    void* vertex;			/* vertex list		*/
    void* vbuf;				/* work buf address	*/
    void* sq;				/* work buf sq adrs	*/
    Float	xad, yad;			/* screen distans aspect	*/
    Float	cx, cy;				/* screen center	*/
    Uint32	dmy[3];
} NJS_CNK_EASY_VERTEX;
NJS_CNK_EASY_VERTEX _nj_vertex_easy;

float _nj_easy_light_col_[3];

void njCnkSetEasyLightIntensity(float diff, float ambi)
{
    _nj_vertex_easy.diff = -diff;
    _nj_vertex_easy.ambi = ambi;
}

void njCnkSetEasyLightColor(float result, float a2, float a3)
{
    _nj_easy_light_col_[0] = result;
    _nj_easy_light_col_[1] = a2;
    _nj_easy_light_col_[2] = a3;
}

void njCnkSetEasyLight(float x, float y, float z)
{
    _nj_vertex_easy.xad = 1;
    _nj_vertex_easy.yad = 1;
    _nj_vertex_easy.cx = HorizontalResolution / 2.0f;
    _nj_vertex_easy.cy = VerticalResolution / 2.0f;

    _nj_vertex_easy.lx = x;
    _nj_vertex_easy.ly = y;
    _nj_vertex_easy.lz = z;
}
int _nj_cnk_clip_num_;
int _nj_calc_vertex_;
int _nj_cnk_clip_vtx_;
int easy_vert_col_flag;
float njInnerProduct(float* a1, float* a2)
{
    return (float)((float)(a1[1] * a2[1]) + (float)(*a1 * *a2)) + (float)(a1[2] * a2[2]);
}

void njCnkEasyVertexVN(NJS_CNK_EASY_VERTEX& vertex)
{    
    NJS_VECTOR* vec = (NJS_VECTOR*)vertex.vertex;
    NJS_CNK_EASY_BUF* buf = (NJS_CNK_EASY_BUF * )vertex.vbuf;
    for(int i = 0; i < vertex.n; i++)
    {
        
        NJS_VECTOR vert = *vec;
        NJS_VECTOR norm = vec[1];
        //njCalcVector(_nj_current_matrix_ptr_, &vert, &vert, 0);
        //njCalcPoint(&norm, &norm, _nj_current_matrix_ptr_);

        float dot = njInnerProduct(&vertex.lx, &norm.x) * vertex.diff;
        if (dot < 0) dot = 0;
        dot += vertex.ambi;
        if (dot > 1)
            dot = 1;
        
        buf[i].x = vert.x;
        buf[i].y = vert.y;
        buf[i].ooz = 1.0f / vert.z;
        buf[i].inten = dot;

        vec += 2;
    }
}

void njCnkEasyVlist(Uint16* vlist, NJS_CNK_EASY_BUF* buf)
{
    Uint16* vl = vlist;
    Uint16 type;

    while ((type = *vl++) != 0x00FF)
    {
        Uint32 size;
        Uint32 v1;
        Uint32 num;

        size = *vl++;
        v1 = *vl++;
        num = *vl++;

        _nj_vertex_easy.n = num;
        _nj_vertex_easy.vertex = vl;
        _nj_vertex_easy.vbuf = buf + v1;

        switch ((Uint8)type)
        {
        case NJD_CV_VN:
            njCnkEasyVertexVN(_nj_vertex_easy);
            break;
        case NJD_CV:
            //njCnkDirectVertexV((Float*)vl, buf, num);
            break;
        case NJD_CV_D8:
            //njCnkDirectVertexVD8((Float*)vl, buf, num);
           // unk_A90 = 1;
            break;
        case NJD_CV_VN_D8:
            //njCnkDirectVertexVND8((Float*)vl, buf, num);
            //unk_A90 = 1;
            break;
        default:
            return;
        }

        //if (_nj_direct_compile_mode_ == 1)
           // unk_A90 = 1;

        vl += ((size * 2) - 2);
    }
}

void njSetCnkTextureNum(int a1, int a2)
{

}

void njSetCnkBlendMode(int a1){}
void njCnkSetMaterial(unsigned int a1, unsigned int *a2, float* a3, float* a4, float* a5)
{

}

float col[4];
void njCnkEasyPlist(short* a1, long a2, NJS_CNK_EASY_BUF* a3)
{
    __int16 v5; // r3
    __int16* v6; // r4
    unsigned int v7; // r0
    int v8; // r8
    __int16 v9; // t1
    unsigned int v17; // r1
    unsigned int* v18; // r1

    while (1)
    {
        v6 = a1 + 1;
        v5 = *a1;
        v7 = *a1;
        if (v7 == 255)
            break;
    LABEL_3:
        v8 = (unsigned __int8)v5;
        if ((unsigned __int8)v5 <= 7u)
        {
            switch ((char)v5)
            {
            case 0:
            case 2:
            case 3:
                a1 = v6;
                continue;
            case 1:
                a1 = v6;
                njSetCnkBlendMode(v7);
                v9 = *v6++;
                v5 = v9;
                v7 = v9;
                if (v9 != 255)
                    goto LABEL_3;
                break;
            default:
                a1 = v6;
                continue;
            }
            break;
        }
        if ((unsigned __int8)v5 <= 0xFu)
        {
            v17 = a1[1];
            a1 += 2;
            njSetCnkTextureNum(v7, v17);
        }
        else if ((unsigned __int8)v5 <= 0x3Fu)
        {
            v18 = (unsigned int*)(a1 + 2);
            a1 += a1[1] + 2;
            njCnkSetMaterial(v7, v18, col, 0, 0);
        }
        else
        {
        }
    }
}

int _njCnkEasyDrawModel(NJS_CNK_MODEL* a1)
{
    unsigned int v5 = 0; // r4

    if (!a1)
        return 0;
    //if ((nj_control_3d_flag_ & 0x100) != 0 && *(float*)(v1 + 20) > 0.0 && njCnkModelClip(v1))
        //return -1;
    if (a1->vlist)
        njCnkEasyVlist((Uint16*)a1->vlist, (NJS_CNK_EASY_BUF*)0x025EFE48);
    if (a1->plist)
        njCnkEasyPlist(a1->plist, v5, (NJS_CNK_EASY_BUF*)0x025EFE48);
    return 0;
}
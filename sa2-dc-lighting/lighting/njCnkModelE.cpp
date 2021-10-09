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
        njCalcVector(_nj_current_matrix_ptr_, &vert, &vert, 0);
        njCalcPoint(&norm, &norm, _nj_current_matrix_ptr_);

        float dot = njInnerProduct(&vertex.lx, &norm.x);
        
        buf[i].x = vert.x;
        buf[i].x = vert.y;

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
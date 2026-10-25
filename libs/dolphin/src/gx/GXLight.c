#include <dolphin/gx.h>
#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXInit.h>

extern float cosf(float x);
extern float sqrtf(float x);

// GXLightObj private data
typedef struct
{
    u32 reserved[3];
    u32 Color;
    f32 a[3];
    f32 k[3];
    f32 lpos[3];
    f32 ldir[3];
} __GXLightObjInt_struct;



void GXInitLightSpot(GXLightObj* lt_obj, f32 cutoff, GXSpotFn spot_func)
{
    f32 a0, a1, a2;
    f32 r;
    f32 d;
    f32 cr;
    __GXLightObjInt_struct* obj;

    obj = (__GXLightObjInt_struct*)lt_obj;

    if (cutoff <= 0.0f || cutoff > 90.0f)
        spot_func = GX_SP_OFF;

    r = (3.1415927f * cutoff) / 180.0f;
    cr = cosf(r);

    switch (spot_func)
    {
    case GX_SP_FLAT:
        a0 = -1000.0f * cr;
        a1 = 1000.0f;
        a2 = 0.0f;
        break;
    case GX_SP_COS:
        a1 = 1.0f / (1.0f - cr);
        a0 = -cr * a1;
        a2 = 0.0f;
        break;
    case GX_SP_COS2:
        a2 = 1.0f / (1.0f - cr);
        a0 = 0.0f;
        a1 = -cr * a2;
        break;
    case GX_SP_SHARP:
        d = 1.0f / ((1.0f - cr) * (1.0f - cr));
        a0 = (cr * (cr - 2.0f)) * d;
        a1 = 2.0f * d;
        a2 = -d;
        break;
    case GX_SP_RING1:
        d = 1.0f / ((1.0f - cr) * (1.0f - cr));
        a2 = -4.0f * d;
        a0 = a2 * cr;
        a1 = (4.0f * (1.0f + cr)) * d;
        break;
    case GX_SP_RING2:
        d = 1.0f / ((1.0f - cr) * (1.0f - cr));
        a0 = 1.0f - ((2.0f * cr * cr) * d);
        a1 = (4.0f * cr) * d;
        a2 = -2.0f * d;
        break;
    case GX_SP_OFF:
    default:
        a0 = 1.0f;
        a1 = 0.0f;
        a2 = 0.0f;
        break;
    }
    obj->a[0] = a0;
    obj->a[1] = a1;
    obj->a[2] = a2;
}


void GXInitLightPos(GXLightObj* lt_obj, f32 x, f32 y, f32 z)
{
    __GXLightObjInt_struct* obj;

    obj = (__GXLightObjInt_struct*)lt_obj;

    obj->lpos[0] = x;
    obj->lpos[1] = y;
    obj->lpos[2] = z;
}


void GXInitLightColor(GXLightObj* lt_obj, GXColor* color)
{
    __GXLightObjInt_struct* obj;

    obj = (__GXLightObjInt_struct*)lt_obj;

    *(u32*)&obj->Color = *(u32*)color;
}

static inline u32 ConvLightID2Num(GXLightID id)
{
    switch (id)
    {
    case GX_LIGHT0:
        return 0;
    case GX_LIGHT1:
        return 1;
    case GX_LIGHT2:
        return 2;
    case GX_LIGHT3:
        return 3;
    case GX_LIGHT4:
        return 4;
    case GX_LIGHT5:
        return 5;
    case GX_LIGHT6:
        return 6;
    case GX_LIGHT7:
        return 7;
    default:
        return 8;
    }
}

static inline void PushLight(const register GXLightObj* lt_obj, register void* dest)
{
    register u32 zero, color;
    register f32 a0_a1, a2_k0, k1_k2;
    register f32 px_py, pz_dx, dy_dz;
#ifdef __MWERKS__ // clang-format off
	asm {
		lwz     color, 12(lt_obj)
		xor     zero, zero, zero
		psq_l   a0_a1, 16(lt_obj), 0, 0
		psq_l   a2_k0, 24(lt_obj), 0, 0
		psq_l   k1_k2, 32(lt_obj), 0, 0
		psq_l   px_py, 40(lt_obj), 0, 0
		psq_l   pz_dx, 48(lt_obj), 0, 0
		psq_l   dy_dz, 56(lt_obj), 0, 0

		stw     zero,  0(dest)
		stw     zero,  0(dest)
		stw     zero,  0(dest)
		stw     color, 0(dest)
		psq_st  a0_a1, 0(dest), 0, 0
		psq_st  a2_k0, 0(dest), 0, 0
		psq_st  k1_k2, 0(dest), 0, 0
		psq_st  px_py, 0(dest), 0, 0
		psq_st  pz_dx, 0(dest), 0, 0
		psq_st  dy_dz, 0(dest), 0, 0
	}
#endif // clang-format on
}

void GXLoadLightObjImm(GXLightObj* lt_obj, GXLightID light)
{
    u32 addr;
    u32 idx;
    __GXLightObjInt_struct* obj;

    obj = (__GXLightObjInt_struct*)lt_obj;

    idx = 31 - __cntlzw(light);

    idx &= 7;

    addr = idx * 0x10 + 0x600;
    GX_WRITE_U8(0x10);
    GX_WRITE_U32(addr | 0xF0000);

    PushLight(lt_obj, (void*)GXFIFO_ADDR);

    gx->bpSentNot = 1;
}





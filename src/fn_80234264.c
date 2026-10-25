// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234264-0x80234444 (480B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"

s32 GetStructure_2(void *, s32, s32 *, s32);
s32 GetInteger(void *, s32, s32 *, s32);
void *fn_80238964(void);
s32 fn_80238970(void);
s32 fn_80238104(void *, s32);
s32 fn_80238784(void *, s32, u8 *, f32 *);
void *fn_801FC0E0(void);
s32 fn_801FA924(void *, f32, f32, f32, f32);
void *fn_801F672C(void);
s32 fn_801F63F0(void *, f32, f32, f32, f32);
s32 fn_80240B0C(void *, u8, u8, u8, u8, u8, u8);
extern f32 lbl_802B09C4;

/* 16-byte out-param: fn_80238784 fills it, the game copies it as two
   8-byte __ps_t pairs, and then reads the LOW lane of each pair -- so the
   two floats it uses are elements 0 and 2, not 0 and 1. */
typedef struct { f32 x[4]; } S8;
/* a 4-byte out-param whose top byte is the only part the game reads */
typedef struct { char p[3]; u8 b3; } B4;
/* the four GetInteger out-params plus the GetStructure_2 handle, one object:
   GCC 2.95 rounds every separate 4-byte stack local up to 8, five of them blow
   the frame by 0x10; as one 20-byte struct the region is exactly 0x18. */
typedef struct { s32 s; B4 x, z, w, l; } Slots;

s32 ScriptCanCleanlyResizePark(void *arg0) {
    u8 in[6];
    B4 sp10;
    S8 dst;
    f32 opt[3];
    S8 res;
    Slots sl;
    register B4 *pa __asm__("r25");
    register B4 *pb __asm__("r29");
    B4 *pc, *pd;
    u8 *pin;
    B4 *p10;
    s32 var_r29;
    u8 bx, bz, bw, blv;

    fn_80240B0C(in, 0, 0, 0, 0, 0, 0);
    sl.s = 0;
    if (GetStructure_2(arg0, QB_NEWBOUNDS, &sl.s, 0) != 0) {
        pa = &sl.x; pb = &sl.z; pc = &sl.w; pd = &sl.l;
        GetInteger((void *)sl.s, QB_X, (s32 *)pa, 0);
        GetInteger((void *)sl.s, QB_Z, (s32 *)pb, 0);
        GetInteger((void *)sl.s, QB_W, (s32 *)pc, 0);
        GetInteger((void *)sl.s, QB_L, (s32 *)pd, 0);
        pin = in;
        bz = pb->b3;
        bx = pa->b3;
        pin[1] = 0;
        in[0] = bx;
        pin[2] = bz;
        bw = pc->b3;
        blv = pd->b3;
        pin[4] = 1;
        pin[5] = blv;
        pin[3] = bw;
        *(s32 *)&sp10 = *(s32 *)in;
        p10 = &sp10;
        *(u16 *)((char *)p10 + 4) = *(u16 *)((char *)pin + 4);
        var_r29 = (fn_80238104(fn_80238964(), (s32)p10) == 0);
        fn_80238784(&res, fn_80238970(), pin, opt);
        *(volatile __ps_t *)&dst = *(volatile __ps_t *)&res;
        *(volatile __ps_t *)((char *)&dst + 8) = *(volatile __ps_t *)((char *)&res + 8);
        if (fn_801FA924(fn_801FC0E0(), dst.x[0] + lbl_802B09C4, dst.x[2] + lbl_802B09C4,
                        (dst.x[0] + opt[0]) - lbl_802B09C4,
                        (dst.x[2] + opt[2]) - lbl_802B09C4) != 0) {
            var_r29 = 0;
        }
        if (fn_801F63F0(fn_801F672C(), dst.x[0], dst.x[2], dst.x[0] + opt[0], dst.x[2] + opt[2]) != 0) {
            var_r29 = 0;
        }
        return var_r29;
    }
    return 0;
}

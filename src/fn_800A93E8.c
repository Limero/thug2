// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A93E8-0x800A94C8 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
#include "dolphin/SN_PS.h"

extern __ps_t lbl_802981C0;
extern f32 lbl_80298224;
extern f32 lbl_80298228;

typedef struct {
    char pad0x0[0x8];
    __ps_t unk0x8;
    __ps_t unk0x10;
    char pad0x18[0x4C];
    s32 unk0x64;
    char pad0x68[0x8];
    __ps_t unk0x70;
    __ps_t unk0x78;
    __ps_t unk0x80;
    __ps_t unk0x88;
    char pad0x90[0x20];
    f32 unk0xB0;
    s32 unk0xB4;
    f32 unk0xB8;
    char pad0xBC[0x30];
    s32 unk0xEC;
} A93E8;

typedef struct {
    __ps_t unk0x0;
    __ps_t unk0x8;
} A93E8Src;

void fn_800A94C8(A93E8 *);
s32 fn_800A952C(A93E8 *);
void fn_800A9200(A93E8 *);

void fn_800A93E8(A93E8 *arg0, s32 arg1, A93E8Src *arg2) {
    f32 c;
    SN_PS_type sp8;

    c = lbl_80298224;
    arg0->unk0xEC = 0;
    arg0->unk0xB4 = 0;
    arg0->unk0x64 = arg1;
    arg0->unk0xB8 = c;
    arg0->unk0xB0 = c;
    arg0->unk0x70 = arg2->unk0x0;
    arg0->unk0x78 = arg2->unk0x8;
    arg0->unk0x8 = arg0->unk0x70;
    arg0->unk0x10 = arg0->unk0x78;
    fn_800A94C8(arg0);
    goto body;
head:
    if (fn_800A952C(arg0) == 0) {
        goto end;
    }
body:
    {
        __ps_t f11;
        __ps_t f13;
        __ps_t f0;
        __ps_t f10;
        __ps_t f12;
        f32 thr;
        f32 x;
        f32 y;
        SN_PS_type res;

        f13 = arg0->unk0x80;
        f0 = arg0->unk0x88;
        f10 = arg0->unk0x10;
        f11 = arg0->unk0x8;
        f13 = __builtin_ps_sub(f13, f11);
        f12 = lbl_802981C0;
        f13 = __builtin_ps_mul(f13, f13);
        thr = lbl_80298228;
        f0 = __builtin_ps_sub(f0, f10);
        f0 = __builtin_ps_merge00(f0, f12);
        f0 = __builtin_ps_madds0(f0, f0, f13);
        f0 = __builtin_ps_sum0(f0, f0, f0);
        f0 = __builtin_ps_rsqrte(f0);
        f0 = __builtin_ps_res(f0);
        res.ps = f0;
        x = res.flt.hi;
        y = x;
        if (y < thr) {
            goto head;
        }
    }
    fn_800A9200(arg0);
end:
    return;
}

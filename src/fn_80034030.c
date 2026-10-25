// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80034030-0x800340C4 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct S34030_sub { char pad0x0[0x20]; f32 unk0x20; } S34030_sub;
typedef struct S34030_big { char pad0x0[0x20C]; s32 unk0x20C; s32 unk0x210; } S34030_big;
typedef struct S34030_obj {
    char pad0x0[4];
    S34030_sub *unk0x4;
    char pad0x8[0x28];
    S34030_big *unk0x30;
    s32 unk0x34;
} S34030_obj;
typedef struct S34030_r { char pad0x0[8]; s32 unk0x8; s32 unk0xC; } S34030_r;
S34030_r *fn_80033604(S34030_obj *);
s32 fn_8002A3E0(s32, void *, void *, s32, s32, S34030_big *, f32);
s32 fn_8006FB50(S34030_big *, s32);
bool fn_80034030(S34030_obj *arg0, void *arg1) {
    s32 temp_r9;
    s32 var_r0;
    temp_r9 = fn_80033604(arg0)->unk0x8;
    __asm__ volatile("" : "+r"(temp_r9));
    var_r0 = (temp_r9 != 0) ? temp_r9 + 0x408 : 0;
    arg0->unk0x30->unk0x20C = var_r0;
    arg0->unk0x30->unk0x210 = fn_80033604(arg0)->unk0xC;
    fn_8002A3E0(arg0->unk0x34, arg1, arg1 + 0x400, arg1 + 0x800, -1, arg0->unk0x30, arg0->unk0x4->unk0x20);
    fn_8006FB50(arg0->unk0x30, 1);
    return true;
}

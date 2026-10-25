// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80101AE0-0x80101B80 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns -mps-float
#include "types.h"
#include "mem.h"

extern char lbl_8029C228[];

typedef struct AE0Obj {
    char pad0x0[4];
    u16 flag04;
    char pad0x6[2];
    s32 unk0x8;
    s32 unk0xC;
    char pad0x10[0x98];
    f32 f_A8;
    s32 w_AC;
    __ps_t p_B0;
    __ps_t p_B8;
    __ps_t p_C0;
    __ps_t p_C8;
} AE0Obj;

void fn_80102444(void *, void *);
s32 fn_80103A50(s32, s32, s32);

void *fn_80101AE0(AE0Obj *arg0, s32 arg1) {
    AE0Obj *temp = Mem_Alloc2(0xD0);
    f32 fa8;
    s32 a8;
    s32 wac;
    u16 flg;
    __ps_t p0;
    __ps_t p1;
    __ps_t p2;
    __ps_t p3;

    fn_80102444(temp, arg0);
    fa8 = arg0->f_A8;
    wac = *(volatile s32 *)&arg0->w_AC;
    a8 = arg0->unk0x8;
    temp->unk0xC = (s32)lbl_8029C228;
    p0 = arg0->p_B0;
    temp->f_A8 = fa8;
    flg = temp->flag04;
    flg |= 0x8000;
    temp->p_B0 = p0;
    p1 = arg0->p_B8;
    temp->w_AC = wac;
    temp->p_B8 = p1;
    p2 = arg0->p_C0;
    temp->flag04 = flg;
    temp->p_C0 = p2;
    p3 = arg0->p_C8;
    temp->p_C8 = p3;
    temp->unk0x8 = fn_80103A50(a8, arg1, 0);
    return temp;
}

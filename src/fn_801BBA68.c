// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BBA68-0x801BBAE0 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern f32 lbl_802AC3B0;
void fn_801BBA68(Unk_0C1F2A74 *arg0, __ps_t *arg1) {
    f32 c;
    f32 t54;
    s32 z;

    c = lbl_802AC3B0;
    z = 0;
    ((__ps_t *)((char *)arg0 + (s32)0x48))[0] = arg1[0];
    ((__ps_t *)((char *)arg0 + (s32)0x50))[0] = arg1[1];
    ((__ps_t *)((char *)arg0 + (s32)0x58))[0] = arg1[2];
    ((__ps_t *)((char *)arg0 + (s32)0x60))[0] = arg1[3];
    ((__ps_t *)((char *)arg0 + (s32)0x68))[0] = arg1[4];
    ((__ps_t *)((char *)arg0 + (s32)0x70))[0] = arg1[5];
    ((__ps_t *)((char *)arg0 + (s32)0x38))[0] = arg1[8];
    ((__ps_t *)((char *)arg0 + (s32)0x40))[0] = arg1[9];
    arg0->unk0x34 = *((f32 *)&((Unk_C7387A53 *)arg1)->unk0x50);
    t54 = *((volatile f32 *)&((Unk_C7387A53 *)arg1)->unk0x54);
    arg0->unk0xE8 = c;
    arg0->unk0x114 = t54;
    arg0->unk0x30 = z;
    *(f32 *)((char *)arg0->unk0x174 + (s32)0x2C) = c;
    ((CScript *)arg0->unk0x174)->unk0x1C = z;
}

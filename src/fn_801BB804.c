// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BB804-0x801BB8C4 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
void fn_8009F53C(void *);
void *Mem_Alloc2(s32 arg0);
s32 fn_80007B94(void);
extern char lbl_802AC518[];
extern f32 lbl_802AC394;
extern f32 lbl_802AC398;
extern f32 lbl_802AC39C;
extern f32 lbl_802AC3A0;
extern f32 lbl_802AC3A4;

typedef struct {
    char pad0x0[0x4];
    s32 unk0x4;
    char pad0x8[0x10];
    s32 unk0x18;
    char pad0x1C[0x10];
    s32 unk0x2C;
    char pad0x30[0x4];
    f32 unk0x34;
    char pad0x38[0xB8];
    f32 unk0xF0;
    f32 unk0xF4;
    f32 unk0xF8;
    f32 unk0xFC;
    f32 unk0x100;
    char pad0x104[0x10];
    f32 unk0x114;
    char pad0x118[0x4];
    f32 unk0x11C;
    char pad0x120[0x58];
    s32 unk0x178;
    s32 unk0x17C;
    s32 unk0x180;
    s32 unk0x184;
} S804;

void *fn_801BB804(S804 *arg0) {
    s32 v178;
    s32 vc;
    f32 t34;
    f32 t11c;
    f32 tf0;
    f32 tf4;
    f32 t100;

    fn_8009F53C(arg0);
    arg0->unk0x18 = (s32) lbl_802AC518;
    for (vc = 4; vc != 0; vc--) {
    }
    arg0->unk0x2C = 0;
    arg0->unk0x4 = QB_SKATERCAMERA;
    Mem_Alloc2(0x98);
    v178 = fn_80007B94();
    t34 = lbl_802AC394;
    t11c = lbl_802AC398;
    tf0 = lbl_802AC39C;
    tf4 = lbl_802AC3A0;
    t100 = lbl_802AC3A4;
    arg0->unk0x178 = v178;
    arg0->unk0x11C = t11c;
    arg0->unk0xF0 = tf0;
    arg0->unk0xF4 = tf4;
    arg0->unk0x114 = t34;
    arg0->unk0x34 = t34;
    arg0->unk0xF8 = t34;
    arg0->unk0xFC = t34;
    arg0->unk0x100 = t100;
    arg0->unk0x17C = 0;
    arg0->unk0x180 = 0;
    arg0->unk0x184 = 0;
    return arg0;
}

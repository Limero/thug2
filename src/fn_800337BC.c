// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800337BC-0x8003388C (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -O1
#include "types.h"
#include "structs.h"
void fn_8002A3E0(s32, s32, s32, s32, s32, s32, s32, float);
s32 fn_80033604(s32);
s32 fn_8006FB50(Unk_5E1C040A *, s32);
s32 fn_80026BF8(void);
bool fn_800337BC(void *arg0, s32 arg1) {
    register s32 r9 asm("r9");
    register s32 r0 asm("r0");
    register s32 r3 asm("r3");
    register s32 r4 asm("r4");
    register s32 r5 asm("r5");
    register s32 r6 asm("r6");
    register s32 r7 asm("r7");
    register s32 r8 asm("r8");
    register s32 r31 asm("r31");
    register s32 r30 asm("r30");
    register float f1 asm("fr1");

    r31 = (s32)arg0;
    r30 = arg1;
    r0 = ((Unk_C8FEE62D *)r31)->unk0x28;
    if (r0 == -1) {
        r3 = ((Unk_C8FEE62D *)r31)->unk0x1C;
        r0 = ((Unk_DB0E2BAB *)r3)->unk0x24;
        if (r0 != 0) {
            r3 = fn_80026BF8();
            ((Unk_C8FEE62D *)r31)->unk0x28 = r3;
        } else {
            r3 = ((Unk_C8FEE62D *)r31)->unk0x20;
            ((Unk_C8FEE62D *)r31)->unk0x1C = fn_8006FB50(r3, 0);
        }
    }
    r3 = r31;
    r3 = fn_80033604(r3);
    r9 = ((Unk_DB0E2BAB *)r3)->unk0x8;
    if (r9 != 0) {
        r0 = r9 + 0x408;
    } else {
        r0 = 0;
    }
    r9 = ((Unk_C8FEE62D *)r31)->unk0x20;
    r3 = r31;
    ((CScript *)r9)->unk0x20C = r0;
    r3 = fn_80033604(r3);
    r0 = ((Unk_DB0E2BAB *)r3)->unk0xC;
    r4 = r30;
    r9 = ((Unk_C8FEE62D *)r31)->unk0x20;
    r5 = r4 + 0x400;
    r6 = r4 + 0x800;
    ((CScript *)r9)->unk0x210 = r0;
    r9 = ((Unk_C8FEE62D *)r31)->unk0x4;
    r7 = ((Unk_C8FEE62D *)r31)->unk0x28;
    r8 = ((Unk_C8FEE62D *)r31)->unk0x20;
    f1 = *((float *)&((CScript *)r9)->unk0x20);
    r3 = ((Unk_C8FEE62D *)r31)->unk0x1C;
    fn_8002A3E0(r3, r4, r5, r6, r7, r8, r9, f1);
    r3 = ((Unk_C8FEE62D *)r31)->unk0x20;
    r4 = 0;
    fn_8006FB50(r3, 1);
    return true;
}

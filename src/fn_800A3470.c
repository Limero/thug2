// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A3470-0x800A34EC (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
typedef struct {
    char p0[0x10];
    s16 o1;
    char p1[2];
    void *f1;
    s16 o2;
    char p3[2];
    void *f2;
} VT3470;

void fn_800A3470(Unk_C7387A53 *arg0, CScript *arg1, s32 arg2) {
    VT3470 *vt;
    vt = (VT3470 *)arg0->unk0x2C;
    arg0->unk0x24 = arg2;
    arg0->unk0x28 = 1;
    ((s32 (*)(void *, void *))vt->f2)((char *)arg0 + vt->o2, arg1);
    arg1->unk0x18 = arg2;
    vt = (VT3470 *)arg0->unk0x2C;
    ((s32 (*)(void *, void *))vt->f1)((char *)arg0 + vt->o1, arg1);
    arg0->unk0x28 = 0;
}

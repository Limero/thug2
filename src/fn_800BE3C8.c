// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BE3C8-0x800BE410 (72B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_801279A0(CStruct *, s32, CStruct *);
bool fn_800BE3C8(Unk_3D11A213 *arg0, s32 arg1, CScript *arg2) {
    __ps_t sp8[2];
    __ps_t *p;

    p = sp8;
    p[0] = arg0->unk0x118;
    p[1] = arg0->unk0x120;
    fn_801279A0(arg2->unk0x18, QB_CENTEROFMASSPOS, p);
    return true;
}

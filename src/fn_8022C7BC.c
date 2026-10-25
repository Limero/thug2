// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022C7BC-0x8022C7E4 (40B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void fn_8022C7BC(void *arg0) {
    register void *o __asm__("r9");
    s32 var_r0;

    o = arg0;
    var_r0 = ((Unk_D269F0B0 *)o)->unk0x8;
    ((Unk_D269F0B0 *)o)->unk0x10 = 0;
    var_r0 &= QB_UNKNOWN_0x7FFFFFFF;
    ((Unk_D269F0B0 *)o)->unk0x18 = 0;
    var_r0 |= QB_UNKNOWN_0x40000000;
    ((Unk_D269F0B0 *)o)->unk0x1C = 0;
    ((Unk_D269F0B0 *)o)->unk0x8 = var_r0;
}

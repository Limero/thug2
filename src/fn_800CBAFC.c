// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CBAFC-0x800CBB74 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
void fn_800CBAFC(Unk_C7387A53 *arg0, void *arg1, s32 arg2) {
    Unk_C8FEE62D *node;
    Unk_C6B642AC *vt;
    register s32 walker __asm__("r9");
    s32 v;
    walker = *(s32 *)&arg0->unk0x38;
    for (; (v = *(s32 *)((char *)walker + 4), v == -1 && (walker = 0),
             node = (Unk_C8FEE62D *)walker, node != NULL); ) {
        if (node->unk0x30 == arg2) {
            vt = *((void * *)&node->unk0x14);
            ((void (*)(void *, void *))vt->unk0x3C)((char *)node + vt->unk0x38, arg1);
        }
        walker = *(s32 *)((char *)node + 0xC);
    }
}
// FLAG: -fno-schedule-insns

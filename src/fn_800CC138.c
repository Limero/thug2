// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC138-0x800CC1D8 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-cse-follow-jumps
#include "types.h"
#include "structs.h"
s32 fn_80031EC8(s32, s32, s32, s32, s32);
s32 fn_800CC138(Unk_C7387A53 *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4) {
    CStruct *node;
    register CStruct *next __asm__("r9");
    s32 v;
    s32 found;
    s32 temp_r3;

    found = 0;
    next = (CStruct *)arg0->unk0x38;
    v = next->unk0x4;
    for (;;) {
        if (v == -1) {
            next = NULL;
        }
        node = next;
        if (node == NULL) {
            break;
        }
        temp_r3 = fn_80031EC8((s32)node, arg1, (s32)arg2, arg3, arg4);
        found = (found != 0) | (temp_r3 != 0);
        next = (CStruct *)node->unk0xC;
        v = next->unk0x4;
    }
    return found;
}

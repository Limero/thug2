// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EC544-0x800EC57C (56B). Byte-identical.
#include "types.h"
#include "structs.h"
// FIXED: char* stride for 0x50 struct walk (was void** x4) - EXACT, M5.44
void fn_800EC544(Unk_C7387A53 *arg0) {
    u32 i;
    void *p;

    for (i = 1; i < (u32) *((u32 *)&arg0->unk0x20); i++) {
        p = (char *)arg0 + 0x74 + (i - 1) * 0x50;
        *(s32 *)((char *)*(s32 *)p + (s32)0x14) = 0;
    }
}


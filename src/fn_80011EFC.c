// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80011EFC-0x80011F20 (36B). Byte-identical.
// AdvanceQueueHead: linked-list queue advancement. Reads head from
// field_0x84, stride from field_0x38, advances head by stride*4 bytes,
// replaces head with next node. Dead store to field_0x3C is compiler
// artifact. Store order at tail (0x84 before 0x3C) is critical.
#include "types.h"
#include "structs.h"
void fn_80011EFC(Unk_C7387A53 *arg0) {
    s32 head;
    s32 skip;
    s32 next;
    head = arg0->unk0x84;
    skip = arg0->unk0x38;
    arg0->unk0x3C = head;
    skip <<= 2;
    next = *(s32 *)head;
    head += skip;
    arg0->unk0x84 = next;
    arg0->unk0x3C = head;
}

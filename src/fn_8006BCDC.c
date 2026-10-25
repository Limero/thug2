// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006BCDC-0x8006BD1C (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Queue dequeue/pop sibling of fn_8006BC90 (which enqueues: copies IN at
// offset [arg0+0x0]+8 and ADVANCES [arg0+0x0] by [arg0+0x4]). This pops the
// last [arg0+0x4]-byte chunk: copies it OUT to arg1 from buffer base arg0+
// (count - size)+8 and RETIRES count by size. arg0 is a bounded byte queue:
// +0x0 = running count, +0x4 = fixed chunk size, +0x8 = payload buffer.
// Keys that mattered (recipe-9 regression): must COMPUTE the
// count-size diff FIRST, store the diff back to [arg0+0x0], and pass len=
// original size — the sibling's post-call store ordering pattern is reversed
// here (store before bl, not after). Suggested rename: QueuePopChunk.
#include "types.h"
#include "structs.h"
void memcpy(s32, s32, s32);
void fn_8006BCDC(CStruct *arg0, s32 arg1) {
    s32 temp_r9;
    s32 temp_r5;

    temp_r9 = arg0->unk0x0;
    temp_r5 = arg0->unk0x4;
    arg0->unk0x0 = temp_r9 - temp_r5;
    memcpy(arg1, (char *)arg0 + ((temp_r9 - temp_r5) + 8), temp_r5);
}
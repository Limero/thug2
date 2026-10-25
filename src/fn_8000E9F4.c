// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000E9F4-0x8000EA90 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// MATCHED 2026-09-14: same destroy-loop family as fn_8000E9F4 (this clone
// keeps the bucket cursor). Fixes vs the old wip draft: fn_80012224's callee
// returns a live next-pointer (m2c dropped the return value), so the inner
// walk is `next = (Rec3 *)node->unk0x8` AFTER the call; cur is a typed
// 3-s32 pointer so the bucket stride is `cur = cur + 1` (+0xC).
#include "types.h"
#include "structs.h"
void fn_80012224(s32, void *);
typedef struct { s32 unk0x0; s32 unk0x4; s32 unk0x8; } Rec3;
void fn_8000E934(Rec3 *);
void fn_8000E9F4(Rec3 *arg0) {
    Rec3 *temp_r3;
    Rec3 *node;
    Rec3 *next;
    Rec3 *cur;
    u32 i;
    u32 n;

    temp_r3 = (Rec3 *)arg0->unk0x4;
    if (temp_r3 != 0) {
        n = 1 << arg0->unk0x0;
        cur = temp_r3;
        for (i = 0; i < n; i++) {
            node = (Rec3 *)cur->unk0x8;
            while (node != 0) {
                next = (Rec3 *)node->unk0x8;
                fn_80012224(0, node);
                node = next;
            }
            fn_8000E934(cur);
            cur = cur + 1;
        }
        arg0->unk0x8 = 0;
    }
}

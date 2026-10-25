// Identification: walks a QB text-token stream (fn_8012B2A0 = token walker,
// 0x24 '$' = terminator) accumulating via fn_8000A730(token, token_len, acc)
// for every token whose first byte is not 1 or 2. Returns the accumulated
// value (-1 if no tokens). Sibling fn_8012D0D8 walks the same stream.
// Suggested rename: ScanTextTokens.
// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012D11C-0x8012D190 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void *fn_8012B2A0(void *);
s32 fn_8000A730(void *, s32, s32);
s32 fn_8012D11C(u8 *arg0) {
    s32 acc;
    u8 *cursor;
    u8 *cur;
    u8 c;

    cursor = arg0;
    acc = -1;
    while ((s32)*cursor != 0x24) {
        cur = cursor;
        cursor = (u8 *)fn_8012B2A0(cur);
        c = *cur;
        if ((u32)(c - 1) > 1U) {
            acc = fn_8000A730(cur, cursor - cur, acc);
        }
    }
    return acc;
}

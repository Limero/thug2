// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125548-0x80125568 (32B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80303248;
typedef struct MemBucket {
    char _pad0[4];
    s32 unk4;
    char _pad8[8];
    s32 unk10;
} MemBucket;
void fn_80125548(MemBucket *arg0) {
    s32 off = (arg0->unk4 & 0xFFF) << 2;
    arg0->unk10 = *(s32 *)((char *)(off + (s32)lbl_80303248));
    *(s32 *)((char *)(off + (s32)lbl_80303248)) = (s32)arg0;
}

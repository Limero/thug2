// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80123690-0x80123864 (468B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad00[0x2E0];
    u32 unk2E0;
    char pad2E4[0xC];
    u32 unk2F0;
    char pad2F4[0x8];
    u32 unk2FC[4];
} CB_t;

typedef void (*blk_fn)(void *dst, u32 kind, s32 src, u32 off, u32 n);

extern CB_t lbl_8039BA58;
extern char lbl_8029DEB4[];
extern char lbl_8029E314[];
extern void fn_801233A8(void);
extern char *lbl_8039BE58;
extern u32 lbl_8039BE5C;
extern u32 lbl_8039BE60;
extern u32 lbl_8039BE64;
extern u8 lbl_8039BE68;
extern blk_fn lbl_8039BE84;
extern s32 OSDisableInterrupts(void);
extern s32 OSRestoreInterrupts(s32);

bool fn_80123690(u32 arg0, s32 arg1, u32 arg2) {
    s32 state;
    u32 head, tail, stride;
    u32 h;

    if (arg0 > 2) {
        OSPanic((s32)lbl_8029DEB4, 0x701, (s32)lbl_8029E314);
    }
    state = OSDisableInterrupts();
    if (lbl_8039BA58.unk2FC[lbl_8039BA58.unk2F0 * 4] < lbl_8039BA58.unk2E0) {
        fn_801233A8();
    }
    stride = lbl_8039BE68 * 2;
    head = lbl_8039BE60;
    tail = lbl_8039BE64;
    if (head >= tail) {
        u32 cap = lbl_8039BE5C;
        u32 n;
        if ((u32)(cap - (head - tail)) < arg2) {
            OSRestoreInterrupts(state);
            return false;
        }
        n = cap - head;
        if (n >= arg2) {
            lbl_8039BE84(lbl_8039BE58 + head * stride, arg0, arg1, 0, arg2);
        } else {
            lbl_8039BE84(lbl_8039BE58 + head * stride, arg0, arg1, 0, n);
            lbl_8039BE84(lbl_8039BE58, arg0, arg1, n, arg2 - n);
        }
    } else {
        if ((u32)(tail - head) >= arg2) {
            lbl_8039BE84(lbl_8039BE58 + head * stride, arg0, arg1, 0, arg2);
        } else {
            OSRestoreInterrupts(state);
            return false;
        }
    }
    h = lbl_8039BE60 + arg2;
    lbl_8039BE60 = h;
    if (h >= lbl_8039BE5C) {
// SOLVED 2026-10-08: the 3-word residual was NOT a register pick -- it
// was the operand ORDER of the wrap-around subtraction, i.e. a real semantic
// bug in the draft. Want's bytes are `subf r0, r5, r0` (r0 = r0 - r5) with
// r5 = lbl_8039BE5C and r0 = h, i.e. `h - cap`; the draft had `cap - h`, which
// compiles to the mirrored `subf r0, r0, r11` and ALSO lands the loaded cap in
// r11 instead of r5. One-line fix:
//     lbl_8039BE60 = h - lbl_8039BE5C;      /* was: lbl_8039BE5C - h */
// -> 100.00% masked, 0 diffs, size EXACT 468B (regdiff_scan had flagged the 3
// words as a pure rename, which hid the swapped-operand reality).
        lbl_8039BE60 = h - lbl_8039BE5C;
    }
    OSRestoreInterrupts(state);
    return true;
}

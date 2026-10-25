// Promoted from src/wip 2026-10-17 (mwcc region). WIP DRAFT — hand-written from disasm 2026-10-09, full rewrite 2026-10-17. family=hand range=0x8025EE04-0x8025EFD4 size=464B
// range 0x8025EE04-0x8025EFD4 size=0x1D0 (464B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
// BAT-slot scanner: returns the CAB58 cursor unless CA370[2] is set (returns
// the cursor as-is, still running the epilogue bump). Otherwise scans table
// slots latching up to three candidates on the F5F4/F61C field pattern and
// returns the first non-negative one, else 0. Both the mid-loop and epilogue
// bumps use the EA50 wraparound protocol; only the epilogue clears CA370[2].
#include "types.h"

extern s32 lbl_803CA370;
extern u32 lbl_803CAB58;
extern s32 fn_8025EA50(void);
extern s32 fn_8025F710(s32 arg0);
extern s32 fn_8025F5CC(s32 arg0);
extern s32 fn_8025F5F4(s32 arg0);
extern s32 fn_8025F61C(s32 arg0);
extern s32 fn_8025F730(s32 arg0);
extern void fn_8025F644(s32 arg0, s32 arg1);

u32 fn_8025EE04(void) {
    u32 cur;
    u32 result;
    s32 a;
    s32 b;
    s32 c;
    s32 entry;
    s32 f0;
    s32 f1;

    cur = lbl_803CAB58;
    result = 0;
    a = -1;
    b = -1;
    c = -1;
    if (lbl_803CA370 == 0) {
        for (;;) {
            entry = fn_8025F710((s32)lbl_803CAB58);
            if (entry == 0) {
                goto bail;
            }
            if (fn_8025F5CC(entry) == 0) {
                goto bail;
            }
            f0 = fn_8025F5F4(entry);
            f1 = fn_8025F61C(entry);
            if (f0 == 0 && f1 == 0) {
                if (fn_8025F730((s32)lbl_803CAB58) == 0) {
                    result = lbl_803CAB58;
                    goto epi;
                }
                goto latch;
            }
        latch:
            if (f0 == 0 && f1 != 0) {
                if (a < 0 && fn_8025F730((s32)lbl_803CAB58) == 0) {
                    a = (s32)lbl_803CAB58;
                }
                goto done;
            }
            if (f0 != 0 && f1 == 0) {
                if (b < 0 && fn_8025F730((s32)lbl_803CAB58) == 0) {
                    b = (s32)lbl_803CAB58;
                }
                goto done;
            }
            if (c < 0 && fn_8025F730((s32)lbl_803CAB58) == 0) {
                c = (s32)lbl_803CAB58;
            }
        done:
            if (f0 != 0) {
                fn_8025F644(entry, 0);
            }
            if (cur == lbl_803CAB58) {
                if (a >= 0) {
                    result = (u32)a;
                    goto epi;
                }
                if (b >= 0) {
                    result = (u32)b;
                    goto epi;
                }
                if (c < 0) {
                    goto epi;
                }
                result = (u32)c;
                goto epi;
            }
            lbl_803CAB58 = lbl_803CAB58 + 1;
            if (lbl_803CAB58 >= (u32)fn_8025EA50()) {
                lbl_803CAB58 = 0;
            }
        }
    bail:
        result = lbl_803CAB58;
    } else {
        result = cur;
    }
epi:
    lbl_803CAB58 = lbl_803CAB58 + 1;
    if (lbl_803CAB58 >= (u32)fn_8025EA50()) {
        lbl_803CA370 = 0;
        lbl_803CAB58 = 0;
    }
    return result;
}

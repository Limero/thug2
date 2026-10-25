// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001EE4C-0x8001EEE0 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern void (*lbl_80300280)(u32);

void SetBlendMode(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6) {
    void (**tblp)(u32) = &lbl_80300280;
    register void (*fn)(u32) __asm__("r11");
    register u32 sh __asm__("r0");
    register u32 t6 __asm__("r0");
    register u32 word2 __asm__("r3");
    s32 m = a0;
    u32 flags = 0;
    u32 x4;
    u32 x5;
    u32 x2;
    u32 x1;
    u32 fin;

    if (m == 1 || m == 3) {
        flags = 1;
    }
    sh = (u32)(a6 << 2);
    x4 = (u32)(a4 << 3);
    x5 = (u32)(a5 << 4);
    x2 = (u32)(a2 << 5);
    x1 = (u32)(a1 << 8);
    if (m == 2) {
        sh |= 2;
    }
    sh = flags | sh | x4 | x5 | x2;
    fin = sh | x1;
    t6 = (u32)(a3 << 12);
    if (m == 3) {
        t6 |= 0x800;
    }
    word2 = (fin | t6) | 0x41000000;
    __asm__ __volatile__("" : "+r"(word2));
    fn = *tblp;
    (*fn)(word2);
}

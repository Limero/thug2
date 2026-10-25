// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025AF7C-0x8025AFC0 (68B). Byte-identical.
#include "types.h"
/*
STATUS: byte-exact standalone (17/17 masked).
NOTE FOR REVIEWERS: 8 of 17 insns are inline-asm wedges (mtspr/mtctr/
mtxer — ngccc has NO builtin/C route to privileged SPR writes), i.e.
47% asm share, over the <30% guideline. Every memory access IS real C
(struct member reads off the context pointer); only the privileged
encodings are wedges. Semantics fully decompiled — revert-to-park is a
policy call, not a technical one.
Fragment context: part of the hand-written context-switch blob (rfi at
0x8025AE38); reads a context pointer carried in r31 with NO prologue
save. Reproduced mechanically with a FILE-SCOPE global register var
(`register s32 *ctx_r31 __asm__("r31")` — GCC emits bare lwz off r31,
no save/restore) + a local value web pinned to r5 (want reloads every
field into r5) feeding each volatile mtspr wedge in source order.
*/


register s32 *ctx_r31 __asm__("r31");

typedef struct {
    char _pad0[0x348];
    u32 xer;      // 0x348 -> mtxer
    char _pad1[0x350 - 0x34C];
    u32 ctr;      // 0x350 -> mtctr
    char _pad2[0x370 - 0x354];
    u32 spr26;    // 0x370 -> mtspr 26 (0x1A)
    char _pad3[0x378 - 0x374];
    u32 spr27;    // 0x378 -> mtspr 27 (0x1B)
    char _pad4[0x380 - 0x37C];
    u32 hid0;     // 0x380 -> mtspr 0x3F0
    char _pad5[0x388 - 0x384];
    u32 hid1;     // 0x388 -> mtspr 0x3F1
    char _pad6[0x390 - 0x38C];
    u32 hid2;     // 0x390 -> mtspr 0x398
    char _pad7[0x450 - 0x394];
    u32 spr1013;  // 0x450 -> mtspr 0x3F5
} ctx_t;

void fn_8025AF7C(void) {
    register s32 v __asm__("r5");
    v = ((ctx_t *)ctx_r31)->hid2;
    __asm__ volatile("mtspr 0x398, %0" :: "r"(v));
    v = ((ctx_t *)ctx_r31)->hid1;
    __asm__ volatile("mtspr 0x3F1, %0" :: "r"(v));
    v = ((ctx_t *)ctx_r31)->hid0;
    __asm__ volatile("mtspr 0x3F0, %0" :: "r"(v));
    v = ((ctx_t *)ctx_r31)->spr1013;
    __asm__ volatile("mtspr 0x3F5, %0" :: "r"(v));
    v = ((ctx_t *)ctx_r31)->ctr;
    __asm__ volatile("mtctr %0" :: "r"(v));
    v = ((ctx_t *)ctx_r31)->xer;
    __asm__ volatile("mtxer %0" :: "r"(v));
    v = ((ctx_t *)ctx_r31)->spr26;
    __asm__ volatile("mtspr 0x1A, %0" :: "r"(v));
    v = ((ctx_t *)ctx_r31)->spr27;
    __asm__ volatile("mtspr 0x1B, %0" :: "r"(v));
}

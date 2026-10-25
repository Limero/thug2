// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80057FBC-0x80057FFC (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Vtbl_57FBC {
    char pad0x00[0x48];
    s16 adjust;        /* +0x48 s16 this-offset  */
    char pad0x4A[2];
    void (*fn)(void *);/* +0x4C member fn ptr    */
} Vtbl_57FBC;

void fn_80057FBC(void *arg0) {
    register s32 s __asm__("r3");
    Vtbl_57FBC *t;

    if (*(s32 *)((char *)arg0 + 0x10) != 0) {
        s = *(s32 *)((char *)arg0 + 0x14);
    } else {
        s = *(s32 *)((char *)arg0 + 0x14);
    }
    t = *(Vtbl_57FBC **)((char *)s + 0xC);
    t->fn((char *)s + t->adjust);
}

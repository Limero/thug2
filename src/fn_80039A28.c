// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80039A28-0x80039A5C (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    s32 unk0x00; s32 unk0x04;
    char _08[0x500];
    f32 unk0x508;
    char _50C[0x7C];
    s32 unk0x588;
    s32 unk0x58C;
    char _590[4];
    s32 unk0x594;
    s32 unk0x598;
} T39A28;
extern char lbl_80291F40[];
extern f32 lbl_80291F0C;
void *fn_80039A28(void *arg0) {
    T39A28 *p = (T39A28 *)arg0;
    p->unk0x598 = (s32)lbl_80291F40;
    p->unk0x04 = 0;
    p->unk0x594 = 0;
    p->unk0x588 = 0;
    p->unk0x58C = 0;
    p->unk0x508 = lbl_80291F0C;
    return arg0;
}

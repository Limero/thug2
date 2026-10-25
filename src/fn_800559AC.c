// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800559AC-0x800559F4 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80364C1C[];
extern char lbl_802931C0[];
typedef struct Unk_559AC { char pad0x0[0x4]; s32 unk0x4; s32 unk0x8; s32 unk0xC; s32 unk0x10; s32 unk0x14; } Unk_559AC;
void fn_800559AC(s32 arg0, s32 arg1) {
    Unk_559AC *p;
    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        p = (Unk_559AC *)lbl_80364C1C;
        p->unk0x14 = (s32)lbl_802931C0;
        p->unk0x4 = -1;
        p->unk0x8 = 0;
        p->unk0x10 = (s32)p;
        p->unk0xC = (s32)p;
    }
}

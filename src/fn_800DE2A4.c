// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DE2A4-0x800DE310 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
typedef struct { char pad[8]; s16 unk0x8; char pad2[2]; s32 unk0xC; } Disp7B;
extern char lbl_8029A1C0[];
void fn_8009F558(void *, s32);
void fn_800DE2A4(Unk_C7387A53 *arg0, s32 arg1) {
    void *o = (void *)*(s32 *)((char *)arg0 + 0x1C);
    *(s32 *)((char *)arg0 + 0x18) = (s32)lbl_8029A1C0;
    if (o != NULL) {
        Disp7B *d = *(Disp7B **)((char *)o + 0x8);
        ((void (*)(void *, s32))d->unk0xC)((char *)o + d->unk0x8, 3);
    }
    fn_8009F558(arg0, arg1);
}

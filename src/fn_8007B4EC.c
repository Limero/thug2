// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007B4EC-0x8007B558 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct { char pad[8]; s16 unk0x8; char pad2[2]; s32 unk0xC; } Disp7B;
extern char lbl_80295B58[];
void fn_8005E5F4(void *, s32);
void fn_8007B4EC(Unk_C7387A53 *arg0, s32 arg1) {
    void *o = (void *)arg0->unk0x50;
    arg0->unk0x4C = (s32)lbl_80295B58;
    if (o != NULL) {
        Disp7B *d = *(Disp7B **)((char *)o + 0x10);
        ((void (*)(void *, s32))d->unk0xC)((char *)o + d->unk0x8, 3);
    }
    fn_8005E5F4(arg0, arg1);
}

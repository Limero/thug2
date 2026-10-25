// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000FE2C-0x8000FEAC (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8000F2F8(void *, void *);
void *Mem_NewZero(s32);
s32 fn_8001094C(void *, s32);
extern char lbl_802FFE98[];
extern char lbl_802905B0[];
#include "structs.h"
void *fn_8000F95C(void *, void *, s32, void *);
void fn_8000F320(Unk_F12C5E01 *self);
void fn_8000FE2C(Unk_C7387A53 *arg0) {
    s32 temp_r3_2;
    Unk_9994C3F5 *temp_r3;

    if ((s32) arg0->unk0x138 == 0) {
        temp_r3 = *(void **)lbl_802FFE98;
        fn_8000F2F8(temp_r3, temp_r3->unk0x11C);
        temp_r3_2 = fn_8001094C(Mem_NewZero(0x1C), 0x27100);
        arg0->unk0x138 = temp_r3_2;
        arg0->unk0x13C = fn_8000F95C(arg0, temp_r3_2, 1, lbl_802905B0);
        fn_8000F320(*(void **)lbl_802FFE98);
    }
}

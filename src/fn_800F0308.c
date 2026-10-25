// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F0308-0x800F0374 (108B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern CStruct * lbl_80301B3C;
void *Mem_NewZero(s32);
s32 fn_800EFFE8(CStruct *);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_800F0074(CStruct *, s32);
void fn_8000F320(Unk_F12C5E01 *);
void fn_800F0308(s32 arg0) {
    Unk_C7387A53 *temp_r3;

    temp_r3 = *(void * *)&lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x12C);
    if (lbl_80301B3C == 0) {
        lbl_80301B3C = fn_800EFFE8(Mem_NewZero(8));
    }
    fn_800F0074(lbl_80301B3C, arg0);
    fn_8000F320(*(void * *)&lbl_802FFE98);
}

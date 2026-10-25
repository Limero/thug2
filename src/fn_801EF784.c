// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801EF784-0x801EF828 (164B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern void* lbl_80305F9C;
s32 fn_801754AC(s32);
s32 fn_8022046C(Unk_74087627 *);
void fn_80220400(Unk_74087627 *);
void fn_801EF784(Unk_C8FEE62D *arg0) {
    s32 var_r9;
    Unk_DB0E2BAB *temp_r9;

    if (fn_801754AC(lbl_80305EAC) == 0) {
        temp_r9 = *((void * *)&arg0->unk0x18);
        ((void (*)(void *, s32))*((void * *)&temp_r9->unk0x44))((char *)arg0 + temp_r9->unk0x40, 1);
        return;
    }
    if (*(s32 *)(arg0->unk0xC + 0xC8) != 0) {
        var_r9 = 1;
        if ((arg0->unk0x1C & 2) == 0) {
            var_r9 = 0;
        }
        if ((var_r9 != 0) && (fn_8022046C(lbl_80305F9C) == 0)) {
            fn_80220400(lbl_80305F9C);
        }
    }
}

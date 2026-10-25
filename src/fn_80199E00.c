// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80199E00-0x80199E54 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
extern void *NextItem(s32 arg0);
extern s32 fn_801403CC(void * arg0);
extern s32 fn_801813F0(CStruct * arg0);
bool fn_80199E00(void) {
    CScript *temp_r3;

    temp_r3 = NextItem(lbl_80305F9C);
    if (temp_r3 != NULL && temp_r3->unk0x18 != 0 && fn_801813F0(fn_801403CC(temp_r3->unk0x18)) <= 0) {
        return true;
    }
    return false;
}

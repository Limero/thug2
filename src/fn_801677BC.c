// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801677BC-0x80167810 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802A866C[];
extern s32 fn_80165660(Unk_F96D0DC8 *, s32, s32);
extern s32 fn_8000B554(s32);
extern s32 sprintf();
void fn_801677BC(s32 arg0, s32 arg1, void *arg2) {
    u8 sp8[24];

    sprintf(arg2, (s32)lbl_802A866C, fn_8000B554(fn_80165660(sp8, arg1, arg0)), sp8);
}

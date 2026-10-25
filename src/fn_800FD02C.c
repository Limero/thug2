// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FD02C-0x800FD074 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029C548[];
extern void fn_801061DC(void *);
extern void fn_800FB114(CStruct *, void *);

void fn_800FD02C(Unk_C7387A53 *arg0, void *arg1) {
    arg0->unk0xC = (s32)lbl_8029C548;
    fn_801061DC(arg0);
    fn_800FB114(arg0, arg1);
}
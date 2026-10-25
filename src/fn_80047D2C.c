// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80047D2C-0x80047D7C (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800460CC(Unk_D9452E8E *);
extern char lbl_80292858[];
s32 fn_80128A90(CStruct *, void *);
void fn_80047D2C(Unk_D9452E8E *arg0, CStruct *arg1) {
    CScreenElement_SetMorph();
    if (fn_80128A90(arg1, (s32)lbl_80292858) != 0) {
        fn_800460CC(arg0);
    }
}

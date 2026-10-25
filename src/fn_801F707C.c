// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F707C-0x801F70E4 (104B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_802AE380[];
extern s32 fn_80127138(CStruct *, void *);
extern s32 fn_80127848(CStruct *, void *, s32);
extern s32 fn_801F2184(s32);

bool fn_801F707C(Unk_F0C166E4 *arg0, s32 arg1, CScript *arg2) {
    fn_80127138(arg2->unk0x18, (s32)lbl_802AE380);
    {
        s32 fld = arg0->unk0xAC00;
        if (fld != 0) {
            s32 temp = arg2->unk0x18;
            fn_80127848(temp, (s32)lbl_802AE380, fn_801F2184(fld));
        }
    }
    return true;
}

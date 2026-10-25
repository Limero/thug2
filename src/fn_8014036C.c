// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014036C-0x801403CC (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_80140164(Unk_FFAD6788 *);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 Script_GetInteger(s32, s32);
s32 fn_8014036C(s32 arg0, s32 arg1, Unk_FFAD6788 *arg2) {
    s32 sp8;

    if (GetInteger(fn_80140164(arg2), arg0, &sp8, 0) != 0) {
        return sp8;
    }
    return Script_GetInteger(arg0, arg1);
}

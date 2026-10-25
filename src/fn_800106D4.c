// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800106D4-0x80010758 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_8000F10C(Unk_4897C6F8 *, s32, s32, Unk_E15B2970 *);
void fn_8000F2D0(void *, void *);
s32 memmove(void *, void *, s32);
extern char lbl_802FFE98[];
s32 fn_800106D4(s32 arg0, s32 arg1) {
    s32 var;

    var = 0;
    if (arg1 != 0) {
        var = (s32)fn_8000F10C(*(void **)lbl_802FFE98, arg1, 1, 0);
    }
    if (arg0 != 0) {
        if (var != 0) {
            memmove((void *)var, (void *)arg0, arg1);
        }
        fn_8000F2D0(*(s32 *)&lbl_802FFE98, arg0);
    }
    return var;
}

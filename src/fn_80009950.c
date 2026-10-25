// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80009950-0x800099AC (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: zero-filled allocation helper on the engine allocator
// (lbl_802FFE98): callers do fn_80009950(sz) + 8 or fn_80009950(sz + 8) and
// treat the 8-byte prefix as a header (fn_801B0544 / fn_801B0EF8 array
// builders). Suggested rename: AllocZeroed.
#include "types.h"
#include "structs.h"
s32 fn_8000F10C(Unk_4897C6F8 *, void *, void *, Unk_E15B2970 *);
extern char lbl_802FFE98[];
s32 fn_80009950(s32 arg0) {
    s32 temp_r3;

    temp_r3 = fn_8000F10C(*(s32 *)&lbl_802FFE98, arg0, 1, 0);
    if (temp_r3 != 0) {
        memset(temp_r3, 0, arg0);
    }
    return temp_r3;
}

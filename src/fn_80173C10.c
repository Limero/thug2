// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80173C10-0x80173C5C (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_8019B834(Unk_9994C3F5 *);
void *fn_8017471C(Unk_C7387A53 *, s32);
void *GetChecksum_3(Unk_6A70655D *, s32);

s32 fn_80173C10(Unk_C7387A53 *arg0) {
    return *(s32 *)((char *)GetChecksum_3(
        (Unk_6A70655D *)fn_8017471C(arg0, fn_8019B834(*(Unk_9994C3F5 **)((char *)arg0 + 0x374))),
        0x270F56E1) + 0x13F8);
}

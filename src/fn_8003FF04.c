// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003FF04-0x8003FF64 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80041338(void *, Unk_31DE137E *, s32, s32 *);
void CObject_RemoveRefLink(void *, void *);
s32 fn_8003FF04(Unk_31DE137E *arg0, s32 arg1, s32 *arg2) {
    s32 sp8[4];
    s32 *temp_r31;

    fn_80041338(&sp8[0], arg0, arg1, arg2);
    temp_r31 = (s32 *)sp8[0];
    if (temp_r31 != NULL) {
        void *sp8p = &sp8[0];

        __asm__("" : "+r"(temp_r31));
        CObject_RemoveRefLink(temp_r31, sp8p);
        sp8[0] = 0;
    }
    return (s32)temp_r31;
}

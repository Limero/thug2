// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003FF64-0x8003FFC4 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80041338(void *arg0, Unk_31DE137E *arg1, s32 arg2, s32 *arg3);
void CObject_RemoveRefLink(void *arg0, void *arg1);
s32 fn_8003FF64(Unk_31DE137E *arg0, s32 arg1) {
    s32 sp18;
    s32 sp8[4];
    s32 *temp_r31;

    sp18 = arg1;
    fn_80041338(&sp8[0], arg0, 0, &sp18);
    temp_r31 = (s32 *)sp8[0];
    if (temp_r31 != NULL) {
        void *sp8p = &sp8[0];

        __asm__("" : "+r"(temp_r31));
        CObject_RemoveRefLink(temp_r31, sp8p);
        sp8[0] = 0;
    }
    return (s32)temp_r31;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022B2A8-0x8022B2FC (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8021B56C(void *);
s32 fn_80219680(void *);
void fn_801396A4(void *);
void fn_80009C00(s32);
void fn_8022B2A8(Unk_31DE137E *arg0) {
    s32 temp_r3;

    if (fn_80219680(arg0) == 0) {
        temp_r3 = fn_8021B56C(arg0);
        if (temp_r3 != 0) {
            fn_801396A4((void *)(temp_r3 + 4));
        }
        fn_80009C00(arg0->unk0xFC);
    }
}
// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801255B8-0x80125600 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct S1255B8 {
    char pad0[4];
    s32 unk4;
    s32 unk8;
} S1255B8;
s32 fn_8012543C(s32);
void fn_8012DE30(s32);
void fn_80125548(S1255B8 *);
void fn_801255B8(S1255B8 *arg0, s32 arg1) {
    s32 temp_r3;

    arg0->unk8 = arg1;
    temp_r3 = fn_8012543C(arg0->unk4);
    if (temp_r3 != 0) {
        fn_8012DE30(temp_r3);
    }
    fn_80125548(arg0);
}

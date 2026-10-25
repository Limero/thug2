// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F0EF0-0x800F0F84 (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_800F0FE4(void);
void fn_800F0FB8(s32);
void fn_800F0B38(s32, s32, s32 (*)(s32, u8 *), CStruct *, s32);
void fn_8012D61C(void);
void fn_800F100C(void);
void fn_8012D60C(void);
void fn_800F0EF0(CStruct *arg0, s32 arg1, s32 (*arg2)(s32, u8 *)) {
    s32 sp8;
    CStruct *node;
    fn_8012D61C();
    fn_800F0FB8(0);
    if ((node = fn_800F0FE4()) != 0) {
        do {
            sp8 = 0;
            if (GetChecksum_2(node, arg0, &sp8, 0) != 0) {
                fn_800F0B38(sp8, arg1, arg2, 0, 0);
            }
        } while ((node = fn_800F0FE4()) != 0);
    }
    fn_800F100C();
    fn_8012D60C();
}

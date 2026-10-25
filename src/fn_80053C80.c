// Promoted from src/wip — byte-identical match
// family=proto range=0x80053C80-0x80053CE4 size=100B
#include "types.h"
#include "structs.h"
extern void fn_80053C04(Unk_DB0E2BAB *, s32);
extern s32 lbl_80364A38[];
extern s32 lbl_80364BF8[];
void fn_80053C80(s32 arg0, s32 arg1) {
    s32 var_ctr;
    s32 *var_r9;

    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        var_ctr = 0x10;
        var_r9 = lbl_80364A38;
        do {
            ((CScript *)var_r9)->unk0x18 = 0;
            var_r9 += 7;
            var_ctr -= 1;
        } while (var_ctr != 0);
        fn_80053C04(lbl_80364BF8, 4);
    }
}
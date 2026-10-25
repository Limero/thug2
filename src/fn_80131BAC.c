// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131BAC-0x80131C48 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_8012ED7C(void *);
s32 fn_80130E34(void *, void *);
s32 fn_80130D24(void *, s32);
void fn_8012F360(void *);
void fn_8012F4DC(void *);
void fn_80131BAC(Unk_15EF4A35 *arg0, s32 arg1) {
    s32 var_r31;

    var_r31 = fn_8012ED7C(0);
    if (var_r31 != 0) {
        do {
            if (fn_80130E34(var_r31, arg0) != 0) {
                if (arg1 == 0) {
                    goto do_it;
                }
                if (fn_80130D24(var_r31, arg1) == 0) {
                    goto next;
                }
do_it:
                fn_8012F360(var_r31);
                fn_8012F4DC(var_r31);
next: ;
            }
            var_r31 = fn_8012ED7C(var_r31);
        } while (var_r31 != 0);
    }
}

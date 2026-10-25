// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023357C-0x802336D8 (348B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8023C598(s32);
void fn_8023357C(void *arg0, void *arg1) {
    u32 swv1;
    register void *o __asm__("r31");
    register void *k __asm__("r30");
    s32 bits;
    s32 cur;
    s32 h;
    register s32 key __asm__("r4");
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r9;

    __asm__("" : "=r"(o) : "0"(arg0));
    __asm__("" : "=r"(k) : "0"(arg1));
    if ((((Unk_C7387A53 *)o)->unk0x44 == QB_EDIT) && (fn_8023C598(0) != 0)) {
        var_r9 = 1;
        if (!(((Unk_C7387A53 *)o)->unk0x4C & 2)) {
            var_r9 = 0;
        }
        if (var_r9 == 0) {
            h = ((CStruct *)k)->unk0x8;
            key = ((CStruct *)k)->unk0x0;
            if (h == QB_ROOT_WINDOW) {
                bits = ((Unk_C7387A53 *)o)->unk0x48;
                cur = bits;
                __asm__("" : "+r"(cur));
                var_r0 = 1;
                if (!(bits & 0x800)) {
                    var_r0 = 0;
                }
                if (var_r0 == 0) {
                    var_r0_2 = 1;
                    if (!(cur & 0x1000)) {
                        var_r0_2 = 0;
                    }
                    if (var_r0_2 == 0) {
                        var_r0_3 = 1;
                        if (!(cur & 1)) {
                            var_r0_3 = 0;
                        }
                        if (var_r0_3 == 0) {
                            var_r0_4 = 1;
                            if (!(cur & 0x8000)) {
                                var_r0_4 = 0;
                            }
                            if (var_r0_4 == 0) {
                                s32 res;
                                switch (swv1 = key) {
                                case QB_PAD_UP:
                                    res = cur | 0x200;
                                    break;
                                case QB_PAD_DOWN:
                                    res = cur | 0x400;
                                    break;
                                case QB_PAD_LEFT:
                                    res = cur | 8;
                                    break;
                                default:
                                    return;
                                case QB_PAD_RIGHT:
                                    res = bits | 0x10;
                                    break;
                                }
                                ((Unk_C7387A53 *)o)->unk0x48 = res;
                                                            }
                        }
                    }
                }
            }
        }
    }
}

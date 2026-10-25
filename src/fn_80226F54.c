// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80226F54-0x80227024 (208B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EC0;
s32 fn_80198B10(s32);
s32 fn_8021D2C4(s32, s32);
register s32 var_r10 __asm__("r10");
s32 fn_80226F54(Unk_C8FEE62D *arg0) {
    void *mgr;
    Unk_C7387A53 *t;
    s32 temp_r7;
    s32 v;
    char *p;
    register s32 target __asm__("r3");
    char *walk;
    register char *copy __asm__("r6");
    register s32 temp_r8 __asm__("r8");
    s32 *tp;

    mgr = *((void * *)&arg0->unk0x18);
    if (fn_80198B10(lbl_80305EC0) == 0) {
        return 1;
    }
    if ((t = fn_8021D2C4((s32)mgr, arg0->unk0x10)) == 0) {
        return 4;
    }
    temp_r7 = t->unk0x34;
    walk = (char *)mgr + 0x7C;
    tp = *(s32 **)arg0;
    __asm__ volatile("" : "+r"(tp));
    copy = walk;
    __asm__ volatile("" : "+r"(copy));
    temp_r8 = temp_r7 * 0x14;
    var_r10 = 0;
    __asm__ volatile("" : "+r"(tp));
    target = *tp;
    if (*(s32 *)((char *)walk + temp_r8) == 0) {
        goto insert;
    }
    walk = (char *)(temp_r8 + (s32)copy);
    p = walk;
    while (1) {
        v = *(s32 *)p;
        p += 4;
        if (v == target) {
            return 4;
        }
        var_r10 += 1;
        if (var_r10 > 4) {
            return 1;
        }
        v = *(s32 *)(walk += 4);
        if (v == 0) {
            break;
        }
    }
insert:
    if (var_r10 <= 4) {
        *(s32 *)((char *)copy + ((temp_r7 * 0x14) + (var_r10 * 4))) = target;
    }
    return 1;
}

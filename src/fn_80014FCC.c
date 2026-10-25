// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014FCC-0x80015058 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802FFF10[];
extern char lbl_803CAF54[];
extern char fn_80014AE8[];
s32 fn_80013254(s32 *);
s32 fn_80014B34(s32);
void fn_8001B7F4(s32, s32, s32, s32);
s32 fn_80014FCC(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    register s32 callback __asm__("r6");
    register s32 value1 __asm__("r4");
    register s32 target __asm__("r3");
    register s32 field_value __asm__("r9");
    register s32 registry_page __asm__("r10");
    s32 count_value;
    s32 temp_r5;
    s32 var_r3;
    s32 after_store;
    s32 dead;

    temp_r5 = fn_80014B34(arg2 * arg3);
    count_value = *(s32 *)&lbl_802FFF10;
    __asm__ __volatile__("lis %0,%1@ha" : "=r"(registry_page) : "s"(lbl_803CAF54), "r"(count_value));
    __asm__ __volatile__("lis %0,%1@ha" : "=r"(callback) : "s"(fn_80014AE8), "r"(count_value));
    value1 = arg1;
    __asm__ __volatile__("" : "+r"(value1));
    count_value = count_value + 1;
    __asm__ __volatile__("addi %0,%0,%1@l" : "+r"(callback) : "s"(fn_80014AE8), "r"(count_value));
    *(s32 *)&lbl_802FFF10 = count_value;
    target = (s32)((char *)arg0 + 0x8C);
    __asm__ __volatile__("" : "+r"(target));
    field_value = arg0->unk0x38 + 1;
    __asm__("stw %1,0x38(%2)" : "=r"(after_store) : "r"(field_value), "r"(arg0));
    __asm__("lwz %0,0x38(%1)" : "=&r"(dead) : "r"(arg0), "r"(after_store));
    __asm__ __volatile__("" :: "r"(dead));
    *(void **)((char *)registry_page - 0x50AC) = arg0;
    __asm__ __volatile__("" : "+r"(callback), "+r"(value1), "+r"(target));
    fn_8001B7F4(target, value1, temp_r5, callback);
    var_r3 = 0;
    if (arg0->unk0x20 != 0) {
        var_r3 = fn_80013254(arg0);
    }
    return var_r3;
}

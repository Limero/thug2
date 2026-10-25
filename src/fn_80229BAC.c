// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80229BAC-0x80229C38 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80229BAC(CScript *arg0) {
    s32 flags;
    s32 var_r3;
    register s32 var_r9 __asm__("r9");
    register s32 t10 __asm__("r10");
    register s32 t20 __asm__("r11");

    flags = arg0->unk0x1D8;
    var_r9 = 1;
    t10 = flags & 0x800;
    if (t10 == 0) {
        __asm__ volatile("li %0,0" : "=r"(var_r9));
    }
    if (var_r9 != 0) {
        return 0;
    }
    var_r9 = 1;
    __asm__ volatile("mr %0,%1" : "=r"(t20) : "r"(flags));
    t10 = flags & 0x1000;
    if (t10 == 0) {
        __asm__ volatile("li %0,0" : "=r"(var_r9));
    }
    if (var_r9 != 0) {
        return 1;
    }
    var_r9 = 1;
    t10 = t20 & 0x2000;
    if (t10 == 0) {
        __asm__ volatile("li %0,0" : "=r"(var_r9));
    }
    if (var_r9 != 0) {
        return 2;
    }
    var_r9 = 1;
    t20 = flags & 0x4000;
    if (t20 == 0) {
        __asm__ volatile("li %0,0" : "=r"(var_r9));
    }
    var_r3 = 3;
    if (var_r9 == 0) {
        var_r3 = -1;
    }
    return var_r3;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80182C08-0x80182C50 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void fn_80182C50(Unk_6A3B48DF *);

void fn_80182C08(Unk_6A3B48DF *arg0) {
    s32 var_ctr;
    s8 *var_r9;
    register s32 var_zb __asm__("r11");

    __asm__("li %0,0" : "=r"(var_zb));
    arg0->unk0x1544 = 0;
    var_r9 = (s8 *)((char *)arg0 + (s32)0xB7F);
    arg0->unk0x154C = 0;
    __asm__ volatile("" ::: "memory");
    var_ctr = 0x9C4;
    do {
        *var_r9 = (s8)var_zb;
        var_r9 -= 1;
        var_ctr -= 1;
    } while (var_ctr != 0);
    fn_80182C50((s32)arg0);
}

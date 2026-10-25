// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023E0F8-0x8023E18C (148B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void *fn_8023897C(void * arg0, s32 arg1, s32 * arg2);
extern void fn_8023DE20(void *arg0);
extern void fn_8023EC64(Unk_C7387A53 * arg0, s32 arg1);

void fn_8023E0F8(CStruct *arg0, s32 arg1) {
    register s32 var_r4 __asm__("r4");
    register void *temp_r3 __asm__("r3");
    register char *p __asm__("r9");
    s32 off;

    temp_r3 = fn_8023897C(arg0->unk0x0, arg0->unk0x6C, (char *)arg0 + 0x70);
    var_r4 = ((Unk_51AF0E3F *)temp_r3)->unk0x14C + arg1;
    if (var_r4 < 0) {
        p = (char *)(((Unk_51AF0E3F *)temp_r3)->unk0x148);
        var_r4 = (s32)p - 1;
    } else if (var_r4 >= (s32)((Unk_51AF0E3F *)temp_r3)->unk0x148) {
        var_r4 = 0;
    }
    ((Unk_51AF0E3F *)temp_r3)->unk0x14C = var_r4;
    if ((s32)((Unk_51AF0E3F *)temp_r3)->unk0x151 != 0) {
        fn_8023DE20(arg0);
        return;
    }
    p = (char *)temp_r3 + 8;
    __asm__("slwi %0,%1,3" : "=&r"(off) : "r"(var_r4));
    fn_8023EC64(arg0, *(s32 *)((char *)p + off));
}

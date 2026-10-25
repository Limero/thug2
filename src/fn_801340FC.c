// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801340FC-0x801341FC (256B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801323D4(CScript *, s32);
void fn_80132458(Unk_B0F19D72 *);
s32 fn_801252F0(s32 *);
void fn_80125354(void *);
void fn_80126808(Unk_80577C09 *, Unk_5D1D68CC *, s32);
void fn_80125320(void *);
void fn_801266EC(Unk_5D1D68CC *);
bool fn_801340FC(void *arg0, Unk_80577C09 *arg1) {
    register char *m1 __asm__("r28");
    register char *m2 __asm__("r27");
    s32 *var_r30;
    s32 temp_r11;

    var_r30 = (s32 *)((char *)arg0 + 0x14C);
    m1 = (char *)0x802A0000;
    m2 = (char *)0x802A0000;
    goto loop_test;
block_process:
    arg0 = (char *)arg0 + 4;
    var_r30 = (s32 *)arg0;
    __asm__("" : "+r"(var_r30));
    if (fn_801252F0(arg0) != 0) {
        fn_80125354(arg0);
        fn_80126808(arg1, arg0, 0);
        fn_80125320(arg0);
    } else {
        fn_80126808(arg1, arg0, 0);
    }
    fn_801266EC(var_r30);
    return true;
block_pop:
    fn_80132458(arg0);
    if (((Unk_2A6B476C *)arg0)->unk0x1F4 != 0) {
        return false;
    }
loop_test:
    temp_r11 = ((Unk_2A6B476C *)arg0)->unk0x1E8;
    if (*(s32 *)((char *)var_r30 + (temp_r11 * 8)) != 0) {
        fn_801323D4(arg0, (s32)(m1 - 0x10D0));
        goto exit0;
    }
    if (((Unk_2A6B476C *)arg0)->unk0x144 != 0) {
        goto block_pop;
    }
    if (((Unk_2A6B476C *)arg0)->unk0x148 != 0) {
        goto block_err2;
    }
    if (temp_r11 == 0) {
        goto block_process;
    }
block_err2:
    fn_801323D4(arg0, (s32)(m2 - 0x10B0));
exit0:
    return false;
}

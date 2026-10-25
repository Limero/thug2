// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80229928-0x80229A70 (328B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EC0;
s32 fn_80145104(Unk_C7387A53 * obj);
u32 fn_800145AC(void);
s32 fn_80198F7C(s32 v);
s32 GetChecksum_3(Unk_6A70655D * obj, u32 hash);
s32 fn_801813F0(CStruct * x);
s32 fn_8022A470(CScript * obj);
void fn_80229918(CScript * obj);

bool fn_80229928(CScript *arg0) {
    s32 sp8;
    register s32 var_r10 __asm__("r10");
    register s32 fp __asm__("r11");
    register s32 fv __asm__("r9");
    s32 var_r11;
    s32 var_r9;

    __asm__("" : : "m"(sp8));
    __asm__ volatile("li 0,1");
    fp = arg0->unk0x1C;
    var_r10 = 1;
    __asm__ volatile("stw 0,8(1)");
    fv = ((Unk_FFAD6788 *)fp)->unk0x68;
    if (!(fv & 1)) {
        var_r10 = 0;
    }
    if (var_r10 == 0) {
        return true;
    }
    if (fn_80145104(arg0->unk0x18) == 0) {
        return true;
    }
    if (*(s32 *)((char *)((Unk_A55B6B5C *)arg0->unk0x18)->unk0x2A8 + 0x1C) <= 9) {
        return true;
    }
    /* raw cmplwi K + blt (unsigned-LT immediate unreachable in plain C):
       displacement reloc-masked; label 8 = shared return-1 block below */
    __asm__ volatile("cmplwi %0, 0x3e8\n\tblt 8f" :: "r"(
        (u32)(fn_800145AC() - arg0->unk0x1E4)));
    if (fn_80198F7C(lbl_80305EC0) == QB_NETFIREFIGHT) {
        if (fn_801813F0(*(s32 *)((char *)GetChecksum_3(arg0->unk0x18,
                                                    QB_SKATERSCORE) +
                                0x1C)) <= 0) {
            return true;
        }
    }
    if (fn_8022A470(arg0) != 0) {
        return true;
    }
    var_r11 = 1;
    if (!(((Unk_A55B6B5C *)arg0->unk0x18)->unk0x114 & 4)) {
        var_r11 = 0;
    }
    if (var_r11 != 0) {
        __asm__ volatile("8:");
        return true;
    }
    if ((u32)(fn_800145AC() - arg0->unk0x1E4) > 0x1388U) {
        fn_80229918(arg0);
        return false;
    }
    var_r9 = 1;
    if (!(arg0->unk0x1D8 & 2)) {
        var_r9 = 0;
    }
    if (var_r9 != 0) {
        return true;
    }
    return false;
}

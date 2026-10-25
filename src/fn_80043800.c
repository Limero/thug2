// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80043800-0x800438E8 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800439B0(s32);
extern void *lbl_802FFE98[];
void fn_8000F320(void *);
s32 Mem_Alloc(s32);
void fn_8000F2F8(void *, s32);
s32 fn_80058EE4();
void fn_80043800(Unk_E80761A5 *arg0, s32 arg1, s32 arg2) {
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r31;
    s32 var_r31_2;
    s32 temp_r3;
    void *g;
    void *pg;
    register s32 pgh __asm__("r30");

    if ((s32) arg0->unk0x1AC != 0) {
        g = lbl_802FFE98[0];
        fn_8000F2F8(g, *(s32 *)((char *)g + 0x124));
        arg0->unk0x1A0 = Mem_Alloc(arg1 * 4);
        g = lbl_802FFE98[0];
        fn_8000F320(g);
        if (arg1 > 0) {
            var_r31 = 0;
            var_r30 = arg1;
            do {
                temp_r3 = fn_80058EE4();
                var_r30 -= 1;
                *(s32 *)((char *)(var_r31 + (s32)arg0->unk0x1A0)) = temp_r3;
                var_r31 += 4;
            } while (var_r30 != 0);
        }
    }
    if (arg2 == 0) {
        __asm__ volatile("lis %0,%1@ha" : "=&r"(pgh) : "s"(lbl_802FFE98));
        arg0->unk0x1A4 = arg1;
        g = *(void **)((char *)pgh - 0x168);
        fn_8000F2F8(g, *(s32 *)((char *)g + 0x124));
        arg0->unk0x19C = Mem_Alloc(arg1 * 4);
        g = *(void **)((char *)pgh - 0x168);
        fn_8000F320(g);
        if (arg1 > 0) {
            var_r30_2 = arg1;
            var_r31_2 = 0;
            do {
                temp_r3 = fn_80058EE4();
                var_r30_2 -= 1;
                *(s32 *)((char *)(var_r31_2 + (s32)arg0->unk0x19C)) = temp_r3;
                var_r31_2 += 4;
            } while (var_r30_2 != 0);
        }
    }
    fn_800439B0(arg0);
}

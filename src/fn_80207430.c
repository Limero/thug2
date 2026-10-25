// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80207430-0x80207538 (264B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AF320;
extern f64 lbl_802AF328;
extern s32 fn_800145AC(void);
extern s32 fn_8009D29C(s32);
extern void *fn_80206F7C(Unk_90685748 *, s32);
void fn_80207430(void *arg0, s32 arg1, s32 arg2) {
    volatile double _dummy;
    struct { char _pad[8]; union { u32 w[2]; f64 d; } u; } cvts;
    register s32 a0 __asm__("r29");
    register s32 a1 __asm__("r28");
    register s32 a2 __asm__("r27");
    register f32 newv __asm__("fr31");
    register s32 idx4 __asm__("r30");
    register s32 hb __asm__("r31");
    s32 *iarr;
    s32 count;
    f64 magic;
    u32 hm;
    f32 cur2;
    register s32 wp __asm__("r9");
    s32 off2;
    s32 i;

    a0 = (s32)arg0;
    a1 = arg1;
    idx4 = a1 * 4;
    hb = a0 + 0x9AC;
    newv = lbl_802AF320;
    a2 = arg2;
    if (*(f32 *)((char *)hb + idx4) != newv) {
        if (a2 != 0) {
            hm = QB_INT_TO_DOUBLE_BIAS;
            cvts.u.w[1] = (u32)fn_800145AC();
            magic = lbl_802AF328;
            __asm__ volatile("" : "+f"(magic));
            cvts.u.w[0] = hm;
            cur2 = *(f32 *)((char *)hb + idx4);
            __asm__ volatile("" : "+f"(cur2));
            if (!((f32)(cvts.u.d - magic) > cur2)) {
                return;
            }
        }
        *(f32 *)((char *)hb + idx4) = newv;
    }
    off2 = a1 * 4;
    iarr = (s32 *)(a0 + 0xA04);
    if (*(s32 *)((char *)iarr + off2) != a2) {
        *(s32 *)((char *)iarr + off2) = a2;
        hb = fn_8009D29C(a1);
        count = ((Unk_1E0E1A41 *)a0)->unk0xA5C;
        i = 0;
        if (i < count) {
            wp = a0 + 0xA60;
            __asm__ volatile("" : "+r"(wp));
            for (; i < count; i++) {
                s32 t;
                t = *(s32 *)wp;
                __asm__ volatile("addi %0,%0,4" : "+r"(wp));
                if (hb == t) {
                    return;
                }
            }
        }
        if (a2 != 0) {
            *(s32 *)((char *)fn_80206F7C(a0, 1) + 8) = hb;
        } else {
            *(s32 *)((char *)fn_80206F7C(a0, 2) + 8) = hb;
        }
    }
}

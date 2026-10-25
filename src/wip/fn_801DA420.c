// WIP DRAFT (non-matching) — hand-rebuilt from ps_disasm (PS intrinsics)
// extra_cflags: -mps-float
// PARKED 93.0% (160/172 insn masked match): semantics fully recovered incl. all PS ops
// (__builtin_ps_mul/merge00/madd/sum0/rsqrte/res under -mps-float; psq_l/st pair loads;
// %10 counter loop via mulhw idiom). Remaining 12 diffs are scheduler/regalloc artifacts:
// (a) min() compare reads the copied reg (f0) instead of raw call result (f1);
// (b) K-anchor lis schedules AFTER the 0x42C store (want before);
// (c) dot2*K fmuls A/C operands swapped (want A=f0,C=f11); asm wedge freezes surrounding loads;
// (d) lt-path K-load FPR colors rotate {f13,f12,f0}->{f12,f0,f13};
// (e) counter lwz sinks past fdivs; magic lis/ori hoists late.
// Key levers found: register f32 pin __asm__("fr1") keeps call result in f1 across PS
// builtins; volatile-cast preserves provably-dead 0x42C store (DSE); two-step clamp staging
// (load->copy->barrier->compare-raw-v) matches both clamp arms; r8/r10 GPR pins fix block2
// obj/t8 webs; shared ganchor asm for lbl_80305F44 load+store.
// family=m2c range=0x801DA420-0x801DA6D0 size=688B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
f32 fn_801417B8(CScript * arg0, s32 arg1);
f32 fn_8014030C(s32 arg0, s32 arg1, Unk_FFAD6788 * arg2);
extern char lbl_802AD278[];
extern f32 lbl_802AD5B8;
extern f32 lbl_802AD5BC;
extern f32 lbl_802AD5C0;
extern f32 lbl_802AD5C4;
extern f32 lbl_802AD5C8;
extern f32 lbl_802AD5CC;
extern f32 lbl_802AD5D0;
extern char lbl_80305F44[];

volatile double _dummy1;
volatile double _dummy2;

void fn_801DA420(Unk_E5E3B9C6 *arg0) {
    f32 var_f31;
    f32 var_f0;
    register f32 temp_f1 __asm__("fr1");
    f32 cmpv;
    f32 temp_f13;
    f32 temp_f12;
    f32 temp_f11;
    f32 temp_f0;
    Unk_F6B09CAF *var_r31;
    s32 temp_r30;
    Unk_C7387A53 *temp_r9;
    s32 temp_r0;
    s32 var_r11;
    s32 temp_r8;
    register s32 o2 __asm__("r10");
    register s32 temp_r8p __asm__("r8");
    Unk_9BABB393 *ganchor;
    __ps_t temp_v13;
    __ps_t temp_v12;
    __ps_t temp_v0;
    f32 sp8[2];
    f32 sp16[2];

    var_r31 = (s32)arg0;
    temp_r30 = arg0->unk0xC;
    if (arg0->unk0x290 == 0) {
        goto L504;
    }
    temp_r9 = arg0->unk0x15BC;
    if (temp_r9->unk0xAC != 0) {
        goto L504;
    }
    if (temp_r9->unk0xA0 != 0) {
        goto L504;
    }
    temp_f1 = fn_801417B8(temp_r30, QB_SKATER_MAX_SPEED_STAT);
    {
        {
            s32 obj = var_r31->unk0xC;
        temp_v13 = ((Unk_073F5245 *)obj)->unk0xC0;
        temp_v12 = *(__ps_t *)lbl_802AD278;
        temp_v13 = __builtin_ps_mul(temp_v13, temp_v13);
        temp_v0 = ((Unk_073F5245 *)obj)->unk0xB8;
        temp_f11 = lbl_802AD5B8;
        temp_v13 = __builtin_ps_merge00(temp_v13, temp_v12);
        temp_v0 = __builtin_ps_madd(temp_v0, temp_v0, temp_v13);
        temp_v0 = __builtin_ps_sum0(temp_v0, temp_v0, temp_v0);
        temp_v0 = __builtin_ps_rsqrte(temp_v0);
        temp_v0 = __builtin_ps_res(temp_v0);
        *(__ps_t *)sp8 = temp_v0;
        temp_f11 = lbl_802AD5B8;
        __asm__ volatile("fmuls %0,%1,%2" : "+f"(temp_f11) : "f"(temp_f1), "f"(temp_f11));
        temp_f13 = sp8[0];
        var_f0 = temp_f13;
        if (var_f0 < temp_f11) {
            return;
        }
        var_f31 = var_f0 / temp_f1;
        }
    }
    cmpv = fn_8014030C(QB_PHYSICS_TRANSFER_SPEED_LIMIT_OVERRIDE_MAX, 1, temp_r30);
    __asm__("" : "+f"(cmpv));
    if (var_f31 < cmpv) {
        var_f0 = var_f31;
    } else {
        var_f0 = cmpv;
    }
    var_r31->unk0x42C = var_f0;
    temp_f0 = lbl_802AD5BC;
    var_r31->unk0x3BC = temp_f0;
    var_r31->unk0x3C0 = temp_f0;
    goto L518;
L504:
    temp_f13 = var_r31->unk0x42C;
    if (temp_f13 == lbl_802AD5C0) {
        return;
    }
L518:
    var_r31->unk0x3B8 = lbl_802AD5C4;
    temp_f1 = fn_8014030C(QB_PHYSICS_TRANSFER_SPEED_LIMIT_OVERRIDE_DROP_RATE, 1, temp_r30);
    temp_f13 = var_r31->unk0x94;
    temp_f0 = var_r31->unk0x42C;
    temp_f12 = lbl_802AD5C0;
    temp_f13 = temp_f13 * temp_f1;
    temp_f0 = temp_f0 - temp_f13;
    *((volatile f32 *)&var_r31->unk0x42C) = temp_f0;
    if (temp_f0 < temp_f12) {
        f32 v3b8 = var_r31->unk0x3B8;
        f32 kc8 = lbl_802AD5C8;
        var_r31->unk0x42C = temp_f12;
        if (v3b8 == kc8) {
            return;
        }
        var_r31->unk0x3B8 = lbl_802AD5CC;
        return;
    } else {
        temp_f1 = fn_801417B8(var_r31->unk0xC, QB_SKATER_MAX_SPEED_STAT);
        temp_r8p = var_r31->unk0x15BC;
        o2 = var_r31->unk0xC;
        temp_v13 = ((Unk_073F5245 *)o2)->unk0xC0;
        temp_v12 = *(__ps_t *)lbl_802AD278;
        var_f31 = temp_f1;
        temp_v13 = __builtin_ps_mul(temp_v13, temp_v13);
        temp_v0 = ((Unk_073F5245 *)o2)->unk0xB8;
        temp_r0 = ((Unk_31DE137E *)temp_r8p)->unk0x1C;
        temp_f11 = lbl_802AD5D0;
        temp_v13 = __builtin_ps_merge00(temp_v13, temp_v12);
        temp_f12 = var_r31->unk0x42C;
        temp_v0 = __builtin_ps_madd(temp_v0, temp_v0, temp_v13);
        temp_v0 = __builtin_ps_sum0(temp_v0, temp_v0, temp_v0);
        temp_v0 = __builtin_ps_rsqrte(temp_v0);
        temp_v0 = __builtin_ps_res(temp_v0);
        *(__ps_t *)sp16 = temp_v0;
        temp_f12 = temp_f12 * var_f31;
        temp_f13 = sp16[0];
        temp_f0 = temp_f13;
        temp_f11 = temp_f0 * temp_f11;
        if (temp_r0 != 1) {
            temp_f0 = var_r31->unk0x3BC;
            temp_f13 = temp_f0;
            __asm__("" : "+f"(temp_f13));
            if (temp_f11 < temp_f0) {
                temp_f13 = temp_f11;
            }
            var_f0 = temp_f13;
            __asm__("" : "+f"(temp_f13));
            if (temp_f12 < temp_f13) {
                var_f0 = temp_f12;
            }
        } else {
            temp_f0 = var_r31->unk0x3BC;
            temp_f13 = temp_f0;
            __asm__("" : "+f"(temp_f13));
            if (temp_f12 < temp_f0) {
                temp_f13 = temp_f12;
            }
            var_f0 = temp_f13;
        }
        if (var_f0 < var_f31) {
            {
                f32 kc8 = lbl_802AD5C8;
                f32 kc0 = lbl_802AD5C0;
                f32 v3b8 = var_r31->unk0x3B8;
                var_r31->unk0x42C = kc0;
                if (v3b8 == kc8) {
                    return;
                }
                var_r31->unk0x3B8 = lbl_802AD5CC;
                return;
            }
        }
        {
            var_r31->unk0x3BC = var_f0;
            temp_f1 = fn_801417B8(var_r31->unk0xC, QB_SKATER_MAX_SPEED_STAT);
            temp_f0 = var_r31->unk0x3BC;
            __asm__ volatile("lis %0,%1@ha" : "=r"(ganchor) : "s"(lbl_80305F44));
            temp_f0 = ((var_r11 = ganchor->unk0x5F44, temp_f0) / var_f31) * temp_f1;
            var_r31->unk0x3C0 = temp_f0;
            do {
                var_r11 = var_r11 + 1;
                var_r11 %= 10;
            } while (var_r11 == 0);
            ganchor->unk0x5F44 = var_r11;
            return;
        }
    }
}

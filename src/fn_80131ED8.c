// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131ED8-0x80131FEC (276B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "qb_constants.h"
extern u8 lbl_802FFE98[];
s32 Mem_Alloc2(s32);
void *fn_800A3D68(s32);
void fn_8000F2F8(s32, s32);
void fn_800A4460(s32, s32);
void fn_800A44C0(s32, s32);
void fn_8000F320(s32);
s32 fn_801291FC(CStruct *);
CStruct *fn_80127358(CStruct *, Unk_C7387A53 *);
s32 fn_800A3E28(s32, Unk_FFAD6788 *, s32, s32, s32, s32, s32);
void fn_80131ED8(Unk_FFAD6788 *arg0, CStruct *arg1,
                 CStruct *arg2) {
    s32 magic;
    s32 fld;
    s32 flag;
    s32 a3;
    s32 a4;
    s32 var_r31;
    s32 var_r9;
    u8 *var_r30;
    void *temp_p;
    Unk_89783F6B *temp_r3_b;
    CStruct *t;

    temp_r3_b = *(Unk_89783F6B **)&lbl_802FFE98;
    fn_8000F2F8((s32) temp_r3_b, (s32) temp_r3_b->unk0x124);
    if (arg0->unk0xE0 != NULL) {
        fn_800A4460((s32) arg0->unk0xE0, (s32) arg2);
    }
    var_r31 = arg1->unk0x4;
    if (((s32) arg0->unk0xE0 == 0) && (var_r31 != 0)) {
        arg0->unk0xE0 = fn_800A3D68(Mem_Alloc2(0x14));
    }
    temp_p = fn_801291FC(arg1);
    if (var_r31 > 0) {
        register s32 mg __asm__("r28");
        __asm__ volatile("lis %0, 0x8036" : "=r"(mg));
        var_r30 = (u8 *) temp_p;
        __asm__ volatile("ori %0, %0, 0x7192" : "+r"(mg));
        magic = mg;
        do {
            t = fn_80127358(*(CStruct **) var_r30, (Unk_C7387A53 *) 0);
            var_r30 += 4;
            __asm__ volatile("" ::: "memory");
            fld = t->unk0x8;
            var_r9 = 0;
            t = t->unk0xC;
            flag = ((fld ^ magic) == 0);
            // pin: flag (pure register xor/subfic/adde) must materialize
            // BEFORE the a3 load — the "+r" ties flag to this point and the
            // memory clobber keeps a3's lwz on the far side (want:
            // [xor][subfic][adde][lwz r5,8(r3)]; plain order sinks flag
            // below the load -> 4-word transposition at 0xA0).
            __asm__ volatile("" : "+r"(flag) :: "memory");
            a3 = t->unk0x8;
            t = t->unk0xC;
            a4 = t->unk0x8;
            t = t->unk0xC;
            if (t != NULL) {
                var_r9 = t->unk0x8;
            }
            fn_800A3E28((s32) arg0->unk0xE0, (s32) arg0, a3, a4, (s32) arg2,
                        flag, var_r9);
            var_r31 -= 1;
        } while (var_r31 != 0);
    }
    if ((s32) arg0->unk0xE0 != 0) {
        fn_800A44C0((s32) arg0->unk0xE0, (s32) arg0);
    }
    fn_8000F320(*(s32 *) lbl_802FFE98);
}

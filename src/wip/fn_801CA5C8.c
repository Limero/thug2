// WIP DRAFT (non-matching) — hand-written from disasm.
// PARKED ~55%: float staging block contains retail-only XO5=8 PS opcode
// (word 0x11206890, doc-06 hard wall — same class as parked fn_801AD5DC)
// feeding two ps_muls0 lane-multiplies; ngccc 3.9.3 has no emitter for it.
// Control flow, calls and arities are exact.
// family=m2c range=0x801CA5C8-0x801CA750 size=392B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// UPDATED 2026-09-15: phantom-arg drop (addr-literal + bare-0 classes); now 4.1%.
#include "structs.h"
extern f32 lbl_802ACE60;
extern f32 lbl_802ACE64;
extern f32 lbl_802ACE68;
extern f32 lbl_802ACE6C;
void fn_8010794C(Unk_C7387A53 *);
s32 fn_80107B20(Unk_E9DCA07D *, s32);
s32 fn_80107D30(Unk_2DB370CA *);
void fn_80107D7C(Unk_2DB370CA *);
s32 fn_80060DE4(Unk_C7387A53 *);
void fn_8005B5FC(s32, f32);
void fn_8005955C(void);
void fn_800DDD98(s32, void *);
void fn_800DDDAC(s32, void *);
void CObject_RemoveRefLink(CStruct *, CStruct *);
void fn_801CA5C8(Unk_67E10D8C *arg0) {
    s32 ctx[34];
    s32 sp90[4];
    s32 spA0[4];
    s32 spB0;
    f32 spC8p[4];
    f32 spD8;
    s32 temp_r31;
    Unk_4370369C *src;
    fn_8010794C(ctx);
    src = *((void * *)&arg0->unk0xC);
    spD8 = lbl_802ACE60;
    *(__ps_t *)(char *)ctx = src->unk0x58;
    ((Unk_73778A2B *)ctx)->unk0x8 = src->unk0x60;
    ((Unk_73778A2B *)ctx)->unk0x10 = src->unk0x58;
    ((Unk_73778A2B *)ctx)->unk0x18 = src->unk0x60;
    ((Unk_F6393DBC *)ctx)->unk0x14 -= lbl_802ACE68;
    ((Unk_F6393DBC *)ctx)->unk0x4 += lbl_802ACE64;
    *(__ps_t *)(char *)spC8p = src->unk0x88;
    ((Unk_EA529D06 *)spC8p)->unk0x8 = src->unk0x90;
    temp_r31 = fn_80107B20(ctx, 1);
    if (temp_r31 == 0) {
        if (spB0 != 0) {
            CObject_RemoveRefLink(spB0, &spB0);
            spB0 = temp_r31;
        }
    } else {
        if ((*(s32 *)(arg0->unk0x2B8 + 0x1C) != 4) &&
            (fn_80107D30(ctx) != 0)) {
            temp_r31 =
                fn_80060DE4((void *)((CScript *)arg0->unk0x2B4)->unk0x210);
            if (temp_r31 != 0) {
                fn_80107D7C(ctx);
                fn_8005B5FC(temp_r31, lbl_802ACE6C);
            } else {
                fn_80107D7C(ctx);
                fn_8005955C();
            }
        }
        fn_800DDD98(arg0->unk0x2C4, &sp90);
        fn_800DDDAC(arg0->unk0x2C4, &spA0);
        if (spB0 != 0) {
            CObject_RemoveRefLink(spB0, &spB0);
            spB0 = 0;
        }
    }
}

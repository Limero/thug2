// PARKED 2026-10-03 — 4.8% (324 B).  PS/pairs body: `psq_l`/`psq_st`/`ps_madd`
// sequence from 0x802344CC on, preceded by a doc-58 phantom call argument
// (fn_802403A0).  FPR wall plus phantom args; needs `-mps-float` and the
// doc-58 pass before it is worth anything.  Best-known body retained.
//
// family=m2c range=0x80234444-0x80234588 size=324B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// UPDATED 2026-09-15 (g): -> 4.8%. doc-58 m2c phantom call argument
// (fn_802403A0): the label/format address materialised for a store was ALSO
// read as the callee's argument (tools/label_call_arg_scan.py).
#include "types.h"
#include "structs.h"
s32 fn_8023378C(s32);
extern char lbl_802B09C8[];
extern char lbl_802B09E4[];
extern char lbl_80305FF4[];
extern char lbl_80305FF8[];
static s32 sp10;
static s32 sp18;
static s32 sp28;

void fn_80234444(Unk_F5317C5D *arg0) {
    s32 sp30;
    f32 sp20;
    Unk_638CF717 sp8;
    f32 temp_f0;

    fn_802403A0();
    *((s32 *)&sp8) = arg0->unk0x0;
    *(s32 *)lbl_80305FF4 = 0;
    sp8.unk0x4 = (u16) arg0->unk0x4;
    fn_80238964(arg0);
    fn_802366E4(&sp8);
    fn_80238964();
    fn_802361E8(0, 0);
    fn_80238784(arg0, &sp30, fn_80238970(), arg0, &sp20);
    0;
    0;
    fn_801FC0E0();
    temp_f0 = *(f32 *)0x802B09FC;
    fn_801FA848(0, sp10 + temp_f0, sp18 + temp_f0, (sp10 + sp20) - temp_f0, (sp18 + sp28) - temp_f0);
    fn_801F672C();
    fn_801F64B8(sp10, sp18, sp10 + sp20, sp18 + sp28);
    fn_8023378C(*(s32 *)lbl_80305FF8);
    if (fn_8023C598(0) != 0) {
        fn_8023C598(1);
        fn_8023E09C(0);
    }
    *(s32 *)lbl_80305FF4 = 1;
    fn_8022D4C4(*((s32 *)fn_80238970()));
    fn_802403A0((s32)lbl_802B09E4);
}
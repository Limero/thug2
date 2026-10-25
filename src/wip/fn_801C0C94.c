// WIP DRAFT (non-matching) — hand edit (float widths fixed from m2c's s32
// casts; direct extern-f32 symbol refs fold lis+lfs; base ptrs P9C/A4 and
// arg0->0x28 re-read fresh per block like want).
//
// PARKED <50%: (a) want's inner float guard is BRANCHY [fcmpu][beq][fmr] but
// every C shape tried (if / two-exit goto / assign-in-condition && /
// volatile field load / "+f" and "+r" barriers / -O1 / all five ProDG
// versions) if-converts it to the fsel+fneg+fsel select expansion;
// (b) scratch-base register roles for the P9C/A4 chases invert vs got.
// Lerp/fmul formula, constants and statement order otherwise match.
// family=m2c range=0x801C0C94-0x801C0D58 size=196B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
extern f32 lbl_802AC614;
extern f32 lbl_802AC618;
extern f32 lbl_802AC61C;
extern f32 lbl_802AC620;
extern f32 lbl_802AC624;
extern f32 lbl_802AC628;
void fn_801C0C94(Unk_FFAD6788 *arg0, f32 *arg1, f32 *arg2) {
    Unk_C7387A53 *tbl9C;
    Unk_9994C3F5 *tblA4;
    f32 var_f0;
    f32 temp_f0;
    f32 temp_f13;
    f32 newv;
    f32 out2;
    f32 v;
    f32 res;

    tbl9C = arg0->unk0x9C;
    var_f0 = lbl_802AC614;
    if (tbl9C->unk0x20 == 0) {
        goto skip1;
    }
    temp_f0 = *((volatile f32 *)&tbl9C->unk0x24);
    if (temp_f0 == var_f0) {
        goto skip1;
    }
    var_f0 = temp_f0;
skip1:
    tblA4 = arg0->unk0xA4;
    temp_f13 = arg0->unk0x28;
    newv = ((var_f0 - temp_f13) * *((f32 *)&tblA4->unk0x11C)) + temp_f13;
    arg0->unk0x28 = newv;
    out2 = *((f32 *)&tblA4->unk0xD0) * newv;
    *arg2 = out2;
    v = *(f32 *)((char *)arg0->unk0x9C + 0x28);
    if (v < lbl_802AC618) {
        *arg2 = out2 * ((((v + lbl_802AC61C) / lbl_802AC61C) * lbl_802AC620) + lbl_802AC624);
    }
    temp_f13 = arg0->unk0x28;
    tblA4 = arg0->unk0xA4;
    res = *((f32 *)&tblA4->unk0xDC);
    if (temp_f13 < lbl_802AC614) {
        res = ((res - lbl_802AC628) * temp_f13) + lbl_802AC628;
    }
    *arg1 = res;
}

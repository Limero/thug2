// PARKED DIFF 18.6%: rebuilt from disasm; semantic content correct. Blockers:
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 34.4262% -> 37.7049% `volatile` keyword(s) removed from the body
// (a) LOCALS SORT — want [sp8@r1+8][gap 0xC-0x1F][cvt hi/lo@0x20/0x24]; every
// C layout gives cvt@8 + sp8@0x10 (GCC sorts the 8-aligned volatile union LOW;
// §6m-93). Tried: volatile double dummy, padded-struct container (frame-template
// recipe 86 -> kept &fr in saved reg, frame 0x48), aligned attrs, plain union
// (SRA decomposed it into SAVED-reg webs r29/r30 — volatile union fixes that),
// register-pin mgc->fr13 (magic lands f13 OK but cascades allocation).
// (b) want-extra dead `mr r9,r11` after the 8009FDD8 return (§6x-89 family).
// (c) FP roles: scale->f11 + const71C->f12 in want vs swapped in got.
// Everything else (chained script pair, min-clamp tail, fctiwz round) matches.
// family=m2c range=0x80214FF0-0x802150E4 size=244B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 32.3% ([1]rev->32.3%).
// UPDATED 2026-09-15: phantom-arg drop (addr-literal + bare-0 classes); now 34.4%.
#include "qb_constants.h"
#include "structs.h"
extern f64 lbl_802AF710;
extern f32 lbl_802AF718;
extern f32 lbl_802AF71C;
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
extern s32 GetStructure(s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern f32 fn_800144C8(void);
void fn_80214FF0(Unk_9C44AE00 *arg0) {
    union { u32 w[2]; f64 d; } cvt;
    f32 sp8;
    f32 temp_f0;
    f32 temp_f12;
    f32 var_f13;
    Unk_C8FEE62D *temp_r8;
    temp_r8 = (void *) *(s32 *)((s32)(GetChecksum_3(arg0->unk0xC, QB_SKATERSCORE)) + 0x1C);
    cvt.w[1] = temp_r8->unk0x18 ^ 0x80000000;
    cvt.w[0] = QB_INT_TO_DOUBLE_BIAS;
    if ((s32) ((f32) (cvt.d - lbl_802AF710) * *((f32 *)&temp_r8->unk0x6C)) > 0) {
        arg0->unk0x1944 = lbl_802AF718;
        return;
    }
    GetFloat(GetStructure(QB_WALK_PARAMETERS), QB_RUN_ADJUST_RATE, &sp8, 1);
    var_f13 = temp_f0;
    temp_f0 = arg0->unk0x1944 - (f32) (sp8 * fn_800144C8());
    temp_f12 = lbl_802AF71C;
    if (temp_f0 < temp_f12) {
        var_f13 = temp_f12;
    }
    arg0->unk0x1944 = var_f13;
}

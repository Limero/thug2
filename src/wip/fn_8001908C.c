// PARKED 2026-10-03 — base 8.1% (1016 B, 260 words).  Random-sample pick.
// m2c best guess retained.  No unsigned dispatch tree in the want, so recipe
// 7w does not apply; residual is decode/prototype.
//
// family=m2c range=0x8001908C-0x80019484 size=1016B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 9.6% ([5]rev->9.6%).
// 2026-09-22 literal->symbol substitution: 9.6 -> 12.3 (symbol for 0x80300134, 0x80290D78, 0x80290D64, 0x80290D6C)
extern char lbl_80290D6C[];
extern char lbl_80290D64[];
extern char lbl_80290D78[];
extern char lbl_80300134[];
#include "structs.h"
bool ScriptNgc_Message(CStruct *);
void fn_8009533C(CStruct *);
void fn_80128294(CStruct *, void *, void *, s32);
s32 fn_8012834C(CStruct *, void *, void *, s32);
s32 fn_80053558(s32, s32, s32, s32, s32);
s32 fn_800537D8(s32);
s32 strcpy(s32, s32);
static s32 sp24;
static s32 spD0;
static s32 spD4;

bool ScriptNgc_Message(CStruct *arg0) {
    f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    s32 spE8;
    s32 spE4;
    s32 spE0;
    s32 spDC;
    f32 spD8;
    s32 *spD4;
    s32 *spD0;
    s32 sp50;
    s32 sp48;
    s32 sp44;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    s32 *sp24;
    s32 sp1C;
    s32 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f31;
    f32 var_f0;
    s32 temp_r30;
    s32 var_r27;
    Unk_9994C3F5 *var_r30;

    fn_80094858(&sp8, 0x80290000, *(f32 *)0x80290D80);
    spD4 = NULL;
    spD0 = NULL;
    if ((fn_80128170(arg0, 0x80290D50, &spD0, 0) == 0) || (fn_80128170(arg0, 0x80290D58, &spD4, 0) == 0)) {
        fn_800948AC(&sp8, 2);
        return false;
    }
    spD8 = *(f32 *)0x8030012C;
    fn_8012834C(arg0, 0x80290D60, &spD8, 0);
    if ((spD0 != NULL) && (spD4 != NULL) && ((strcpy(&sp50, spD0), spD0 = &sp50, var_r30 = fn_800537D8(&sp50), ((var_r30 == NULL) == 0)) || (fn_80053558(spD0, 0, 0, 0, 0), var_r30 = fn_800537D8(spD0), ((var_r30 == NULL) == 0)))) {
        sp24 = spD4;
        spE4 = 0x80;
        spE8 = 0xFF;
        spDC = 0x80;
        spE0 = 0x80;
        fn_80128294(arg0, 0x80290D40, &spDC, 0);
        fn_80128294(arg0, 0x80290D44, &spE0, 0);
        fn_80128294(arg0, 0x80290D48, &spE4, 0);
        fn_80128294(arg0, 0x80290D4C, &spE8, 0);
        sp44 = spE8 | (spE4 << 8) | (spE0 << 0x10) | (spDC << 0x18);
        temp_r30 = var_r30->unk0x8;
        sp1C = temp_r30;
        if (temp_r30 != 0) {
            sp2C = spD8;
            spF8 = *(s32 *)0x80290D80;
            spEC = *(f32 *)0x80290D84;
            fn_8012834C(arg0, lbl_80290D64, &spEC, 0);
            sp34 = spEC;
            sp30 = spEC;
            sp48 = 0;
            fn_800945F8(temp_r30, sp24, &spF0, &spF4);
            temp_f31 = *(f32 *)0x80290D88;
            if (spF0 > temp_f31) {
                spF0 = temp_f31;
            }
            if (fn_8012834C(arg0, lbl_80290D6C, &spF8, 0) != 0) {
                var_f0 = spF8;
            } else {
                var_f0 = (temp_f31 - (spF0 * spEC)) * *(f32 *)0x80290D8C;
            }
            var_r27 = 0;
            spFC = temp_f0;
            sp100 = temp_f0;
            temp_f0 = *(s32 *)0x80290D80;
            sp28 = var_f0;
            if ((fn_8012834C(arg0, 0x80290D70, &spFC, 0) != 0) || (fn_8012834C(arg0, lbl_80290D78, &sp100, 0) != 0)) {
                fn_8012834C(arg0, 0x80290D70, &spFC, 0);
                var_r27 = 1;
                fn_8012834C(arg0, lbl_80290D78, &sp100, 0);
                sp28 = *(f32 *)0x80300130 + spFC;
                sp2C = *(f32 *)lbl_80300134 + sp100;
            }
            temp_f0_2 = *(s32 *)0x80290D80;
            sp38 = temp_f0_2;
            sp3C = temp_f0_2;
            fn_8009533C(&sp8);
            *(s32 *)0x80300130 = (f32) ((spF0 * spEC) + sp28);
            *(s32 *)lbl_80300134 = spD8;
            if (var_r27 == 0) {
                *(s32 *)0x8030012C = (f32) (spD8 + (f32) (f64) (s32) (spF4 * spEC));
            }
        }
    }
    fn_800948AC(&sp8, 2);
    return true;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80232B98-0x80232CDC (324B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern char lbl_8029FC18[];
s32 fn_8023C598(s32);
void fn_8023E09C(CStruct *, s32);
void fn_80232DFC(void *, s32);
void fn_80243EF0();
void fn_802438A4();
s32 fn_8019CF2C(s32);
s32 fn_801749CC(Unk_C7387A53 *);
s32 fn_80238970();
void fn_802394F8(Unk_673C6403 *, s32, Unk_C7387A53 *);
void fn_802334D4(Unk_C7387A53 *);
void fn_8019CF94();
void fn_80232B98(Unk_C7387A53 *arg0, s32 arg1) {
    s32 sp8[4];
    register s32 *q __asm__("r11");
    s32 *pA;
    s32 *pB;
    Unk_C7387A53 *temp_r3;
    Unk_C7387A53 *temp_r9;

    if (arg1 != 0) {
        arg0->unk0x44 = arg1;
    }
    arg0->unk0x48 = 0;
    if (fn_8023C598(0) != 0) {
        s32 t = fn_8023C598(1);
        s32 b = ((arg0->unk0x44 ^ QB_EDIT) == 0);
        fn_8023E09C(t, b);
    }
    if ((arg1 == QB_TEST_PLAY) || (arg1 == QB_REGULAR_PLAY)) {
        fn_80232DFC(arg0, 0);
        fn_80243EF0();
        fn_802438A4();
    } else {
        fn_80232DFC(arg0, 1);
    }
    pB = &sp8[1];
    q = &sp8[0];
    q[3] = (s32)lbl_8029FC18;
    pA = q;
    temp_r3 = fn_8019CF2C(0);
    pB[1] = (s32)temp_r3;
    if (arg1 == QB_EDIT) {
        fn_801749CC(lbl_80305EAC);
        temp_r9 = (Unk_C7387A53 *)pB[1];
        temp_r9->unk0x50 = 320;
        temp_r9->unk0x54 = 100;
        fn_802394F8(fn_80238970(), 0, 0);
    } else {
        temp_r3->unk0x50 = 320;
        temp_r3->unk0x54 = 50;
    }
    fn_802334D4(arg0);
    pA[3] = (s32)lbl_8029FC18;
    fn_8019CF94();
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131474-0x8013152C (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80305F9C[];
s32 fn_8009CF2C(CStruct *);
void fn_80137CB4(Unk_9F066EC1 *);
s32 fn_8021B55C(s32, s32);
void fn_8013DE78(void *, Unk_C71E6DE1 *);

void fn_80131474(s32 arg0, CScript *arg1, s32 arg2, s8 arg3) {
    struct {
        s32 sp8;
        s32 spC;
        s32 sp10;
        s8 sp14;
        char pad15[3];
        u8 mb18;
        u16 mh1A;
        void *mp1C;
        s32 unk20;
        s32 m24;
        u8 m28;
        char tail[0x16];
    } fr;
    s32 temp_r27;
    s32 b55c;

    temp_r27 = *(s32 *)&lbl_80305F9C;
    if (fn_8009CF2C(temp_r27) != 0) {
        fn_80137CB4(&fr.mb18);
        fr.sp8 = arg0;
        fr.spC = -1;
        fr.sp10 = arg2;
        fr.sp14 = arg3;
        if (arg1 != NULL) {
            fr.spC = arg1->unk0x18;
        }
        b55c = fn_8021B55C(temp_r27, 0);
        fr.mp1C = &fr.sp8;
        fr.mh1A = 0x10;
        fr.mb18 = 0x49;
        fr.m24 = 2;
        fr.m28 = 8;
        fn_8013DE78(b55c, &fr.mb18);
    }
}
// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80130F40-0x80131008 (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80305F9C[];
s32 fn_8009CF2C(CStruct *);
void fn_80137CB4(Unk_9F066EC1 *);
s32 fn_80129C08(s32, void *, s32, s32, s32);
s32 fn_8021B55C(s32, s32);
void fn_8013DE78(void *, Unk_C71E6DE1 *);

void fn_80130F40(s32 arg0, s32 arg1, CScript *arg2) {
    struct {
        s32 sp8;
        s32 spC;
        char buf[0x400];
        u8 mb410;
        u16 mh412;
        void *mp414;
        char pad418[4];
        s32 unk41C;
        u8 m420;
        char tail[0x12];
    } fr;
    s32 temp_r28;
    s32 temp_r30;
    s32 b55c;

    temp_r28 = *(s32 *)&lbl_80305F9C;
    if (fn_8009CF2C(temp_r28) != 0) {
        fn_80137CB4(&fr.mb410);
        fr.sp8 = arg0;
        fr.spC = -1;
        if (arg2 != NULL) {
            fr.spC = arg2->unk0x18;
        }
        temp_r30 = fn_80129C08(arg1, &fr.buf, 0x400, 1, 0);
        b55c = fn_8021B55C(temp_r28, 0);
        fr.mp414 = &fr.sp8;
        fr.mh412 = temp_r30 + 8;
        fr.mb410 = 0x48;
        fr.unk41C = 2;
        fr.m420 = 8;
        fn_8013DE78(b55c, &fr.mb410);
    }
}
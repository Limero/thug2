// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80161A00-0x80161AC0 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8021B55C(s32, s32);
void fn_80137CB4(Unk_9F066EC1 *);
void fn_8013DE78(void *, Unk_C71E6DE1 *);
typedef struct B41_msg {
    u8 f0; u8 f1; s16 f2; s32 f4; s32 f8; s32 fc; u8 f10;
    s32 f14; s32 f18; s32 f1c; u8 f20; char pad21[3];
} B41_msg;
typedef struct B41_pr { u8 b; u8 p3[3]; s32 w; } B41_pr;
typedef struct B41_frame {
    B41_msg m;
    char _pad24[4];
    s32 sp30;
    s32 sp34;
    B41_pr pr;
} B41_frame;
bool ScriptBroadcastEnterVehicle(CStruct *arg0) {
    B41_frame f;
    Unk_1D62F22E *p30;
    CStruct *pptr;
    s32 temp_r29;
    s32 temp_r3;

    temp_r29 = lbl_80305F9C;
    p30 = &f.sp30;
    GetChecksum_2(arg0, QB_SKATERID, p30, 1);
    GetChecksum_2(arg0, QB_CONTROL_TYPE, &f.sp34, 1);
    if ((temp_r3 = fn_8021B55C(temp_r29, 0)) != 0) {
        fn_80137CB4(&f.m);
        f.pr.b = p30->unk0x3;
        pptr = &f.pr;
        pptr->unk0x4 = f.sp34;
        f.m.f0 = 0x89;
        f.m.f4 = (s32)(long)pptr;
        f.m.fc = 2;
        f.m.f2 = 8;
        f.m.f10 = 8;
        fn_8013DE78(temp_r3, &f.m);
    }
    return true;
}

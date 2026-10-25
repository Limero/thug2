// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801614BC-0x8016158C (208B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
void fn_80137CB4(Unk_9F066EC1 *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8009CF2C(CStruct *);
s32 fn_8021B55C(s32, s32);
s32 fn_8013DE78(void *, Unk_C71E6DE1 *);

typedef struct {
    u8 b;
    s8 pad0;
    s16 h;
    void *ptr;
    s32 unk8;
    s32 w;
    s8 e;
    char pad1[0x17];
} msg_t;

bool ScriptReportObjectPickup(CStruct *pParams, CScript *pScript) {
    msg_t msg;
    s32 out1;
    s32 out2;
    s32 sp38;
    s32 ctx;
    s32 ret;

    ctx = lbl_80305F9C;
    fn_80137CB4(&msg);
    GetChecksum_2(pParams, QB_COLOBJID, &out1, 0);
    GetChecksum_2(pParams, QB_ID, &out2, 0);
    if (fn_8009CF2C(ctx) != 0) {
        ret = fn_8021B55C(ctx, 0);
    } else {
        ret = fn_8021B55C(ctx, out1);
    }
    sp38 = out2;
    msg.b = 0x90;
    msg.w = 2;
    msg.e = 8;
    msg.ptr = &sp38;
    msg.h = 4;
    fn_8013DE78(ret, &msg);
    return true;
}

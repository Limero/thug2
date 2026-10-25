// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80228140-0x802281BC (124B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EAC[];
void fn_80137CB4(Unk_9F066EC1 *);
s32 fn_8017E020(Unk_C7387A53 *);
void fn_8013DE78(void *, Unk_C71E6DE1 *);

bool fn_80228140(Unk_C7387A53 *arg0) {
    struct { u8 b; char p0[1]; s16 h; s32 p; char p1[4]; s32 w; s8 e; char pad2[0x13]; } sp;
    s32 mgr;
    CStruct *temp_r28;

    mgr = *(s32 *)&lbl_80305EAC;
    fn_80137CB4(&sp.b);
    temp_r28 = *(void **)arg0;
    temp_r28->unk0x4 = fn_8017E020(mgr);
    sp.b = 0x81;
    sp.w = 2;
    sp.e = 8;
    sp.p = (s32)temp_r28;
    sp.h = 8;
    fn_8013DE78(arg0->unk0xC, &sp.b);
    return true;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015B25C-0x8015B304 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct { char _0[0x37C]; Unk_31DE137E *obj; } KOA_t;
extern KOA_t *lbl_80305EAC;
s32 ContainsFlag(CStruct *, s32);
s32 fn_80128E34(CStruct *, s32, s32 *, s32);
s32 fn_801A2C10(Unk_31DE137E *, s32);
s32 fn_801A2F2C(Unk_31DE137E *, s32);
void fn_801A2A58(Unk_31DE137E *);
s32 ScriptKillObjectAnim(CStruct *arg0) {
    s32 sp8;
    Unk_31DE137E *temp_r30;
    s32 temp_r3;
    KOA_t *g;

    g = lbl_80305EAC;
    temp_r30 = g->obj;
    if (ContainsFlag(arg0, QB_CURRENT) != 0) {
        return fn_801A2C10(temp_r30, 0);
    }
    temp_r3 = ContainsFlag(arg0, QB_ALL);
    if (temp_r3 == 0) {
        sp8 = temp_r3;
        {
            register s32 *p5 __asm__("r5") = &sp8;
            register s32 c6 __asm__("r6") = 1;
            fn_80128E34(arg0, QB_NAME, p5, c6);
        }
        fn_801A2F2C(temp_r30, sp8);
    } else {
        fn_801A2A58(temp_r30);
    }
    return 1;
}

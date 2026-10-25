// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80221EAC-0x80221FF8 (332B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A83F8[];
extern s32 lbl_80305F9C;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 fn_8021D454(s32, CStruct *, s32);
s32 fn_8021D4E8(s32, CStruct *, s32);
s32 strcasecmp(s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddComponent(CStruct *, s32, s32, void *);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
bool ScriptRemovePlayer(CStruct *pParams, CScript *pScript) {
    struct {
        s32 ctx[3];
        char _p0[4];
        s32 sp18;
        s32 sp1C;
    } fr;
    s32 *pb;
    s32 *pc;
    s32 mgr;
    s32 temp_r30;
    CScript *var_r30;

    pb = &fr.ctx[0];
    pb[2] = (s32)lbl_802A83F8;
    pb[1] = 0;
    fr.sp18 = 0;
    fr.sp1C = 0;
    mgr = lbl_80305F9C;
    GetInteger(pParams, QB_INDEX, &fr.sp18, 0);
    __asm__("mr %0,%1" : "=r"(pc) : "r"(pb));
    GetString(pParams, QB_NAME, &fr.sp1C, 0);
    var_r30 = fn_8021D454(mgr, pb, 0);
    if (var_r30 != 0) {
    loop_1:
        if (fr.sp18 == 0) {
            if (strcasecmp((s32)((char *)var_r30 + 0x3C), fr.sp1C) == 0) {
                var_r30->unk0x1D8 |= 0x400;
                temp_r30 = CStruct_ctor(CStruct_new(8));
                AddComponent(temp_r30, QB_NAME, 3, fr.sp1C);
                Script_RunScript(QB_CREATE_KICK_BAN_MENU, temp_r30, 0, 0, 0);
                if (temp_r30 != 0) {
                    CStruct_delete(temp_r30, 3);
                }
            }
        } else {
            fr.sp18 -= 1;
            var_r30 = fn_8021D4E8(mgr, &fr.ctx[0], 0);
            if (var_r30 != 0) {
                goto loop_1;
            }
        }
    }
    pc[2] = (s32)lbl_802A83F8;
    return true;
}

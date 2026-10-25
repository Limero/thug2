// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80221288-0x802213D0 (328B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
extern char lbl_802A83F8[];
s32 fn_80219698(s32, s32);
void fn_80137CB4(Unk_9F066EC1 *);
s32 fn_8021B554(Unk_9994C3F5 *);
void Script_RunScript(s32, s32, s32, s32, s32);
s32 fn_8021B55C(s32, s32);
void fn_8013DE78(void *, Unk_C71E6DE1 *);
s32 fn_8021D454(s32, CStruct *, s32);
s32 fn_8022986C(CScript *);
s32 fn_8022A9B8(Unk_31DE137E *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);
s32 fn_8021D4E8(s32, CStruct *, s32);
bool ScriptEndNetworkGame(s32 arg0, s32 arg1) {
    struct {
        s32 ctx[4];
        u8 msg[0x28];
    } fr;
    s32 *spb;
    s32 *sp;
    u8 *mb;
    u8 *m;
    u8 *me;
    s32 b55cret;
    s32 mgr;
    s32 temp_r29;
    s32 var_r30;

    spb = &fr.ctx[0];
    __asm__("mr %0,%1" : "=r"(sp) : "r"(spb));
    spb[1] = 0;
    spb[2] = (s32)lbl_802A83F8;
    mgr = lbl_80305F9C;
    if (fn_80219698(mgr, arg1) != 0) {
        mb = &fr.msg[0];
        __asm__("mr %0,%1" : "=r"(m) : "r"(mb));
        fn_80137CB4(mb);
        temp_r29 = fn_8021B554(mgr);
        Script_RunScript(QB_DO_BACKEND_RETRY, 0, 0, 0, 0);
        fr.msg[0] = 0x6A;
        *(s32 *)&fr.msg[0xC] = 2;
        fr.msg[0x10] = 8;
        var_r30 = fn_8021D454(mgr, sp, 1);
        if (var_r30 != 0) {
            do {
                if (fn_8022986C(var_r30) == 0) {
                    fn_8013CC84(temp_r29, fn_8022A9B8(var_r30), m);
                }
                var_r30 = fn_8021D4E8(mgr, &fr.ctx[0], 1);
            } while (var_r30 != 0);
        }
    } else {
        me = &fr.msg[0];
        fn_80137CB4(me);
        b55cret = fn_8021B55C(mgr, 0);
        fr.msg[0] = 0x65;
        *(s32 *)&fr.msg[0xC] = 2;
        fr.msg[0x10] = 8;
        fn_8013DE78(b55cret, me);
    }
    sp[2] = (s32)lbl_802A83F8;
    return true;
}

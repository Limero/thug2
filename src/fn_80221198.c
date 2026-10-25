// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80221198-0x80221288 (240B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
extern char lbl_802A83F8[];
s32 fn_80219698(s32, s32);
void fn_80137CB4(Unk_9F066EC1 *);
s32 fn_8021B554(Unk_9994C3F5 *);
s32 fn_8021D454(s32, CStruct *, s32);
s32 fn_8022989C(CScript *);
s32 fn_8022A9B8(Unk_31DE137E *);
void fn_8013CC84(void *, s32, Unk_C71E6DE1 *);
s32 fn_8021D4E8(s32, CStruct *, s32);
bool ScriptSendGameOverToObservers(s32 arg0, s32 arg1) {
    struct {
        s32 ctx[4];
        u8 msg[0x28];
    } fr;
    s32 *spb;
    s32 *sp;
    u8 *msb;
    u8 *ms;
    s32 mgr;
    s32 temp_r29;
    s32 var_r31;

    spb = &fr.ctx[0];
    __asm__("mr %0,%1" : "=r"(sp) : "r"(spb));
    spb[1] = 0;
    spb[2] = (s32)lbl_802A83F8;
    mgr = lbl_80305F9C;
    if (fn_80219698(mgr, arg1) != 0) {
        msb = &fr.msg[0];
        __asm__("mr %0,%1" : "=r"(ms) : "r"(msb));
        fn_80137CB4(msb);
        temp_r29 = fn_8021B554(mgr);
        fr.msg[0] = 0x5A;
        *(s32 *)&fr.msg[0xC] = 2;
        fr.msg[0x10] = 8;
        var_r31 = fn_8021D454(mgr, sp, 1);
        if (var_r31 != 0) {
            do {
                if (fn_8022989C(var_r31) != 0) {
                    fn_8013CC84(temp_r29, fn_8022A9B8(var_r31), ms);
                }
                var_r31 = fn_8021D4E8(mgr, &fr.ctx[0], 1);
            } while (var_r31 != 0);
        }
    }
    sp[2] = (s32)lbl_802A83F8;
    return true;
}

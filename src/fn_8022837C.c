// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022837C-0x80228498 (284B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
void *fn_8021D358(s32, s32);
void fn_8022A42C(CScript *);
void fn_80172E64(s32, s32, s32);
s32 fn_8022986C(CScript *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddString(CStruct *, s32, void *);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);

bool fn_8022837C(Unk_71EAD930 *arg0) {
    u8 cmd = arg0->unk0x4;
    void *t9 = *(void **)arg0;
    s32 f18 = arg0->unk0x18;

    if (cmd == 0x8D) {
        if (*(s32 *)t9 >= 0) {
            void *temp = fn_8021D358(f18, ((Unk_5B449B03 *)t9)->unk0x2);
            if (temp != NULL) {
                s32 mgr = *(s32 *)&lbl_80305EAC;
                fn_8022A42C(temp);
                fn_80172E64(mgr, ((CScript *)temp)->unk0x18, 1);
                if (fn_8022986C(temp) != 0) {
                    Script_RunScript(QB_ELIMINATEDYOU, 0, 0, 0, 0);
                } else {
                    s32 hand = CStruct_ctor(CStruct_new(8));
                    AddString(hand, QB_STRING0, (char *)temp + 0x3C);
                    Script_RunScript(QB_ELIMINATEDOTHER, hand, 0, 0, 0);
                    if (hand != 0) {
                        CStruct_delete(hand, 3);
                    }
                }
            }
        } else {
            Script_RunScript(QB_ELIMINATEDNONE, 0, 0, 0, 0);
        }
    }
    return true;
}

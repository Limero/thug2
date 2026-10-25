// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802282B8-0x8022837C (196B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8021D2C4(s32, s32);
s32 fn_802204A4(Unk_C7387A53 *);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddString(CStruct *, s32, void *);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_802204AC(Unk_C7387A53 *);

bool fn_802282B8(Unk_C8FEE62D *arg0) {
    s32 f18;
    s32 t29;

    f18 = arg0->unk0x18;
    t29 = fn_8021D2C4(f18, arg0->unk0x10);
    if (((*(s32 *)*(void **)arg0 ^ QB_UNKNOWN_0xDEADFACE) != *((s32 *)*(void **)arg0 + 1)) && (fn_802204A4(f18) == 0)) {
        s32 hand = CStruct_ctor(CStruct_new(8));
        AddString(hand, QB_STRING0, t29 + 0x3C);
        Script_RunScript(QB_NOTIFY_CLIENT_CHEATING, hand, 0, 0, 0);
        if (hand != 0) {
            CStruct_delete(hand, 3);
        }
        fn_802204AC(f18);
    }
    return true;
}

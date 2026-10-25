// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C320-0x8015C3B0 (144B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 fn_801754AC(s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_80143F5C(Unk_7B36180C *, CStruct *);
s32 ScriptProfileEquals(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 var_r3;

    if (arg1 == 0) {
        goto fb;
    }
    if (arg1->unk0xBC == 0) {
        goto fb;
    }
    if (*(s32 *)((char *)(arg1->unk0xBC) + 0x1C) != (s32)QB_OBJECT_TYPE_SKATER) {
        goto fb;
    }
    var_r3 = arg1->unk0xBC;
    return fn_80143F5C(var_r3, arg0);
fb:
    if (fn_801754AC(lbl_80305EAC) == 0) {
        return 0;
    }
    var_r3 = fn_801746A4(lbl_80305EAC, 0);
    if (var_r3 == 0) {
        return 0;
    }
    return fn_80143F5C(var_r3, arg0);
}

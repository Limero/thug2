// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80199C44-0x80199DC4 (384B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AA894[];
extern char lbl_802AA89C[];
extern char lbl_802AA8A4[];
s32 fn_80128E64(CStruct *, void *, void *, s32);
s32 fn_80128CB0(CStruct *, void *, void *, s32);
s32 Mem_NewZero(s32);
s32 fn_80199558(CStruct *);
s32 fn_80199678(CStruct *, s32);
s32 fn_80199B1C(CStruct *, s32);
s32 fn_8019992C(CStruct *);
s32 fn_80199DC4(CStruct *);
s32 fn_80199EAC(CStruct *);
s32 fn_80199F9C(CStruct *);
s32 fn_80199C44(CStruct *arg0) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 var_r3;

    fn_80128E64(arg0, (s32)lbl_802AA894, &sp8, 1);
    var_r3 = 0;
    switch ((u32)sp8) {
    case QB_HIGHEST_SCORE:
        var_r3 = fn_80199558(Mem_NewZero(8));
        break;
    case QB_TARGET_SCORE:
        fn_80128CB0(arg0, (s32)lbl_802AA89C, &spC, 1);
        var_r3 = fn_80199678(Mem_NewZero(0xC), spC);
        break;
    case QB_UNKNOWN_0x6FAD9811:
        fn_80128CB0(arg0, (s32)lbl_802AA8A4, &sp10, 1);
        var_r3 = fn_80199B1C(Mem_NewZero(0xC), sp10);
        break;
    case QB_COMPLETE_GOALS:
        var_r3 = fn_8019992C(Mem_NewZero(8));
        break;
    case QB_LAST_MAN_STANDING:
        var_r3 = fn_80199DC4(Mem_NewZero(8));
        break;
    case QB_ELIMINATION:
        var_r3 = fn_80199EAC(Mem_NewZero(8));
        break;
    case QB_COLLECT_ALL_OBJECTS:
        var_r3 = fn_80199F9C(Mem_NewZero(8));
        break;
    }
    return var_r3;
}

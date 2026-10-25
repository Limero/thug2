// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80116D2C-0x80116E5C (304B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
typedef struct CStruct CStruct;
extern char lbl_8029D1C4[];
extern char lbl_8029D268[];
extern char lbl_8029D27C[];
extern char lbl_8029D288[];
extern char lbl_8029D28C[];

s32 GetText(s32 arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor();
void AddChecksum(s32 arg0, s32 arg1, s32 arg2);
void fn_80126FF4(s32 arg0, s32 arg1);
s32 fn_801168CC(s32 arg0, s32 arg1);
void fn_80128170(s32 arg0, s32 arg1, s32 *arg2, s32 arg3);
s32 sprintf(s32 arg0, ...);
void CStruct_delete(s32 arg0, s32 arg1);
s32 GetInteger(s32 arg0, s32 arg1, s32 *arg2, s32 arg3);

bool fn_80116D2C(CStruct *arg0, CStruct *arg1) {
    s32 sp8;
    s32 spC;
    s32 obj;

    sp8 = (s32)lbl_8029D268;
    if (GetText(arg1, 0, &sp8, 0) != 0) {
        CStruct_new(8);
        obj = CStruct_ctor();
        AddChecksum(obj, QB_TEXTNAME, QB_PRINTFTEXT);
        fn_80126FF4(obj, arg1);
        if (fn_801168CC(obj, obj) != 0) {
            fn_80128170(obj, (s32)lbl_8029D27C, &sp8, 0);
        } else {
            sp8 = (s32)lbl_8029D1C4;
        }
        sprintf(arg0, (s32)lbl_8029D288, sp8);
        if (obj != 0) {
            CStruct_delete(obj, 3);
        }
    } else {
        spC = 0;
        if (GetInteger(arg1, 0, &spC, 0) != 0) {
            sprintf(arg0, (s32)lbl_8029D28C, spC);
        }
    }
    return true;
}

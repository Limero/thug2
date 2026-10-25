// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80041F8C-0x80041FDC (80B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void CScreenElement_SetProperties(Unk_1F686599 * arg0, CStruct * arg1);
s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 *arg2, s32 arg3);
void fn_80041F8C(Unk_1F686599 *arg0, CStruct *arg1) {
    GetChecksum_2((void *)arg1, QB_FOCUSABLE_CHILD, (s32 *)((char *)arg0 + (s32)0x190), 0);
    CScreenElement_SetProperties(arg0, arg1);
}

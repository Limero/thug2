// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801992A8-0x8019933C (148B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80129570(s32 arg0, s32 arg1);
void fn_80198190(s32 arg0);
void fn_801980C4(void *);
void fn_80126FF4(void *, void *);
extern char lbl_802AA7A4[];
extern char lbl_802AA7B4[];
extern char lbl_802AA7CC[];
#include "structs.h"
s32 fn_80198278(s32, s32, s32);
bool fn_801992A8(void * arg0, CStruct *arg1) {
    s32 temp_r28;

    fn_80198278(arg0,(s32)lbl_802AA7A4, arg1);
    temp_r28 = arg0 + 4;
    fn_80198278(arg0,(s32)lbl_802AA7B4, arg1);
    fn_80198278(arg0,(s32)lbl_802AA7CC, arg1);
    fn_80126FF4(temp_r28, arg1);
    fn_801980C4(arg0);
    fn_80198190(arg0);
    fn_80129570(temp_r28, 0);
    return true;
}
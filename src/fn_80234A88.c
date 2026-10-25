// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234A88-0x80234AD8 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern void fn_80128CB0(CStruct *, void *, void *, s32);
extern s32 fn_80243EF0(void);
extern void fn_80243CE8(s32, s32, Unk_FFAD6788 *);
extern char lbl_802B0A18[];
bool ScriptFireCustomParkGap(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp8;
    fn_80128CB0(arg0, lbl_802B0A18, &sp8, 1);
    fn_80243CE8(fn_80243EF0(), sp8, arg1);
    return true;
}

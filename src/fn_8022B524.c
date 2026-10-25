// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022B524-0x8022B5D0 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8022B2FC(void *);
void fn_8022B2A8(void *);
void fn_8022B214(void *);
void fn_8021D3F8(void *);
void fn_8000F320(void *);
s32 fn_800145AC();
s32 fn_8000F2F8(s32, s32);
extern s32 lbl_80305FC0;
extern bool lbl_80305FC4;
s32 fn_80219680(CStruct *o);
extern void *lbl_802FFE98;
void fn_8022B524(Unk_31DE137E *arg0, s32 arg1) {
    u32 lim = 0x1388U;
    if (arg1 == 0 && (u32)(fn_800145AC() - lbl_80305FC0) < (u32)lim) {
        return;
    }
    lbl_80305FC0 = fn_800145AC();
    lbl_80305FC4 = 1;
    fn_8000F2F8((s32)lbl_802FFE98, ((Unk_FFAD6788 *)lbl_802FFE98)->unk0x134);
    fn_8022B2A8(arg0);
    fn_8022B2FC(arg0);
    fn_8022B214(arg0);
    if (fn_80219680(arg0) == 0) fn_8021D3F8(arg0);
    fn_8000F320(lbl_802FFE98);
}

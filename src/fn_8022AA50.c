// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022AA50-0x8022AABC (108B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_802FFE98[];
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern s32 Mem_NewZero(s32 arg0);
extern s32 fn_801A44A0(s32 arg0);
extern void fn_8000F320(Unk_F12C5E01 * arg0);

void *fn_8022AA50(Unk_A9157FE7 *arg0) {
    Unk_B0F19D72 *mgr;

    mgr = *(s32 *)lbl_802FFE98;
    fn_8000F2F8((void *)mgr, mgr->unk0x5F8);
    *((s32 *)&arg0->unk0x1C) = fn_801A44A0(Mem_NewZero(0x74));
    mgr = *(s32 *)lbl_802FFE98;
    arg0->unk0x24 = 0;
    *((s32 *)&arg0->unk0x2C) = 0;
    *((s32 *)&arg0->unk0x30) = 0;
    *((s32 *)&arg0->unk0x38) = 0;
    arg0->unk0x40 = 0;
    fn_8000F320((void *)mgr);
    return arg0;
}

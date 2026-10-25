// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018BED8-0x8018BFAC (212B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void CStruct_delete(s32, s32);
void fn_8019094C(s32, void *);
void fn_801907E0(s32, void *);
#include "qb_constants.h"
#include "structs.h"
#include "mem.h"
s32 fn_8018BDB8(s32, s32);
extern char lbl_802A95C0[];
extern char lbl_802A9690[];
void fn_8018BED8(Unk_DB0E2BAB *arg0, s32 arg1) {
    arg0->unk0x14 = (s32)lbl_802A9690;
    fn_801907E0(arg0, QB_DESTROY);
    if ((s32) arg0->unk0x18 != 0) {
        fn_8019094C((s32) arg0->unk0x18, 3);
    }
    if ((s32) arg0->unk0x20 != 0) {
        CStruct_delete((s32) arg0->unk0x20, 3);
    }
    if ((s32) arg0->unk0x24 != 0) {
        CStruct_delete((s32) arg0->unk0x24, 3);
    }
    fn_8018BDB8(arg0, arg0->unk0x2C);
    fn_8018BDB8(arg0, arg0->unk0x30);
    arg0->unk0x14 = (s32)lbl_802A95C0;
    *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x10) + 0xC) =  arg0->unk0xC;
    *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0xC) + 0x10) =  arg0->unk0x10;
    arg0->unk0xC = arg0;
    arg0->unk0x10 = arg0;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}

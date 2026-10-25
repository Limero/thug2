// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A1718-0x801A1778 (96B). Byte-identical.
#include "types.h"
#include "structs.h"
extern f32 lbl_802AB198;
extern char lbl_802AB250[];
extern void fn_800AB0F0(Unk_C8FEE62D *);
extern void fn_8002DCCC(Unk_C8FEE62D *);
void *fn_801A1718(Unk_C8FEE62D *arg0) {
    fn_800AB0F0(arg0);
    arg0->unk0x14 = (s32)lbl_802AB250;
    fn_8002DCCC((char *)arg0 + (s32)0x74);
    *((f32 *)&arg0->unk0x3C) = lbl_802AB198;
    arg0->unk0x70 = 0;
    arg0->unk0x40 = 0;
    arg0->unk0x44 = 0;
    return arg0;
}

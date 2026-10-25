// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007E9E8-0x8007EA5C (116B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern char lbl_80296298[];
s32 Mem_NewZero(s32);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
void fn_8007E9E8(Unk_31DE137E *arg0) {
    Unk_9994C3F5 *p;
    Unk_C8FEE62D *node;

    p = *(void * *)&lbl_802FFE98;
    fn_8000F2F8(p, p->unk0x118);
    node = Mem_NewZero(0x18);
    p = *(void * *)&lbl_802FFE98;
    node->unk0x4 = -1;
    node->unk0x8 = 0;
    node->unk0x14 = (s32)lbl_80296298;
    node->unk0xC = node;
    node->unk0x10 = node;
    arg0->unk0x1C = node;
    fn_8000F320(p);
}

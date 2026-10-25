// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007EA5C-0x8007EAE8 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern Unk_9994C3F5 *lbl_802FFE98;
extern char lbl_802962B0[];
void *Mem_NewZero(s32);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
void fn_8007EA5C(Unk_31DE137E *arg0, s32 arg1) {
    Unk_9994C3F5 *p;
    Unk_C8FEE62D *node;
    Unk_C8FEE62D *prev;

    p = lbl_802FFE98;
    fn_8000F2F8(p, p->unk0x118);
    node = Mem_NewZero(0x18);
    node->unk0xC = node;
    node->unk0x10 = node;
    node->unk0x14 = (s32)lbl_802962B0;
    node->unk0x4 = arg1;
    node->unk0x8 = 0;
    p = lbl_802FFE98;
    prev = arg0->unk0x1C;
    node->unk0x10 = prev->unk0x10;
    node->unk0xC = prev;
    ((Unk_C8FEE62D *)prev->unk0x10)->unk0xC = node;
    prev->unk0x10 = node;
    fn_8000F320(p);
}

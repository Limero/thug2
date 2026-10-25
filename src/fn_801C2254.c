// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C2254-0x801C22E0 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802ABCF0[];
extern char lbl_802ABD38[];
extern char lbl_802AC9E8[];
void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_801C2254(CScript *arg0, s32 arg1) {
    Unk_C8FEE62D *n;
    Unk_C8FEE62D *m;

    n = (s32 *)((char *)arg0 + (s32)0x34);
    arg0->unk0x18 = (s32)lbl_802AC9E8;
    n->unk0x14 = (s32)lbl_802ABD38;
    ((Unk_C7387A53 *)n->unk0x10)->unk0xC = n->unk0xC;
    ((CStruct *)n->unk0xC)->unk0x10 = n->unk0x10;
    n->unk0xC = (s32)n;
    n->unk0x10 = (s32)n;
    m = (s32 *)((char *)arg0 + (s32)0x1C);
    m->unk0x14 = (s32)lbl_802ABCF0;
    ((Unk_C7387A53 *)m->unk0x10)->unk0xC = m->unk0xC;
    ((CStruct *)m->unk0xC)->unk0x10 = m->unk0x10;
    m->unk0xC = (s32)m;
    m->unk0x10 = (s32)m;
    fn_8009F558(arg0, arg1);
}

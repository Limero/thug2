// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C838-0x8009C8A8 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80297880[];
extern char lbl_80297868[];
void *Mem_NewZero(s32);
void *fn_8009C838(Unk_C8FEE62D *arg0) {
    Unk_C8FEE62D *temp_r3;

    arg0->unk0x4 = 0;
    arg0->unk0xC = 0;
    arg0->unk0x14 = (s32)lbl_80297880;
    temp_r3 = Mem_NewZero(0x18);
    temp_r3->unk0x8 = 0;
    temp_r3->unk0x14 = (s32)lbl_80297868;
    temp_r3->unk0x4 = arg0;
    temp_r3->unk0xC = temp_r3;
    temp_r3->unk0x10 = temp_r3;
    arg0->unk0x10 = temp_r3;
    return arg0;
}
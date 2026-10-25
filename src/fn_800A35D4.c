// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A35D4-0x800A3680 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8000A578(s32, s32);
void fn_800A32C0(void);
void *Mem_NewZero(s32);
void fn_80009B04(void *, s32);
void fn_800A329C(void);
extern s32 lbl_80303148;
extern char lbl_80297F38[];
extern char lbl_80297F80[];
extern char lbl_80297FF0[];
void *fn_800A35D4(Unk_C7387A53 *arg0) {
    CScript *temp_r30;
    Unk_C8FEE62D *temp_r9;
    s32 fnp;

    fn_800A32C0();
    temp_r9 = (char *)arg0 + 0x30;
    arg0->unk0x2C = (s32)lbl_80297F38;
    temp_r9->unk0x4 = -1;
    temp_r9->unk0x8 = 0;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    temp_r9->unk0x14 = (s32)lbl_80297FF0;
    temp_r30 = Mem_NewZero(0x24);
    fnp = (s32)fn_800A329C;
    fn_80009B04(temp_r30, 0x3E8);
    temp_r30->unk0x1C = fnp;
    temp_r30->unk0x18 = (s32)lbl_80297F80;
    temp_r30->unk0x20 = arg0;
    arg0->unk0x48 = temp_r30;
    fn_8000A578(lbl_80303148 + 0xA0, temp_r30);
    return arg0;
}

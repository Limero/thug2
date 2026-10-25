// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A1954-0x800A1A08 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800A35D4(void);
void fn_80009B04(void *, s32);
void fn_8000A578(void *, void *);
void fn_80125D54(s32, s32, s32);
void fn_800A1FE8(void);
#include "qb_constants.h"
#include "structs.h"
s32 Mem_NewZero(s32);
extern char lbl_80297CB8[];
extern char lbl_80297D00[];
extern s32 lbl_80303148;
extern char lbl_8039EA60[];
extern char lbl_8039E870[];
void *fn_800A1954(Unk_C7387A53 *arg0) {
    CScript *temp_r30;
    s32 cb;

    fn_800A35D4();
    arg0->unk0x2C = (s32)lbl_80297CB8;
    temp_r30 = Mem_NewZero(0x24);
    cb = (s32)fn_800A1FE8;
    fn_80009B04(temp_r30, -0x384);
    temp_r30->unk0x18 = (s32)lbl_80297D00;
    temp_r30->unk0x1C = cb;
    temp_r30->unk0x20 = arg0;
    arg0->unk0x4C = temp_r30;
    fn_8000A578(*(s32 *)&lbl_80303148 + 8, temp_r30);
    fn_80125D54(QB_OBJECT, (s32)lbl_8039EA60, 0x10);
    fn_80125D54(QB_COMPOSITEOBJECT, (s32)lbl_8039E870, 0x10);
    return arg0;
}

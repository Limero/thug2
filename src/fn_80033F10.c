// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033F10-0x80033FA0 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80291C5C;
extern char lbl_80291D20[];
extern void fn_80033538(void);
extern s32 fn_8005525C(void);
extern s32 fn_8006FB50(Unk_5E1C040A *, s32);
extern s32 fn_800335E0(CStruct *);
extern s32 GetChecksum_3(Unk_6A70655D *, void *);
extern s32 fn_800CBDE0(void);
void *fn_80033F10(Unk_DB0E2BAB *arg0) {
    f32 temp_f0;

    fn_80033538();
    temp_f0 = lbl_80291C5C;
    arg0->unk0x14 = (s32) lbl_80291D20;
    *((f32 *)&arg0->unk0x2C) = temp_f0;
    *((f32 *)&arg0->unk0x18) = temp_f0;
    *((f32 *)&arg0->unk0x1C) = temp_f0;
    *((f32 *)&arg0->unk0x20) = temp_f0;
    *((f32 *)&arg0->unk0x24) = temp_f0;
    *((f32 *)&arg0->unk0x28) = temp_f0;
    arg0->unk0x30 = fn_8005525C();
    arg0->unk0x34 = fn_8006FB50((Unk_5E1C040A *)arg0->unk0x30, 0);
    GetChecksum_3((Unk_6A70655D *)fn_800335E0((CStruct *)arg0), (void *)QB_ANIMBLENDER);
    arg0->unk0x38 = fn_800CBDE0();
    return arg0;
}
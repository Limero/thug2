// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80024100-0x800241E8 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_802912A4[];
extern char lbl_802912A8[];
#include "structs.h"
s32 CObject_AddRefLink(s32, s32);
void CObject_RemoveRefLink(CStruct *, CStruct *);
extern char lbl_802912B0[];

typedef struct F9C4L F9C4L;

/* true layout of the touched region of Unk_DB0E2BAB for THIS function */
struct F9C4L {
    s32 unk0x0;
    f32 unk0x4;
    f32 unk0x8;
    f32 unk0xC;
    f32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    s32 unk0x20;
    s32 unk0x24;
};

void *fn_80024100(Unk_DB0E2BAB *arg0, CStruct *arg1, CStruct *arg2) {
    F9C4L *a;
    f32 temp_f0;
    f32 temp_f13;
    CStruct *temp_r11;
    void *temp_r30;

    a = (F9C4L *)arg0;
    temp_f13 = *(f32 *)lbl_802912A4;
    temp_f0 = *(f32 *)lbl_802912A8;
    a->unk0x24 = (s32)lbl_802912B0;
    temp_r11 = (char *)arg0 + 0x18;
    a->unk0x4 = temp_f13;
    a->unk0x8 = temp_f13;
    a->unk0xC = temp_f0;
    a->unk0x10 = temp_f0;
    a->unk0x14 = 0;
    temp_r11->unk0x4 = 0;
    temp_r11->unk0x8 = 0;
    a->unk0x18 = 0;
    if (arg1 != NULL) {
        a->unk0x4 = *((f32 *)&arg1->unk0x4);
        a->unk0x8 = *((f32 *)&arg1->unk0x8);
        a->unk0xC = *((f32 *)&arg1->unk0xC);
        a->unk0x10 = *((f32 *)&arg1->unk0x10);
    } else {
        a->unk0x4 = temp_f13;
        a->unk0xC = temp_f0;
        a->unk0x8 = temp_f13;
        a->unk0x10 = temp_f0;
    }
    temp_r30 = (char *)arg0 + 0x18;
    if ((s32) a->unk0x18 != 0) {
        CObject_RemoveRefLink(*(s32 *)((char *)temp_r30), temp_r30);
        a->unk0x18 = 0;
    }
    a->unk0x18 = arg2;
    if (arg2 != 0) {
        CObject_AddRefLink(arg2, temp_r30);
    }
    return arg0;
}

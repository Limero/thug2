// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018B90C-0x8018B9D4 (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void GetInteger(void *, void *, void *, void *);
void fn_8018FC80(void *);
void fn_801907E0(void *, void *);
void fn_80190764(void *);
#include "qb_constants.h"
#include "structs.h"
s32 fn_8000F2F8(s32, s32);
extern char lbl_802FFE98[];
void fn_8000F320(Unk_F12C5E01 *self);
s32 fn_80128978(s32 arg0, s32 arg1);
void fn_8018B90C(Unk_C7387A53 *arg0) {
    s32 sp8;
    Unk_9994C3F5 *temp_r3;

    temp_r3 = *(void * *)&lbl_802FFE98;
    fn_8000F2F8(temp_r3, temp_r3->unk0x11C);
    fn_80190764(arg0);
    fn_801907E0(arg0, QB_INIT);
    fn_8018FC80(arg0);
    sp8 = 0;
    arg0->unk0x70 = (s32) (arg0->unk0x70 | 0x80000000);
    GetInteger(arg0->unk0x20, QB_UNLIMITED_TIME, &sp8, 0);
    if (sp8 != 0) {
        arg0->unk0x70 = (s32) (arg0->unk0x70 | 0x80000);
    }
    if (fn_80128978(arg0->unk0x20, QB_DONT_DEACTIVATE_UPON_EXPIRATION) != 0) {
        arg0->unk0x70 = (s32) (arg0->unk0x70 & QB_UNKNOWN_0xFDFFFFFF);
    }
    fn_8000F320(*(void * *)&lbl_802FFE98);
}
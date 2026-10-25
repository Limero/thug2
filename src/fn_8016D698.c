// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016D698-0x8016D920 (648B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8016F120(void *, void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(void *, void *, void *, void *);
void GetChecksum_2(void *, s32, void *, s32);
void CStruct_dtor(void *);
s32 fn_80126FF4(void *, void *);
s32 GetStructure_2(s32, s32, s32, s32);
s32 ContainsFlag(CStruct *arg0, s32 arg1);
void fn_8016D698(Unk_71062261 *arg0, CStruct *arg1) {
    s32 spC;
    s32 sp8;
    u32 temp_r9;
    register s32 var_r11 __asm__("r11");
    char *b154;
    char *b15C;
    char *b160;
    char *b198;
    char *b15C2;
    char *b160h;
    s32 temp_r3;

    arg0->unk0x35C = 1;
    b154 = (char *)arg0 + 0x154;
    GetInteger(arg1, QB_SYSTEM, &sp8, 1);
    sp8 = sp8 - 1;
    CStruct_dtor(*(s32 *)(b154 + (sp8 * 0x190)));
    fn_80126FF4(*(s32 *)(b154 + (sp8 * 0x190)), arg1);
    GetChecksum_2(arg1, QB_CURRENT_STATE, (char *)arg0 + ((sp8 * 0x190) + 0xC) + 0x150, 0);
    b15C = (char *)arg0 + 0x15C;
    temp_r9 = *(u32 *)(b15C + (sp8 * 0x190));
    switch (temp_r9) {
    case QB_MORNING:
        var_r11 = QB_AFTERNOON;
        break;
    case QB_AFTERNOON:
        var_r11 = QB_EVENING;
        break;
    case QB_EVENING:
        var_r11 = QB_NIGHT;
        break;
    case QB_NIGHT:
        var_r11 = QB_MORNING;
        break;
    default:
        var_r11 = 0;
        break;
    }
    b160 = (char *)arg0 + 0x160;
    *(s32 *)(b160 + (sp8 * 0x190)) = var_r11;
    if (GetStructure_2(arg1, QB_OVERWRITE_CURRENT_STATE, &spC, 0) != 0) {
        fn_8016F120(arg0, spC, (char *)arg0 + ((sp8 * 0x190) + 0xC));
    } else if (GetStructure_2(arg1, *(u32 *)((b15C2 = (char *)arg0 + 0x15C) + (sp8 * 0x190)), &spC, 0) != 0) {
        fn_8016F120(arg0, spC, (char *)arg0 + ((sp8 * 0x190) + 0xC));
        GetInteger(spC, QB_STATE_LENGTH, (char *)arg0 + ((sp8 * 0x190) + 0xC) + 0x17C, 1);
    }
    b160h = (char *)arg0 + 0x160;
    if (GetStructure_2(arg1, *(u32 *)(b160h + (sp8 * 0x190)), &spC, 0) != 0) {
        fn_8016F120(arg0, spC, (char *)arg0 + ((sp8 * 0x190) + 0xC) + 0xA4);
    }
    GetInteger(arg1, QB_TRANSITION_LENGTH, (char *)arg0 + ((sp8 * 0x190) + 0xC) + 0x178, 0);
    temp_r3 = ContainsFlag(arg1, QB_SKY);
    b198 = (char *)arg0 + 0x198;
    *(s32 *)(b198 + (sp8 * 0x190)) = temp_r3;
}

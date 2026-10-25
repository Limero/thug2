// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80209514-0x802096A0 (396B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_80128978(s32, s32);
void fn_802023C4(Unk_59E38960 *, s32);
void fn_801F0E84(CScript *);
s32 fn_8009F204(Unk_C8FEE62D *, void *, Unk_C8FEE62D *);
void AddChecksum(CStruct *, s32, s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
s32 fn_801309EC(Unk_DB0E2BAB *);
s32 fn_8020C500(Unk_90685748 *);

bool fn_80209514(Unk_183EC3C4 *arg0, CStruct *arg1, s32 arg2, CStruct *arg3) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 temp_r9;
    s32 temp_r0;
    Unk_C8FEE62D *temp_r31;

    sp8 = 0;
    GetChecksum_2(arg1, QB_SCR, &sp8, 0);
    if (sp8 == QB_GRIND) {
        temp_r9 = arg0->unk0x2C;
        __asm__ volatile(
            "lwz %1, 0x25c(%1)\n\t"
            "cmpwi %1, 0\n\t"
            "li %0, 0\n\t"
            "beq 1f\n\t"
            "lwz %0, 0x54(%1)\n"
            "1:"
            : "=r"(temp_r0), "+b"(temp_r9));
        if (temp_r0 == 0) {
            goto ret0;
        }
    }
    if ((GetStructure_2(arg1, QB_PARAMS, &spC, 0) != 0) && (fn_80128978(spC, QB_ISEXTRA) == 0)) {
        fn_802023C4(arg0->unk0x38, sp8);
    }
    if (sp8 == 0) {
        goto ret0;
    }
    (arg0->unk0x1C) += 1;
    arg0->unk0x12AC = 0;
    arg0->unk0x12F4 = 0;
    arg0->unk0x1278 = 0;
    sp10 = 0;
    GetStructure_2(arg1, QB_PARAMS, &sp10, 0);
    fn_801F0E84(arg0->unk0x30);
    temp_r31 = arg0->unk0xC;
    fn_8009F204(temp_r31, (void *)sp8, (void *)sp10);
    if (arg2 != 0) {
        AddChecksum(*(s32 *)((char *)(temp_r31->unk0x14) + 0x18), 0, arg2);
    }
    fn_80126FF4(*(s32 *)((char *)(temp_r31->unk0x14) + 0x18), arg3);
    fn_801309EC(temp_r31->unk0x14);
    *(s32 *)((char *)(arg0->unk0x34) + 0x144) = 1;
    fn_8020C500(arg0);
    (arg0->unk0x1C) -= 1;
    return true;
ret0:
    return false;
}

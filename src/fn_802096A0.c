// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802096A0-0x8020989C (508B). Byte-identical.
// extra_cflags: -fno-gcse
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_802092E0(Unk_CF8B1206 * arg0);
void fn_8009F190(Unk_C8FEE62D * arg0);
void fn_8012F8E8(Unk_FFAD6788 * arg0, s32 arg1, CStruct * arg2);
s32 fn_801259C8(s32, s32);
s32 fn_80129528(CStruct *, s32);
s32 fn_80209514(Unk_183EC3C4 * arg0, CStruct * arg1, s32 arg2, CStruct * arg3);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 AddInteger(CStruct *, s32, s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void fn_8009F204(Unk_C8FEE62D * arg0, void *arg1, Unk_C8FEE62D * arg2);
s32 CStruct_delete(CStruct *, s32);
void fn_801309EC(Unk_DB0E2BAB * arg0);
void fn_8020C500(Unk_90685748 * arg0);
s32 GetStructure(s32, s32);
s32 Game_GetGoalManager();
s32 fn_801880EC(Unk_C7387A53 *, CStruct *);
void fn_802096A0(Unk_1DFFEF1A *arg0, s32 arg1, CStruct *arg2, CStruct *arg3) {
    register s32 a1 __asm__("r28");
    s32 sp8;
    s32 spC;
    s32 sp10;
    register s32 temp_r29 __asm__("r29");
    s32 temp_r31;
    s32 entry;
    s32 temp_ret;
    s32 ret228;
    s32 newEntry;
    Unk_C8FEE62D *temp_ptr;
    s32 var_one;

    a1 = arg1;
    *(s32 *)(arg0->unk0x34 + 0x144) = 0;
    arg0->unk0xA68 = 0;
    if ((arg0->unk0xA70) == -1) {
        return;
    }
    __asm__("li %0,1" : "=r"(var_one));
again:;
    {
        register char *b0 __asm__("r11") = (char *)arg0 + 0xA78;
        register char *b4 __asm__("r10") = (char *)arg0 + 0xA7C;
        char *bA = (char *)arg0 + 0xA88;
        register s32 idxv __asm__("r9");
        idxv = arg0->unk0xA70;
        idxv *= 0x14;
        temp_r31 = *(s32 *)(b0 + idxv);
        temp_r29 = *(s32 *)(b4 + idxv);
        arg0->unk0xA68 = *(s32 *)(bA + idxv);
        fn_802092E0(arg0);
        if (temp_r31 != 0) {
            if (arg1 != 0) {
                fn_8009F190(arg0->unk0xC);
                fn_8012F8E8(*(s32 *)(arg0->unk0xC + 0x14), arg1, arg2);
            }
            entry = fn_80129528(fn_801259C8(temp_r31, 0), temp_r29);
            temp_ret = fn_80209514(arg0, entry, 0, arg3);
            if (temp_ret != 0) {
                return;
            }
            sp8 = temp_ret;
            GetChecksum_2(entry, QB_TRICKSLOT, &sp8, 0);
            if (sp8 == 0) {
                return;
            }
            spC = temp_ret;
            ret228 = GetInteger(arg0->unk0xA6C, sp8, &spC, 0);
            if (ret228 != 0) {
                temp_r31 = CStruct_ctor(CStruct_new(8));
                AddInteger(temp_r31, QB_TRICK_INDEX, spC);
                fn_80126FF4(temp_r31, arg3);
                temp_ptr = arg0->unk0xC;
                fn_8009F204(temp_ptr, QB_CREATEATRICK, temp_r31);
                if (temp_r31 != 0) {
                    CStruct_delete(temp_r31, 3);
                }
                fn_801309EC(temp_ptr->unk0x14);
                *(s32 *)(arg0->unk0x34 + 0x144) = var_one;
                fn_8020C500(arg0);
                return;
            }
            sp10 = ret228;
            GetChecksum_2(arg0->unk0xA6C, sp8, &sp10, 0);
            if (sp10 == 0) {
                return;
            }
            newEntry = GetStructure(sp10, 0);
            if (newEntry == 0) {
                return;
            }
            fn_801880EC(Game_GetGoalManager(), newEntry);
            fn_80209514(arg0, newEntry, 0, arg3);
            return;
        }
        if (arg0->unk0xA70 == -1) {
            return;
        }
        goto again;
    }
}

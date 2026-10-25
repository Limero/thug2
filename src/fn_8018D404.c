// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018D404-0x8018D5D4 (464B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A9628[];
extern char lbl_802A962C[];
extern s32 lbl_80305EAC;
extern s32 GetArray(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetString(CStruct * arg0, s32 * arg1, s32 * arg2, s32 arg3);
extern s32 fn_801745B4(s32 arg0);
extern s32 fn_801403CC(void * arg0);
extern s32 Script_GenerateCRC(void *arg0);
extern s32 fn_8000A7F8(void * arg0, u8 * arg1);
extern s32 fn_80182150(Unk_FFAD6788 * arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 fn_801293FC(CStruct * arg0, s32 arg1);
s32 sprintf(s32 arg0, ...);

bool fn_8018D404(Unk_C8FEE62D *arg0, s32 arg1) {
    u8 sp8[0x18];
    void *sp20;
    u8 *sp24;
    register void *p __asm__("r9");
    register void *arg __asm__("r3");
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r3;
    u32 temp_r0;
    u32 var_r30;
    void *temp_r29_2;
    char *temp_r30_2;
    Unk_4C649A8C *temp_r30_3;

    sp20 = NULL;
    if (GetArray(arg0->unk0x20, QB_REQUIRED_GAPS, &sp20, 0) == 0) {
        return false;
    }
    sp24 = (u8 *)lbl_802A9628;
    GetString(arg0->unk0x20, QB_REQUIRED_TRICK_NAME, &sp24, 0);
    if ((s32)*sp24 == 0) {
        goto block_11;
    }
    temp_r3 = fn_801745B4(*(s32 *)&lbl_80305EAC);
    if (temp_r3 == 0) {
        return false;
    }
    temp_r29 = fn_801403CC(temp_r3);
    temp_r30 = Script_GenerateCRC(sp24);
    temp_r31 = fn_8000A7F8(QB_BS_, sp24);
    temp_r28 = fn_8000A7F8(QB_FS_, sp24);
    if ((fn_80182150(temp_r29, temp_r30, 0, 0, 1) != 0) || (fn_80182150(temp_r29, temp_r31, 0, 0, 1) != 0) || (fn_80182150(temp_r29, temp_r28, 0, 0, 1) != 0)) {
        goto block_11;
    }
    return false;
block_11:
    p = sp20;
    for (var_r30 = 0; (temp_r0 = *((u32 *)&((CStruct *)p)->unk0x4)), ((arg = p), var_r30 < temp_r0); ) {
        if (arg1 == fn_801293FC(arg, var_r30)) {
            sprintf((s32)&sp8, (s32)lbl_802A962C, var_r30 + 1);
            temp_r30_2 = (char *)arg0->unk0x14;
            temp_r30_3 = temp_r30_2 + 0xA0;
            temp_r29_2 = (void *)((char *)arg0 + ((Unk_BC571107 *)temp_r30_2)->unk0xA0);
            ((s32 (*)(void *, void *, s32, s32))temp_r30_3->unk0x4)(temp_r29_2, (void *)Script_GenerateCRC(&sp8), 1, 0);
            return true;
        }
        p = sp20;
        var_r30++;
    }
    return false;
}

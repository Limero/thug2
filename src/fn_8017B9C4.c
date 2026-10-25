// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017B9C4-0x8017BB28 (356B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

extern s32 lbl_802FFE98;
extern s32 lbl_80305EC0;
extern s32 lbl_80305F1C;
extern char lbl_802A90BC[];

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
} Obj_801292A8;

typedef struct {
    char pad0x0[2];
    s8 unk0x2;
    char pad0x3;
    volatile s32 unk0x4;
    s32 unk0x8;
} A129068;

s32 IsTrue(s32, s32);
void fn_8000F2F8(void *, void *);
void fn_8000F320(void *);
s32 CStruct_new(s32);
s32 CStruct_ctor(void);
void CStruct_delete(void *, s32);
void fn_8003E7CC(s32);
s32 fn_80128F94(void);
void fn_80129068(A129068 *, s32, s8);
void fn_801292A8(Obj_801292A8 *, s32, s32);
s32 fn_801A96B8(s32, u8);
void fn_801A977C(void *, void *);
void fn_801A97C4(void *);
s32 Script_GenerateCRC(s32);
s32 fn_80127F40(s32, s32, s32);

s32 fn_8017B9C4(u8 **arg0) {
    s32 sp8[8];
    s32 temp_r25;
    s32 temp_r26;
    s32 temp_r30;
    register s32 var_r29 __asm__("r29");
    s32 var_r31;
    u8 temp_r4;
    register u8 *var_r28 __asm__("r28");
    register u8 *temp_r27 __asm__("r27");

    temp_r27 = *arg0;
    if (IsTrue(lbl_80305EC0, QB_SHOULD_MODULATE_COLOR) == 0) {
        return 4;
    }
    var_r28 = temp_r27 + 8;
    temp_r25 = lbl_80305F1C;
    var_r29 = 0;
    fn_8000F2F8((void *)lbl_802FFE98, *(s32 *)((char *)lbl_802FFE98 + 0x12C));
    CStruct_new(8);
    temp_r26 = CStruct_ctor();
    do {
        if (temp_r27[var_r29] != 0) {
            var_r31 = 0;
            fn_8003E7CC(0xC);
            temp_r30 = fn_80128F94();
            fn_80129068(temp_r30, temp_r27[var_r29], 0xD);
            while (var_r31 < (s32)temp_r27[var_r29]) {
                temp_r4 = *var_r28;
                var_r28 += 1;
                fn_801292A8(temp_r30, var_r31, fn_801A96B8(temp_r25, temp_r4));
                var_r31 += 1;
            }
            sprintf(sp8, lbl_802A90BC, var_r29);
            fn_80127F40(temp_r26, Script_GenerateCRC(sp8), temp_r30);
        }
        var_r29 += 1;
    } while (var_r29 <= 7);
    fn_801A977C(temp_r25, temp_r26);
    fn_801A97C4(temp_r25);
    if (temp_r26 != 0) {
        CStruct_delete(temp_r26, 3);
    }
    fn_8000F320((void *)lbl_802FFE98);
    return 1;
}

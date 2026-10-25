// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80199968-0x80199AE4 (380B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
typedef struct Node {
    char pad0x4[0x4];
    s32 unk0x4;
    char pad0x8[0x4];
    struct Node *unk0xC;
} Node;

typedef struct Owner {
    char pad0x38[0x38];
    Node *unk0x38;
} Owner;

typedef struct FnTbl {
    char pad0xB0[0xB0];
    s16 off0xB0;
    s32 (*fn0xB4)(void *, s32);
} FnTbl;

typedef struct Sub {
    char pad0x0[0x0];
    s32 unk0x0;
} Sub;

typedef struct Elem {
    char pad0x14[0x14];
    FnTbl *unk0x14;
    char pad0x18[0x18];
    Sub *unk0x30;
} Elem;

typedef struct Script {
    char pad0x18[0x18];
    s32 unk0x18;
} Script;

extern s32 lbl_80305EAC;
extern s32 lbl_80305F9C;
extern s32 lbl_80305EC0;
extern s32 Game_GetGoalManager(void);
extern s32 fn_80198B10(s32);
extern s32 fn_80198B68(s32);
extern s32 fn_80184248(void *);
extern s32 fn_80228720(s32, s32);
extern s32 fn_80184168(void *);
extern void *fn_801746A4(Owner *, s32);
extern Elem *fn_80183A64(void *, s32);
extern s32 fn_8018E3B8(void *);

bool fn_80199968(s32 arg0) {
    Owner *temp_r24;
    register void *temp_r25 __asm__("r25");
    s32 temp_r29;
    s32 temp_r30;
    register s32 var_r26 __asm__("r26");
    s32 var_r31;
    register u32 temp_r27 __asm__("r27");
    u32 var_r11;
    u32 var_r28;
    u32 var_r30;
    Node *var_r9;
    Elem *temp_r3;
    FnTbl *temp_r9;
    register Script *temp_r29_2 __asm__("r29");
    register char *base __asm__("r23");

    temp_r24 = (Owner *)lbl_80305EAC;
    temp_r29 = lbl_80305F9C;
    temp_r25 = (void *)Game_GetGoalManager();
    if (fn_80198B10(lbl_80305EC0) != 0) {
        var_r31 = 0;
        temp_r30 = fn_80184248(temp_r25);
        __asm__("" : "+r"(temp_r30));
        while (var_r31 < fn_80198B68(lbl_80305EC0)) {
            if (fn_80228720(temp_r29, var_r31) >= temp_r30) {
                return true;
            }
            var_r31 += 1;
        }
        return false;
    }
    var_r28 = 0U;
    temp_r27 = (u32)fn_80184168(temp_r25);
    base = (char *)temp_r24 + 0x2C;
loop_7:
    var_r9 = *(Node **)(base + 0xC);
    var_r11 = 0U;
    goto test_9;
loop_9:
    var_r9 = var_r9->unk0xC;
    var_r11 += 1;
test_9:
    if ((s32)var_r9->unk0x4 == -1) {
        var_r9 = NULL;
    }
    if (var_r9 != NULL) {
        goto loop_9;
    }
    if (var_r28 < var_r11) {
        temp_r29_2 = (Script *)fn_801746A4(temp_r24, var_r28);
        var_r30 = 0U;
        var_r26 = 1;
        if (var_r30 >= temp_r27) {
            goto after_14;
        }
    loop_14:
        temp_r3 = fn_80183A64(temp_r25, var_r30);
        if (temp_r3->unk0x30->unk0x0 == 0 && fn_8018E3B8(temp_r3) != 0) {
            temp_r9 = temp_r3->unk0x14;
            if (temp_r9->fn0xB4((char *)temp_r3 + temp_r9->off0xB0, temp_r29_2->unk0x18) == 0) {
                goto flag0;
            }
        }
        var_r30 += 1;
        if (var_r30 < temp_r27) {
            goto loop_14;
        }
        goto after_14;
    after_14:
        if (var_r26 != 0) {
            return true;
        }
        goto cont_7;
    flag0:
        var_r26 = 0;
        goto after_14;
    cont_7:
        var_r28 += 1;
        goto loop_7;
    }
    return false;
}

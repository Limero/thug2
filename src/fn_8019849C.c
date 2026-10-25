// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019849C-0x8019868C (496B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

// The vtable reached through item->unk0x4.  Want reads the method offsets
// with lha (+0x18/+0x20) and the function pointers with lwz (+0x1C/+0x24),
// so the offsets are s16.  The corpus-voted CScript types both as s32, which
// emits lwz — a file-local typedef is the whole fix (no header edit).
typedef struct {
    char pad0x18[0x18];
    s16 off0x18;
    char pad0x1A[2];
    void (*fn0x1C)(void *);
    s16 off0x20;
    char pad0x22[2];
    void (*fn0x24)(void *);
} VT_8019849C;

s32 fn_80128C80(s32, s32, s32, s32);
s32 fn_8019868C(s32);
s32 Game_GetGoalManager(void);
s32 fn_80184170(s32, s32);
s32 fn_80183A94(s32);
s32 fn_8018D118(s32);

bool fn_8019849C(s32 arg0) {
    s32 sp8;
    s32 temp_r0;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r3;
    s32 var_r27;
    s32 var_r31;
    s32 var_r3;
    u32 var_r10;
    u32 var_r11;
    u32 var_r11_2;
    Unk_C7387A53 *temp_r28_2;
    /* Want homes the arg0+0xC container in r28 and n_ok in r27; GCC's
     * local hard-reg pool hands them out the other way round. */
    register s32 pin28 __asm__("r28");
    void *temp_r3_2;
    void *temp_r3_3;
    VT_8019849C *temp_r9;
    /* The indirect call's argument (item + s16 offset) must be built in the
     * call's own argument register r3; left free, the offset takes r3 and
     * the item falls into a scratch. */
    register s32 p_item __asm__("r3");
    CStruct *var_r30;
    CStruct *var_r9;
    CStruct *var_r9_2;

    temp_r28 = arg0 + 4;
    sp8 = 0;
    fn_80128C80(temp_r28, QB_IS_ELIMISKATE, (s32 *)&sp8, 0);
    temp_r0 = sp8;
    temp_r29 = temp_r0 ^ 1;
    temp_r29 = (temp_r29 == 0);
    /* Zero-code barrier: keeps the subfic/adde fold in front of the second
     * call's argument setup (ori / li r6).  5 words, no emitted insn. */
    __asm__("" : "+r"(temp_r29));
    sp8 = 0;
    fn_80128C80(temp_r28, QB_IS_SCAVENGER_HUNT, (s32 *)&sp8, 0);
    temp_r30 = sp8 ^ 1;
    temp_r30 = (temp_r30 == 0);
    if ((fn_8019868C(arg0) != 0) && (temp_r29 == 0) && (temp_r30 == 0)) {
        temp_r30_2 = Game_GetGoalManager();
        if (fn_80184170(temp_r30_2, 1) > 0) {
            temp_r3 = fn_80183A94(temp_r30_2);
            if ((temp_r3 != 0) && (fn_8018D118(temp_r3) <= 0)) {
                return true;
            }
        }
    }
    pin28 = (s32)(arg0 + 0xC);
    temp_r28_2 = (Unk_C7387A53 *)pin28;
    var_r27 = 0;
    var_r31 = 0;
    var_r10 = 0U;
loop_8:
    var_r9 = (CStruct *)(*(s32 *)(pin28 + 0xC));
    var_r11 = 0U;
    goto chk_10;
bdy_10:
    var_r9 = (CStruct *)var_r9->unk0xC;
    var_r11 += 1;
chk_10:
    if ((s32) var_r9->unk0x4 == -1) {
        var_r9 = NULL;
    }
    if (var_r9 != NULL) {
        goto bdy_10;
    }
    if (var_r10 < var_r11) {
        var_r9_2 = (CStruct *)(*(s32 *)(pin28 + 0xC));
        var_r11_2 = var_r10;
        if ((s32) var_r9_2->unk0x4 == -1) {
            var_r9_2 = NULL;
        }
        temp_r29 = var_r10 + 1;
loop_17:
        if (var_r9_2 != NULL) {
            if (0 == var_r11_2--) {
                goto found_17;
            }
            var_r9_2 = (CStruct *)var_r9_2->unk0xC;
            if ((s32) var_r9_2->unk0x4 == -1) {
                var_r9_2 = NULL;
            }
            goto loop_17;
        } else {
            var_r30 = NULL;
        }
body_17:
        p_item = (s32)var_r30->unk0x4;
        temp_r9 = ((CStruct *)p_item)->unk0x4;
        if (((s32 (*)(void *))temp_r9->fn0x1C)((s32)p_item + temp_r9->off0x18) != 0) {
            p_item = (s32)var_r30->unk0x4;
            var_r31 += 1;
            temp_r9 = ((CStruct *)p_item)->unk0x4;
            if (((s32 (*)(void *))temp_r9->fn0x24)((s32)p_item + temp_r9->off0x20) != 0) {
                var_r27 += 1;
            }
        }
        var_r10 = temp_r29;
        goto loop_8;
found_17:
        var_r30 = var_r9_2;
        goto body_17;
    }
    if (var_r31 != 0) {
        if (var_r27 == var_r31) {
            return true;
        }
    }
    return false;
}

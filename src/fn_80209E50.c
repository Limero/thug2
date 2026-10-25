// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80209E50-0x80209FF0 (416B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Bitmask-driven script/event dispatcher: walks the entries of a lookup
// table (fn_801259C8 / count at +4), skipping slots masked out by arg2,
// and for each active slot runs the associated handlers
// (fn_802093E8, fn_80206D2C, fn_80206DE4, fn_80207990, fn_80209514) and
// the message-registration helpers (GetChecksum_2, GetStructure). Returns 1
// once any handler path succeeded; the +0x130C flag short-circuits the
// remaining slots. Suggested rename: ProcessSlotMaskedEvents / DispatchMaskedHandlers.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void *fn_801259C8(s32 arg0, s32 arg1);
extern s32 fn_80129528(CStruct * arg0, s32 arg1);
extern s32 fn_802093E8(Unk_59E38960 * arg0, CStruct * arg1);
extern s32 fn_80206D2C(void *arg0, s32 arg1);
extern s32 fn_80206DE4(void *arg0, CStruct * arg1);
extern s32 fn_80207990(void *arg0, CStruct * arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 fn_80209514(Unk_183EC3C4 * arg0, CStruct * arg1, s32 arg2, CStruct * arg3);
extern void GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern s32 GetStructure(s32 arg0, s32 arg1);

s32 fn_80209E50(Unk_BBA0A5F0 *arg0, s32 arg1, s32 arg2) {
    s32 spC;
    s32 sp8;
    s32 temp_r25;
    s32 temp_r29;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r30;
    s32 temp_r31;

    s32 var_r27;
    CStruct *temp_r24;
    u32 mask;
    register s32 var_r26 __asm__("r26");

    var_r26 = 0;
    temp_r24 = fn_801259C8(arg1, 0);
    if (temp_r24 != NULL) {
        temp_r25 = temp_r24->unk0x4;
        var_r27 = 0;
        if (var_r26 < temp_r25) {
            do {
                mask = 1U << var_r27;
                if (!(arg2 & mask)) {
                    temp_r31 = fn_80129528(temp_r24, var_r27);
                    if (fn_802093E8(arg0, temp_r31) != 0) {
                        temp_r30 = fn_80206D2C(arg0, temp_r31);
                        temp_r29 = fn_80206DE4(arg0, temp_r31);
                        if ((fn_80207990(arg0, temp_r30, 2, -5, 0) != 0) || (fn_80207990(arg0, temp_r29, 2, -5, 0) != 0)) {
                            temp_r3_3 = fn_80209514(arg0, temp_r31, QB_ISEXTRA, 0);
                            if (temp_r3_3 != 0) {
                                var_r26 = 1;
                            } else {
                                sp8 = temp_r3_3;
                                GetChecksum_2(temp_r31, (s32)QB_TRICKSLOT, &sp8, 0);
                                if (sp8 != 0) {
                                    spC = temp_r3_3;
                                    GetChecksum_2(arg0->unk0xA6C, sp8, &spC, 0);
                                    if (spC != 0) {
                                        temp_r3_4 = GetStructure(spC, 0);
                                        if (temp_r3_4 != 0) {
                                            if (fn_80209514(arg0, temp_r3_4, QB_ISEXTRA, 0) != 0) {
                                                var_r26 = 1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if ((s32) arg0->unk0x130C == 0) {
                            return var_r26;
                        }
                    }
                }
                var_r27 += 1;
            } while (var_r27 < temp_r25);
        }
    }
    return var_r26;
}

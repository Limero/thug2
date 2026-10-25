// WIP DRAFT (concrete attempt;)
// family=m2c range=0x801168CC-0x80116CFC size=1072B
// PARKED: large format-text candidate scored 10.6%; byte parser, vararg formatting, and global object ABI remain unresolved.
// FIXED 2026-09-13: the PrintThousands call passes 4 args; it now uses a separate
// 4-arg prototype (fn_80009628_4). REL24 targets are relocation-masked, so the
// name is free. Draft now COMPILES (was a bare FAIL).
// The call below passes four arguments (m2c emitted the extra set); the branch
// target is relocation-masked, so a distinct 4-arg prototype compiles the same
// instruction stream.
// UPDATED 2026-09-15 (e): 9.3% -> 9.9%. raw address literal -> registered lbl_ symbol: MWCC emits lis+ori for a literal constant but lis+addi for a symbol address. tools/raw_sym_scan.py automated the A/B; keep the best body.
// UPDATED 2026-09-15 (f): 9.9% -> 10.7% by DELETING the recorded `FLAG: -fno-rerun-cse-after-loop` line.  A FLAG line is a cached decision taken against an older body (doc 55); tools/flagdrop_scan.py A/Bs the header flags against the default and this one is now a regressor.
#include "types.h"
extern char lbl_8029D1C4[];
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(s32, s32, s32, s32);
static s32 spC0;

char* PrintThousands(s32 arg0, char arg1);
char* fn_80009628_4(s32 arg0, s32 arg1, f32 arg2, char arg3);

s32 fn_801168CC(CStruct *arg0, CStruct *arg1) {
    f32 spC8;
    s32 spC4;
    u8 *spC0;
    s32 spBC;
    s32 spB8;
    u8 spA8;
    u8 sp40;
    u8 sp9;
    u8 sp8;
    f32 temp_r9_3;
    f32 temp_r9_4;
    f32 var_r3;
    s32 temp_r0_2;
    s32 temp_r3_2;
    s32 var_r23;
    s32 var_r30;
    u8 *temp_r31;
    u8 *var_r11;
    u8 *var_r29;
    u8 *var_r31;
    u8 *var_r4;
    u8 temp_r0;
    u8 temp_r9;
    u8 temp_r9_2;
    u8 var_r0;
    u8 var_r0_2;
    u8 var_r0_3;
    CStruct *temp_r3;

    spB8 = 0;
    var_r23 = 1;
    GetChecksum_2(arg1, QB_TEXTNAME, &spB8, 0);
    spBC = 0;
    GetChecksum_2(arg1, QB_CHECKSUMNAME, &spBC, 0);
    spC0 = (u8 *)lbl_8029D1C4;
    if (GetString(arg1, 0, &spC0, 0) == 0) {
        goto block_1;
    }
    var_r31 = spC0;
    var_r29 = (u8 *)0x80383248;
    var_r0 = *((s32 *)var_r31);
    if ((s32) var_r0 != 0) {
loop_4:
        if (((s32) var_r0 == 0x5C) && ((s32) *(s32 *)((char *)var_r31 + (s32)0x1) == 0x25)) {
            var_r0_2 = *(s32 *)((char *)var_r31 + (s32)0x1);
            var_r31 += 1;
            goto block_44;
        }
        var_r0_2 = ((Unk_9F066EC1 *)var_r31)->unk0x0;
        if ((s32) var_r0_2 == 0x25) {
            temp_r0 = *(s32 *)((char *)var_r31 + (s32)0x1);
            temp_r31 = var_r31 + 1;
            var_r11 = &sp8;
            if ((s32) temp_r0 == 0x25) {
                temp_r9 = *(s32 *)((char *)temp_r31 + (s32)0x1);
                var_r31 = temp_r31 + 1;
                if (((u32) (temp_r9 - 0x61) <= 0x19U) || ((u32) (temp_r9 - 0x41) <= 0x19U) || ((u32) (temp_r9 - 0x30) <= 9U) || ((s32) temp_r9 == 0x5F)) {
                    do {
loop_13:
                        *((s32 *)var_r11) = ((Unk_9F066EC1 *)var_r31)->unk0x0;
                        var_r11 += 1;
                        temp_r9_2 = *(s32 *)((char *)var_r31 + (s32)0x1);
                        var_r31 += 1;
                        if ((u32) (temp_r9_2 - 0x61) <= 0x19U) {
                            goto loop_13;
                        }
                        if ((u32) (temp_r9_2 - 0x41) <= 0x19U) {
                            goto loop_13;
                        }
                        if ((u32) (temp_r9_2 - 0x30) <= 9U) {
                            goto loop_13;
                        }
                    } while ((s32) temp_r9_2 == 0x5F);
                }
            } else {
                sp8 = temp_r0;
                var_r31 = temp_r31 + 1;
                var_r11 = &sp9;
            }
            *((s32 *)var_r11) = 0;
            temp_r3 = fn_801272AC(arg1, Script_GenerateCRC(&sp8));
            if (temp_r3 != NULL) {
                *(u32 *)((char *)0x80383634 + (s32)0x0) = (u32) ((*(u32 *)((char *)0x80383634 + (s32)0x0) & ~0x7F0000) | (((*((u32 *)&temp_r3->unk0x0) & 0x7F) << 0x10) & 0x7F0000));
                *(f32 *)((char *)0x80383634 + (s32)0x8) = (f32) *((f32 *)&temp_r3->unk0x8);
                fn_8012B1C0(arg0, 0x80383634);
                temp_r0_2 = ((u32) *(u32 *)((char *)0x80383634 + (s32)0x0) >> 0x10U) & 0x7F;
                switch (temp_r0_2) {                
                case 1:
                    temp_r3_2 = ContainsFlag(arg1, QB_USECOMMAS);
                    if (temp_r3_2 != 0) {
                        strcpy(&sp40, fn_80009628_4(arg0, arg1, *(f32 *)((char *)0x80383634 + (s32)0x8), ','));
                    } else {
                        spC4 = temp_r3_2;
                        if (GetInteger(arg1, QB_INTEGER_WIDTH, (f32 *) &spC4, 0) != 0) {
                            sprintf(&sp40, (u8 *)0x8029D230, (f32) spC4, *(f32 *)((char *)0x80383634 + (s32)0x8));
                        } else {
                            sprintf(&sp40, (u8 *)0x8029D238, *(f32 *)((char *)0x80383634 + (s32)0x8));
                        }
                    }
                    var_r30 = strlen(&sp40);
                    var_r4 = &sp40;
block_40:
                    strcpy(var_r29, var_r4);
                    var_r29 = &var_r29[var_r30];
                    break;
                case 2:
                    spC8 = 4e-45f;
                    GetInteger(arg1, QB_DECIMALPLACES, &spC8, 0);
                    sprintf(&spA8, (u8 *)0x8029D23C, spC8);
                    sprintf(arg0, &sp40, &spA8, *(f32 *)((char *)0x80383634 + (s32)0x8));
block_39:
                    var_r30 = strlen(&sp40);
                    var_r4 = &sp40;
                    goto block_40;
                case 5:
                    temp_r9_3 = *(f32 *)((char *)0x80383634 + (s32)0x8);
                    sprintf(&sp40, (u8 *)0x8029D244, *(s32 *)((char *)(s32)temp_r9_3 + (s32)0x4), *(s32 *)((char *)(s32)temp_r9_3 + (s32)0x8));
                    goto block_39;
                case 6:
                    temp_r9_4 = *(f32 *)((char *)0x80383634 + (s32)0x8);
                    sprintf(&sp40, (u8 *)0x8029D250, *(s32 *)((char *)(s32)temp_r9_4 + (s32)0x4), *(s32 *)((char *)(s32)temp_r9_4 + (s32)0x8), *(s32 *)((char *)(s32)temp_r9_4 + (s32)0xC));
                    goto block_39;
                case 13:
                    var_r23 = 2;
                    sprintf(&sp40, (u8 *)0x8029D264, (f32) fn_80126698(*(f32 *)((char *)0x80383634 + (s32)0x8)));
                    goto block_39;
                default:
                    var_r3 = *(f32 *)((char *)0x80383634 + (s32)0x8);
                    var_r0_3 = *(s32 *)((char *)(s32)var_r3 + (s32)0x0);
                    if ((s32) var_r0_3 != 0) {
                        do {
                            *((s32 *)var_r29) = var_r0_3;
                            var_r0_3 = *(s32 *)((char *)(s32)var_r3 + (s32)0x1);
                            var_r3 = (f32) ((s32) var_r3 + 1);
                            var_r29 += 1;
                        } while ((s32) var_r0_3 != 0);
                    }
                    break;
                }
                goto block_45;
            }
block_1:
            return 0;
        }
block_44:
        *((s32 *)var_r29) = var_r0_2;
        var_r31 += 1;
        var_r29 += 1;
block_45:
        var_r0 = *((s32 *)var_r31);
        if ((s32) var_r0 == 0) {
            goto block_46;
        }
        goto loop_4;
    }
block_46:
    *((s32 *)var_r29) = 0;
    if (spB8 != 0) {
        AddString(arg0, 0x80383248);
    }
    if (spBC != 0) {
        AddChecksum(arg0, spBC, Script_GenerateCRC((u8 *)0x80383248));
    }
    return var_r23;
}

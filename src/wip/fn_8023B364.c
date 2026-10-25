// PARKED 2026-10-05: DIFF 9.25%, object 908 B == want 908 B
// (size now matches). Frame and every local offset now match want too; what is
// left is register numbering plus one extra callee-saved register in want.
//
// SEMANTICS: a level/script-header parser. If arg0->unk0x1772C bit 2 is clear
// it (a) clears a 0x3A98-byte block at arg0+0x17394 downwards with BYTE stores,
// (b) builds a 16-byte descriptor at arg0+0x13C94, (c) walks arg0->unk0x80,
// hashing sub-records with GetChecksum and packing matches into a bitfield,
// (d) calls fn_80243C18 32 times collecting the returned nodes into a LOCAL
// array of 32, and (e) CRC's arg0+0x13C98 over 0x3A94 bytes.
//
// TYPE FIXES MADE (all verified against the want disassembly,
// all kept):
//  1. `static s32 sp10;` was a FILE-SCOPE static that the draft then indexed
//     as `(&sp10)[i]`. want keeps that array on the STACK: `addi r31,r1,0x10`
//     then `stw r3,0(r31)` / `addi r31,r31,4` / `addi r28,r1,0x10` with
//     `slwi r29,r30,2` + `lwzx`. So it is a local `s32 sp10[32]` (0x80 B) -
//     which is what makes `stwu r1,-0xd0` come out at all (the old body had a
//     0x50 frame because the array lived in .bss).
//  2. The zero-fill loop stores a BYTE (`*var_r9 = 0`, s8* -> `stb`), not a
//     word; the draft's `*((s32 *)var_r9) = 0` emitted `stw`.
//  3. `void **var_r31_2` -> `void *var_r31_2`. The walking pointer is advanced
//     with `+= 4`, and want advances it by 4 BYTES (`addi r31,r31,4`); with a
//     `void **` GCC advances by 16.
//  4. Local declaration order (sp8, then the array, then sp90) reproduces
//     want's layout exactly: sp8 at r1+0x08 (word store `stw r9,8(r1)`, byte
//     reads at 9/a/b, u16 store `sth r0,4(r19)` with r19 = r1+0x90), array at
//     r1+0x10, flag word at r1+0x90.
//
// STILL BLOCKING:
//  * want saves 13 GPRs (`stmw r18,0x98`) where this body saves 12
//    (`stmw r19,0x9c`) - one long-lived value more in the original, worth the
//    4-byte offset of the save area. Everything else that differs is the
//    register NUMBER of the same values (want `addis r3,r30,1` / `mr r23,r3`,
//    got `addis r9,r30,1` / `mr r24,r9`; want keeps `addi r28,r30,0x3530`
//    live, got recomputes), which is why the index-aligned score sits at 9%
//    even though the two streams are nearly isomorphic.
//  * The body still has ~20 `*((s32 *)ptr)` puns through `u8 *` / `void *`
//    pointers that will each need the same "give it a real type" treatment.
//    Those are the next things to try; they were left alone here because each
//    one needs its own want-vs-got check and the register numbering has to be
//    fixed first for the score to move at all.
//  * NOTE ON THE NUMBER: the earlier body scored 12.78% with frame 0x50
//    and a .bss-resident array. That is index-alignment luck, not progress.
// family=m2c range=0x8023B364-0x8023B6F0 size=908B
#include "types.h"
extern char lbl_802B0DB8[];
#include "qb_constants.h"
#include "structs.h"
s32 Crc_GenerateCRCCaseSensitive(s32, s32);
extern char lbl_80305FF8[];

void fn_8023B364(Unk_E4EF6F7F *arg0) {
    Unk_EB9D76D8 sp8;
    s32 sp10[32];
    s32 sp90;
    s16 var_r21;
    s16 var_r22;
    s32 *temp_r25;
    s32 temp_r0_2;
    s32 temp_r0_4;
    s32 temp_r29_2;
    s32 temp_r30;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r5;
    s32 var_r6;
    s32 var_r9_2;
    s8 *var_r9;
    s8 temp_r9;
    u32 temp_r20;
    u32 var_r31;
    u8 *var_r11;
    u8 *var_r26;
    u8 *var_r31_3;
    u8 *var_r9_3;
    u8 temp_r0;
    u8 temp_r0_3;
    void *var_r31_2;
    Unk_A65310C4 *temp_r10;
    void *temp_r11;
    void *temp_r11_2;
    Unk_435171A8 *temp_r11_3;
    CStruct *temp_r21;
    Unk_57D8CDC4 *temp_r24;
    Unk_F96D0DC8 *temp_r29;
    Unk_31F789C4 *temp_r3;
    Unk_C7387A53 *temp_r3_2;
    void *temp_r4;
    void *temp_r4_2;
    void *temp_r7;
    Unk_C7387A53 *var_r27;

    if (!(arg0->unk0x1772C & 4)) {
        var_ctr = 0x3A98;
        temp_r29 = (char *)arg0 + 0x3524;
        var_r9 = (char *)arg0 + 0x1772B;
        do {
            *var_r9 = 0;
            var_r9 -= 1;
            var_ctr -= 1;
        } while (var_ctr != 0);
        temp_r24 = (char *)arg0 + 0x13C94;
        temp_r21 = fn_80125A08((s32)lbl_802B0DB8, 1);
        temp_r20 = temp_r21->unk0x4;
        temp_r24->unk0xC = (u8) arg0->unk0x3524;
        *(s32 *)((char *)temp_r24 + (s32)0xA) = 0;
        *(s32 *)((char *)temp_r24 + (s32)0x6) = 0x4E24;
        temp_r24->unk0x8 = (u16) arg0->unk0x3522;
        temp_r24->unk0xD = (u8) temp_r29->unk0x2;
        temp_r24->unk0xE = (u8) temp_r29->unk0x3;
        temp_r24->unk0xF = (u8) temp_r29->unk0x5;
        temp_r24->unk0x18 = (s32) *(s32 *)((s32 *)(*(void **)(s32)lbl_80305FF8) + 0x7C);
        temp_r24->unk0x14 = (s8) *(s32 *)(*(s32 *)((char *)((char *)arg0) + 0x0) + 0x20);
        strcpy((char *)arg0 + 0x13CB0, (char *)arg0 + 0x17730);
        var_r11 = (char *)arg0 + 0x13CF0;
        var_r9_2 = 0;
        do {
            var_ctr_2 = 0x3A;
            var_r9_3 = (var_r9_2 * 0x3A0) + ((char *)arg0 + 0x3530 + 3);
loop_5:
            var_r9_3 += 0x10;
            temp_r0 = *((s32 *)var_r9_3);
            *((s32 *)var_r11) = temp_r0;
            var_r11 += 1;
            var_ctr_2 -= 1;
            if (var_ctr_2 != 0) {
                goto loop_5;
            }
            var_r9_2 += 1;
        } while (var_r9_2 <= 0x39);
        var_r27 = arg0->unk0x80;
        var_r26 = var_r11;
        var_r22 = 0;
        if (var_r27 != NULL) {
            do {
                fn_802432A0(var_r27);
                temp_r3 = fn_802416F8();
                temp_r0_2 = temp_r3->unk0x8;
                if (!(temp_r0_2 & 8) && !(temp_r0_2 & 0x100) && (temp_r0_2 & 4)) {
                    temp_r25 = var_r26 + 4;
                    var_r31 = 0;
                    *((s32 *)&sp8) = temp_r3->unk0x0;
                    sp8.unk0x4 = (u16) temp_r3->unk0x4;
                    temp_r30 = temp_r3->unk0x34;
loop_14:
                    if (var_r31 < temp_r20) {
                        if (GetChecksum(temp_r21, var_r31) == temp_r30) {
                            var_r22 += 1;
                            *((s32 *)var_r26) = (s32) ((var_r31 & 0x3FF) | ((u8) *((s32 *)&sp8) << 0xA) | (*(s32 *)((char *)&sp8 + 0x2) << 0x12));
                            var_r26 += 8;
                            *((s32 *)temp_r25) = (temp_r3->unk0xC & 3) | ((((s8) sp8.unk0x1 + 0x10) * 4) & 0x7C);
                        } else {
                            var_r31 += 1;
                            goto loop_14;
                        }
                    }
                }
                var_r27 = var_r27->unk0xC;
            } while (var_r27 != NULL);
        }
        temp_r24->unk0x10 = var_r22;
        var_r21 = 0;
        var_r30 = 0;
        var_r31_2 = &sp10;
        do {
            sp90 = 0;
            temp_r3_2 = fn_80243C18(arg0->unk0x177C8, var_r30, &sp90);
            if ((temp_r3_2 != NULL) && (sp90 == 0) && ((s32) temp_r3_2->unk0x48 == 2)) {
                *((s32 *)var_r31_2) = temp_r3_2;
                var_r21 += 1;
                var_r31_2 += 4;
            }
            var_r30 += 1;
        } while (var_r30 <= 0x1F);
        var_r30_2 = 0;
        var_r31_3 = var_r26;
        *(s32 *)((char *)temp_r24 + (s32)0x12) = var_r21;
        if (var_r21 > 0) {
            do {
                temp_r29_2 = var_r30_2 * 4;
                ((Unk_24830D7B *)var_r31_3)->unk0x8 = 0U;
                var_r6 = 0;
                temp_r4 = var_r31_3 + 6;
                var_r5 = 0;
                var_r30_3 = 0;
loop_27:
                temp_r11 = (&sp10)[var_r30_2];
                temp_r10 = var_r30_3 + temp_r11;
                temp_r7 = temp_r11 + var_r5;
                *((s32 *)var_r31_3 + (s32)var_r6) = *((s32 *)var_r30_3 + (s32)temp_r11);
                temp_r11_2 = temp_r7;
                var_r30_3 += 6;
                *((s32 *)var_r31_3 + 2 + var_r6) = (s8) *((s8 *)&temp_r10->unk0x1) + 8;
                *((s32 *)var_r31_3 + 4 + var_r6) = *(s32 *)((char *)temp_r10 + (s32)0x2);
                var_r5 += 4;
                temp_r0_3 = ((Unk_24830D7B *)var_r31_3)->unk0x8 | (*((s32 *)temp_r11 + 0xC + var_r5) << var_r5);
                ((Unk_24830D7B *)var_r31_3)->unk0x8 = temp_r0_3;
                temp_r9 = (*(s32 *)((char *)temp_r7 + (s32)0x17) * 0x10) & 0xF0;
                *((s32 *)temp_r4 + (s32)var_r6) = temp_r9;
                *((s32 *)temp_r4 + (s32)var_r6) = temp_r9 | (*(s32 *)((char *)temp_r11_2 + (s32)0x1F) & 0xF);
                var_r6 += 1;
                if (var_r6 <= 1) {
                    goto loop_27;
                }
                var_r30_2 += 1;
                temp_r4_2 = (&sp10)[var_r30_2];
                strcpy(var_r31_3 + 0xA, temp_r4_2 + 0x24);
                temp_r11_3 = *(&sp10 + temp_r29_2);
                ((Unk_24830D7B *)var_r31_3)->unk0x2A = (u16) temp_r11_3->unk0x46;
                ((Unk_24830D7B *)var_r31_3)->unk0x2C = (s32) temp_r11_3->unk0x50;
                var_r31_3 += 0x30;
            } while (var_r30_2 < var_r21);
        }
        temp_r24->unk0x4 = (s16) ((s32)var_r31_3 - (s32)temp_r24);
        temp_r0_4 = arg0->unk0x1772C;
        if (!(temp_r0_4 & 5)) {
            arg0->unk0x1772C = (s32) (temp_r0_4 | 8);
        }
        arg0->unk0x1772C = (s32) ((arg0->unk0x1772C | 3) & QB_UNKNOWN_0xFFFFFFFB);
        *((s32 *)&arg0->unk0x13C94) = Crc_GenerateCRCCaseSensitive((char *)arg0 + 0x13C98, 0x3A94);
    }
}

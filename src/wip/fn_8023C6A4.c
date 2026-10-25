// PARKED 2026-09-27 (ag20): best 79.7% (was 79.7%). Residual 13 words:
//   (a) register rotation — want prev=r28/&sp8=r27, got prev=r27/&sp8=r28 (6
//       words: li r28,0/li r27,0; addi r27,r1,8/addi r28,r1,8; cmpwi r28/cmpwi
//       r27; stw r30,0x14(r28/r27); mr r28,mr r27; lbz r0,5(r27/r28));
//   (b) call-site &sp8 rematerialization — want addi r3,r1,8 + addi r5,r1,8,
//       got mr r3/r5 from the homed &sp8 (3 words; doc-15 arg-setup order:
//       want [r9][r4-r8][r3], got [r3][r4-r8][r9]);
//   (c) load order — want lwz r9,0(r29) [temp_r9=arg0->unk0[0]] before lbz
//       r0,3(r27) [b0] (2 words);
//   (d) loop latch — want mr r31,r30 then cmpwi r30,0, got the reverse (2 words).
// Family: register-allocation rotation (prev/&sp8) + doc-15 arg-setup/remat.
// KEY FINDING (ag20): a register pin (prev->r28 via an s32 alias) forces the
//   allocation and CASCADES — 79.7% -> 89.06% (7 diffs), proving the register
//   swap is the root cause and not source-reachable. The remaining 7 (remat 3,
//   load 2, latch 2) resist every source shape tried. Pin NOT used in the
//   final body per the no-asm preference; left as a documented diagnostic.
// family=m2c range=0x8023C6A4-0x8023C7A4 size=256B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// Semantics: walk arg0->unk0x60 list (next=unk0x14). Per node: fn_80240B0C(&sp8,0,0,0,0,0,0)
//   then fn_802451A4(node,arg0,&sp8); 4-way unsigned byte compare (sp8[3]/sp8[5] vs
//   arg0->unk0[0]+0x3524[3/5]) — if any b0>b3||b0>b5||b2>b3||b2>b5, unlink node
//   (fix prev->unk0x14 or arg0->unk0x60 head) + fn_802448E4(node,3); else prev=node.
//   Finally arg0->unk0x64 = arg0->unk0x60; fn_8023E0F8(arg0, 0).
// TRIED (19 variants, no-asm except the pin diagnostic): volatile s32 sp8 (broke
//   alloc); u8 sp8[6] array + sp8[3]/sp8[5] (remat OK but r1-direct reads + broke
//   alloc); named byte-ptr b at top / if-top / before-prev (all hoist &sp8 to entry
//   -> broke alloc); init-order swap; load-order; latch comma-condition; while-loop;
//   M8.31 return-type flips on fn_80240B0C / fn_802451A4 (no help); pin+array,
//   pin+byte-ptr (broke alloc); pin+load, pin+latch (no change).
// FLAG: -fno-expensive-optimizations -fno-schedule-insns2
#include "types.h"
#include "structs.h"
void fn_8023E0F8(CStruct *, s32);
void fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
void fn_802448E4(Unk_5AA7B5D7 *, s32);
void fn_802451A4(Unk_F96D0DC8 *, void *, Unk_F96D0DC8 *);
void fn_8023C6A4(CStruct *arg0) {
    s32 sp8;
    u8 b0;
    u8 b2;
    u8 b3;
    u8 b5;
    void *temp_r30;
    void *temp_r9;
    Unk_C8FEE62D *var_r28;
    Unk_C8FEE62D *var_r31;

    var_r28 = NULL;
    var_r31 = arg0->unk0x60;
    if (var_r31 != NULL) {
        do {
            temp_r30 = var_r31->unk0x14;
            fn_80240B0C((Unk_F96D0DC8 *)&sp8, 0, 0, 0, 0, 0, 0);
            fn_802451A4(var_r31, arg0, (Unk_F96D0DC8 *)&sp8);
            b0 = *(u8 *)((char *)&sp8 + 0x3);
            temp_r9 = arg0->unk0x0 + 0x3524;
            b3 = *(u8 *)((char *)temp_r9 + 0x3);
            if (b0 > b3 || (b5 = *(u8 *)((char *)temp_r9 + 0x5), b0 > b5) || (b2 = *(u8 *)((char *)&sp8 + 0x5), b2 > b3) || b2 > b5) {
                if (var_r28 != NULL) {
                    var_r28->unk0x14 = temp_r30;
                }
                if (var_r31 == arg0->unk0x60) {
                    arg0->unk0x60 = temp_r30;
                }
                if (var_r31 != NULL) {
                    fn_802448E4(var_r31, 3);
                }
            } else {
                var_r28 = var_r31;
            }
            var_r31 = temp_r30;
        } while (temp_r30 != NULL);
    }
    arg0->unk0x64 = arg0->unk0x60;
    fn_8023E0F8(arg0, 0);
}
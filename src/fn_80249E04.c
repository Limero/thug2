// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80249E04-0x80249F70 (364B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* ---- Callee audit (from the retail prologues + epilogues; m2c had all four wrong) ----
 *  fn_8024C970  mr r30,r3 then immediately clobbers r4 -> 1-arg; returns s32
 *               (`mr r30,r3` right after the call in want).        s32  fn(void *)
 *  fn_8024A0B0  mr r28,r3; mr r19,r4 ; epilogue (0x8024A418) sets no r3 -> 2-arg void
 *  fn_80249F70  mr r29,r3 ; epilogue (0x8024A09C) sets no r3 -> 1-arg void
 *  fn_8024A438  mr r31,r3 ; epilogue (0x8024AEDC) sets no r3 -> 1-arg void
 *  m2c passed 3/3/1/1 args; the extra args made ngccc emit `mr r4,r3; mr r5,r3`
 *  arg-setup that want does not have.  Being 1-arg also matters because it leaves
 *  the caller's r4/r5 untouched, which is exactly what want shows at the `bl`.
 */
s32 fn_8024C970(void *);
void fn_8024A0B0(void *, s32);
void fn_80249F70(void *);
void fn_8024A438(void *);

/* Sub-record at arg0+0x30 (want addresses it as one base register r11 with +4..+0x14
 * displacements).  f0C and f14 hold POINTERS (arg1), f04 receives arg1[1].  A file-local
 * typedef with the honest pointer member types compiles warning-free and byte-exactly;
 * the corpus `Unk_C8FEE62D` (all-s32 fields) also matched but threw four cast warnings. */
typedef struct E04_sub {
    char pad00[4];
    s32 f04;
    s32 f08;
    s32 *f0C;
    s32 f10;
    struct E04_sub *f14;
} E04_sub;

bool fn_80249E04(Unk_98D3ADCB *arg0, s32 *arg1, s32 arg2, s32 *arg3) {
    E04_sub *temp_r9;
    s32 temp_v4;      /* arg1[1], hoisted so both loads precede the three-store run */
    s32 temp_r11_2;
    s32 temp_r9_2;
    s32 temp_r9_3;
    s32 temp_r9_4;
    s32 var_r9;
    s32 temp_fl;      /* arg0->unk0x8, its OWN name — sharing one name across the
                       * prologue and this block collapsed 3 registers onto one */
    s32 temp_v9;
    E04_sub *temp_r11;
    s32 temp_r3;

    temp_r11 = (E04_sub *)((char *)arg0 + 0x30);
    temp_r11->f14 = (E04_sub *)arg1;
    temp_r11->f0C = arg1;
    arg0->unk0x30 = *arg1;
    temp_r9 = (E04_sub *)temp_r11->f14;   /* want re-loads this instead of forwarding r4 */
    temp_v4 = temp_r9->f04;
    temp_r11->f04 = temp_v4;
    temp_r11->f08 = 0;
    temp_r11->f10 = arg2;                 /* store order 0x4,0x8,0x10 emits want's
                                           * 0x10,0x4,0x8 (recipe 24/64 rotation) */
    temp_r3 = fn_8024C970((char *)arg0 + 0x48);
    if (temp_r3 == 1) {
        fn_8024A0B0(arg0, 0);
    } else if (temp_r3 == 0) {
        fn_80249F70(arg0);
    } else if (temp_r3 == 2) {
        fn_8024A438(arg0);
    } else {
        fn_8024A0B0(arg0, 1);
    }
    *arg3 = arg0->unk0xC;
    /* `!= 2` (not `== 2`, and not `== 0 || == 2`): the spelling picks BOTH the branch
     * polarity (want `beq` to the swap block) and which arm is inlined (want has the
     * flag block falling through and the 2-insn swap out of line).  A disjunction here
     * costs ~55 points: it makes ngccc allocate cr4 for r==0 plus an entry `mfcr r12`. */
    if (temp_r3 != 2) {
        temp_fl = arg0->unk0x8;
        if (temp_fl & 1) {
            *arg3 = arg0->unk0x10;
            /* want loads unk0x14 FIRST here (m2c's direction was reversed) */
            if (arg0->unk0x8 & 2) {
                temp_r9_2 = arg0->unk0x14;
                arg0->unk0x14 = arg0->unk0x20;
                arg0->unk0x20 = temp_r9_2;
            }
            temp_r11_2 = arg0->unk0x10;   /* want's 3-load order is 0x10,0x14,0xC */
            temp_r9_3 = arg0->unk0x14;
            temp_v9 = arg0->unk0xC;
            arg0->unk0x14 = temp_r11_2;
            arg0->unk0xC = temp_r9_3;
            arg0->unk0x10 = temp_v9;
        } else {
            if (temp_fl & 2) {
                temp_r9_4 = arg0->unk0x10;
                arg0->unk0x10 = arg0->unk0x20;
                arg0->unk0x20 = temp_r9_4;
            }
            var_r9 = arg0->unk0x10;
            arg0->unk0x10 = arg0->unk0xC;
            goto block_16;   /* both arms share the `unk0xC = var_r9` tail: crossjump
                             * merges it, and sharing the var keeps want's 4-insn swap */
        }
    } else {
        var_r9 = arg0->unk0x1C;
        arg0->unk0x1C = arg0->unk0xC;
block_16:
        arg0->unk0xC = var_r9;
    }
    arg0->unk0x108 = arg0->unk0x108 + 1;
    return true;
}

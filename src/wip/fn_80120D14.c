// PARKED 2026-10-03 — base 11.2% (524 B).  Carries phantom call arguments
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 11.1940% -> 12.5926% per-object flags: -Os -> -fno-schedule-insns
// (doc-58): the address materialised for a store is ALSO read as the callee's
// argument.  DVD/AX subsystem; heavy on the phantom-arg family rather than on
// a codegen wall.  Retained as the best-known body.
//
// family=m2c range=0x80120D14-0x80120F20 size=524B
// Measured: DIFF 7.2%. m2c generated body; significant structural and regalloc divergence.
// FLAG: -fno-schedule-insns
// UPDATED 2026-09-15: doc-56 rescan (all undeclared callees at once, tools/protoscale.py); now 9.6%.
// UPDATED 2026-09-15: doc-56 all-at-once prototype rescan (tools/protoscale.py 2026-09-16); now 9.7%.
// 2026-09-22 literal->symbol substitution: 9.7 -> 11.2 (symbol for 0x8011FB48)
extern char fn_8011FB48[];
#include "qb_constants.h"
#include "structs.h"
s32 AXAcquireVoice(s32, s32, s32);
extern f32 lbl_8029D848;
extern f32 lbl_8029D84C;
extern s32 lbl_80302F04;
extern f32 lbl_80302F0C;
extern s32 lbl_80302F10;
void DVDReadAsyncPrio(void *, void *, void *, void *, void *, void *, void *);
void DVDClose(void *);
s32 fn_80120D14(s32 arg0, s32 arg1, s32 arg3, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    f32 temp_f1;
    s32 temp_r0;
    s32 temp_r26;
    s32 temp_r30;
    s32 temp_r3;
    s32 var_r5;
    CStruct *temp_r28;
    if (fn_80121448(arg1) == 1) {
        temp_r30 = arg1 * 0x21C;
        temp_r28 = fn_800153C4(arg0, lbl_80302F10);
        DVDConvertPathToEntrynum(0x8029D830);
        temp_r26 = temp_r30 + 0x8038F0EC;
        if (DVDFastOpen(temp_r26 + (*(s32 *)((char *)temp_r30 + (s32)0x8038F0E8) * 0x3C)) != 0) {
            if ((temp_r28 != NULL) && ((s32) temp_r28->unk0x4 != 0)) {
                temp_r3 = AXAcquireVoice(0x1F, fn_8011FB48, 0);
                *(s32 *)((char *)temp_r30 + (s32)0x8038F2CC) = temp_r3;
                *(s32 *)((char *)temp_r30 + (s32)0x8038F0E0) = 0;
                *(s32 *)((char *)temp_r30 + (s32)0x8038F0E4) = 0;
                *(s32 *)((char *)temp_r30 + (s32)0x8038F0C4) = 0;
                *(s32 *)((char *)temp_r30 + (s32)0x8038F0CC) = 0;
                *(s32 *)((char *)temp_r30 + (s32)0x8038F2D0) = 0;
                *(s32 *)((char *)temp_r30 + (s32)0x8038F0C8) = (s32) temp_r28->unk0x0;
                lbl_80302F04 |= 0x2000 << arg1;
                *(s32 *)((char *)temp_r30 + (s32)0x8038F0C0) = (s32) temp_r28->unk0x4;
                temp_f1 = lbl_8029D848;
                *(f32 *)((char *)temp_r30 + (s32)0x8038F0D0) = (f32) (farg2 * lbl_80302F0C);
                *(s32 *)((char *)temp_r30 + (s32)0x8038F0D8) = farg0;
                *(s32 *)((char *)temp_r30 + (s32)0x8038F0DC) = farg1;
                fn_8011F590(temp_r3 + 0x138, temp_r3, 0, 0, 0x8038F0D0, 0x802A0000, 0x8038F0D8, 0x8038F0DC, temp_f1, temp_f1, lbl_8029D84C);
                var_r5 = 0x4060;
                *(s32 *)((char *)temp_r30 + (s32)0x8038F2D8) = arg3;
                temp_r0 = temp_r28->unk0x4;
                if ((u32) temp_r0 <= 0x405FU) {
                    var_r5 = temp_r0 & QB_UNKNOWN_0xFFFFFFE0;
                }
                *(s32 *)((char *)temp_r30 + (s32)0x8038F2D4) = 0;
                DVDReadAsyncPrio(temp_r26 + (*(s32 *)((char *)temp_r30 + (s32)0x8038F0E8) * 0x3C), *(s32 *)((s32 *)(arg1 * 4) + 0x80302F14), var_r5, temp_r28->unk0x0, 0x8011FDD0, 2, 0x8038F2D4);
                return 1;
            }
            DVDClose(temp_r30 + 0x8038F0EC + (*(s32 *)((char *)temp_r30 + (s32)0x8038F0E8) * 0x3C));
            goto block_8;
        }
    }
block_8:
    return 0;
}

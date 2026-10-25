// PARKED 2026-09-27 (ag06): best 30.0% (was 22.2%). DIFF — register-allocation
// mismatch in the bit-count loop. WANT: index r11, count r10, array base r3 (a
// copy of arg0 via `mr r3, r30`), i+1 in r8, word reuses r11; GOT: index r9,
// count r8, base in r30 (folded, no copy), word r11 separate. The missing
// `mr r3, r30` base copy shifts every subsequent word by one. Tried: pointer
// param (u32* arg0), named base pointer (GCC folds trivial copies of arg0),
// for/while/do-while outer loops, counted inner loop (for j<32 -> mtctr/bdnz,
// matches), correct u32 element indexing, removed the extra (u32)arg1>0 guard,
// OSPanic args as char[] symbols (lis+addi address form), volatile
// lbl_8039BE98 for the count re-read (worse). The base copy is not forceable
// from C — GCC folds any named pointer that is a trivial copy of arg0, and
// the scheduler normalises the scratch-register assignment. Known family:
// regalloc (register-allocation coin-flip on the loop's scratch registers).
//
// WIP DRAFT (non-matching) — body hand-written to fix the m2c draft's structure.
// family=m2c range=0x8012399C-0x80123A98 size=252B
#include "types.h"
s32 OSPanic(s32, s32, s32);
extern char lbl_8029DEB4[];
extern char lbl_8029E338[];
extern u8 lbl_8039BE68;
extern s32 lbl_8039BE90;
extern s32 lbl_8039BE94;
extern u32 lbl_8039BE98;
void fn_8012399C(s32 arg0, s32 arg1) {
    s32 temp_r29;
    s32 var_r9;
    u32 var_r10;
    u32 var_r11;

    temp_r29 = OSDisableInterrupts();
    lbl_8039BE90 = arg0;
    lbl_8039BE94 = arg1;
    if (arg1 != 0) {
        lbl_8039BE98 = 0U;
        var_r11 = 0;
        var_r10 = 0U;
        while (var_r11 < (u32) arg1) {
            u32 word = ((u32 *)arg0)[var_r11];
            for (var_r9 = 0; var_r9 < 32; var_r9++) {
                if (word & (1U << var_r9)) {
                    var_r10 += 1;
                }
            }
            var_r11 += 1;
        }
        lbl_8039BE98 = var_r10;
        if (lbl_8039BE98 > 2U) {
            OSPanic(lbl_8029DEB4, 0x7B7, lbl_8029E338);
        }
    } else {
        lbl_8039BE98 = lbl_8039BE68;
    }
    OSRestoreInterrupts(temp_r29);
}

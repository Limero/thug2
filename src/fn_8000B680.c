// fn_8000B680 — deferred-call countdown dispatcher (4th matched function).
//
// Pattern: a global counter decrements each call; when it passes 1 the else
// path runs a stored callback (if any) then clears both globals. The
// callback is invoked through a table: task+0x20 -> tbl, (s16)tbl[8] is a
// byte offset added to the task pointer, (u32)tbl[12] is the function.
//
// Matching notes (ngccc / GCC 2.95.2, -O2 -G0):
//  * GPR-only saves (stmw r30/r31) — the FPR +8-frame quirk does NOT apply
//    to GPR-only functions, so this matched byte-for-byte.
//  * The two globals are separate (NOT a struct): the original materializes
//    the 0x80300000 base twice (r31 for the counter, r30 for the task).
//  * The final zero-out must be written task-first, counter-second: ngccc
//    reorders the stores to counter-first, matching the original. Do not
//    "fix" the order.
//  * The counter compare is unsigned (cmplwi) — keep it `unsigned int`.
#include "types.h"
#include "structs.h"

extern unsigned int lbl_802FFE80; /* counter */
extern void *lbl_802FFE7C;        /* pending callback context */

void fn_8000B680(void) {
    if (lbl_802FFE80 > 1) {
        lbl_802FFE80 -= 1;
    } else {
        void *task = lbl_802FFE7C;
        if (task != 0) {
            char *tbl = *((char * *)&((Unk_C7387A53 *)task)->unk0x20);
            int off = *((short *)&((Unk_42076946 *)tbl)->unk0x8);
            void (*fp)(void *, int) = *(void (**)(void *, int))(tbl + 12);
            fp((char *)task + off, 3);
        }
        // Written task-first on purpose — ngccc emits counter-first here,
        // which is what the original does.
        lbl_802FFE7C = 0;
        lbl_802FFE80 = 0;
    }
}

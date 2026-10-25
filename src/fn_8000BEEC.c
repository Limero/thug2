// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000BEEC-0x8000BF3C (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void fn_8000BF3C(Unk_FFAD6788 *);
void fn_8000C39C(Unk_76808E8C *);
void fn_8000BF80(Unk_AD12C14B *);

// ID: state-machine command dispatcher (suggested rename: CmdDispatch /
// Object_ProcessCommand). Reads *(arg0+0xDC): state 1 → fn_8000C39C,
// state 2 → fn_8000BF80, state 5 → fn_8000BF3C, else no-op.
// Layout recipe (cracked 2026-09-06, was parked 85%): the if/return-structured
// GOTO form — compares inline in want's order (==1, >1, ==2, ==5), the two
// single-call blocks as trailing labels, bare `return;` on the inline path —
// makes GCC place both call blocks out of line exactly like want. (A flat
// goto chain had failed at 68%.)

void fn_8000BEEC(Unk_FFAD6788 *arg0) {
    s32 state;
    state = arg0->unk0xDC;
    if (state == 1)
        goto state1;
    if (state > 1) {
        if (state == 2)
            goto state2;
        if (state == 5)
            fn_8000BF3C(arg0);
    }
    return;
state1:
    fn_8000C39C((Unk_76808E8C *)arg0);
    return;
state2:
    fn_8000BF80((Unk_AD12C14B *)arg0);
}

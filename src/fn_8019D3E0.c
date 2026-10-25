// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019D3E0-0x8019D438 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029FD38[];
s32 fn_8009CFB8(s32);
void fn_8009D354(void *, s32);
void fn_8009D020(void);

// WINNER fn_8019D3E0 (88B) - doc 23 sibling. f64 anchor at slot 8 explains the
// empty 0xC halfword; result stored via temp-var web (mr r0,r3 copy); protos
// kill both crclr; D354 takes the CFB8 RESULT as arg0 (r3 passthrough).
void fn_8019D3E0(void *arg0, s32 arg1) {
    f64 dbl;
    s32 sp10;
    s32 v;

    ((Unk_59AB5482 *)&dbl)->unk0xC = (s32)lbl_8029FD38;
    v = fn_8009CFB8(0);
    sp10 = v;
    fn_8009D354((void *)v, arg1);
    ((Unk_59AB5482 *)&dbl)->unk0xC = (s32)lbl_8029FD38;
    fn_8009D020();
    __asm__("" : : "m"(dbl), "m"(sp10));
}

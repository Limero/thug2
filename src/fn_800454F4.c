// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800454F4-0x80045550 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_8003F360(void);
extern void *fn_80054FD8(void);
extern void fn_8009E274(Unk_31DE137E *, s32);
extern char lbl_80292718[];
void *fn_800454F4(Unk_4313CFEA *arg0) {
    fn_8003F360();
    arg0->unk0x190 = 0;
    *((void * *)&arg0->unk0x8) = lbl_80292718;
    *((void * *)&arg0->unk0x194) = fn_80054FD8();
    fn_8009E274(arg0, QB_UNKNOWN_0x118F6383);
    return arg0;
}
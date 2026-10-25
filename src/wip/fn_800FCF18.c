// family=m2c range=0x800FCF18-0x800FD02C size=276B
// WIP draft - PARKED. See notes below.
// range=0x800FCF18-0x800FD02C size=276 B
// PARKED: three-chain scheduler interleave artifact in first block.
//   Retail interleaves the constant loads as the c164 page into r11, the
//   vtable page into r9, the first float load, the c168 page into r10, the
//   vtable address completion, and the second float load. The build instead
//   loads the c164 page, then the c168 page, then the first float load, then
//   the vtable page, then the second float load, and only then completes the
//   vtable address.
//   Resists: all 6 statement permutations x 6 store orders, -fno-schedule-insns/-insns2/
//   -fno-sched-spec/-interblock, vt-temp chain splits, proto/return-type variants,
//   extern decl orders. Everything else (65/69 words incl. both empty CTR loops,
//   derived-pointer stores, full tail block) matches. Same class as docs/parkings/
//   15-call-arg-setup-scheduling.md coin-flips. Needs game-exact ProDG scheduler.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029C164;
extern f32 lbl_8029C168;
extern char lbl_8029C548[];
extern void fn_800FB0F0(Unk_5B449B03 *);

void *fn_800FCF18(Unk_132A52FF *arg0) {
    f32 c164;
    f32 c168;
    s32 i;

    fn_800FB0F0(arg0);
    c164 = lbl_8029C164;
    c168 = lbl_8029C168;
    arg0->unk0xC = (s32)lbl_8029C548;
    arg0->unk0x10 = c164;
    {
        char *p = (char *)arg0 + 0x10;
        ((Unk_5EF41E38 *)p)->unk0x4 = c164;
        ((Unk_5EF41E38 *)p)->unk0x8 = c164;
        ((Unk_4C649A8C *)p)->unk0xC = c168;
    }
    for (i = 4; i != 0; i--) ;
    for (i = 4; i != 0; i--) ;
    arg0->unk0xA0 = 0;
    c168 = lbl_8029C168;
    *((f32 *)&arg0->unk0x20) = c168;
    c164 = lbl_8029C164;
    arg0->unk0x34 = c168;
    arg0->unk0x24 = c164;
    arg0->unk0x28 = c164;
    arg0->unk0x2C = c164;
    arg0->unk0x30 = c164;
    arg0->unk0x38 = c164;
    arg0->unk0x3C = c164;
    {
        char *q = (char *)arg0 + 0x20;
        ((Unk_C4D756ED *)q)->unk0x20 = c164;
        ((Unk_1D62F22E_2 *)q)->unk0x24 = c164;
        ((Unk_1D62F22E_2 *)q)->unk0x28 = c168;
        ((Unk_1D62F22E_2 *)q)->unk0x2C = c164;
    }
    arg0->unk0x50 = c164;
    arg0->unk0x54 = c164;
    arg0->unk0x58 = c164;
    arg0->unk0x5C = c168;
    arg0->unk0x60 = c168;
    arg0->unk0x64 = c164;
    arg0->unk0x68 = c164;
    arg0->unk0x6C = c164;
    arg0->unk0x70 = c164;
    arg0->unk0x74 = c168;
    arg0->unk0x78 = c164;
    arg0->unk0x7C = c164;
    *((f32 *)&arg0->unk0x80) = c164;
    arg0->unk0x84 = c164;
    arg0->unk0x88 = c168;
    arg0->unk0x8C = c164;
    arg0->unk0x90 = c164;
    arg0->unk0x94 = c164;
    arg0->unk0x98 = c164;
    arg0->unk0x9C = c168;
    return arg0;
}

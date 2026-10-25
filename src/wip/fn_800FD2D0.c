// WIP draft - PARKED. See notes below.
// family=m2c range=0x800FD2D0-0x800FD388 size=184B
// PARKED: 13/46 words (28%). Frame size matches with all-stack-slot locals
// volatile under -mps-float, and both if/else arms plus the indexed float
// loads are structurally right, but register allocation diverges from the
// original: the original keeps the input object pointer, the output pointer
// copy, the temp index, and the scaled index each in a distinct fixed register,
// while this build cascades them through different registers. The tail
// pair-load/store section also scrambles: the ordering of the two pair loads,
// the spill to stack slots, the constant reload, and the second copy for the
// output pair all differ. Tried: volatile on/off per local,
// sp24 non-vol (PRE), f174 staging temp, q/p/out named __ps_t vars, direct
// pair casts, statement reorderings. Needs GCC regalloc pinning not yet found.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 15.2% ([1]rev->15.2%).
#include "types.h"
#include "structs.h"
extern f32 lbl_8029C170;
extern f32 lbl_8029C174;
void *fn_800FD2D0(Unk_EA529D06 *arg0, Unk_9994C3F5 *arg1, s32 arg2) {
    volatile f32 sp8;
    volatile f32 spC;
    volatile f32 sp10;
    volatile f32 sp14;
    volatile f32 sp18;
    volatile f32 sp1C;
    volatile f32 sp20;
    volatile f32 sp24;
    s32 var_r0;
    char *var_r11;
    char *temp_r8;
    __ps_t q;
    __ps_t p;
    __ps_t out;
    f32 f174;

    temp_r8 = *((char * *)&arg1->unk0x8);
    if (((Unk_1D62F22E_2 *)temp_r8)->unk0x3C != 0) {
        var_r11 = (char *)(arg2 * 0xC);
        sp18 = *(f32 *)(var_r11 + ((Unk_1D62F22E_2 *)temp_r8)->unk0x3C);
        sp1C = *(f32 *)(var_r11 + ((Unk_1D62F22E_2 *)temp_r8)->unk0x3C + 4);
        var_r0 = ((Unk_1D62F22E_2 *)temp_r8)->unk0x3C;
        sp24 = lbl_8029C170;
    } else {
        sp24 = lbl_8029C170;
        var_r0 = ((Unk_1D62F22E_2 *)temp_r8)->unk0x30;
        sp1C = *(f32 *)(var_r11 + ((Unk_1D62F22E_2 *)temp_r8)->unk0x30 + 4);
        sp18 = *(f32 *)(var_r11 + ((Unk_1D62F22E_2 *)temp_r8)->unk0x30);
        var_r11 = (char *)(arg2 * 0xC);
    }
    sp20 = *(f32 *)(var_r11 + var_r0 + 8);
    q = *(__ps_t *)&sp18;
    p = *(__ps_t *)&sp20;
    *(__ps_t *)&sp10 = p;
    f174 = lbl_8029C174;
    *(__ps_t *)&sp8 = q;
    sp14 = f174;
    out = q;
    *(__ps_t *)((char *)arg0) = out;
    arg0->unk0x8 = *(__ps_t *)&sp10;
    return arg0;
}

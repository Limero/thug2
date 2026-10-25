// WIP DRAFT (non-matching) — hand rebuild from disasm
// 2026-10-08: reload_pin_sweep WIN — pin `b4u` -> `register ... b4u __asm__("r11")` => official 94.8% (sweep base 90.62%). ONE pin only; pins are not additive.
// UPDATE 2026-10-18: two occupancy-attack variants measured WORSE, reverted.
// (a) clrlwi asm order [b5,b4,b3]: b5 lands r6 (want) but emission order flips
// (93.8%). (b) delay `bp2[4]=b4u` past asm(b5) so r11 stays occupied: both
// clrlwis go fresh but swapped (b4->r6, b5->r7 vs want r7/r6 — allocator gives
// the first asm the lower reg; 92.7%). Residual stays the 5-word load-order +
// b5-color cascade. Baseline 94.8% restored.
// family=m2c range=0x8023EC64-0x8023EDE4 size=384B
// PARKED 90.6%: else-arm three byte-load/coloring rotation (want +4->r11,
// +5->r10, +3->r0; ngccc insists +3->r11-first cascade into clrlwi wedge
// colors e7/e6 swap). All shapes tried: 6 load orders, u8/s32 temps,
// wedge interleave/non-interleave, +/-r barriers, 4 sched flag combos —
// coloring invariant. Rest of body byte-exact incl. dead clrlwi wedges
// (needed to keep DSE from killing the cond-tail re-store).
// family=m2c range=0x8023EC64-0x8023EDE4 size=384B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
void fn_802371CC(Unk_673C6403 * arg0, Unk_4A174A22 * arg1, s32 arg2);
void fn_80236E10(s32 *arg0, s32 arg1);
void *fn_80236EF4(CStruct * arg0, s32 arg1, s32 *arg2);
void *fn_80236FE4(CStruct * arg0, CStruct * arg1, s32 arg2);
void fn_8023D848(Unk_D329255D * arg0);
void fn_8023EDE4(Unk_C7387A53 * arg0, s32 arg1);
void fn_802394F8(Unk_673C6403 * arg0, s32 arg1, Unk_C7387A53 * arg2);
void fn_8023EC64(Unk_C7387A53 *arg0, s32 arg1) {
    s32 temp_r0;
    Unk_B0F7076A *var_r30;
    s32 b3;
    s32 b4;
    s32 b5;
    u8 b3u;
    register u8 b4u __asm__("r11");
    u8 b5u;
    Unk_9994C3F5 *field;

    field = *((s32 * *)&arg0->unk0x48);
    if (field != NULL) {
        field->unk0x8 &= ~0x200;
        fn_802371CC(*(void **)arg0, *((s32 * *)&arg0->unk0x48), 0);
        fn_80236E10((s32 *)*(void **)arg0, 0);
        arg0->unk0x48 = 0;
    }
    var_r30 = fn_80236EF4(*(void **)arg0, arg1, 0);
    if (var_r30->unk0x8 & 1) {
        u8 *bp1 = (u8 *)arg0 + 4;
        bp1[3] = 1;
        bp1[4] = 1;
        bp1[5] = 1;
    } else {
        temp_r0 = (s32)fn_80236FE4(*(void **)arg0, var_r30, 0x204);
        arg0->unk0x48 = temp_r0;
        ((Unk_1D62F22E_2 *)temp_r0)->unk0x8 |= 0x200;
        b4u = *(u8 *)(arg0->unk0x48 + 4);
        b5u = *(u8 *)(arg0->unk0x48 + 5);
        b3u = *(u8 *)(arg0->unk0x48 + 3);
        {
            u8 *bp2 = (u8 *)arg0 + 4;
            __asm__ __volatile__("clrlwi %0,%1,0x18" : "=r"(b4) : "r"(b4u));
            bp2[4] = b4u;
            __asm__ __volatile__("clrlwi %0,%1,0x18" : "=r"(b5) : "r"(b5u));
            bp2[3] = b3u;
            __asm__ __volatile__("clrlwi %0,%1,0x18" : "=r"(b3) : "r"(b3u));
            bp2[5] = b5u;
            if (arg0->unk0x3C & 1) {
                bp2[3] = b5;
                bp2[4] = b4;
                bp2[5] = b3;
            }
        }
    }
    fn_8023D848(arg0);
    temp_r0 = *((s32 *)&var_r30->unk0x8);
    if (temp_r0 & 0x800) {
        fn_8023EDE4(arg0, 2);
    } else if (temp_r0 & 0x8000) {
        fn_8023EDE4(arg0, 4);
        fn_802394F8(*(void **)arg0, 0, NULL);
    } else if (temp_r0 & 0x10000) {
        fn_8023EDE4(arg0, 6);
        fn_802394F8(*(void **)arg0, 0, NULL);
    } else {
        fn_8023EDE4(arg0, 1);
        fn_802394F8(*(void **)arg0, 0, NULL);
    }
}

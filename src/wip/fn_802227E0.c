// WIP DRAFT (non-matching) — C body hand-rebuilt from disasm
// RE-MEASURED 2026-10-07: 95.65% (was 87.0%).  THE TWO BARRIERS WERE THE
// RESIDUAL — the conjunction trap again (AGENTS §6bf-A/§6bg): deleting ONLY
// the `__asm__ volatile("" :: "r"(pblk))` gives 86.96%, deleting ONLY the
// `__asm__("" ::: "memory")` gives 82.61%, deleting BOTH gives 95.65%.
// Both are now deleted; the doc-15 arg-move transposition at the fn_8021B55C
// call site closed by itself once they were gone.
// REMAINING (2 words, one transposition in the tail store run; object 184B ==
// symbol): want `[stb r8,0x18(r1)][sth r8,0xa(r1)]`, got the reverse.  Both
// store v8 (=8).  Source order is [+0x10][+2] and emits [+2][+0x10]; swapping
// the two lines, moving them to address order, and moving `fr.pw = fr.sp34`
// down instead all make it much worse (65.9% / 63.8% / 84.8% — the whole tail
// re-schedules), so want's order is not reachable from either permutation of
// this statement pair.
// 2026-10-20: union-overlay blk (u8 f10 @0x10 / u16 f2 @2 members instead of
// casts) ties 95.65% (same stb/sth swap); split narrow values (u8 b8/u16 h8 +
// pointer-opacity d10) collapses to 30.4% with a 0x50->0x58 frame growth.
// Member typing does not steer the tie-break; kept baseline body as best.
// 2026-10-16: volatile-stb-only / volatile-both / inter-store memory
// barrier / literal-8 store values / -fno-schedule-insns{,2} /
// -fno-sched-spec / -fno-sched-interblock — all keep the same stb/sth swap
// or regress.
// ROOT CAUSE of the swap: the two stores are a clean two-store run of the
// SAME class carrying the SAME value (v8 == 8), and ngccc rotates such a run
// right by one — source [stb +0x10][sth +2] is emitted [sth +2][stb +0x10].
// Reversing the source lines removes the rotation but re-schedules the
// surrounding tail (65.9%), because the pair stops being the tail's last two
// statements. So the only shape that can win is one where the pair stays last
// but is no longer a same-value same-class run: a *zero-emission* source
// statement between them (a redundant pointer assignment that CSE removes, or
// a cast that produces no RTL) is the one untried lever here. Do not re-grind
// the type/volatile/flag permutations — they are all measured above.
// 2026-10-22: the "zero-emission statement between the pair" lever was measured
// in four forms (`(void)v8;`, `p30 = p30;`, `if (v8) { }`, `(void)(v8 + 0);`)
// between the two stores: all eliminated before RTL, 95.65% unchanged. Making
// either store volatile is also unchanged (both: 84.78%, the tail re-schedules).
// PARKED 87.0% (old note): doc-15 arg-move transposition at fn_8021B55C call site ([li r4,0][mr r3,r28] want vs [mr][li] got); param-type flips, nv/volatile barriers on mgr/m2, comma staging, stmt reordering, mgr r28-pin, -fno-gcse/-fno-sched* all resist (87.0%). Body otherwise exact incl. frame + store schedule.
// family=m2c range=0x802227E0-0x80222898 size=184B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
extern char lbl_802AFED4[];
extern char lbl_802AFED8[];
extern char lbl_80305F9C[];
s32 fn_80137CB4(Unk_9F066EC1 * arg0);
s32 fn_80128294(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
s32 GetChecksum_4(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
s32 fn_8021B55C(void *arg0, s32 arg1);
s32 fn_8013DE78(void * arg0, Unk_C71E6DE1 * arg1);

bool ScriptFCFSRequestToggleProSet(CStruct *arg0) {
    struct {
        u8 blk[0x28];
        u8 sp30[4];
        s32 sp34;
        s32 pw;
        u8 pb;
    } fr;
    u8 *p30;
    Unk_6A78CE27 *pp;
    s32 v8;
    s32 v63;
    s32 v2;
    register u8 *pblk __asm__("r4");
    s32 mgr;
    s32 ret;

    mgr = *(s32 *)&lbl_80305F9C;
    fn_80137CB4(&fr.blk);
    p30 = &fr.sp30[0];
    fn_80128294((void *)arg0, (s32)lbl_802AFED4, p30, 1);
    GetChecksum_4((void *)arg0, (s32)lbl_802AFED8, &fr.sp34, 1);
    ret = fn_8021B55C((void *)mgr, 0);
    pp = &fr.pw;
    v8 = 8;
    v63 = 0x63;
    pp->unk0x4 = p30[3];
    v2 = 2;
    *(s32 *)((char *)fr.blk + 4) = (s32)pp;
    pblk = &fr.blk[0];
    fr.pw = fr.sp34;
    *(u8 *)((char *)fr.blk + 0) = (u8)v63;
    *(s32 *)((char *)fr.blk + 0xC) = v2;
    *(u8 *)((char *)fr.blk + 0x10) = (u8)v8;
    *(u16 *)((char *)fr.blk + 2) = (u16)v8;
    fn_8013DE78(ret, pblk);
    return true;
}

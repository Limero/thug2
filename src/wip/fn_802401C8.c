// WIP DRAFT (non-matching) — PARKED 2026-08-25
// Reached 21.6% (with -fno-schedule-insns; 18.1% plain). Remaining diffs:
// (1) temp_r9 web homes in saved r11 vs want scratch r9 (want's top-of-fn
//     `lwz r9,0x34(r30)` resists named-var/pin/per-case-web/GCSE-inline forms);
// (2) want RECYCLES r30 as the 3-store case base after temp_r30 dies — GCC
//     gives the base its own saved reg r29 -> frame 0x18 vs 0x10, stmw r29
//     vs stmw r30 (pin-a-copy + same-var reassignment both fail to coalesce);
// (3) upper subtree orientation: want keeps {9BF9,AF62} inline w/ bgt away to
//     {CC63,E113}; every if/goto shape emits the inverse or extra ble;
// (4) case-body block interleave (want: AF62,9BF9,E113,2D98,7DE1,AFFF,65B6,
//     CC63) not reproducible from flat switch (balance_case_nodes forbids the
//     2/5 root split), nested switches, or goto dispatch.
// Tried: flat switch x3 orders, phantom empty cases (root steering works:
// root=7DE1 achieved w/ 3 low phantoms but phantom pivot emits compares),
// nested if+switch x4 polarities, goto-dispatch chains, pins r30/r9/r11,
// vtbl web naming, per-case temps, -fno-sched-insns/-insns2/-gcse/-sched-spec.
// Callee ground truth: MemAvailable(s32)->s32; fn_80240614/fn_80240A6C/
// fn_80240AAC are 0-arg s32 (prologues overwrite r3). Reset-case hash is
// 0xAF6240B2 == QB_RESET (verified vs want lis -0x509e/ori 0x40b2 AND the
// game hash table; an earlier edit misdecoded the signed lis as 0xAF6140B2
// and wrongly blamed qb_constants.h — §6o-102 hazard-in-reverse).
// family=m2c range=0x802401C8-0x802403A0 size=472B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 18.6% ([1]rev->18.6%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_802FFE98;
extern char lbl_80306018[];
extern s32 lbl_80306064;
extern s32 lbl_80306068;
extern s32 lbl_8030606C;
s32 MemAvailable(Unk_C8FEE62D *);
void fn_80240614(void);
s32 fn_80240A6C(void);
s32 fn_80240AAC(void);
void fn_802401C8(s32 arg0) {
    CStruct *base;
    s32 v6c;
    register s32 *temp_r30 __asm__("r30");
    register s32 *base11 __asm__("r11");
    s32 temp_r9;

    temp_r30 = *(s32 **)((char *)*(void **)&lbl_802FFE98 + 0x11C);
    temp_r9 = ((Unk_C7387A53 *)temp_r30)->unk0x34;
    if ((u32)arg0 == 0x7DE18688u) {
        goto L_7de1;
    }
    if ((u32)arg0 > 0x7DE18688u) {
        goto L_up_root;
    }
    if ((u32)arg0 == 0x2D987043u) {
        goto L_2d98;
    }
    if ((u32)arg0 < 0x2D987043u) {
        return;
    }
    if ((u32)arg0 == 0x65B63305u) {
        goto L_65b6;
    }
    return;
L_up_root:
    if ((u32)arg0 == 0xAFFF3067u) {
        goto L_afff;
    }
    if ((u32)arg0 > 0xAFFF3067u) {
        goto L_up2;
    }
    if ((u32)arg0 == 0x9BF91DBEu) {
        goto L_9bf9;
    }
    if ((u32)arg0 != QB_RESET) {
        return;
    }
    goto L_af62;
L_up2:
    if ((u32)arg0 == 0xCC63F828u) {
        goto L_cc63;
    }
    if ((u32)arg0 != 0xE113C765u) {
        return;
    }
    goto L_e113;
L_af62:
    fn_80240614();
    return;
L_9bf9:
    base = temp_r30;
    base->unk0x48 =
        base->unk0x2C + MemAvailable(temp_r9);
    base->unk0x68 = fn_80240AAC();
    base->unk0x64 = v6c;
    v6c = fn_80240A6C();
    base = (s32 *)lbl_80306018;
    return;
L_e113:
    lbl_80306064 = ((Unk_C7387A53 *)temp_r30)->unk0x2C + MemAvailable(temp_r9);
    return;
L_2d98:
    lbl_80306068 = ((Unk_C7387A53 *)temp_r30)->unk0x2C + MemAvailable(temp_r9);
    return;
L_7de1:
    base11 = (s32 *)lbl_80306018;
    ((Unk_C7387A53 *)base11)->unk0x50 -=
        ((Unk_C7387A53 *)temp_r30)->unk0x2C + MemAvailable(temp_r9);
    return;
L_afff:
    lbl_8030606C = ((Unk_C7387A53 *)temp_r30)->unk0x2C + MemAvailable(temp_r9);
    return;
L_65b6:
    base11 = (s32 *)lbl_80306018;
    ((Unk_C7387A53 *)base11)->unk0x54 -=
        ((Unk_C7387A53 *)temp_r30)->unk0x2C + MemAvailable(temp_r9);
    return;
L_cc63:
    base = (s32 *)lbl_80306018;
    base->unk0x5C =
        ((Unk_C7387A53 *)temp_r30)->unk0x2C + MemAvailable(temp_r9);
    base->unk0x58 = ((Unk_C7387A53 *)temp_r30)->unk0x2C;
}

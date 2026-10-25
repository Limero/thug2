// WIP DRAFT — PARKED 2026-09-21 (rebuilt; was 54.9% with a WRONG frame).
// 2026-10-08: re-measured base = 12.7% (the 54.9% header is stale —
// some later edit regressed it). reload_pin_sweep WIN: retype the local
// `S21EEF4 *sp` -> `register S21EEF4 *sp __asm__("r3")` => official 84.5%
// (11 diffs). Only r3 binds: r11/r28/r29 spellings of the same pin re-measure
// at the 12.7% baseline, so GCC is rematerialising `&sp8` rather than holding
// the pointer. Residual 11 words are the prologue/pointer home: want keeps
// `addi r11, r1, 8` + `mr r28, r11` (home r28) and stores through r11, got
// stores through r3.
// family=m2c range=0x8021EEF4-0x8021F010 size=284B
// FLAG: -fno-schedule-insns2
// Net-lobby script command: seeds a 12-byte request record, branches on
// fn_80219698(arg0), then fn_8019915C/fn_801989CC on the lobby global,
// drains the list with fn_8021D454/fn_8021D4E8, and stamps
// arg0->unk0x1D8 = fn_800145AC().
//
// Rebuild fixes (each independently verified against want):
//   * the m2c `Unk_59AB5482 sp8;` is a 0x44-byte shared struct — it forced a
//     0x58 frame (want 0x28) and shifted every r1 displacement. want only
//     touches sp8+4 and sp8+8, so the record is a local 12-byte struct.
//   * `fn_80219698` is called with arg0 (r3 is never reloaded before the
//     bl) — m2c passed (s32)lbl_802A83F8, which made GCC emit a `mr r3,r9`.
//   * `fn_8019915C` is 2-arg `(s32, s32)` (matched callers
//     fn_80174AE8/fn_8015C6A8): `fn_8019915C(lbl_80305EC0, QB_NETLOBBY)`,
//     NOT the m2c 3-arg form (`*lbl_80305EC0` also failed on the extra arg0).
//
// PARKED — residual is the entry-block address materialization: the want
// loads the r9 high half, births sp+8 into scratch r11, completes the
// address with -0x7c08, zeroes r0 and homes arg0 into r31, then copies r11
// to the r28 home and performs the 8(r11) and 4(r11) stores. This draft
// births sp+8 directly into r28 and performs both stores off r28 with no
// copy.
// i.e. want keeps ONE extra live address pseudo (computed into scratch r11
// then copied to the callee-saved home r28 across the six calls); ngccc folds
// it into a single `addi r28,r1,8`. Because got is then 4 B short the masked
// word compare slips by one word and reports 12.7% — the 54.9% of the old
// draft was purely a length coincidence (its 0x58 frame kept 284 B). Tried:
// local struct vs `s32 sp8[3]`, a `S21EEF4 *sp` pointer for the stores (whole
// body or final store only), pointer assigned before/after the init stores —
// all land on 280 B / 12.7%. Everything downstream of the prologue is exact.
#include "types.h"
void fn_80229C38(void *);
void fn_8021FF74(void *arg0);
s32 fn_80219698(void *arg0);
#include "qb_constants.h"
#include "structs.h"
s32 fn_8021F748(s32);
extern char lbl_802A83F8[];
extern s32 lbl_80305EC0;
s32 fn_8021D454(CScript *arg0, void *arg1, s32 arg2);
s32 fn_800145AC(void);
void fn_801989CC(s32 arg0, s32 arg1);
s32 fn_80198B68(s32 arg0);
void fn_8019915C(s32 arg0, s32 arg1);
s32 fn_8021D4E8(CScript *arg0, void *arg1, s32 arg2);
s32 NextNewPlayerInfo(CScript *arg0);
void fn_8021F500(CScript *arg0);
void fn_8022A510(s32 arg0, s32 arg1);
s32 fn_80219A80(CScript *arg0);

typedef struct S21EEF4 {
    char pad0x0[4];
    s32 unk0x4;
    s32 unk0x8;
} S21EEF4;

void fn_8021EEF4(CScript *arg0) {
    S21EEF4 sp8;
    register S21EEF4 *sp __asm__("r3");
    s32 temp_r3;
    s32 var_r3;
    s32 var_r3_2;

    sp = &sp8;
    sp->unk0x8 = (s32)lbl_802A83F8;
    sp->unk0x4 = 0;
    if (fn_80219698(arg0) != 0) {
        arg0->unk0x2C = fn_8021F748((s32)arg0);
        var_r3 = fn_80219A80(arg0);
    } else {
        var_r3 = fn_80198B68(lbl_80305EC0);
    }
    arg0->unk0x28 = QB_NETLOBBY;
    fn_8019915C(lbl_80305EC0, QB_NETLOBBY);
    fn_801989CC(lbl_80305EC0, var_r3);
    arg0->unk0x34 = 0;
    fn_8021F500(arg0);
    temp_r3 = NextNewPlayerInfo(arg0);
    if (temp_r3 != 0) {
        fn_8022A510(temp_r3, 0);
    }
    var_r3_2 = fn_8021D454(arg0, &sp8, 1);
    if (var_r3_2 != 0) {
        do {
            fn_80229C38((void *)var_r3_2);
            var_r3_2 = fn_8021D4E8(arg0, &sp8, 1);
        } while (var_r3_2 != 0);
    }
    fn_8021FF74(arg0);
    arg0->unk0x1D8 = fn_800145AC();
    sp->unk0x8 = (s32)lbl_802A83F8;
}

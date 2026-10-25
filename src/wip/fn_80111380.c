// WIP DRAFT (non-matching) — semantic C rebuilt from the retail control flow.
// family=m2c range=0x80111380-0x80111574 size=500B
// PARKED 81.6% (102/125 reloc-masked words, GOT 496B vs WANT 500B): the
// prologue, frame, sector lookup, all eight GetFloat wrapper calls, the first
// five eager bitwise status reductions, helper ABI, and epilogue are exact.
// The sole blocker is the sixth status reduction. WANT retains two dead
// compares after v_freq — cmpwi r31,0 then cmpwi r3,0 — before loading the
// v_phase argument, but emits no branch, boolean materialization, or AND.
// A short-circuit && leaves only cmpwi r31 (the body below, 496B); a ternary
// leaves both compares plus an extra beq (504B); bitwise &/comparison
// expressions, discarded expressions, and loops either delete both compares
// or add code; -fno-thread-jumps is neutral. No semantic plain-C lowering found.
// ABI audit: script handler is (CStruct *, CScript *); GetChecksum_4 and
// fn_8012834C return s32 status, the latter writes f32; fn_800546A0 returns the
// sector pointer consumed by fn_800582F4. No inline asm is used.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// 2026-10-04 (bf): the -4B residual is ONE missing instruction — want's tail
// keeps BOTH `cmpwi r31,0` (found) and `cmpwi r3,0` (status) at 0x80111514/18
// and then DISCARDS the boolean (the next insn is just arg setup for the final
// fn_8012834C). Got keeps only the first. So retail computes a dead `found`;
// cc1 folds it away. Read as a DCE disagreement, not a source-shape one.
// Hypothesis tested and REJECTED: the source mixes `&` and `&&` in the found
// chain (five bitwise `&`, the last logical `&&`), and want's two compares look
// like the last one should also be bitwise. Measured: making the last one `&`
// is WORSE — 75.9% and the object SHRINKS to 464B (further from 500B); making
// all six `&&` is 24.6% / 456B. So the existing mix is load-bearing and is not
// the lever. Forcing the dead compare to survive would mean adding a use of
// `found`, which is a transcription rather than a match — not attempted.
#include "types.h"
#include "structs.h"
s32 GetChecksum_4(CStruct *, char *, s32 *, s32);
CStruct *fn_800546A0(s32);
s32 fn_8012834C(CStruct *, char *, f32 *, s32);
void fn_800582F4(CStruct *, f32, f32, f32, f32, f32, f32, f32, f32);
extern char lbl_8029CFC0[];
extern char lbl_8029CFC8[];
extern char lbl_8029CFD0[];
extern char lbl_8029CFD8[];
extern char lbl_8029CFE0[];
extern char lbl_8029CFE8[];
extern char lbl_8029CFF0[];
extern char lbl_8029CFF8[];
extern char lbl_8029D000[];
bool ScriptSetUVWibbleParams(CStruct *pParams, CScript *pScript) {
    f32 vPhase;
    f32 vFreq;
    f32 vAmp;
    f32 uPhase;
    f32 vVel;
    f32 uFreq;
    f32 uAmp;
    f32 uVel;
    s32 sectorHash;
    CStruct *sector;
    s32 found;
    s32 status;

    GetChecksum_4(pParams, lbl_8029CFC0, &sectorHash, 0);
    sector = fn_800546A0(sectorHash);
    found = fn_8012834C(pParams, lbl_8029CFC8, &uVel, 0);
    status = fn_8012834C(pParams, lbl_8029CFD0, &uAmp, 0);
    found = ((found != 0) & (status != 0));

    status = fn_8012834C(pParams, lbl_8029CFD8, &uFreq, 0);
    found = ((found != 0) & (status != 0));

    status = fn_8012834C(pParams, lbl_8029CFE0, &uPhase, 0);
    found = ((found != 0) & (status != 0));

    status = fn_8012834C(pParams, lbl_8029CFE8, &vVel, 0);
    found = ((found != 0) & (status != 0));

    status = fn_8012834C(pParams, lbl_8029CFF0, &vAmp, 0);
    found = ((found != 0) & (status != 0));

    status = fn_8012834C(pParams, lbl_8029CFF8, &vFreq, 0);
    found = ((found != 0) && (status != 0));

    fn_8012834C(pParams, lbl_8029D000, &vPhase, 0);
    fn_800582F4(sector, uVel, uAmp, uFreq, uPhase, vVel, vAmp, vFreq, vPhase);
    return true;
}

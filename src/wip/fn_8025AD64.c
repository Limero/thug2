// WIP DRAFT — hand-written from disassembly (PARKED)
// family=hand range=0x8025AD64-0x8025AE3C size=216B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
/*
PARK ANALYSIS (fragment of one hand-written system asm routine):
This is the CONTEXT-RESTORE / INTERRUPT-RETURN tail of the blob:
  lwz r4,0x6CC(r31); cmpwi r4,3; bne skip
  stw 0x1000 -> QB_UNKNOWN_0xCC003000              ; DI reset when ctx field == 3
  skip:
  li r5,0; stw r5,0x6BC(r31)
  bl fn_8025AF7C                        ; GPR-independent SPR restore
  bl fn_8025AFC0                        ; FPR restore fragment
  lwz r5,0x360(r31); mtcrf 0xFF,r5      ; restore ALL CR fields
  lwz r5,0x358(r31); mtlr r5            ; restore LR
  sth *(ctx+0x6C8) -> QB_UNKNOWN_0xCC004010        ; PE interrupt enable halfword
  stw 0 -> *0x803089B0                  ; clear a .data flag
  lwz r30..r13 from ctx+0xF0..+0x68     ; full callee-saved GPR restore
  lwz r2,0x10(r31); lwz r3,0x18(r31)
  lwz r1,8(r31); lwz r0,0(r31)          ; stack switch + LR into r0
  lwz r31,0xF8(r31)
  rfi                                   <- SUPERVISOR return-from-int
Blockers vs standalone ngccc C (all hard walls):
  1. `rfi` is privileged; no compiler path emits it (inline-asm-only);
  2. mtcrf 0xFF / MSR-class ops likewise;
  3. the body RESTORES r13-r31/r2/r1 from memory and then executes rfi —
     no C function can overwrite its own r1/r31 and keep executing;
  4. reads r31 with NO prologue save.
Not attempted beyond confirming each wall; whole-body asm transcription
is banned. Root cause: genuine hand-written interrupt/context-switch
code, dtk-split into pseudo-"functions"; not compiler-reachable.
Below: semantic C (inert, non-matching), privileged ops commented.
*/
register s32 *ctx_r31 __asm__("r31");

void fn_8025AF7C(void);
void fn_8025AFC0(void);

void Vtable0x80308A40_m5(void) {
    if (*(s32 *)((s32)ctx_r31 + 0x6CC) == 3) {
        *(volatile u32 *)QB_UNKNOWN_0xCC003000 = 0x1000;
    }
    *(u32 *)((s32)ctx_r31 + 0x6BC) = 0;
    fn_8025AF7C();
    fn_8025AFC0();
    /* mtcrf 0xFF, [ctx+0x360]  — CR restore */
    /* mtlr [ctx+0x358]         — LR restore */
    *(volatile u16 *)QB_UNKNOWN_0xCC004010 = *(u16 *)((s32)ctx_r31 + 0x6C8);
    *(volatile u32 *)0x803089B0 = 0;
    /* full GPR restore r13-r31 + r2 + r1 + r0 from ctx, then rfi */
}

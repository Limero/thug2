// WIP DRAFT — hand-written from disassembly (PARKED)
// family=hand range=0x8025AF18-0x8025AF7C size=100B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// UPDATED 2026-09-15: phantom-arg drop (addr-literal + bare-0 classes); now 17.2%.
/*
PARK ANALYSIS (fragment of one hand-written system asm routine):
"Send string over debug console" + SHARED TAIL entered from outside:
  entry 0x8025AF18: mr r5,r3; strlen-loop on arg0; mr r4,r3
  === label 0x8025AF3C is bl'd FROM fn_8025AE3C/fn_8025AEEC ===
  addi r3,r31,0x708; mr r28,r5; mflr r29
  bl fn_8025A1D0(r31+0x708, len, ...)
  stb 0xD -> (r31+0x700); sthbrx len -> (r31+0x702)
  lwz r0,0x6A4(r31); mtlr r0; blrl          ; vcall via ctx fn-ptr
  mtlr r29; blr
Blockers vs standalone ngccc C (hard walls):
  1. mid-body entry label 0x8025AF3C is a call target from OTHER
     dtk symbols — impossible for a standalone object;
  2. uses r28/r29/r31 with NO prologue saves;
  3. blrl dispatch through a context-held fn pointer.
Tried: file-scope global-register pin for r31 (proven on fn_8025AF7C);
blockers 1/2 are structural. Root cause: hand-written console/context
code sliced by dtk boundaries; not compiler-reachable standalone.
Below: semantic C (inert, non-matching).
*/
register s32 *ctx_r31 __asm__("r31");
void fn_8025A1D0(s32 a0, s32 a1);
static u32 dbg_strlen(const char *s) {
    const char *p = s;
    while (*p != 0) {
        p++;
    }
    return (u32)(s32)(p - s);
}
void fn_8025AF18(const char *str, s32 arg0) {
    u32 len = dbg_strlen(str);   /* WANT: subf r5,r3,r5 */
    /* --- shared tail (external entry @0x8025AF3C) ---
       r4 = str, r5 = len here */
    fn_8025A1D0((s32)ctx_r31 + 0x708, (s32)len);
    *(u8 *)((s32)ctx_r31 + 0x700) = 0xD;
    *(u16 *)((s32)ctx_r31 + 0x702) = 0;  /* sthbrx of len */
    {
        s32 (*cb)(s32, s32) = *(s32 (**)(s32, s32))((s32)ctx_r31 + 0x6A4);
        cb((s32)ctx_r31 + 0x700, 10);
    }
}

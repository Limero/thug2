// WIP DRAFT (non-matching) — hand-rebuilt body; see PARKED note.
// PARKED 2026-10-21: 95.7% (45/47, size-exact 188B). Only two words differ, and
// they are adjacent: the call's `li r3,0` and the `addi r27,r10,0x38` that
// materialises the walker. Want emits the argument set-up first and the addi
// last (directly before the call); this body emits the addi first. Every other
// word — frame, the whole lbl-store/`mr r24` prefix, the loop, the closing
// store and the call to the destructor — is byte-identical.
// family=m2c range=0x8019E194-0x8019E250 size=188B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// SEMANTICS: `dbl` (4 stack words at r1+8..0x18) receives the same rodata
// label at +0xC on entry and again just before fn_8009D020; in between
// fn_8009CFB8(0) returns a scratch buffer stored at r1+0x10 and addressed
// through r25, and four walker slots (a0+0x38, stride 4) each fix up one
// entry: fn_80009C00(entry), fn_8000A578(res+idxb+0xC, entry), then the two
// entry fields at +0x1C/+0x20 from res+8+idxb. fn_802336D8 is the promoted
// single-slot twin of this function and was used as the oracle for the
// frame/store/idiom choices.
//
// LOAD-BEARING (all measured on this body):
//  * `__asm__("" : : "m"(sp8), "m"(spC), "m"(pad0), "m"(pad1))` — the empty
//    memory-clobber statement is what keeps the 0x38 frame and the four-word
//    stack layout (dropping it collapses the body to ~15%, shrinking it to
//    one word of frame collapses it to ~66%).
//  * `__asm__("mr %0,%1" : "=&r"(a0) : "r"(arg0))` — emitting the arg copy as
//    a real asm `mr` (rather than a plain C assignment) is what places the
//    copy AFTER the label's high half and makes the rest of the prologue order
//    match (plain `a0 = arg0;` scores 78.7%).
//  * `__asm__ volatile("" : "+r"(res))` in the loop keeps res memory-backed so
//    the per-iteration reload and the loop tail stay exact.
//
// WHAT DID NOT HELP THIS ROUND (measured): moving the a0 assignment or the
// walker computation after the label store collapses the a0 copy (14.9-21.3%);
// a `+r` barrier on the walker moves the addi EARLIER (87.2%) rather than
// later; a `+r` barrier on count reaches 83.0% with the same prologue but a
// worse addi slot; loop-init forms (`for (walker = ..., count = 4; ...)`) put
// the addi after the call result store (56-60%); volatile casts on the label
// store, a pinned r27 walker, pointer-typed walker variants, `f64`-based
// stack layout and the 6 scheduling flags tried all score <= 95.7%.
//
// The remaining swap is a schedule2 priority tie between a constant set-up
// (li, ready immediately, short path) and the walker address (longer path into
// the loop). Both orders are legal for the source shape used here, so the
// parked body is the closest reproducible form; do not re-run statement-order
// permutations of the prologue without a new lever for that tie.
//
// Verify: object `.text` == 0xBC (188B, matches symbols.txt size:0xBC); only
// `.text` + `.rela.text`; relocations are 4 x ADDR16_HA/LO (all page 0x8029,
// five symbols) + 4 REL24 (fn_8009CFB8, fn_80009C00 x1, fn_8000A578 x1,
// fn_8009D020) and no REL14, matching the want's branch set.
#include "types.h"
extern char lbl_8029FD38[];
extern s32 fn_8009CFB8(s32);
extern void fn_80009C00(void *);
extern void fn_8000A578(void *, void *);
extern void fn_8009D020(void);
void fn_8019E194(void *arg0) {
    s32 sp8;
    s32 spC;
    s32 pad0;
    s32 pad1;
    void *walker;
    void *entry;
    char *fb;
    s32 res;
    s32 count;
    s32 idxb;
    s32 p;
    s32 temp;
    register void *a0 __asm__("r10");

    __asm__("" : : "m"(sp8), "m"(spC), "m"(pad0), "m"(pad1));
    *(s32 *)((char *)&sp8 + 0xC) = (s32)lbl_8029FD38;
    __asm__("mr %0,%1" : "=&r"(a0) : "r"(arg0));
    walker = (char *)a0 + 0x38;
    temp = fn_8009CFB8(0);
    *(s32 *)((char *)&spC + 4) = temp;
    count = 4;
    do {
        entry = *(void **)((char *)walker - 0x10);
        if (entry != NULL) {
            res = *(s32 *)((char *)&spC + 4);
            idxb = *(s32 *)walker * 0x94;
            fn_80009C00(entry);
            p = (s32)((char *)res + (idxb + 8));
            fn_8000A578((char *)p + 4, entry);
            __asm__ volatile("" : "+r"(res));
            fb = (char *)res + 8;
            *(s32 *)((char *)entry + 0x1C) = p + 0x50;
            *(s32 *)((char *)entry + 0x20) = *(s32 *)(fb + idxb);
        }
        walker += 4;
        count -= 1;
    } while (count != 0);
    *(s32 *)((char *)&sp8 + 0xC) = (s32)lbl_8029FD38;
    fn_8009D020();
}

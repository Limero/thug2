// WIP DRAFT (non-matching) — best body 52.5% (m2c baseline, keep!)
// PARKED (init-anchor wall; 3 probes + isolated pin tests, all worse):
// Full want-decode (see disasm 0x80137434/156 insns): init materializes the
// lbl_8029F190 address ONCE into r10 and reuses it for both structs, consts
// r0=-1/r8=0 shared the same way, counter `li r29,0` + fmt page anchor
// `lis r28,0x802A` placed MID-STORES, loop fmt via `addi r5,r28,-0xF94`
// (== lbl_8029F06C), idx byte-masked `clrlwi r30,r29,0x18`, B40 calls need a
// real 3-arg proto (want has NO crclr there), sprintf==fn_80269F4C keeps its
// crclr (implicit/varargs `(s32,...)`), tail countdown is mtctr/bdnz with
// `stb` zero stores, 0x61A80 stays a bare lis+ori literal.
// Tried: full typed rewrite incl. page-anchor var (9.6% — constant page
// const-folds to per-iter lis+ori, killing the anchor AND the frame span),
// `register ... __asm__("r28")` pin (10.9% — ProDG cc1 SILENTLY DROPS
// pointer pins (doc §76-178) AND const-folds even s32 pins; isolated -S
// probe proves `lis 0,0x8029` with no r28 traffic). The anchor needs an
// opaque single-lis web (reloc-derived pages need lis+addi; ha-rounding
// defeats &0xFFFF0000 masking) — no pure-C route found. A one-line
// `register s32 ... __asm__("r28")` fed by a NON-constant MIGHT work but was
// not found; full-body asm is banned (§4g/180).
// family=m2c range=0x80137434-0x801376A4 size=624B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// UPDATED 2026-09-15 (e): 52.5% -> 73.1%. m2c invented a *symbol* call argument: it read the lis/addi pair that materialises a label address as an extra arg. tools/label_arg_scan.py automated the A/B; keep the best body.
#include "types.h"
#include "structs.h"
void fn_80137AE4(s32, s32, s32);
extern char lbl_8029F06C[];
extern char lbl_8029F078[];
extern char lbl_8029F084[];
extern char lbl_8029F094[];
extern char lbl_8029F0A8[];
extern char lbl_8029F0BC[];
extern char lbl_8029F0D0[];
extern char lbl_8029F0E8[];
extern char lbl_8029F0FC[];
extern char lbl_8029F100[];
extern char lbl_8029F10C[];
extern char lbl_8029F124[];
extern char lbl_8029F130[];
extern char lbl_8029F13C[];
extern char lbl_8029F14C[];
extern char lbl_8029F160[];
extern char lbl_8029F16C[];
extern char lbl_8029F17C[];
extern char lbl_8029F190[];
void *fn_80137434(Unk_F386DC9F *arg0) {
    s32 var_ctr;
    s8 *var_r9;
    u8 temp_r30;
    u8 var_r29;
    Unk_C8FEE62D *temp_r11;
    Unk_C8FEE62D *temp_r9;

    temp_r9 = (char *)arg0 + 4;
    temp_r9->unk0x14 = (s32)lbl_8029F190;
    temp_r11 = (char *)arg0 + 0x1C;
    temp_r9->unk0x4 = -1;
    var_r29 = 0;
    temp_r9->unk0x8 = 0;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    temp_r11->unk0x14 = (s32)lbl_8029F190;
    temp_r11->unk0x4 = -1;
    temp_r11->unk0x8 = 0;
    temp_r11->unk0xC = temp_r11;
    temp_r11->unk0x10 = temp_r11;
    do {
        temp_r30 = var_r29;
        fn_80137AE4(arg0, temp_r30, (s32)lbl_8029F06C);
        var_r29 += 1;
        fn_80137B40(arg0, temp_r30, 0);
    } while ((s32) var_r29 <= 0xFE);
    fn_80137AE4(arg0, 1U, (s32)lbl_8029F078);
    fn_80137AE4(arg0, 2U, (s32)lbl_8029F084);
    fn_80137AE4(arg0, 3U, (s32)lbl_8029F094);
    fn_80137AE4(arg0, 4U, (s32)lbl_8029F0A8);
    fn_80137AE4(arg0, 5U, (s32)lbl_8029F0BC);
    fn_80137AE4(arg0, 6U, (s32)lbl_8029F0D0);
    fn_80137AE4(arg0, 7U, (s32)lbl_8029F0E8);
    fn_80137AE4(arg0, 8U, (s32)lbl_8029F0FC);
    fn_80137AE4(arg0, 0x11U, (s32)lbl_8029F100);
    fn_80137AE4(arg0, 0x10U, (s32)lbl_8029F10C);
    fn_80137AE4(arg0, 9U, (s32)lbl_8029F124);
    fn_80137AE4(arg0, 0xAU, (s32)lbl_8029F130);
    fn_80137AE4(arg0, 0xBU, (s32)lbl_8029F13C);
    fn_80137AE4(arg0, 0xCU, (s32)lbl_8029F14C);
    fn_80137B40(arg0, 9U, 1);
    fn_80137B40(arg0, 8U, 1);
    sprintf((char *)arg0 + 0x2140);
    sprintf((char *)arg0 + 0x2184, (s32)lbl_8029F16C);
    sprintf((char *)arg0 + 0x2194, (s32)lbl_8029F17C);
    var_ctr = 3;
    arg0->unk0x22FC = 5;
    arg0->unk0x2300 = 0;
    var_r9 = (char *)arg0 + 0x2174;
    arg0->unk0x22E8 = 0;
    arg0->unk0x2134 = 0;
    arg0->unk0x22F4 = 0;
    arg0->unk0x22F0 = 0;
    arg0->unk0x22F8 = 0;
    arg0->unk0x22EC = 0;
    do {
        *((s32 *)var_r9) = 0;
        var_r9 -= 0x10;
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk0x21A4 = 0;
    arg0->unk0x238C = 0x61A80;
    return arg0;
}

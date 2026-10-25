// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DDEA8-0x800DDF90 (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
// REBUILT 2026-10-11 from full want decode (58 words) — was a raw-m2c
// body parked at 11.3% DIFF. Rebuild notes: frame 0x120, stmw r30
// (r30=arg0, r31=&sp10); sp10 is a 256B char buffer @0x10 (0x10+0x100=0x110);
// sp110 @0x110 holds a char*; the F2BA8 call uses the TRUE x10 proto with
// sp8/spC (both 0) as the two stack args — the `stw r0,0xc/8` pair is their
// init, and declaring x8 instead deletes them as dead stores (was 56.9%);
// final word was the call's arg1: fresh `sp10`, not `mr r4,r31` (98.3%->EXACT).
// strstr-test is `or.` (pointer truthiness); lbl_8029A058 doubles as u32 const
// and NUL-string.
s32 fn_800F2BA8(s32, void *, s32, s32, s32, s32, s32, s32, s32, s32);
s32 GetText(CStruct *, s32, char **, s32);
char *strcat(char *, const char *);
char *strstr(const char *, const char *);
extern s32 lbl_8029A04C;
extern char lbl_8029A054[];
extern char lbl_8029A058[];
extern s32 lbl_80301B48;
void fn_800DDEA8(Unk_31DE137E *arg0, CStruct *arg1) {
    char *temp_r31;
    char sp10[0x100];
    s32 spC;
    s32 sp8;
    char *sp110;
    char *temp_r3;
    s32 w0;

    sp110 = 0;
    if (GetText(arg1, QB_MODEL, &sp110, 0) != 0) {
        w0 = lbl_8029A04C;
        temp_r31 = sp10;
        ((s32 *)sp10)[0] = w0;
        ((s32 *)temp_r31)[1] = *(&lbl_8029A04C + 1);
        strcat(temp_r31, sp110);
        temp_r3 = strstr(temp_r31, lbl_8029A054);
        if (temp_r3) {
            *(s32 *)temp_r3 = *(s32 *)lbl_8029A058;
        } else {
            strcat(temp_r31, lbl_8029A058);
        }
        spC = 0;
        sp8 = 0;
        arg0->unk0x1C = fn_800F2BA8(lbl_80301B48, sp10, 0, 0, 0, 0, 0, 0, sp8, spC);
    }
}

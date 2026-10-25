// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AA0BC-0x800AA1F4 (312B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ID: skater/animation-name table init — installs 16 fixed rodata strings
// (lbl_802982DC..) into a table of 0x24-byte slots at the given arg0
// offsets via fn_800AA080, then zeroes the counters at 0x274/0x278 and
// returns the object. Store order (0x274 before 0x278) is load-bearing.
// Suggested rename: InitNameTableEntries.
#include "types.h"
#include "structs.h"
extern char lbl_802982DC[];
extern char lbl_802982E0[];
extern char lbl_802982E8[];
extern char lbl_802982F0[];
extern char lbl_802982F8[];
extern char lbl_80298300[];
extern char lbl_80298308[];
extern char lbl_80298314[];
extern char lbl_80298318[];
extern char lbl_8029831C[];
extern char lbl_80298320[];
extern char lbl_80298324[];
extern char lbl_80298328[];
extern char lbl_8029832C[];
extern char lbl_80298330[];
extern char lbl_80298338[];
void fn_800AA080(Unk_31DE137E *, void *);
void *fn_800AA0BC(Unk_CFB386B2 *arg0) {
    fn_800AA080((char *)arg0 + 4, (s32)lbl_802982DC);
    fn_800AA080((char *)arg0 + 0x28, (s32)lbl_802982E0);
    fn_800AA080((char *)arg0 + 0x4C, (s32)lbl_802982E8);
    fn_800AA080((char *)arg0 + 0x70, (s32)lbl_802982F0);
    fn_800AA080((char *)arg0 + 0x190, (s32)lbl_802982F8);
    fn_800AA080((char *)arg0 + 0x16C, (s32)lbl_80298300);
    fn_800AA080((char *)arg0 + 0x1B4, (s32)lbl_80298308);
    fn_800AA080((char *)arg0 + 0x1D8, (s32)lbl_80298314);
    fn_800AA080((char *)arg0 + 0x94, (s32)lbl_80298318);
    fn_800AA080((char *)arg0 + 0xB8, (s32)lbl_8029831C);
    fn_800AA080((char *)arg0 + 0xDC, (s32)lbl_80298320);
    fn_800AA080((char *)arg0 + 0x100, (s32)lbl_80298324);
    fn_800AA080((char *)arg0 + 0x124, (s32)lbl_80298328);
    fn_800AA080((char *)arg0 + 0x148, (s32)lbl_8029832C);
    fn_800AA080((char *)arg0 + 0x1FC, (s32)lbl_80298330);
    fn_800AA080((char *)arg0 + 0x220, (s32)lbl_80298338);
    arg0->unk0x274 = 0;
    arg0->unk0x278 = 0;
    return arg0;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801018D0-0x8010192C (92B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800071D4(s32);
void fn_800FCF18(void);
void fn_801019C4(Unk_DB0E2BAB *, s32 *);
extern char lbl_8029C228[];
void *fn_801018D0(Unk_C7387A53 *arg0, void *arg1) {
    fn_800FCF18();
    arg0->unk0xC = (s32)lbl_8029C228;
    fn_800071D4((char *)arg0 + 0xB0);
    fn_801019C4(arg0, arg1);
    arg0->unk0xAC = 1;
    return arg0;
}

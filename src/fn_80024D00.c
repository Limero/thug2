// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80024D00-0x80024DA8 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern void fn_80060490(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void fn_80054388(s32, s32, void *);
extern s32 fn_800551B4(s32);
extern void fn_800551D4(void *);
extern char lbl_802913E8[];
void fn_80024D00(Unk_C7387A53 *arg0, s32 arg1) {
    s32 sp10[0x80];
    s32 sp8;

    if (arg0->unk0xC != 0) {
        fn_800551D4((void *)arg0->unk0xC);
        arg0->unk0xC = 0;
    }
    arg0->unk0xC = fn_800551B4(1);
    memset(sp10, 0, 0x200);
    fn_80054388(arg1, (s32)lbl_802913E8, sp10);
    sp8 = 0;
    fn_80060490(arg0->unk0xC, (s32)sp10, 0, 1, 0, 0, 0, 1, sp8);
}

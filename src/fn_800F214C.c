// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F214C-0x800F21E8 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8029B418[];
extern char lbl_8029B440[];
void fn_8009C838(void);
s32 Mem_Alloc2(s32);
s32 fn_800F321C(s32, s32);
void fn_800F2324(void *);
void *Mem_NewZero(s32);
void fn_80009B04(void *, s32);
void fn_800F31B4(void);

void *fn_800F214C(char *arg0) {
    register s32 tp __asm__("r28");
    s32 c;
    char *t;

    fn_8009C838();
    *(s32 *)(arg0 + 0x14) = (s32)lbl_8029B418;
    *(s32 *)(arg0 + 0x24) = fn_800F321C(Mem_Alloc2(0x18), 0xA);
    fn_800F2324(arg0);
    *(s32 *)(arg0 + 0x2C) = 0;
    *(s32 *)(arg0 + 0x28) = 0;
    *(s32 *)(arg0 + 0x1C) = 0;
    t = Mem_NewZero(0x24);
    tp = (s32)t;
    c = (s32)fn_800F31B4;
    fn_80009B04(t, 0);
    *(s32 *)((char *)tp + 0x1C) = c;
    *(s32 *)((char *)tp + 0x20) = (s32)arg0;
    *(s32 *)((char *)tp + 0x18) = (s32)lbl_8029B440;
    *(s32 *)(arg0 + 0x40) = (s32)t;
    return arg0;
}

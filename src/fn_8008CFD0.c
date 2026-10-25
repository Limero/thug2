// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8008CFD0-0x8008D05C (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80081794(void *);
s32 fn_8005CF80(Unk_9994C3F5 *, void *);
s32 fn_80067BEC();
extern s32 lbl_80366478;
extern char lbl_80296D10[];
extern char lbl_80296D28[];
void *fn_8008CFD0(Unk_3FE1622A *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s8 arg5) {
    Unk_C7387A53 *temp_r3;

    fn_80067BEC();
    arg0->unk0x20 = (s32)lbl_80296D10;
    arg0->unk0x8 = (s32)lbl_80296D28;
    arg0->unk0x17C = 0;
    temp_r3 = fn_8005CF80((Unk_9994C3F5 *)lbl_80366478, (void *)arg3);
    if (temp_r3 != NULL) {
        arg0->unk0x17C = (s32) temp_r3->unk0xC;
    }
    *(s8 *)&arg0->unk0x178 = (s8)fn_80081794((void *)arg4);
    *(s8 *)((char *)arg0 + 0x179) = arg5;
    return arg0;
}

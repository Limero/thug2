// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8008C2C0-0x8008C34C (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8006759C(void *);
s32 fn_8005CF80(Unk_9994C3F5 *, void *);
extern s32 lbl_80366478;
extern char lbl_80296C68[];
extern char lbl_80296C80[];
s32 fn_80081794(s32);
void *fn_8008C2C0(Unk_6C9FBB53 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s8 arg5) {
    Unk_C7387A53 *temp_r3;

    fn_8006759C(arg0);
    arg0->unk0x20 = (s32)lbl_80296C68;
    arg0->unk0x8 = (s32)lbl_80296C80;
    arg0->unk0x17C = 0;
    temp_r3 = (Unk_C7387A53 *)fn_8005CF80((Unk_9994C3F5 *)lbl_80366478, (void *)arg3);
    if (temp_r3 != NULL) {
        arg0->unk0x17C = (s32) temp_r3->unk0xC;
    }
    *(s8 *)&arg0->unk0x178 = (s8)fn_80081794(arg4);
    *(s8 *)((char *)arg0 + 0x179) = arg5;
    return arg0;
}

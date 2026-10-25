// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80081CBC-0x80081D48 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *Mem_Alloc(s32);
void fn_8006BD88(void *, s32);
extern char lbl_80296610[];
void *fn_80081CBC(Unk_C7387A53 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 cnt;
    u32 n;
    void *buf;

    fn_8006BD88(arg0, arg1);
    arg0->unk0x2C = arg2;
    arg0->unk0x30 = arg3;
    cnt = arg1 * 3;
    arg0->unk0x28 = (s32)lbl_80296610;
    buf = Mem_Alloc(arg1 * 0x48);
    n = (u32)cnt - 1;
    if (n != 0xffffffffu) {
        do {
        } while (n-- != 0u);
    }
    arg0->unk0x34 = (s32)buf;
    arg0->unk0x3C = arg5;
    arg0->unk0x38 = arg4;
    return arg0;
}

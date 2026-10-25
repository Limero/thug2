// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC808-0x800CC860 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8006B5FC(Unk_C7387A53 *, s32);
void fn_800CC808(Unk_C7387A53 *arg0) {
    register s32 nin __asm__("r9");
    CStruct *v;

    nin = arg0->unk0x28;
    goto chk;
bdy:
    __asm__("" : "+r"(v));
    fn_8006B5FC(v, arg0->unk0xC);
    nin = v->unk0xC;
chk:
    if (*(s32 *)((char *)nin + 4) == -1) {
        nin = 0;
    }
    v = (CStruct *)nin;
    if (v != NULL) {
        goto bdy;
    }
}

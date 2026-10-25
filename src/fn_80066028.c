// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80066028-0x800660E8 (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "mem.h"
#include "structs.h"
void fn_800551D4(void *);
void fn_80062DBC(Unk_EDE83D0E *, s32);
extern char lbl_802941A8[];
extern char lbl_802941C0[];
void fn_80066028(Unk_BBFD729E *arg0, s32 arg1) {
    s32 idx;
    u32 i;

    arg0->unk0x20 = (s32)lbl_802941A8;
    arg0->unk0x8 = (s32)lbl_802941C0;
    if (arg0->unk0x178 != 0) {
        Mem_Free2((void *)arg0->unk0x178);
        arg0->unk0x178 = 0;
    }
    if (arg0->unk0x180 != 0) {
        i = 0;
        if (i < arg0->unk0x170) {
            idx = 0;
            do {
                fn_800551D4(*(s32 *)((char *)idx + arg0->unk0x180));
                idx += 4;
                i += 1;
            } while (i < arg0->unk0x170);
        }
        if (arg0->unk0x180 != 0) {
            Mem_Free2((void *)arg0->unk0x180);
        }
        arg0->unk0x180 = 0;
    }
    fn_80062DBC(arg0, arg1);
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80165580-0x80165600 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_803A00D0[];
extern char lbl_803A00D8[];
void fn_80165580(s32 arg0, u16 arg1) {
    CStruct *temp_r3;
    s32 *p;
    u32 n;
    char *b;

    if ((arg1 == 0xFFFF) && (arg0 != 0)) {
        b = lbl_803A00D0;
        *(s32 *)(b + 4) = 0;
        temp_r3 = Mem_Alloc2(0xC);
        n = 5;
        *(s32 *)lbl_803A00D0 = (s32)temp_r3;
        temp_r3->unk0x8 = temp_r3;
        temp_r3->unk0x4 = temp_r3;
        p = (s32 *)lbl_803A00D8;
        do {
            *p = 0;
            p += 3;
            n--;
        } while (n != 0);
    }
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80191DBC-0x80191E30 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_80301A38[];

s32 fn_80191FD4();
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_800A398C(s32);

void fn_80191DBC(s32 arg0) {
    s32 sp8;
    s32 z;
    s32 h;
    register s32 v __asm__("r4");
    Unk_9994C3F5 *temp_r3;
    Unk_C6B642AC *temp_r9;

    s32 ret = fn_80191FD4();
    z = 0;
    __asm__("" : "+r"(z));
    h = QB_TRIGGER_OBJ_ID;
    __asm__("" : "+r"(h));
    sp8 = z;
    GetChecksum_2(ret, h, &sp8, 0);
    v = sp8;
    if (v != 0) {
        temp_r3 = (void *)fn_800A398C(*(s32 *)&lbl_80301A38);
        if (temp_r3 != NULL) {
            temp_r9 = *((void * *)&temp_r3->unk0x8);
            ((s32 (*)(void *))temp_r9->unk0x3C)((char *)temp_r3 + temp_r9->unk0x38);
        }
    }
}

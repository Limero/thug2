// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005C9A8-0x8005CA70 (200B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8005D1F8(void *);
s32 fn_8005D20C(void *, s32);
s32 fn_8005C5B4(void *);
void fn_8005D2C8(void *, s32 *);
void fn_8005C9A8(Unk_9994C3F5 *arg0, s32 arg1) {
    s32 sp8;
    void *temp_r30;
    void *var_r31;
    CStruct *temp_r9;
    s16 off;

    if (arg0->unk0x8 == 0) {
        return;
    }
    fn_8005D1F8((void *)arg0->unk0x8);
    var_r31 = (void *)fn_8005D20C((void *)arg0->unk0x8, 0);
    if (var_r31 == NULL) {
        return;
    }
    do {
        temp_r30 = (void *)fn_8005D20C((void *)arg0->unk0x8, 0);
        if ((arg1 != 0) || (((*(u16 *)((char *)var_r31 + 4)) & 1) == 0)) {
            sp8 = fn_8005C5B4(var_r31);
            if (var_r31 != NULL) {
                temp_r9 = ((CStruct *)var_r31)->unk0x8;
                off = *(s16 *)((char *)temp_r9 + 8);
                ((void (*)(void *, s32))*(s32 *)((char *)temp_r9 + 0xC))((char *)var_r31 + off, 3);
            }
            fn_8005D2C8((void *)arg0->unk0x8, &sp8);
        }
        var_r31 = temp_r30;
    } while (var_r31 != NULL);
}

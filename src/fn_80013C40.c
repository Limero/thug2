// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80013C40-0x80013CAC (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: sets the object's +0x14 callback table to lbl_80290888,
// then if the +0x18 child exists, dispatches its vtable entry at +0x1C with
// (child + s16 offset, 3); finally forwards to fn_8009C8A8(arg0, arg1). A
// setup/notify helper on the object vtable family.
#include "types.h"
#include "structs.h"
extern char lbl_80290888[];
void fn_8009C8A8(Unk_C8FEE62D *, s32);
void fn_80013C40(Unk_C8FEE62D *arg0, s32 arg1) {
    void *temp_r11;
    Unk_31DE137E *temp_r9;

    temp_r11 = arg0->unk0x18;
    arg0->unk0x14 = (s32)lbl_80290888;
    if (temp_r11 != NULL) {
        temp_r9 = ((CScript *)temp_r11)->unk0x18;
        ((s32 (*)(void *, s32))temp_r9->unk0x1C)(temp_r11 + * (s16 *) ((char *)temp_r9 + (s32)0x18), 3);
    }
    fn_8009C8A8(arg0, arg1);
}
// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802246D4-0x80224734 (96B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 lbl_80303148;
s32 fn_80222C2C(Unk_C7387A53 *, s32);
s32 fn_8013E2BC(Unk_440CB216 *);
s32 fn_8000A578(void *, s32);

bool fn_802246D4(Unk_C8FEE62D *arg0) {
    void *mgr = *((void * *)&arg0->unk0x18);
    s32 base = lbl_80303148;
    fn_80222C2C(mgr, 1);
    if (fn_8013E2BC(*((void * *)&arg0->unk0xC)) == 0) {
        fn_8000A578((char *)base + 8, ((Unk_FFAD6788 *)mgr)->unk0xDC);
    }
    return true;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DDF90-0x800DE000 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: if the object's QB_MODEL script property is set, resolves
// the +0x18 handler object and dispatches its vtable entry at +0x1C with
// (obj + s16 offset at +0x18, arg1). Script-property-driven vtable dispatch
// helper.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetText(CStruct *, void *, void *, void *);
void fn_800DDF90(CScript *arg0, CStruct *arg1) {
    s32 sp8;
    Unk_4E705049 *temp_r9;

    sp8 = 0;
    if (GetText(arg1, QB_MODEL, &sp8, 0) != 0) {
        temp_r9 = arg0->unk0x18;
        ((s32 (*)(void *, void *))temp_r9->unk0x1C)((char *)arg0 + temp_r9->unk0x18, arg1);
    }
}

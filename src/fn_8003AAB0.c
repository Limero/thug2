// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003AAB0-0x8003AB40 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
CStruct *CStruct_new(s32);
void CStruct_delete(CStruct *, s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void CStruct_dtor(CStruct *);
u8 *fn_80129EA0(CStruct *, u8 *);
CStruct *CStruct_ctor(CStruct *);
u8 *fn_8003AAB0(Unk_31DE137E *arg0, u8 *arg1) {
    Unk_80577C09 *context;
    CStruct *script;
    s32 has_value;

    context = (Unk_80577C09 *)((char *)arg0 + 0x58);
    script = CStruct_ctor(CStruct_new(8));
    arg1 = fn_80129EA0(script, arg1);
    CStruct_dtor(context);
    fn_80126FF4(context, script);
    if (script != NULL) {
        CStruct_delete(script, 3);
    }
    has_value = 1;
    if (*arg1 == 0) {
        has_value = 0;
    }
    arg0->unk0x64 = has_value;
    return arg1 + 1;
}

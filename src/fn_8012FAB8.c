// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012FAB8-0x8012FAFC (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: float-parameter pop helper for the scripted-parameter
// machine (m2c family, 0x8012F948 switch). Reads a 4-byte script token via
// fn_8012DC0C, converts it with CStruct_dtor and stores it to *(arg0+0x10);
// used by the Wibble/UV-scroll parameter ops (callers incl. fn_8012FDC0).
// Suggested rename: ScriptedParamPopFloat.
#include "types.h"
#include "structs.h"
s32 fn_8012DC0C(CStruct *, u8 *, CStruct *);
s32 CStruct_dtor(CStruct *);
void fn_8012FAB8(Unk_C8FEE62D *arg0) {
    CStruct_dtor(arg0->unk0x14);
    arg0->unk0x10 = fn_8012DC0C(arg0->unk0x14, arg0->unk0x10, arg0->unk0x18);
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004DD24-0x8004DD70 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// IDENTIFIED (2026-09-01): Script text/screen-element API cluster
// (0x8004Dxxx; m2c named siblings ScriptTextElementBackspace etc.) —
// sets the element name label lbl_80292A28 at obj+0x8, registers
// obj->0x190 as the active global via fn_8005DC6C, then activates via
// fn_8003F608(obj, arg1). Suggested rename: ScriptTextElementSetName /
// ScriptRegisterTextElement — no symbol.txt name exists yet.
#include "types.h"
#include "structs.h"
extern char lbl_80292A28[];
void fn_8005DC6C(CStruct *);
void fn_8003F608(Unk_E2A1CCEB *, void *);
void fn_8004DD24(Unk_4313CFEA *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_80292A28;
    fn_8005DC6C(arg0->unk0x190);
    fn_8003F608(arg0, arg1);
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80163920-0x80163958 (56B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 AddString(CStruct *, void *, void *);
extern char lbl_80305DF8[];
bool ScriptGetParkName(void *arg0, CScript *arg1) {
    AddString(arg1->unk0x18, QB_PARKNAME, lbl_80305DF8);
    return false;
}

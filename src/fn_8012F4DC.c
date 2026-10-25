// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012F4DC-0x8012F544 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80301A78[];
void fn_800A4B40(CStruct *, s32);
void fn_800A43A0(CStruct *, s32);
void fn_800A5CAC(CStruct *, s32);
void fn_8012F4DC(Unk_FFAD6788 *arg0) {
    if ((s32) arg0->unk0xE0 != 0) {
        fn_800A4B40((CStruct *)arg0->unk0xE0, (s32)arg0);
        fn_800A43A0((CStruct *)arg0->unk0xE0, QB_ALL_GROUPS);
    }
    if (arg0->unk0xCC & QB_UNKNOWN_0x08000000) {
        fn_800A5CAC(*(s32 *)&lbl_80301A78, (s32)arg0);
    }
}

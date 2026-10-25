// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018E868-0x8018E8C8 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct { char pad0x0[0x18C]; f32 unk0x18C; } Unk_Sk8;
s32 fn_801745B4(s32);
Unk_Sk8 *GetChecksum_3(s32, s32);
void AddInteger(s32, s32, s32);
extern s32 lbl_80305EAC;
void fn_8018E868(Unk_C7387A53 *arg0) {
    s32 t;
    s32 v;
    t = fn_801745B4(lbl_80305EAC);
    v = (s32)GetChecksum_3(t, QB_SKATERSTATE)->unk0x18C;
    AddInteger(arg0->unk0x20, QB_START_HEIGHT, v);
}

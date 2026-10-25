// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AD3DC-0x801AD448 (108B). Byte-identical.
#include "types.h"
#include "structs.h"

extern f32 lbl_802ABC0C;

// MATCHED
bool fn_801AD3DC(void *arg0, Unk_C7387A53 *arg1, Unk_C7387A53 *arg2) {
    if (fabs(*((f32 *)&arg1->unk0x28) - *((f32 *)&arg2->unk0x28)) > lbl_802ABC0C) {
        return false;
    }
    if (fabs(*((f32 *)&arg1->unk0x2C) - *((f32 *)&arg2->unk0x2C)) > lbl_802ABC0C) {
        return false;
    }
    if (fabs(*((f32 *)&arg1->unk0x30) - *((f32 *)&arg2->unk0x30)) > lbl_802ABC0C) {
        return false;
    }
    return true;
}

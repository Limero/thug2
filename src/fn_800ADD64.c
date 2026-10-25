// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800ADD64-0x800ADE30 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802985C4;
extern bool lbl_8030016C;
extern char lbl_80305EE4[];
s32 Script_GetInteger(s32, s32);
s32 fn_8000C394(void *);
void fn_800ADD64(Unk_4C4E48CA *arg0) {
    Unk_4C4E48CA *self;
    void *t;

    self = arg0;
    if (Script_GetInteger(QB_SKIPCUTSCENEABORT, 0) == 0) {
        if ((self->unk0x3464 != 0) && (*(f32 *)((char *)self + 0x3484) != lbl_802985C4)) {
            t = *(void **)((char *)*(void **)&lbl_80305EE4 + 0x28);
            if ((fn_8000C394(*(void **)((char *)t + 0x20)) != 0) && (*(s32 *)((char *)*(void **)((char *)t + 0x20) + 0x18) != 0) && (*(s32 *)((char *)*(void **)((char *)t + 0x1C) + 0x20) & 0x40)) {
                self->unk0x3468 = 1;
                *(f32 *)((char *)self + 0x3484) = self->unk0x3474;
            }
        }
        if (lbl_8030016C != 0) {
            self->unk0x3468 = 1;
            *(f32 *)((char *)self + 0x3484) = self->unk0x3474;
        }
    }
}

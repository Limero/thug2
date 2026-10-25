// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011A708-0x8011A7FC (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern f32 lbl_8029D508;
extern bool lbl_802FFE58;
s32 fn_80119470(void);
s32 fn_80119934(s32, s32);
s32 fn_8011970C(void *);
void fn_8011A450(s32, s32, f32 *, s32);
void fn_8011ED64(s32, void *, f32);
void Script_GetInteger(s32, s32);
typedef struct { s32 id1; s32 id2; void *unk0x8; char rest[0x30]; } PoolEnt;
extern PoolEnt lbl_80387E44[];
typedef struct { char pad[0x20]; f32 gain; } VoiceDef;
s32 fn_8011A708(void *arg0, s32 arg1, void *arg2, f32 farg0) {
    f32 sp8;
    f32 temp_f0;
    s32 idx;
    s32 var_r3;
    VoiceDef *ent;
    sp8 = farg0;
    if (fn_80119470() != 0) {
        return 1;
    }
    idx = fn_80119934(arg0, arg1);
    if (idx >= 0) {
        var_r3 = 0;
        ent = lbl_80387E44[idx].unk0x8;
        if (ent == NULL) {
            var_r3 = 0;
        } else {
            if (fn_8011970C(arg2) == 0) {
                fn_8011A450(arg0, arg2, &sp8, ent);
            }
            temp_f0 = sp8 * ent->gain * lbl_8029D508;
            sp8 = temp_f0;
            fn_8011ED64(idx, arg2, temp_f0);
            var_r3 = 1;
        }
    } else {
        if (lbl_802FFE58 == 0) {
            Script_GetInteger(QB_UNKNOWN_0x6D2E270E, 0);
        }
        var_r3 = 0;
    }
    return var_r3;
}

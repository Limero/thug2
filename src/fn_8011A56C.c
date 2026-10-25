// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011A56C-0x8011A6A8 (316B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80119470(void);
s32 fn_80119B24(s32, s32);
s32 fn_801198C8(s32, s32);
s32 fn_8011EF98(void *, s32, f32);
void fn_8011A450(s32, s32, f32 *, s32);
s32 fn_8011A4E4(s32, void *, s32, s32);
s32 fn_80119A08(s32, s32);
s32 Script_GetInteger(s32, s32);
extern bool lbl_802FFE58;
typedef struct S1A56C { s32 id1; s32 id2; void *unk0x8; char rest[0x30]; } S1A56C;
extern S1A56C lbl_80387E44[];
s32 fn_8011A56C(s32 arg0, s32 arg1, s32 arg2, f32 farg0, s32 arg3, s32 arg4) {
    s32 t;
    s32 idx;
    S1A56C *e;

    if (fn_80119470() != 0) {
        return 0;
    }
    t = fn_80119B24(arg0, arg1);
    if (t == 0) {
        return 0;
    }
    if (arg3 == 0) {
        arg3 = arg1;
    }
    if (lbl_802FFE58 == 0 && Script_GetInteger(QB_DEBUGSOUNDFX, 0) != 0 && arg4 == 0) {
        fn_801198C8(arg0, arg3);
    }
    fn_8011A450(arg0, arg2, &farg0, t);
    idx = fn_8011EF98((void *)(t + 0x14), arg2, farg0);
    if (idx == -1) {
        return 0;
    }
    e = &lbl_80387E44[idx];
    e->id2 = arg3;
    e->id1 = fn_80119A08(arg0, arg3);
    e->unk0x8 = (void *)t;
    fn_8011A4E4(arg0, &e->rest[0], t, arg4);
    if (lbl_802FFE58 == 0) {
        Script_GetInteger(QB_DEBUGSOUNDFX, 0);
    }
    return e->id1;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801D32A0-0x801D3314 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 fn_8014030C(s32, s32, Unk_FFAD6788 *);
void fn_801D3314(Unk_99111807 *);
void fn_801D33B8(Unk_17FD7108 *);
void fn_801D32A0(Unk_713AD995 *arg0) {
    s32 ctx = arg0->unk0xC;
    if (((arg0->unk0x320 != 0) || (*(s32 *)(arg0->unk0x15BC + 0xA0) != 0)) || (arg0->unk0x378 != fn_8014030C(QB_PHYSICS_ROLLING_FRICTION, 1, ctx))) {
        fn_801D3314(arg0);
        fn_801D33B8(arg0);
    }
}

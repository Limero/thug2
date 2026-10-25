// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004DF00-0x8004E0B4 (436B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void CScreenElement_SetProperties(void *, void *);
s32 CScreenElement_resolve_just(void *, void *, u32, void *, void *);
s32 GetInteger(void *, u32, s32 *, s32);
s32 GetFloat(void *, u32, f32 *, s32);
s32 ContainsFlag(void *, u32);
void CBaseMenu_SetProperties(Unk_31DE137E *arg0, CStruct *arg1) {
    register f32 *p __asm__("r29");
    f32 just[2] = {0, 0};
    s32 sp10;
    s32 sp14;
    s32 tmp;

    p = just;
    if (CScreenElement_resolve_just(arg0, arg1, QB_INTERNAL_JUST, p, p + 1) != 0) {
        *(f32 *)((char *)arg0 + 0x1A4) = *(f32 *)((char *)p + 4);
        *(f32 *)((char *)arg0 + 0x1A0) = just[0];
    }
    sp10 = 0;
    if (GetInteger(arg1, QB_REGULAR_SPACE_AMOUNT, &sp10, 0) != 0) {
        *(f32 *)((char *)arg0 + 0x1AC) = (f32)sp10;
    }
    GetFloat(arg1, QB_PADDING_SCALE, (f32 *)((char *)arg0 + 0x1B0), 0);
    sp14 = 0;
    if (GetInteger(arg1, QB_SPACING_BETWEEN, &sp14, 0) != 0) {
        *(f32 *)((char *)arg0 + 0x1B4) = (f32)sp14;
    }
    tmp = ContainsFlag(arg1, QB_ENABLE_PAD_HANDLING);
    if (tmp != 0) {
        *(s32 *)((char *)arg0 + 0x1B8) = 1;
    } else if (ContainsFlag(arg1, QB_DISABLE_PAD_HANDLING) != 0) {
        *(s32 *)((char *)arg0 + 0x1B8) = tmp;
    }
    tmp = ContainsFlag(arg1, QB_ALLOW_WRAP);
    if (tmp != 0) {
        *(s32 *)((char *)arg0 + 0x1BC) = 1;
    } else if (ContainsFlag(arg1, QB_DONT_ALLOW_WRAP) != 0) {
        *(s32 *)((char *)arg0 + 0x1BC) = tmp;
    }
    CScreenElement_SetProperties(arg0, arg1);
}

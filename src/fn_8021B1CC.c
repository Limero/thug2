// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021B1CC-0x8021B270 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_80137CB4(void *);
s32 fn_802201A4(CScript *);
s32 fn_8021B55C(CScript *, s32);
void fn_8013DE78(s32, void *);
void fn_8013E184(s32, s32);
void fn_8021B3E0(CScript *);
void fn_80009C00(void *);
void fn_80216D10(CScript *);

void fn_8021B1CC(CScript *arg0) {
    u8 sp8[0x28];
    s32 t;

    fn_80137CB4(sp8);
    if (fn_802201A4(arg0) == 9) {
        return;
    }
    if (fn_802201A4(arg0) == 7) {
        return;
    }
    if (fn_802201A4(arg0) == 8) {
        return;
    }
    t = fn_8021B55C(arg0, 0);
    sp8[0] = 0xB;
    fn_8013DE78(t, sp8);
    fn_8013E184(t, 0);
    fn_8021B3E0(arg0);
    fn_80009C00(*(void **)((char *)arg0 + 0xE8));
    fn_80216D10(arg0);
}

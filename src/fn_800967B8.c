// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800967B8-0x80096884 (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 pad;
} V4;

extern s32 lbl_803018A8;
extern f32 lbl_80297494;
extern f32 lbl_80297498;

s32 fn_80098C1C(s32, s32, s32);
void fn_8001D424(s32);
void C_MTX_LookAt(s32, s32, s32, s32);

void fn_800967B8(s32 arg0, V4 *arg1, V4 *arg2) {
    s32 sp18;
    V4 sp8;
    register V4 *p __asm__("r11");
    s32 temp_r3;
    s32 mgr;
    f32 eqA;
    f32 eqB;
    f32 neA;
    f32 neB;

    mgr = lbl_803018A8;
    sp18 = arg0;
    temp_r3 = fn_80098C1C(mgr, &sp18, 1);
    if (temp_r3 != 0) {
        fn_8001D424((s32)&sp8);
        if ((arg1->x == arg2->x) && (arg1->z == arg2->z)) {
            eqA = lbl_80297494;
            p = &sp8;
            eqB = lbl_80297498;
            p->y = eqA;
            p->z = eqB;
            sp8.x = eqA;
        } else {
            neA = lbl_80297494;
            p = &sp8;
            neB = lbl_80297498;
            sp8.x = neA;
            p->y = neB;
            p->z = neA;
        }
        C_MTX_LookAt(temp_r3 + 0xC, (s32)arg1, (s32)&sp8, (s32)arg2);
    }
}

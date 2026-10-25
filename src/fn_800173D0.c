// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800173D0-0x80017480 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-expensive-optimizations
#include "types.h"
void fn_80016AB0(void *o, float a, float b, float c);
void fn_800175CC(void *, void *, void *, void *, void *);
extern char C_MTXFrustum[];
void fn_80016AC4(void *o, float a, float b, float c);
#include "structs.h"
extern f32 lbl_80290C50;
extern f32 lbl_80290C54;
void fn_80016AD8(s32 arg0, f32 farg0, f32 farg1, f32 farg2);
void fn_800173D0(Unk_FFAD6788 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 t1;
    f32 t2;
    f32 t3;

    ((s32 (*)(s32, f32, f32, f32, f32, f32, f32)) C_MTXFrustum)((char *)arg0 + 0xC0, farg1, -farg1, -farg0, farg0, farg2, farg3);
    arg0->unk0xBC = 0;
    fn_800175CC(arg0, 0, 0, 0x200, 0x180);
    t1 = lbl_80290C50;
    t2 = t1;
    __asm__("" : "+f"(t2));
    t3 = t2;
    fn_80016AB0(arg0, t1, t2, t3);
    temp_f1_2 = lbl_80290C50;
    fn_80016AC4(arg0, temp_f1_2, lbl_80290C54, temp_f1_2);
    temp_f1_3 = lbl_80290C50;
    fn_80016AD8(arg0, temp_f1_3, temp_f1_3, lbl_80290C54);
}

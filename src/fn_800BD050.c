// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BD050-0x800BD1A0 (336B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetVector(CStruct *, s32, CStruct *, s32);
void CStruct_new(s32);
s32 CStruct_ctor();
void fn_80126F88(Unk_80577C09 *, CStruct *);
void fn_801279A0(CStruct *, s32, CStruct *);
s32 fn_8009F27C(CStruct *, Unk_15EF4A35 *, s32, s32, s32);
void fn_801309EC();
void CStruct_delete(CStruct *, s32);
s32 fn_8011A9FC(s32);
s32 fn_8012772C(CStruct *, s32, f32);
void fn_800CCD34(CScript *, CStruct *);
extern f32 lbl_80298E28;
extern f32 lbl_80298E2C;
extern char lbl_80302C34[];
void fn_800BD050(Unk_EE2F0A28 *arg0, void *arg1, f32 farg0) {
    __attribute__((aligned(16))) char sp8[16];
    __ps_t *q;
    if (farg0 > arg0->unk0xF0) {
        if (arg0->unk0xD0 != 0) {
            s32 handle;
            CStruct_new(8);
            handle = CStruct_ctor();
            if (arg0->unk0xDC != 0) {
                fn_80126F88(handle, arg0->unk0xDC);
            }
            ((__ps_t *)sp8)[0] = ((__ps_t *)arg1)[0];
            q = (__ps_t *)sp8;
            q[1] = ((__ps_t *)arg1)[1];
            fn_801279A0(handle, QB_BOUNCEPOS, q);
            fn_8009F27C(arg0->unk0xC, arg0->unk0xD0, handle, 0, 0);
            fn_801309EC();
            if (handle != 0) {
                CStruct_delete(handle, 3);
            }
        }
        if ((arg0->unk0x1A4 != 0) && (arg0->unk0xE4 != 0)) {
            s32 chk;
            chk = 0x3B - fn_8011A9FC(*(s32 *)&lbl_80302C34);
            __asm__("" :: "r"(chk));
            if (chk > 0xC) {
                f32 lim = arg0->unk0xF4;
                f32 mx = lbl_80298E28;
                f32 mn = lbl_80298E2C;
                register f32 t __asm__("fr0");
                register f32 v __asm__("fr13");
                register f32 w __asm__("fr1");
                t = farg0 * mx / lim;
                v = t;
                __asm__("" : "+f"(t));
                if (t > mx) {
                    v = mx;
                }
                w = v;
                __asm__("" : "+f"(v));
                if (v < mn) {
                    w = mn;
                }
                fn_8012772C(arg0->unk0xE4, QB_PERCENT, w);
                fn_800CCD34(arg0->unk0x1A4, arg0->unk0xE4);
            }
        }
    }
}

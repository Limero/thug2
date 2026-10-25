// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013B038-0x8013B130 (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void *fn_8013E034(void *arg0, void *sp);
void *fn_8013E068(void *arg0, void *sp);
void fn_8013F6E4(void *arg0);
s32 fn_8013F708(void *arg0);
s32 fn_8013C530(void *arg0, void *arg1);
s32 fn_8013C6F0(void *arg0, void *arg1);
void fn_8013E098(void *arg0, void *arg1);
extern char lbl_8029F480[];
typedef struct { char _0[0x68]; s32 f68; } Obj;
typedef struct { s32 u0; s32 u4; s32 u8; s32 _p0C; s32 s18; } Fr;
void fn_8013B038(void *arg0) {
    Fr fr;
    s32 var_r9;
    s32 f68v;
    s32 eight;
    void *temp_r29;
    Obj *var_r31;
    register Fr *q __asm__("r4");
    register Fr *p __asm__("r27");

    q = &fr;
    p = q;
    q->u8 = (s32)lbl_8029F480;
    q->u4 = 0;
    var_r31 = fn_8013E034(arg0, q);
    if (var_r31 != NULL) {
        do {
            eight = 8;
            temp_r29 = fn_8013E068(arg0, &fr);
            f68v = var_r31->f68;
            fr.s18 = eight;
            var_r9 = 1;
            if (!(f68v & 8)) {
                var_r9 = 0;
            }
            if ((var_r9 != 0) && (fn_8013C6F0(arg0, var_r31) == 0)) {
                fn_8013F6E4(var_r31);
            }
            if ((fn_8013F708(var_r31) == 0) && (fn_8013C530(arg0, var_r31) == 0) && (fn_8013C6F0(arg0, var_r31) == 0)) {
                fn_8013E098(arg0, var_r31);
            }
            var_r31 = temp_r29;
        } while (var_r31 != NULL);
    }
    p->u8 = (s32)lbl_8029F480;
}

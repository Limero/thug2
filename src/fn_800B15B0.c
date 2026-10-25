// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B15B0-0x800B16FC (332B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80301A38;
extern void *lbl_80301B0C;
typedef struct {
    char _p0[4];
    s32 f4;
    char _p8[0x50];
    s32 f58;
    s32 f5C;
    u32 f60;
    u32 f64;
    s32 f68;
    char _p6C[0x38];
    s32 fA4;
} T_15B0;
typedef struct {
    char _p[8];
    s32 f8;
    s32 fC;
} T_Node;
extern void *fn_800A398C(s32, s32);
extern void fn_8009F310(void *, s32, s32, s32, s32, s32);
void fn_800B15B0(T_15B0 *arg0, s32 arg1) {
    s32 temp_r0 = arg0->f58;
    if (temp_r0 != arg1) {
        if (temp_r0 != 0) {
            if (arg0->f5C != 0) {
                s32 var_r30 = 0;
                if (arg0->f60 != 0) {
                    do {
                        if (arg0->f60 & 1) {
                            void *var_r3 = fn_800A398C(lbl_80301A38, arg0->f5C + var_r30);
                            if (var_r3 != NULL) {
                                s32 *temp_r9 = *(s32 **)((char *)var_r3 + 8);
                                ((s32 (*)(void *))*(s32 *)((char *)temp_r9 + 0x3C))((char *)var_r3 + *(s16 *)((char *)temp_r9 + 0x38));
                            }
                        }
                        var_r30 += 1;
                    } while ((arg0->f60 >>= 1) != 0);
                }
            } else {
                T_Node *temp_r30 = (T_Node *)lbl_80301B0C;
                if (temp_r30 != NULL) {
                    s32 var_r28 = 0;
                    if (arg0->f64 != 0) {
                        do {
                            if (arg0->f64 & 1) {
                                void *var_r3 = fn_800A398C(lbl_80301A38, var_r28);
                                temp_r30->f8 = 0;
                                temp_r30->fC = 1;
                                if (var_r3 != NULL) {
                                    fn_8009F310(var_r3, arg0->fA4, arg0->f4, 0, 0, 0);
                                }
                                temp_r30->fC = 0;
                            }
                            var_r28 += 1;
                        } while ((arg0->f64 >>= 1) != 0);
                    }
                }
            }
        }
        arg0->f58 = arg1;
        arg0->f68 = -1;
    }
}

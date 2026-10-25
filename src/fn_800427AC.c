// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800427AC-0x80042924 (376B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct S427AC {
    char _00[0xC];
    s32 f_0C;
    char _10[0x180];
    char *f_190;
    u32 _194;
    s32 f_198;
} S427AC;

typedef struct Mgr427AC {
    char _00[0x124];
    s32 f_124;
} Mgr427AC;

extern Mgr427AC *lbl_802FFE98;

s32 strlen(const char *);
void Mem_Free(s32);
s32 Mem_Alloc(s32);
void fn_8000F2F8(void *, s32);
void fn_8000F320(void *);
s32 fn_800537FC(char *);
void fn_800586CC(void *, void *, void *, void *);
void fn_8003F93C(S427AC *, s32, f32, f32);

void fn_800427AC(S427AC *arg0, char *arg1) {
    s32 temp_r31;
    s32 temp_r28;
    char *var_r30;
    char *var_r31;
    u8 var_r9;
    f32 sp8;
    f32 spC;

    temp_r31 = strlen(arg1);
    temp_r28 = temp_r31 + 1;
    if (arg0->f_190 != 0) {
        if (strlen(arg0->f_190) >= temp_r31) {
            goto block_2;
        }
        if (arg0->f_190 != 0) {
            Mem_Free(arg0->f_190);
        }
    }
    fn_8000F2F8(lbl_802FFE98, lbl_802FFE98->f_124);
    arg0->f_190 = (char *)Mem_Alloc(temp_r28);
    fn_8000F320(lbl_802FFE98);
block_2:
    var_r30 = arg1;
    var_r31 = arg0->f_190;
    var_r9 = *(u8 *)var_r30;
    if (var_r9 != 0) {
        do {
            if (var_r9 == '\\') {
                if ((s8)var_r30[1] == '\\') {
                    var_r31[0] = var_r9;
                    *++var_r31 = *++var_r30;
                    var_r30++;
                    var_r31++;
                } else if ((s8)var_r30[1] == '_') {
                    var_r31[0] = ' ';
                    var_r30 += 2;
                    var_r31++;
                } else if ((s8)var_r30[1] == 'm') {
                    var_r31[0] = var_r9;
                    var_r30 += 2;
                    *++var_r31 = 'b';
                    *++var_r31 = fn_800537FC(var_r30++);
                    var_r31++;
                } else {
                    var_r31[0] = *(u8 *)var_r30;
                    var_r30++;
                    var_r31++;
                }
            } else {
                var_r31[0] = *(u8 *)var_r30;
                var_r30++;
                var_r31++;
            }
            var_r9 = *(u8 *)var_r30;
        } while (var_r9 != 0);
    }
    var_r31[0] = 0;
    if (arg0->f_198 != 0) {
        fn_800586CC(arg0->f_198, arg0->f_190, &sp8, &spC);
        if ((arg0->f_0C & 0x2000) == 0) {
            fn_8003F93C(arg0, 0, sp8, spC);
        }
    }
    arg0->f_0C = arg0->f_0C | 0x1000;
}

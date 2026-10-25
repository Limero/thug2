// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800093AC-0x800094D0 (292B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *Mem_Alloc(s32);
void Mem_Free2(void *);
typedef struct {
    char pad0x0[0x8];
    u8 *buf;
    s32 cap;
} Str_t;
void fn_800093AC(Str_t *arg0, s8 *arg1, s32 arg2, s32 arg3) {
    s32 var_r30;
    s32 var_r5;
    s32 var_r11;
    s8 c;
    u8 *p;

    if ((arg1 != NULL) && (arg3 >= arg2)) {
        c = arg1[arg2];
        if (c == 0) {
            if (arg0->buf != NULL) {
                Mem_Free2(arg0->buf);
            }
            p = (u8 *)Mem_Alloc(1);
            *p = c;
            arg0->buf = p;
            arg0->cap = 2;
            return;
        }
        var_r30 = (arg3 - arg2) + 2;
        if (var_r30 <= 3) {
            var_r30 = 4;
        }
        if (arg0->buf != NULL) {
            if (var_r30 > arg0->cap) {
                Mem_Free2(arg0->buf);
                arg0->buf = NULL;
            }
            if (arg0->buf == NULL) {
                goto block_12;
            }
        } else {
        block_12:
            arg0->cap = var_r30;
            arg0->buf = (u8 *)Mem_Alloc(var_r30);
        }
        var_r5 = arg2;
        var_r11 = 0;
        if (var_r5 <= arg3) {
            do {
                arg0->buf[var_r11] = arg1[var_r5];
                var_r5 += 1;
                var_r11 += 1;
            } while (var_r5 <= arg3);
        }
        arg0->buf[var_r11] = 0;
        return;
    }
    if (arg0->buf != NULL) {
        Mem_Free2(arg0->buf);
        arg0->buf = NULL;
    }
}

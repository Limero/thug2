// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80032588-0x80032610 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char p[0xC];
    s32 prio;
} Node32588;
typedef struct {
    char pad0[0x40];
    void *arr[6];
    s32 count;
} Rec32588;
void fn_80032588(Rec32588 *arg0, void *arg1, s32 arg2) {
    s32 i;
    s32 j;
    s32 cnt = arg0->count;
    void **w;
    void **base;

    i = 0;
    if (i < cnt) {
        register s32 wp __asm__("r11");
        wp = (s32)((char *)arg0 + 0x40);
        w = (void **)wp;
        base = w;
        do {
            Node32588 *x = (Node32588 *)*w;
            w = (void **)((char *)w + 4);
            if (arg2 > x->prio) {
                j = cnt;
                if (cnt > i) {
                    void **src = (void **)((char *)((s32)(j * 4) + (s32)base));
                    do {
                        j--;
                        *src = src[-1];
                        src--;
                    } while (j > i);
                }
                break;
            }
            i++;
            cnt = arg0->count;
        } while (i < cnt);
    }
    arg0->arr[i] = arg1;
    arg0->count = arg0->count + 1;
}

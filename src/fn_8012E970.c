// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012E970-0x8012EA18 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_8012DE30(s32);
s32 fn_8012543C(s32);
s32 fn_80125548(s32);
s32 fn_8012E88C(s32);
extern s32 lbl_803032BC;
extern s32 lbl_8039C530[];
typedef struct { char _0[4]; s32 f4; } S_t;
void fn_8012E970(void) {
    s32 i = 0;
    if (i < lbl_803032BC) {
        s32 b = (s32)lbl_8039C530;
        s32 *p = (s32 *)(b + 4);
        s32 off = 0;
        do {
            s32 w = *p;
            p += 2;
            if (w != 0) {
                fn_8012DE30(*(s32 *)((char *)off + b));
            } else {
                S_t *e = *(S_t **)((char *)off + b);
                fn_8012DE30(fn_8012543C(e->f4));
                fn_80125548(*(s32 *)((char *)off + b));
            }
            fn_8012E88C(*(s32 *)((char *)off + b));
            off += 8;
            i++;
        } while (i < lbl_803032BC);
    }
    lbl_803032BC = 0;
}

// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012570C-0x80125784 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern f32 lbl_8029E470;
typedef struct { char _0[0xC]; s32 iC; } SV;
typedef struct { char _0[0xC]; f32 fC; } FV;
void *fn_80125480(void);
f32 fn_8012570C(s32 arg0, s32 arg1) {
    void *p;
    u8 mode;
    p = fn_80125480();
    if (p == NULL) {
        goto dflt;
    }
    mode = *(u8 *)((char *)p + 2);
    if (mode != 1) {
        if (mode == 2) {
            return ((FV *)p)->fC;
        }
        goto dflt;
    }
    return (f32)(f64)(s32)((SV *)p)->iC;
dflt:
    return lbl_8029E470;
}

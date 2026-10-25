// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022F184-0x8022F1F0 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern s32 lbl_80301B40;
s32 fn_800F1F2C(s32, s32);
void fn_800F1E1C(s32, s32);
void *fn_8012543C(s32);
void fn_8012DE30(void *);
void fn_8022F184(s32 arg0) {
    s32 t = lbl_80301B40;
    void *node;
    if (fn_800F1F2C(t, QB_NODEARRAY) != 0) {
        fn_800F1E1C(t, QB_NODEARRAY);
        node = (void *)fn_8012543C(QB_NODEARRAY);
        if (node != 0) {
            fn_8012DE30(node);
        }
    }
}

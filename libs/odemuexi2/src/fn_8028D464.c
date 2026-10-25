// Dolphin db-module (OdemuExi2) - fn_8028D464
// mwcc GC/1.2.5n, cflags_odemuexi2.
// Branches through the registered fn-ptr at lbl_803CAF1C (r13 sdata-rel)
// if non-NULL.
#include "dolphin/types.h"
typedef void (*cb_t)(void);
extern cb_t lbl_803CAF1C;
void fn_8028D464(void) {
    if (lbl_803CAF1C != NULL) {
        lbl_803CAF1C();
    }
}
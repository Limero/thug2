// Promoted from src/wip (raw-lit sweep draft hand-refined to exact match).
// range 0x8005BA3C-0x8005BA68 (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80366458;
extern void fn_8007DD50(void);
void fn_8005BA3C(s32 *arg0) {
    lbl_80366458 = *arg0;
    fn_8007DD50();
}
